# execute with      python3 scattering_calibration_plot_metal_sheets.py

from numba import jit, cuda 
import pandas as pd 
import matplotlib.pyplot as plt 
import math
import numpy as np
import time
import csv
from scipy.optimize import curve_fit
from matplotlib.ticker import PercentFormatter



def time_cut_of_data(file_name, logbook_name, log_starting_point, file_number, list_of_x_positions, list_of_material_thicknesses):
    data = pd.read_csv(file_name, sep='\s+', names= ['Event', 'Timestamp', 'Width', 'Intensity'])
    logbook = pd.read_csv(logbook_name, sep='\s+', skiprows=(16+log_starting_point-1) , names= ['Event', 'X Position (mm)', 'Y Index', '[ADD 1] Position (deg)', '[ADD 2] Position (mm)' , '[ADD 3] Count ()', '[ADD 4] Charge (pC)', 'UNIX Time Stamp (seconds)'])
    logbook['Event'] = logbook['Event'].astype(int)
    logbook_list = ([])

    for i in range(len(list_of_x_positions)):
        if i==1:
            help_list=([logbook.loc[logbook['X Position (mm)'] == list_of_x_positions[i]], logbook.loc[logbook['X Position (mm)'] == 51.5]])
            help = pd.concat(help_list)             #Measurements on stage position 51.5 and 68.0 are actually the same thickness, here these two are merged
            logbook_list.append(help)
        else:
            logbook_list.append(logbook.loc[logbook['X Position (mm)'] == list_of_x_positions[i]])

    list_of_boundaries = [get_boundaries(logbook) for logbook in logbook_list]
    
    file_details = {
        0: (1712160150, 'Nickel_data/output_measurement_203_amended.csv'),
        1: (1712224363, 'Aluminum_data/output_measurement_211_amended.csv'),
        2: (1712235885.5, 'Aluminum_data/output_measurement_221_amended.csv')}
    timestamp_offset, output_filename = file_details[file_number]

    data_timestamps = data.loc[:, "Timestamp"]
    length_of_dataset = data_timestamps.shape[0]
    data_timestamp_array = data_timestamps.to_numpy()

    scan = timestamp_scan(list_of_x_positions, list_of_material_thicknesses, list_of_boundaries, timestamp_offset, length_of_dataset, data_timestamp_array)
    thickness_region_allocation = scan[0]
    thickness_allocation = scan[1]
    rows_to_drop = data.shape[0]- len(thickness_region_allocation)
    data.drop(data.tail(rows_to_drop).index, inplace = True)
    print("dropped ", rows_to_drop, " rows from data to be of same length with analysis")
    data.insert(4, "Stage x Position", thickness_region_allocation, True)
    data.insert(5, "Material Thickness", thickness_allocation, True)
    data.to_csv(output_filename, sep=',', index=False) 
    print('time-cut data successfully saved as ', output_filename)
@jit
def timestamp_scan(list_of_x_positions, list_of_material_thicknesses, list_of_boundaries, timestamp_offset, length_of_dataset, data_timestamp_array):
    thickness_region_allocation = []
    thickness_allocation = []
    
    for i in range(length_of_dataset):                                  #iteration over every datapoint of the measurement
        found = False
        for m in range(len(list_of_boundaries)):                        #iteration over every x position of the stage in logfile corresponding to material thickness 
            if found == True:
                break
            for l in range(len(list_of_boundaries[m][0])):              #iteration over every start and end point of measurement repetition
                start = list_of_boundaries[m][0][l] - timestamp_offset
                end = list_of_boundaries[m][1][l] - timestamp_offset
                print("Comparing:", start, "<= ", data_timestamp_array[i], "<=", end)
                if start <= data_timestamp_array[i] <= end:
                    thickness_region_allocation.append(list_of_x_positions[m])
                    thickness_allocation.append(list_of_material_thicknesses[m])
                    print("added", list_of_x_positions[m], "to slot: ", i)
                    found = True
                    break
                else:
                    print("skipped width for: ", i)
        if not found:
            thickness_region_allocation.append(0)
            thickness_allocation.append(0)

    return(thickness_region_allocation, thickness_allocation)

def get_boundaries(logbook_list):    
    log = logbook_list.loc[:, "Event"]              #Take a slice with only the Event numbers
    array = log.to_numpy()                          #convert event numbers into numpy array to compare consecutive entries if there is a skip to determine boundaries
    list_of_start_event_boundaries=([array[0]])
    list_of_end_event_boundaries=([])
    for i in range(1, len(array)):
        if array[i] > array[i-1]+1:
            list_of_start_event_boundaries.append(array[i])
            list_of_end_event_boundaries.append(array[i-1])
    list_of_end_event_boundaries.append(array[(len(array)-1)])

    start_time_boundaries=([])                  #When the corresponding events are found, those rows are searched and the timestamp will be given
    end_time_boundaries=([])
    for i in range(len(list_of_start_event_boundaries)):
        event_start_frame = logbook_list.loc[logbook_list['Event'] == list_of_start_event_boundaries[i]]
        event_end_frame = logbook_list.loc[logbook_list['Event'] == list_of_end_event_boundaries[i]]

        event_start_frame = event_start_frame.iloc[0, 7]
        event_end_frame = event_end_frame.iloc[0, 7]
        start_time_boundaries.append(event_start_frame)
        end_time_boundaries.append(event_end_frame)

    return start_time_boundaries, end_time_boundaries

def drop_unphysical_data(data_list):
    new_data = ([])
    for i in range(len(data_list)):
        help = data_list[i]
        help = help[help['Width'] < 100.0]
        new_data.append(help)
    return new_data

def get_mean(data, reference_mean):
    d = 75*10**(-3) # distance metal sheets <-> detector in m
    data.loc[:, ["Width"]] = (np.sqrt((data.loc[:, ["Width"]])**2 - (reference_mean[0])**2)) *(55*10**(-6))     #background deduction
    data.loc[:, ["Width"]] = (np.arctan(data.loc[:, ["Width"]]/d)*10**(+3))
    data_mean = data.loc[:, 'Width'].mean() 
    data_std = data.loc[:, 'Width'].var() 
    N = data.shape[0]

    return data_mean**2, data_std**2, N

def get_mean_alu(data, data_2, reference_mean, reference_mean_2):
    d = 75*10**(-3) # distance metal sheets <-> detector in m
    data.loc[:, ["Width"]] = (np.sqrt((data.loc[:, ["Width"]])**2 - (reference_mean[0])**2)) *(55*10**(-6))     #background deduction
    data_2.loc[:, ["Width"]] = (np.sqrt((data_2.loc[:, ["Width"]])**2 - (reference_mean_2[0])**2)) *(55*10**(-6))     #background deduction
    data.loc[:, ["Width"]] = (np.arctan(data.loc[:, ["Width"]]/d)*10**(+3))
    data_2.loc[:, ["Width"]] = (np.arctan(data_2.loc[:, ["Width"]]/d)*10**(+3))
    frames = [data, data_2]
    result = pd.concat(frames)
    N = data.shape[0]
    data_mean = result.loc[:, 'Width'].mean() 
    data_std = result.loc[:, 'Width'].std() 

    return data_mean**2, data_std**2, N

def separate_data(data, list_of_x_positions):
    return [
        data.loc[data['Stage x Position'] == list_of_x_positions[i]]
        for i in range(len(list_of_x_positions))
    ]

def ladderplot(data_list, dataset, list_of_x_positions, list_of_material_thicknesses):
    material = "nickel" if dataset==0 else "aluminium"
    widths=[]
    material_thicknesses=[]
    help=[]
    if dataset == 0:
        ladder_filename = f"Nickel_data/ladderplot_{material.lower()}"
    else:
        ladder_filename = f"Aluminum_data/ladderplot_{material.lower()}_dataset_{dataset}"

    for i in range(len(list_of_x_positions)):
        help = data_list[i].loc[:, "Width"]
        help = help.to_numpy()
        widths.append(help)

        help2 = data_list[i].loc[:, "Stage x Position"]
        help2 = help2.to_numpy()
        material_thicknesses.append(help2)

    fig, ax = plt.subplots(figsize=(10,10), layout='constrained')
    for i in range(len(list_of_x_positions)):
        ax.scatter(widths[i], material_thicknesses[i], label = list_of_material_thicknesses[i])
    ax.set_xlabel('Width (in pixels)', style='normal')
    ax.set_ylabel('Stage x position (in mm)')
    if dataset == 0:
        ax.set_title(f'Ladderplot {material}')
    else:
        ax.set_title(f'Ladderplot {material} dataset {str(dataset)}')
    ax.legend(title='Material thickness (mm):', fontsize=14)
    ax.grid()
    ax.set_axisbelow(True)
    if dataset == 1 or dataset == 2:
        plt.xlim([0, 35])
    else:  
        plt.xlim([0, 90])
    plt.savefig(ladder_filename, dpi = 300)
    print("Ladderplot saved as " + ladder_filename)

def gauss(x,a,mu,sigma):
    return a*np.exp(-(x-mu)**2/(2*sigma**2))

def histogram(data_list, dataset, list_of_x_positions, list_of_material_thicknesses):
    material = "nickel" if dataset==0 else "aluminium"
    widths=[]
    material_thicknesses=[]
    help=[]
    binning = 50 if dataset == 0 else 60
    histo_filename = (f"histogram_{material.lower()}_dataset_{dataset}_{binning}bins_lower_half")

    for i in range(len(list_of_x_positions)):
        help = data_list[i].loc[:, "Width"]
        help = help.to_numpy()
        widths.append(help)

        help2 = data_list[i].loc[:, "Stage x Position"]
        help2 = help2.to_numpy()
        material_thicknesses.append(help2)
        
    startparams_amplitude0 = [300,300,300,300,300,300,300,300,300,300,300,300,7000,7000]
    startparams_amplitude1 = [1,1,1,1,1,1,1,1,1,1,1,100,100,1]
    startparams_amplitude2 = [200,200,200,200,200,200,200,200,200,200,200,200,110,200]
    startparams_mu0 = [6,7,8,9,9,12,17,18,20,24,29,29,60,45]
    startparams_mu1 = [6,7,8,9,9,12,17,18,20,24,29,15,30,45]
    startparams_mu2 = [6,7,7,9,8,7,10,9,14,12,18,16,29,24]
    startparams_sigma0 = [1,1,1,1,2,2,2,2,3,3,3,3,3,3]
    startparams_sigma1 = [1,1,1,1,2,2,2,2,3,3,3,3,4,4]
    startparams_sigma2 = [1,1,1,1,2,2,2,2,3,3,3,3,2,4]
    binses_dataset0 = [24,4000,34,50,22,32,42,2200,28,32,70,34,400,120]
    binses_dataset1 = [24,28,34,50,36,32,54,30,28,32,56,34,86,62]
    binses_dataset2 = [24,28,34,50,36,32,54,30,22,32,42,34,80,52]
    colors = ["blue", "orange", "green", "red", "violet", "brown", "pink", "gray", "olive", "cyan", "blue", "orange", "red", "green" ]
    lowerhalf = [0,2,4,6,8,10]
    upperhalf = [1,3,5,7,9,11,12,13]
    all = [0,1,2,3,4,5,6,7,8,9,10,11,12,13]
    if dataset == 0:
        #plot_histo(lowerhalf, widths, startparams_amplitude0, startparams_mu0, startparams_sigma0, binses_dataset0, colors, list_of_material_thicknesses, dataset, material, histo_filename)
        #plot_histo(upperhalf, widths, startparams_amplitude0, startparams_mu0, startparams_sigma0, binses_dataset0, colors, list_of_material_thicknesses, dataset, material, histo_filename)
        plot_histo(all, widths, startparams_amplitude0, startparams_mu0, startparams_sigma0, binses_dataset0, colors, list_of_material_thicknesses, dataset, material, histo_filename)
    elif dataset == 1:
        #plot_histo(lowerhalf, widths, startparams_amplitude1, startparams_mu1, startparams_sigma1, binses_dataset1, colors, list_of_material_thicknesses, dataset, material, histo_filename)
        #plot_histo(upperhalf, widths, startparams_amplitude1, startparams_mu1, startparams_sigma1, binses_dataset1, colors, list_of_material_thicknesses, dataset, material, histo_filename)
        plot_histo(all, widths, startparams_amplitude1, startparams_mu1, startparams_sigma1, binses_dataset1, colors, list_of_material_thicknesses, dataset, material, histo_filename)
    else:
        #plot_histo(lowerhalf, widths, startparams_amplitude2, startparams_mu2, startparams_sigma2, binses_dataset2, colors, list_of_material_thicknesses, dataset, material, histo_filename)
        #plot_histo(upperhalf, widths, startparams_amplitude2, startparams_mu2, startparams_sigma2, binses_dataset2, colors, list_of_material_thicknesses, dataset, material, histo_filename)
        plot_histo(all, widths, startparams_amplitude2, startparams_mu2, startparams_sigma2, binses_dataset2, colors, list_of_material_thicknesses, dataset, material, histo_filename)

    plt.show()

def plot_histo(list_of_halves, widths, startparams_amplitude, startparams_mu, startparams_sigma, binses, colors, list_of_material_thicknesses, dataset, material, histo_filename):
    if len(list_of_halves) < 10:
        if dataset == 0:
            fig, ax = plt.subplots(figsize=(14,14), layout='constrained')
        else:
            fig, ax = plt.subplots(figsize=(10,10), layout='constrained')
    else:
        fig, ax = plt.subplots(figsize=(16,16), layout='constrained')
    for i in range(len(list_of_halves)):
        r = list_of_halves[i]
        max = widths[r].max()
        min = widths[r].min()
        bins = binses[r]
        binning = bins
        n, bins, patches = plt.hist(widths[r], log=False, alpha=0.7, bins=binning , label = list_of_material_thicknesses[r], color= colors[r])
        x = np.linspace(min, max, binning)
        y = n 
        popt,pcov = curve_fit(gauss,x,y,p0=[startparams_amplitude[r], startparams_mu[r], startparams_sigma[r]], maxfev=1000000)
        perr = np.sqrt(np.diag(pcov))
        print("The optimal parameters for fitting a gaussian to the width distribution of scattering from ", material, " with thickness " , list_of_material_thicknesses[i] , "mm are: ")
        print("amplitude " ,popt[0], ", mu ", popt[1], ", sigma ",abs(popt[2]))
        print("The errors on those are:\namplitude " ,perr[0], ", mu ", perr[1], ", sigma ",abs(perr[2]))
        print("")
        plt.plot(x,gauss(x,*popt), color="black")
    ax.set_xlabel('Width (in pixels)', style='normal')
    ax.set_ylabel('No. of counted width')
    ax.set_title(f'Histogram {material} dataset {str(dataset)} with changing bins')
    ax.legend(fontsize=10, shadow=True, title='Material thickness (mm):')
    ax.grid()
    ax.set_axisbelow(True)
    if len(list_of_halves) < 10:
        plt.ylim([1, 1000])
        if dataset == 1 or dataset == 2:
            plt.xlim([5, 25])
        else:  
            plt.xlim([5, 60])
            plt.ylim([1, 30000])
    elif dataset == 1 or dataset == 2:
        plt.ylim([0, 600])
        plt.xlim([5, 35])
    else: 
        plt.ylim([0, 6000])
        plt.xlim([5, 75])
        
    if list_of_halves[0] != 0:
        histo_filename = (f"histogram_{material.lower()}_dataset_{dataset}_{binning}bins_upper_half")
        plt.xlim([5, 35])
        if dataset == 0:
            plt.xlim([5, 90])
    plt.savefig(histo_filename, dpi = 300)
    print("Histogram saved as " + histo_filename)


def func(x, p0, p1, p2, p3, p4):
    return ((p0+p1*(x-p2)**0.5)*(p3+p4*x**2))

def calibrationplot(material_nickel, material_aluminum, means_list_nickel, means_list_aluminum, std_list_nickel, std_list_aluminum, N_list_nickel, N_list_aluminum):   
    radiation_length_nickel = 14.24                       #in mm                                   
    radiation_length_aluminum = 88.97                     #in mm   
    error_in_radiation_length = 0.002                     #considering the decimal value given by pdg 
    error_in_material_thickness = 0.0002                  #error in mm

    m = len(list_of_material_thicknesses_nickel)

    material_budget_nickel = ([])
    material_budget_aluminum = ([])
    material_budget_error_nickel = ([])
    material_budget_error_aluminum = ([])
    for i in range (1, m):
        material_budget_nickel.append(material_nickel[i]/radiation_length_nickel)
        material_budget_aluminum.append(material_aluminum[i]/radiation_length_aluminum)
        material_budget_error_nickel_i = np.sqrt(((error_in_material_thickness/radiation_length_nickel)**2+(error_in_radiation_length*material_nickel[i]/(radiation_length_nickel)**2)**2))
        material_budget_error_aluminum_i = np.sqrt(((error_in_material_thickness/radiation_length_aluminum)**2+(error_in_radiation_length*material_aluminum[i]/(radiation_length_aluminum)**2)**2))
        material_budget_error_nickel.append(material_budget_error_nickel_i)
        material_budget_error_aluminum.append(material_budget_error_aluminum_i)

    xerror_nickel = std_list_nickel/(np.sqrt(N_list_nickel))
    xerror_aluminum = std_list_aluminum/(np.sqrt(N_list_aluminum))
    nickel = {'Material budget nickel': material_budget_nickel, ' Material budget error': material_budget_error_nickel, ' mean-squared deviation angle from reference beam': means_list_nickel, ' xerror': xerror_nickel}
    plot_data_nickel = pd.DataFrame(data=nickel)
    aluminum = {'Material budget aluminium': material_budget_aluminum, ' Material budget error': material_budget_error_aluminum, ' mean-squared deviation angle from reference beam': means_list_aluminum, ' xerror': xerror_aluminum}
    plot_data_aluminum = pd.DataFrame(data=aluminum)
    plot_data_nickel.to_csv('Calibration_data/calibration_data_nickel.csv', sep=',', index=False)
    plot_data_aluminum.to_csv('Calibration_data/calibration_data_aluminum.csv', sep=',', index=False) 
    peek_data = pd.read_csv('../PEEK/Calibration_data/calibration_data_peek.csv', sep=',', skiprows=(1), names= ['Material Budget Peek', 'Material Budget error', 'mean-squared deviation angle from reference beam', 'xerror'])
    material_budget_peek = list(peek_data.iloc[:, 0])
    material_budget_error_peek = list(peek_data.iloc[:, 1])
    means_list_peek = list(peek_data.iloc[:, 2])
    xerror_peek = list(peek_data.iloc[:, 3])
    
    fit_data_means = *means_list_nickel, *means_list_aluminum, *means_list_peek
    fit_data_material_budgets = *material_budget_nickel, *material_budget_aluminum, *material_budget_peek
    fit_yerror = *material_budget_error_nickel, *material_budget_error_aluminum, *material_budget_error_peek
    fit_xerror = *xerror_nickel, *xerror_aluminum, *xerror_peek
    
    all_data = {'Material Budget ': fit_data_material_budgets, ' Material budget error': fit_yerror, ' mean-squared deviation angle from reference beam': fit_data_means, ' xerror': fit_xerror}
    plot_fit_data = pd.DataFrame(data=all_data)
    plot_fit_data.to_csv('Calibration_data/calibration_data_all.csv', sep=',', index=False) 
    
    fit_data_means_array = np.array(fit_data_means)
    fit_data_material_budgets_array = np.array(fit_data_material_budgets)
    fit_yerror_array = np.array(fit_yerror)
    fit_xerror_array = np.array(fit_xerror)
    
    
    #popt, pcov = curve_fit(polynom, fit_data_means_array, fit_data_material_budgets_array)              #The curve fit can be done with or without start value of parameters
    popt, pcov = curve_fit(func, fit_data_means_array, fit_data_material_budgets_array, method = 'lm', p0 = [-0.1, 0.3, -0.2, 1.2, 0.01]) 
    #popt, pcov = curve_fit(func, fit_data_means_array, fit_data_material_budgets_array, sigma=fit_yerror_array, absolute_sigma=True, method = 'lm', p0 = [-0.1, 0.3, -0.2, 1.2, 0.01])
    
    print('The fit parameters are:  p_0=%5.3f, p_1=%5.3f, p_2=%5.3f, p_3=%5.3f, p_4=%5.3f' % tuple(popt))
    condition_number_covariant_matrix = np.linalg.cond(pcov)                    #This is a measurement of overparametrization, everything under 50 is fine. Is it above chances are high there are redundant parameters
    print('Covariant Matrix condition number is: ', condition_number_covariant_matrix)
    matrix_diagonal = np.diag(pcov)                                             #In the Matrix diagonal one can see which parameters cause big uncertainties
    print('Matrix diagonal is: ', matrix_diagonal)

    fig, ax = plt.subplots(figsize=(14,14), layout='constrained')
    ax.scatter( means_list_nickel, material_budget_nickel, label = 'Nickel') #Plotting data onto the axes
    ax.errorbar( means_list_nickel, material_budget_nickel, yerr = material_budget_error_nickel , xerr = xerror_nickel, fmt="o")
    
    ax.scatter( means_list_aluminum, material_budget_aluminum, label = 'Aluminium') #Plotting data onto the axes
    ax.errorbar( means_list_aluminum, material_budget_aluminum, yerr = material_budget_error_aluminum , xerr = xerror_aluminum, fmt="o")
    
    ax.scatter( means_list_peek, material_budget_peek, label = 'PEEK') #Plotting data onto the axes
    ax.errorbar( means_list_peek, material_budget_peek, yerr = material_budget_error_peek , xerr = xerror_peek, fmt="o")
    highland_y=np.arange(0.0001, 1, 0.0001)
    ax.plot(highland(highland_y), highland_y, label = 'Highland prediction')
    ax.set_xscale('log')
    ax.set_yscale('log')
    ax.set_xlabel('$mean^2$ deviation angle from reference beam [$mrad^2$]', style='normal')            #think of a new name for mean... it's technically not a mean
    ax.set_ylabel('Material budget')
    ax.set_title('Calibration plot')
    ax.grid()
    ax.set_axisbelow(True)
    plt.xlim([1, 10000])
    plt.ylim([0.0001, 1])
    plt.savefig('metal_sheet_calibration_plot', dpi = 300)
    func_x=np.arange(1,10000)
    ax.plot(func_x, func(func_x, *popt), label='fit: p_0=%5.3f, p_1=%5.3f, p_2=%5.3f, p_3=%5.3f, p_4=%5.3f' % tuple(popt))
    ax.legend(fontsize = 14, shadow=True, title='fit function: (p0+p1*(x-p2)**0.5)*(p3+p4*x**2)')
    plt.savefig('all_data_fit_calibration_plot', dpi = 300)

def calibrationplot_both_alus(material_nickel, material_aluminum, means_list_nickel, means_list_aluminum_1, means_list_aluminum_2, std_list_nickel, _1, std_list_aluminum_2, N_list_nickel, N_list_aluminum_1, N_list_aluminum_2):
    radiation_length_nickel = 14.24                       #in mm                                   
    radiation_length_aluminum = 88.97                     #in mm   
    error_in_radiation_length = 0.002                     #considering the decimal value given by pdg 
    error_in_material_thickness = 0.0002                  #error in mm

    m = len(list_of_material_thicknesses)

    material_budget_nickel = ([])
    material_budget_aluminum = ([])
    highland_prediction_list = ([])
    material_budget_for_highland = ([])
    highland_prediction_list_nickel = ([])
    highland_prediction_list_aluminum = ([])
    material_budget_error_nickel = ([])
    material_budget_error_aluminum = ([])
    for i in range (1, m):
        material_budget_nickel.append(material_nickel[i]/radiation_length_nickel)
        material_budget_aluminum.append(material_aluminum[i]/radiation_length_aluminum)
        material_budget_error_nickel_i = np.sqrt(((error_in_material_thickness/radiation_length_nickel)**2+(error_in_radiation_length*material_nickel[i]/(radiation_length_nickel)**2)**2))
        material_budget_error_aluminum_i = np.sqrt(((error_in_material_thickness/radiation_length_aluminum)**2+(error_in_radiation_length*material_aluminum[i]/(radiation_length_aluminum)**2)**2))
        material_budget_error_nickel.append(material_budget_error_nickel_i)
        material_budget_error_aluminum.append(material_budget_error_aluminum_i)
        highland_prediction_list_nickel.append(highland(material_budget_nickel[i-1])[0])       #retrieves Theta**2 from Highland prediction
        highland_prediction_list_aluminum.append(highland(material_budget_aluminum[i-1])[0])       #retrieves Theta**2 from Highland prediction

    for i in range(len(highland_prediction_list_aluminum)):
        highland_prediction_list.extend((highland_prediction_list_aluminum[i], highland_prediction_list_nickel[i],))
        material_budget_for_highland.extend((material_budget_aluminum[i], material_budget_nickel[i]))

    xerror_nickel = std_list_nickel/(np.sqrt(N_list_nickel))
    xerror_aluminum_1 = std_list_aluminum_1/(np.sqrt(N_list_aluminum_1))
    xerror_aluminum_2 = std_list_aluminum_2/(np.sqrt(N_list_aluminum_2))
    nickel = {'Material Budget Nickel': material_budget_nickel, ' Material Budget error': material_budget_error_nickel, ' mean-squared deviation angle from reference beam': means_list_nickel, ' xerror': xerror_nickel}
    plot_data_nickel = pd.DataFrame(data=nickel)
    aluminum_1 = {'Material Budget Aluminum': material_budget_aluminum, ' Material Budget error': material_budget_error_aluminum, ' mean-squared deviation angle from reference beam': means_list_aluminum_1, ' xerror': xerror_aluminum_1}
    plot_data_aluminum_1 = pd.DataFrame(data=aluminum_1)
    aluminum_2 = {'Material Budget Aluminum': material_budget_aluminum, ' Material Budget error': material_budget_error_aluminum, ' mean-squared deviation angle from reference beam': means_list_aluminum_2, ' xerror': xerror_aluminum_2}
    plot_data_aluminum_2 = pd.DataFrame(data=aluminum_2)
    plot_data_nickel.to_csv('Calibration_data/calibration_data_nickel.csv', sep=',', index=False)
    plot_data_aluminum_1.to_csv('Calibration_data/calibration_data_aluminum_1.csv', sep=',', index=False) 
    plot_data_aluminum_2.to_csv('Calibration_data/calibration_data_aluminum_2.csv', sep=',', index=False)

    fig, ax = plt.subplots(figsize=(6,6), layout='constrained')
    ax.scatter( means_list_nickel, material_budget_nickel, label = 'Nickel') #Plotting data onto the axes
    ax.errorbar( means_list_nickel, material_budget_nickel, yerr = material_budget_error_nickel , xerr = xerror_nickel, fmt="o")
    ax.scatter( means_list_aluminum_1, material_budget_aluminum, label = 'Aluminium_1') #Plotting data onto the axes
    ax.errorbar( means_list_aluminum_1, material_budget_aluminum, yerr = material_budget_error_aluminum , xerr = xerror_aluminum_1, fmt="o")
    ax.scatter( means_list_aluminum_2, material_budget_aluminum, label = 'Aluminium_2') #Plotting data onto the axes
    ax.errorbar( means_list_aluminum_2, material_budget_aluminum, yerr = material_budget_error_aluminum , xerr = xerror_aluminum_2, fmt="o")
    ax.plot(highland_prediction_list, material_budget_for_highland, label = 'Highland prediction')
    ax.set_xscale('log')
    ax.set_yscale('log')
    ax.set_xlabel('$mean^2$ deviation angle from reference beam [$mrad^2$]', style='normal')            #think of a new name for mean... it's technically not a mean
    ax.set_ylabel('Material budget')
    ax.set_title('Calibration plot')
    ax.legend()
    ax.grid()
    ax.set_axisbelow(True)
    #plt.xlim([0, 35])
    plt.savefig('metal_sheet_calibration_plot_both_alu_datasets', dpi=300)
    plt.show()

def highland(material_budget):
    beam_energy_MeV = 154.5                                                                     #beam energy in MeV
    electron_mass = 0.510998950                                                                 #electron mass in MeV
    momentum = ((beam_energy_MeV)**2 - (electron_mass)**2)**(0.5)                               #relativistic momentum of electron beam
    lorentz_factor = np.sqrt(1+(momentum/electron_mass))    
    beta = np.sqrt(1-(1/lorentz_factor)**2)
    Theta = (13.6/(beta*momentum))*((material_budget)**(0.5))*(1+0.038*np.log(material_budget))  #Highland formula with c=1
    Theta = Theta*10**(+3)                                                                      #from rad to mrad
    return Theta**2

if __name__ == '__main__':
    plt.rcParams.update({'font.size': 18})
    start_time = time.time()
    list_of_x_positions = ([35.0, 68.0, 84.5, 101.0, 117.5, 134.0, 150.5, 167.0, 183.5, 200.0, 216.5, 233.0, 249.5, 266.0])       #266 is skipped because that is the second zero/reference measurement
    list_of_material_thicknesses_nickel = ([0.0, 0.025, 0.075, 0.05, 0.15, 0.1, 0.35, 0.25, 0.75, 0.5, 1.5, 1.0, 3.0, 2.0])     #in mm 
    list_of_material_thicknesses_aluminum = ([0.0, 0.025, 0.095, 0.07, 0.27, 0.2, 0.6, 0.4, 1.4, 1.0, 3.0, 2.0, 6.0, 4.0])
    files_list=(['Nickel_data/output_measurement_203.dat', 'Aluminum_data/output_measurement_211.dat', 'Aluminum_data/output_measurement_221.dat'])
    files_list_amen=(['Nickel_data/output_measurement_203_amended.csv', 'Aluminum_data/output_measurement_211_amended.csv', 'Aluminum_data/output_measurement_221_amended.csv'])
    ask = input("Do you want to do the time slicing of measurement data (no skips to analysis)?  ")
    if ask.lower() in ["y","yes"]:
        print("0 for nickel overnight \n1 for aluminum scan1 \n2 for aluminum scan2 ")
        dataset = int(input("Which dataset do you want to slice? "))
        if dataset == 0:
            list_of_material_thicknesses = list_of_material_thicknesses_nickel
        else:
            list_of_material_thicknesses = list_of_material_thicknesses_aluminum
        answer = input("This computation will take a long time to do (~1 hour), continue? ")
        if answer.lower() in ["y","yes"]:
            logbook_files_list = (['Nickel_data/eCTLogger_ni_overnight.txt', 'Aluminum_data/eCTLogger_al_shortscan1.txt', 'Aluminum_data/eCTLogger_al_shortscan2.txt'])
            list_of_log_starting_points = ([17, 654, 1])
            time_cut_of_data(files_list[dataset], logbook_files_list[dataset], list_of_log_starting_points[dataset], dataset, list_of_x_positions, list_of_material_thicknesses)
    else:
        ask = input("Do you want to create a ladderplot? ")
        if ask.lower() in ["y","yes"]:
            print("0 for nickel overnight \n1 for aluminum scan1 \n2 for aluminum scan2 ")
            dataset = int(input("Which dataset do you want to produce the ladderplot for? "))
            if dataset == 0:
                list_of_material_thicknesses = list_of_material_thicknesses_nickel.copy()
            else:
                list_of_material_thicknesses = list_of_material_thicknesses_aluminum.copy()
            data = pd.read_csv(files_list_amen[dataset], sep=',', skiprows=(1), names= ['Event', 'Timestamp', 'Width', 'Intensity', 'Stage x Position', 'Material Thickness'])
            data_list = separate_data(data, list_of_x_positions) 
            ask2 = input("Do you want to drop unphysical data? ")    #all data points with width > 100 will be dropped
            if ask2.lower() in ["y","yes"]:
                data_list = drop_unphysical_data(data_list)
            ladderplot(data_list, dataset, list_of_x_positions, list_of_material_thicknesses)
        ask = input("Do you want to create a histogram? ")
        if ask.lower() in ["y","yes"]:
            print("0 for nickel overnight \n1 for aluminum scan1 \n2 for aluminum scan2 ")
            dataset = int(input("Which dataset do you want to produce the histogram for? "))
            if dataset == 0:
                list_of_material_thicknesses = list_of_material_thicknesses_nickel.copy()
            else:
                list_of_material_thicknesses = list_of_material_thicknesses_aluminum.copy()
            files_list_amen=(['Nickel_data/output_measurement_203_amended.csv', 'Aluminum_data/output_measurement_211_amended.csv', 'Aluminum_data/output_measurement_221_amended.csv'])
            data = pd.read_csv(files_list_amen[dataset], sep=',', skiprows=(1), names= ['Event', 'Timestamp', 'Width', 'Intensity', 'Stage x Position', 'Material Thickness'])
            data_list = separate_data(data, list_of_x_positions) 
            histogram(data_list, dataset, list_of_x_positions, list_of_material_thicknesses)
        ask = input("Do you want to produce a calibration plot? ")
        if ask.lower() in ["y","yes"]:
            data_nickel = pd.read_csv(files_list_amen[0], sep=',', skiprows=(1), names= ['Event', 'Timestamp', 'Width', 'Intensity', 'Stage x Position', 'Material Thickness'])
            data_list_nickel = separate_data(data_nickel, list_of_x_positions)
            data_list_nickel = drop_unphysical_data(data_list_nickel)
            data_aluminum = pd.read_csv(files_list_amen[1], sep=',', skiprows=(1), names= ['Event', 'Timestamp', 'Width', 'Intensity', 'Stage x Position', 'Material Thickness'])
            data_list_aluminum = separate_data(data_aluminum, list_of_x_positions)
            data_list_aluminum = drop_unphysical_data(data_list_aluminum)
            data_aluminum_2 = pd.read_csv(files_list_amen[2], sep=',', skiprows=(1), names= ['Event', 'Timestamp', 'Width', 'Intensity', 'Stage x Position', 'Material Thickness'])
            data_list_aluminum_2 = separate_data(data_aluminum_2, list_of_x_positions)
            data_list_aluminum_2 = drop_unphysical_data(data_list_aluminum_2)                   
            
            means_list_nickel = ([])
            std_list_nickel = ([])
            N_list_nickel = ([])
            means_list_aluminum = ([])
            std_list_aluminum = ([])
            N_list_aluminum = ([])
            means_list_aluminum_1 = ([])
            std_list_aluminum_1 = ([])
            N_list_aluminum_1 = ([])
            means_list_aluminum_2 = ([])
            std_list_aluminum_2 = ([])
            N_list_aluminum_2 = ([])
            
            reference_nickel = ([])
            reference_aluminum = ([])
            reference_aluminum_2 = ([])
            data_ref_nickel = data_list_nickel[0]
            reference_nickel.append(data_ref_nickel.loc[:, 'Width'].mean()) 
            reference_nickel.append(data_ref_nickel.loc[:, 'Width'].std())
            reference_nickel.append(data_ref_nickel.shape[0])
            data_ref_aluminum = data_list_aluminum[0]
            reference_aluminum.append(data_ref_aluminum.loc[:, 'Width'].mean())
            reference_aluminum.append(data_ref_aluminum.loc[:, 'Width'].std())
            reference_aluminum.append(data_ref_aluminum.shape[0])
            data_ref_aluminum_2 = data_list_aluminum_2[0]
            reference_aluminum_2.append(data_ref_aluminum_2.loc[:, 'Width'].mean())
            reference_aluminum_2.append(data_ref_aluminum_2.loc[:, 'Width'].std())
            reference_aluminum_2.append(data_ref_aluminum_2.shape[0])
            
            for i in range (1, len(data_list_nickel)):
                help_nickel = get_mean(data_list_nickel[i], reference_nickel)
                means_list_nickel.append(help_nickel[0])
                std_list_nickel.append(help_nickel[1])
                N_list_nickel.append(help_nickel[2])
                help_aluminum = get_mean_alu(data_list_aluminum[i], data_list_aluminum_2[i], reference_aluminum, reference_aluminum_2)
                help_aluminum_1 = get_mean(data_list_aluminum[i], reference_aluminum)
                #help_aluminum_2 = get_mean(data_list_aluminum_2[i], reference_aluminum_2)
                means_list_aluminum.append(help_aluminum[0])
                std_list_aluminum.append(help_aluminum[1])
                N_list_aluminum.append(help_aluminum[2])
                means_list_aluminum_1.append(help_aluminum_1[0])
                std_list_aluminum_1.append(help_aluminum_1[1])
                N_list_aluminum_1.append(help_aluminum_1[2])
                #means_list_aluminum_2.append(help_aluminum_2[0])
                #std_list_aluminum_2.append(help_aluminum_2[1])
                #N_list_aluminum_2.append(help_aluminum_2[2])
                        
            calibrationplot(list_of_material_thicknesses_nickel, list_of_material_thicknesses_aluminum, means_list_nickel, means_list_aluminum, std_list_nickel, std_list_aluminum, N_list_nickel, N_list_aluminum)
            #calibrationplot(list_of_material_thicknesses_nickel, list_of_material_thicknesses_aluminum, means_list_nickel, means_list_aluminum_1, std_list_nickel, std_list_aluminum_1, N_list_nickel, N_list_aluminum_1)
            #calibrationplot_both_alus(list_of_material_thicknesses_nickel, list_of_material_thicknesses_aluminum, means_list_nickel, means_list_aluminum_1, means_list_aluminum_2, std_list_nickel, std_list_aluminum_1, std_list_aluminum_2, N_list_nickel, N_list_aluminum_1, N_list_aluminum_2)
        plt.show()
    end_time = time.time()
    print("Computing time was:  ", round(end_time - start_time, 2), " s")
    print("Which in minutes is: ", round((end_time - start_time)/60, 2) , " min")


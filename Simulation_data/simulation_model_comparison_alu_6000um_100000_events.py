# execute with      python3 simulation_time_measurement.py

import pandas as pd
import time
import os

if __name__ == '__main__':
    Batch_begin = time.time()
    os.system('source ../../allpix-squared/.ci/init_x86_64.sh')
    config = 'EM_modules.conf'
    cores = '60'
    #thicknesses_alu = ['70um', '200um', '270um', '400um', '600um', '1000um', '1400um', '2000um', '3000um', '4000um', '6000um']
    #thicknesses_alu = ['3000um', '4000um', '6000um']
    thicknesses_alu = ['6000um']
    material = 'alu'
    events = '100000'
    EM_modules_list = ["EM_Opt1","EM_Opt3"]
    EM_modules_mark = ["_EMV", "_EMY"]
    differences = []
    thick_list = []
    EM_model_list = []
    material_list = []
    
    for i in range(len(thicknesses_alu)):
        thick = thicknesses_alu[i]
        geometry_file = 'geometries/geometry_{}_{}.conf'.format(material, thick)
        directory = 'Simulation_data/{}_{}_{}_events'.format(material, thick, events)
        
        for j in range(len(EM_modules_list)):
            module = EM_modules_list[j]
            module_mark = EM_modules_mark[j]
            print("Starting EM Module: ", module)
            output_directory = directory + '/%s' % (module)
            start_time = time.time()
            if module == "EM_Opt1":
                command = '../../allpix-squared/install/bin/allpix -c %s -j%s -o output_directory="%s" -o detectors_file="%s" -o number_of_events="%s" -o physics_list="FTFP_BERT%s" -o msc_energy_limit=100MeV' % (config, cores, output_directory, geometry_file, events, module_mark)
            else:
                command = '../../allpix-squared/install/bin/allpix -c %s -j%s -o output_directory="%s" -o detectors_file="%s" -o number_of_events="%s" -o physics_list="FTFP_BERT%s"' % (config, cores, output_directory, geometry_file, events, module_mark)
            os.system(command)
            end_time = time.time()
            print("Computing time was:  ", round(end_time - start_time, 2), " s")
            print("Which in minutes is: ", round((end_time - start_time)/60, 2) , " min")
            diff = end_time - start_time
            differences.append(diff)
            thick_list.append(thick)
            EM_model_list.append(module)
            material_list.append(material)
    
    timestamp = {'Computing Time': differences, 'Material': material_list, 'Thickness': thick_list, 'EM_Model': EM_model_list}
    time_data = pd.DataFrame(data=timestamp)
    time_file = 'timing_data/computing_time_6000um_high_statistics_Wentzel_Urban.csv'
    time_data.to_csv(time_file, sep=',', index=False)
    
    Batch_end = time.time()
    print('The complete processing time of this script was: ', round(Batch_end - Batch_begin, 2), " s")
    print("Which in minutes is: ", round((Batch_end - Batch_begin)/60, 2) , " min")
    print("And in hours is: ", round((Batch_end - Batch_begin)/3600, 2) , " h")

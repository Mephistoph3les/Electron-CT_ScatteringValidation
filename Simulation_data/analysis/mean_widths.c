#include <string>
#include "TCanvas.h"
#include "TROOT.h"
#include "TGraphErrors.h"
#include "TF1.h"
#include "TLegend.h"
#include "TArrow.h"
#include "TLatex.h"
#include "math.h"

void mean_widths() {
    string events = "10000";
    string material = "aluminum";
    string thick = "all";

    string data_Opt1_0um = "../alu_0um_1000_events/EM_Opt1/Corryoutput/histograms.root";
    string data_Opt3_0um = "../alu_0um_1000_events/EM_Opt3/Corryoutput/histograms.root";
    string data_Opt4_0um = "../alu_0um_1000_events/EM_Opt4/Corryoutput/histograms.root";

    string data_Opt1_70um = "../alu_70um_1000_events/EM_Opt1/Corryoutput/histograms.root";
    string data_Opt3_70um = "../alu_70um_10000_events/EM_Opt3/Corryoutput/histograms.root";
    string data_Opt4_70um = "../alu_70um_10000_events/EM_Opt4/Corryoutput/histograms.root";

    string data_Opt1_200um = "../alu_200um_1000_events/EM_Opt1/Corryoutput/histograms.root";
    string data_Opt3_200um = "../alu_200um_10000_events/EM_Opt3/Corryoutput/histograms.root";
    string data_Opt4_200um = "../alu_200um_10000_events/EM_Opt4/Corryoutput/histograms.root";

    string data_Opt1_270um = "../alu_270um_1000_events/EM_Opt1/Corryoutput/histograms.root";
    string data_Opt3_270um = "../alu_270um_10000_events/EM_Opt3/Corryoutput/histograms.root";
    string data_Opt4_270um = "../alu_270um_10000_events/EM_Opt4/Corryoutput/histograms.root";

    string data_Opt1_400um = "../alu_400um_1000_events/EM_Opt1/Corryoutput/histograms.root";
    string data_Opt3_400um = "../alu_400um_10000_events/EM_Opt3/Corryoutput/histograms.root";
    string data_Opt4_400um = "../alu_400um_10000_events/EM_Opt4/Corryoutput/histograms.root";

    string data_Opt1_600um = "../alu_600um_1000_events/EM_Opt1/Corryoutput/histograms.root";
    string data_Opt3_600um = "../alu_600um_10000_events/EM_Opt3/Corryoutput/histograms.root";
    string data_Opt4_600um = "../alu_600um_10000_events/EM_Opt4/Corryoutput/histograms.root";

    string data_Opt1_1000um = "../alu_1000um_1000_events/EM_Opt1/Corryoutput/histograms.root";
    string data_Opt3_1000um = "../alu_1000um_10000_events/EM_Opt3/Corryoutput/histograms.root";
    string data_Opt4_1000um = "../alu_1000um_10000_events/EM_Opt4/Corryoutput/histograms.root";

    string data_Opt1_1400um = "../alu_1400um_1000_events/EM_Opt1/Corryoutput/histograms.root";
    string data_Opt3_1400um = "../alu_1400um_10000_events/EM_Opt3/Corryoutput/histograms.root";
    string data_Opt4_1400um = "../alu_1400um_10000_events/EM_Opt4/Corryoutput/histograms.root";

    string data_Opt1_2000um = "../alu_2000um_1000_events/EM_Opt1/Corryoutput/histograms.root";
    string data_Opt3_2000um = "../alu_2000um_10000_events/EM_Opt3/Corryoutput/histograms.root";
    string data_Opt4_2000um = "../alu_2000um_10000_events/EM_Opt4/Corryoutput/histograms.root";

    string data_Opt1_3000um = "../alu_3000um_1000_events/EM_Opt1/Corryoutput/histograms.root";
    string data_Opt3_3000um = "../alu_3000um_10000_events/EM_Opt3/Corryoutput/histograms.root";
    string data_Opt4_3000um = "../alu_3000um_10000_events/EM_Opt4/Corryoutput/histograms.root";

    string data_Opt1_4000um = "../alu_4000um_1000_events/EM_Opt1/Corryoutput/histograms.root";
    string data_Opt3_4000um = "../alu_4000um_10000_events/EM_Opt3/Corryoutput/histograms.root";
    string data_Opt4_4000um = "../alu_4000um_10000_events/EM_Opt4/Corryoutput/histograms.root";

    string data_Opt1_6000um = "../alu_6000um_1000_events/EM_Opt1/Corryoutput/histograms.root";
    string data_Opt3_6000um = "../alu_6000um_10000_events/EM_Opt3/Corryoutput/histograms.root";
    string data_Opt4_6000um = "../alu_6000um_10000_events/EM_Opt4/Corryoutput/histograms.root";
    
    TFile *f3_0um = TFile::Open(data_Opt1_0um.c_str());
    TFile *f5_0um = TFile::Open(data_Opt3_0um.c_str());
    TFile *f6_0um = TFile::Open(data_Opt4_0um.c_str());

    TFile *f3_70um = TFile::Open(data_Opt1_70um.c_str());
    TFile *f5_70um = TFile::Open(data_Opt3_70um.c_str());
    TFile *f6_70um = TFile::Open(data_Opt4_70um.c_str());

    TFile *f3_200um = TFile::Open(data_Opt1_200um.c_str());
    TFile *f5_200um = TFile::Open(data_Opt3_200um.c_str());
    TFile *f6_200um = TFile::Open(data_Opt4_200um.c_str());

    TFile *f3_270um = TFile::Open(data_Opt1_270um.c_str());
    TFile *f5_270um = TFile::Open(data_Opt3_270um.c_str());
    TFile *f6_270um = TFile::Open(data_Opt4_270um.c_str());

    TFile *f3_400um = TFile::Open(data_Opt1_400um.c_str());
    TFile *f5_400um = TFile::Open(data_Opt3_400um.c_str());
    TFile *f6_400um = TFile::Open(data_Opt4_400um.c_str());

    TFile *f3_600um = TFile::Open(data_Opt1_600um.c_str());
    TFile *f5_600um = TFile::Open(data_Opt3_600um.c_str());
    TFile *f6_600um = TFile::Open(data_Opt4_600um.c_str());

    TFile *f3_1000um = TFile::Open(data_Opt1_1000um.c_str());
    TFile *f5_1000um = TFile::Open(data_Opt3_1000um.c_str());
    TFile *f6_1000um = TFile::Open(data_Opt4_1000um.c_str());

    TFile *f3_1400um = TFile::Open(data_Opt1_1400um.c_str());
    TFile *f5_1400um = TFile::Open(data_Opt3_1400um.c_str());
    TFile *f6_1400um = TFile::Open(data_Opt4_1400um.c_str());

    TFile *f3_2000um = TFile::Open(data_Opt1_2000um.c_str());
    TFile *f5_2000um = TFile::Open(data_Opt3_2000um.c_str());
    TFile *f6_2000um = TFile::Open(data_Opt4_2000um.c_str());

    TFile *f3_3000um = TFile::Open(data_Opt1_3000um.c_str());
    TFile *f5_3000um = TFile::Open(data_Opt3_3000um.c_str());
    TFile *f6_3000um = TFile::Open(data_Opt4_3000um.c_str());

    TFile *f3_4000um = TFile::Open(data_Opt1_4000um.c_str());
    TFile *f5_4000um = TFile::Open(data_Opt3_4000um.c_str());
    TFile *f6_4000um = TFile::Open(data_Opt4_4000um.c_str());

    TFile *f3_6000um = TFile::Open(data_Opt1_6000um.c_str());
    TFile *f5_6000um = TFile::Open(data_Opt3_6000um.c_str());
    TFile *f6_6000um = TFile::Open(data_Opt4_6000um.c_str());

    string WidthsX = "AnalysisElectronCT/timepix/widthsX";
    string WidthsY = "AnalysisElectronCT/timepix/widthsY";

    TH2D* hx3_0um = static_cast<TH2D*>(f3_0um->Get(WidthsX.c_str()));
    TH2D* hx5_0um = static_cast<TH2D*>(f5_0um->Get(WidthsX.c_str()));
    TH2D* hx6_0um = static_cast<TH2D*>(f6_0um->Get(WidthsX.c_str()));

    TH2D* hx3_70um = static_cast<TH2D*>(f3_70um->Get(WidthsX.c_str()));
    TH2D* hx5_70um = static_cast<TH2D*>(f5_70um->Get(WidthsX.c_str()));
    TH2D* hx6_70um = static_cast<TH2D*>(f6_70um->Get(WidthsX.c_str()));

    TH2D* hx3_200um = static_cast<TH2D*>(f3_200um->Get(WidthsX.c_str()));
    TH2D* hx5_200um = static_cast<TH2D*>(f5_200um->Get(WidthsX.c_str()));
    TH2D* hx6_200um = static_cast<TH2D*>(f6_200um->Get(WidthsX.c_str()));

    TH2D* hx3_270um = static_cast<TH2D*>(f3_270um->Get(WidthsX.c_str()));
    TH2D* hx5_270um = static_cast<TH2D*>(f5_270um->Get(WidthsX.c_str()));
    TH2D* hx6_270um = static_cast<TH2D*>(f6_270um->Get(WidthsX.c_str()));

    TH2D* hx3_400um = static_cast<TH2D*>(f3_400um->Get(WidthsX.c_str()));
    TH2D* hx5_400um = static_cast<TH2D*>(f5_400um->Get(WidthsX.c_str()));
    TH2D* hx6_400um = static_cast<TH2D*>(f6_400um->Get(WidthsX.c_str()));

    TH2D* hx3_600um = static_cast<TH2D*>(f3_600um->Get(WidthsX.c_str()));
    TH2D* hx5_600um = static_cast<TH2D*>(f5_600um->Get(WidthsX.c_str()));
    TH2D* hx6_600um = static_cast<TH2D*>(f6_600um->Get(WidthsX.c_str()));

    TH2D* hx3_1000um = static_cast<TH2D*>(f3_1000um->Get(WidthsX.c_str()));
    TH2D* hx5_1000um = static_cast<TH2D*>(f5_1000um->Get(WidthsX.c_str()));
    TH2D* hx6_1000um = static_cast<TH2D*>(f6_1000um->Get(WidthsX.c_str()));

    TH2D* hx3_1400um = static_cast<TH2D*>(f3_1400um->Get(WidthsX.c_str()));
    TH2D* hx5_1400um = static_cast<TH2D*>(f5_1400um->Get(WidthsX.c_str()));
    TH2D* hx6_1400um = static_cast<TH2D*>(f6_1400um->Get(WidthsX.c_str()));

    TH2D* hx3_2000um = static_cast<TH2D*>(f3_2000um->Get(WidthsX.c_str()));
    TH2D* hx5_2000um = static_cast<TH2D*>(f5_2000um->Get(WidthsX.c_str()));
    TH2D* hx6_2000um = static_cast<TH2D*>(f6_2000um->Get(WidthsX.c_str()));

    TH2D* hx3_3000um = static_cast<TH2D*>(f3_3000um->Get(WidthsX.c_str()));
    TH2D* hx5_3000um = static_cast<TH2D*>(f5_3000um->Get(WidthsX.c_str()));
    TH2D* hx6_3000um = static_cast<TH2D*>(f6_3000um->Get(WidthsX.c_str()));

    TH2D* hx3_4000um = static_cast<TH2D*>(f3_4000um->Get(WidthsX.c_str()));
    TH2D* hx5_4000um = static_cast<TH2D*>(f5_4000um->Get(WidthsX.c_str()));
    TH2D* hx6_4000um = static_cast<TH2D*>(f6_4000um->Get(WidthsX.c_str()));

    TH2D* hx3_6000um = static_cast<TH2D*>(f3_6000um->Get(WidthsX.c_str()));
    TH2D* hx5_6000um = static_cast<TH2D*>(f5_6000um->Get(WidthsX.c_str()));
    TH2D* hx6_6000um = static_cast<TH2D*>(f6_6000um->Get(WidthsX.c_str()));

    double mean3_0um = hx3_0um->GetMean();
    double mean3_error_0um = hx3_0um->GetMeanError();
    double mean5_0um = hx5_0um->GetMean();
    double mean5_error_0um = hx5_0um->GetMeanError();
    double mean6_0um = hx6_0um->GetMean();
    double mean6_error_0um = hx6_0um->GetMeanError();

    double mean3_70um = hx3_70um->GetMean();
    double mean3_error_70um = hx3_70um->GetMeanError();
    double mean5_70um = hx5_70um->GetMean();
    double mean5_error_70um = hx5_70um->GetMeanError();
    double mean6_70um = hx6_70um->GetMean();
    double mean6_error_70um = hx6_70um->GetMeanError();

    double mean3_200um = hx3_200um->GetMean();
    double mean3_error_200um = hx3_200um->GetMeanError();
    double mean5_200um = hx5_200um->GetMean();
    double mean5_error_200um = hx5_200um->GetMeanError();
    double mean6_200um = hx6_200um->GetMean();
    double mean6_error_200um = hx6_200um->GetMeanError();

    double mean3_270um = hx3_270um->GetMean();
    double mean3_error_270um = hx3_270um->GetMeanError();
    double mean5_270um = hx5_270um->GetMean();
    double mean5_error_270um = hx5_270um->GetMeanError();
    double mean6_270um = hx6_270um->GetMean();
    double mean6_error_270um = hx6_270um->GetMeanError();

    double mean3_400um = hx3_400um->GetMean();
    double mean3_error_400um = hx3_400um->GetMeanError();
    double mean5_400um = hx5_400um->GetMean();
    double mean5_error_400um = hx5_400um->GetMeanError();
    double mean6_400um = hx6_400um->GetMean();
    double mean6_error_400um = hx6_400um->GetMeanError();

    double mean3_600um = hx3_600um->GetMean();
    double mean3_error_600um = hx3_600um->GetMeanError();
    double mean5_600um = hx5_600um->GetMean();
    double mean5_error_600um = hx5_600um->GetMeanError();
    double mean6_600um = hx6_600um->GetMean();
    double mean6_error_600um = hx6_600um->GetMeanError();

    double mean3_1000um = hx3_1000um->GetMean();
    double mean3_error_1000um = hx3_1000um->GetMeanError();
    double mean5_1000um = hx5_1000um->GetMean();
    double mean5_error_1000um = hx5_1000um->GetMeanError();
    double mean6_1000um = hx6_1000um->GetMean();
    double mean6_error_1000um = hx6_1000um->GetMeanError();

    double mean3_1400um = hx3_1400um->GetMean();
    double mean3_error_1400um = hx3_1400um->GetMeanError();
    double mean5_1400um = hx5_1400um->GetMean();
    double mean5_error_1400um = hx5_1400um->GetMeanError();
    double mean6_1400um = hx6_1400um->GetMean();
    double mean6_error_1400um = hx6_1400um->GetMeanError();

    double mean3_2000um = hx3_2000um->GetMean();
    double mean3_error_2000um = hx3_2000um->GetMeanError();
    double mean5_2000um = hx5_2000um->GetMean();
    double mean5_error_2000um = hx5_2000um->GetMeanError();
    double mean6_2000um = hx6_2000um->GetMean();
    double mean6_error_2000um = hx6_2000um->GetMeanError();

    double mean3_3000um = hx3_3000um->GetMean();
    double mean3_error_3000um = hx3_3000um->GetMeanError();
    double mean5_3000um = hx5_3000um->GetMean();
    double mean5_error_3000um = hx5_3000um->GetMeanError();
    double mean6_3000um = hx6_3000um->GetMean();
    double mean6_error_3000um = hx6_3000um->GetMeanError();

    double mean3_4000um = hx3_4000um->GetMean();
    double mean3_error_4000um = hx3_4000um->GetMeanError();
    double mean5_4000um = hx5_4000um->GetMean();
    double mean5_error_4000um = hx5_4000um->GetMeanError();
    double mean6_4000um = hx6_4000um->GetMean();
    double mean6_error_4000um = hx6_4000um->GetMeanError();

    double mean3_6000um = hx3_6000um->GetMean();
    double mean3_error_6000um = hx3_6000um->GetMeanError();
    double mean5_6000um = hx5_6000um->GetMean();
    double mean5_error_6000um = hx5_6000um->GetMeanError();
    double mean6_6000um = hx6_6000um->GetMean();
    double mean6_error_6000um = hx6_6000um->GetMeanError();

    const int n_points=12;
    double x_vals[n_points]={0,70,200,270,400,600,1000,1400,2000,3000,4000,6000};
    //double x_vals[n_points]={70,70,70,70,70,70,70,70,70};
    double EM_Opt1_y_vals[n_points]={mean3_0um,mean3_70um,mean3_200um,mean3_270um,mean3_400um,mean3_600um,mean3_1000um,mean3_1400um,mean3_2000um,mean3_3000um,mean3_4000um,mean3_6000um};
    double EM_Opt1_y_errors[n_points]={mean3_error_0um,mean3_error_70um,mean3_error_200um,mean3_error_270um,mean3_error_400um,mean3_error_600um,mean3_error_1000um,mean3_error_1400um,mean3_error_2000um,mean3_error_3000um,mean3_error_4000um,mean3_error_6000um};
    double EM_Opt3_y_vals[n_points]={mean5_0um,mean5_70um,mean5_200um,mean5_270um,mean5_400um,mean5_600um,mean5_1000um,mean5_1400um,mean5_2000um,mean5_3000um,mean5_4000um,mean5_6000um};
    double EM_Opt3_y_errors[n_points]={mean5_error_0um,mean5_error_70um,mean5_error_200um,mean5_error_270um,mean5_error_400um,mean5_error_600um,mean5_error_1000um,mean5_error_1400um,mean5_error_2000um,mean5_error_3000um,mean5_error_4000um,mean5_error_6000um};
    double EM_Opt4_y_vals[n_points]={mean6_0um,mean6_70um,mean6_200um,mean6_270um,mean6_400um,mean6_600um,mean6_1000um,mean6_1400um,mean6_2000um,mean6_3000um,mean6_4000um,mean6_6000um};
    double EM_Opt4_y_errors[n_points]={mean6_error_0um,mean6_error_70um,mean6_error_200um,mean6_error_270um,mean6_error_400um,mean6_error_600um,mean6_error_1000um,mean6_error_1400um,mean6_error_2000um,mean6_error_3000um,mean6_error_4000um,mean6_error_6000um};
    
    //double EM_Opt1_y_vals[n_points]={mean3_70um,mean3_200um,mean3_270um,mean3_400um,mean3_600um,mean3_1000um,mean3_1400um,mean3_2000um,mean3_3000um,mean3_4000um};
    //double EM_Opt1_y_errors[n_points]={mean3_error_70um,mean3_error_200um,mean3_error_270um,mean3_error_400um,mean3_error_600um,mean3_error_1000um,mean3_error_1400um,mean3_error_2000um,mean3_error_3000um,mean3_error_4000um};
    //double EM_Opt3_y_vals[n_points]={mean5_70um,mean5_200um,mean5_270um,mean5_400um,mean5_600um,mean5_1000um,mean5_1400um,mean5_2000um,mean5_3000um,mean5_4000um,mean5_6000um};
    //double EM_Opt3_y_errors[n_points]={mean5_error_70um,mean5_error_200um,mean5_error_270um,mean5_error_400um,mean5_error_600um,mean5_error_1000um,mean5_error_1400um,mean5_error_2000um,mean5_error_3000um,mean5_error_4000um,mean5_error_6000um};
    //double EM_Opt4_y_vals[n_points]={mean6_70um,mean6_200um,mean6_270um,mean6_400um,mean6_600um,mean6_1000um,mean6_1400um,mean6_2000um,mean6_3000um,mean6_4000um,mean6_6000um};
    //double EM_Opt4_y_errors[n_points]={mean6_error_70um,mean6_error_200um,mean6_error_270um,mean6_error_400um,mean6_error_600um,mean6_error_1000um,mean6_error_1400um,mean6_error_2000um,mean6_error_3000um,mean6_error_4000um,mean6_error_6000um};


    // Instance of the graph
    TGraphErrors EM_Opt1(n_points,x_vals,EM_Opt1_y_vals,nullptr,EM_Opt1_y_errors);
    TGraphErrors EM_Opt3(n_points,x_vals,EM_Opt3_y_vals,nullptr,EM_Opt3_y_errors);
    TGraphErrors EM_Opt4(n_points,x_vals,EM_Opt4_y_vals,nullptr,EM_Opt4_y_errors);
    EM_Opt4.SetTitle("Mean Widths different Modules;aluminum thickness [um];mean width [pixels]");

    //TF1 *f1 = new TF1("f1","([0]+[1]*pow((pow(x,2)-[2]), 0.5))*([3]+[4]*pow(x,2))");
    //TF1 *f1 = new TF1("f1","([0]+[1]*x+[2]*pow(x,2))");
    //f1->SetParameters(-0.6,0.07,120,0.06,0.00001);
    //f1->SetLineColor(1);
    //EM_Opt3.Fit("f1");

    // Make the plot aesthetically better
    EM_Opt1.SetMarkerStyle(104);
    EM_Opt1.SetMarkerSize(1);
    EM_Opt1.SetMarkerColor(2);
    EM_Opt1.SetLineColor(2);
    EM_Opt1.SetFillColorAlpha(9, 0.571);
    EM_Opt3.SetMarkerStyle(105);
    EM_Opt3.SetMarkerSize(1);
    EM_Opt3.SetMarkerColor(4);
    EM_Opt3.SetLineColor(4);
    EM_Opt3.SetFillColorAlpha(9, 0.571);
    EM_Opt4.SetMarkerStyle(106);
    EM_Opt4.SetMarkerSize(1);
    EM_Opt4.SetMarkerColor(7);
    EM_Opt4.SetLineColor(7);
    EM_Opt4.SetFillColorAlpha(9, 0.571);

    EM_Opt1.GetXaxis()->SetRangeUser(0,6000);
    //EM_Opt3.GetXaxis()->SetRangeUser(5,30);
    //EM_Opt4.GetXaxis()->SetRangeUser(5,30);

    TCanvas* c1 = new TCanvas("c1","c1",1920,1080);

    EM_Opt1.SetTitle("Aluminium diff. thicknesses model comparison");
    EM_Opt1.GetXaxis()->SetTitle("Alu thickness [#mum]");
    EM_Opt1.GetYaxis()->SetTitle("Mean beam width [px]");

    // Draw the graph !
    EM_Opt1.DrawClone("ACPSLE");
    EM_Opt3.DrawClone("same");
    EM_Opt4.DrawClone("same");
    //f1->DrawClone("same");

    gStyle->SetOptStat("ne");
    //gStyle->SetOptStat(0);
    //gStyle->SetOptFit(1111);
    
    TLegend leg(.1,.7,.3,.9,"MSC simulation model");
    leg.SetFillColor(0);
    EM_Opt1.SetFillColor(0);
    EM_Opt3.SetFillColor(0);
    EM_Opt4.SetFillColor(0);

    c1->SetGridx();
    c1->SetGridy();
    // c1->SetLogy();
    // c1->SetLogx();
    leg.AddEntry(&EM_Opt1,"Wentzel VI");
    leg.AddEntry(&EM_Opt3,"Urban MSC");
    leg.AddEntry(&EM_Opt4,"Goudsmit Saunderson");
    //leg.AddEntry(f1,"fit-function: $\\epsilon = (p_0+p_1#sqrt{(\\theta_{dev}^2-p_2)})(p_3+p_4 \\theta_{dev}^2)$");
    //leg.AddEntry(f1,"fit-function: $\\epsilon = (p_0+p_1#sqrt{(x-p_2)})(p_3+p_4 x)$");
    leg.DrawClone();

    // Draw an arrow on the canvas
    // TArrow arrow(8,8,6.2,23,0.02,"|>");
    // arrow.SetLineWidth(2);
    // arrow.DrawClone();

    // Add some text to the plot
    // TLatex text(8.2,7.5,"#splitline{Maximum}{Deviation}");
    // text.DrawClone();

    //Adjust margin so z-axis label is not cut off:;
    //gPad->SetLeftMargin(0.13);

    c1->SaveAs("PDFs/mean_widths_10000_events_all_alu.png");
    c1->Print("all_alu_data.txt");
    //EM_Opt1.Print("example.txt");
    //EM_Opt3.Print("example.txt");
    EM_Opt4.Print("example.txt");
}
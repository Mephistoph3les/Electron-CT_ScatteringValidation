#include <string>
void widths_macro() {
    string events = "10000";
    string material = "aluminum";

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


    TCanvas* c1 = new TCanvas("c1","c1",1920,1080);

    // Split canvas into 2x1;
    c1->SetGridx();
    c1->SetGridy();
    c1->Divide(6,2);
    
    //Rename the histogram and the axis labels:;
    hx3_0um->SetTitle("Aluminium 0um WidthX");
    hx3_0um->GetXaxis()->SetTitle("Width X [px]");
    hx3_0um->GetYaxis()->SetTitle("# frames");
    hx3_0um->GetXaxis()->SetRangeUser(0,20);
    hx3_0um->GetYaxis()->SetRangeUser(0,600);
    hx3_0um->SetLineColor(3);
    hx5_0um->SetLineColor(5);
    hx6_0um->SetLineColor(6);

    hx3_70um->SetTitle("Aluminium 70um WidthX");
    hx3_70um->GetXaxis()->SetTitle("Width X [px]");
    hx3_70um->GetYaxis()->SetTitle("# frames");
    hx3_70um->GetXaxis()->SetRangeUser(0,20);
    hx3_70um->GetYaxis()->SetRangeUser(0,600);
    hx3_70um->SetLineColor(3);
    hx5_70um->SetLineColor(5);
    hx6_70um->SetLineColor(6);

    hx3_200um->SetTitle("Aluminium 200um WidthX");
    hx3_200um->GetXaxis()->SetTitle("Width X [px]");
    hx3_200um->GetYaxis()->SetTitle("# frames");
    hx3_200um->GetXaxis()->SetRangeUser(0,20);
    hx3_200um->GetYaxis()->SetRangeUser(0,600);
    hx3_200um->SetLineColor(3);
    hx5_200um->SetLineColor(5);
    hx6_200um->SetLineColor(6);

    hx3_270um->SetTitle("Aluminium 270um WidthX");
    hx3_270um->GetXaxis()->SetTitle("Width X [px]");
    hx3_270um->GetYaxis()->SetTitle("# frames");
    hx3_270um->GetXaxis()->SetRangeUser(0,20);
    hx3_270um->GetYaxis()->SetRangeUser(0,600);
    hx3_270um->SetLineColor(3);
    hx5_270um->SetLineColor(5);
    hx6_270um->SetLineColor(6);

    hx3_400um->SetTitle("Aluminium 400um WidthX");
    hx3_400um->GetXaxis()->SetTitle("Width X [px]");
    hx3_400um->GetYaxis()->SetTitle("# frames");
    hx3_400um->GetXaxis()->SetRangeUser(0,20);
    hx3_400um->GetYaxis()->SetRangeUser(0,600);
    hx3_400um->SetLineColor(3);
    hx5_400um->SetLineColor(5);
    hx6_400um->SetLineColor(6);

    hx3_600um->SetTitle("Aluminium 600um WidthX");
    hx3_600um->GetXaxis()->SetTitle("Width X [px]");
    hx3_600um->GetYaxis()->SetTitle("# frames");
    hx3_600um->GetXaxis()->SetRangeUser(0,20);
    hx3_600um->GetYaxis()->SetRangeUser(0,600);
    hx3_600um->SetLineColor(3);
    hx5_600um->SetLineColor(5);
    hx6_600um->SetLineColor(6);

    hx3_1000um->SetTitle("Aluminium 1000um WidthX");
    hx3_1000um->GetXaxis()->SetTitle("Width X [px]");
    hx3_1000um->GetYaxis()->SetTitle("# frames");
    hx3_1000um->GetXaxis()->SetRangeUser(0,20);
    hx3_1000um->GetYaxis()->SetRangeUser(0,600);
    hx3_1000um->SetLineColor(3);
    hx5_1000um->SetLineColor(5);
    hx6_1000um->SetLineColor(6);

    hx3_1400um->SetTitle("Aluminium 1400um WidthX");
    hx3_1400um->GetXaxis()->SetTitle("Width X [px]");
    hx3_1400um->GetYaxis()->SetTitle("# frames");
    hx3_1400um->GetXaxis()->SetRangeUser(0,20);
    hx3_1400um->GetYaxis()->SetRangeUser(0,600);
    hx3_1400um->SetLineColor(3);
    hx5_1400um->SetLineColor(5);
    hx6_1400um->SetLineColor(6);

    hx3_2000um->SetTitle("Aluminium 2000um WidthX");
    hx3_2000um->GetXaxis()->SetTitle("Width X [px]");
    hx3_2000um->GetYaxis()->SetTitle("# frames");
    hx3_2000um->GetXaxis()->SetRangeUser(0,20);
    hx3_2000um->GetYaxis()->SetRangeUser(0,600);
    hx3_2000um->SetLineColor(3);
    hx5_2000um->SetLineColor(5);
    hx6_2000um->SetLineColor(6);

    hx3_3000um->SetTitle("Aluminium 3000um WidthX");
    hx3_3000um->GetXaxis()->SetTitle("Width X [px]");
    hx3_3000um->GetYaxis()->SetTitle("# frames");
    hx3_3000um->GetXaxis()->SetRangeUser(0,20);
    hx3_3000um->GetYaxis()->SetRangeUser(0,600);
    hx3_3000um->SetLineColor(3);
    hx5_3000um->SetLineColor(5);
    hx6_3000um->SetLineColor(6);
    
    hx3_4000um->SetTitle("Aluminum 4000um WidthX");
    hx3_4000um->GetXaxis()->SetTitle("Width X [px]");
    hx3_4000um->GetYaxis()->SetTitle("# frames");
    hx3_4000um->GetXaxis()->SetRangeUser(0,20);
    hx3_4000um->GetYaxis()->SetRangeUser(0,600);
    hx3_4000um->SetLineColor(3);
    hx5_4000um->SetLineColor(5);
    hx6_4000um->SetLineColor(6);

    hx3_6000um->SetTitle("Aluminum 6000um WidthX");
    hx3_6000um->GetXaxis()->SetTitle("Width X [px]");
    hx3_6000um->GetYaxis()->SetTitle("# frames");
    hx3_6000um->GetXaxis()->SetRangeUser(0,20);
    hx3_6000um->GetYaxis()->SetRangeUser(0,600);
    hx3_6000um->SetLineColor(3);
    hx5_6000um->SetLineColor(5);
    hx6_6000um->SetLineColor(6);

    //Access first section on canvas:;
    c1->cd(1);
    TLegend *leg1 = new TLegend(0.6,0.7,0.9,0.9);
    hx3_0um->Draw("colz");
    hx5_0um->Draw("same");
    hx6_0um->Draw("same");
    gStyle->SetOptStat(0);
    // hx1_0um->GetXaxis()->SetRangeUser(0,10);
    hx3_0um->GetYaxis()->SetRangeUser(0,600);
    leg1->AddEntry(hx3_0um,"Wentzel VI");
    leg1->AddEntry(hx5_0um,"Urban MSC");
    leg1->AddEntry(hx6_0um,"Goudsmit Saunderson");
    leg1->SetTextSize(0.05);
    leg1->Draw();

    //Access second section on canvas:;
    c1->cd(2);
    TLegend *leg2 = new TLegend(0.6,0.7,0.9,0.9);
    hx3_70um->Draw("colz");
    hx5_70um->Draw("same");
    hx6_70um->Draw("same");
    gStyle->SetOptStat(0);
    leg2->AddEntry(hx3_70um,"Wentzel VI");
    leg2->AddEntry(hx5_70um,"Urban MSC");
    leg2->AddEntry(hx6_70um,"Goudsmit Saunderson");
    leg2->Draw();

    //Access third section on canvas:;
    c1->cd(3);
    TLegend *leg3 = new TLegend(0.6,0.7,0.9,0.9);
    hx3_200um->Draw("colz");
    hx5_200um->Draw("same");
    hx6_200um->Draw("same");
    gStyle->SetOptStat(0);
    leg3->AddEntry(hx3_200um,"Wentzel VI");
    leg3->AddEntry(hx5_200um,"Urban MSC");
    leg3->AddEntry(hx6_200um,"Goudsmit Saunderson");
    leg3->Draw();

    //Access fourth section on canvas:;
    c1->cd(4);
    TLegend *leg4 = new TLegend(0.6,0.7,0.9,0.9);
    hx3_270um->Draw("colz");
    hx5_270um->Draw("same");
    hx6_270um->Draw("same");
    gStyle->SetOptStat(0);
    leg4->AddEntry(hx3_270um,"Wentzel VI");
    leg4->AddEntry(hx5_270um,"Urban MSC");
    leg4->AddEntry(hx6_270um,"Goudsmit Saunderson");
    leg4->Draw();

    //Access fifth section on canvas:;
    c1->cd(5);
    TLegend *leg5 = new TLegend(0.6,0.7,0.9,0.9);
    hx3_400um->Draw("colz");
    hx5_400um->Draw("same");
    hx6_400um->Draw("same");
    gStyle->SetOptStat(0);
    leg5->AddEntry(hx3_400um,"Wentzel VI");
    leg5->AddEntry(hx5_400um,"Urban MSC");
    leg5->AddEntry(hx6_400um,"Goudsmit Saunderson");
    leg5->Draw();

    //Access sixth section on canvas:;
    c1->cd(6);
    TLegend *leg6 = new TLegend(0.6,0.7,0.9,0.9);
    hx3_600um->Draw("colz");
    hx5_600um->Draw("same");
    hx6_600um->Draw("same");
    gStyle->SetOptStat(0);
    leg6->AddEntry(hx3_600um,"Wentzel VI");
    leg6->AddEntry(hx5_600um,"Urban MSC");
    leg6->AddEntry(hx6_600um,"Goudsmit Saunderson");
    leg6->Draw();

    //Access seventh section on canvas:;
    c1->cd(7);
    TLegend *leg7 = new TLegend(0.6,0.7,0.9,0.9);
    hx3_1000um->Draw("colz");
    hx5_1000um->Draw("same");
    hx6_1000um->Draw("same");
    gStyle->SetOptStat(0);
    leg7->AddEntry(hx3_1000um,"Wentzel VI");
    leg7->AddEntry(hx5_1000um,"Urban MSC");
    leg7->AddEntry(hx6_1000um,"Goudsmit Saunderson");
    leg7->Draw();

    //Access eighth section on canvas:;
    c1->cd(8);
    TLegend *leg8 = new TLegend(0.6,0.7,0.9,0.9);
    hx3_1400um->Draw("colz");
    hx5_1400um->Draw("same");
    hx6_1400um->Draw("same");
    gStyle->SetOptStat(0);
    leg8->AddEntry(hx3_1400um,"Wentzel VI");
    leg8->AddEntry(hx5_1400um,"Urban MSC");
    leg8->AddEntry(hx6_1400um,"Goudsmit Saunderson");
    leg8->Draw();

    c1->cd(9);
    TLegend *leg9 = new TLegend(0.6,0.7,0.9,0.9);
    hx3_2000um->Draw("colz");
    hx5_2000um->Draw("same");
    hx6_2000um->Draw("same");
    gStyle->SetOptStat(0);
    leg9->AddEntry(hx3_2000um,"Wentzel VI");
    leg9->AddEntry(hx5_2000um,"Urban MSC");
    leg9->AddEntry(hx6_2000um,"Goudsmit Saunderson");
    leg9->Draw();

    c1->cd(10);
    TLegend *leg10 = new TLegend(0.6,0.7,0.9,0.9);
    hx3_3000um->Draw("colz");
    hx5_3000um->Draw("same");
    hx6_3000um->Draw("same");
    gStyle->SetOptStat(0);
    leg10->AddEntry(hx3_3000um,"Wentzel VI");
    leg10->AddEntry(hx5_3000um,"Urban MSC");
    leg10->AddEntry(hx6_3000um,"Goudsmit Saunderson");
    leg10->Draw();

    c1->cd(11);
    TLegend *leg11 = new TLegend(0.6,0.7,0.9,0.9);
    hx3_4000um->Draw("colz");
    hx5_4000um->Draw("same");
    hx6_4000um->Draw("same");
    gStyle->SetOptStat(0);
    leg11->AddEntry(hx3_4000um,"Wentzel VI");
    leg11->AddEntry(hx5_4000um,"Urban MSC");
    leg11->AddEntry(hx6_4000um,"Goudsmit Saunderson");
    leg11->SetTextSize(0.12);
    leg11->Draw();

    c1->cd(12);
    TLegend *leg12 = new TLegend(0.6,0.7,0.9,0.9);
    hx3_6000um->Draw("colz");
    hx5_6000um->Draw("same");
    hx6_6000um->Draw("same");
    gStyle->SetOptStat(0);
    leg12->AddEntry(hx3_6000um,"Wentzel VI");
    leg12->AddEntry(hx5_6000um,"Urban MSC");
    leg12->AddEntry(hx6_6000um,"Goudsmit Saunderson");
    leg12->Draw();

    //Adjust margin so z-axis label is not cut off:;
    // gPad->SetLeftMargin(0.13);

    c1->SaveAs("PDFs/Gauss_Widths_{events}_events_{thick}_{material}.png");

}
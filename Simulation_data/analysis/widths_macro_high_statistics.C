#include <string>
void widths_macro_high_statistics() {
    string events = "100000";
    string material = "aluminum";
    string thick = "1000um";

    string data_Opt0_1000um = "../alu_1000um_100000_events/EM_Opt0/Corryoutput/histograms.root";
    string data_Opt4_1000um = "../alu_1000um_100000_events/EM_Opt4/Corryoutput/histograms.root";

    TFile *f2_1000um = TFile::Open(data_Opt0_1000um.c_str());
    TFile *f6_1000um = TFile::Open(data_Opt4_1000um.c_str());

    string WidthsX = "AnalysisElectronCT/timepix/widthsX";
    string WidthsY = "AnalysisElectronCT/timepix/widthsY";

    TH2D* hx2_1000um = static_cast<TH2D*>(f2_1000um->Get(WidthsX.c_str()));
    TH2D* hx6_1000um = static_cast<TH2D*>(f6_1000um->Get(WidthsX.c_str()));

    TH2D* hy2_1000um = static_cast<TH2D*>(f2_1000um->Get(WidthsY.c_str()));
    TH2D* hy6_1000um = static_cast<TH2D*>(f6_1000um->Get(WidthsY.c_str()));


    double mean2_1000um = hx2_1000um->GetMean();
    double mean2_error_1000um = hx2_1000um->GetMeanError();
    double mean6_1000um = hx6_1000um->GetMean();
    double mean6_error_1000um = hx6_1000um->GetMeanError();


    TCanvas* c1 = new TCanvas("c1","c1",3840,2160);

    // Split canvas into 2x1;
    c1->SetGridx();
    c1->SetGridy();
   
   

    hx2_1000um->SetTitle("aluminum 1000um WidthsX 100000 events");
    hx2_1000um->GetXaxis()->SetTitle("Width X [px]");
    hx2_1000um->GetYaxis()->SetTitle("# frames");
    hx2_1000um->GetXaxis()->SetRangeUser(10,15);
    //hx2_1000um->GetYaxis()->SetRangeUser(0,600);
    hx2_1000um->SetLineColor(2);
    hx6_1000um->SetLineColor(4);

    //Access seventh section on canvas:;
    c1->cd(1);
    TLegend *leg7 = new TLegend(0.6,0.7,0.9,0.9);
    hx2_1000um->Draw("colz");
    hx6_1000um->Draw("same");
    gStyle->SetOptStat(0);
    leg7->AddEntry(hx2_1000um,"Urban Msc WidthX");
    leg7->AddEntry(hx6_1000um,"Gaudsmit Saunderson WidthX");
    leg7->Draw();

 
    //Adjust margin so z-axis label is not cut off:;
    // gPad->SetLeftMargin(0.13);

    c1->SaveAs("PDFs/Gauss_Widths_100000_events_1000um_alu_increased_binning.png");

}

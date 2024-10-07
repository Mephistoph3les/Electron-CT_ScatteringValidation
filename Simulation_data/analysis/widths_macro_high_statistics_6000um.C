#include <string>

void widths_macro_high_statistics_6000um() {
    string events = "100000";
    string material = "aluminum";
    string thick = "6000um";

    string data_Opt1_6000um = "../alu_6000um_100000_events/EM_Opt1/Corryoutput/histograms.root";
    string data_Opt3_6000um = "../alu_6000um_100000_events/EM_Opt3/Corryoutput/histograms.root";
    string data_Opt4_6000um = "../alu_6000um_100000_events/EM_Opt4/Corryoutput/histograms.root";

    TFile *f2_6000um = TFile::Open(data_Opt1_6000um.c_str());
    TFile *f3_6000um = TFile::Open(data_Opt3_6000um.c_str());
    TFile *f6_6000um = TFile::Open(data_Opt4_6000um.c_str());

    string WidthsX = "AnalysisElectronCT/timepix/widthsX";
    string WidthsY = "AnalysisElectronCT/timepix/widthsY";

    TH1D* hx2_6000um = static_cast<TH1D*>(f2_6000um->Get(WidthsX.c_str()));
    TH1D* hx3_6000um = static_cast<TH1D*>(f3_6000um->Get(WidthsX.c_str()));
    TH1D* hx6_6000um = static_cast<TH1D*>(f6_6000um->Get(WidthsX.c_str()));

    TCanvas* c1 = new TCanvas("c1","Aluminum 6000um Simulation WidthsX 100000 events",1920,1080);

    c1->SetGridx();
    c1->SetGridy();
    
    hx2_6000um->SetTitle("aluminum 6000um WidthsX 100000 events");
    hx2_6000um->GetXaxis()->SetTitle("Width X [px]");
    hx2_6000um->GetYaxis()->SetTitle("# frames");
    hx2_6000um->GetXaxis()->SetRangeUser(24,35);
    hx3_6000um->GetXaxis()->SetRangeUser(24,35);
    hx6_6000um->GetXaxis()->SetRangeUser(24,35);
    TF1 *f1 = new TF1("f1","gaus",24,35);
    TF1 *f2 = new TF1("f2","gaus",24,35);
    TF1 *f3 = new TF1("f3","gaus",24,35);
    f1->SetParameters(29.2, 1);
    f2->SetParameters(29.2, 1);
    f3->SetParameters(29.2, 1);
    f1->SetLineColor(1);
    f2->SetLineColor(2);
    f3->SetLineColor(3);
    hx2_6000um->SetLineColor(2);
    hx3_6000um->SetLineColor(6);
    hx6_6000um->SetLineColor(4);

    c1->cd(1);
    TLegend *leg1 = new TLegend(0.1,0.7,0.35,0.9);
    hx2_6000um->SetTitle("aluminum 6000um Model data comparison");
    hx2_6000um->Draw("colz");
    hx3_6000um->Draw("same");
    hx6_6000um->Draw("same");
    gStyle->SetOptStat(0000);
    gStyle->SetOptFit(0000);
    leg1->AddEntry(hx2_6000um,"Wentzel VI");
    leg1->AddEntry(hx3_6000um,"Urban Msc");
    leg1->AddEntry(hx6_6000um,"Goudsmit Saunderson");
    leg1->SetTextSize(0.02);
    leg1->Draw();

    c1->SaveAs("PDFs/Gauss_Widths_100000_events_6000um_alu_increased_binning_test.png");
}

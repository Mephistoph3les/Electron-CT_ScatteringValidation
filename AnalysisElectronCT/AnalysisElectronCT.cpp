/**
 * @file
 * @brief Implementation of module AnalysisElectronCT
 *
 * @copyright Copyright (c) 2020 CERN and the Corryvreckan authors.
 * This software is distributed under the terms of the MIT License, copied verbatim in the file "LICENSE.md".
 * In applying this license, CERN does not waive the privileges and immunities granted to it by virtue of its status as an
 * Intergovernmental Organization or submit itself to any jurisdiction.
 */

#include "AnalysisElectronCT.h"
#include "TF1.h"

using namespace corryvreckan;

AnalysisElectronCT::AnalysisElectronCT(Configuration& config, std::shared_ptr<Detector> detector)
    : Module(config, detector), m_detector(detector) {

    ignore_first_frame_ = config_.get<bool>("ignore_first_frame", false);
    compute_xray_ = config_.get<bool>("compute_xray", false);
    store_data_ = config_.get<bool>("store_data", false);
}

void AnalysisElectronCT::initialize() {

    for(auto& detector : get_detectors()) {
        LOG(DEBUG) << "Initialise for detector " + detector->getName();
    }

    // Initialise member variables
    m_eventNumber = 0;

    int xpixels = m_detector->nPixels().X();
    int ypixels = m_detector->nPixels().Y();

    int plot_frames = config_.get<int>("plot_frames", 1000);
    charge_weighting_ = config_.get<bool>("charge_weighting", true);
    fitted_profile_ = config_.get<bool>("fitted_profile", true);
    compute_xray_ = config_.get<bool>("compute_xray");
    store_data_ = config_.get<bool>("store_data");

    if(compute_xray_) {
        x_frames_ = config_.get<int>("xray_x_frames", 300);
        chop_frames_ = config_.get<int>("xray_chop_frames", 0);
    }else{
        chop_frames_ = 0;
    }

    std::string title = "Integrated hit map;x [px]; y [px];hits";
    hitMapIntegrated =
        new TH2F("hitMapIntegrated", title.c_str(), xpixels, -0.5, xpixels - 0.5, ypixels, -0.5, ypixels - 0.5);
    title = "Hit map of last frame;x [px]; y [px];hits";
    hitMapLastFrame = new TH2F("hitMapLastFrame", title.c_str(), xpixels, -0.5, xpixels - 0.5, ypixels, -0.5, ypixels - 0.5);

    title = "Integrated charge map;x [px]; y [px];charge [ke]";
    chargeMapIntegrated =
        new TH2F("chargeMapIntegrated", title.c_str(), xpixels, -0.5, xpixels - 0.5, ypixels, -0.5, ypixels - 0.5);
    title = "Charge map of last frame;x [px]; y [px];charge [ke]";
    chargeMapLastFrame =
        new TH2F("chargeMapLastFrame", title.c_str(), xpixels, -0.5, xpixels - 0.5, ypixels, -0.5, ypixels - 0.5);

    title = "Hits per frame;hits;frame";
    hitsPerFrame = new TH1F("hitsPerFrame", title.c_str(), xpixels * ypixels / 50, -0.5, xpixels * ypixels - 0.5);
    title = "Charge per frame;charge [ke];frame";
    chargePerFrame = new TH1F("chargePerFrame", title.c_str(), 1000, 0, 5e6);

    title = "Hit column (projection X);x [px];hits";
    projectionX = new TH1F("projectionX", title.c_str(), xpixels, -0.5, xpixels - 0.5);
    title = "Hit column (projection Y);y [px];hits";
    projectionY = new TH1F("projectionY", title.c_str(), ypixels, -0.5, ypixels - 0.5);

    title = "Charge column (projection X);x [px];charge [ke]";
    projectionChargeX = new TH1F("projectionChargeX", title.c_str(), xpixels, -0.5, xpixels - 0.5);
    title = "Charge column (projection Y);y [px];charge [ke]";
    projectionChargeY = new TH1F("projectionChargeY", title.c_str(), ypixels, -0.5, ypixels - 0.5);

    title = "centers (RMS) X;RMS X [px];frames";
    centersX = new TH1F("centersX", title.c_str(), xpixels, -0.5, xpixels - 0.5);
    title = "centers (RMS) Y;RMS Y [px];frames";
    centersY = new TH1F("centersY", title.c_str(), ypixels, -0.5, ypixels - 0.5);

    title = "Widths (RMS) X;RMS X [px];frames";
    widthsX = new TH1F("widthsX", title.c_str(), 1000, 0, 50);
    title = "Widths (RMS) Y;RMS Y [px];frames";
    widthsY = new TH1F("widthsY", title.c_str(), 1000, 0, 50);

    title = "Hits per frame vs Frame Nr.;frame;hits";
    nHitsVsFrame = new TProfile("nHitsVsFrame", title.c_str(), 10, -0.5, plot_frames - 0.5);
    nHitsVsFrame->GetXaxis()->SetCanExtend(true);
    title = "Charge per frame vs Frame Nr.;frame;charge [ke]";
    chargeVsFrame = new TProfile("chargeVsFrame", title.c_str(), 10, -0.5, plot_frames - 0.5);
    chargeVsFrame->GetXaxis()->SetCanExtend(true);

    title = "Projection X vs Frame Nr.;frame;projection x";
    projectionXVsFrame =
        new TH2F("projectionXVsFrame", title.c_str(), 50, -0.5, plot_frames - 0.5, xpixels / 5, -0.5, xpixels - 0.5);
    projectionXVsFrame->GetXaxis()->SetCanExtend(true);
    title = "Projection Y vs Frame Nr.;frame;projection y";
    projectionYVsFrame =
        new TH2F("projectionYVsFrame", title.c_str(), 50, -0.5, plot_frames - 0.5, xpixels / 5, -0.5, xpixels - 0.5);
    projectionYVsFrame->GetXaxis()->SetCanExtend(true);

    title = "Projection Charge X vs Frame Nr.;frame;projection charge x";
    projectionChargeXVsFrame =
        new TH2F("projectionChargeXVsFrame", title.c_str(), 50, -0.5, plot_frames - 0.5, xpixels / 5, -0.5, xpixels - 0.5);
    projectionChargeXVsFrame->GetXaxis()->SetCanExtend(true);
    title = "Projection Charge Y vs Frame Nr.;frame;projection charge y";
    projectionChargeYVsFrame =
        new TH2F("projectionChargeYVsFrame", title.c_str(), 50, -0.5, plot_frames - 0.5, xpixels / 5, -0.5, xpixels - 0.5);
    projectionChargeYVsFrame->GetXaxis()->SetCanExtend(true);

    title = "Frames vs Time;time [s];frames";
    framesVsTime = new TH1F("framesVsTime", title.c_str(), 20, 0, 20);
    framesVsTime->GetXaxis()->SetCanExtend(true);

    title = "Center position X vs Frame Nr.;frame;center x [px]";
    centersXVsFrame = new TProfile("centersXVsFrame", title.c_str(), 50, -0.5, plot_frames - 0.5);
    centersXVsFrame->GetXaxis()->SetCanExtend(true);
    title = "Center position Y vs Frame Nr.;frame;center y [px]";
    centersYVsFrame = new TProfile("centersYVsFrame", title.c_str(), 50, -0.5, plot_frames - 0.5);
    centersYVsFrame->GetXaxis()->SetCanExtend(true);

    title = "Width X vs Frame Nr.;frame;width x [px]";
    widthsXVsFrame = new TProfile("widthsXVsFrame", title.c_str(), 50, -0.5, plot_frames - 0.5);
    widthsXVsFrame->GetXaxis()->SetCanExtend(true);
    title = "Width Y vs Frame Nr.;frame;width y [px]";
    widthsYVsFrame = new TProfile("widthsYVsFrame", title.c_str(), 50, -0.5, plot_frames - 0.5);
    widthsYVsFrame->GetXaxis()->SetCanExtend(true);

    title = "Width X vs Frame Nr. - Last 1500 frames;frame;width x [px]";
    widthsXVsFrameLast1500 = new TH1F("widthsXVsFrameLast1500", title.c_str(), 1500, -0.5, 1500 - 0.5);
    title = "Width Y vs Frame Nr. - Last 1500 frames;frame;width y [px]";
    widthsYVsFrameLast1500 = new TH1F("widthsYVsFrameLast1500", title.c_str(), 1500, -0.5, 1500 - 0.5);

    title = "Hit Timestamp within Frame;time [us];hits";
    hitTimeWithinFrame = new TH1F("hitTimeWithinFrame", title.c_str(), 2000, 0, 20);

    title = "Pixel Charge;charge [ToT];pixels";
    pixelCharge = new TH1F("pixelCharge", title.c_str(), 1000, -0.5, 1000 - 0.5);

    title = "X-Ray;x [a.u.];y [a.u.]";

    if(compute_xray_) {
        xray = new TH2F("xray", title.c_str(), x_frames_, -0.5, x_frames_, 50, -0.5, 49.5);
    }

    if(store_data_) {
        file_output_ = std::ofstream(config_.get<std::string>("file_name"), std::ofstream::out);
    }
}

StatusCode AnalysisElectronCT::run(const std::shared_ptr<Clipboard>& clipboard) {

    hitMapLastFrame->Reset();
    chargeMapLastFrame->Reset();

    if(ignore_first_frame_ && m_eventNumber == 0) {
        m_eventNumber++;
        return StatusCode::Success;
    }

    auto pixels = clipboard->getData<Pixel>(m_detector->getName());

    long unsigned int nPixels = pixels.size();
    LOG(DEBUG) << "Picked up " << nPixels << " pixels for device " << m_detector->getName();

    double frameStart = clipboard->getEvent()->start();

    // Extend axes if necessary
    if(m_eventNumber > nHitsVsFrame->GetXaxis()->GetXmax()) {
        LOG(DEBUG) << "Extending axis to " << m_eventNumber * 2;
        nHitsVsFrame->ExtendAxis(m_eventNumber * 2, nHitsVsFrame->GetXaxis());
        projectionXVsFrame->ExtendAxis(m_eventNumber * 2, projectionXVsFrame->GetXaxis());
        projectionYVsFrame->ExtendAxis(m_eventNumber * 2, projectionYVsFrame->GetXaxis());
        projectionChargeXVsFrame->ExtendAxis(m_eventNumber * 2, projectionChargeXVsFrame->GetXaxis());
        projectionChargeYVsFrame->ExtendAxis(m_eventNumber * 2, projectionChargeYVsFrame->GetXaxis());
        centersXVsFrame->ExtendAxis(m_eventNumber * 2, centersXVsFrame->GetXaxis());
        centersYVsFrame->ExtendAxis(m_eventNumber * 2, centersYVsFrame->GetXaxis());
        widthsXVsFrame->ExtendAxis(m_eventNumber * 2, widthsXVsFrame->GetXaxis());
        widthsYVsFrame->ExtendAxis(m_eventNumber * 2, widthsYVsFrame->GetXaxis());
        chargeVsFrame->ExtendAxis(m_eventNumber * 2, chargeVsFrame->GetXaxis());
    }
    if(static_cast<double>(Units::convert(frameStart, "s")) > framesVsTime->GetXaxis()->GetXmax()) {
        framesVsTime->ExtendAxis(static_cast<double>(Units::convert(frameStart, "s")), framesVsTime->GetXaxis());
    }

    hitsPerFrame->Fill(static_cast<double>(nPixels));
    nHitsVsFrame->Fill(m_eventNumber, static_cast<double>(nPixels));

    framesVsTime->Fill(static_cast<double>(Units::convert(frameStart, "s")));

    if(widthsXLast1500.size() == 1500) {
        widthsXLast1500.erase(widthsXLast1500.begin());
        widthsYLast1500.erase(widthsYLast1500.begin());
    }

    double total_charge = 0;

    for(auto& pixel : pixels) {
        int pxcol = pixel->column();
        int pxrow = pixel->row();
        double pxcharge = pixel->charge();

        total_charge += pxcharge;

        hitMapIntegrated->Fill(pxcol, pxrow);
        hitMapLastFrame->Fill(pxcol, pxrow);

        chargeMapIntegrated->Fill(pxcol, pxrow, pxcharge);
        chargeMapLastFrame->Fill(pxcol, pxrow, pxcharge);

        projectionX->Fill(pxcol);
        projectionY->Fill(pxrow);

        projectionChargeX->Fill(pxcol, pxcharge);
        projectionChargeY->Fill(pxrow, pxcharge);

        projectionXVsFrame->Fill(m_eventNumber, pxcol);
        projectionYVsFrame->Fill(m_eventNumber, pxrow);

        projectionChargeXVsFrame->Fill(m_eventNumber, pxcol, pxcharge);
        projectionChargeYVsFrame->Fill(m_eventNumber, pxrow, pxcharge);

        hitTimeWithinFrame->Fill(static_cast<double>(Units::convert(pixel->timestamp() - frameStart, "us")));

        pixelCharge->Fill(pxcharge);
    }

    double centerX = 0;
    double centerY = 0;
    double widthX = 0;
    double widthY = 0;
    if(charge_weighting_) {
        if(fitted_profile_) {
            auto fitX = new TF1("fitX", "gaus(0)", 0, m_detector->nPixels().X());
            auto projX = chargeMapLastFrame->ProjectionX();
            if(projX->GetEntries() > 10) {
                fitX->SetParameter(1, projX->GetMean());
                fitX->SetParameter(2, projX->GetRMS());
                projX->Fit(fitX, "QNW");
                centerX = fitX->GetParameter(1);
                widthX = fitX->GetParameter(2);
            }

            auto fitY = new TF1("fitY", "gaus(0)", 0, m_detector->nPixels().Y());
            auto projY = chargeMapLastFrame->ProjectionY();
            if(projY->GetEntries() > 10) {
                fitY->SetParameter(1, projY->GetMean());
                fitY->SetParameter(2, projY->GetRMS());
                projY->Fit(fitY, "QNW");
                centerY = fitY->GetParameter(1);
                widthY = fitY->GetParameter(2);
            }
        } else {
            centerX = chargeMapLastFrame->GetMean(1);
            centerY = chargeMapLastFrame->GetMean(2);
            widthX = chargeMapLastFrame->GetRMS(1);
            widthY = chargeMapLastFrame->GetRMS(2);
        }
    } else {
        if(fitted_profile_) {
            auto fitX = new TF1("fitX", "gaus(0)", 0, m_detector->nPixels().X());
            auto projX = hitMapLastFrame->ProjectionX();
            if(projX->GetEntries() > 10) {
                fitX->SetParameter(1, projX->GetMean());
                fitX->SetParameter(2, projX->GetRMS());
                projX->Fit(fitX, "QNW");
                centerX = fitX->GetParameter(1);
                widthX = fitX->GetParameter(2);
            }

            auto fitY = new TF1("fitY", "gaus(0)", 0, m_detector->nPixels().Y());
            auto projY = hitMapLastFrame->ProjectionY();
            if(projY->GetEntries() > 10) {
                fitY->SetParameter(1, projY->GetMean());
                fitY->SetParameter(2, projY->GetRMS());
                projY->Fit(fitY, "QNW");
                centerY = fitY->GetParameter(1);
                widthY = fitY->GetParameter(2);
            }
        } else {
            centerX = hitMapLastFrame->GetMean(1);
            centerY = hitMapLastFrame->GetMean(2);
            widthX = hitMapLastFrame->GetRMS(1);
            widthY = hitMapLastFrame->GetRMS(2);
        }
    }

    centersX->Fill(centerX);
    centersY->Fill(centerY);
    widthsX->Fill(widthX);
    widthsY->Fill(widthY);

    centersXVsFrame->Fill(m_eventNumber, centerX);
    centersYVsFrame->Fill(m_eventNumber, centerY);
    widthsXVsFrame->Fill(m_eventNumber, widthX);
    widthsYVsFrame->Fill(m_eventNumber, widthY);

    chargePerFrame->Fill(total_charge);
    chargeVsFrame->Fill(m_eventNumber, total_charge);

    // Modify running graphs
    widthsXLast1500.push_back(widthX);
    widthsYLast1500.push_back(widthY);
    for(int i = 0; i < std::min(1500, static_cast<int>(widthsXLast1500.size())); ++i) {
        widthsXVsFrameLast1500->SetBinContent(i + 1, widthsXLast1500.at(static_cast<unsigned int>(i)));
        widthsYVsFrameLast1500->SetBinContent(i + 1, widthsYLast1500.at(static_cast<unsigned int>(i)));
    }

    int n = m_eventNumber - chop_frames_;

    if(compute_xray_) {
        int ycoord = static_cast<int>(std::floor(n / x_frames_));
        bool odd_y = static_cast<bool>(ycoord % 2);
        int xcoord = (odd_y ? x_frames_ - n % x_frames_ : n % x_frames_);

        if(n >= 0) {
            xray->SetBinContent(xcoord + 1, ycoord + 1, (widthX + widthY) / 2);
        }
    }

    if(store_data_) {
      file_output_ << n << " " << std::setprecision(3) << std::fixed << static_cast<double>(Units::convert(frameStart, "s")) << std::defaultfloat << " " << (widthX + widthY) / 2 << " " << total_charge << std::endl;
    }

    // Increment event counter
    m_eventNumber++;

    // Return value telling analysis to keep running
    return StatusCode::Success;
}

void AnalysisElectronCT::finalize(const std::shared_ptr<ReadonlyClipboard>&) {

    LOG(DEBUG) << "Analysed " << m_eventNumber << " events";
    if(store_data_) {
        file_output_.close();
    }
}

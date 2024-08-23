#include "ConverterFrame.hpp"
#include "Worker/ProcessHandler.hpp"
#include "Worker/ProgressServer.hpp"

using namespace std;

const vector<wxString> ConverterFrame::inputFormatNames = {"PNG", "JPG", "JPEG", "BMP", "Targa", "Cineon", "DPX", "OpenEXR", "Radiance HDR", "TIFF", "WebP"};
const vector<wxString> ConverterFrame::outputFormatNames = {"MP4", "QuickTime", "Ogg", "Matroska (MKV)"};
const vector<wxString> ConverterFrame::inputFormats = {"png", "jpg", "jpeg", "bmp", "tga", "cin", "dpx", "exr", "hdr", "tiff", "webp"};
const vector<wxString> ConverterFrame::outputFormats = {"mp4", "mov", "ogg", "mkv"};

ConverterFrame::ConverterFrame(wxWindow *parent) : AbstractConverterFrame(parent) {
    choiceInput->Set(inputFormatNames);
    choiceInput->SetSelection(0);

    choiceOutput->Set(outputFormatNames);
    choiceOutput->SetSelection(0);

    const wxTextValidator validator(wxFILTER_NUMERIC);
    txtFps->SetValidator(validator);
}

void ConverterFrame::onSelectInput(wxCommandEvent& event) {

}

void ConverterFrame::onFormatInput(wxCommandEvent& event) {

}

void ConverterFrame::onSelectOutput(wxCommandEvent& event) {

}

void ConverterFrame::onFormatOutput(wxCommandEvent& event) {

}

void ConverterFrame::onConvert(wxCommandEvent& event) {

}

void ConverterFrame::setFrameNumber(const int &number) const {
    gaugeProgress->SetValue(number);
}

void ConverterFrame::reportSuccess() const {
    cout << "Success" << endl;
}

void ConverterFrame::reportError() const {
    cout << "Error" << endl;
}


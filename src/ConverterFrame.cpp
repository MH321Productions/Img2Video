#include "ConverterFrame.hpp"

using namespace std;

const vector<wxString> ConverterFrame::inputFormatNames = {"PNG", "JPG", "JPEG", "BMP", "Targa", "Cineon", "DPX", "OpenEXR", "Radiance HDR", "TIFF", "WebP"};
const vector<wxString> ConverterFrame::outputFormatNames = {"MP4", "QuickTime", "Ogg", "Matroska (MKV)"};
const vector<string> ConverterFrame::inputFormats = {"png", "jpg", "jpeg", "bmp", "tga", "cin", "dpx", "exr", "hdr", "tiff", "webp"};
const vector<string> ConverterFrame::outputFormats = {"mp4", "mov", "ogg", "mkv"};

ConverterFrame::ConverterFrame(wxWindow *parent) : AbstractConverterFrame(parent) {
    choiceInput->Set(inputFormatNames);
    choiceInput->SetSelection(0);

    choiceOutput->Set(outputFormatNames);
    choiceOutput->SetSelection(0);
}

void ConverterFrame::onTextInput(wxCommandEvent& event) {

}

void ConverterFrame::onSelectInput(wxCommandEvent& event) {

}

void ConverterFrame::onFormatInput(wxCommandEvent& event) {

}

void ConverterFrame::onTextOutput(wxCommandEvent& event) {

}

void ConverterFrame::onSelectOutput(wxCommandEvent& event) {

}

void ConverterFrame::onFormatOutput(wxCommandEvent& event) {

}

void ConverterFrame::onConvert(wxCommandEvent& event) {

}
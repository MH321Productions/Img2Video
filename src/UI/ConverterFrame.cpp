#include <wx/filedlg.h>
#include <wx/dirdlg.h>
#include <wx/msgdlg.h>

#include "ConverterFrame.hpp"
#include "Worker/ProcessHandler.hpp"

using namespace std;

const vector<wxString> ConverterFrame::inputFormatNames = {"PNG", "JPG", "JPEG", "BMP", "Targa", "Cineon", "DPX", "OpenEXR", "Radiance HDR", "TIFF", "WebP"};
const vector<wxString> ConverterFrame::outputFormatNames = {"MP4", "QuickTime", "Ogg", "Matroska (MKV)"};
const vector<wxString> ConverterFrame::inputFormats = {"png", "jpg", "jpeg", "bmp", "tga", "cin", "dpx", "exr", "hdr", "tiff", "webp"};
const vector<wxString> ConverterFrame::outputFormats = {"mp4", "mov", "ogg", "mkv"};
const wxString ConverterFrame::wildcardFormatter = "%s Files|*.%s";
const wxString ConverterFrame::inputFormatter = "%s/%%04d.%s";

wxDEFINE_EVENT(EVT_CONVERT_STATUS, ConvertStatusEvent);

ConverterFrame::ConverterFrame(wxWindow *parent) : AbstractConverterFrame(parent), processHandler(this) {
    choiceInput->Set(inputFormatNames);
    choiceInput->SetSelection(0);

    choiceOutput->Set(outputFormatNames);
    choiceOutput->SetSelection(0);

    const wxTextValidator validator(wxFILTER_NUMERIC);
    txtFps->SetValidator(validator);

    Bind(EVT_CONVERT_STATUS, &ConverterFrame::onSetConvertStatus, this);
}

void ConverterFrame::onClosing(wxCloseEvent &event) {
    if (running) {
        if (wxMessageBox("A conversion is still running. Do You want to abort it?", "Confirmation required", wxYES_NO | wxICON_WARNING | wxCENTER, this) == wxYES) {
            processHandler.abortConversion();
            this->Destroy();
        }
        else event.Veto();
    } else {
        this->Destroy();
    }
}

void ConverterFrame::onSelectInput(wxCommandEvent& event) {
    wxDirDialog dialog(this, "Select input directory");
    if (dialog.ShowModal() != wxID_OK) return;

    inputFolder = dialog.GetPath();
    txtInputFolder->SetValue(inputFolder);
    checkCanConvert();
}

void ConverterFrame::onFormatInput(wxCommandEvent& event) {
    selectedInputFormat = choiceInput->GetSelection();
    checkCanConvert();
}

void ConverterFrame::onSelectOutput(wxCommandEvent& event) {
    wxFileDialog dialog(
        this, "Select output file",
        "", "",
        wxString::Format(wildcardFormatter, outputFormatNames.at(selectedOutputFormat), outputFormats.at(selectedOutputFormat)),
        wxFD_SAVE | wxFD_OVERWRITE_PROMPT
    );
    if (dialog.ShowModal() != wxID_OK) return;

    outputFile = dialog.GetPath();
    if (!outputFile.EndsWith(outputFormats.at(selectedOutputFormat))) outputFile.Append('.').Append(outputFormats.at(selectedOutputFormat));

    txtOutputFile->SetValue(outputFile);
    checkCanConvert();
}

void ConverterFrame::onFormatOutput(wxCommandEvent& event) {
    int oldSelection = selectedOutputFormat;
    selectedOutputFormat = choiceOutput->GetSelection();

    if (!outputFile.IsEmpty()) {
        outputFile.RemoveLast(outputFormats.at(oldSelection).length() + 1);
        outputFile.Append('.').Append(outputFormats.at(selectedOutputFormat));
        txtOutputFile->SetValue(outputFile);
    }

    checkCanConvert();
}

void ConverterFrame::onFps(wxCommandEvent &event) {
    fps = txtFps->GetValue();
    checkCanConvert();
}

void ConverterFrame::onSetConvertStatus(ConvertStatusEvent &event) {
    wxString speedTxt = "Speed: ";
    speedTxt << event.getSpeed() << "x";

    gaugeProgress->SetValue(event.getFrameNumber());
    lblFrames->SetLabel(wxString::Format("Frames: %d/%d", event.getFrameNumber(), totalFrameCount));
    lblSpeed->SetLabel(speedTxt);
}

void ConverterFrame::onConvert(wxCommandEvent& event) {
    running = true;
    btnStart->Disable();

    //Construct input argument
    wxString input = wxString::Format(inputFormatter, inputFolder, inputFormats.at(selectedInputFormat));

    //Start ffmpeg
    ProcessInfo info = {
         input,
         outputFile,
         fps
    };
    processHandler.startConversion(info);
    btnStop->Enable();
}

void ConverterFrame::onAbortConversion(wxCommandEvent &event) {
    if (wxMessageBox("Should the conversion be aborted?", "Confirmation required", wxYES_NO | wxCENTER | wxICON_QUESTION, this) != wxYES) return;

    bool aborted = processHandler.abortConversion();
    btnStop->Disable();
    btnStart->Enable();
    gaugeProgress->SetValue(0);
    running = false;

    if (aborted) wxMessageBox("The conversion was aborted", "Information", wxOK | wxICON_INFORMATION, this);
}

void ConverterFrame::setTotalFrameCount(const int &number) {
    totalFrameCount = number;
    gaugeProgress->SetRange(totalFrameCount);
}

void ConverterFrame::setConversionStatus(const int &number, const double& speed) {
    auto* event = new ConvertStatusEvent(EVT_CONVERT_STATUS, GetId(), number, speed);
    event->SetEventObject(this);

    QueueEvent(event);
}

void ConverterFrame::checkCanConvert() {
    if (!inputFolder.IsEmpty() && !outputFile.IsEmpty() && !fps.IsEmpty() && !running) btnStart->Enable();
    else btnStart->Disable();
}

void ConverterFrame::reportSuccess() {
    running = false;
    btnStop->Disable();

    wxMessageBox("The images were converted successfully", "Conversion finished", wxOK | wxICON_INFORMATION, this);

    checkCanConvert();
}

void ConverterFrame::reportError(const wxString& reason) {
    running = false;
    btnStop->Disable();

    wxString msg = "The images couldn't be converted";
    if (!reason.IsEmpty()) msg << ":\n" << reason;

    wxMessageBox(msg, "Conversion error", wxOK | wxICON_ERROR, this); //TODO: Get msg message from ffmpeg

    checkCanConvert();
}

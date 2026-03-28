#ifndef IMG2VIDEO_CONVERTERFRAME_HPP
#define IMG2VIDEO_CONVERTERFRAME_HPP

#include <vector>
#include <thread>

#include "AbstractConverterFrame.h"
#include "Worker/ProcessHandler.hpp"

class ConvertStatusEvent : public wxEvent {
    public:
        ConvertStatusEvent(wxEventType eventType, int winid, const int& frameNumber, const double& speed)
            : wxEvent(winid, eventType), frameNumber(frameNumber), speed(speed) {}

        wxEvent* Clone() const override { return new ConvertStatusEvent(*this); }

        int getFrameNumber() const { return frameNumber; }
        double getSpeed() const { return speed; }

    private:
        const int frameNumber;
        const double speed;
};

class ConverterFrame : public AbstractConverterFrame {
    public:
        explicit ConverterFrame(wxWindow* parent);

        void setTotalFrameCount(const int& number);
        void setConversionStatus(const int& number, const double& speed);
        void reportSuccess();
        void reportError(const wxString& reason = wxEmptyString);

    private:
        static const std::vector<wxString> inputFormatNames;
        static const std::vector<wxString> outputFormatNames;
        static const std::vector<wxString> inputFormats;
        static const std::vector<wxString> outputFormats;
        static const wxString wildcardFormatter;
        static const wxString inputFormatter;

        wxString inputFolder = "";
        wxString outputFile = "";
        wxString fps = "";
        int selectedInputFormat = 0;
        int selectedOutputFormat = 0;
        ProcessHandler processHandler;
        bool running = false;
        int totalFrameCount = 0;

        void onClosing(wxCloseEvent& event) override;
        void onSelectInput(wxCommandEvent& event) override;
        void onFormatInput(wxCommandEvent& event) override;
        void onSelectOutput(wxCommandEvent& event) override;
        void onFormatOutput(wxCommandEvent& event) override;
        void onFps(wxCommandEvent& event) override;
        void onConvert(wxCommandEvent& event) override;
        void onAbortConversion(wxCommandEvent& event) override;
        void onSetConvertStatus(ConvertStatusEvent& event);

        void checkCanConvert();
};

wxDECLARE_EVENT(EVT_CONVERT_STATUS, ConvertStatusEvent);

#endif //IMG2VIDEO_CONVERTERFRAME_HPP

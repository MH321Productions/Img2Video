#ifndef IMG2VIDEO_CONVERTERFRAME_HPP
#define IMG2VIDEO_CONVERTERFRAME_HPP

#include <vector>
#include <thread>

#include "AbstractConverterFrame.h"

class ConverterFrame : public virtual AbstractConverterFrame {
    public:
        explicit ConverterFrame(wxWindow* parent);

        void setFrameNumber(const int& number) const;
        void reportSuccess() const;
        void reportError() const;

    private:
        static const std::vector<wxString> inputFormatNames;
        static const std::vector<wxString> outputFormatNames;
        static const std::vector<wxString> inputFormats;
        static const std::vector<wxString> outputFormats;

        wxString inputFolder = "/home/mika/RenderedImages"; //TODO: Don't hardcode
        wxString outputFile = "/home/mika/Test.mp4";        //TODO: Don't hardcode
        std::thread progressServerThread;
        std::thread processHandlerThread;

        void onSelectInput(wxCommandEvent& event) override;
        void onFormatInput(wxCommandEvent& event) override;
        void onSelectOutput(wxCommandEvent& event) override;
        void onFormatOutput(wxCommandEvent& event) override;
        void onConvert(wxCommandEvent& event) override;
};

#endif //IMG2VIDEO_CONVERTERFRAME_HPP

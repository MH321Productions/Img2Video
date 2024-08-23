#ifndef IMG2VIDEO_CONVERTERFRAME_HPP
#define IMG2VIDEO_CONVERTERFRAME_HPP

#include <vector>
#include <map>
#include <string>

#include "AbstractConverterFrame.h"

class ConverterFrame : public virtual AbstractConverterFrame {
    public:
        explicit ConverterFrame(wxWindow* parent);

    private:
        static const std::vector<wxString> inputFormatNames;
        static const std::vector<wxString> outputFormatNames;
        static const std::vector<std::string> inputFormats;
        static const std::vector<std::string> outputFormats;

        void onTextInput(wxCommandEvent& event) override;
        void onSelectInput(wxCommandEvent& event) override;
        void onFormatInput(wxCommandEvent& event) override;
        void onTextOutput(wxCommandEvent& event) override;
        void onSelectOutput(wxCommandEvent& event) override;
        void onFormatOutput(wxCommandEvent& event) override;
        void onConvert(wxCommandEvent& event) override;
};

#endif //IMG2VIDEO_CONVERTERFRAME_HPP

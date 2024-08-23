#include <wx/wx.h>

#include "ConverterFrame.hpp"

class ConverterApplication : public wxApp {
    public:
        bool OnInit() override {
            ConverterFrame* frame = new ConverterFrame(nullptr);
            frame->Show();
            return true;
        }
};

wxIMPLEMENT_APP(ConverterApplication);
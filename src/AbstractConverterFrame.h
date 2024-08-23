///////////////////////////////////////////////////////////////////////////
// C++ code generated with wxFormBuilder (version 4.2.1-0-g80c4cb6)
// http://www.wxformbuilder.org/
//
// PLEASE DO *NOT* EDIT THIS FILE!
///////////////////////////////////////////////////////////////////////////

#pragma once

#include <wx/artprov.h>
#include <wx/xrc/xmlres.h>
#include <wx/intl.h>
#include <wx/string.h>
#include <wx/stattext.h>
#include <wx/gdicmn.h>
#include <wx/font.h>
#include <wx/colour.h>
#include <wx/settings.h>
#include <wx/textctrl.h>
#include <wx/button.h>
#include <wx/bitmap.h>
#include <wx/image.h>
#include <wx/icon.h>
#include <wx/choice.h>
#include <wx/sizer.h>
#include <wx/frame.h>

///////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
/// Class AbstractConverterFrame
///////////////////////////////////////////////////////////////////////////////
class AbstractConverterFrame : public wxFrame
{
	private:

	protected:
		wxStaticText* lblInputFolder;
		wxTextCtrl* txtInputFolder;
		wxButton* btnInputFolder;
		wxStaticText* lblInputFormat;
		wxChoice* choiceInput;
		wxStaticText* lblOutputFile;
		wxTextCtrl* txtOutputFile;
		wxButton* btnOutputFile;
		wxStaticText* lblOutputFormat;
		wxChoice* choiceOutput;
		wxButton* btnStart;

		// Virtual event handlers, override them in your derived class
		virtual void onTextInput( wxCommandEvent& event ) { event.Skip(); }
		virtual void onSelectInput( wxCommandEvent& event ) { event.Skip(); }
		virtual void onFormatInput( wxCommandEvent& event ) { event.Skip(); }
		virtual void onTextOutput( wxCommandEvent& event ) { event.Skip(); }
		virtual void onSelectOutput( wxCommandEvent& event ) { event.Skip(); }
		virtual void onFormatOutput( wxCommandEvent& event ) { event.Skip(); }
		virtual void onConvert( wxCommandEvent& event ) { event.Skip(); }


	public:

		AbstractConverterFrame( wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = _("Img2Video"), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( 500,300 ), long style = wxCAPTION|wxCLOSE_BOX|wxMINIMIZE_BOX|wxSYSTEM_MENU|wxCLIP_CHILDREN|wxTAB_TRAVERSAL );

		~AbstractConverterFrame();

};


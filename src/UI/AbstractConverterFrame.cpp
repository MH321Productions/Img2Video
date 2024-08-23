///////////////////////////////////////////////////////////////////////////
// C++ code generated with wxFormBuilder (version 4.2.1-0-g80c4cb6)
// http://www.wxformbuilder.org/
//
// PLEASE DO *NOT* EDIT THIS FILE!
///////////////////////////////////////////////////////////////////////////

#include "AbstractConverterFrame.h"

///////////////////////////////////////////////////////////////////////////

AbstractConverterFrame::AbstractConverterFrame( wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style ) : wxFrame( parent, id, title, pos, size, style )
{
	this->SetSizeHints( wxSize( -1,-1 ), wxSize( -1,-1 ) );

	wxBoxSizer* szMain;
	szMain = new wxBoxSizer( wxVERTICAL );

	wxFlexGridSizer* szIO;
	szIO = new wxFlexGridSizer( 3, 5, 0, 0 );
	szIO->AddGrowableCol( 1 );
	szIO->AddGrowableRow( 0 );
	szIO->AddGrowableRow( 1 );
	szIO->AddGrowableRow( 2 );
	szIO->SetFlexibleDirection( wxBOTH );
	szIO->SetNonFlexibleGrowMode( wxFLEX_GROWMODE_SPECIFIED );

	lblInputFolder = new wxStaticText( this, wxID_ANY, _("Input folder:"), wxDefaultPosition, wxDefaultSize, 0 );
	lblInputFolder->Wrap( -1 );
	szIO->Add( lblInputFolder, 0, wxALIGN_CENTER_VERTICAL|wxALIGN_RIGHT|wxALL, 5 );

	txtInputFolder = new wxTextCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_READONLY );
	szIO->Add( txtInputFolder, 0, wxALIGN_CENTER_VERTICAL|wxALL|wxEXPAND, 5 );

	btnInputFolder = new wxButton( this, wxID_ANY, _("Select folder"), wxDefaultPosition, wxDefaultSize, 0 );
	szIO->Add( btnInputFolder, 0, wxALIGN_CENTER_VERTICAL|wxALL|wxEXPAND, 5 );

	lblInputFormat = new wxStaticText( this, wxID_ANY, _("Input format:"), wxDefaultPosition, wxDefaultSize, 0 );
	lblInputFormat->Wrap( -1 );
	szIO->Add( lblInputFormat, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5 );

	wxArrayString choiceInputChoices;
	choiceInput = new wxChoice( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, choiceInputChoices, 0 );
	choiceInput->SetSelection( 0 );
	szIO->Add( choiceInput, 0, wxALIGN_CENTER_VERTICAL|wxALL|wxEXPAND, 5 );

	lblOutputFile = new wxStaticText( this, wxID_ANY, _("Output file:"), wxDefaultPosition, wxDefaultSize, 0 );
	lblOutputFile->Wrap( -1 );
	szIO->Add( lblOutputFile, 0, wxALIGN_CENTER_VERTICAL|wxALIGN_RIGHT|wxALL, 5 );

	txtOutputFile = new wxTextCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_READONLY );
	szIO->Add( txtOutputFile, 0, wxALIGN_CENTER_VERTICAL|wxALL|wxEXPAND, 5 );

	btnOutputFile = new wxButton( this, wxID_ANY, _("Select file"), wxDefaultPosition, wxDefaultSize, 0 );
	szIO->Add( btnOutputFile, 0, wxALIGN_CENTER_VERTICAL|wxALL|wxEXPAND, 5 );

	lblOutputFormat = new wxStaticText( this, wxID_ANY, _("Output format:"), wxDefaultPosition, wxDefaultSize, 0 );
	lblOutputFormat->Wrap( -1 );
	szIO->Add( lblOutputFormat, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5 );

	wxArrayString choiceOutputChoices;
	choiceOutput = new wxChoice( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, choiceOutputChoices, 0 );
	choiceOutput->SetSelection( 0 );
	szIO->Add( choiceOutput, 0, wxALIGN_CENTER_VERTICAL|wxALL|wxEXPAND, 5 );

	lblFps = new wxStaticText( this, wxID_ANY, _("FPS:"), wxDefaultPosition, wxDefaultSize, 0 );
	lblFps->Wrap( -1 );
	szIO->Add( lblFps, 0, wxALIGN_CENTER_VERTICAL|wxALIGN_RIGHT|wxALL, 5 );

	txtFps = new wxTextCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
	szIO->Add( txtFps, 0, wxALIGN_CENTER_VERTICAL|wxALL|wxEXPAND, 5 );


	szMain->Add( szIO, 1, wxEXPAND, 5 );

	btnStart = new wxButton( this, wxID_ANY, _("Convert!"), wxDefaultPosition, wxDefaultSize, 0 );
	btnStart->Enable( false );

	szMain->Add( btnStart, 0, wxALL|wxEXPAND, 5 );

	gaugeProgress = new wxGauge( this, wxID_ANY, 100, wxDefaultPosition, wxDefaultSize, wxGA_HORIZONTAL );
	gaugeProgress->SetValue( 0 );
	szMain->Add( gaugeProgress, 0, wxALL|wxEXPAND, 5 );


	this->SetSizer( szMain );
	this->Layout();

	this->Centre( wxBOTH );

	// Connect Events
	btnInputFolder->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( AbstractConverterFrame::onSelectInput ), NULL, this );
	choiceInput->Connect( wxEVT_COMMAND_CHOICE_SELECTED, wxCommandEventHandler( AbstractConverterFrame::onFormatInput ), NULL, this );
	btnOutputFile->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( AbstractConverterFrame::onSelectOutput ), NULL, this );
	choiceOutput->Connect( wxEVT_COMMAND_CHOICE_SELECTED, wxCommandEventHandler( AbstractConverterFrame::onFormatOutput ), NULL, this );
	btnStart->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( AbstractConverterFrame::onConvert ), NULL, this );
}

AbstractConverterFrame::~AbstractConverterFrame()
{
}

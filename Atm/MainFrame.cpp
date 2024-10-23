#include "MainFrame.h"
#include "Account.h"
#include "FormatValidate.h"
#include <wx/wx.h>
#include <string>
#include <ctime>
#include <wx/valtext.h>
#include <wx/sound.h>

MainFrame::MainFrame(const wxString& title) : wxFrame(nullptr, wxID_ANY, title, wxDefaultPosition, wxDefaultSize, wxDEFAULT_FRAME_STYLE & ~(wxRESIZE_BORDER)) 
{
	CreateControls();
	BindEventHandlers();
	atm.loadAcc();
}

void MainFrame::CreateControls()
{

	wxFont mainFont(wxFontInfo(wxSize(0, 20)).Bold());

	panel = new wxPanel(this);
	panel->SetFont(mainFont);

	panel->SetBackgroundColour(wxColour(8, 17, 17));
	wxBitmap bitmap("images/monitorBg.png", wxBITMAP_TYPE_PNG);
	backgroundBitmap = new wxStaticBitmap(panel, wxID_ANY, bitmap, wxDefaultPosition, wxSize(1024, 768));

	wxBitmap noOpBitmap("images/noOperationBg.jpg", wxBITMAP_TYPE_JPEG);
	noOperationPanel = new wxStaticBitmap(backgroundBitmap, wxID_ANY, noOpBitmap, wxPoint(112, 80), wxSize(800, 600));
	
	wxBitmap processBitmap("images/processBg.jpg", wxBITMAP_TYPE_JPEG);
	processPanel = new wxStaticBitmap(backgroundBitmap, wxID_ANY, processBitmap, wxPoint(112, 80), wxSize(800, 600));
	processPanel->Hide();

	wxBitmap withdrawProcessBitmap("images/withdrawDoneBg.jpg", wxBITMAP_TYPE_JPEG);
	withdrawSuccess = new wxStaticBitmap(backgroundBitmap, wxID_ANY, withdrawProcessBitmap, wxPoint(112, 80), wxSize(800, 600));
	withdrawSuccess->Hide();
	
	wxBitmap depositProcessBitmap("images/depositDoneBg.jpg", wxBITMAP_TYPE_JPEG);
	depositSuccess = new wxStaticBitmap(backgroundBitmap, wxID_ANY, depositProcessBitmap, wxPoint(112, 80), wxSize(800, 600));
	depositSuccess->Hide();

	wxBitmap transferProcessBitmap("images/fundTransferDoneBg.jpg", wxBITMAP_TYPE_JPEG);
	transferSuccess = new wxStaticBitmap(backgroundBitmap, wxID_ANY, transferProcessBitmap, wxPoint(112, 80), wxSize(800, 600));
	transferSuccess->Hide();
	
	wxBitmap takeCardBitmap("images/takeCardBg.jpg", wxBITMAP_TYPE_JPEG);
	takeCard = new wxStaticBitmap(backgroundBitmap, wxID_ANY, takeCardBitmap, wxPoint(112, 80), wxSize(800, 600));
	takeCard->Hide();

	wxBitmap exitAtmBitmap("images/exitBg.jpg", wxBITMAP_TYPE_JPEG);
	exitAtm = new wxStaticBitmap(backgroundBitmap, wxID_ANY, exitAtmBitmap, wxPoint(112, 80), wxSize(800, 600));
	exitAtm->Hide();

	//Register Account
	wxBitmap registerBitmap("images/registerBg.png", wxBITMAP_TYPE_PNG);
	registerPanel = new wxStaticBitmap(backgroundBitmap, wxID_ANY, registerBitmap, wxPoint(112, 80), wxSize(800, 600));

	wxString allowedChars = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz ";
	wxTextValidator nameValidator(wxFILTER_INCLUDE_CHAR_LIST);
	nameValidator.SetCharIncludes(allowedChars);

	registerName = new wxTextCtrl(registerPanel, wxID_ANY, wxEmptyString, wxPoint(320, 200), wxSize(390, 40), 0, nameValidator);
	registerName->SetHint("Enter Name");
	registerName->SetBackgroundColour(wxColor(248, 247, 255));

	registerBirthMonth = new wxTextCtrl(registerPanel, wxID_ANY, wxEmptyString, wxPoint(320, 250), wxSize(40, 40), 0, wxTextValidator(wxFILTER_NUMERIC));
	registerBirthMonth->SetHint("MM");
	registerBirthMonth->SetMaxLength(2);
	registerBirthMonth->SetBackgroundColour(wxColor(248, 247, 255));

	registerBirthDay = new wxTextCtrl(registerPanel, wxID_ANY, wxEmptyString, wxPoint(380, 250), wxSize(40, 40), 0, wxTextValidator(wxFILTER_NUMERIC));
	registerBirthDay->SetHint("DD");
	registerBirthDay->SetMaxLength(2);
	registerBirthDay->SetBackgroundColour(wxColor(248, 247, 255));

	registerBirthYear = new wxTextCtrl(registerPanel, wxID_ANY, wxEmptyString, wxPoint(440, 250), wxSize(70, 40), 0, wxTextValidator(wxFILTER_NUMERIC));
	registerBirthYear->SetHint("YYYY");
	registerBirthYear->SetMaxLength(4);
	registerBirthYear->SetBackgroundColour(wxColor(248, 247, 255));

	registerContact = new wxTextCtrl(registerPanel, wxID_ANY, wxEmptyString, wxPoint(320, 300), wxSize(190, 40), 0, wxTextValidator(wxFILTER_NUMERIC));
	registerContact->SetHint("+63(9XX)-XXX-XXXX");
	registerContact->SetMaxLength(13);
	registerContact->SetBackgroundColour(wxColor(248, 247, 255));

	registerPin = new wxTextCtrl(registerPanel, wxID_ANY, wxEmptyString, wxPoint(320, 350), wxSize(190, 40), wxTE_PASSWORD, wxTextValidator(wxFILTER_NUMERIC));
	registerPin->SetHint("Enter Pin");
	registerPin->SetMaxLength(6);
	registerPin->SetBackgroundColour(wxColor(248, 247, 255));

	registerAccButton = new wxButton(registerPanel, wxID_ANY, "Confirm", wxPoint(320, 410), wxSize(190, 50));

	cancelRegisterButton = new wxButton(registerPanel, wxID_ANY, "Cancel", wxPoint(520, 410), wxSize(190, 50));
	registerPanel->Hide();
	
	//Initial Deposit Before Complete Register
	wxBitmap initialDepositBitmap("images/initialDepositBg.png", wxBITMAP_TYPE_PNG);
	initialDepositPanel = new wxStaticBitmap(backgroundBitmap, wxID_ANY, initialDepositBitmap, wxPoint(112, 80), wxSize(800, 600));

	inputInitialDeposit = new wxTextCtrl(initialDepositPanel, wxID_ANY, wxEmptyString, wxPoint(450, 250), wxSize(120, 40), 0, wxTextValidator(wxFILTER_NUMERIC));
	inputInitialDeposit->SetHint("0.00");
	inputInitialDeposit->SetMaxLength(8);
	inputInitialDeposit->SetBackgroundColour(wxColor(248, 247, 255));

	confirmInitialDepositButton = new wxButton(initialDepositPanel, wxID_ANY, "Confirm", wxPoint(320, 350), wxSize(190, 50));
	cancelInitialDepositButton = new wxButton(initialDepositPanel, wxID_ANY, "Cancel", wxPoint(520, 350), wxSize(190, 50));
	initialDepositPanel->Hide();

	//Enter Account
	wxBitmap enterAccBitmap("images/enterAccBg.png", wxBITMAP_TYPE_PNG);
	enterAccountPanel = new wxStaticBitmap(backgroundBitmap, wxID_ANY, enterAccBitmap, wxPoint(112, 80), wxSize(800, 600));

	enterAccNum = new wxTextCtrl(enterAccountPanel, wxID_ANY, wxEmptyString, wxPoint(320, 200), wxSize(390, 40), 0, wxTextValidator(wxFILTER_NUMERIC));
	enterAccNum->SetHint("Enter Account Number");
	enterAccNum->SetMaxLength(5);
	enterAccNum->SetBackgroundColour(wxColor(248, 247, 255));

	enterPin = new wxTextCtrl(enterAccountPanel, wxID_ANY, wxEmptyString, wxPoint(320, 250), wxSize(190, 40), wxTE_PASSWORD, wxTextValidator(wxFILTER_NUMERIC));
	enterPin->SetHint("Enter Pin");
	enterPin->SetMaxLength(6);
	enterPin->SetBackgroundColour(wxColor(248, 247, 255));

	enterAccButton = new wxButton(enterAccountPanel, wxID_ANY, "Confirm", wxPoint(320, 330), wxSize(190, 50));
	cancelEnterAccountButton = new wxButton(enterAccountPanel, wxID_ANY, "Cancel", wxPoint(520, 330), wxSize(190, 50));
	enterAccountPanel->Hide();

	//Main Menu
	wxBitmap mainMenuBitmap("images/mainMenuBg.png", wxBITMAP_TYPE_PNG);
	mainPanel = new wxStaticBitmap(backgroundBitmap, wxID_ANY, mainMenuBitmap, wxPoint(112, 80), wxSize(800, 600));
	
	balanceButton = new wxButton(mainPanel, wxID_ANY, "BALANCE INQUIRY", wxPoint(280, 190), wxSize(225, 69));
	depositButton = new wxButton(mainPanel, wxID_ANY, "DEPOSIT", wxPoint(280, 270), wxSize(225, 69));
	fundTransferButton = new wxButton(mainPanel, wxID_ANY, "FUND TRANSFER", wxPoint(280, 350), wxSize(225, 69));
	withdrawButton = new wxButton(mainPanel, wxID_ANY, "WITHDRAW", wxPoint(520, 190), wxSize(225, 69));
	accountSettingsButton = new wxButton(mainPanel, wxID_ANY, "ACCOUNT", wxPoint(520, 270), wxSize(225, 69));
	cancelMainMenuButton = new wxButton(mainPanel, wxID_ANY, "CANCEL", wxPoint(520, 350), wxSize(225, 69));
	mainPanel->Hide();

	//Balance Inquiry
	wxBitmap balanceBitmap("images/balanceBg.png", wxBITMAP_TYPE_PNG);
	balancePanel = new wxStaticBitmap(backgroundBitmap, wxID_ANY, balanceBitmap, wxPoint(112, 80), wxSize(800, 600));
	
	printBalance = new wxStaticText(balancePanel, wxID_ANY, wxEmptyString, wxPoint(340, 190), wxSize(150, 30));
	printBalance->SetBackgroundColour(*wxWHITE);
	wxFont bigFont(wxFontInfo(wxSize(0, 30)).Bold());
	printBalance->SetFont(bigFont);

	returnFromBalanceButton = new wxButton(balancePanel, wxID_ANY, "Return", wxPoint(520, 350), wxSize(190, 50));
	balancePanel->Hide();

	//Deposit
	wxBitmap depositBitmap("images/depositBg.png", wxBITMAP_TYPE_PNG);
	depositPanel = new wxStaticBitmap(backgroundBitmap, wxID_ANY, depositBitmap, wxPoint(112, 80), wxSize(800, 600));

	inputDeposit = new wxTextCtrl(depositPanel, wxID_ANY, wxEmptyString, wxPoint(450, 250), wxSize(120, 40), 0, wxTextValidator(wxFILTER_NUMERIC));
	inputDeposit->SetHint("0.00");
	inputDeposit->SetMaxLength(8);
	inputDeposit->SetBackgroundColour(wxColor(248, 247, 255));

	confirmDeposit = new wxButton(depositPanel, wxID_ANY, "Deposit", wxPoint(320, 350), wxSize(190, 50));
	cancelDepositButton = new wxButton(depositPanel, wxID_ANY, "Cancel", wxPoint(520, 350), wxSize(190, 50));
	depositPanel->Hide();

	//Withdraw
	wxBitmap withdrawBitmap("images/withdrawBg.png", wxBITMAP_TYPE_PNG);
	withdrawPanel = new wxStaticBitmap(backgroundBitmap, wxID_ANY, withdrawBitmap, wxPoint(112, 80), wxSize(800, 600));

	inputWithdraw = new wxTextCtrl(withdrawPanel, wxID_ANY, wxEmptyString, wxPoint(450, 250), wxSize(120, 40), 0, wxTextValidator(wxFILTER_NUMERIC));
	inputWithdraw->SetHint("0.00");
	inputWithdraw->SetMaxLength(8);
	inputWithdraw->SetBackgroundColour(wxColor(248, 247, 255));

	confirmWithdraw = new wxButton(withdrawPanel, wxID_ANY, "Wtihdraw", wxPoint(320, 350), wxSize(190, 50));
	cancelWithdrawButton = new wxButton(withdrawPanel, wxID_ANY, "Cancel", wxPoint(520, 350), wxSize(190, 50));
	withdrawPanel->Hide();

	//Fund Transfer
	wxBitmap fundTransferBitmap("images/fundTransferBg.png", wxBITMAP_TYPE_PNG);
	fundTransferPanel = new wxStaticBitmap(backgroundBitmap, wxID_ANY, fundTransferBitmap, wxPoint(112, 80), wxSize(800, 600));

	inputAccTransfer = new wxTextCtrl(fundTransferPanel, wxID_ANY, wxEmptyString, wxPoint(320, 200), wxSize(390, 40), 0, wxTextValidator(wxFILTER_NUMERIC));
	inputAccTransfer->SetHint("Input Account Number of Recipient");
	inputAccTransfer->SetMaxLength(8);
	inputAccTransfer->SetBackgroundColour(wxColor(248, 247, 255));

	inputAmountTransfer = new wxTextCtrl(fundTransferPanel, wxID_ANY, wxEmptyString, wxPoint(320, 250), wxSize(390, 40), 0, wxTextValidator(wxFILTER_NUMERIC));
	inputAmountTransfer->SetHint("Input Amount to Transfer");
	inputAmountTransfer->SetMaxLength(8);
	inputAmountTransfer->SetBackgroundColour(wxColor(248, 247, 255));

	confirmFundTransferButton = new wxButton(fundTransferPanel, wxID_ANY, "Transfer", wxPoint(320, 330), wxSize(190, 50));
	cancelFundTransferButton = new wxButton(fundTransferPanel, wxID_ANY, "Cancel", wxPoint(520, 330), wxSize(190, 50));
	fundTransferPanel->Hide();

	//Account Settings
	wxBitmap accountSettingsBitmap("images/accountSettingsBg.png", wxBITMAP_TYPE_PNG);
	accountPanel = new wxStaticBitmap(backgroundBitmap, wxID_ANY, accountSettingsBitmap, wxPoint(112, 80), wxSize(800, 600));

	changeAccInfoButton = new wxButton(accountPanel, wxID_ANY, "Change Information", wxPoint(280, 230), wxSize(225, 69));
	changeAccPinButton = new wxButton(accountPanel, wxID_ANY, "Change Pin", wxPoint(520, 230), wxSize(225, 69));
	cancelAccountSettingsButton = new wxButton(accountPanel, wxID_ANY, "Cancel", wxPoint(400, 350), wxSize(225, 69));
	accountPanel->Hide();

	//Change Account Information
	wxBitmap changeInfoBitmap("images/changeInfoBg.jpg", wxBITMAP_TYPE_JPEG);
	changeInfoPanel = new wxStaticBitmap(backgroundBitmap, wxID_ANY, changeInfoBitmap, wxPoint(112, 80), wxSize(800, 600));

	printName = new wxStaticText(changeInfoPanel, wxID_ANY, wxEmptyString, wxPoint(320, 100), wxSize(200, 40));
	printName->SetBackgroundColour(*wxWHITE);

	changeNameInput = new wxTextCtrl(changeInfoPanel, wxID_ANY, wxEmptyString, wxPoint(320, 150), wxSize(390, 40), 0, nameValidator);
	changeNameInput->SetHint("Enter New Name");
	changeNameInput->SetBackgroundColour(wxColor(248, 247, 255));

	printBday = new wxStaticText(changeInfoPanel, wxID_ANY, wxEmptyString, wxPoint(320, 200), wxSize(200, 40));
	printBday->SetBackgroundColour(*wxWHITE);

	changeMonthInput = new wxTextCtrl(changeInfoPanel, wxID_ANY, wxEmptyString, wxPoint(320, 250), wxSize(40, 40), 0, wxTextValidator(wxFILTER_NUMERIC));
	changeMonthInput->SetHint("MM");
	changeMonthInput->SetMaxLength(2);
	changeMonthInput->SetBackgroundColour(wxColor(248, 247, 255));

	changeDayInput = new wxTextCtrl(changeInfoPanel, wxID_ANY, wxEmptyString, wxPoint(380, 250), wxSize(40, 40), 0, wxTextValidator(wxFILTER_NUMERIC));
	changeDayInput->SetHint("DD");
	changeDayInput->SetMaxLength(2);
	changeDayInput->SetBackgroundColour(wxColor(248, 247, 255));

	changeYearInput = new wxTextCtrl(changeInfoPanel, wxID_ANY, wxEmptyString, wxPoint(440, 250), wxSize(70, 40), 0, wxTextValidator(wxFILTER_NUMERIC));
	changeYearInput->SetHint("YYYY");
	changeYearInput->SetMaxLength(4);
	changeYearInput->SetBackgroundColour(wxColor(248, 247, 255));

	printContact = new wxStaticText(changeInfoPanel, wxID_ANY, wxEmptyString, wxPoint(320, 300), wxSize(200, 40));
	printContact->SetBackgroundColour(*wxWHITE);

	changeContactInput = new wxTextCtrl(changeInfoPanel, wxID_ANY, wxEmptyString, wxPoint(320, 350), wxSize(190, 40), 0, wxTextValidator(wxFILTER_NUMERIC));
	changeContactInput->SetHint("+63(9XX)-XXX-XXXX");
	changeContactInput->SetMaxLength(13);
	changeContactInput->SetBackgroundColour(wxColor(248, 247, 255));

	confirmInfoChangeButton = new wxButton(changeInfoPanel, wxID_ANY, "Confirm", wxPoint(320, 410), wxSize(190, 50));
	cancelChangeAccInfoButton = new wxButton(changeInfoPanel, wxID_ANY, "Cancel", wxPoint(520, 410), wxSize(190, 50));

	changeInfoPanel->Hide();

	//Change Pin
	wxBitmap changePinBitmap("images/changePinBg.jpg", wxBITMAP_TYPE_JPEG);
	changePinPanel = new wxStaticBitmap(backgroundBitmap, wxID_ANY, changePinBitmap, wxPoint(112, 80), wxSize(800, 600));

	inputCurrentPin = new wxTextCtrl(changePinPanel, wxID_ANY, wxEmptyString, wxPoint(420, 200), wxSize(200, 40), wxTE_PASSWORD, wxTextValidator(wxFILTER_NUMERIC));
	inputCurrentPin->SetHint("Input Current Pin");
	inputCurrentPin->SetMaxLength(6);
	inputCurrentPin->SetBackgroundColour(wxColor(248, 247, 255));

	inputNewPin = new wxTextCtrl(changePinPanel, wxID_ANY, wxEmptyString, wxPoint(420, 250), wxSize(200, 40), wxTE_PASSWORD, wxTextValidator(wxFILTER_NUMERIC));
	inputNewPin->SetHint("Input New Pin");
	inputNewPin->SetMaxLength(6);
	inputNewPin->SetBackgroundColour(wxColor(248, 247, 255));

	inputConfirmNewPin = new wxTextCtrl(changePinPanel, wxID_ANY, wxEmptyString, wxPoint(420, 300), wxSize(200, 40), wxTE_PASSWORD, wxTextValidator(wxFILTER_NUMERIC));
	inputConfirmNewPin->SetHint("Confirm New Pin");
	inputConfirmNewPin->SetMaxLength(6);
	inputConfirmNewPin->SetBackgroundColour(wxColor(248, 247, 255));

	confirmPinChangeButton = new wxButton(changePinPanel, wxID_ANY, "Confirm", wxPoint(320, 410), wxSize(190, 50));
	cancelChangePinButton = new wxButton(changePinPanel, wxID_ANY, "Cancel", wxPoint(520, 410), wxSize(190, 50));

	changePinPanel->Hide();

}

void MainFrame::BindEventHandlers()
{
	this->Bind(wxEVT_CLOSE_WINDOW, &MainFrame::OnWindowClosed, this);
	this->Bind(wxEVT_CHAR_HOOK, &MainFrame::OnKeyPress, this);

	noOperationPanel->Bind(wxEVT_LEFT_DOWN, &MainFrame::OnScreenClicked, this);

	//Register Acc Binds
	registerAccButton->Bind(wxEVT_BUTTON, &MainFrame::OnRegisterButtonClicked, this);
	registerAccButton->Bind(wxEVT_BUTTON, &MainFrame::OnButtonPressed, this);

	cancelRegisterButton->Bind(wxEVT_BUTTON, &MainFrame::OnCancelRegisterClicked, this);
	cancelRegisterButton->Bind(wxEVT_BUTTON, &MainFrame::OnButtonPressed, this);

	registerName->Bind(wxEVT_TEXT, &MainFrame::NameInput, this);

	registerBirthMonth->Bind(wxEVT_TEXT, &MainFrame::OnInputRegisterMonth, this);
	registerBirthMonth->Bind(wxEVT_KILL_FOCUS, &MainFrame::OnRegisterMonthFocusLost, this);
	registerBirthMonth->Bind(wxEVT_CHAR, &MainFrame::OnlyNumInput, this);

	registerBirthDay->Bind(wxEVT_TEXT, &MainFrame::OnInputRegisterDay, this);
	registerBirthDay->Bind(wxEVT_KILL_FOCUS, &MainFrame::OnRegisterDayFocusLost, this);
	registerBirthDay->Bind(wxEVT_CHAR, &MainFrame::OnlyNumInput, this);

	registerBirthYear->Bind(wxEVT_TEXT, &MainFrame::OnInputRegisterYear, this);
	registerBirthYear->Bind(wxEVT_KILL_FOCUS, &MainFrame::OnRegisterYearFocusLost, this);
	registerBirthYear->Bind(wxEVT_CHAR, &MainFrame::OnlyNumInput, this);

	registerContact->Bind(wxEVT_CHAR, &MainFrame::OnlyNumInput, this);
	registerContact->Bind(wxEVT_TEXT, &MainFrame::OnInputRegisterContact, this);

	registerPin->Bind(wxEVT_CHAR, &MainFrame::OnlyNumInput, this);
	registerPin->Bind(wxEVT_TEXT, &MainFrame::OnInputRegisterPin, this);

	//Initial Deposit
	confirmInitialDepositButton->Bind(wxEVT_BUTTON, &MainFrame::OnConfirmInitialDepositClicked, this);
	confirmInitialDepositButton->Bind(wxEVT_BUTTON, &MainFrame::OnButtonPressed, this);

	cancelInitialDepositButton->Bind(wxEVT_BUTTON, &MainFrame::OnCancelInitialDepositClicked, this);
	cancelInitialDepositButton->Bind(wxEVT_BUTTON, &MainFrame::OnButtonPressed, this);

	inputInitialDeposit->Bind(wxEVT_CHAR, &MainFrame::OnlyNumInput, this);
	inputInitialDeposit->Bind(wxEVT_TEXT, &MainFrame::OnInputFormatInitialDepositAmount, this);
	inputInitialDeposit->Bind(wxEVT_TEXT, &MainFrame::OnInputInitialDeposit, this);

	//Enter Acc Binds
	enterAccButton->Bind(wxEVT_BUTTON, &MainFrame::OnEnterAccButtonClicked, this);
	enterAccButton->Bind(wxEVT_BUTTON, &MainFrame::OnButtonPressed, this);

	cancelEnterAccountButton->Bind(wxEVT_BUTTON, &MainFrame::OnCancelEnterAccClicked, this);
	cancelEnterAccountButton->Bind(wxEVT_BUTTON, &MainFrame::OnButtonPressed, this);

	enterAccNum->Bind(wxEVT_CHAR, &MainFrame::OnlyNumInput, this);
	
	enterPin->Bind(wxEVT_CHAR, &MainFrame::OnlyNumInput, this);
	enterPin->Bind(wxEVT_TEXT, &MainFrame::OnInputEnterPin, this);

	//Main Menu Binds
	cancelMainMenuButton->Bind(wxEVT_BUTTON, &MainFrame::OnCancelMainMenuClicked, this);
	cancelMainMenuButton->Bind(wxEVT_BUTTON, &MainFrame::OnButtonPressed, this);

	//Balance Inquiry Binds
	balanceButton->Bind(wxEVT_BUTTON, &MainFrame::OnBalanceButtonClicked, this);
	balanceButton->Bind(wxEVT_BUTTON, &MainFrame::OnButtonPressed, this);

	returnFromBalanceButton->Bind(wxEVT_BUTTON, &MainFrame::ReturnFromBalanceToMain, this);
	returnFromBalanceButton->Bind(wxEVT_BUTTON, &MainFrame::OnButtonPressed, this);

	//Deposit Binds
	depositButton->Bind(wxEVT_BUTTON, &MainFrame::OnDepositButtonClicked, this);
	depositButton->Bind(wxEVT_BUTTON, &MainFrame::OnButtonPressed, this);

	confirmDeposit->Bind(wxEVT_BUTTON, &MainFrame::OnConfirmDepositClicked, this);
	confirmDeposit->Bind(wxEVT_BUTTON, &MainFrame::OnButtonPressed, this);

	cancelDepositButton->Bind(wxEVT_BUTTON, &MainFrame::OnCancelDepositClicked, this);
	cancelDepositButton->Bind(wxEVT_BUTTON, &MainFrame::OnButtonPressed, this);

	inputDeposit->Bind(wxEVT_CHAR, &MainFrame::OnlyNumInput, this);
	inputDeposit->Bind(wxEVT_TEXT, &MainFrame::OnInputFormatDepositAmount, this);
	inputDeposit->Bind(wxEVT_TEXT, &MainFrame::OnInputDeposit, this);

	//Withdraw Binds
	withdrawButton->Bind(wxEVT_BUTTON, &MainFrame::OnWithdrawButtonClicked, this);
	withdrawButton->Bind(wxEVT_BUTTON, &MainFrame::OnButtonPressed, this);
	
	confirmWithdraw->Bind(wxEVT_BUTTON, &MainFrame::OnConfirmWithdrawClicked, this);
	confirmWithdraw->Bind(wxEVT_BUTTON, &MainFrame::OnButtonPressed, this);

	cancelWithdrawButton->Bind(wxEVT_BUTTON, &MainFrame::OnCancelWithdrawClicked, this);
	cancelWithdrawButton->Bind(wxEVT_BUTTON, &MainFrame::OnButtonPressed, this);

	inputWithdraw->Bind(wxEVT_CHAR, &MainFrame::OnlyNumInput, this);
	inputWithdraw->Bind(wxEVT_TEXT, &MainFrame::OnInputFormatWithdrawAmount, this);
	inputWithdraw->Bind(wxEVT_TEXT, &MainFrame::OnInputWithdraw, this);

	//Fund Transfer Binds
	fundTransferButton->Bind(wxEVT_BUTTON, &MainFrame::OnFundTransferButtonClicked, this);
	fundTransferButton->Bind(wxEVT_BUTTON, &MainFrame::OnButtonPressed, this);

	confirmFundTransferButton->Bind(wxEVT_BUTTON, &MainFrame::OnConfirmFundTransferClicked, this);
	confirmFundTransferButton->Bind(wxEVT_BUTTON, &MainFrame::OnButtonPressed, this);

	cancelFundTransferButton->Bind(wxEVT_BUTTON, &MainFrame::OnCancelFundTransferClicked, this);
	cancelFundTransferButton->Bind(wxEVT_BUTTON, &MainFrame::OnButtonPressed, this);

	inputAccTransfer->Bind(wxEVT_CHAR, &MainFrame::OnlyNumInput, this);
	inputAccTransfer->Bind(wxEVT_TEXT, &MainFrame::OnInputFundTransfer, this);

	inputAmountTransfer->Bind(wxEVT_CHAR, &MainFrame::OnlyNumInput, this);
	inputAmountTransfer->Bind(wxEVT_TEXT, &MainFrame::OnInputFormatTransferAmount, this);
	inputAmountTransfer->Bind(wxEVT_TEXT, &MainFrame::OnInputFundTransfer, this);

	//Change Account Info Binds
	accountSettingsButton->Bind(wxEVT_BUTTON, &MainFrame::OnAccountSettingsClicked, this);
	accountSettingsButton->Bind(wxEVT_BUTTON, &MainFrame::OnButtonPressed, this);

	cancelAccountSettingsButton->Bind(wxEVT_BUTTON, &MainFrame::OnCancelAccSettingsClicked, this);
	cancelAccountSettingsButton->Bind(wxEVT_BUTTON, &MainFrame::OnButtonPressed, this);

	changeAccInfoButton->Bind(wxEVT_BUTTON, &MainFrame::OnChangeAccInfoClicked, this);
	changeAccInfoButton->Bind(wxEVT_BUTTON, &MainFrame::OnButtonPressed, this);

	confirmInfoChangeButton->Bind(wxEVT_BUTTON, &MainFrame::OnConfirmInfoChangeClicked, this);
	confirmInfoChangeButton->Bind(wxEVT_BUTTON, &MainFrame::OnButtonPressed, this);

	cancelChangeAccInfoButton->Bind(wxEVT_BUTTON, &MainFrame::OnCancelChangeAccInfoClicked, this);
	cancelChangeAccInfoButton->Bind(wxEVT_BUTTON, &MainFrame::OnButtonPressed, this);

	changeMonthInput->Bind(wxEVT_TEXT, &MainFrame::OnChangeBirthMonth, this);
	changeMonthInput->Bind(wxEVT_CHAR, &MainFrame::OnlyNumInput, this);
	changeMonthInput->Bind(wxEVT_KILL_FOCUS, &MainFrame::OnChangeMonthFocusLost, this);

	changeDayInput->Bind(wxEVT_TEXT, &MainFrame::OnChangeBirthDay, this);
	changeDayInput->Bind(wxEVT_CHAR, &MainFrame::OnlyNumInput, this);
	changeDayInput->Bind(wxEVT_KILL_FOCUS, &MainFrame::OnChangeDayFocusLost, this);

	changeYearInput->Bind(wxEVT_TEXT, &MainFrame::OnChangeBirthYear, this);
	changeYearInput->Bind(wxEVT_CHAR, &MainFrame::OnlyNumInput, this);
	changeYearInput->Bind(wxEVT_KILL_FOCUS, &MainFrame::OnChangeYearFocusLost, this);

	changeContactInput->Bind(wxEVT_CHAR, &MainFrame::OnlyNumInput, this);
	changeContactInput->Bind(wxEVT_TEXT, &MainFrame::OnChangeContact, this);

	//Change Pin
	changeAccPinButton->Bind(wxEVT_BUTTON, &MainFrame::OnChangeAccPinClicked, this);
	changeAccPinButton->Bind(wxEVT_BUTTON, &MainFrame::OnButtonPressed, this);

	cancelChangePinButton->Bind(wxEVT_BUTTON, &MainFrame::OnCancelChangePinClicked, this);
	cancelChangePinButton->Bind(wxEVT_BUTTON, &MainFrame::OnButtonPressed, this);

	inputCurrentPin->Bind(wxEVT_CHAR, &MainFrame::OnlyNumInput, this);
	inputCurrentPin->Bind(wxEVT_TEXT, &MainFrame::OnInputCurrentPin, this);

	inputNewPin->Bind(wxEVT_CHAR, &MainFrame::OnlyNumInput, this);
	inputNewPin->Bind(wxEVT_TEXT, &MainFrame::OnInputNewPin, this);

	inputConfirmNewPin->Bind(wxEVT_CHAR, &MainFrame::OnlyNumInput, this);
	inputConfirmNewPin->Bind(wxEVT_TEXT, &MainFrame::OnInputConfirmPin, this);

	confirmPinChangeButton->Bind(wxEVT_BUTTON, &MainFrame::OnConfirmPinChangeClicked, this);
	confirmPinChangeButton->Bind(wxEVT_BUTTON, &MainFrame::OnButtonPressed, this);
}

void MainFrame::OnKeyPress(wxKeyEvent& event)
{
	if (event.GetKeyCode() == WXK_F11) {
		bool isFullScreen = this->IsFullScreen();
		this->ShowFullScreen(!isFullScreen, wxFULLSCREEN_NOBORDER);
		backgroundBitmap->Center();
		this->Layout();
	}

	else if (event.GetKeyCode() == 'F' && event.ControlDown()) {
		bool isFullScreen = this->IsFullScreen();
		this->ShowFullScreen(!isFullScreen, wxFULLSCREEN_NOBORDER);
		
		backgroundBitmap->Center();

		this->Layout();
	}
	else {
		event.Skip();
	}
}


void MainFrame::OnWindowClosed(wxCloseEvent& evt)
{
	atm.storeAcc();
	evt.Skip();
}

void MainFrame::OnScreenClicked(wxMouseEvent& evt)
{
	noOperationPanel->Hide();
	
	registerPanel->Show();
	Layout();
}

void MainFrame::OnlyNumInput(wxKeyEvent& evt)
{
	int keyCode = evt.GetKeyCode();

	if (wxIsdigit(keyCode) || keyCode == WXK_BACK) {
		evt.Skip();
	}

}

void MainFrame::NameInput(wxCommandEvent& evt)
{
	wxString name = registerName->GetValue();

	if (name.length() == 1 && name[0] == ' ') {
		registerName->Clear();
	}
}

void MainFrame::OnButtonPressed(wxCommandEvent& evt)
{
	wxSound buttonSFX("sfx/button.wav");
	buttonSFX.Play();
	
	evt.Skip();
}

void MainFrame::OnInputRegisterPin(wxCommandEvent& evt)
{
	formatValidate.OnValidatePin(registerPin);
}

void MainFrame::AddInformation()
{
	d.accNum = std::to_string(atm.createAccNumber());

	if (registerName->IsEmpty() || registerBirthMonth->IsEmpty() || registerBirthDay->IsEmpty() || registerBirthYear->IsEmpty()
		|| registerContact->IsEmpty() || registerPin->IsEmpty()) {

		wxLogMessage("Complete Input Information");
		return;

	}

	long month, day, year;
	if ((registerBirthMonth->GetValue().ToLong(&month) && registerBirthDay->GetValue().ToLong(&day) &&
		registerBirthYear->GetValue().ToLong(&year))) {
		d.bday = formatValidate.FormatBday(month, day, year);
	}
	

	wxString inputContact = registerContact->GetValue();
	if (inputContact.length() < 13) {
		registerContact->SetBackgroundColour(*wxRED);
		registerContact->Clear();
		registerContact->Refresh();
	}
	d.contact = inputContact.ToStdString();
	
	wxString pin = registerPin->GetValue();;
	if (pin.length() < 4) {
		registerPin->SetBackgroundColour(*wxRED);
		registerPin->Clear();
		registerPin->Refresh();
		return;
	}
	d.pinCode = pin.ToStdString();

	wxString inputName = registerName->GetValue();
	inputName = inputName.Trim();
	d.name = inputName.ToStdString();

	if (!(registerName->IsEmpty() && registerBirthMonth->IsEmpty() && registerBirthDay->IsEmpty() && registerBirthYear->IsEmpty()
		&& registerContact->IsEmpty() && registerPin->IsEmpty())) {
		
		registerPanel->Hide();
		initialDepositPanel->Show();

		registerName->Clear();

		registerBirthMonth->Clear();
		registerBirthDay->Clear();
		registerBirthYear->Clear();

		registerContact->Clear();
		registerPin->Clear();

		Layout();
	}
}

void MainFrame::OnCancelRegisterClicked(wxCommandEvent& evt)
{
	registerPanel->Hide();

	registerName->Clear();
	registerBirthMonth->Clear();
	registerBirthDay->Clear();
	registerBirthYear->Clear();
	registerContact->Clear();
	registerPin->Clear();

	enterAccountPanel->Show();
	Layout();
}

void MainFrame::OnInputRegisterContact(wxCommandEvent& evt)
{
	formatValidate.OnValidateContact(registerContact);
}

void MainFrame::OnInputRegisterMonth(wxCommandEvent& evt)
{
	formatValidate.OnValidateMonth(registerBirthMonth, registerBirthDay, registerBirthYear);
}

void MainFrame::OnRegisterMonthFocusLost(wxFocusEvent& evt)
{
	formatValidate.FormatMonthOnFocusLost(registerBirthMonth);
	evt.Skip();
}

void MainFrame::OnInputRegisterDay(wxCommandEvent& evt)
{
	formatValidate.OnValidateDay(registerBirthMonth, registerBirthDay, registerBirthYear);
}

void MainFrame::OnRegisterDayFocusLost(wxFocusEvent& evt)
{
	formatValidate.FormatDayOnFocusLost(registerBirthDay);
	evt.Skip();
}

void MainFrame::OnInputRegisterYear(wxCommandEvent& evt)
{
	formatValidate.OnValidateYear(registerBirthMonth, registerBirthDay, registerBirthYear);
}

void MainFrame::OnRegisterYearFocusLost(wxFocusEvent& evt)
{
	formatValidate.FormatYearOnFocusLost(registerBirthYear);
	evt.Skip();
}

void MainFrame::OnRegisterButtonClicked(wxCommandEvent& evt)
{
	AddInformation();
}

void MainFrame::ConfirmInitialDeposit()
{	
	double initialDeposit = wxAtof(inputInitialDeposit->GetValue());

	int successfulDeposit = atm.confirmInitialDeposit(initialDeposit);

	if (successfulDeposit == -1) {
		inputInitialDeposit->Clear();
		inputInitialDeposit->SetBackgroundColour(*wxRED);
		return;
	}

	if (successfulDeposit == 0) {
		d.balance = initialDeposit;
		atm.registerAcc(d);
		ShowAccountInfo(d);

		inputInitialDeposit->Clear();

		initialDepositPanel->Hide();
		enterAccountPanel->Show();
		Layout();
	}
}

void MainFrame::OnInputInitialDeposit(wxCommandEvent& evt)
{
	wxString amountString = inputInitialDeposit->GetValue();

	if (amountString.length() > 1) {
		inputInitialDeposit->SetBackgroundColour(wxColor(248, 247, 255));
		inputInitialDeposit->Refresh();
	}
	evt.Skip();
}

void MainFrame::OnInputFormatInitialDepositAmount(wxCommandEvent& evt)
{
	formatValidate.FormatAmount(inputInitialDeposit);
}

void MainFrame::OnConfirmInitialDepositClicked(wxCommandEvent& evt)
{
	ConfirmInitialDeposit();
}

void MainFrame::OnCancelInitialDepositClicked(wxCommandEvent& evt)
{
	initialDepositPanel->Hide();
	registerPanel->Show();
	inputInitialDeposit->Clear();
	inputInitialDeposit->SetBackgroundColour(wxColor(248, 247, 255));

	Layout();
}

void MainFrame::ShowAccountInfo(const Account& account)
{
	wxString accountInfo = wxString::Format(
		"Account Number: %s\n"
		"Name: %s\n"
		"Birthday: %s\n"
		"Contact: %s\n"
		"Pin Code: %s",
		account.accNum, account.name, account.bday, account.contact, account.pinCode
	);

	wxMessageBox(accountInfo, "Account Information", wxOK | wxICON_INFORMATION);
}

void MainFrame::EnterAccount()
{
	wxString accNum = enterAccNum->GetValue();
	string num = accNum.ToStdString();

	wxString pinCode = (enterPin->GetValue());
	string pin = pinCode.ToStdString();

	int enter = atm.enterAcc(num, pin);

	if (enter == 1) {
		enterAccountPanel->Hide();
		enterAccNum->Clear();
		enterPin->Clear();
		mainPanel->Show();
		Layout();
	}

	else if(enter == 0) {
		wxLogMessage("Wrong Pin");
		enterPin->SetBackgroundColour(*wxRED);
		enterPin->Clear();
		enterPin->Refresh();
	}

	else if(enter == -1){
		wxLogMessage("Account Not Found");
	}

}

void MainFrame::OnInputEnterPin(wxCommandEvent& evt)
{
	formatValidate.OnValidatePin(enterPin);
}

void MainFrame::OnEnterAccButtonClicked(wxCommandEvent& evt)
{
	EnterAccount();
}

void MainFrame::OnCancelEnterAccClicked(wxCommandEvent& evt)
{
	enterAccountPanel->Hide();

	enterAccNum->Clear();
	enterPin->Clear();
	enterPin->SetBackgroundColour(wxColor(248, 247, 255));
	registerPanel->Show();
	Layout();
}

void MainFrame::BalanceInquiry()
{
	double balance = atm.getBalance();
	wxString currentBalance = wxString::Format("Your Current Balance: \n  %.2f", balance);
	printBalance->SetLabel(currentBalance);
	Layout();
}

void MainFrame::OnBalanceButtonClicked(wxCommandEvent& evt)
{
	mainPanel->Hide();
	balancePanel->Show();
	BalanceInquiry();
}

void MainFrame::ReturnFromBalanceToMain(wxCommandEvent& evt) {
	balancePanel->Hide();
	mainPanel->Show();
	
	Layout();
}

void MainFrame::OnDepositButtonClicked(wxCommandEvent& evt)
{
	mainPanel->Hide();
	depositPanel->Show();
	Layout();
}

void MainFrame::DepositMoney()
{
	double amount = wxAtof(inputDeposit->GetValue());

	if (amount > 0) {
		atm.deposit(amount);
		inputDeposit->Clear();
		ProcessTransaction(depositPanel);
	}
	else {
		inputDeposit->Clear();
		inputDeposit->SetBackgroundColour(*wxRED);
		return;
	}
	 
}

void MainFrame::OnInputDeposit(wxCommandEvent& evt)
{
	wxString amountString = inputDeposit->GetValue();

	if (amountString.length() > 1) {
		inputDeposit->SetBackgroundColour(wxColor(248, 247, 255));
		inputDeposit->Refresh();
	}
	evt.Skip();
}

void MainFrame::OnCancelDepositClicked(wxCommandEvent& evt)
{
	depositPanel->Hide();
	inputDeposit->Clear();
	inputDeposit->SetBackgroundColour(wxColor(248, 247, 255));

	mainPanel->Show();
	Layout();
}

void MainFrame::OnConfirmDepositClicked(wxCommandEvent& evt)
{
	DepositMoney();
}

void MainFrame::OnInputFormatDepositAmount(wxCommandEvent& evt)
{
	formatValidate.FormatAmount(inputDeposit);
}

void MainFrame::OnWithdrawButtonClicked(wxCommandEvent& evt)
{
	mainPanel->Hide();
	withdrawPanel->Show();
	Layout();
}

void MainFrame::OnCancelWithdrawClicked(wxCommandEvent& evt)
{
	withdrawPanel->Hide();
	inputWithdraw->Clear();
	inputWithdraw->SetBackgroundColour(wxColor(248, 247, 255));

	mainPanel->Show();
	Layout();
}

void MainFrame::WithdrawMoney()
{
	
	double amount = wxAtof(inputWithdraw->GetValue());
	double currentBalance = atm.getBalance();

	if (amount <= 0 || amount > currentBalance) {
		inputWithdraw->Clear();
		inputWithdraw->SetBackgroundColour(*wxRED);
		return;
	}
	
	else {
		if (amount <= currentBalance) {
			atm.withdraw(amount);
			ProcessTransaction(withdrawPanel);
			inputWithdraw->Clear();
		}
	}
}

void MainFrame::OnConfirmWithdrawClicked(wxCommandEvent& evt)
{
	WithdrawMoney();
	Layout();
}

void MainFrame::OnInputFormatWithdrawAmount(wxCommandEvent& evt)
{
	formatValidate.FormatAmount(inputWithdraw);
}

void MainFrame::OnInputWithdraw(wxCommandEvent& evt)
{
	wxString amountString = inputWithdraw->GetValue();

	if (amountString.length() > 1) {
		inputWithdraw->SetBackgroundColour(wxColor(248, 247, 255));
		inputWithdraw->Refresh();
	}
	evt.Skip();
}

void MainFrame::OnFundTransferButtonClicked(wxCommandEvent& evt)
{
	mainPanel->Hide();
	fundTransferPanel->Show();
	Layout();
}

void MainFrame::TransferMoney()
{
	if (inputAccTransfer->IsEmpty() || inputAmountTransfer->IsEmpty())
	{
		inputAccTransfer->SetBackgroundColour(*wxRED);
		inputAmountTransfer->SetBackgroundColour(*wxRED);
	}

	else if (!inputAccTransfer->IsEmpty() && !inputAmountTransfer->IsEmpty()) {
		string accNum = inputAccTransfer->GetValue().ToStdString();
		double amount = wxAtof(inputAmountTransfer->GetValue());

		int successfulTransfer = atm.fundTransfer(accNum, amount);

		if (successfulTransfer == -1) {
			wxLogMessage("No Account Found");
			
		}

		else if (successfulTransfer == 0) {
			wxLogMessage("Cannot Transfer to Self");
			inputAccTransfer->Clear();
			inputAccTransfer->SetBackgroundColour(*wxRED);
			inputAccTransfer->Refresh();
		}

		else if (successfulTransfer == -2) {
			inputAmountTransfer->Clear();
			inputAmountTransfer->SetBackgroundColour(*wxRED);
			inputAmountTransfer->Refresh();
		}

		else if (successfulTransfer == 1) {
			inputAccTransfer->Clear();
			inputAmountTransfer->Clear();

			ProcessTransaction(fundTransferPanel);
			Layout();
		}
	}
}

void MainFrame::OnInputFundTransfer(wxCommandEvent& evt)
{
	wxString amountString = inputAmountTransfer->GetValue();
	wxString accString = inputAccTransfer->GetValue();

	if (amountString.length() > 1) {
		inputAmountTransfer->SetBackgroundColour(wxColor(248, 247, 255));
		inputAmountTransfer->Refresh();
	}

	if (accString.length() > 1) {
		inputAccTransfer->SetBackgroundColour(wxColor(248, 247, 255));
		inputAccTransfer->Refresh();
	}

	evt.Skip();
}

void MainFrame::OnInputFormatTransferAmount(wxCommandEvent& evt)
{
	formatValidate.FormatAmount(inputAmountTransfer);
}

void MainFrame::OnConfirmFundTransferClicked(wxCommandEvent& evt)
{
	TransferMoney();
}

void MainFrame::OnCancelFundTransferClicked(wxCommandEvent& evt)
{
	fundTransferPanel->Hide();
	inputAccTransfer->Clear();
	inputAccTransfer->SetBackgroundColour(wxColor(248, 247, 255));

	inputAmountTransfer->Clear();
	inputAmountTransfer->SetBackgroundColour(wxColor(248, 247, 255));

	mainPanel->Show();
	Layout();
}

void MainFrame::OnAccountSettingsClicked(wxCommandEvent& evt)
{
	mainPanel->Hide();
	accountPanel->Show();
	Layout();
}

void MainFrame::OnChangeAccInfoClicked(wxCommandEvent& evt)
{
	accountPanel->Hide();
	changeInfoPanel->Show();
	PrintCurrentInformation();
}

void MainFrame::OnCancelAccSettingsClicked(wxCommandEvent& evt)
{
	accountPanel->Hide();
	mainPanel->Show();
	Layout();
}

void MainFrame::PrintCurrentInformation()
{
	string accName= atm.getAccName();
	wxString currentName = wxString::Format("Account Name: %s", accName);
	printName->SetLabel(currentName);
	
	string accBday = atm.getAccBday();
	wxString currentBday = wxString::Format("Account Birthdate: %s", accBday);
	printBday->SetLabel(currentBday);

	string accContact = atm.getAccContact();
	wxString currentContact = wxString::Format("Account Contact: %s", accContact);
	printContact->SetLabel(currentContact);

	Layout();
}

void MainFrame::UpdateInformation()
{
	if (!changeNameInput->IsEmpty()) {
		wxString newAccName = changeNameInput->GetValue();
		newAccName = newAccName.Trim();

		atm.changeAccName(newAccName.ToStdString());
		changeNameInput->Clear();
	}

	long month, day, year;
	if ((changeMonthInput->GetValue().ToLong(&month) && changeDayInput->GetValue().ToLong(&day) &&
		changeYearInput->GetValue().ToLong(&year))) {
		wxString newBday = formatValidate.FormatBday(month, day, year);
		atm.changeAccBday(newBday.ToStdString());

		changeMonthInput->Clear();
		changeDayInput->Clear();
		changeYearInput->Clear();
	}

	wxString contact = changeContactInput->GetValue();
	if (contact.Length() < 13) {
		changeContactInput->SetBackgroundColour(*wxRED);
		changeContactInput->Clear();
		return;
	}
	else {
		string newAccContact = contact.ToStdString();
		atm.changeAccContact(newAccContact);
		changeContactInput->Clear();
	}
}

void MainFrame::OnCancelChangeAccInfoClicked(wxCommandEvent& evt)
{
	changeInfoPanel->Hide();

	changeNameInput->Clear();

	changeMonthInput->Clear();
	changeMonthInput->SetBackgroundColour(wxColor(248, 247, 255));

	changeDayInput->Clear();
	changeDayInput->SetBackgroundColour(wxColor(248, 247, 255));

	changeYearInput->Clear();
	changeYearInput->SetBackgroundColour(wxColor(248, 247, 255));

	changeContactInput->Clear();
	changeContactInput->SetBackgroundColour(wxColor(248, 247, 255));

	mainPanel->Show();
	Layout();
}

void MainFrame::OnChangeBirthMonth(wxCommandEvent& evt) 
{
	formatValidate.OnValidateMonth(changeMonthInput, changeDayInput, changeYearInput);
}

void MainFrame::OnChangeMonthFocusLost(wxFocusEvent& evt)
{
	formatValidate.FormatMonthOnFocusLost(changeMonthInput);
	evt.Skip();
}

void MainFrame::OnChangeBirthDay(wxCommandEvent& evt)
{
	formatValidate.OnValidateDay(changeMonthInput, changeDayInput, changeYearInput);
}

void MainFrame::OnChangeDayFocusLost(wxFocusEvent& evt)
{
	formatValidate.FormatDayOnFocusLost(changeDayInput);
	evt.Skip();
}

void MainFrame::OnChangeBirthYear(wxCommandEvent& evt)
{
	formatValidate.OnValidateYear(changeMonthInput, changeDayInput, changeYearInput);
}

void MainFrame::OnChangeYearFocusLost(wxFocusEvent& evt)
{
	formatValidate.FormatYearOnFocusLost(changeYearInput);
	evt.Skip();
}

void MainFrame::OnChangeContact(wxCommandEvent& evt)
{
	formatValidate.OnValidateContact(changeContactInput);
}

void MainFrame::OnConfirmInfoChangeClicked(wxCommandEvent& evt)
{
	UpdateInformation();
	PrintCurrentInformation();
}

void MainFrame::OnChangeAccPinClicked(wxCommandEvent& evt)
{
	accountPanel->Hide();
	changePinPanel->Show();
	Layout();
}

void MainFrame::UpdatePin()
{
	wxString currentPinL = inputCurrentPin->GetValue();
	wxString newPinL = inputNewPin->GetValue();
	wxString confirmPinL = inputConfirmNewPin->GetValue();

	if (inputCurrentPin->IsEmpty() && inputNewPin->IsEmpty() && inputConfirmNewPin->IsEmpty())
	{
		wxLogMessage("Incomplete Input");
	}

	if (newPinL.length() < 4 && confirmPinL.length() < 4) {
		wxLogMessage("Invalid Pin");
		return;
	}

	else if(!inputCurrentPin->IsEmpty() && !inputNewPin->IsEmpty() && !inputConfirmNewPin->IsEmpty()){
		string currentPin = inputCurrentPin->GetValue().ToStdString();
		string newPin = inputNewPin->GetValue().ToStdString();
		string confirmPin = inputConfirmNewPin->GetValue().ToStdString();

		int confirm = atm.changeAccPin(currentPin, newPin, confirmPin);

		if (confirm == 1) {
			changePinPanel->Hide();

			inputCurrentPin->Clear();
			inputCurrentPin->SetBackgroundColour(wxColor(248, 247, 255));

			inputNewPin->Clear();
			inputNewPin->SetBackgroundColour(wxColor(248, 247, 255));

			inputConfirmNewPin->Clear();
			inputConfirmNewPin->SetBackgroundColour(wxColor(248, 247, 255));

			mainPanel->Show();
			Layout();
		}

		else if (confirm == 0 && currentPinL.length() < 4) {
			inputCurrentPin->SetBackgroundColour(*wxRED);
			inputCurrentPin->Clear();
			inputCurrentPin->Refresh();
		}

		else if (confirm == -1 && newPinL.length() < 4 && confirmPinL.length() < 4) {
			inputConfirmNewPin->SetBackgroundColour(*wxRED);
			inputConfirmNewPin->Clear();
			inputConfirmNewPin->Refresh();

			inputNewPin->SetBackgroundColour(*wxRED);
			inputNewPin->Clear();
			inputNewPin->Refresh();
		}
	}
}

void MainFrame::OnCancelChangePinClicked(wxCommandEvent& evt)
{
	changePinPanel->Hide();

	inputCurrentPin->Clear();
	inputCurrentPin->SetBackgroundColour(wxColor(248, 247, 255));

	inputNewPin->Clear();
	inputNewPin->SetBackgroundColour(wxColor(248, 247, 255));

	inputConfirmNewPin->Clear();
	inputConfirmNewPin->SetBackgroundColour(wxColor(248, 247, 255));

	mainPanel->Show();
	Layout();
}


void MainFrame::OnInputCurrentPin(wxCommandEvent& evt)
{
	formatValidate.OnValidatePin(inputCurrentPin);
}

void MainFrame::OnInputNewPin(wxCommandEvent& evt)
{
	formatValidate.OnValidatePin(inputNewPin);
}

void MainFrame::OnInputConfirmPin(wxCommandEvent& evt)
{
	formatValidate.OnValidatePin(inputConfirmNewPin);
}

void MainFrame::OnConfirmPinChangeClicked(wxCommandEvent& evt)
{
	UpdatePin();
}

void MainFrame::OnCancelMainMenuClicked(wxCommandEvent& evt)
{
	mainPanel->Hide();
	takeCard->Show();
	wxSound getCardSound("sfx/getCard.wav");
	getCardSound.Play();
	Delay(8000);

	takeCard->Hide();
	exitAtm->Show();
	wxSound exitSound("sfx/exit.wav");
	exitSound.Play();
	
	Delay(3000);


	exitAtm->Hide();
	noOperationPanel->Show();
	
	Layout();
}

void MainFrame::Delay(int milliseconds) {
	wxLongLong start = wxGetLocalTimeMillis();
	while ((wxGetLocalTimeMillis() - start).GetValue() < milliseconds) {
		wxYield();
	}
}


void MainFrame::ProcessTransaction(wxStaticBitmap* panel) {
	panel->Hide();
	processPanel->Show();
	//plpay sound coressponding to transact
	if (panel == depositPanel || panel == fundTransferPanel) {
		wxSound insertMoneySound("sfx/deposit.wav");
		insertMoneySound.Play();
		Delay(4000);
	}

	if (panel == withdrawPanel) {
		wxSound withdrawSound("sfx/withdraw.wav");
		withdrawSound.Play();
		Delay(6000);
	}
	
	
	OnProcess(panel);
	
}

void MainFrame::OnProcess(wxStaticBitmap* panel) {
	processPanel->Hide();

	if (panel == depositPanel) {
		depositSuccess->Show();
	}

	if (panel == withdrawPanel) {
		withdrawSuccess->Show();
	}

	if (panel == fundTransferPanel) {
		transferSuccess->Show();
	}

	Delay(3000);
	OnSuccess(panel);
}

void MainFrame::OnSuccess(wxStaticBitmap* panel) {

	depositSuccess->Hide();
	withdrawSuccess->Hide();
	transferSuccess->Hide();
	mainPanel->Show();

	Layout();
}



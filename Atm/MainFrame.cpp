#include "MainFrame.h"
#include <wx/wx.h>
#include "Account.h"
#include <string>


MainFrame::MainFrame(const wxString& title) : wxFrame(nullptr, wxID_ANY, title) 
{
	CreateControls();
	BindEventHandlers();
	atm.loadAcc();
}

void MainFrame::CreateControls()
{

	wxPanel* panel = new wxPanel(this);

	//Register Account
	registerPanel = new wxPanel(panel, wxID_ANY, wxDefaultPosition, wxSize(800, 600));
	registerName = new wxTextCtrl(registerPanel, wxID_ANY, wxEmptyString, wxPoint(320, 100), wxSize(200, 40));
	registerName->SetHint("Enter Name");
	registerBday = new wxTextCtrl(registerPanel, wxID_ANY, wxEmptyString, wxPoint(320, 150), wxSize(200, 40));
	registerBday->SetHint("Enter Birthdate");
	registerContact = new wxTextCtrl(registerPanel, wxID_ANY, wxEmptyString, wxPoint(320, 200), wxSize(200, 40));
	registerContact->SetHint("Enter Contact Number");
	registerPin = new wxTextCtrl(registerPanel, wxID_ANY, wxEmptyString, wxPoint(320, 250), wxSize(200, 40), wxTE_PASSWORD);
	registerPin->SetHint("Enter Pin");
	registerAccButton = new wxButton(registerPanel, wxID_ANY, "Confirm", wxPoint(320, 300), wxSize(120, 35));

	//Enter Account
	enterAccountPanel = new wxPanel(panel, wxID_ANY, wxDefaultPosition, wxSize(800, 600));
	enterAccNum = new wxTextCtrl(enterAccountPanel, wxID_ANY, wxEmptyString, wxPoint(320, 200), wxSize(200, 40));
	enterAccNum->SetHint("Enter Account Number");
	enterPin = new wxTextCtrl(enterAccountPanel, wxID_ANY, wxEmptyString, wxPoint(320, 250), wxSize(200, 40), wxTE_PASSWORD);
	enterPin->SetHint("Enter Pin");
	enterAccButton = new wxButton(enterAccountPanel, wxID_ANY, "Confirm", wxPoint(320, 300), wxSize(120, 35));
	enterAccountPanel->Hide();

	//Main Menu
	mainPanel = new wxPanel(panel, wxID_ANY, wxDefaultPosition, wxSize(800, 600));
	balanceButton = new wxButton(mainPanel, wxID_ANY, "BALANCE INQUIRY", wxPoint(150, 100), wxSize(120, 35));
	depositButton = new wxButton(mainPanel, wxID_ANY, "DEPOSIT", wxPoint(150, 150), wxSize(120, 35));
	fundTransferButton = new wxButton(mainPanel, wxID_ANY, "FUND TRANSFER", wxPoint(150, 200), wxSize(120, 35));
	withdrawButton = new wxButton(mainPanel, wxID_ANY, "WITHDRAW", wxPoint(350, 100), wxSize(120, 35));
	accountSettingsButton = new wxButton(mainPanel, wxID_ANY, "ACCOUNT", wxPoint(350, 150), wxSize(120, 35));
	cancelMainMenuButton = new wxButton(mainPanel, wxID_ANY, "CANCEL", wxPoint(350, 200), wxSize(120, 35));
	mainPanel->Hide();

	//Balance Inquiry
	balancePanel = new wxPanel(panel, wxID_ANY, wxDefaultPosition, wxSize(800, 600));
	printBalance = new wxStaticText(balancePanel, wxID_ANY, wxEmptyString, wxPoint(250, 250), wxSize(200, 40));
	returnFromBalanceButton = new wxButton(balancePanel, wxID_ANY, "Return", wxPoint(150, 100), wxSize(120, 35));
	balancePanel->Hide();

	//Deposit
	depositPanel = new wxPanel(panel, wxID_ANY, wxDefaultPosition, wxSize(800,600));
	inputDeposit = new wxTextCtrl(depositPanel, wxID_ANY, wxEmptyString, wxPoint(320, 250), wxSize(200, 40));
	inputDeposit->SetHint("0.00");
	confirmDeposit = new wxButton(depositPanel, wxID_ANY, "Confirm", wxPoint(320, 300), wxSize(120, 35));
	depositPanel->Hide();

	//Withdraw
	withdrawPanel = new wxPanel(panel, wxID_ANY, wxDefaultPosition, wxSize(800, 600));
	inputWithdraw = new wxTextCtrl(withdrawPanel, wxID_ANY, wxEmptyString, wxPoint(320, 250), wxSize(200, 40));
	inputWithdraw->SetHint("0.00");
	confirmWithdraw = new wxButton(withdrawPanel, wxID_ANY, "Wtihdraw", wxPoint(150, 100), wxSize(120, 35));
	withdrawPanel->Hide();

	//Fund Transfer
	fundTransferPanel = new wxPanel(panel, wxID_ANY, wxDefaultPosition, wxSize(800, 600));
	confirmFundTransferButton = new wxButton(fundTransferPanel, wxID_ANY, "Confirm Fund Transfer", wxPoint(250, 200), wxSize(120, 35));
	inputAccTransfer = new wxTextCtrl(fundTransferPanel, wxID_ANY, wxEmptyString, wxPoint(250, 100), wxSize(200, 40));
	inputAccTransfer->SetHint("Input Account Number of Recipient");
	inputAmountTransfer = new wxTextCtrl(fundTransferPanel, wxID_ANY, wxEmptyString, wxPoint(250, 150), wxSize(200, 40));
	inputAmountTransfer->SetHint("Input Amount to Transfer");
	fundTransferPanel->Hide();

	//Account Settings
	accountPanel = new wxPanel(panel, wxID_ANY, wxDefaultPosition, wxSize(800, 600));
	changeAccInfoButton = new wxButton(accountPanel, wxID_ANY, "Change Information", wxPoint(100, 300), wxSize(120, 35));
	changeAccPinButton = new wxButton(accountPanel, wxID_ANY, "Change Pin", wxPoint(200, 300), wxSize(120, 35));
	accountPanel->Hide();

	//Change Account Information
	changeInfoPanel  = new wxPanel(panel, wxID_ANY, wxDefaultPosition, wxSize(800, 600));

	printName = new wxStaticText(changeInfoPanel, wxID_ANY, wxEmptyString, wxPoint(250, 100), wxSize(200, 40));
	changeNameInput = new wxTextCtrl(changeInfoPanel, wxID_ANY, wxEmptyString, wxPoint(250, 150), wxSize(200, 40));
	changeNameInput->SetHint("Enter New Name");

	printBday = new wxStaticText(changeInfoPanel, wxID_ANY, wxEmptyString, wxPoint(250, 200), wxSize(200, 40));
	changeBdayInput = new wxTextCtrl(changeInfoPanel, wxID_ANY, wxEmptyString, wxPoint(250, 250), wxSize(200, 40));
	changeBdayInput->SetHint("Enter New Birthdate");

	printContact = new wxStaticText(changeInfoPanel, wxID_ANY, wxEmptyString, wxPoint(250, 300), wxSize(200, 40));
	changeContactInput = new wxTextCtrl(changeInfoPanel, wxID_ANY, wxEmptyString, wxPoint(250, 350), wxSize(200, 40));
	changeContactInput->SetHint("Enter New Contact Number");

	confirmInfoChangeButton = new wxButton(changeInfoPanel, wxID_ANY, "Confirm Changed Information", wxPoint(250, 400), wxSize(170, 35));

	changeInfoPanel->Hide();

	//Change Pin
	changePinPanel = new wxPanel(panel, wxID_ANY, wxDefaultPosition, wxSize(800, 600));
	confirmPinChangeButton = new wxButton(changePinPanel, wxID_ANY, "Confirm Change Pin", wxPoint(250, 250), wxSize(120, 35));

	inputCurrentPin = new wxTextCtrl(changePinPanel, wxID_ANY, wxEmptyString, wxPoint(250, 100), wxSize(200, 40));
	inputCurrentPin->SetHint("Input Current Pin");

	inputNewPin = new wxTextCtrl(changePinPanel, wxID_ANY, wxEmptyString, wxPoint(250, 150), wxSize(200, 40));
	inputNewPin->SetHint("Input New Pin");

	inputConfirmNewPin = new wxTextCtrl(changePinPanel, wxID_ANY, wxEmptyString, wxPoint(250, 200), wxSize(200, 40));
	inputConfirmNewPin->SetHint("Confirm New Pin");

	changePinPanel->Hide();

}

void MainFrame::BindEventHandlers()
{
	this->Bind(wxEVT_CLOSE_WINDOW, &MainFrame::OnWindowClosed, this);

	registerAccButton->Bind(wxEVT_BUTTON, &MainFrame::OnRegisterButtonClicked, this);
	enterAccButton->Bind(wxEVT_BUTTON, &MainFrame::OnEnterAccButtonClicked, this);

	balanceButton->Bind(wxEVT_BUTTON, &MainFrame::OnBalanceButtonClicked, this);
	returnFromBalanceButton->Bind(wxEVT_BUTTON, &MainFrame::ReturnFromBalanceToMain, this);

	depositButton->Bind(wxEVT_BUTTON, &MainFrame::OnDepositButtonClicked, this);
	confirmDeposit->Bind(wxEVT_BUTTON, &MainFrame::OnConfirmDepositClicked, this);

	withdrawButton->Bind(wxEVT_BUTTON, &MainFrame::OnWithdrawButtonClicked, this);
	confirmWithdraw->Bind(wxEVT_BUTTON, &MainFrame::OnConfirmWithdrawClicked, this);

	fundTransferButton->Bind(wxEVT_BUTTON, &MainFrame::OnFundTransferButtonClicked, this);
	confirmFundTransferButton->Bind(wxEVT_BUTTON, &MainFrame::OnConfirmFundTransferClicked, this);

	accountSettingsButton->Bind(wxEVT_BUTTON, &MainFrame::OnAccountSettingsClicked, this);

	changeAccInfoButton->Bind(wxEVT_BUTTON, &MainFrame::OnChangeAccInfoClicked, this);
	confirmInfoChangeButton->Bind(wxEVT_BUTTON, &MainFrame::OnConfirmInfoChangeClicked, this);
	
	changeAccPinButton->Bind(wxEVT_BUTTON, &MainFrame::OnChangeAccPinClicked, this);
	confirmPinChangeButton->Bind(wxEVT_BUTTON, &MainFrame::OnConfirmPinChangeClicked, this);

	//cancelMainButton->Bind(wxEVT_BUTTON, &MainFrame::OnCancelMainMenuClicked, this);
	
}

void MainFrame::OnWindowClosed(wxCloseEvent& evt)
{
	atm.storeAcc();
	evt.Skip();
}

void MainFrame::AddInformation()
{
	Account d;

	d.accNum = std::to_string(atm.createAccNumber());
	d.name = registerName->GetValue().ToStdString();
	d.bday = registerBday->GetValue().ToStdString();
	d.contact = registerContact->GetValue().ToStdString();
	d.pinCode = registerPin->GetValue().ToStdString();

	if (registerName->IsEmpty() || registerBday->IsEmpty() || registerContact->IsEmpty() || registerPin->IsEmpty()) {
		wxLogMessage("Complete Input Information");
		return;
	}
	else {
		atm.registerAcc(d);
		ShowAccountInfo(d);

		registerPanel->Hide();

		registerName->Clear();
		registerBday->Clear();
		registerContact->Clear();
		registerPin->Clear();

		enterAccountPanel->Show();
		Layout();
	}
}

void MainFrame::OnRegisterButtonClicked(wxCommandEvent& evt)
{
	AddInformation();
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
	}

	else if(enter == -1){
		wxLogMessage("Account Not Found");
	}

}

void MainFrame::OnEnterAccButtonClicked(wxCommandEvent& evt)
{
	EnterAccount();
}

void MainFrame::BalanceInquiry()
{
	double balance = atm.getBalance();
	wxString currentBalance = wxString::Format("Your Current Balance: %.2f", balance);
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

void MainFrame::AddMoney()
{
	double amount = wxAtof(inputDeposit->GetValue());

	if (amount >= 0) {
		atm.deposit(amount);
		wxLogMessage("Deposit Successful");
		inputDeposit->Clear();
	}
	else {
		wxLogMessage("Invalid Amount");
	}

}

void MainFrame::OnConfirmDepositClicked(wxCommandEvent& evt)
{
	AddMoney();
	depositPanel->Hide();
	mainPanel->Show();
}

void MainFrame::OnWithdrawButtonClicked(wxCommandEvent& evt)
{
	mainPanel->Hide();
	withdrawPanel->Show();
	Layout();
}

void MainFrame::WithdrawMoney()
{
	double amount = wxAtof(inputWithdraw->GetValue());
	double currentBalance = atm.getBalance();

	if (amount <= 0 || amount > currentBalance) {
		wxLogMessage("Invalid Amount");
	}
	else {
		if (amount <= currentBalance) {
			atm.withdraw(amount);
			wxLogMessage("Withdraw Successful");
			inputWithdraw->Clear();
		}
	}

}

void MainFrame::OnConfirmWithdrawClicked(wxCommandEvent& evt)
{
	WithdrawMoney();
	withdrawPanel->Hide();
	mainPanel->Show();
	Layout();
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
		wxLogMessage("Incomplete Input");
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
		}

		else if (successfulTransfer == -2) {
			wxLogMessage("Invalid Amount");
		}

		else if (successfulTransfer == 1) {
			fundTransferPanel->Hide();
			inputAccTransfer->Clear();
			inputAmountTransfer->Clear();
			mainPanel->Show();
			Layout();
		}
	}
}

void MainFrame::OnConfirmFundTransferClicked(wxCommandEvent& evt)
{
	TransferMoney();
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
		string newAccName = changeNameInput->GetValue().ToStdString();
		atm.changeAccName(newAccName);
		changeNameInput->Clear();
	}

	if (!changeBdayInput->IsEmpty()) {
		string newAccBday = changeBdayInput->GetValue().ToStdString();
		atm.changeAccBday(newAccBday);
		changeBdayInput->Clear();
	}

	if (!changeContactInput->IsEmpty()) {
		string newAccContact = changeContactInput->GetValue().ToStdString();
		atm.changeAccContact(newAccContact);
		changeContactInput->Clear();
	}

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
	if (inputCurrentPin->IsEmpty() && inputNewPin->IsEmpty() && inputConfirmNewPin->IsEmpty())
	{
		wxLogMessage("Incomplete Input");
	}
	else if(!inputCurrentPin->IsEmpty() && !inputNewPin->IsEmpty() && !inputConfirmNewPin->IsEmpty()){
		string currentPin = inputCurrentPin->GetValue().ToStdString();
		string newPin = inputNewPin->GetValue().ToStdString();
		string confirmPin = inputConfirmNewPin->GetValue().ToStdString();

		int confirm = atm.changeAccPin(currentPin, newPin, confirmPin);

		if (confirm == 1) {
			changePinPanel->Hide();
			inputCurrentPin->Clear();
			inputNewPin->Clear();
			inputConfirmNewPin->Clear();
			mainPanel->Show();
			Layout();
		}

		else if (confirm == 0) {
			wxLogMessage("Input Pin does not match Current Pin");
		}

		else if (confirm == -1) {
			wxLogMessage("New Pin does not match Confirm Pin");
		}
	}
}

void MainFrame::OnConfirmPinChangeClicked(wxCommandEvent& evt)
{
	UpdatePin();
}

void MainFrame::OnCancelMainMenuClicked(wxCommandEvent& evt)
{
	wxLogMessage("wag na kupal");
}
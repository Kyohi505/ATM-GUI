#include "MainFrame.h"
#include <wx/wx.h>
#include "Account.h"
#include <string>
#include <ctime>
#include <wx/valtext.h>


MainFrame::MainFrame(const wxString& title) : wxFrame(nullptr, wxID_ANY, title) 
{
	CreateControls();
	BindEventHandlers();
	atm.loadAcc();
}

void MainFrame::CreateControls()
{

	wxPanel* panel = new wxPanel(this);

	noOperationPanel = new wxPanel(panel, wxID_ANY, wxDefaultPosition, wxSize(800, 600));

	//Register Account
	registerPanel = new wxPanel(panel, wxID_ANY, wxDefaultPosition, wxSize(800, 600));

	wxString allowedChars = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz ";
	wxTextValidator nameValidator(wxFILTER_INCLUDE_CHAR_LIST);
	nameValidator.SetCharIncludes(allowedChars);

	registerName = new wxTextCtrl(registerPanel, wxID_ANY, wxEmptyString, wxPoint(320, 100), wxSize(200, 40), 0, nameValidator);
	registerName->SetHint("Enter Name");

	registerBirthMonth = new wxTextCtrl(registerPanel, wxID_ANY, wxEmptyString, wxPoint(320, 150), wxSize(30, 40), 0, wxTextValidator(wxFILTER_NUMERIC));
	registerBirthMonth->SetHint("MM");
	registerBirthMonth->SetMaxLength(2);

	registerBirthDay = new wxTextCtrl(registerPanel, wxID_ANY, wxEmptyString, wxPoint(360, 150), wxSize(30, 40), 0, wxTextValidator(wxFILTER_NUMERIC));
	registerBirthDay->SetHint("DD");
	registerBirthDay->SetMaxLength(2);

	registerBirthYear = new wxTextCtrl(registerPanel, wxID_ANY, wxEmptyString, wxPoint(400, 150), wxSize(50, 40), 0, wxTextValidator(wxFILTER_NUMERIC));
	registerBirthYear->SetHint("YYYY");
	registerBirthYear->SetMaxLength(4);

	registerContact = new wxTextCtrl(registerPanel, wxID_ANY, wxEmptyString, wxPoint(320, 200), wxSize(200, 40), 0, wxTextValidator(wxFILTER_NUMERIC));
	registerContact->SetHint("Enter Contact Number");
	registerContact->SetMaxLength(13);

	registerPin = new wxTextCtrl(registerPanel, wxID_ANY, wxEmptyString, wxPoint(320, 250), wxSize(200, 40), wxTE_PASSWORD, wxTextValidator(wxFILTER_NUMERIC));
	registerPin->SetHint("Enter Pin");
	registerPin->SetMaxLength(6);
	registerAccButton = new wxButton(registerPanel, wxID_ANY, "Confirm", wxPoint(320, 300), wxSize(120, 35));
	cancelRegisterButton = new wxButton(registerPanel, wxID_ANY, "Cancel", wxPoint(450, 300), wxSize(120, 35));
	registerPanel->Hide();

	//Enter Account
	enterAccountPanel = new wxPanel(panel, wxID_ANY, wxDefaultPosition, wxSize(800, 600));
	enterAccNum = new wxTextCtrl(enterAccountPanel, wxID_ANY, wxEmptyString, wxPoint(320, 200), wxSize(200, 40), 0, wxTextValidator(wxFILTER_NUMERIC));
	enterAccNum->SetHint("Enter Account Number");
	enterAccNum->SetMaxLength(5);

	enterPin = new wxTextCtrl(enterAccountPanel, wxID_ANY, wxEmptyString, wxPoint(320, 250), wxSize(200, 40), wxTE_PASSWORD, wxTextValidator(wxFILTER_NUMERIC));
	enterPin->SetHint("Enter Pin");
	enterPin->SetMaxLength(6);

	enterAccButton = new wxButton(enterAccountPanel, wxID_ANY, "Confirm", wxPoint(320, 300), wxSize(120, 35));
	cancelEnterAccountButton = new wxButton(enterAccountPanel, wxID_ANY, "Cancel", wxPoint(450, 300), wxSize(120, 35));
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
	inputDeposit = new wxTextCtrl(depositPanel, wxID_ANY, wxEmptyString, wxPoint(320, 250), wxSize(200, 40), 0, wxTextValidator(wxFILTER_NUMERIC));
	inputDeposit->SetHint("0.00");
	confirmDeposit = new wxButton(depositPanel, wxID_ANY, "Confirm", wxPoint(300, 300), wxSize(120, 35));
	cancelDepositButton = new wxButton(depositPanel, wxID_ANY, "Cancel", wxPoint(400, 300), wxSize(120, 35));
	depositPanel->Hide();

	//Withdraw
	withdrawPanel = new wxPanel(panel, wxID_ANY, wxDefaultPosition, wxSize(800, 600));
	inputWithdraw = new wxTextCtrl(withdrawPanel, wxID_ANY, wxEmptyString, wxPoint(320, 250), wxSize(200, 40), 0, wxTextValidator(wxFILTER_NUMERIC));
	inputWithdraw->SetHint("0.00");
	confirmWithdraw = new wxButton(withdrawPanel, wxID_ANY, "Wtihdraw", wxPoint(150, 100), wxSize(120, 35));
	cancelWithdrawButton = new wxButton(withdrawPanel, wxID_ANY, "Cancel", wxPoint(250, 100), wxSize(120, 35));
	withdrawPanel->Hide();

	//Fund Transfer
	fundTransferPanel = new wxPanel(panel, wxID_ANY, wxDefaultPosition, wxSize(800, 600));
	inputAccTransfer = new wxTextCtrl(fundTransferPanel, wxID_ANY, wxEmptyString, wxPoint(250, 100), wxSize(200, 40), 0, wxTextValidator(wxFILTER_NUMERIC));
	inputAccTransfer->SetHint("Input Account Number of Recipient");
	inputAmountTransfer = new wxTextCtrl(fundTransferPanel, wxID_ANY, wxEmptyString, wxPoint(250, 150), wxSize(200, 40), 0, wxTextValidator(wxFILTER_NUMERIC));
	inputAmountTransfer->SetHint("Input Amount to Transfer");
	confirmFundTransferButton = new wxButton(fundTransferPanel, wxID_ANY, "Confirm Fund Transfer", wxPoint(250, 200), wxSize(120, 35));
	cancelFundTransferButton = new wxButton(fundTransferPanel, wxID_ANY, "Cancel", wxPoint(400, 200), wxSize(120, 35));
	fundTransferPanel->Hide();

	//Account Settings
	accountPanel = new wxPanel(panel, wxID_ANY, wxDefaultPosition, wxSize(800, 600));
	changeAccInfoButton = new wxButton(accountPanel, wxID_ANY, "Change Information", wxPoint(100, 300), wxSize(120, 35));
	changeAccPinButton = new wxButton(accountPanel, wxID_ANY, "Change Pin", wxPoint(200, 300), wxSize(120, 35));
	cancelAccountSettingsButton = new wxButton(accountPanel, wxID_ANY, "Cancel", wxPoint(350, 350), wxSize(120, 35));
	accountPanel->Hide();

	//Change Account Information
	changeInfoPanel  = new wxPanel(panel, wxID_ANY, wxDefaultPosition, wxSize(800, 600));

	printName = new wxStaticText(changeInfoPanel, wxID_ANY, wxEmptyString, wxPoint(250, 100), wxSize(200, 40));
	changeNameInput = new wxTextCtrl(changeInfoPanel, wxID_ANY, wxEmptyString, wxPoint(250, 150), wxSize(200, 40), 0, nameValidator);
	changeNameInput->SetHint("Enter New Name");

	printBday = new wxStaticText(changeInfoPanel, wxID_ANY, wxEmptyString, wxPoint(250, 200), wxSize(200, 40));
	changeBdayInput = new wxTextCtrl(changeInfoPanel, wxID_ANY, wxEmptyString, wxPoint(250, 250), wxSize(200, 40));
	changeBdayInput->SetHint("Enter New Birthdate");

	printContact = new wxStaticText(changeInfoPanel, wxID_ANY, wxEmptyString, wxPoint(250, 300), wxSize(200, 40));
	changeContactInput = new wxTextCtrl(changeInfoPanel, wxID_ANY, wxEmptyString, wxPoint(250, 350), wxSize(200, 40));
	changeContactInput->SetHint("Enter New Contact Number");

	confirmInfoChangeButton = new wxButton(changeInfoPanel, wxID_ANY, "Confirm Changed Information", wxPoint(250, 400), wxSize(170, 35));
	cancelChangeAccInfoButton = new wxButton(changeInfoPanel, wxID_ANY, "Cancel", wxPoint(400, 400), wxSize(170, 35));

	changeInfoPanel->Hide();

	//Change Pin
	changePinPanel = new wxPanel(panel, wxID_ANY, wxDefaultPosition, wxSize(800, 600));

	inputCurrentPin = new wxTextCtrl(changePinPanel, wxID_ANY, wxEmptyString, wxPoint(250, 100), wxSize(200, 40), wxTE_PASSWORD, wxTextValidator(wxFILTER_NUMERIC));
	inputCurrentPin->SetHint("Input Current Pin");

	inputNewPin = new wxTextCtrl(changePinPanel, wxID_ANY, wxEmptyString, wxPoint(250, 150), wxSize(200, 40), wxTE_PASSWORD, wxTextValidator(wxFILTER_NUMERIC));
	inputNewPin->SetHint("Input New Pin");

	inputConfirmNewPin = new wxTextCtrl(changePinPanel, wxID_ANY, wxEmptyString, wxPoint(250, 200), wxSize(200, 40), wxTE_PASSWORD, wxTextValidator(wxFILTER_NUMERIC));
	inputConfirmNewPin->SetHint("Confirm New Pin");

	confirmPinChangeButton = new wxButton(changePinPanel, wxID_ANY, "Confirm Change Pin", wxPoint(250, 250), wxSize(120, 35));
	cancelChangePinButton = new wxButton(changePinPanel, wxID_ANY, "Cancel", wxPoint(400, 250), wxSize(120, 35));

	changePinPanel->Hide();

}

void MainFrame::BindEventHandlers()
{
	this->Bind(wxEVT_CLOSE_WINDOW, &MainFrame::OnWindowClosed, this);

	noOperationPanel->Bind(wxEVT_LEFT_DOWN, &MainFrame::OnScreenClicked, this);

	registerAccButton->Bind(wxEVT_BUTTON, &MainFrame::OnRegisterButtonClicked, this);
	cancelRegisterButton->Bind(wxEVT_BUTTON, &MainFrame::OnCancelRegisterClicked, this);
	
	registerName->Bind(wxEVT_TEXT, &MainFrame::NameInput, this);

	registerBirthMonth->Bind(wxEVT_TEXT, &MainFrame::OnInputMonth, this);
	registerBirthMonth->Bind(wxEVT_KILL_FOCUS, &MainFrame::OnMonthFocusLost, this);
	registerBirthMonth->Bind(wxEVT_CHAR, &MainFrame::OnlyNumInput, this);

	registerBirthDay->Bind(wxEVT_TEXT, &MainFrame::OnInputDay, this);
	registerBirthDay->Bind(wxEVT_KILL_FOCUS, &MainFrame::OnDayFocusLost, this);
	registerBirthDay->Bind(wxEVT_CHAR, &MainFrame::OnlyNumInput, this);

	registerBirthYear->Bind(wxEVT_TEXT, &MainFrame::OnInputYear, this);
	registerBirthYear->Bind(wxEVT_CHAR, &MainFrame::OnlyNumInput, this);

	registerContact->Bind(wxEVT_CHAR, &MainFrame::OnlyNumInput, this);
	registerContact->Bind(wxEVT_TEXT, &MainFrame::OnInputContact, this);
	registerPin->Bind(wxEVT_CHAR, &MainFrame::OnlyNumInput, this);

	enterAccButton->Bind(wxEVT_BUTTON, &MainFrame::OnEnterAccButtonClicked, this);
	cancelEnterAccountButton->Bind(wxEVT_BUTTON, &MainFrame::OnCancelEnterAccClicked, this);
	enterAccNum->Bind(wxEVT_CHAR, &MainFrame::OnlyNumInput, this);
	enterPin->Bind(wxEVT_CHAR, &MainFrame::OnlyNumInput, this);

	cancelMainMenuButton->Bind(wxEVT_BUTTON, &MainFrame::OnCancelMainMenuClicked, this);

	balanceButton->Bind(wxEVT_BUTTON, &MainFrame::OnBalanceButtonClicked, this);
	returnFromBalanceButton->Bind(wxEVT_BUTTON, &MainFrame::ReturnFromBalanceToMain, this);

	depositButton->Bind(wxEVT_BUTTON, &MainFrame::OnDepositButtonClicked, this);
	confirmDeposit->Bind(wxEVT_BUTTON, &MainFrame::OnConfirmDepositClicked, this);
	cancelDepositButton->Bind(wxEVT_BUTTON, &MainFrame::OnCancelDepositClicked, this);
	inputDeposit->Bind(wxEVT_CHAR, &MainFrame::OnlyNumInput, this);

	withdrawButton->Bind(wxEVT_BUTTON, &MainFrame::OnWithdrawButtonClicked, this);
	confirmWithdraw->Bind(wxEVT_BUTTON, &MainFrame::OnConfirmWithdrawClicked, this);
	cancelWithdrawButton->Bind(wxEVT_BUTTON, &MainFrame::OnCancelWithdrawClicked, this);
	inputWithdraw->Bind(wxEVT_CHAR, &MainFrame::OnlyNumInput, this);

	fundTransferButton->Bind(wxEVT_BUTTON, &MainFrame::OnFundTransferButtonClicked, this);
	confirmFundTransferButton->Bind(wxEVT_BUTTON, &MainFrame::OnConfirmFundTransferClicked, this);
	cancelFundTransferButton->Bind(wxEVT_BUTTON, &MainFrame::OnCancelFundTransferClicked, this);
	inputAccTransfer->Bind(wxEVT_CHAR, &MainFrame::OnlyNumInput, this);
	inputAmountTransfer->Bind(wxEVT_CHAR, &MainFrame::OnlyNumInput, this);

	accountSettingsButton->Bind(wxEVT_BUTTON, &MainFrame::OnAccountSettingsClicked, this);
	cancelAccountSettingsButton->Bind(wxEVT_BUTTON, &MainFrame::OnCancelAccSettingsClicked, this);

	changeAccInfoButton->Bind(wxEVT_BUTTON, &MainFrame::OnChangeAccInfoClicked, this);
	confirmInfoChangeButton->Bind(wxEVT_BUTTON, &MainFrame::OnConfirmInfoChangeClicked, this);
	cancelChangeAccInfoButton->Bind(wxEVT_BUTTON, &MainFrame::OnCancelChangeAccInfoClicked, this);
	
	changeBdayInput->Bind(wxEVT_CHAR, &MainFrame::OnlyNumInput, this);
	changeContactInput->Bind(wxEVT_CHAR, &MainFrame::OnlyNumInput, this);

	changeAccPinButton->Bind(wxEVT_BUTTON, &MainFrame::OnChangeAccPinClicked, this);
	confirmPinChangeButton->Bind(wxEVT_BUTTON, &MainFrame::OnConfirmPinChangeClicked, this);
	cancelChangePinButton->Bind(wxEVT_BUTTON, &MainFrame::OnCancelChangePinClicked, this);
	inputCurrentPin->Bind(wxEVT_CHAR, &MainFrame::OnlyNumInput, this);
	inputNewPin->Bind(wxEVT_CHAR, &MainFrame::OnlyNumInput, this);
	inputConfirmNewPin->Bind(wxEVT_CHAR, &MainFrame::OnlyNumInput, this);

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

void MainFrame::AddInformation()
{
	Account d;

	d.accNum = std::to_string(atm.createAccNumber());
	wxString inputName = registerName->GetValue();
	inputName = inputName.Trim();
	d.name = inputName.ToStdString();

	long month, day, year;
	if (!registerBirthMonth->GetValue().ToLong(&month) || !registerBirthDay->GetValue().ToLong(&day) ||
		!registerBirthYear->GetValue().ToLong(&year) || !ValidateDate(month, day, year)) {
		wxLogMessage("Invalid Input Date");
		return;
	}
	else {
		d.bday = StoreBday(month, day, year);
	}

	d.contact = registerContact->GetValue().ToStdString();
	d.pinCode = registerPin->GetValue().ToStdString();

	if (registerName->IsEmpty() || registerBirthMonth->IsEmpty() || registerBirthDay->IsEmpty() || registerBirthYear->IsEmpty()
		|| registerContact->IsEmpty() || registerPin->IsEmpty()) {

		wxLogMessage("Complete Input Information");
		return;

	}
	else {
		atm.registerAcc(d);
		ShowAccountInfo(d);

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
}

int MainFrame::GetCurrentYear()
{
	time_t t = time(0);
	struct tm* now = localtime(&t);
	return (now->tm_year + 1900);
}

int MainFrame::GetDaysInMonth(long month, long year)
{
	int dayInMonth[] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };

	if (year % 4 == 0 && year % 100 != 0 || year % 400 == 0) {
		dayInMonth[1] = 29;
	}

	return dayInMonth[month - 1];
}

string MainFrame::StoreBday(long month, long day, long year) {

	wxString bday = wxString::Format("%02d/%02d/%04d", month, day, year);
	return bday.ToStdString();

}

bool MainFrame::ValidateDate(long month, long day, long year)
{
	int currentYear = GetCurrentYear();
	int daysInMonth = GetDaysInMonth(month, year);

	bool isValid = true;

	if (month < 1 || month > 12) {
		isValid = false;
	}

	if (day < 1 || day > daysInMonth) {
		isValid = false;
	}

	if (year > currentYear) {
		isValid = false;
	}

	return isValid;
}

void MainFrame::OnInputMonth(wxCommandEvent& evt)
{
	long month;
	wxString validMonth = registerBirthMonth->GetValue();

	if (validMonth.length() > 0) {
		if (validMonth.length() == 2) {
			if (validMonth[0] != '0' && validMonth[0] != '1') {
				registerBirthMonth->SetBackgroundColour(*wxRED);
				registerBirthMonth->Clear();
				return;
			}

			registerBirthMonth->SetBackgroundColour(*wxWHITE);
		}

		if (validMonth.length() == 2 && validMonth.ToLong(&month)) {
			if (month < 1 || month > 12) {
				registerBirthMonth->SetBackgroundColour(*wxRED);
				registerBirthMonth->Clear();
				return;
			}

			OnInputDay(evt);
		}
	}

	registerBirthMonth->Refresh();
}


void MainFrame::OnMonthFocusLost(wxFocusEvent& evt)
{
	long month;
	wxString validMonth = registerBirthMonth->GetValue();

	if (validMonth.ToLong(&month) && validMonth.length() == 1)
	{
		registerBirthMonth->SetValue(wxString::Format("0%ld", month));
	}

	evt.Skip();
}

void MainFrame::OnInputDay(wxCommandEvent& evt)
{
	long day;
	long month;
	long year;

	wxString validDay = registerBirthDay->GetValue();
	wxString validMonth = registerBirthMonth->GetValue();
	wxString validYear = registerBirthYear->GetValue();

	if (validDay.ToLong(&day)) {
		
		if (registerBirthMonth->IsEmpty() || registerBirthYear->IsEmpty()) {
			if (day > 31) {
				registerBirthDay->Clear();
				registerBirthDay->SetBackgroundColour(*wxRED);
				return;
			}

			else {
				registerBirthDay->Refresh();
				registerBirthDay->SetBackgroundColour(*wxWHITE);
			}
		}

		if (!registerBirthMonth->IsEmpty() && registerBirthYear->IsEmpty()) {
			if (!registerBirthDay->IsEmpty() && validMonth.length() == 2) {
				if (validMonth[1] == '2' && day > 29) {
					registerBirthDay->Clear();
					registerBirthDay->SetBackgroundColour(*wxRED);
					return;
				}
			}
		}
	}

	if (validMonth.ToLong(&month) && validYear.ToLong(&year) && validDay.ToLong(&day)) {
		int dayMonth = GetDaysInMonth(month, year);

		if (!registerBirthMonth->IsEmpty() && !registerBirthYear->IsEmpty()) {
			if (!registerBirthDay->IsEmpty() && validYear.length() == 4) {

				if (day > dayMonth || day < 1 && day > 31)
				{
					registerBirthDay->Clear();
					registerBirthDay->SetBackgroundColour(*wxRED);
					return;
				}
				else {
					if (validDay.length() == 2) {
						registerBirthDay->Refresh();
						registerBirthDay->SetBackgroundColour(*wxWHITE);
					}
				}

			}
		}
	}
	registerBirthDay->Refresh();
}

void MainFrame::OnDayFocusLost(wxFocusEvent& evt)
{
	long day;
	wxString validDay = registerBirthDay->GetValue();

	if (validDay.ToLong(&day) && validDay.length() == 1)
	{
		registerBirthDay->SetValue(wxString::Format("0%ld", day));
	}

	evt.Skip();
}

void MainFrame::OnInputYear(wxCommandEvent& evt)
{
	long year;
	long day;
	long month;

	wxString validYear = registerBirthYear->GetValue();
	wxString validDay = registerBirthDay->GetValue();
	wxString validMonth = registerBirthMonth->GetValue();

	int currentYear = GetCurrentYear();
	wxString yearString = wxString::Format("%d", currentYear);

	if (validYear.ToLong(&year) && validYear.length() > 0) {

		if (validYear[0] == '0') {
			registerBirthYear->SetBackgroundColour(*wxRED);
			registerBirthYear->Clear();
			wxLogMessage("Invalid Year: Cannot start with 0");
			return;
		}

		if (validYear.length() == 1 && validYear[0] == '1') {
			return;
		}

		if (validYear.length() == 2) {
			if (validYear[0] == '1' && validYear[1] != '9') {
				registerBirthYear->SetBackgroundColour(*wxRED);
				registerBirthYear->Clear();
				return;
			}
		}

		if (validYear.length() == 2) {
			int inputFirstDigit = validYear[0] - '0';
			int inputSecondDigit = validYear[1] - '0';
			int currentFirstDigit = yearString[0] - '0';
			int currentSecondDigit = yearString[1] - '0';

			if (inputFirstDigit > currentFirstDigit ||
				(inputFirstDigit == currentFirstDigit && inputSecondDigit > currentSecondDigit)) {
				registerBirthYear->SetBackgroundColour(*wxRED);
				registerBirthYear->Clear();
				return;
			}
		}

		if (validYear.length() == 4 && year > currentYear) {
			registerBirthYear->SetBackgroundColour(*wxRED);
			registerBirthYear->Clear();
			return;
		}

		if (validDay.ToLong(&day) && validMonth.ToLong(&month) && validMonth.length() == 2 && validYear.length() == 4) {
			if (month == 2) {
				if (!(year % 4 == 0 && year % 100 != 0 || year % 400 == 0)) {
					if (day > 28) {
						registerBirthYear->SetBackgroundColour(*wxRED);
						registerBirthYear->Clear();
						return;
					}
				}
				else if ((year % 4 == 0 && year % 100 != 0 || year % 400 == 0)) {
					if (day <= 29) {
						registerBirthYear->SetBackgroundColour(*wxWHITE);
					}
				}
			}
		}

		if (validYear.length() == 4 && year <= currentYear) {
			registerBirthYear->SetBackgroundColour(*wxWHITE);
		}
	}

	registerBirthYear->Refresh();
}

void MainFrame::OnInputContact(wxCommandEvent& evt)
{
	wxString currentInput = registerContact->GetValue();

	if (currentInput.IsEmpty()) {
		currentInput = "+63";
		registerContact->SetValue(currentInput);
		registerContact->SetInsertionPointEnd();
	}
	else {
		if (currentInput == "+63") {
			registerContact->SetInsertionPointEnd();
			return;
		}

		if (currentInput.length() < 3 || !(currentInput.StartsWith("+63"))) {
			if (currentInput.Length() > 3) {
				currentInput = "+63" + currentInput.Remove(0, 3);
			}
			else {
				currentInput = "+63";
			}
			registerContact->SetValue(currentInput);
		}
	}

	// Make sure cursor is placed at the end of the input field
	registerContact->SetInsertionPointEnd();
	// Refresh the input field
	registerContact->Refresh();
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

void MainFrame::OnCancelRegisterClicked(wxCommandEvent& evt)
{
	registerPanel->Hide();

	registerName->Clear();
	//registerBday->Clear();
	registerContact->Clear();
	registerPin->Clear();

	enterAccountPanel->Show();
	Layout();
}

void MainFrame::OnCancelEnterAccClicked(wxCommandEvent& evt)
{
	enterAccountPanel->Hide();

	enterAccNum->Clear();
	enterPin->Clear();

	registerPanel->Show();
	Layout();
}

void MainFrame::OnCancelMainMenuClicked(wxCommandEvent& evt)
{
	mainPanel->Hide();
	enterAccountPanel->Show();
	Layout();
}

void MainFrame::OnCancelDepositClicked(wxCommandEvent& evt)
{
	depositPanel->Hide();
	inputDeposit->Clear();
	mainPanel->Show();
	Layout();
}

void MainFrame::OnCancelWithdrawClicked(wxCommandEvent& evt)
{
	withdrawPanel->Hide();
	inputWithdraw->Clear();
	mainPanel->Show();
	Layout();
}

void MainFrame::OnCancelFundTransferClicked(wxCommandEvent& evt)
{
	fundTransferPanel->Hide();
	inputAccTransfer->Clear();
	mainPanel->Show();
	Layout();
}

void MainFrame::OnCancelAccSettingsClicked(wxCommandEvent& evt)
{
	accountPanel->Hide();
	mainPanel->Show();
	Layout();
}

void MainFrame::OnCancelChangeAccInfoClicked(wxCommandEvent& evt)
{
	changeInfoPanel->Hide();

	changeNameInput->Clear();
	changeBdayInput->Clear();
	changeContactInput->Clear();

	mainPanel->Show();
	Layout();
}

void MainFrame::OnCancelChangePinClicked(wxCommandEvent& evt)
{
	changePinPanel->Hide();

	inputCurrentPin->Clear();
	inputNewPin->Clear();
	inputConfirmNewPin->Clear();

	mainPanel->Show();
	Layout();
}

#pragma once
#include <wx/wx.h>
#include "Account.h"
#include "FormatValidate.h"

class MainFrame : public wxFrame
{
public:
	MainFrame(const wxString& title);

private:
	
	Account d;
	AtmSystem atm;
	FormatValidate formatValidate;

	void OnKeyPress(wxKeyEvent& event);

	wxPanel* panel;
	wxStaticBitmap* backgroundBitmap;

	wxStaticBitmap* mainPanel;

	void CreateControls();
	void BindEventHandlers();
	void OnWindowClosed(wxCloseEvent& evt);
	void OnScreenClicked(wxMouseEvent& evt);
	void OnlyNumInput(wxKeyEvent& evt);
	void NameInput(wxCommandEvent& evt);
	wxStaticBitmap* noOperationPanel;

	void OnButtonPressed(wxCommandEvent& evt);

	//Register Account
	void OnRegisterButtonClicked(wxCommandEvent& evt);
	void AddInformation();

	wxStaticBitmap* registerPanel;
	wxStaticText* showAccNumber;
	wxTextCtrl* registerName;

	void OnInputRegisterPin(wxCommandEvent& evt);

	void OnInputRegisterMonth(wxCommandEvent& evt);
	void OnRegisterMonthFocusLost(wxFocusEvent& evt);

	void OnInputRegisterDay(wxCommandEvent& evt);
	void OnRegisterDayFocusLost(wxFocusEvent& evt);

	void OnInputRegisterYear(wxCommandEvent& evt);
	void OnRegisterYearFocusLost(wxFocusEvent& evt);

	wxTextCtrl* registerBirthMonth;
	wxTextCtrl* registerBirthDay;
	wxTextCtrl* registerBirthYear;
	
	wxTextCtrl* registerContact;
	void OnInputRegisterContact(wxCommandEvent& evt);


	wxTextCtrl* registerPin;
	wxButton* registerAccButton;

	//Format Amount
	void OnInputFormatInitialDepositAmount(wxCommandEvent& evt);
	void OnInputFormatDepositAmount(wxCommandEvent& evt);
	void OnInputFormatWithdrawAmount(wxCommandEvent& evt);
	void OnInputFormatTransferAmount(wxCommandEvent& evt);
	
	//Initial Deposit
	wxStaticBitmap* initialDepositPanel;
	wxTextCtrl* inputInitialDeposit;
	wxButton* confirmInitialDepositButton;
	wxButton* cancelInitialDepositButton;

	void OnInputInitialDeposit(wxCommandEvent& evt);
	void ConfirmInitialDeposit();
	void OnConfirmInitialDepositClicked(wxCommandEvent& evt);
	void OnCancelInitialDepositClicked(wxCommandEvent& evt);


	//Enter Account NUmber and Pin
	void EnterAccount();
	void OnEnterAccButtonClicked(wxCommandEvent& evt);
	void OnInputEnterPin(wxCommandEvent& evt);

	wxStaticBitmap* enterAccountPanel;
	wxTextCtrl* enterAccNum;
	wxTextCtrl* enterPin;
	wxButton* enterAccButton;
	
	//Main Menu
	wxButton* balanceButton;
	wxButton* depositButton;
	wxButton* withdrawButton;
	wxButton* accountSettingsButton;
	wxButton* fundTransferButton;

	//BalanceInquiry
	void BalanceInquiry();
	void OnBalanceButtonClicked(wxCommandEvent& evt);
	void ReturnFromBalanceToMain(wxCommandEvent& evt);

	wxStaticBitmap* balancePanel;
	wxStaticText* printBalance;
	wxButton* returnFromBalanceButton;


	//Deposit
	void OnDepositButtonClicked(wxCommandEvent& evt);
	void DepositMoney();
	void OnConfirmDepositClicked(wxCommandEvent& evt);
	void OnInputDeposit(wxCommandEvent& evt);

	wxStaticBitmap* depositPanel;
	wxButton* confirmDeposit;
	wxTextCtrl* inputDeposit;

	
	//Withdraw
	void WithdrawMoney();
	void OnWithdrawButtonClicked(wxCommandEvent& evt);
	void OnConfirmWithdrawClicked(wxCommandEvent& evt);
	void OnInputWithdraw(wxCommandEvent& evt);

	wxStaticBitmap* withdrawPanel;
	wxButton* confirmWithdraw;
	wxTextCtrl* inputWithdraw;


	//Fund Transfer
	void TransferMoney();
	void OnFundTransferButtonClicked(wxCommandEvent& evt);
	void OnConfirmFundTransferClicked(wxCommandEvent& evt);
	void OnInputFundTransfer(wxCommandEvent& evt);

	wxStaticBitmap* fundTransferPanel;
	wxButton* confirmFundTransferButton;
	wxTextCtrl* inputAccTransfer;
	wxTextCtrl* inputAmountTransfer;

	//Account Settings
	void OnAccountSettingsClicked(wxCommandEvent& evt);

	wxStaticBitmap* accountPanel;
	wxButton* changeAccInfoButton;
	wxButton* changeAccPinButton;
	
	//Change Information
	void OnChangeAccInfoClicked(wxCommandEvent& evt);
	void PrintCurrentInformation();
	void OnConfirmInfoChangeClicked(wxCommandEvent& evt);
	void UpdateInformation();

	wxStaticBitmap* changeInfoPanel;
	wxStaticText* printName;
	wxStaticText* printBday;
	wxStaticText* printContact;

	wxTextCtrl* changeNameInput;

	wxTextCtrl* changeMonthInput;
	wxTextCtrl* changeDayInput;
	wxTextCtrl* changeYearInput;

	void OnChangeBirthMonth(wxCommandEvent& evt);
	void OnChangeMonthFocusLost(wxFocusEvent& evt);

	void OnChangeBirthDay(wxCommandEvent& evt);
	void OnChangeDayFocusLost(wxFocusEvent& evt);

	void OnChangeBirthYear(wxCommandEvent& evt);
	void OnChangeYearFocusLost(wxFocusEvent& evt);
	
	wxTextCtrl* changeContactInput;
	void OnChangeContact(wxCommandEvent& evt);

	wxButton* confirmInfoChangeButton;

	//Change Pin
	void OnChangeAccPinClicked(wxCommandEvent& evt);
	void OnConfirmPinChangeClicked(wxCommandEvent& evt);
	void UpdatePin();

	wxStaticBitmap* changePinPanel;
	wxButton* confirmPinChangeButton;

	wxTextCtrl* inputCurrentPin;
	wxTextCtrl* inputNewPin;
	wxTextCtrl* inputConfirmNewPin;
	void OnInputCurrentPin(wxCommandEvent& evt);
	void OnInputNewPin(wxCommandEvent& evt);
	void OnInputConfirmPin(wxCommandEvent& evt);

	//Cancel Buttons
	wxButton* cancelRegisterButton;
	void OnCancelRegisterClicked(wxCommandEvent& evt);

	wxButton* cancelEnterAccountButton;
	void OnCancelEnterAccClicked(wxCommandEvent& evt);

	wxButton* cancelMainMenuButton;
	void OnCancelMainMenuClicked(wxCommandEvent& evt);

	wxButton* cancelDepositButton;
	void OnCancelDepositClicked(wxCommandEvent& evt);

	wxButton* cancelWithdrawButton;
	void OnCancelWithdrawClicked(wxCommandEvent& evt);

	wxButton* cancelFundTransferButton;
	void OnCancelFundTransferClicked(wxCommandEvent& evt);

	wxButton* cancelAccountSettingsButton;
	void OnCancelAccSettingsClicked(wxCommandEvent& evt);

	wxButton* cancelChangeAccInfoButton;
	void OnCancelChangeAccInfoClicked(wxCommandEvent& evt);

	wxButton* cancelChangePinButton;
	void OnCancelChangePinClicked(wxCommandEvent& evt);


	wxStaticBitmap* processPanel;
	void ProcessTransaction(wxStaticBitmap* panel);
	void Delay(int milliseconds);
	void OnProcess(wxStaticBitmap* panel);
	void OnSuccess(wxStaticBitmap* panel);
	
	wxStaticBitmap* withdrawSuccess;
	wxStaticBitmap* depositSuccess;
	wxStaticBitmap* transferSuccess;

	wxStaticBitmap* takeCard;
	wxStaticBitmap* exitAtm;

	//show acc after register
	void ShowAccountInfo(const Account& account);

};


#pragma once
#include <wx/wx.h>
#include "Account.h"

class MainFrame : public wxFrame
{
public:
	MainFrame(const wxString& title);
	AtmSystem atm;

private:
	void CreateControls();
	void BindEventHandlers();
	void OnWindowClosed(wxCloseEvent& evt);
	void OnScreenClicked(wxMouseEvent& evt);
	void OnlyNumInput(wxKeyEvent& evt);
	void NameInput(wxCommandEvent& evt);
	wxPanel* noOperationPanel;

	//Register Account
	void OnRegisterButtonClicked(wxCommandEvent& evt);
	void AddInformation();

	wxPanel* registerPanel;
	wxStaticText* showAccNumber;
	wxTextCtrl* registerName;

	int GetCurrentYear();
	int GetDaysInMonth(long month, long year);

	string StoreBday(long month, long day, long year);

	bool ValidateDate(long month, long day, long year);

	void OnInputMonth(wxCommandEvent& evt);
	void OnMonthFocusLost(wxFocusEvent& evt);

	void OnInputDay(wxCommandEvent& evt);
	void OnDayFocusLost(wxFocusEvent& evt);

	void OnInputYear(wxCommandEvent& evt);

	wxTextCtrl* registerBirthMonth;
	wxTextCtrl* registerBirthDay;
	wxTextCtrl* registerBirthYear;
	
	wxTextCtrl* registerContact;
	void OnInputContact(wxCommandEvent& evt);

	wxTextCtrl* registerPin;
	wxButton* registerAccButton;
	

	//Enter Account NUmber and Pin
	void EnterAccount();
	void OnEnterAccButtonClicked(wxCommandEvent& evt);

	wxPanel* enterAccountPanel;
	wxTextCtrl* enterAccNum;
	wxTextCtrl* enterPin;
	wxButton* enterAccButton;
	
	//Main Menu
	wxPanel* mainPanel;
	wxButton* balanceButton;
	wxButton* depositButton;
	wxButton* withdrawButton;
	wxButton* accountSettingsButton;
	wxButton* fundTransferButton;

	//BalanceInquiry
	void BalanceInquiry();
	void OnBalanceButtonClicked(wxCommandEvent& evt);
	void ReturnFromBalanceToMain(wxCommandEvent& evt);

	wxPanel* balancePanel;
	wxStaticText* printBalance;
	wxButton* returnFromBalanceButton;


	//Deposit
	void OnDepositButtonClicked(wxCommandEvent& evt);
	void AddMoney();
	void OnConfirmDepositClicked(wxCommandEvent& evt);

	wxPanel* depositPanel;
	wxButton* confirmDeposit;
	wxTextCtrl* inputDeposit;

	
	//Withdraw
	void WithdrawMoney();
	void OnWithdrawButtonClicked(wxCommandEvent& evt);
	void OnConfirmWithdrawClicked(wxCommandEvent& evt);

	wxPanel* withdrawPanel;
	wxButton* confirmWithdraw;
	wxTextCtrl* inputWithdraw;


	//Fund Transfer
	void TransferMoney();
	void OnFundTransferButtonClicked(wxCommandEvent& evt);
	void OnConfirmFundTransferClicked(wxCommandEvent& evt);

	wxPanel* fundTransferPanel;
	wxButton* confirmFundTransferButton;
	wxTextCtrl* inputAccTransfer;
	wxTextCtrl* inputAmountTransfer;

	//Account Settings
	void OnAccountSettingsClicked(wxCommandEvent& evt);

	wxPanel* accountPanel;
	wxButton* changeAccInfoButton;
	wxButton* changeAccPinButton;
	
	//Change Information
	void OnChangeAccInfoClicked(wxCommandEvent& evt);
	void PrintCurrentInformation();
	void OnConfirmInfoChangeClicked(wxCommandEvent& evt);
	void UpdateInformation();

	wxPanel* changeInfoPanel;
	wxStaticText* printName;
	wxStaticText* printBday;
	wxStaticText* printContact;

	wxTextCtrl* changeNameInput;
	wxTextCtrl* changeBdayInput;
	wxTextCtrl* changeContactInput;
	wxButton* confirmInfoChangeButton;

	//Change Pin
	void OnChangeAccPinClicked(wxCommandEvent& evt);
	void OnConfirmPinChangeClicked(wxCommandEvent& evt);
	void UpdatePin();

	wxPanel* changePinPanel;
	wxButton* confirmPinChangeButton;
	wxTextCtrl* inputCurrentPin;
	wxTextCtrl* inputNewPin;
	wxTextCtrl* inputConfirmNewPin;
	
	//ReviewMoneyScreen
	wxPanel* reviewAddedBalance;
	wxPanel* reviewWithdrawnMoney;

	/*Animations
	wxPanel* AtmOpeningAnimation;
	wxPanel* DefaultAtmAnimation;
	wxPanel* AtmWithdrawAnimation;
	wxPanel* AtmDepositAnimation;
	*/

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


	void ShowAccountInfo(const Account& account);

	wxButton* cancelInitialDepositButon;//no initial deposit yet
	void OnCancelInitialDepositClicked(wxCommandEvent& evt);

};


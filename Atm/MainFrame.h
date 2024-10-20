#pragma once
#include <wx/wx.h>
#include "Account.h"

class MainFrame : public wxFrame
{
public:
	MainFrame(const wxString& title);
	AtmSystem atm;

private:
	
	Account d;

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

	void OnInputRegisterPin(wxCommandEvent& evt);
	void OnValidatePin(wxTextCtrl* inputPin);

	string StoreBday(long month, long day, long year);

	void OnInputRegisterMonth(wxCommandEvent& evt);
	bool OnValidateMonth(wxTextCtrl* monthInput, wxTextCtrl* dayInput);
	void OnRegisterMonthFocusLost(wxFocusEvent& evt);
	void FormatMonthOnFocusLost(wxTextCtrl* monthInput);

	void OnInputRegisterDay(wxCommandEvent& evt);
	bool OnValidateDay(wxTextCtrl* monthInput, wxTextCtrl* dayInput, wxTextCtrl* yearInput);
	void OnRegisterDayFocusLost(wxFocusEvent& evt);
	void FormatDayOnFocusLost(wxTextCtrl* dayInput);

	void OnInputRegisterYear(wxCommandEvent& evt);
	bool OnValidateYear(wxTextCtrl* monthInput, wxTextCtrl* dayInput, wxTextCtrl* yearInput);
	void OnRegisterYearFocusLost(wxFocusEvent& evt);
	void FormatYearOnFocusLost(wxTextCtrl* yearInput);

	wxTextCtrl* registerBirthMonth;
	wxTextCtrl* registerBirthDay;
	wxTextCtrl* registerBirthYear;
	
	wxTextCtrl* registerContact;
	void OnInputRegisterContact(wxCommandEvent& evt);
	void OnValidateContact(wxTextCtrl* contactInput);

	wxTextCtrl* registerPin;
	wxButton* registerAccButton;

	//Format Amount
	void FormatAmount(wxTextCtrl* inputAmount);
	void OnInputFormatInitialDepositAmount(wxCommandEvent& evt);
	void OnInputFormatDepositAmount(wxCommandEvent& evt);
	void OnInputFormatWithdrawAmount(wxCommandEvent& evt);
	void OnInputFormatTransferAmount(wxCommandEvent& evt);
	
	//Initial Deposit
	wxPanel* initialDepositPanel;
	wxTextCtrl* inputInitialDeposit;
	wxButton* confirmInitialDepositButton;
	wxButton* cancelInitialDepositButton;
	void ConfirmInitialDeposit();
	void OnConfirmInitialDepositClicked(wxCommandEvent& evt);
	void OnCancelInitialDepositClicked(wxCommandEvent& evt);


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

	wxPanel* changePinPanel;
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

	//show acc after register
	wxPanel* ShowAccountInfoPanel;
	void ShowAccountInfo(const Account& account);


	//ReviewMoneyScreen
	wxPanel* reviewDepositBalancePanel;
	wxButton* exitReviewDepositButton;
	wxStaticText* PrintDepositedAmount;
	wxStaticText* PrintAfterDepositBalance;
	void OnExitReviewDepositClicked(wxCommandEvent& evt);

	wxPanel* reviewWithdrawnMoneyPanel;
	wxButton* exitReviewWithdrawnButton;
	wxStaticText* PrintWithdrawnAmount;
	wxStaticText* PrintAfterWithdrawBalance;
	void OnExitReviewWithdrawnClicked(wxCommandEvent& evt);

	wxPanel* reviewTransferedMoneyPanel;
	wxButton* exitReviewTransferedButton;
	wxStaticText* PrintTransferedAmount;
	wxStaticText* PrintAfterTransferBalance;
	void OnExitReviewTransferedClicked(wxCommandEvent& evt);

	
	/*Animations
	wxPanel* AtmOpeningAnimation;
	wxPanel* DefaultAtmAnimation;
	wxPanel* AtmWithdrawAnimation;
	wxPanel* AtmDepositAnimation;
	*/

};


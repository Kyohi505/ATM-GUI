#pragma once
#include <wx/wx.h>

class FormatValidate
{
public:

	void OnValidatePin(wxTextCtrl* inputPin);

	int GetCurrentYear();
	int GetDaysInMonth(long month, long year);

	string FormatBday(long month, long day, long year);

	bool OnValidateMonth(wxTextCtrl* monthInput, wxTextCtrl* dayInput, wxTextCtrl* yearInput);
	void FormatMonthOnFocusLost(wxTextCtrl* monthInput);

	bool OnValidateDay(wxTextCtrl* monthInput, wxTextCtrl* dayInput, wxTextCtrl* yearInput);
	void FormatDayOnFocusLost(wxTextCtrl* dayInput);

	bool OnValidateYear(wxTextCtrl* monthInput, wxTextCtrl* dayInput, wxTextCtrl* yearInput);
	void FormatYearOnFocusLost(wxTextCtrl* yearInput);

	

	void OnValidateContact(wxTextCtrl* contactInput);

	void FormatAmount(wxTextCtrl* inputAmount);
};


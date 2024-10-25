#include "MainFrame.h"
#include "Account.h"
#include "FormatValidate.h"
#include <wx/wx.h>
#include <string>
#include <ctime>

void FormatValidate::OnValidatePin(wxTextCtrl* inputPin)
{
	wxString pin = inputPin->GetValue();

	if (pin.length() > 3) {
		inputPin->SetBackgroundColour(wxColor(248, 247, 255));
		inputPin->Refresh();
	}

}

int FormatValidate::GetCurrentYear()
{
	time_t t = time(0);
	struct tm* now = localtime(&t);
	return (now->tm_year + 1900);
}

int FormatValidate::GetDaysInMonth(long month, long year)
{
	int dayInMonth[] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };

	if (year % 4 == 0 && year % 100 != 0 || year % 400 == 0) {
		dayInMonth[1] = 29;
	}

	return dayInMonth[month - 1];
}

string FormatValidate::FormatBday(long month, long day, long year)
{
	wxString bday = wxString::Format("%02d/%02d/%04d", month, day, year);
	return bday.ToStdString();
}

bool FormatValidate::OnValidateMonth(wxTextCtrl* monthInput, wxTextCtrl* dayInput, wxTextCtrl* yearInput)
{
	long month;
	long day;
	long year;
	wxString validDay = dayInput->GetValue();
	wxString validMonth = monthInput->GetValue();
	wxString validYear = yearInput->GetValue();


	if (validMonth.length() > 0) {
		if (validMonth.length() == 2) {
			if (validMonth[0] != '0' && validMonth[0] != '1') {
				monthInput->SetBackgroundColour(*wxRED);
				monthInput->Clear();
				return false;
			}

			if (!dayInput->IsEmpty()) {

				if (validDay.ToLong(&day) && validMonth == "02" && day > 29) {
					dayInput->Clear();
					dayInput->SetBackgroundColour(*wxRED);
					return false;
				}
				if (!yearInput->IsEmpty()) {
					if (validYear.ToLong(&year)) {
						if (!(year % 4 == 0 && year % 100 != 0 || year % 400 == 0)) {
							if (validMonth == "02" && day > 28) {
								dayInput->SetBackgroundColour(*wxRED);
								dayInput->Clear();
								return false;
							}
						}
					}
				}
			}

			if (validMonth.ToLong(&month)) {
				if (month < 1 || month > 12) {
					monthInput->SetBackgroundColour(*wxRED);
					monthInput->Clear();
					return false;
				}
				else if (month >= 1 || month <= 12) {
					monthInput->Refresh();
					monthInput->SetBackgroundColour(wxColor(248, 247, 255));
					return true;
				}

			}

		}

	}
	return false;
	monthInput->Refresh();
}

void FormatValidate::FormatMonthOnFocusLost(wxTextCtrl* monthInput)
{
	long month;
	wxString formatMonth = monthInput->GetValue();

	if (!monthInput->IsEmpty()) {
		if (formatMonth.ToLong(&month) && formatMonth.length() == 1)
		{
			monthInput->SetValue(wxString::Format("0%ld", month));
		}
	}
}

bool FormatValidate::OnValidateDay(wxTextCtrl* monthInput, wxTextCtrl* dayInput, wxTextCtrl* yearInput)
{
	long day;
	long month;
	long year;

	wxString validDay = dayInput->GetValue();
	wxString validMonth = monthInput->GetValue();
	wxString validYear = yearInput->GetValue();

	if (validDay.ToLong(&day)) {

		if (monthInput->IsEmpty() || yearInput->IsEmpty()) {
			if (day > 31 || validDay == "00") {
				dayInput->Clear();
				dayInput->SetBackgroundColour(*wxRED);
				return false;
			}

			if (!monthInput->IsEmpty() && yearInput->IsEmpty()) {
				if (validMonth == "02") {
					if (day > 29) {
						dayInput->Clear();
						dayInput->SetBackgroundColour(*wxRED);
						return false;
					}

					else {
						dayInput->Refresh();
						dayInput->SetBackgroundColour(wxColor(248, 247, 255));
						return true;
					}
				}
			}

			else {
				dayInput->Refresh();
				dayInput->SetBackgroundColour(wxColor(248, 247, 255));
				return true;
			}
		}

	}

	if (validMonth.ToLong(&month) && validYear.ToLong(&year) && validDay.ToLong(&day)) {
		int dayMonth = GetDaysInMonth(month, year);

		if (!monthInput->IsEmpty() && !yearInput->IsEmpty()) {
			if (!dayInput->IsEmpty() && validYear.length() == 4) {

				if (day > dayMonth || day < 1 && day > 31 || validDay == "00")
				{
					dayInput->Clear();
					dayInput->SetBackgroundColour(*wxRED);
					return false;
				}
				else {
					if (validDay.length() == 2) {
						dayInput->Refresh();
						dayInput->SetBackgroundColour(wxColor(248, 247, 255));
						return true;
					}
				}

			}
		}
	}

	return false;
	dayInput->Refresh();
}

void FormatValidate::FormatDayOnFocusLost(wxTextCtrl* dayInput)
{
	long day;
	wxString formatDay = dayInput->GetValue();

	if (!dayInput->IsEmpty()) {
		if (formatDay.ToLong(&day) && formatDay.length() == 1)
		{
			dayInput->SetValue(wxString::Format("0%ld", day));
		}
	}
}

bool FormatValidate::OnValidateYear(wxTextCtrl* monthInput, wxTextCtrl* dayInput, wxTextCtrl* yearInput)
{
	long year;
	long day;
	long month;

	wxString validYear = yearInput->GetValue();
	wxString validDay = dayInput->GetValue();
	wxString validMonth = monthInput->GetValue();

	int currentYear = GetCurrentYear();
	wxString yearString = wxString::Format("%d", currentYear);

	if (validYear.ToLong(&year) && validYear.length() > 0) {

		if (validYear[0] == '0') {
			yearInput->SetBackgroundColour(*wxRED);
			yearInput->Clear();
			return false;
		}

		if (validYear.length() == 2) {
			if (validYear[0] == '1' && validYear[1] != '9') {
				yearInput->SetBackgroundColour(*wxRED);
				yearInput->Clear();
				return false;
			}
		}

		if (validYear.length() == 2) {
			int inputFirstDigit = validYear[0] - '0';
			int inputSecondDigit = validYear[1] - '0';
			int currentFirstDigit = yearString[0] - '0';
			int currentSecondDigit = yearString[1] - '0';

			if (inputFirstDigit > currentFirstDigit ||
				(inputFirstDigit == currentFirstDigit && inputSecondDigit > currentSecondDigit)) {
				yearInput->SetBackgroundColour(*wxRED);
				yearInput->Clear();
				return false;
			}
		}

		if (validYear.length() == 4 && year > currentYear) {
			yearInput->SetBackgroundColour(*wxRED);
			yearInput->Clear();
			return false;
		}

		if (validDay.ToLong(&day) && validMonth.ToLong(&month) && validMonth.length() == 2 && validYear.length() == 4) {
			if (validMonth == "02") {
				if (!(year % 4 == 0 && year % 100 != 0 || year % 400 == 0)) {
					if (day > 28) {
						dayInput->SetBackgroundColour(*wxRED);
						dayInput->Clear();
						return false;
					}
				}
				else if ((year % 4 == 0 && year % 100 != 0 || year % 400 == 0)) {
					if (day <= 29) {
						yearInput->Refresh();
						yearInput->SetBackgroundColour(wxColor(248, 247, 255));
						return true;
					}
				}
			}
		}

		if (validYear.length() == 4 && year <= currentYear) {
			yearInput->Refresh();
			yearInput->SetBackgroundColour(wxColor(248, 247, 255));
			return true;
		}
	}

	return false;
	yearInput->Refresh();
}

void FormatValidate::FormatYearOnFocusLost(wxTextCtrl* yearInput)
{
	wxString formatYear = yearInput->GetValue();

	if (formatYear.length() < 4) {
		yearInput->SetBackgroundColour(*wxRED);
		yearInput->Clear();
	}
}

void FormatValidate::OnValidateContact(wxTextCtrl* contactInput)
{
	wxString currentInput = contactInput->GetValue();

	if (currentInput.IsEmpty()) {
		currentInput = "+63";
		contactInput->SetValue(currentInput);
		contactInput->SetInsertionPointEnd();
	}

	if (currentInput.length() == 13) {
		contactInput->Refresh();
		contactInput->SetBackgroundColour(wxColor(248, 247, 255));
	}

	else {
		if (currentInput == "+63") {
			contactInput->SetInsertionPointEnd();
			return;
		}

		if (currentInput.length() < 3 || !(currentInput.StartsWith("+63"))) {
			if (currentInput.Length() > 3) {
				currentInput = "+63" + currentInput.Remove(0, 3);
			}
			else {
				currentInput = "+63";
			}
			contactInput->SetValue(currentInput);
		}
	}

	contactInput->SetInsertionPointEnd();
	contactInput->Refresh();
}

void FormatValidate::FormatAmount(wxTextCtrl* inputAmount)
{
	inputAmount->GetEventHandler()->SetEvtHandlerEnabled(false);

	wxString amount = inputAmount->GetValue();
	int inputBeforeCents = inputAmount->GetInsertionPoint();

	if (amount.IsEmpty() || amount == ".00") {
		inputAmount->SetValue(wxEmptyString);
		inputAmount->SetInsertionPoint(0);

		inputAmount->GetEventHandler()->SetEvtHandlerEnabled(true);
		return;
	}

	if (!amount.EndsWith(".00")) {
		if (amount.Contains('.')) {
			amount = amount.BeforeLast('.') + ".00";
		}
		else {
			amount += ".00";
		}

		inputAmount->SetValue(amount);

		if (inputBeforeCents <= amount.Length() - 3) {
			inputAmount->SetInsertionPoint(inputBeforeCents);
		}
		else {
			inputAmount->SetInsertionPoint(amount.Length() - 3);
		}
	}


	inputAmount->GetEventHandler()->SetEvtHandlerEnabled(true);
}

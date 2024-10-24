#pragma once
#include <string>
#include <vector>

using std::string;
using std::vector;

struct Account	
{
	string name;
	string bday;
	string contact;
	string accNum;
	string pinCode;
	double balance = 0;
};

struct Node	
{
	Account data;
	Node* next;
	Node(Account x) : data(x), next(NULL){}
};

class AtmSystem 
{
private:
	Node* head;
	Node* currentUser;

public:
	AtmSystem() : head(NULL), currentUser(NULL) {}
	
	void registerAcc(Account x);
	int enterAcc(string num, string pin);
	int createAccNumber();
	double getBalance();
	int confirmInitialDeposit(double x);
	void deposit(double x);
	void withdraw(double x);
	int fundTransfer(string x, double y);

	void changeAccName(string x);
	void changeAccBday(string x);
	void changeAccContact(string x);
	int changeAccPin(string currentPin, string newPin, string confirmedPin);
	
	string getAccName();
	string getAccBday();
	string getAccContact();
	string getAccPin();

	void storeAcc();
	void loadAcc();

	string checkUsb();
	vector<string> getAvailableDrives();
	string detectNewDrive(const vector<string>& detectedDrives);

	void storePinToUSB(const string& usbDrive, const string& accNum, const string& pin);
	bool checkRegisterUSB(const string& usbDrive);
	string getAccNumUSB(const string& usbDrive);
};
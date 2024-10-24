#include "Account.h"
#include <string>
#include <fstream>
#include <filesystem>
#include <vector>
#include <algorithm>

int AtmSystem::createAccNumber()
{
	int uniqueAccNum;
	bool unique;

	do {
		unique = true;
		uniqueAccNum = 10000 + rand() % 90000;

		Node* p = head;
		while (p != NULL) {
			if (std::stoi(p->data.accNum) == uniqueAccNum) {
				unique = false;
				break;
			}
			p = p->next;
		}
	} while (!unique);


	return uniqueAccNum;
}

void AtmSystem::registerAcc(Account x)
{

	Node *p, *q, *newNode;
	p = q = head;

	newNode = new Node(x);

	while (p != NULL) {
		q = p;
		p = p->next;
	}

	if (p == head) {
		head = newNode;
	}
	else {
		q->next = newNode;
		newNode->next = p;
	}
}

int AtmSystem::confirmInitialDeposit(double x) {

	if (x < 5000) {
		return -1;
	}
	if (x >= 5000) {
		return 0;
	}
}

int AtmSystem::enterAcc(string num, string pin)
{
	Node* p = head;
	
	while (p != NULL &&  num != p->data.accNum) {
		p = p->next;
	}
	if (p == NULL) {
		return -1;
	}
	else if(p->data.pinCode != pin){
		return 0;
	}

	else{
		if (p != NULL && p->data.pinCode == pin) {
			currentUser = p;
			return 1;
		}
	}

}

double AtmSystem::getBalance()
{
	return currentUser->data.balance;
}

void AtmSystem::deposit(double x)
{
	currentUser->data.balance += x;
}

void AtmSystem::withdraw(double x)
{
	currentUser->data.balance -= x;
}

int AtmSystem::fundTransfer(string x, double y)
{
	Node* p = head;
	while (p != NULL && p->data.accNum != x) {
		p = p->next;
	}

	if (p == NULL) {
		return -1;
	}

	else if (x == currentUser->data.accNum) {
		return 0;
	}

	else if (y <= 0 && y > currentUser->data.balance) {
		return -2;
	}

	else if (x == p->data.accNum && y > 0 && y < currentUser->data.balance) {
		currentUser->data.balance -= y;
		p->data.balance += y;
		return 1;
	}
}

void AtmSystem::storeAcc()
{
	Node* p = head;
	std::ofstream file("AccountList.txt");

	while (p != NULL)
	{
		file << p->data.name << '\n'
			<< p->data.bday << '\n'
			<< p->data.contact << '\n'
			<< p->data.accNum << '\n'
			<< p->data.balance << '\n'
			<< p->data.encryptedPin << '\n';
		p = p->next;
	}

	file.close();
}

void AtmSystem::loadAcc()
{
	std::ifstream file("AccountList.txt");
	Account d;

	while (getline(file, d.name) &&
		getline(file, d.bday) &&
		getline(file, d.contact) &&
		getline(file, d.accNum) &&
		file >> d.balance)
	{
		file.ignore();
		getline(file, d.encryptedPin);

		d.pinCode = decryptEncrypt(d.encryptedPin, key);

		Node* p = new Node(d);
		p->next = head;
		head = p;
	}

	file.close();
}

string AtmSystem::checkUsb()
{
	static vector<string> detectedDrives = getAvailableDrives();
	string newDrive = detectNewDrive(detectedDrives);

	if (!newDrive.empty()) {
		return newDrive;
	}

	return "";
}

vector<string> AtmSystem::getAvailableDrives()
{
	vector<string> drives;

	for (char drive = 'A'; drive <= 'Z'; drive++) {
		string drivePath = string(1, drive) + ":\\";

		if (std::filesystem::exists(drivePath) && std::filesystem::is_directory(drivePath)) {
			drives.push_back(drivePath);
		}
	}

	return drives;
}

string AtmSystem::detectNewDrive(const vector<string>& detectedDrives)
{
	std::vector<std::string> currentDrives = getAvailableDrives();

	for (const auto& drive : currentDrives) {
		if (std::find(detectedDrives.begin(), detectedDrives.end(), drive) == detectedDrives.end()) {
			return drive;
		}
	}
	return "";
}

void AtmSystem::storePinToUSB(const string& usbDrive, const string& accNum, const string& pin)
{
	string filePath = usbDrive + "pinCode.txt";
	std::ofstream file(filePath);
	if (file) {
		file << accNum << "\n" << pin;
		file.close();
	}

}

bool AtmSystem::checkRegisterUSB(const string& usbDrive)
{
	string filePath = usbDrive + "pinCode.txt";

	std::ifstream file(filePath);
	if (file) {
		file.close();
		return true;
	}
	return false;
}

string AtmSystem::getAccNumUSB(const string& usbDrive)
{
	string filePath = usbDrive + "pinCode.txt";
	string accNum;

	std::ifstream file(filePath);
	if (file) {
		getline(file, accNum);
		file.close();
		return accNum;
	}
	return "";
}

string AtmSystem::decryptEncrypt(string pin, string key)
{
	string result = pin;
	for (size_t i = 0; i < pin.length(); i++) {
		result[i] = pin[i] ^ key[i % key.length()];
	}
	return result;
}

string AtmSystem::getAccName()
{
	return currentUser->data.name;
}

string AtmSystem::getAccBday()
{
	return currentUser->data.bday;
}

string AtmSystem::getAccContact()
{
	return currentUser->data.contact;
}

string AtmSystem::getAccPin()
{
	return currentUser->data.pinCode;
}

void AtmSystem::changeAccName(string x)
{
	currentUser->data.name = x;
}

void AtmSystem::changeAccBday(string x)
{
	currentUser->data.bday = x;
}

void AtmSystem::changeAccContact(string x)
{
	currentUser->data.contact = x;
}

int AtmSystem::changeAccPin(string currentPin, string newPin, string confirmedPin)
{
	string decryptedCurrentPin = decryptEncrypt(currentUser->data.encryptedPin, key);

	if (decryptedCurrentPin != currentPin) {
		return 0;
	}

	else if (currentUser->data.pinCode == currentPin && newPin != confirmedPin) {
		return -1;
	}

	else if (currentUser->data.pinCode == currentPin && newPin == confirmedPin) {
		currentUser->data.pinCode = newPin;
		currentUser->data.encryptedPin = decryptEncrypt(newPin, key);

		string currentDrive = checkUsb();
		storePinToUSB(currentDrive, currentUser->data.accNum, currentUser->data.encryptedPin);
		return 1;
	}
	
}

  
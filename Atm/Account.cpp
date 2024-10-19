#include "Account.h"
#include <string>
#include <fstream>

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

int AtmSystem::initialDeposit(double x) {

	if (x < 5000) {
		return 1;
	}
	if (x > 5000) {
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
	std::ofstream file("pinCode.txt");

	while (p != NULL) {
		file << p->data.name << "\n" << p->data.bday << " " << p->data.contact << " "
			<< p->data.balance << " " << p->data.accNum << " " << p->data.pinCode << '\n';

		p = p->next;
	}

	file.close();
}

void AtmSystem::loadAcc()
{

	std::ifstream file("pinCode.txt");
	Account d;

	while (std::getline(file, d.name)) {

		file >> d.bday >> d.contact >> d.balance >> d.accNum >> d.pinCode;
		file.ignore();

		Node* p, * q, * newNode;
		p = q = head;
		newNode = new Node(d);

		while (p != NULL) {
			q = p;
			p = p->next;
		}

		if (p == head)
			head = newNode;
		else
			q->next = newNode;
		newNode->next = p;
	}
	file.close();
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
	
	if (currentUser->data.pinCode != currentPin) {
		return 0;
	}

	else if (currentUser->data.pinCode == currentPin && newPin != confirmedPin) {
		return -1;
	}

	else if (currentUser->data.pinCode == currentPin && newPin == confirmedPin) {
		currentUser->data.pinCode = newPin;
		return 1;
	}
	
}

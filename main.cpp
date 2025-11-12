#include <cstring>
#include <fstream>
#include <iostream>
#include <limits>
#include <memory>
#include <string>

using namespace	std;

struct			Account
{
	char		account_number[32];
	char		holder_name[64];
	double		balance;
};

// function to check if an account exists -> Open file in read mode
bool	accountExists(fstream &f, const char *acc_nb)
{
	Account	tmp;

	f.clear();
	f.seekg(0, ios::beg); // move read pointer to start
	while (f.read(reinterpret_cast<char *>(&tmp), sizeof(tmp)))
	{
		if (strncmp(tmp.account_number, acc_nb,
				sizeof(tmp.account_number)) == 0)
			return (true);
	}
	return (false);
}

// function to create an account -> write to end of file
Account	createAccount(fstream &f, const char *acc_nb, const char *acc_name,
		double balance)
{
	Account	ac;

	f.clear();
	f.seekp(0, ios::end); // move write pointer to the end
	strncpy(ac.account_number, acc_nb, sizeof(ac.account_number) - 1);
	ac.account_number[sizeof(ac.account_number) - 1] = '\0';
	strncpy(ac.holder_name, acc_name, sizeof(ac.holder_name) - 1);
	ac.holder_name[sizeof(ac.holder_name) - 1] = '\0';
	ac.balance = balance;
	f.write(reinterpret_cast<char *>(&ac), sizeof(ac));
	return (ac);
}

// print info about account -> read mode
void	viewDetails(fstream &f, const char *acc_nb)
{
	Account	ac;

	f.clear();
	f.seekg(0, ios::beg);
	while (f.read(reinterpret_cast<char *>(&ac), sizeof(ac)))
	{
		if (strcmp(ac.account_number, acc_nb) == 0)
		{
			cout << "Account holder name: " << ac.holder_name << endl;
			cout << "Account balance: " << ac.balance << endl;
			return ;
		}
	}
}

// search where the record is and modify the value of its balance
void	depositAmount(fstream &f, const char *acc_nb, double amount)
{
	Account	tmp;

	f.clear();
	f.seekg(0, ios::beg);
	while (f.read(reinterpret_cast<char *>(&tmp), sizeof(tmp)))
	{
		if (strcmp(tmp.account_number, acc_nb) == 0)
		{
			tmp.balance += amount;
			// Move write pointer back to the start of this record
			f.seekp(-static_cast<long>(sizeof(tmp)), ios::cur);
			f.write(reinterpret_cast<char *>(&tmp), sizeof(tmp));
			f.flush();
			cout << "Deposit successful. New balance: " << tmp.balance << endl;
			return ;
		}
	}
	cout << "Account not found." << endl;
}

void	withdrawAmount(fstream &f, const char *acc_nb, double amount)
{
	Account	tmp;

	f.clear();
	f.seekg(0, ios::beg);
	while (f.read(reinterpret_cast<char *>(&tmp), sizeof(tmp)))
	{
		if (strcmp(tmp.account_number, acc_nb) == 0)
		{
			// found the record
			if (tmp.balance >= amount)
			{
				// withdraw
				tmp.balance -= amount;
				f.seekp(-static_cast<long>(sizeof(tmp)), ios::cur);
				f.write(reinterpret_cast<char *>(&tmp), sizeof(tmp));
				f.flush();
				cout << "Withdraw successfull. New balance: " << tmp.balance << endl;
				return ;
			}
			else
			{
				cout << "Balance not sufficient." << endl;
				return ;
			}
		}
	}
	cout << "Account not found." << endl;
}

int	main(void)
{
	int		option;
	char	account_number[32];
	char	holder_name[64];
	double	balance;
	double	amount;

	fstream f("data.bin", ios::binary | ios::in | ios::out);
	if (!f)
	{
		cerr << "Error opening the file" << endl;
		exit(1);
	}
	while (true)
	{
		cout << "Bank Management System" << endl;
		cout << "1.Create Account" << endl;
		cout << "2.View Account" << endl;
		cout << "3.Deposit Money" << endl;
		cout << "4.Withdraw Money" << endl;
		cout << "5.Exit" << endl;
		cout << "Enter an option: " << endl;
		while (!(cin >> option) || option < 1 || option > 5)
		{
			cout << "Please enter a valid option" << endl;
			cin.clear();
			cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		}
		switch (option)
		{
		case 1:
			// get info from user
			cout << "Enter account number: " << endl;
			cin >> account_number;
			// check if the account already exists
			if (accountExists(f, account_number))
			{
				cout << "This account already exists. Choose option 2 to view account" << endl;
				break ;
			}
			cout << "Enter holder full name: " << endl;
			cin >> holder_name;
			cout << "Enter balance in USD: " << endl;
			cin >> balance;
			createAccount(f, account_number, holder_name, balance);
			break ;
		case 2:
			cout << "Enter account number: " << endl;
			cin >> account_number;
			if (accountExists(f, account_number))
			{
				viewDetails(f, account_number);
			}
			else
			{
				cout << "This account does not exist. Choose option 1 to create account." << endl;
			}
			break ;
		case 3:
			// deposit money
			cout << "Enter account number: " << endl;
			cin >> account_number;
			if (accountExists(f, account_number))
			{
				cout << "Enter amount to deposit: " << endl;
				do
				{
					cin >> amount;
				} while (amount < 0);
				depositAmount(f, account_number, amount);
			}
			else
			{
				cout << "This account does not exist. Choose option 1 to create account." << endl;
			}
			break ;
		case 4:
			// withdraw money
			cout << "Enter account number: " << endl;
			cin >> account_number;
			if (accountExists(f, account_number))
			{
				cout << "Enter amount to withdraw: " << endl;
				do
				{
					cin >> amount;
				} while (amount < 0);
				withdrawAmount(f, account_number, amount);
			}
			else
			{
				cout << "This account does not exist. Choose option 1 to create account." << endl;
			}
			break ;
		case 5:
			cout << "Exited successfully" << endl;
			return (0);
		}
	}
	return (0);
}

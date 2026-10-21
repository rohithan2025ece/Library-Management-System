#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <iomanip>
using namespace std;

class Account {
public:
    int number;
    string name;
    double balance;

    Account(int n = 0, string s = "", double b = 0) {
        number = n;
        name = s;
        balance = b;
    }
};

vector<Account> accounts;

void loadData() {
    accounts.clear();
    ifstream file("bank_data.txt");
    int n;
    string name;
    double b;
    while (file >> n) {
        file.ignore();
        getline(file, name, '|');
        file >> b;
        accounts.push_back(Account(n, name, b));
    }
    file.close();
}

void saveData() {
    ofstream file("bank_data.txt");
    for (int i = 0; i < (int)accounts.size(); i++)
        file << accounts[i].number << '\n'
             << accounts[i].name << '|' << accounts[i].balance << '\n';
    file.close();
}

int findAccount(int n) {
    for (int i = 0; i < (int)accounts.size(); i++)
        if (accounts[i].number == n) return i;
    return -1;
}

void createAccount() {
    int n;
    string name;
    double amount;
    cout << "Enter account number: ";
    cin >> n;
    if (findAccount(n) != -1) {
        cout << "Account number already exists!\n";
        return;
    }
    cin.ignore();
    cout << "Enter customer name: ";
    getline(cin, name);
    cout << "Enter opening balance: ";
    cin >> amount;
    if (amount < 0) {
        cout << "Invalid amount!\n";
        return;
    }
    accounts.push_back(Account(n, name, amount));
    saveData();
    cout << "Account created successfully!\n";
}

void depositMoney() {
    int n;
    double amount;
    cout << "Enter account number: ";
    cin >> n;
    int i = findAccount(n);
    if (i == -1) {
        cout << "Account not found!\n";
        return;
    }
    cout << "Enter deposit amount: ";
    cin >> amount;
    if (amount <= 0) {
        cout << "Amount must be greater than zero.\n";
        return;
    }
    accounts[i].balance += amount;
    saveData();
    cout << "Deposit successful. Balance: Rs. "
         << fixed << setprecision(2) << accounts[i].balance << '\n';
}

void withdrawMoney() {
    int n;
    double amount;
    cout << "Enter account number: ";
    cin >> n;
    int i = findAccount(n);
    if (i == -1) {
        cout << "Account not found!\n";
        return;
    }
    cout << "Enter withdrawal amount: ";
    cin >> amount;
    if (amount <= 0) {
        cout << "Amount must be greater than zero.\n";
        return;
    }
    if (amount > accounts[i].balance) {
        cout << "Insufficient balance!\n";
        return;
    }
    accounts[i].balance -= amount;
    saveData();
    cout << "Withdrawal successful. Balance: Rs. "
         << fixed << setprecision(2) << accounts[i].balance << '\n';
}

void checkBalance() {
    int n;
    cout << "Enter account number: ";
    cin >> n;
    int i = findAccount(n);
    if (i == -1) {
        cout << "Account not found!\n";
        return;
    }
    cout << "\nAccount Number: " << accounts[i].number
         << "\nCustomer Name: " << accounts[i].name
         << "\nBalance: Rs. " << fixed << setprecision(2)
         << accounts[i].balance << '\n';
}

void displayAccounts() {
    if (accounts.empty()) {
        cout << "No accounts available.\n";
        return;
    }
    cout << "\nACCOUNT LIST\n";
    for (int i = 0; i < (int)accounts.size(); i++)
        cout << "Account: " << accounts[i].number
             << " | Name: " << accounts[i].name
             << " | Balance: Rs. " << fixed << setprecision(2)
             << accounts[i].balance << '\n';
}

int main() {
    loadData();
    int choice;
    do {
        cout << "\n===== BANK MANAGEMENT APPLICATION =====\n"
             << "1. Create Account\n"
             << "2. Deposit Money\n"
             << "3. Withdraw Money\n"
             << "4. Check Balance\n"
             << "5. Display All Accounts\n"
             << "6. Exit\n"
             << "Enter choice: ";
        cin >> choice;

        switch (choice) {
            case 1: createAccount(); break;
            case 2: depositMoney(); break;
            case 3: withdrawMoney(); break;
            case 4: checkBalance(); break;
            case 5: displayAccounts(); break;
            case 6: cout << "Thank you for using the bank system!\n"; break;
            default: cout << "Invalid choice. Try again.\n";
        }
    } while (choice != 6);

    return 0;
}

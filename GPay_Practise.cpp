#include <iostream>
#include <string>
using namespace std;

class User {
private:
    string name;
    string mobile;
    string password;
    int pin;
    double balance;

public:
    void registerUser(string name, string mobile, string password, int pin) {
        this->name = name;
        this->mobile = mobile;
        this->password = password;
        this->pin = pin;
        this->balance = 0.0;
    }

    string getMobile() {
        return mobile;
    }

    string getName() {
        return name;
    }

    double getBalance() {
        return balance;
    }

    bool login(string enteredPassword, int enteredPin) {
        if (enteredPassword == password && enteredPin == pin) {
            return true;
        }
        return false;
    }

    void checkBalance() {
        cout << "Current Balance: Rs. " << balance << endl;
    }

    void addMoney(double amount) {
        balance += amount;
    }

    bool withdrawMoney(double amount) {
        if (balance >= amount) {
            balance -= amount;
            return true;
        }
        return false;
    }

    bool verifyPin(int enteredPin) {
        return enteredPin == pin;
    }
};

class Transaction {
public:
    string sender;
    string receiver;
    double amount;

    void displayTransaction() {
        cout << "\n===== TRANSACTION DETAILS =====" << endl;
        cout << "Sender: " << sender << endl;
        cout << "Receiver: " << receiver << endl;
        cout << "Amount: Rs. " << amount << endl;
    }
};

int main() {
    User user[5];
    string name, mobile, password;
    int pin;

    int choice;
    int totalUsers = 0;

    do {
        cout << "\n================================" << endl;
        cout << "        SMART WALLET APP" << endl;
        cout << "================================" << endl << endl;

        cout << "1. Register" << endl;
        cout << "2. Login" << endl;
        cout << "3. Exit" << endl;

        cout << "\nEnter choice: ";
        cin >> choice;

        switch (choice) {
            // REGISTER
            case 1: {
                if (totalUsers >= 5) {
                    cout << "\nMaximum 5 users already registered!" << endl;
                    break;
                }

                cout << "\n===== REGISTER USER " << totalUsers + 1 << " =====" << endl;

                cout << "Enter name: ";
                cin >> name;

                cout << "Enter mobile number: ";
                cin >> mobile;

                // Check if mobile number is already registered
                bool alreadyExists = false;
                for (int i = 0; i < totalUsers; i++) {
                    if (user[i].getMobile() == mobile) {
                        alreadyExists = true;
                        break;
                    }
                }

                if (alreadyExists) {
                    cout << "\nA user with this mobile number is already registered!" << endl;
                    break;
                }

                cout << "Enter password: ";
                cin >> password;

                cout << "Enter pin: ";
                cin >> pin;

                user[totalUsers].registerUser(name, mobile, password, pin);
                totalUsers++;
                cout << "\nRegistration Successful!" << endl;
                break;
            }

            // LOGIN
            case 2: {
                if (totalUsers == 0) {
                    cout << "\nNo users registered yet!" << endl;
                    break;
                }

                string loginMobile;
                string loginPassword;
                int loginPin;

                cout << "\n===== LOGIN =====" << endl;

                cout << "Enter mobile number: ";
                cin >> loginMobile;

                cout << "Enter password: ";
                cin >> loginPassword;

                cout << "Enter pin: ";
                cin >> loginPin;

                int loggedInUser = -1;

                // Search for user
                for (int i = 0; i < totalUsers; i++) {
                    if (user[i].getMobile() == loginMobile &&
                        user[i].login(loginPassword, loginPin)) {
                        loggedInUser = i;
                        break;
                    }
                }

                // LOGIN SUCCESSFUL
                if (loggedInUser != -1) {
                    cout << "\nLogin Successful!" << endl << endl;
                    cout << "================================" << endl;
                    cout << "WELCOME, " << user[loggedInUser].getName() << endl;
                    cout << "================================" << endl;

                    int walletChoice;

                    // WALLET MENU
                    do {
                        cout << endl;
                        cout << "1. Check Balance" << endl;
                        cout << "2. Add Money" << endl;
                        cout << "3. Send Money" << endl;
                        cout << "4. Withdraw Money" << endl;
                        cout << "5. Logout" << endl;

                        cout << "\nEnter choice: ";
                        cin >> walletChoice;

                        switch (walletChoice) {
                            case 1: {
                                // Check Balance
                                user[loggedInUser].checkBalance();
                                break;
                            }

                            case 2: {
                                // Add Money
                                double amountToAdd;
                                cout << "Enter amount to add: ";
                                cin >> amountToAdd;

                                if (amountToAdd <= 0) {
                                    cout << "\nInvalid amount! Amount must be greater than 0." << endl;
                                    break;
                                }

                                user[loggedInUser].addMoney(amountToAdd);
                                cout << "\nAmount added successfully!" << endl;
                                user[loggedInUser].checkBalance();
                                break;
                            }

                            case 3: {
                                // Send Money
                                string receiverMobile;
                                double amount;
                                int enteredPin;

                                cout << endl << "===== SEND MONEY =====" << endl;

                                cout << "Enter receiver mobile number: ";
                                cin >> receiverMobile;

                                // Prevent sending money to yourself
                                if (receiverMobile == user[loggedInUser].getMobile()) {
                                    cout << "\nYou cannot send money to yourself!" << endl;
                                    break;
                                }

                                int receiverIndex = -1;

                                // Find receiver
                                for (int i = 0; i < totalUsers; i++) {
                                    if (user[i].getMobile() == receiverMobile) {
                                        receiverIndex = i;
                                        break;
                                    }
                                }

                                // Check if receiver exists
                                if (receiverIndex == -1) {
                                    cout << "\nReceiver not found!" << endl;
                                    break;
                                }

                                cout << "Enter amount: ";
                                cin >> amount;

                                // Validate amount
                                if (amount <= 0) {
                                    cout << "\nInvalid amount! Amount must be greater than 0." << endl;
                                    break;
                                }

                                cout << "Enter your PIN: ";
                                cin >> enteredPin;

                                // Verify sender's PIN
                                if (!user[loggedInUser].verifyPin(enteredPin)) {
                                    cout << "\nIncorrect PIN!" << endl;
                                    break;
                                }

                                // Deduct money from sender
                                if (user[loggedInUser].withdrawMoney(amount)) {
                                    // Add money to receiver
                                    user[receiverIndex].addMoney(amount);

                                    cout << "\nMoney sent successfully!" << endl;

                                    // Create transaction object when paying to another user
                                    Transaction txn;
                                    txn.sender = user[loggedInUser].getName();
                                    txn.receiver = user[receiverIndex].getName();
                                    txn.amount = amount;

                                    // Display all variable values inside Transaction class
                                    txn.displayTransaction();
                                } else {
                                    cout << "\nInsufficient balance!" << endl;
                                }

                                break;
                            }

                            case 4: {
                                // Withdraw Money
                                double withdrawAmount;
                                int enteredPin;

                                cout << endl << "===== WITHDRAW MONEY =====" << endl;
                                cout << "Enter amount to withdraw: ";
                                cin >> withdrawAmount;

                                if (withdrawAmount <= 0) {
                                    cout << "\nInvalid amount! Amount must be greater than 0." << endl;
                                    break;
                                }

                                cout << "Enter your PIN: ";
                                cin >> enteredPin;

                                if (!user[loggedInUser].verifyPin(enteredPin)) {
                                    cout << "\nIncorrect PIN!" << endl;
                                    break;
                                }

                                if (user[loggedInUser].withdrawMoney(withdrawAmount)) {
                                    cout << "\nWithdrawal successful!" << endl;
                                    cout << "Amount withdrawn: Rs. " << withdrawAmount << endl;
                                    user[loggedInUser].checkBalance();
                                } else {
                                    cout << "\nInsufficient balance!" << endl;
                                }

                                break;
                            }

                            case 5: {
                                cout << "\nLogging out..." << endl;
                                break;
                            }

                            default: {
                                cout << "\nInvalid choice!" << endl;
                                break;
                            }
                        }

                    } while (walletChoice != 5);

                }
                // LOGIN FAILED
                else {
                    cout << "\nInvalid mobile number, password, or pin!" << endl;
                }
                break;
            }

            // EXIT
            case 3: {
                cout << "\nThank you for using Smart Wallet App!" << endl;
                break;
            }

            // INVALID CHOICE
            default: {
                cout << "\nInvalid choice! Please try again." << endl;
                break;
            }
        }

    } while (choice != 3);

    return 0;
}
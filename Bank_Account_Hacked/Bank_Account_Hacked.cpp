#include <iostream>
#include <string>
using namespace std;

// Base class representing generic bank account
class BaseAccountClass {
protected:
    string accountHolderName;
    string accountNumber;
    double balance;
    bool isFlagged; // Status tracking whether account is flagged / permissions revoked

public:
    BaseAccountClass(string name, string number, double initialBalance)
        : accountHolderName(name), accountNumber(number), balance(initialBalance), isFlagged(false) {}

    virtual ~BaseAccountClass() {}

    // Non-virtual function: SendMoney
    void SendMoney(double amount) {
        if (isFlagged) {
            cout << "[ACCESS DENIED] Account " << accountNumber 
                 << " is FLAGGED! Permission revoked for SendMoney." << endl;
            return;
        }

        if (amount <= 0) {
            cout << "Invalid transfer amount: Rs " << amount << endl;
        } else if (amount <= balance) {
            balance -= amount;
            cout << "Amount sent: Rs " << amount << " | Remaining Balance: Rs " << balance << endl;
        } else {
            cout << "Insufficient balance! Current Balance: Rs " << balance << endl;
        }
    }

    // Virtual function: ReceiveMoney (Runtime Polymorphism)
    virtual void ReceiveMoney(double amount) {
        if (isFlagged) {
            cout << "[ACCESS DENIED] Account " << accountNumber 
                 << " is FLAGGED! Permission revoked for ReceiveMoney." << endl;
            return;
        }

        if (amount <= 0) {
            cout << "Invalid deposit amount: Rs " << amount << endl;
        } else {
            balance += amount;
            cout << "Amount received: Rs " << amount << " | New Balance: Rs " << balance << endl;
        }
    }

    // Virtual functions to Give and Take Permissions via Runtime Polymorphism
    virtual void givePermission() {
        isFlagged = false;
        cout << "[PERMISSION GRANTED] BaseAccount: Restrictions lifted. Account is active." << endl;
    }

    virtual void takePermission() {
        isFlagged = true;
        cout << "[PERMISSION REVOKED] BaseAccount: Account flagged! All transactions blocked." << endl;
    }

    // Display account information
    void displayStatus() const {
        cout << "------------------------------------------" << endl;
        cout << "Account Holder : " << accountHolderName << endl;
        cout << "Account Number : " << accountNumber << endl;
        cout << "Current Balance: Rs " << balance << endl;
        cout << "Account Status : " << (isFlagged ? "FLAGGED (Permissions Suspended)" : "ACTIVE (Permissions Granted)") << endl;
        cout << "------------------------------------------" << endl;
    }
};

// Derived class representing consumer bank account
class ConsumerAccountClass : public BaseAccountClass {
public:
    ConsumerAccountClass(string name, string number, double initialBalance)
        : BaseAccountClass(name, number, initialBalance) {}

    // Overriding the virtual ReceiveMoney function
    void ReceiveMoney(double amount) override {
        cout << "\n[Consumer Account Log] Processing ReceiveMoney via Runtime Polymorphism..." << endl;
        if (isFlagged) {
            cout << "[ALERT] Consumer Account (" << accountNumber << ") is currently FLAGGED." << endl;
            cout << "[SECURITY BLOCKED] Deposit of Rs " << amount << " denied due to revoked permissions." << endl;
            return;
        }
        cout << "[Consumer Account Security Check] Status clear. Depositing funds..." << endl;
        BaseAccountClass::ReceiveMoney(amount);
    }

    // Overriding givePermission to provide consumer-specific logic
    void givePermission() override {
        isFlagged = false;
        cout << "\n>>> [SECURITY OVERRIDE - Consumer Account]: Permissions RESTORED. Account UNFLAGGED. <<<" << endl;
    }

    // Overriding takePermission to provide consumer-specific logic
    void takePermission() override {
        isFlagged = true;
        cout << "\n>>> [SECURITY ALERT - Consumer Account]: SUSPICIOUS ACTIVITY! Permissions REVOKED. Account FLAGGED! <<<" << endl;
    }
};

int main() {
    cout << "==========================================" << endl;
    cout << "  BANK ACCOUNT FLAGGED / HACK SIMULATION  " << endl;
    cout << "==========================================" << endl;

    // Create an instance of ConsumerAccountClass
    ConsumerAccountClass consumerAcc("Alice Johnson", "ACC-987654321", 5000.0);

    // Upcasting: Base class pointer pointing to Derived class object
    BaseAccountClass* accountPtr = &consumerAcc;

    cout << "\n[INITIAL STATE]" << endl;
    accountPtr->displayStatus();

    // 1. Performing normal transactions with initial permissions active
    cout << "\n[1. NORMAL TRANSACTIONS]" << endl;
    accountPtr->SendMoney(1200.0);      // Calls BaseAccountClass::SendMoney
    accountPtr->ReceiveMoney(800.0);    // Dynamically dispatched to ConsumerAccountClass::ReceiveMoney

    accountPtr->displayStatus();

    // 2. Simulate account being hacked/flagged: Take permissions using Runtime Polymorphism
    cout << "\n[2. SUSPICIOUS ACTIVITY DETECTED - TAKING PERMISSIONS]" << endl;
    accountPtr->takePermission();       // Dynamically dispatched to ConsumerAccountClass::takePermission

    accountPtr->displayStatus();

    // 3. Attempting transactions while account is flagged
    cout << "\n[3. ATTEMPTING TRANSACTIONS WHILE ACCOUNT IS FLAGGED]" << endl;
    cout << "--- Attempt to SendMoney (Rs 500.00) ---" << endl;
    accountPtr->SendMoney(500.0);       // Blocked due to flagged status

    cout << "\n--- Attempt to ReceiveMoney (Rs 1000.00) ---" << endl;
    accountPtr->ReceiveMoney(1000.0);   // Blocked dynamically by ConsumerAccountClass

    accountPtr->displayStatus();

    // 4. Verification completed: Give permissions back using Runtime Polymorphism
    cout << "\n[4. IDENTITY VERIFIED - GIVING PERMISSIONS BACK]" << endl;
    accountPtr->givePermission();       // Dynamically dispatched to ConsumerAccountClass::givePermission

    accountPtr->displayStatus();

    // 5. Retrying transactions after permissions are restored
    cout << "\n[5. TRANSACTIONS AFTER RESTORING PERMISSIONS]" << endl;
    accountPtr->ReceiveMoney(1500.0);   // Dynamically dispatched (Allowed)
    accountPtr->SendMoney(300.0);       // Allowed

    cout << "\n[FINAL STATE]" << endl;
    accountPtr->displayStatus();

    return 0;
}
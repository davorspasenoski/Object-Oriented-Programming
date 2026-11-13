// Да се дефинира класа Account со следните информации:

// ownerName (string)

// amount (float)

// Потребно е да се имплементираат потребните конструктори, деструктор, getters и setters за Account (5 поени).

// Да се дефинира апстрактна класа Taxable со следните чисто виртуелни функции (5 поени):

// float getAmount() — ја враќа состојбата на сметката пред каков било данок или камата

// float getTaxedAmount() — ја враќа конечната состојба по сите пресметки на данок

// void printDetails() — печати детали за Taxable

// Да се дефинираат две класи SavingsAccount и BusinessAccount кои наследуваат од Account и Taxable (5 поени).

// За класата SavingsAccount, се чуваат следните дополнителни атрибути:

// interestRate (float) — годишната каматна стапка (пр. 0.05 за 5%)
// interestTaxRate (float) — даночната стапка применета на заработената камата, е иста за секој објект од SavingsAccount, иницијална вредност е 0.10 (10%)
// Да се имплементираат getter getInterestTaxRate() и setter setInterestTaxRate() за interestTaxRate. (5 поени)

// getTaxedAmount() се пресметува на следниов начин (5 поени):

// InterestEarned = amount * interestRate

// TaxOnInterest = interestEarned * interestTaxRate

// Конечна состојба = amount + interestEarned - taxOnInterest

 

// getAmount() ја враќа состојбата без никакви измени. (2 поени)

// printDetails() го печати секој SavingsAccount во следниот формат (2 поени):

// [ownerName] (Savings) - Interest Rate: [interestRate] - Raw Amount: [amount] - After Tax: [taxedAmount] 

// За класата BusinessAccount, се чуваат следните дополнителни атрибути:

// businessType (string) — типот на бизнис (пр. "LLC", "Corp")
// corporateTaxRate (float) — даночната стапка применета на целата состојба на сметката, е иста за секој објект од BusinessAccount, почетна вредност е 0.20 (20%)
 

// Да се имплементираат getter getCorporateTaxRate() и setter setCorporateTaxRate() за corporateTaxRate. (5 поени)

 

// getTaxedAmount() се пресметува на следниов начин (5 поени):

// TaxOnBalance = amount * corporateTaxRate

// Конечна состојба = amount - taxOnBalance

 

// getAmount() ја враќа состојбата без никакви измени. (2 поени)

 

// printDetails() го печати секој BusinessAccount во следниот формат (2 поени):

// [ownerName] (Business) - Type: [businessType] - Raw Amount: [amount] - After Tax: [taxedAmount] 

// Да се дефинира следнава глобална функција (7 поени):

// void printBusinessAccountStats(Taxable** accounts, int n)

// Оваа функција прима низа од покажувачи од Taxable објекти, ги филтрира само оние од тип BusinessAccount, ги печати нивните детали и ја пресметува и прикажува просечната конечна состојба (по данок) само за нив. Доколку нема деловни сметки, треба да се испечати пораката "There are no business accounts".

// Искористете #include <iomanip> и cout << fixed << setprecision(2) за заокружување.


#include <iostream>
#include <cstring>
#include <iomanip>
using namespace std;

class Taxable {
public:
    virtual float getAmount () const = 0;
    virtual float getTaxedAmount ()const = 0;
    virtual void printDetails()const = 0;
};

/*
TODO: Your code here!
Don't copy main function in your solution!
*/
class Taxable;
class Account {
protected:
    string ownerName;
    float amount;
public:
    Account (string ownerName = "", float amount = 0) {
        this->ownerName = ownerName;
        this->amount = amount;
    }

    [[nodiscard]] string owner_name() const {
        return ownerName;
    }

    void set_owner_name(const string &owner_name) {
        ownerName = owner_name;
    }

    [[nodiscard]] float amount1() const {
        return amount;
    }

    void set_amount(float amount) {
        this->amount = amount;
    }

    virtual float getAmount () const = 0;
    virtual float getTaxedAmount ()const = 0;
    virtual void printDetails()const = 0;

    ~Account() {}
};
class SavingsAccount : public Account, public Taxable {
private:
    float interestRate;
    static float interestTaxRate;
public:
    SavingsAccount(const string &ownerName, float amount, float interest_rate)
        : Account(ownerName, amount),
          interestRate(interest_rate) {
    }

    float getName() const {
        return interestRate;
    }

    void setName(float interest_rate) {
        interestRate = interest_rate;
    }
    float getTaxedAmount() const override {
        int zarabotka = amount * interestRate;
        int taxOnInterest = zarabotka * interestTaxRate;
        int final_boss = amount + interestRate - taxOnInterest;

        return final_boss;
    }
    float getAmount() const override {
        return amount;
    }
    void printDetails() const override {
        cout<<owner_name() << " (Savings) - Interest Rate: " << interestRate <<
            " - Raw Amount: " << amount << " - After tax: " <<getTaxedAmount();
    }
    void printBusinessAccountStats(Taxable** accounts, int n) {}
};

 float SavingsAccount :: interestTaxRate = 0.10;

class BusinessAccount : public Account, public Taxable {
private:
    string businesstype;
    static float corporateTaxRate;
public:
    BusinessAccount(const string &ownerName, float amount, const string &businesstype)
        : Account(ownerName, amount),
          businesstype(businesstype) {
    }

    string getBusinesstype1() const {
        return businesstype;
    }

    void set_businesstype(float businesstype) {
        this->businesstype = businesstype;
    }

    float getTaxedAmount() const override {
        int zarabotka = amount * corporateTaxRate;

        int final_boss = amount - zarabotka;

        return final_boss;
    }
    float getAmount() const override {
        return amount;
    }
    void printDetails() const override {
        cout<<owner_name() << " (Business) - Type: " << businesstype <<
            " - Raw Amount: " << amount << " - After tax: " <<getTaxedAmount();
    }
};

void printBusinessAccountStats(Taxable** accounts, int n) {
    float totalTaxedAmount = 0;
    int  businessCount = 0;

    for (int i=0; i<n; i++) {
        BusinessAccount * temp = dynamic_cast<BusinessAccount *>(accounts[i]);

        if (temp!=nullptr) {
            temp->printDetails();
            cout<<endl;
            totalTaxedAmount += temp ->getTaxedAmount();
            businessCount++;
        }
    }
    if (businessCount==0) {
        cout << "There are no business accounts" << endl;
    } else {
        cout << fixed << setprecision(2);
        cout << "Average taxed amount: " << (totalTaxedAmount / businessCount) << endl;
    }
}


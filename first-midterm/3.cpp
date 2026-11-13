// За потребите на еден приватен банкар кој тргува со акции, потребно е да се направи модул за менаџирање со клиентски портфолија.

// За таа цел, треба да се креира класа StockRecord. Класата треба да содржи:

// ID, кој означува која е акцијата која се тргува (низа од 12 знаци)
// Име на компанијата која ја издала акцијата (низа од 50 знаци)
// Цена според која се купени акциите (реален број)
// Моментална цена на акцијата (реален број)
// Број на акции кои се купени (цел број)
// За класата да се дефинираат потребните конструктори и set метода за моменталната цена со потпис void setNewPrice(double c) (10 поени). Исто така, да се имплементираат методи double value() и double profit(). Првата треба да ја пресметува вредноста на акциите, а втората треба да го пресметува моменталниот профит од акциите. Пресметката се врши на следниот начин (5 поени):

// Вредност = број на акции * моментална цена 
// Профит = број на акции * (моментална цена - цена по која се купени)
// Дополнително, да се преоптовари операторот << за печатење на објектот во следниот формат (5 поени): Компанија БројНаАкции КуповнаЦена МоменталнаЦена Профит

// Да се креира класа Client која содржи:

// Име и презиме на клиентот (низа од 60 знаци)
// ID на сметка (цел број)
// Низа од компании кои ги поседува клиентот (динамичка низа од објекти од класата StockRecord)
// Број на објекти во низата (цел број)
// За класата Client да се дефинираат потребните конструктори, деструктор и метода double totalValue() која ќе ја пресметува моменталната вредност на акциите кои ги поседува клиентот. Таа се пресметува како збир од вредноста на сите акции од секоја компанија од кои е составено клиентското портфолио (15 поени). Дополнително, за класата да се преоптоварат операторите:

// += за купување на нова компанија во портфолиото (додавање на нов објект од класата StockRecord во низата со компании) (10 поени)

// << за печатење на информации за портфолиото на клиентот така што во првиот ред ќе бидат прикажани ID на сметката и моменталната вредност на портфолиото одделени со празно место, а во секој нареден ред ќе бидат прикажани компаниите од кои е составено портфолиото, секоја во посебен ред (5 поени)

// Комплетна функционанлост (5 поени)

#include<iostream>
#include<cstring>
using namespace std;
class StockRecord {
private:
    char id[13];
    char ime[51];
    double cena;
    double momentalnacena;
    int brakcii;
public:
StockRecord(){};
    StockRecord(char *id, char *ime, double cena, int brakcii) {
        strcpy(this->id, id);
        strcpy(this->ime, ime);
        this->cena = cena;
        this-> brakcii = brakcii;
    }

    StockRecord(const StockRecord &sr) {
        strcpy(this->id, sr.id);
        strcpy(this->ime, sr.ime);
        this->cena = sr.cena;
        this->brakcii = sr.brakcii;
    }

    void setNewPrice(double c) {
        momentalnacena = c;
    }
    double value() {
     return brakcii * momentalnacena;
    }
    double profit() {
        return brakcii * (momentalnacena - cena);
    }

    friend ostream& operator<<(ostream& out, const StockRecord& obj) {
        double profit = (obj.momentalnacena - obj.cena) * obj.brakcii;

        out << obj.ime << " "
            << obj.brakcii << " "
            << obj.cena << " "
            << obj.momentalnacena << " "
            << profit << endl;
        return out;
    }
    int operator%(const StockRecord &sr) {
        return sr.brakcii%10;
    }

};
class Client {
private:
    char ime_prezime[61];
    int id;
    StockRecord *akcii;
    int brobjekti;
public:
    Client(){}
    Client(char ime_prezime[] = "", int id = 0) {
        strcpy(ime_prezime, ime_prezime);
        this->id = id;
        this->brobjekti = 0;
        this->akcii = NULL;
    }
    Client(const Client &c) {
        strcpy(this->ime_prezime, c.ime_prezime);
        this->id = c.id;
        this->brobjekti = c.brobjekti;
        this->akcii = new StockRecord[c.brobjekti];
        for (int i =0; i < c.brobjekti; i++) {
            this->akcii[i] = c.akcii[i];
        }
    }

    double totalValue() {
        double total = 0.0;
        for (int i = 0; i < brobjekti ; i++) {
       total = total + akcii[i].value();
        }
        return total;
    }

    Client& operator+=(const StockRecord& sr) {
        StockRecord *temp = new StockRecord[brobjekti + 1];

        for (int i = 0; i < brobjekti ; i++) {
            temp[i] = akcii[i];
        }
        temp[brobjekti] = sr;
    
        akcii = temp;
        brobjekti++;

        return *this;
    }

    friend ostream& operator<<(ostream& out, Client& c) {
        out << c.id << " " << c.totalValue() << endl;
        for (int i = 0; i < c.brobjekti; i++) {
            out << c.akcii[i];
        }

        return out;
    }
    ~Client(){}
};
int main(){

    int test;
    cin >> test;

    if(test == 1){
        double price;
        cout << "=====TEST NA KLASATA StockRecord=====" << endl;
        StockRecord sr("1", "Microsoft", 60.0, 100);
        cout << "Konstruktor OK" << endl;
        cin >> price;
        sr.setNewPrice(price);
        cout << "SET metoda OK" << endl;
    }
    else if(test == 2){
        cout << "=====TEST NA METODITE I OPERATOR << OD KLASATA StockRecord=====" << endl;
        char id[12], company[50];
        double price, newPrice;
        int n, shares;
        cin >> n;
        for(int i = 0; i < n; ++i){
            cin >> id;
            cin >> company;
            cin >> price;
            cin >> newPrice;
            cin >> shares;
            StockRecord sr(id, company, price, shares);
            sr.setNewPrice(newPrice);
            cout << sr.value() << endl;
            cout << sr;
        }
    }
    else if(test == 3){
        cout << "=====TEST NA KLASATA Client=====" << endl;
        char companyID[12], companyName[50], clientName[50];
        int clientID, n, shares;
        double oldPrice, newPrice;
        bool flag = true;
        cin >> clientName;
        cin >> clientID;
        cin >> n;
        Client c(clientName, clientID);
        cout << "Konstruktor OK" << endl;
        for(int i = 0; i < n; ++i){
            cin >> companyID;
            cin >> companyName;
            cin >> oldPrice;
            cin >> newPrice;
            cin >> shares;
            StockRecord sr(companyID, companyName, oldPrice, shares);
            sr.setNewPrice(newPrice);
            c += sr;
            if(flag){
                cout << "Operator += OK" << endl;
                flag = false;
            }
        }
        cout << c;
        cout << "Operator << OK" << endl;
    }
    return 0;

}

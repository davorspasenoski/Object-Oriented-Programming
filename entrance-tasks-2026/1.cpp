// Да се дефинира класа User во која се чуваат информации за:

// Корисничко име (низа од најмногу 50 знаци) - default вредност user
// Лозинка (низа од најмногу 50 знаци) - default вредност password
// Број на најави на корисникот во системот (цел број) - default вредност 0
// За класата да се дефинираат потребните конструктори и:

// да се преоптовари оператор << за печатење - кој печати информации за корисникот во форматот како во тест примерите
// метод bool strongPassword() - кој враќа информација дали лозинката е силна
// Една лозинка е силна доколку:

// Има најмалку 12 знаци
// Мнозинство знаци не се ниту букви ниту бројки
// Пример лозинката qwerty123456 не е силна (сите знаци се букви и бројки)
// Лозинката qwerty*_$%^&! е силна (7 од 13 знаци не се букви ниту бројки)
// Да се дополни главната функција на означеното место со читање на број N, па информации за N корисници и корисниците да се додадат во низата users.

// Помош: Може да ги користите функциите isalpha(), isdigit() или isalnum() од библиотеката ctype.


#include <iostream>
#include <cstring>
#include <cctype>
#include <ostream>

using namespace std;

/*
 * Your code here!
 * */

class User {
private:
    char ime[50];
    char lozinka[50];
    int brnajavi = 0;
public:
    User(char ime[] = "user", char lozinka[] = "password", int brnajavi = 0) {
        strcpy(this->ime,ime);
        strcpy(this->lozinka,lozinka);
        this->brnajavi = brnajavi;
    }

    friend std::ostream & operator<<(std::ostream &os, const User &obj) {

        os<<obj.ime<<" "<<obj.lozinka<<" "<<obj.brnajavi;
        return os;
    }

    bool strongPassword() {
        int znaci = 0;
        for (int i = 0; i < strlen(lozinka); i++) {
            znaci++;
        }


        int num = 0;
        for (int i = 0; i < strlen(lozinka); i++) {
            if (!isalnum(lozinka[i])) {
                num++;
            }
        }

        int dr = 0;
        for (int i = 0; i < strlen(lozinka); i++) {
            if (isdigit(lozinka[i])) {
                dr++;
            }
        }

        int br = 0;
        for (int i = 0; i < strlen(lozinka); i++) {
            if (isalpha(lozinka[i])) {
                br++;
            }
        }



        if (znaci >= 12 && num > dr && num > br) {
            return true;
        }
        return false;


    }


};
int main() {
    int n;

    User users[100];

    cin>>n;
    for (int i = 0; i < n; i++) {
        char ime[50];
        char lozinka[50];
        int brnajavi = 0;

        cin>>ime;
        cin>>lozinka;
        cin>>brnajavi;

        users[i] = User(ime,lozinka,brnajavi);


    }

    int choice;
    cin >> choice;

    if (choice == 1) {
        for (int i = 0; i < n; i++) {
            cout << users[i] << endl;
        }
    } else if (choice == 2) {
        for (int i = 0; i < n; i++) {
            if (users[i].strongPassword()) {
                cout << "STRONG" << endl;
            } else {
                cout << "WEEK" << endl;
            }
        }
    } else {
        cout << "Test default constructor" << endl;
        cout << users[n+1] << endl;
    }

    return 0;
}

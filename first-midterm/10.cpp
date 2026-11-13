// Да се креира класа Tanc во која се чуваат податоци за името на танцот и земја на потекло (низи од 15 знаци) .

// Потоа да се креирa класа Tancer во која се чуваат податоци за име и презиме (низи од максимум 20 знаци), низа од 5 танци (објекти од класата Tanc) кои дадениот танчер може да ги игра. Дополнително, за оваа класа да се обезбеди функција со потпис :

// void tancuvanje(Tancer *t, int n, char *zemja)

// што ќе ги испечати во посебен ред името и презимето на танчерите што знаат да играат барем по еден танц од земјата која е проследена како аргумент на функцијата, како и името на танцот во формат: Име Презиме, Име на танц

#include <iostream>
#include <cstring>
using namespace std;
class tanc {
private:
    char imetanc[15];
    char zemja[15];
public:
    tanc(char imetanc[] = "", char zemja[] = "") {
        strcpy(this->imetanc,imetanc);
        strcpy(this->zemja,zemja);
    }
    const char* getzemja() {
        return zemja;
    }
    const char* getimetanc() {
        return imetanc;
    }
};

class tancer {
private:
    char imetancer[15];
    char prezimetancer[15];
    tanc tanci[5];
    int brtanci;
public:
    tancer(char imetancer[] = "", char prezimetancer[] = "",tanc *tanci = NULL, int brtanci = 0) {
        strcpy(this->imetancer,imetancer);
        strcpy(this->prezimetancer,prezimetancer);
        this->brtanci = brtanci;
        if (NULL != tanci) {
            for (int i =0; i < brtanci; i++) {
                this->tanci[i] = tanci[i];
            }
        }
    }
    int getbrtanci() {
        return brtanci;
    }
    tanc getTancPoIndeks(int i)  {
        return tanci[i];
    }
    const char* getIme() {
        return imetancer;
    }
    const char* getPrezime() {
        return prezimetancer;
    }
};
void tancuvanje(tancer *t, int n, char *zemja) {
    for (int i = 0; i < n; i ++) {
        for (int j = 0; j < t[i].getbrtanci(); j++) {
            if (strcmp(t[i].getTancPoIndeks(j).getzemja(), zemja) == 0) {
                cout << t[i].getIme() << " " << t[i].getPrezime() << ", "
                     << t[i].getTancPoIndeks(j).getimetanc() << endl;
                break;
            }
        }
    }
}
int main() {
    int n;
    cin>>n;

    tancer tanceri[100];
    for (int i =0; i < n; i ++) {
        char imetancer[15];
        char prezimetancer[15];
        cin>>imetancer>>prezimetancer;


        int br_tanci_vlez = 3;
        tanc vidtanc[5];
        for (int j = 0; j < 3; j++) {
            char imetanc[15];
            char zemja[15];
            cin>>imetanc>>zemja;
            vidtanc[j] = tanc(imetanc,zemja);

        }
tanceri[i] = tancer(imetancer, prezimetancer, vidtanc, br_tanci_vlez);    }
    char prebarajZemja[16];
    cin >> prebarajZemja;
    tancuvanje(tanceri,n,prebarajZemja);

}





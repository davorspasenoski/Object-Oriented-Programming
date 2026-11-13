// Да се дефинира класата Pesna во која се чуваат информации за (5 поени):

// име на песна (динамички алоцирано поле од знаци)
// времетраење на песната во минути
// тип на песна кој може да биде: поп, рап или рок (енумерација tip)
// Да се обезбедат сите потребни методи за класата за правилно функционирање на програмата. (10 поени)

// Дополнително за оваа класа да се дефинира методот:

// pecati() - функција во која ќе се печатат одделени со цртичка(-): името на песната во наводници и времетраењето на песната со постфикс min. (5 поени)
// Да се креира класата CD во која се чуваат информации за (5 поени):

// низа од песни снимени на CD-то (Поле од најмногу 10 објекти од класата Pesna )
// број на песни снимени на CD-то
// максимално времетраење на песните на CD-то (во минути)
// Да се обезбедат сите потребни методи за класата за правилно функционирање на програмата. (5 поени)

// Дополнително за оваа класа да се дефинираат методите:

// dodadiPesna (Pesna p) - со кој се додава песната p на CDто, но само ако има доволно преостанато место (земајќи го предвид максималното времетраење на песните на CDто и времетраењата на песните на CD-то) и ако има помалку од 10 песни на CD-то. (10 поени)
// pecatiPesniPoTip(tip t) – со кој се печатат информациите за сите песни од тип t (поп, рап или рок). (10 поени)
// Комплетна функционалност (5 поени).

#include <iostream>
#include <cstring>
using namespace std;

enum tip { POP, RAP, ROK };

class Pesna {
private:
    char *ime;
    int minuti;
    tip kojtip;
public:
    Pesna(const char *novoIme = "", int minuti = 0, tip kojtip = ROK) {
        this->minuti = minuti;
        this->kojtip = kojtip;
        this->ime = new char[strlen(novoIme) + 1];
        strcpy(this->ime, novoIme);
    }


    Pesna(const Pesna &a) {
        this->minuti = a.minuti;
        this->kojtip = a.kojtip;
        this->ime = new char[strlen(a.ime) + 1];
        strcpy(this->ime, a.ime);
    }

    Pesna& operator=(const Pesna &p) {
        if (this != &p) {
            delete[] ime;
            this->minuti = p.minuti;
            this->kojtip = p.kojtip;
            this->ime = new char[strlen(p.ime) + 1];
            strcpy(this->ime, p.ime);
        }
        return *this;
    }

    ~Pesna() {
        delete[] ime;
    }

    void pecati() {
        cout << "\"" << this->ime << "\"-" << minuti << "min" << endl;
    }

    tip getPesna() {
	    return this->kojtip;
    }
    int getMinuti() {
	    return this->minuti;
    }
};

class CD {
private:
    Pesna pesni[10];
    int Broj;
    int mincd; 
public:
    CD(int maxMinuti = 0) {
        this->Broj = 0;
        this->mincd = maxMinuti;
    }

    void dodadiPesna(Pesna &p) {
        int momentalniMinuti = 0;
        for (int i = 0; i < Broj; i++) {
            momentalniMinuti += pesni[i].getMinuti();
        }

        if (Broj < 10 && (momentalniMinuti + p.getMinuti() <= mincd)) {
            pesni[Broj] = p;
            Broj++;
        }
    }

    Pesna getPesna(int i) { return pesni[i]; }
    int getBroj() { return this->Broj; }

    void pecatiPesniPoTip(tip t) {
        for (int i = 0; i < Broj; i++) {
            if (pesni[i].getPesna() == t) {
                pesni[i].pecati();
            }
        }
    }
};

int main() {
	// se testira zadacata modularno
    int testCase;
    cin >> testCase;

	int n, minuti, kojtip;
	char ime[50];

	if(testCase == 1) {
        cout << "===== Testiranje na klasata Pesna ======" << endl;
        cin >> ime;
        cin >> minuti;
        cin >> kojtip; //se vnesuva 0 za POP,1 za RAP i 2 za ROK
        Pesna p(ime,minuti,(tip)kojtip);
		p.pecati();
    } else if(testCase == 2) {
        cout << "===== Testiranje na klasata CD ======" << endl;
		CD omileno(20);
		cin>>n;
			for (int i=0;i<n;i++){
				cin >> ime;
				cin >> minuti;
				cin >> kojtip; //se vnesuva 0 za POP,1 za RAP i 2 za ROK
				Pesna p(ime,minuti,(tip)kojtip);
				omileno.dodadiPesna(p);
			}
        	for (int i=0; i<n; i++)
				(omileno.getPesna(i)).pecati();
	}
    else if(testCase == 3) {
        cout << "===== Testiranje na metodot dodadiPesna() od klasata CD ======" << endl;
		CD omileno(20);
		cin>>n;
			for (int i=0;i<n;i++){
				cin >> ime;
				cin >> minuti;
				cin >> kojtip; //se vnesuva 0 za POP,1 za RAP i 2 za ROK
				Pesna p(ime,minuti,(tip)kojtip);
				omileno.dodadiPesna(p);
			}
        	for (int i=0; i<omileno.getBroj(); i++)
				(omileno.getPesna(i)).pecati();
    }
    else if(testCase == 4) {
        cout << "===== Testiranje na metodot pecatiPesniPoTip() od klasata CD ======" << endl;
		CD omileno(20);
		cin>>n;
			for (int i=0;i<n;i++){
				cin >> ime;
				cin >> minuti;
				cin >> kojtip; //se vnesuva 0 za POP,1 za RAP i 2 za ROK
				Pesna p(ime,minuti,(tip)kojtip);
				omileno.dodadiPesna(p);
			}
        cin>>kojtip;
        omileno.pecatiPesniPoTip((tip)kojtip);

    }
    else if(testCase == 5) {
        cout << "===== Testiranje na metodot pecatiPesniPoTip() od klasata CD ======" << endl;
		CD omileno(20);
		cin>>n;
			for (int i=0;i<n;i++){
				cin >> ime;
				cin >> minuti;
				cin >> kojtip; //se vnesuva 0 za POP,1 za RAP i 2 za ROK
				Pesna p(ime,minuti,(tip)kojtip);
				omileno.dodadiPesna(p);
			}
        cin>>kojtip;
        omileno.pecatiPesniPoTip((tip)kojtip);

    }

return 0;
}

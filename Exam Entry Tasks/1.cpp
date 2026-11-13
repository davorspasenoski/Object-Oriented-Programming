// // Да се дефинира класа Song за претставување на информации за песна.
// // Во класата се чуваат следните информации:
// // - име на песната (string)
// // - број на слушања (int)
// // - број на лајкови (int)
// // - времетраење на песната во секунди (int)
// // За класата да се имплементираат:
// // - Потребните конструктори, set и get методи
// // - Метод void print() const за печатење на информациите за песната во прегледен формат: име, број на слушања, број на лајкови и времетраење.

// // Да се дефинира класа Playlist за претставување на музичка плејлиста.
// // Во класата се чуваат следните информации:
// // - име на плејлистата (string)
// // - динамички алоцирана низа од песни Song* (не е дозволено користење на std::vector)
// // - број на песни во плејлистата (int)

// // За класата да се имплементираат:

// // - Потребните конструктори
// // - Метод double playlistEngagement() const кој го пресметува степенот на интеракција на корисниците со плејлистата според формулата:
// // playlistEngagement = (вкупно слушања + 2 * вкупно лајкови) / вкупно времетраење
// // Доколку вкупното времетраење на песните во плејлистата е 0, методот враќа 0.
// // - Метод void print() const кој го печати името на плејлистата, а потоа секоја песна во форматот зададен во Song::print(). Песните се печатат во истиот редослед како што се додадени во низата.
// На крајот да се испечати степенот на интеракција на корисниците со плејлистата.
// // - Оператор Playlist& operator+=(const Song& s) кој додава нова песна во плејлистата, односно ја проширува динамичката низа за еден елемент.
// // Во функцијата main() каде што е означено треба од тастатура да се прочитаат информации за N песни, да се формира плејлиста со тие песни со користење на операторот +=. 
// Потоа  на стандарден излез да се испечатат податоците за плејлистата, вклучувајќи ги и податоците за сите нејзини песни.

#include <iostream>
#include <string>
#include <iomanip>
using namespace std;
class Song {
private:
    string ime;
    int slusanja;
    int lajkovi;
    int vremetraenje;
public:
    Song(string ime = "", int slusanja = 0, int lajkovi = 0, int vremetraenje = 0) {
        this->ime = ime;
        this->slusanja = slusanja;
        this->lajkovi = lajkovi;
        this->vremetraenje = vremetraenje;
    }

    Song(const Song &s) {
        this->ime = s.ime;
        this->slusanja = s.slusanja;
        this->lajkovi = s.lajkovi;
        this->vremetraenje = s.vremetraenje;
    }

    [[nodiscard]] string getime() const {
        return ime;
    }

    [[nodiscard]] int getslusanja() const {
        return slusanja;
    }

    [[nodiscard]] int getlajkovi() const {
        return lajkovi;
    }

    [[nodiscard]] int getvremetraenje() const {
        return vremetraenje;
    }

    void set_ime(const string &ime) {
        this->ime = ime;
    }

    void set_slusanja(int slusanja) {
        this->slusanja = slusanja;
    }

    void set_lajkovi(int lajkovi) {
        this->lajkovi = lajkovi;
    }

    void set_vremetraenje(int vremetraenje) {
        this->vremetraenje = vremetraenje;
    }


    void print()const {
        //Brala_Moma_Kapini - listens: 1000, likes: 150, duration: 200
        cout<<ime<<" - listens: "<<slusanja<<", likes: "<<lajkovi<<", duration: "<<vremetraenje<<endl;
    }
};

class Playlist {
private:
    string imeplejlista;
    Song *pesni;
    int brpesni;
public:
    Playlist(string imeplejlista = "") {
        this->imeplejlista = imeplejlista;
        this->pesni = nullptr;
        this->brpesni = 0;
    }

    Playlist(const Playlist &p) {
        this->imeplejlista = p.imeplejlista;
        this->brpesni = p.brpesni;
        if (p.brpesni > 0) {
            this->pesni = new Song[brpesni];
            for (int i = 0; i < brpesni; i++) {
                pesni[i] = p.pesni[i];
            }
        }else {
            pesni = nullptr;
        }
    }

    Playlist& operator = (const Playlist& p) {
        if (this != &p) {
            delete[] pesni;
            this->imeplejlista = p.imeplejlista;
            this->brpesni = p.brpesni;
            if (p.brpesni > 0) {
                this->pesni = new Song[brpesni];
                for (int i = 0; i < brpesni; i++) {
                    pesni[i] = p.pesni[i];
                }
            }else {
                pesni = nullptr;
            }
        }
        return *this;
    }

    double playlistEngagement() const {
        double vkupnoslusanja = 0;
        double vkupnolajkovi = 0;
        double vkupnovreme = 0;

        for (int i = 0; i < brpesni; i++) {
            vkupnolajkovi = vkupnolajkovi + pesni[i].getlajkovi();
            vkupnoslusanja = vkupnoslusanja + pesni[i].getslusanja();
            vkupnovreme = vkupnovreme + pesni[i].getvremetraenje();
        }

        if (vkupnovreme > 0) {
            //(вкупно слушања + 2 * вкупно лајкови) / вкупно времетраење
            return (vkupnoslusanja + 2 * vkupnolajkovi) / vkupnovreme;
        }else {
            return 0.0;
        }
    }

    void print() const {
        cout<<"Playlist: "<<imeplejlista<<endl;
        if (brpesni > 0) {
            for (int i = 0; i < brpesni; i++) {
                pesni[i].print();
            }
        }else {
            cout<<"No songs in playlist"<<endl;
        }

        cout<<"Playlist engagement: "<<fixed<<setprecision(2)<<playlistEngagement()<<endl;
    }


    Playlist& operator+=(const Song& s) {
        Song* temp = new Song[brpesni + 1];

        for (int i = 0; i < brpesni; i++) {
            temp[i] = pesni[i];
        }

        temp[brpesni] = s;
        delete[] pesni;
        pesni = temp;
        brpesni++;
        return *this;
    }
};
int main() {
    int testCase;
    cin >> testCase;

    if (testCase == 1) {
        // TODO your code HERE!

        string ime;
        cin>>ime;
        int n;
        cin>>n;

        Playlist p(ime);
        for (int i = 0; i < n; i++) {
            string ime;
            int slusanja;
            int lajkovi;
            int vremetraenje;

            cin>>ime;
            cin>>slusanja;
            cin>>lajkovi;
            cin>>vremetraenje;

            Song s(ime,slusanja,lajkovi,vremetraenje);
            p += s;

        }

        p.print();
    } else if(testCase == 2) {
        Playlist original("Original");
        original += Song("Song A", 500, 100, 180);
        original += Song("Song B", 300, 50, 200);

        {
            Playlist copy(original);
            copy += Song("Song C", 100, 20, 150);

            cout << "=== copy (inside scope) ===" << endl;
            copy.print();
            cout << endl;
        }

        cout << "=== original (after copy destroyed) ===" << endl;
        original.print();
    } else if (testCase == 3) {
        Playlist *p1 = new Playlist("P1");
        *p1 += Song("Alpha", 900, 180, 240);
        *p1 += Song("Beta", 600, 120, 190);

        Playlist *p2 = new Playlist("P2");
        *p2 += Song("Gamma", 200, 40, 160);

        *p2 = *p1;

        delete p1;

        cout << "=== p2 (after p1 deleted, must still be intact) ===" << endl;
        p2->print();
        cout << endl;

        *p2 = *p2;
        cout << "=== p2 after self-assignment ===" << endl;
        p2->print();

        delete p2;

        return 0;
    }
}

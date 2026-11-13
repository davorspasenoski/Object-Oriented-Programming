// Да се имплементира класа List во којашто ќе се чуваат информации за:

// броеви што се дел од листата (динамички алоцирана низа од цели броеви)
// бројот на броеви што се дел од листата
// За класата да се дефинираат следните методи:

// конструктор (со аргументи), copy-конструктор, деструктор, оператор =
// void pecati()метод што ќе ги печати информациите за листата во форматот: [број на елементи во листата]: x1 x2 .. xn sum: [сума] average: [просек]
// int sum() метод што ја враќа сумата на елементите во листата
// double average() метод што ќе го враќа просекот на броевите во листата
// Дополнително, креирајте класата ListContainer, во која што ќе се чуваат информации за:

// низа од листи (динамички алоцирана низа од објекти од класата List)
// број на елементи во низата од листи (цел број)
// број на обиди за додавање на листа во контејнерот (цел број првично поставен на нула)
// За класата потребно е да ги дефинирате следните методи:

// конструктор (default), copy-конструктор, деструктор, оператор =
// void pecati() метод што ќе ги печати информациите за контејнерот во форматот: List number: [реден број на листата] List info: [испечатени информации за листата со методот List::pecati()] \n sum: [сума] average: [просек]
// доколку контејнерот е празен се печати само порака The list is empty.
// void addNewList(List l) метод со којшто се додава листа во контејнерот
// Напомена: една листа се додава во контејнерот ако и само ако има различна сума од сите листи што се веќе додадени во контејнерот
// int sum() метод што ја враќа сумата на сите елементи во сите листи
// double average() метод што го враќа просекот на сите елементи во сите листи во контејнерот


#include <iostream>
#include <cstring>

using namespace std;

class List {
private:
    int *broevi;
    int n;

public:
    List() {
        this->n = 0;
        this->broevi = nullptr;
    }

    List(int *niza, int n) {
        this->n = n;
        this->broevi = new int[n];
        for (int i = 0; i < n; i++) {
            this->broevi[i] = niza[i];
        }
    }

    List(const List &other) {
        this->n = other.n;
        if (other.n > 0) {
            this->broevi = new int[other.n];
            for (int i = 0; i < other.n; i++) {
                this->broevi[i] = other.broevi[i];
            }
        } else {
            this->broevi = nullptr;
        }
    }

    List& operator=(const List &other) {
        if (this != &other) {
            delete[] broevi;
            this->n = other.n;
            if (other.n > 0) {
                this->broevi = new int[other.n];
                for (int i = 0; i < other.n; i++) {
                    this->broevi[i] = other.broevi[i];
                }
            } else {
                this->broevi = nullptr;
            }
        }
        return *this;
    }

    ~List() {
        delete[] broevi;
    }

    int sum() const {
        int s = 0;
        for (int i = 0; i < n; i++) s += broevi[i];
        return s;
    }

    double average() const {
        if (n == 0) return 0;
        return (double)sum() / n;
    }

    void pecati() const {
        cout << n << ": ";
        for (int i = 0; i < n; i++) cout << broevi[i] << " ";
        cout << "sum: " << sum() << " average: " << average() << endl;
    }

    int getBrBroevi() const { return n; }
};

class ListContainer {
private:
    List *listi;
    int n;
    int brObidi;

public:
    ListContainer() {
        this->n = 0;
        this->listi = nullptr;
        this->brObidi = 0;
    }

    ListContainer(const ListContainer &other) {
        this->n = other.n;
        this->brObidi = other.brObidi;
        this->listi = new List[this->n];
        for (int i = 0; i < this->n; i++) {
            this->listi[i] = other.listi[i];
        }
    }

    ListContainer& operator=(const ListContainer &other) {
        if (this != &other) {
            delete[] listi;
            this->n = other.n;
            this->brObidi = other.brObidi;
            this->listi = new List[this->n];
            for (int i = 0; i < this->n; i++) {
                this->listi[i] = other.listi[i];
            }
        }
        return *this;
    }

    ~ListContainer() {
        delete[] listi;
    }

    void addNewList(List l) {
        brObidi++;
        // Проверка дали веќе постои листа со иста сума
        for (int i = 0; i < n; i++) {
            if (listi[i].sum() == l.sum()) {
                return; // Не ја додаваме
            }
        }

        // Реалокација
        List *tmp = new List[n + 1];
        for (int i = 0; i < n; i++) {
            tmp[i] = listi[i];
        }
        tmp[n] = l;
        delete[] listi;
        listi = tmp;
        n++;
    }

    int sum() const {
        int s = 0;
        for (int i = 0; i < n; i++) s += listi[i].sum();
        return s;
    }

    double average() const {
        int vkSuma = 0;
        int vkElementi = 0;
        for (int i = 0; i < n; i++) {
            vkSuma += listi[i].sum();
            vkElementi += listi[i].getBrBroevi();
        }
        if (vkElementi == 0) return 0;
        return (double)vkSuma / vkElementi;
    }

    void print() {
        if (n == 0) {
            cout << "The list is empty" << endl;
            return;
        }
        for (int i = 0; i < n; i++) {
            cout << "List number: " << i + 1 << " List info: ";
            listi[i].pecati();
        }
        cout << "Sum: " << sum() << " Average: " << average() << endl;
        cout << "Successful attempts: " << n << " Failed attempts: " << brObidi - n << endl;
    }
};
int main() {

    ListContainer lc;
    int N;
    cin>>N;

    for (int i=0;i<N;i++) {
        int n;
        int niza[100];

        cin>>n;

        for (int j=0;j<n;j++){
            cin>>niza[j];

        }

        List l=List(niza,n);

        lc.addNewList(l);
    }


    int testCase;
    cin>>testCase;

    if (testCase==1) {
        cout<<"Test case for operator ="<<endl;
        ListContainer lc1;
        lc1.print();
        cout<<lc1.sum()<<" "<<lc.sum()<<endl;
        lc1=lc;
        lc1.print();
        cout<<lc1.sum()<<" "<<lc.sum()<<endl;
        lc1.sum();
        lc1.average();

    }
    else {
        lc.print();
    }
}

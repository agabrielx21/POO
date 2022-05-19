#include <bits/stdc++.h>
#include <string>
using namespace std;
class IoBase{
public:
    virtual istream &read(istream &is) { // nu este nevoie de obiectul citit, pt ca avem this
        return is; // vom vedea ca in interfete deseori nu avem functionalitati
    }

    // metoda scriere
    virtual ostream &write(ostream &os) const { // nu este nevoie de obiectul citit, pt ca avem this
        return os; // vom vedea ca in interfete deseori nu avem functionalitati
    }

    // ...
    friend ostream &operator<<(ostream &os, const IoBase &base) {
        return base.write(os);
    }

    friend istream &operator>>(istream &is, IoBase &base) {
        return base.read(is);
    }
};

template<typename T>
istream &operator>>(istream &is, vector<T> &vec) {
    // empty vector:
    vec.clear();
    // read length:
    int n;
    cout << "Introduceti numarul de elemente: ";
    cin >> n;
    // read items
    for (int i = 0; i < n; ++i) {
        T var;
        cin >> var;
        vec.push_back(var);
    }
    return is;
}

template<typename T>
ostream &operator<<(ostream &os, const vector<T> &vec) {
    os << "[ ";
    for(auto& var : vec) {
        os << var << " ; ";
    }
    os << ']';

    return os;
}

class Statie : public IoBase{
protected:
        string strada,nume;
        int numar, sector;
        vector <int> linii;
        unsigned int ID;
        static unsigned int staticID;
        string serie;
    public:
        Statie() : ID(++staticID){}

    Statie(const string &strada, const string &nume, int numar, int sector, const vector<int> &linii, unsigned int id,
           const string &serie);

    istream &read(istream &is) override;

    virtual string generareSerie(){}

    const string &getStrada() const;

    const string &getNume() const;

    const vector<int> &getLinii() const;

    void setNume(const string &nume);

    unsigned int getId() const;

    const string &getSerie() const;

    void setSerie(const string &serie);

    ostream &write(ostream &os) const override;

};

class Urbana : public Statie {
public:
    Urbana() {}

    Urbana(const string &strada, const string &nume, int numar, int sector, const vector<int> &linii, unsigned int id,
           const string &serie) : Statie(strada, nume, numar, sector, linii, id, serie) {}

    istream &read(istream &is) override {
        Statie::read(is);
        return is;
    }

    ostream &write(ostream &os) const override {
        Statie::write(os);
        return os;
    }

    string generareSerie() override {
    string serie;
    string x = to_string(this->ID);
    serie = "<SU><" + x + ">";
    return serie;
    }


};

class ExtraUrbana : public Statie {
public:
    ExtraUrbana(){};

    ExtraUrbana(const string &strada, const string &nume, int numar, int sector, const vector<int> &linii,
                unsigned int id, const string &serie) : Statie(strada, nume, numar, sector, linii, id, serie) {}

    istream &read(istream &is) override {
        Statie::read(is);
        return is;
    }

    ostream &write(ostream &os) const override {
        Statie::write(os);
        return os;
    }

    string generareSerie() override {
        string serie;
        string x = to_string(this->ID);
        serie = "<SE><" + x + "> ";
        return serie;
    }



};

unsigned int Statie::staticID = 0;

Statie::Statie(const string &strada, const string &nume, int numar, int sector, const vector<int> &linii,
               unsigned int id, const string &serie) : strada(strada), nume(nume), numar(numar), sector(sector),
                                                       linii(linii), ID(++staticID), serie(serie) {}

unsigned int Statie::getId() const {
    return ID;
}

const string &Statie::getSerie() const {
    return serie;
}

istream &Statie::read(istream &is) {
    IoBase::read(is);
    cout << "Nume : ";
    is >> nume;
    cout << "Strada : ";
    is >> strada;
    cout << "Numar : ";
    is >> numar;
    cout << "Sector : ";
    is >> sector;
    cout << "Introduceti nr linii : ";
    int n,linie;
    cin >> n;
    for(int i=0 ; i<n; i++){
        cin >> linie;
        linii.push_back(linie);
    }
    return is;
}

ostream &Statie::write(ostream &os) const {
    IoBase::write(os);
    cout << "Nume statie : ";
    os << nume << endl;
    cout << "Nume strada : ";
    os << strada << endl;
    cout << "Numar strada : ";
    os << numar << endl;
    cout << "Sector : ";
    os << sector << endl;
    cout << "Seria statiei : ";
    os << serie << endl;
    cout << "Linii statie: ";
    for(auto item: linii)
        cout << item << " ";
    cout << endl;
    return os;
}

void Statie::setSerie(const string &serie) {
    Statie::serie = serie;
}

const string &Statie::getNume() const {
    return nume;
}

void Statie::setNume(const string &nume) {
    Statie::nume = nume;
}

const string &Statie::getStrada() const {
    return strada;
}

const vector<int> &Statie::getLinii() const {
    return linii;
}

shared_ptr<Statie> citireStatii (){
    int type;
    cout<<"1.Urbana\n2.ExtraUrbana";
    shared_ptr<Statie> s;
    cin >> type;
    if(type == 1)
        s = make_shared<Urbana>();
    else if(type == 2)
        s = make_shared<ExtraUrbana>();
    else return nullptr;
    cin >> *s;
    s->setSerie(s->generareSerie());
    return s;

}

class Menu {
private:
    vector <shared_ptr<Statie>> statii;
public:
    void showOptions(){
        cout << "Choose your option: ";
        cout << "1. Adaugare statie" << endl;
        cout << "2. Afisare statii" << endl;
        cout << "3. Afisare dupa .. " << endl;
        cout << "4. Afisare statii prin care trece un autobuz " << endl;
        cout << "5. Estimare pret intre doua statii" << endl;

    }
    void run(){
        showOptions();
        int option;
        cin >> option;
        while ( 0<option && option<6) {
            if(option == 1)
                citire();
            else if(option == 2)
                afisare();
            else if(option == 3)
                afisare2();
            else if(option == 4)
                afisareAutobuz();
            else if(option == 5)
                pret();
            else {
                cout << "Programul s-a incheiat cu succes !" ;
                break;
            }
            showOptions();
            cin >> option;
    } }
    void citire(){
        statii.push_back(citireStatii());
    }
    void afisare(){
        for(int i=0; i<statii.size(); i++)
            cout << *statii[i];
    }

    void afisare2(){
        cout << "Alegere detalii\n1.Numele\n2.Adresa\n3.Codul stației";
        int optiune;
        cin >> optiune;
        if(optiune == 1){
            cout << "Introduceti numele dupa care se va face cautarea: ";
            string name;
            cin >> name;
            for(int i=0; i<statii.size(); i++){
                if(statii[i]->getNume() == name)
                    cout << *statii[i];
            }
        }
        else if(optiune == 2){
            cout << "Introduceti strada dupa care se va face cautarea: ";
            string street;
            cin >> street;
            for(int i=0; i<statii.size(); i++){
                if(statii[i]->getStrada() == street)
                    cout << *statii[i];
            }
        }
        else if(optiune == 3){
            cout << "Introduceti codul statiei : ";
            string n;
            cin >> n;
            for(int i=0; i<statii.size(); i++){
                if(statii[i]->getSerie() == n)
                    cout << *statii[i];
            }
        }
    }
    void afisareAutobuz(){
        cout << "Introduceti nr. traseului ";
        int n;
        cin >> n;
        for(int i=0; i<statii.size(); i++){
            vector <int> copy = statii[i]->getLinii();
            for (auto x : copy)
                if(n==x){
                   cout << statii[i]->getNume() << " ";
        }

    } }
    void pret(){
        int U=0,EU=0;
        float pret = 2;
        vector <int> statia1,statia2;
        string s1,s2;
        cout << "Introduceti statia de plecare :" ;
        cin >> s1;
        cout << "Introduceti statia de sosire : ";
        cin >> s2;
        bool linieDirecta = false;
        for(int i=0; i<statii.size(); i++){
            if(statii[i]->getNume() == s1) {
                statia1 = statii[i]->getLinii();
                auto* urban = dynamic_cast<Urbana*>(statii[i].get());
                auto* extra = dynamic_cast<ExtraUrbana*>(statii[i].get());
                if(urban!=nullptr)
                    U++;
                if(extra!= nullptr)
                    EU++;
            }
            if(statii[i]->getNume() == s2) {
                statia2 = statii[i]->getLinii();
                auto* urban = dynamic_cast<Urbana*>(statii[i].get());
                auto* extra = dynamic_cast<ExtraUrbana*>(statii[i].get());
                if(urban!=nullptr)
                    U=U+1;
                if(extra!= nullptr)
                    EU=EU+1;
            }
        }
        for(auto x: statia1)
            for(auto y:statia2)
                if(x==y)
                    linieDirecta = true;
        if(U==2 && EU==0 && linieDirecta == 0)
            pret = 2.3;
        if(U==0 && EU==2 && linieDirecta == 1)
            pret = 2.4;
        if(U==0 && EU==2 && linieDirecta == 0)
            pret = 2.5;
        if(U==1 && EU==1 && linieDirecta == 1)
            pret = 2.6;
        if(U==1 && EU==1 && linieDirecta == 0)
            pret = 2.8;
    }
};

int main(){
    Menu meniu;
    meniu.run();
    return 0;
}

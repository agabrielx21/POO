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

class Bilet : public IoBase{
    protected:
        string plecare,sosire,serie;
        int luna,an,zi,ora;
        int cod;
        int durata;
        int distanta;
        float pret;
        int clasa;
        static unsigned int staticID;
        unsigned int id;

public:

    Bilet() : id(++staticID) {}

    Bilet(const string &plecare, const string &sosire, const string &serie, int luna, int an, int zi, int ora, int cod,
          int durata, int distanta, float pret, int clasa, unsigned int id) : plecare(plecare), sosire(sosire),
                                                                              serie(serie), luna(luna), an(an), zi(zi),
                                                                              ora(ora), cod(cod), durata(durata),
                                                                              distanta(distanta), pret(pret),
                                                                              clasa(clasa), id(++staticID) {}


    istream &read(istream &is) override {
        IoBase::read(is);
        cout << "Introduceti statia de plecare : " ;
        is >> plecare;
        cout << "Introduceti statia de sosire : ";
        is >> sosire;
        cout << "Introduceti ziua,luna si anul calatoriei: ";
        is >> zi >> luna >> an;
        cout << "Introduceti ora calatoriei : ";
        is >> ora;
        cout << "Introduceti codul trenului : ";
        is >> cod;
        cout << "Introduceti durata calatoriei exprimata in minute : ";
        is >> durata;
        cout << "Introduceti distanta calatoriei exprimata in kilometri : ";
        is >> distanta;
        cout << "Introduceti clasa : ";
        is >> clasa;
        return is;
    }

    ostream &write(ostream &os) const override {
        IoBase::write(os);
        cout << "Statia de plecare:";
        os << plecare << endl;
        cout << "Statia de sosire:";
        os << sosire << endl;
        cout << "Ziua,luna si anul calatoriei: ";
        os << zi << " " << luna << " " << an << endl;
        cout << "Ora calatoriei : ";
        os << ora << endl;
        cout << "Codul trenului:";
        os << cod << endl;
        cout << "Durata (minute) :";
        os << durata << endl;
        cout << "Distanta :";
        os << distanta << endl;
        cout << "Clasa: ";
        os << clasa << endl;
        cout << "Seria: ";
        os << serie << endl;
        cout << "Pret: ";
        os << pret << endl;
        cout << "ID: ";
        os << id << endl;
        return os;
    }
    virtual float calculatorPret(){}
    virtual string generareSerie(){}

    float getPret() const {
        return pret;
    }

    const string &getSerie() const {
        return serie;
    }

    int getCod() const {
        return cod;
    }

    int getDistanta() const {
        return distanta;
    }

    unsigned int getId() const {
        return id;
    }



};

unsigned int Bilet::staticID = 0;



class Regio : public Bilet {
public:
    Regio(){}

    Regio(const string &plecare, const string &sosire, const string &serie, int luna, int an, int zi, int ora, int cod,
          int durata, int distanta, float pret, int clasa, unsigned int id) : Bilet(plecare, sosire, serie, luna, an,
                                                                                    zi, ora, cod, durata, distanta,
                                                                                    pret, clasa, id) {}

    istream &read(istream &is) override {
        return Bilet::read(is);
    }

    ostream &write(ostream &os) const override {
        return Bilet::write(os);
    }

    float calculatorPret() override{
        pret = distanta * 39 / 100;
        if(clasa == 1)
            pret = pret * 12 / 10;
        return pret;
    }
    string generareSerie() override{
        string series = to_string(this->id);
        if (clasa == 1)
            serie = "<R><I>-<" + series + ">";
        else serie = "<R><II>-<" + series + ">";
        return serie;
    }

};
class InterRegio : public Bilet {
private:
    int numarLoc;
public:
    InterRegio(){}

    InterRegio(const string &plecare, const string &sosire, const string &serie, int luna, int an, int zi, int ora,
               int cod, int durata, int distanta, float pret, int clasa, unsigned int id, int numarLoc) : Bilet(plecare,
                                                                                                                sosire,
                                                                                                                serie,
                                                                                                                luna,
                                                                                                                an, zi,
                                                                                                                ora,
                                                                                                                cod,
                                                                                                                durata,
                                                                                                                distanta,
                                                                                                                pret,
                                                                                                                clasa,
                                                                                                                id),
                                                                                                          numarLoc(
                                                                                                                  numarLoc) {}

    istream &read(istream &is) override {
        Bilet::read(is);
        cout << "Introduceti numarul locului: ";
        is >> numarLoc;
        return is;
    }

    ostream &write(ostream &os) const override {
        Bilet::write(os);
        cout << "Numarul locului: ";
        os << numarLoc;
        return os;
    }

    string generareSerie() override{
        string series = to_string(this->id);
        if (clasa == 1)
            serie = "<IR><I>-<" + series + ">";
        else serie = "<IR><II>-<" + series +">";
        return serie;
    }

    float calculatorPret() override{
        pret = distanta * 7 / 10;
        if(clasa == 1)
            pret = pret * 12 / 10;
        return pret;
    }

};
shared_ptr<Bilet> citireBilet(){
    int tip;
    cout<<"1.Regio\n2.InterRegio";
    cin>>tip;
    shared_ptr<Bilet> b;
    if(tip==1){
        b = make_shared<Regio>();
    } else if (tip==2){
        b = make_shared<InterRegio>();
    }  else {
        cout << "Categorie gresita! ";
        return nullptr;
    }
    cin >> *b;
    b->generareSerie();
    b->calculatorPret();
    return b;
}

class Meniu{
private:
    vector <shared_ptr<Bilet>> bilete;
public:
    void showOptions(){
        cout << "Choose your option: ";
        cout << "1. Adaugare bilet" << endl;
        cout << "2. Afisare bilete" << endl;
        cout << "3. Afisare bilete dupa codul trenului" << endl;
        cout << "4. Afisare bilete dupa distanta" << endl;
        cout << "5. Stergere bilet dupa serie" << endl;

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
                afisareCod();
            else if(option == 4)
                afisareDistanta();
            else if(option == 5)
                stergere();
            else {
                cout << "Programul s-a incheiat cu succes !" ;
                break;
            }
            showOptions();
            cin >> option;
        } }
    void citire(){
        bilete.push_back(citireBilet());

    }
    void afisare(){
        for(int i=0; i<bilete.size(); i++)
            cout<< *bilete[i];
    }
    void afisareCod() {
        int cod;
        cout << "Introduceti cod";
        cin >> cod;
        for (int i = 0; i < bilete.size(); i++) {
            if (bilete[i]->getCod() == cod) {
                cout << *bilete[i] << endl;
            }
        } }
        void afisareDistanta() {
            int dis;
            cout << "Introduceti distanta de comparat";
            cin >> dis;
            for (int i = 0; i < bilete.size(); i++) {
                if (bilete[i]->getDistanta() > dis)
                    cout << *bilete[i] << endl;
            }
        }
        void stergere() {
            string serie;
            cout << "Introduceti seria";
            cin >> serie;
            for (auto it = bilete.begin(); it != bilete.end(); ++it) {
                if (it->get()->getSerie() == serie) {
                    bilete.erase(it, it + 1);
                    break;
                }
            }
        }

};
int main(){

    Meniu meniu;
    meniu.run();
    return 0; }


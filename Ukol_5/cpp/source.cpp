#include <iostream>
#include <vector>

//  třída Organismus
class Organismus {
public:
    virtual void aktualizuj() = 0;
    virtual ~Organismus() {}
};

//Třída Zvire (dědí z Organismus)
class Zvire : public Organismus {
protected:
    int energie;
public:
    Zvire(int e) : energie(e) {}
    virtual void pohyb() = 0;
};

// Třída Rostlina (dědí z Organismus)
class Rostlina : public Organismus {
public:
    void aktualizuj() override {
        std::cout << "Rostlina roste.\n";
    }
};

// Třída Bylozravec (dědí z Zvire)
class Bylozravec : public Zvire {
public:
    Bylozravec(int e) : Zvire(e) {}
    void pohyb() override {
        std::cout << "Býložravec se pohybuje.\n";
    }
    void aktualizuj() override {
        std::cout << "Býložravec se krmí.\n";
    }
};

// Třída Masozravec (dědí z Zvire)
class Masozravec : public Zvire {
public:
    Masozravec(int e) : Zvire(e) {}
    void pohyb() override {
        std::cout << "Masožravec loví.\n";
    }
    void aktualizuj() override {
        std::cout << "Masožravec se krmí.\n";
    }
};

// Třída Prostredi (správa ekosystému)
class Prostredi {
private:
    std::vector<Organismus*> organismy;
public:
    void pridatOrganismus(Organismus* o) {
        organismy.push_back(o);
    }
    void aktualizuj() {
        for (auto o : organismy) {
            o->aktualizuj();
        }
    }
};


int main() {
    Prostredi ekosystem;
    Rostlina r;
    Bylozravec b(100);
    Masozravec m(200);
    
    ekosystem.pridatOrganismus(&r);
    ekosystem.pridatOrganismus(&b);
    ekosystem.pridatOrganismus(&m);
    
    ekosystem.aktualizuj();
    return 0;
}

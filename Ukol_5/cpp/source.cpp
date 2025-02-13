// organismus.h
#ifndef ORGANISMUS_H
#define ORGANISMUS_H

class Organismus {
public:
    virtual void aktualizuj() = 0;
    virtual ~Organismus() {}
};

#endif // ORGANISMUS_H

// zvire.h
#ifndef ZVIRE_H
#define ZVIRE_H

#include "organismus.h"

class Zvire : public Organismus {
protected:
    int energie;
public:
    Zvire(int e) : energie(e) {}
    virtual void pohyb() = 0;
};

#endif // ZVIRE_H

// rostlina.h
#ifndef ROSTLINA_H
#define ROSTLINA_H

#include "organismus.h"

class Rostlina : public Organismus {
public:
    void aktualizuj() override;
};

#endif // ROSTLINA_H

// bylozravec.h
#ifndef BYLOZRAVEC_H
#define BYLOZRAVEC_H

#include "zvire.h"

class Bylozravec : public Zvire {
public:
    Bylozravec(int e) : Zvire(e) {}
    void pohyb() override;
    void aktualizuj() override;
};

#endif // BYLOZRAVEC_H

// masozravec.h
#ifndef MASOZRAVEC_H
#define MASOZRAVEC_H

#include "zvire.h"

class Masozravec : public Zvire {
public:
    Masozravec(int e) : Zvire(e) {}
    void pohyb() override;
    void aktualizuj() override;
};

#endif // MASOZRAVEC_H

// prostredi.h
#ifndef PROSTREDI_H
#define PROSTREDI_H

#include <vector>
#include "organismus.h"

class Prostredi {
private:
    std::vector<Organismus*> organismy;
public:
    void pridatOrganismus(Organismus* o);
    void aktualizuj();
};

#endif // PROSTREDI_H

// source.cpp
#include "rostlina.h"
#include "bylozravec.h"
#include "masozravec.h"
#include "prostredi.h"
#include <iostream>

void Rostlina::aktualizuj() {
    std::cout << "Rostlina roste.\n";
}

void Bylozravec::pohyb() {
    std::cout << "Býložravec se pohybuje.\n";
}

void Bylozravec::aktualizuj() {
    std::cout << "Býložravec se krmí.\n";
}

void Masozravec::pohyb() {
    std::cout << "Masožravec loví.\n";
}

void Masozravec::aktualizuj() {
    std::cout << "Masožravec se krmí.\n";
}

void Prostredi::pridatOrganismus(Organismus* o) {
    organismy.push_back(o);
}

void Prostredi::aktualizuj() {
    for (auto o : organismy) {
        o->aktualizuj();
    }
}

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

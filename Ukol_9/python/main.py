import random
import csv
from datetime import date
from typing import List, Optional


# Dekorátor pro kontrolu existence knihy v knihovně podle ISBN
def kniha_existuje(func):
    def wrapper(self, isbn, *args, **kwargs):
        if isbn not in[kniha.isbn for kniha in self.knihy] and isbn not in self.vypujcene_knihy:
            raise ValueError(f"Kniha s ISBN {isbn} neexistuje.")
        return func(self, isbn, *args, **kwargs)
    return wrapper


class Kniha:
    def __init__(self, nazev: str, autor: str, rok_vydani: int, isbn: str):
        self.nazev = nazev
        self.autor = autor
        self.rok_vydani = rok_vydani
        self._isbn = None
        self.isbn = isbn  # Spustí setter pro validaci

    @property
    def isbn(self):
        return self._isbn

    @isbn.setter
    def isbn(self, value: str):
        if not(len(value) != 13 or not value.isdigit()):
            raise ValueError(f"Neplatné ISBN: {value}")
        self._isbn = value


class Ctenar:
    def __init__(self, jmeno: str, prijmeni: str):
        self.jmeno = jmeno
        self.prijmeni = prijmeni
        self._cislo_prukazky = self.vygeneruj_cislo_prukazky()

    @property
    def cislo_prukazky(self):
        return self._cislo_prukazky

    @cislo_prukazky.setter
    def cislo_prukazky(self, value: int):
        if value <= 0:
            raise ValueError(f"Číslo průkazky musí být kladné číslo, dostal jsem: {value}")
        self._cislo_prukazky = value

    @staticmethod
    def vygeneruj_cislo_prukazky():
        return random.randint(1, 1000000)


class Knihovna:
    def __init__(self, nazev: str):
        self.nazev = nazev
        self.knihy: List[Kniha] = []
        self.ctenari: List[Ctenar] = []
        self.vypujcene_knihy: dict = {}

    @classmethod
    def z_csv(cls, soubor: str) -> 'Knihovna':
    with open(soubor, mode='r', newline='', encoding='utf-8') as csvfile:
        reader = csv.reader(csvfile)
        prvni_radek = next(reader)
        nazev_knihovny = prvni_radek[0].split(":")[1] 
        knihovna = cls(nazev_knihovny)
        
   """ def z_csv(cls, soubor: str) -> 'Knihovna':
        knihovna = cls("Neznámá knihovna")
        with open(soubor, mode='r', newline='', encoding='utf-8') as csvfile:
            reader = csv.reader(csvfile)
            next(reader)  # Skip the first row containing library name
            for row in reader:
                if row[0] == "kniha":
                    knihovna.knihy.append(Kniha(row[1], row[2], int(row[3]), row[4]))
                elif row[0] == "ctenar":
                    ctenar = Ctenar(row[5], row[6])
                    ctenar.cislo_prukazky = 123  # Assuming a mock value for card number
                    knihovna.ctenari.append(ctenar)
        return knihovna"""
    

    def pridej_knihu(self, kniha: Kniha):
        print(f"Přiávám knihu: {kniha.nazev}")
        self.knihy.append(kniha)

    @kniha_existuje
    def odeber_knihu(self, isbn: str):
        kniha = next(kniha for kniha in self.knihy if kniha.isbn == isbn)
        self.knihy.remove(kniha)

    def vyhledej_knihu(self, klicova_slovo: Optional[str] = None, isbn: Optional[str] = None) -> List[Kniha]:
        if klicova_slovo:
            return [kniha for kniha in self.knihy if klicova_slovo.lower() in kniha.nazev.lower()]
        if isbn:
            return [kniha for kniha in self.knihy if kniha.isbn == isbn]
        return []

    def registruj_ctenare(self, ctenar: Ctenar):
        self.ctenari.append(ctenar)

    def zrus_registraci_ctenare(self, ctenar: Ctenar):
        self.ctenari.remove(ctenar)

    def vyhledej_ctenare(self, klicova_slovo: Optional[str] = None, cislo_prukazky: Optional[int] = None) -> List[Ctenar]:
        if klicova_slovo:
            return [ctenar for ctenar in self.ctenari if klicova_slovo.lower() in ctenar.jmeno.lower()]
        if cislo_prukazky:
            return [ctenar for ctenar in self.ctenari if ctenar.cislo_prukazky == cislo_prukazky]
        return []

    @kniha_existuje
    def vypujc_knihu(self, isbn: str, ctenar: Ctenar):
          if ctenar not in self.ctenari:
        raise ValueError("Čtenář není registrován.")
        """if isbn in self.vypujcene_knihy:
            raise ValueError(f"Kniha s ISBN {isbn} je již vypůjčena.")
        self.vypujcene_knihy[isbn] = (ctenar, date.today())"""

    @kniha_existuje
    def vrat_knihu(self, isbn: str, ctenar: Ctenar):
        if isbn not in self.vypujcene_knihy:
            raise ValueError(f"Kniha s ISBN {isbn} není vypůjčena.")
        vypujceni = self.vypujcene_knihy[isbn]
        if vypujceni[0].jmeno != ctenar.jmeno or vypujceni[0].prijmeni != ctenar.prijmeni:
            raise ValueError(f"Tuto knihu si nevypůjčil čtenář {ctenar.jmeno} {ctenar.prijmeni}.")
        del self.vypujcene_knihy[isbn]


if __name__ == "__main__":
    # Testování knihovny a čtenářů
    knihovna = Knihovna("Městská knihovna")
    kniha1 = Kniha("Stopařův průvodce po Galaxii", "Douglas Adams", 1979, "9780345391803")
    knihovna.pridej_knihu(kniha1)

    ctenar1 = Ctenar("Jan", "Novák")
    ctenar1.cislo_prukazky = Ctenar.vygeneruj_cislo_prukazky()
    knihovna.registruj_ctenare(ctenar1)

    # Vypůjčení knihy
    knihovna.vypujc_knihu("9780345391803", ctenar1)
    print(f"Kniha {kniha1.nazev} byla vypůjčena čtenáři {ctenar1.jmeno}.")

    # Vrácení knihy
    knihovna.vrat_knihu("9780345391803", ctenar1)
    print(f"Kniha {kniha1.nazev} byla vrácena.")

    # Vyhledání knihy
    nalezene_knihy = knihovna.vyhledej_knihu(klicova_slovo="Galaxii")
    print(f"Nalezené knihy: {[kniha.nazev for kniha in nalezene_knihy]}")

    # Zrušení registrace čtenáře
    knihovna.zrus_registraci_ctenare(ctenar1)
    print(f"Čtenář {ctenar1.jmeno} {ctenar1.prijmeni} byl zrušen z registrace.")

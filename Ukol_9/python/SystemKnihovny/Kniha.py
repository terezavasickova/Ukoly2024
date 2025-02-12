///class Kniha:
    def __init__(self, nazev: str, autor: str, rok_vydani: int, isbn: str):
        self._nazev = nazev
        self._autor = autor
        self._rok_vydani = rok_vydani
        self.isbn = isbn

    # doplňte potřebné gettry a setry

    def __str__(self) -> str:
        return ""///
        
#import re

class Kniha:
    def __init__(self, nazev, autor, rok_vydani, isbn):
        self.nazev = nazev
        self.autor = autor
        self.rok_vydani = rok_vydani
        self.isbn = isbn
        
        if not self.validuj_isbn(isbn):
            raise ValueError(f"ISBN '{isbn}' není platné.")

    def validuj_isbn(self, isbn):
        # Jednoduchá validace ISBN (např. kontrola délky a formátu)
        return bool(re.match(r"^\d{13}$", isbn))

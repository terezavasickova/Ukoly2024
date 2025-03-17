def soucet(cisla: list[int]) -> int:
    """Vypočítá součet čísel v seznamu.

    Args:
      cisla: Seznam čísel.

    Returns:
      Součet čísel.
    """
    return sum(cisla)


def soucin(cisla: list[int]) -> int:
    """Vypočítá součin čísel v seznamu.

    Args:
      cisla: Seznam čísel.

    Returns:
      Součin čísel.
    """
    if not cisla:
        return 0
    produkt = 1
    for cislo in cisla:
        produkt *= cislo
    return produkt


def prumer(cisla: list[int]) -> float:
    """Vypočítá průměrnou hodnotu čísel v seznamu.

    Args:
      cisla: Seznam čísel.

    Returns:
      Průměrná hodnota čísel.
    """
    if not cisla:
        raise ValueError("Seznam cisel je prazdny")
    return sum(cisla) / len(cisla)


def median(cisla: list[int]) -> float:
    """Vypočítá medián čísel v seznamu.

    Args:
      cisla: Seznam čísel.

    Returns:
      Medián čísel.
    """
    if not cisla:
        raise ValueError("Seznam cisel je prazdny")
    cisla.sort()
    n = len(cisla)
    if n % 2 == 0:
        return (cisla[n//2 - 1] + cisla[n//2]) / 2.0
    else:
        return cisla[n//2]


def main():
    """Načte vstup od uživatele, zavolá funkce pro výpočet a vypíše výsledky."""
    vstup = input("Zadejte seznam cisel oddelenych carkou: ")
    cisla = [int(cislo) for cislo in vstup.split(",")]

    print("Soucet:", soucet(cisla))
    print("Soucin:", soucin(cisla))
    print("Prumerna hodnota:", prumer(cisla))
    print("Median:", median(cisla))


if __name__ == "__main__":
    main()

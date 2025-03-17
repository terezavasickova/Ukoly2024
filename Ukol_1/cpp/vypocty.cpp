#include <iostream>
#include <vector>
#include <sstream>
#include <algorithm>

int soucet(const std::vector<int> &cisla) {
    int sum = 0;
    for (int cislo : cisla) {
        sum += cislo;
    }
    return sum;
}

int soucin(const std::vector<int> &cisla) {
    int product = 1;
    for (int cislo : cisla) {
        product *= cislo;
    }
    return product;
}

double prumer(const std::vector<int> &cisla) {
    if (cisla.empty()) return 0;
    return static_cast<double>(soucet(cisla)) / cisla.size();
}

double median(std::vector<int> cisla) {
    if (cisla.empty()) return 0;
    std::sort(cisla.begin(), cisla.end());
    int n = cisla.size();
    if (n % 2 == 0) {
        return (cisla[n/2 - 1] + cisla[n/2]) / 2.0;
    } else {
        return cisla[n/2];
    }
}

#ifndef __TEST__
int main() {
    std::cout << "Zadejte seznam cisel oddelenych carkou: ";
    std::string vstup;
    std::getline(std::cin, vstup);

    std::vector<int> cisla;
    std::stringstream ss(vstup);
    std::string hodnota;
    while (std::getline(ss, hodnota, ',')) {
        cisla.push_back(std::stoi(hodnota));
    }

    std::cout << "Soucet: " << soucet(cisla) << std::endl;
    std::cout << "Soucin: " << soucin(cisla) << std::endl;
    std::cout << "Prumerna hodnota: " << prumer(cisla) << std::endl;
    std::cout << "Median: " << median(cisla) << std::endl;

    return 0;
}
#endif

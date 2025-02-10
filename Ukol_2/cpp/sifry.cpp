#include <iostream>
#include <fstream>
#include <string>

// Funkce pro otevření souboru
std::string otevri_soubor(const std::string& jmeno_souboru)
{
    std::ifstream soubor(jmeno_souboru);
    if (!soubor.is_open()) {
        std::cerr << "Nepodařilo se otevřít soubor: " << jmeno_souboru << std::endl;
        return "";
    }

    std::string obsah((std::istreambuf_iterator<char>(soubor)), std::istreambuf_iterator<char>());
    soubor.close();
    return obsah;
}

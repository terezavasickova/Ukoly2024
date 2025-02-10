#include <iostream>
#include <fstream>
#include <string>

// Funkce pro otevření souboru

a píše mi to tento error:18s
1s
Run cd Ukol_2/cpp && mkdir -p build && cd build && cmake .. && make && ./mytests || exit 1
CMake Deprecation Warning at CMakeLists.txt:1 (cmake_minimum_required):
  Compatibility with CMake < 3.10 will be removed from a future version of
  CMake.

  Update the VERSION argument <min> value.  Or, use the <min>...<max> syntax
  to tell CMake that the project requires at least <min> but has been updated
  to work with policies introduced by <max> or earlier.


-- The C compiler identification is GNU 13.3.0
-- The CXX compiler identification is GNU 13.3.0
-- Detecting C compiler ABI info
-- Detecting C compiler ABI info - done
-- Check for working C compiler: /usr/bin/cc - skipped
-- Detecting C compile features
-- Detecting C compile features - done
-- Detecting CXX compiler ABI info
-- Detecting CXX compiler ABI info - done
-- Check for working CXX compiler: /usr/bin/c++ - skipped
-- Detecting CXX compile features
-- Detecting CXX compile features - done
-- Found GTest: /usr/lib/x86_64-linux-gnu/cmake/GTest/GTestConfig.cmake (found version "1.14.0")
-- Configuring done (0.6s)
-- Generating done (0.0s)
-- Build files have been written to: /home/runner/work/Ukoly2024/Ukoly2024/Ukol_2/cpp/build
[ 25%] Building CXX object CMakeFiles/sifry.dir/sifry.cpp.o
[ 50%] Linking CXX executable sifry
/usr/bin/ld: /usr/lib/gcc/x86_64-linux-gnu/13/../../../x86_64-linux-gnu/Scrt1.o: in function _start':
(.text+0x1b): undefined reference to main'
collect2: error: ld returned 1 exit status
make[2]: *** [CMakeFiles/sifry.dir/build.make:101: sifry] Error 1
make[1]: *** [CMakeFiles/Makefile2:90: CMakeFiles/sifry.dir/all] Error 2
make: *** [Makefile:101: all] Error 2 
std::string otevri_soubor(const std::string& vstup.txt)
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

// Funkce pro Caesarovu šifru
std::string caesar_sifra(const std::string& text, int posun, bool sifrovat)
{
    std::string vysledek = "";
    int real_posun = sifrovat ? posun : -posun;

    for (char znak : text) {
        if (isalpha(znak)) {
            char zaklad = islower(znak) ? 'a' : 'A';
            znak = zaklad + (znak - zaklad + real_posun + 26) % 26;
        }
        vysledek += znak;
    }

    return vysledek;
}

// Funkce pro Vigenerovu šifru
std::string vigener_sifra(const std::string& text, const std::string& klic, bool sifrovat)
{
    std::string vysledek = "";
    int klic_delka = klic.length();

    for (size_t i = 0; i < text.length(); ++i) {
        char znak = text[i];
        char klic_znak = klic[i % klic_delka];

        if (isalpha(znak)) {
            char zaklad = islower(znak) ? 'a' : 'A';
            char zaklad_klic = islower(klic_znak) ? 'a' : 'A';
            int posun = sifrovat ? (klic_znak - zaklad_klic) : -(klic_znak - zaklad_klic);
            znak = zaklad + (znak - zaklad + posun + 26) % 26;
        }

        vysledek += znak;
    }

    return vysledek;
}

// Funkce pro XOR šifru
std::string xor_sifra(const std::string& text, const std::string& klic, bool sifrovat)
{
    std::string vysledek = "";
    int klic_delka = klic.length();

    for (size_t i = 0; i < text.length(); ++i) {
        vysledek += text[i] ^ klic[i % klic_delka];
    }

    return vysledek;
}

// Funkce pro uložení řetězce do souboru
void uloz_do_souboru(const std::string& jmeno_souboru, const std::string& obsah)
{
    std::ofstream soubor(jmeno_souboru);
    if (!soubor.is_open()) {
        std::cerr << "Nepodařilo se uložit do souboru: " << jmeno_souboru << std::endl;
        return;
    }

    soubor << obsah;
    soubor.close();
}

#ifndef __TEST__ // Add this preprocessor guard
int main()
{
    // Načtení vstupního souboru
    std::string vstupni_text = otevri_soubor("vstup.txt");

    // Šifrování textu pomocí Caesarovy šifry
    std::string sifrovany_text_caesar = caesar_sifra(vstupni_text, 3, true);
    std::cout << "Caesarova šifra: " << sifrovany_text_caesar << std::endl;

    // Šifrování textu pomocí Vigenerovy šifry
    std::string sifrovany_text_vigener = vigener_sifra(vstupni_text, "tajny_klic", true);
    std::cout << "Vigenerova šifra: " << sifrovany_text_vigener << std::endl;

    // Šifrování textu pomocí XOR šifry
    std::string sifrovany_text_xor = xor_sifra(vstupni_text, "heslo", true);
    std::cout << "XOR šifra: " << sifrovany_text_xor << std::endl;

    // Uložení šifrovaných textů do souborů
    uloz_do_souboru("sifrovany_caesar.txt", sifrovany_text_caesar);
    uloz_do_souboru("sifrovany_vigener.txt", sifrovany_text_vigener);
    uloz_do_souboru("sifrovany_xor.txt", sifrovany_text_xor);

    // Dešifrování textů
    std::cout << "Dešifrovaný text pomocí Caesarovy šifry: " << caesar_sifra(otevri_soubor("sifrovany_caesar.txt"), 3, false) << std::endl;
    std::cout << "Dešifrovaný text pomocí Vigenerovy šifry: " << vigener_sifra(otevri_soubor("sifrovany_vigener.txt"), "tajny_klic", false) << std::endl;
    std::cout << "Dešifrovaný text pomocí XOR šifry: " << xor_sifra(otevri_soubor("sifrovany_xor.txt"), "heslo", false) << std::endl;

    return 0;
}
#endif // __TEST__

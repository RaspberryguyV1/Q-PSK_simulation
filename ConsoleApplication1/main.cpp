#include <iostream>
#include <fstream> 
#include <iomanip>
#include <string>
#include <vector>
#include "encoder.h"
#include "Modulator.h"
#include "Demodulator.h"
#include "decoder.h"
//Zapisanie do pliku sygnału (symulacja medium transmisyjnego)
void zapiszDoPliku(const std::vector<double>& fala, std::string nazwaPliku) {
    std::ofstream plik(nazwaPliku);

    if (!plik.is_open()) {
        std::cout << "Blad: Nie mozna otworzyc pliku do zapisu!" << std::endl;
        return;
    }

    for (const auto& probka : fala) {
        plik << probka << "\n";
    }

    plik.close();
}
//Wczytanie z pliku (symulacja medium transmisyjnego)
std::vector<double> wczytajZPliku(std::string nazwaPliku) {
    std::vector<double> odczytaneDane;
    std::ifstream plik(nazwaPliku);

    if (!plik.is_open()) {
        std::cerr << "Blad: Nie mozna otworzyc pliku do odczytu!" << std::endl;
        return odczytaneDane;
    }

    double wartosc;
    while (plik >> wartosc) {
        odczytaneDane.push_back(wartosc);
    }

    plik.close();
    return odczytaneDane;
}

void dodajSzum(std::vector<double>& fala, double silaSzumu) {
    srand(time(NULL));
    for (int i = 0; i < fala.size(); i++)
    {
        double losowa = ((double)rand() / RAND_MAX) * 2.0 - 1.0;
        fala[i] += silaSzumu * losowa;
    }
}
int main() {
    double frequency = 1000;
    int sampleRate = 4*frequency;
    int symbolDuration = 4;
    
    Encoder enkoder;
    Modulator modulator(sampleRate, symbolDuration, frequency);
    Demodulator demodulator(sampleRate, symbolDuration, frequency);
    Decoder dekoder;
    std::string wiadomosc;
    std::cout << "Podaj wiadomosc do transmisji: " << std::endl;
    std::getline(std::cin, wiadomosc);
    //1. Kodowanie
    std::vector<std::bitset<2>> symbol = enkoder.encode(wiadomosc);
    std::cout << "Nadane symbole: ";
    for (int i = 0; i < symbol.size(); i++)
    {
        std::cout << symbol[i] << " ";
    }
    std::cout << std::endl;
    
    //2. Modulacja
    std::vector<double> fala = modulator.modulate(symbol);

    //Szum
    dodajSzum(fala, 0.7 /*<-natężenie szumu*/);
    
    //3 Nadanie
    zapiszDoPliku(fala, "sygnal.txt");
    
    //4. Odebranie
    std::vector<double> odebranaFala = wczytajZPliku("sygnal.txt");
    
    //5. Demodulacja
    std::vector<std::bitset<2>> odebraneBity = demodulator.demodulate(odebranaFala);

    std::cout << "Odebrane symbole: ";
    for (int i = 0; i < odebraneBity.size(); i++)
    {
        std::cout << odebraneBity[i] << " ";
    }
    std::cout << std::endl;
    
    //6. Dekodowanie
    std::string odebranaWiadomosc = dekoder.decode(odebraneBity);
    std::cout << "Wiadomosc to: " << odebranaWiadomosc << std::endl;
    
    
    // TEST TRANSMISJI
    std::cout << "\n--- WERYFIKACJA DANYCH ---" << std::endl;

    size_t limit = (symbol.size() < odebraneBity.size()) ? symbol.size() : odebraneBity.size();
    int licznikBledow = 0;
    int maxBledowDoWypisania = 10; // Zabezpieczenie przed zbędną ilością błędów w raporcie

    
    for (size_t i = 0; i < limit; i++)
    {
        if (odebraneBity[i] != symbol[i])
        {
            licznikBledow++;
            if (licznikBledow <= maxBledowDoWypisania) {
                std::cout << "[BLAD] Indeks " << i
                    << ": Wyslano " << symbol[i]
                    << ", Odebrano " << odebraneBity[i] << std::endl;
            }
            else if (licznikBledow == maxBledowDoWypisania + 1) {
                std::cout << "... (reszta bledow ukryta) ..." << std::endl;
            }
        }
    }
    if (licznikBledow == 0) {
        std::cout << "[ OK ]" << std::endl;
    }
    else {
        std::cout << "[ FAIL ] " << licznikBledow << " blednych symboli." << std::endl;
    }
    return 0;
}
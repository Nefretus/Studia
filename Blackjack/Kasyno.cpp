#include "Kasyno.h"
#include"Gracz.h"
#include"Bot.h"
#include<iostream>
#include<fstream>
#include<iomanip>

const int liczbaKolorow = 4;
const int liczbaFigur = 13;
const int liczbaKart = 52;

Kasyno::Kasyno() : liczbaGraczy(0), gracze(nullptr), boty(nullptr), liczbaBotow(0) {
	int n = 0;
	while (n < liczbaKart) {
		for (int i = 0; i < liczbaKolorow; i++) {
			for (int j = 0; j < liczbaFigur; j++) {
				talia[n].setKolor(i);
				talia[n].setWartosc(j);
				n++;
			}
		}
	}
}

void Kasyno::dodajGraczy() {
	gracze = new Gracz[liczbaGraczy];
	for (int i = 0; i < liczbaGraczy; i++) {
		gracze[i].nadajNazwe();
	}
}

void Kasyno::dodajBoty() {
	boty = new Bot[liczbaBotow];
	for (int i = 0; i < liczbaBotow; i++) {
		boty[i].nadajNazwe(i);
	}
}

void Kasyno::tasuj() {
	Karta temp;
	for (int i = 0; i < 100; i++) {
		int losuj1 = rand() % liczbaKart;
		int losuj2 = rand() % liczbaKart;
		temp = talia[losuj1];
		talia[losuj1] = talia[losuj2];
		talia[losuj2] = temp;
	}
}

Karta* Kasyno::dajKarte() {
	int ileKartWydano = 0;
	for (int i = 0; i < liczbaGraczy; i++) {
		ileKartWydano += gracze[i].ileKartMaGracz();
	}
	for (int i = 0; i < liczbaBotow; i++) {
		ileKartWydano += boty[i].ileKartMaGracz();
	}
	return &talia[ileKartWydano];
}

void Kasyno::rozdajDwieKarty() {
	for (int i = 0; i < liczbaGraczy; i++) {
		for (int j = 0; j < 2; j++) {
			gracze[i].wezKarte(dajKarte());
		}
	}
	for (int i = 0; i < liczbaBotow; i++) {
		for (int j = 0; j < 2; j++) {
			boty[i].wezKarte(dajKarte());
		}
	}
}

void Kasyno::pokazStanPoRozgrywce() {
	std::cout.setf(std::ios::left, std::ios::adjustfield);
	for (int i = 0; i < liczbaGraczy; i++) {
		std::cout << std::setw(15) <<  gracze[i].getNazwa() << std::setw(15) << gracze[i].jakaWartoscKart();
		gracze[i].wypiszKarty();
		std::cout << '\n';
	}
	for (int i = 0; i < liczbaBotow; i++) {
		std::cout << std::setw(15) << boty[i].getNazwa() << std::setw(15) << boty[i].jakaWartoscKart();
		boty[i].wypiszKarty();
		std::cout << '\n';
	}
	std::cout.unsetf(std::ios::left);
}

void Kasyno::graj() {
	system("cls");
	tasuj();
	std::cout << "Wprowadz ile graczy ludzkich: (1-3)\n";
	liczbaGraczy = wprowadzDane();
	while (!(liczbaGraczy > 0 && liczbaGraczy <= 3)) {
		std::cout << "Zle dane!\n";
		liczbaGraczy = wprowadzDane();
	}
	dodajGraczy();
	std::cout<<"Wprowadz ile graczy wirutalnych: (1-3)\n";
	liczbaBotow = wprowadzDane();
	while (!(liczbaBotow > 0 && liczbaBotow <= 3)) {
		std::cout << "Zle dane!\n";
		liczbaBotow = wprowadzDane();
	}
	dodajBoty();
	rozdajDwieKarty();
	while (!wszyscyGraczePas()) {
		for (int i = 0; i < liczbaGraczy; i++) {
			gracze[i].podejmijDecyzje(*this);
		}
		for (int i = 0; i < liczbaBotow; i++) {
			boty[i].podejmijDecyzje(*this);
		}
	}
	pokazStanPoRozgrywce();
	ktoWygral();
	zapiszDoPliku();
	zwolnijPamiec();
}

void Kasyno::zwolnijPamiec() {
	delete[] gracze;
	delete[] boty;
	boty = nullptr;
	liczbaBotow = 0;
	gracze = nullptr;
	liczbaGraczy = 0;
}

bool Kasyno::wszyscyGraczePas() {
	for (int i = 0; i < liczbaGraczy; i++) {
		if (!gracze[i].getCzyPas()) {
			return false;
		}
	}
	for (int i = 0; i < liczbaBotow; i++) {
		if (!boty[i].getCzyPas()) {
			return false;
		}
	}
	return true;
}

int Kasyno::znajdzMaxPktBotow() {
	int wygrywajacaLiczbaPkt = 0;
	for (int i = 0; i < liczbaBotow; i++) {
		if (wygrywajacaLiczbaPkt == 0) { 
			wygrywajacaLiczbaPkt = boty[i].jakaWartoscKart();
		}
		else {
			if (wygrywajacaLiczbaPkt > 21) {
				wygrywajacaLiczbaPkt = boty[i].jakaWartoscKart();
			}
			else {
				if ((boty[i].jakaWartoscKart() > wygrywajacaLiczbaPkt) && (boty[i].jakaWartoscKart() <= 21)) {
					wygrywajacaLiczbaPkt = boty[i].jakaWartoscKart();
				}
			}
		}
	}
	return wygrywajacaLiczbaPkt;
}

int Kasyno::znajdzMaxPktGraczy() {
	int wygrywajacaLiczbaPkt = 0;
	for (int i = 0; i < liczbaGraczy; i++) {
		if (wygrywajacaLiczbaPkt == 0) {
			wygrywajacaLiczbaPkt = gracze[i].jakaWartoscKart();
		}
		else {
			if (wygrywajacaLiczbaPkt > 21) {
				wygrywajacaLiczbaPkt = gracze[i].jakaWartoscKart();
			}
			else {
				if ((gracze[i].jakaWartoscKart() > wygrywajacaLiczbaPkt) && (gracze[i].jakaWartoscKart() <= 21)) {
					wygrywajacaLiczbaPkt = gracze[i].jakaWartoscKart();
				}
			}
		}
	}
	return wygrywajacaLiczbaPkt;
}

int Kasyno::ktoWygral() {
	int wygrywajacaLiczbaPkt = 0;
	int punktyGraczy, punktyBotow;
	punktyGraczy = znajdzMaxPktGraczy();
	punktyBotow = znajdzMaxPktBotow();
	if ((punktyGraczy > punktyBotow) && punktyGraczy <= 21) {
		wygrywajacaLiczbaPkt = punktyGraczy;
	}
	else if (punktyBotow <= 21) {
		wygrywajacaLiczbaPkt = punktyBotow;
	}
	else if (punktyGraczy <= 21){
		wygrywajacaLiczbaPkt = punktyGraczy;
	}
	else {
		std::cout << "Nie ma zwyciezcy!\n";
		return 0;
	}
	for (int i = 0; i < liczbaGraczy; i++) {
		if (gracze[i].jakaWartoscKart() == wygrywajacaLiczbaPkt) {
			std::cout << "Wygrywa Gracz o imieniu " << gracze[i].getNazwa() << "!\n";
		}
	}
	for (int i = 0; i < liczbaBotow; i++) {
		if (boty[i].jakaWartoscKart() == wygrywajacaLiczbaPkt) {
			std::cout << "Wygrywa Gracz o imieniu " << boty[i].getNazwa() << "!\n";
		}
	}
	return 0;
}

void Kasyno::zapiszDoPliku() {
	std::ofstream plik("wyniki.txt", std::ifstream::out);
	if (plik.is_open()) {
		for (int i = 0; i < liczbaGraczy; i++) {
			plik.setf(std::ios::left, std::ios::adjustfield);
			plik  << std::setw(20) << gracze[i].getNazwa();
			plik << std::setw(20) << gracze[i].jakaWartoscKart();
			for (int j = 0; j < gracze[i].ileKartMaGracz(); j++) {
				if (gracze[i].getKarta(j) != nullptr) {
					char znak = gracze[i].getKarta(j)->getKolor() + 94;
					plik << gracze[i].getKarta(j)->getFigura() << znak;
				}
			}
			plik << '\n';
		}
		for (int i = 0; i < liczbaBotow; i++) {
			plik.setf(std::ios::left, std::ios::adjustfield);
			plik << std::setw(20) << boty[i].getNazwa();
			plik << std::setw(20) << boty[i].jakaWartoscKart();
			for (int j = 0; j < boty[i].ileKartMaGracz(); j++) {
				if (boty[i].getKarta(j) != nullptr) {
					char znak = boty[i].getKarta(j)->getKolor() + 94;
					plik << boty[i].getKarta(j)->getFigura() << znak;
				}
			}
			plik << '\n';
		}
		std::cout << "Zapis do pliku zakonczyl sie powodzeniem!\n";
		plik.close();
	}
	else {
		std::cout << "Nie udalo sie utworzyc pliku!";
	}
}

int Kasyno::wprowadzDane() {
	int decyzja;
	while (1) {
		std::cin >> decyzja;
		if (std::cin.fail()) {
			std::cout << "Zle dane, sprobuj jeszcze raz!";
			std::cin.clear();
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		}
		else
			break;
	}
	return decyzja;
}

Kasyno::~Kasyno() {
	delete[] gracze;
	delete[] boty;
}
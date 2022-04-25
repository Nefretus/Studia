#include<iostream>
#include"Symulacja.h"

template<typename T>
T wprowadzDane() {
	T decyzja;
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

void printMenu(int& wybor) {
	std::cout << "Menu \n1.Symulacja z regulatorem dwustawnym\n2.Symulacja z regulatorem PID\n3.Zmiana parametrow symulacji (wymiary i moc grzejnika)\n4.Koniec\n";
	wybor = wprowadzDane<int>();
	system("cls");
}

void ustawParametry(Symulacja** _symulacja) {
	if (*_symulacja) {
		delete *_symulacja;
	}
	float wysokosc, szerokosc, glebokosc, mocNominalna;
	while (1337) {
		std::cout << "Podaj wysokosc pomieszczenia: \n";
		wysokosc = wprowadzDane<float>();
		std::cout << "Podaj szerokosc: \n";
		szerokosc = wprowadzDane<float>();
		std::cout << "Podaj glebokosc: \n";
		glebokosc = wprowadzDane<float>();
		std::cout << "Moc nominalna grzejnika: \n";
		mocNominalna = wprowadzDane<float>();
		try {
			*_symulacja = new Symulacja(wysokosc, szerokosc, glebokosc, mocNominalna);
		}
		catch (const char* e) {
			std::cout << e;
			std::cout << "Sprobuj ponownie!\n";
			continue;
		}
		break;
	}
}

void symuluj(const char* _jakiRegulator, Symulacja** _s) {
	int liczbaIteracji;
	if (*_s == nullptr) {
		std::cout << "Symulacja uruchamiana jest pierwszy raz, zacznij od zdefiniowania pomieszczenia: \n";
		ustawParametry(_s);
	}
	std::cout << "Podaj zadana temperature: \n";
	(*_s)->dodajRegulator(_jakiRegulator, wprowadzDane<float>());
	std::cout << "Podaj liczbe iteracji: \n";
	liczbaIteracji = wprowadzDane<int>();
	std::cout << "Podaj czas probkowania: \n";
	(*_s)->przebieg(liczbaIteracji, wprowadzDane<float>());
}

int main() {
	Symulacja *s = nullptr;
	int wybor;
	bool koniec = false;
	while (!koniec) {
		printMenu(wybor);
		switch (wybor) {
		case 1:
			symuluj("BB", &s);
			break;
		case 2:
			symuluj("PID", &s);
			break;
		case 3:
			ustawParametry(&s);
			break;
		case 4:
			koniec = true;
			break;
		default:
			break;
		}
	}
	delete s;
	return 0;
}

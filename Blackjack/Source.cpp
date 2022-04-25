#include<iostream>
#include<stdlib.h>
#include<time.h>
#include"Kasyno.h"

// Przy wpisywaniu do pliku zastapilem kolory nastepujacymi znakami:
// kier(3) -> literka a
// karo(4) -> literka b
// trefl(5) -> literka c
// pik(6) -> literka d
// dla lepszego sprawdzania zostawilem dodatkowo wyswietlanie wynikow w konsoli

int main() {
	srand((unsigned int)time(NULL));
	Kasyno kasyno;
	int wybor;
	std::cout << "MENU: \n1.Graj\n2.Koniec\n";
	wybor = kasyno.wprowadzDane();
	bool koniec = false;
	while (!koniec) {
		switch (wybor) {
		case 1:
			kasyno.graj();
			std::cout << "MENU: \n1.Graj\n2.Koniec\n";
			wybor = kasyno.wprowadzDane();
			break;
		case 2:
			koniec = true;
			break;
		default:
			system("cls");
			std::cout << "MENU: \n1.Graj\n2.Koniec\n";
			wybor = kasyno.wprowadzDane();
			break;
		}
	}
	return 0;
}
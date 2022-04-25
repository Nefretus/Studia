#pragma once
#include"Gracz.h"
class Kasyno;
class Bot : public Gracz {
public:
	Bot();
	int getOdwaga() { return odwaga; }
	void nadajNazwe(int _numerBota);
	void podejmijDecyzje(Kasyno& _kasyno);
private:
	int odwaga;
};
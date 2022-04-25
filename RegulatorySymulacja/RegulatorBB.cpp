#include "RegulatorBB.h"
#include"Pomieszczenie.h"
#include"Grzejnik.h"

const float MAX_MOC = 1.0;
const float WYLACZ = 0;

void RegulatorBB::steruj(float _czas) {
	if (pomieszczenie == nullptr || grzejnik == nullptr) {
		throw - 1;
	}
	if (pomieszczenie->getTemperatura() < getZadanaTemperatura()) {
		grzejnik->setPoziomMocy(MAX_MOC);
	}
	else
		grzejnik->setPoziomMocy(WYLACZ);
}
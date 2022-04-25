#include "Grzejnik.h"

Grzejnik::Grzejnik(float _moc) : mocNominalna(_moc), poziomMocy(0)
{}

void Grzejnik::setPoziomMocy(float _nowaMoc) {
	if (_nowaMoc > 1) {
		poziomMocy = 1;
	}
	else if (_nowaMoc < 0) {
		poziomMocy = 0;
	}
	else
		poziomMocy = _nowaMoc;
}

float Grzejnik::emitowaneCieplo(float _dt) {
	float aktualnaMoc = poziomMocy * mocNominalna;
	return aktualnaMoc * _dt;
}
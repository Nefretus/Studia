#pragma once
class Grzejnik {
public:
	Grzejnik(float _moc);
	float getMocNominalna() { return mocNominalna; }
	float getPoziomMocy() { return poziomMocy; }
	void setPoziomMocy(float _moc);
	float emitowaneCieplo(float dt);
private:
	const float mocNominalna;
	float poziomMocy;
};

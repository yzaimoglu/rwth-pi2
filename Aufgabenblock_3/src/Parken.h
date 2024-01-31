#include "Verhalten.h"

#ifndef PARKEN_H_
#define PARKEN_H_

class Weg;
class Fahrzeug;

// Erbt von Verhalten
class Parken : public Verhalten {
public:
	// Standardkonstruktor und genutzer Konstruktor
	Parken();
	Parken(Weg& weg, double dStartzeitpunkt);

	// Überschreiben der vererbten Methode dStrecke
	virtual double dStrecke(Fahrzeug& aFahrzeug, double dZeitintervall) override;

	// Destruktor
	~Parken();
private:
	double p_dStartzeitpunkt;
};

#endif

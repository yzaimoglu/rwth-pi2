#ifndef STRECKENENDE_H_
#define STRECKENENDE_H_

#include "Fahrausnahme.h"

// Erbt von Fahrausnahme
class Streckenende : public Fahrausnahme {
public:
	// Standardkonstruktor und genutzer Konstruktor
	Streckenende();
	Streckenende(Fahrzeug& fahrzeug, Weg& weg);

	// Bearbeitungsmethode
	virtual void vBearbeiten();
	virtual ~Streckenende();
};
#endif

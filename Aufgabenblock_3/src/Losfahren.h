#ifndef LOSFAHREN_H_
#define LOSFAHREN_H_

#include "Fahrausnahme.h"

class Fahrzeug;

// Erbt von der Klasse Fahrausnahme
class Losfahren : public Fahrausnahme {
public:
	// Standardkonstruktor und genutzer Konstruktor
	Losfahren();
	Losfahren(Fahrzeug& fahrzeug, Weg& weg);

	// Bearbeitungsmethode bei der Fehlermeldung
	virtual void vBearbeiten();

	// Standarddestruktor
	virtual ~Losfahren();
};

#endif

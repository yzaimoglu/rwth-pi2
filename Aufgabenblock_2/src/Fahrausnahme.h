#ifndef FAHRAUSNAHME_H_
#define FAHRAUSNAHME_H_

#include "Fahrzeug.h"
#include "Weg.h"
#include <exception>

// Erbt Exception für das throwen
class Fahrausnahme : public std::exception {
public:
	// Standardkonstruktor und genutzer Konstruktor
	Fahrausnahme();
	Fahrausnahme(Fahrzeug& fahrzeug, Weg& weg);

	// Pure virtuelle Funktion, die overridden wird
	virtual void vBearbeiten() = 0;

	virtual ~Fahrausnahme();
// protected, da die subklassen Zugriff haben sollen
protected:
	Fahrzeug& p_pFahrzeug;
	Weg& p_pWeg;
};

#endif

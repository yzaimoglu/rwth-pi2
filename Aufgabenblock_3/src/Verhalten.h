#include "Fahrzeug.h"

#ifndef VERHALTEN_H_
#define VERHALTEN_H_

#define INSTANCEOF_REF(derivedType, baseREF) (dynamic_cast<derivedType*>(&baseREF) != nullptr)
#define INSTANCEOF_PTR(derivedType, basePTR) (dynamic_cast<derivedType*>(basePTR) != nullptr)

class Weg;

class Verhalten {
public:
	// Standardkonstruktor und genutzter Konstruktor
	Verhalten();
	Verhalten(Weg& weg);

	// Returned den Weg
	Weg* getWeg() {
		return p_pWeg;
	}

	// Pure virtuelle Methode für die dStrecke
	virtual double dStrecke(Fahrzeug& aFzg, double dZeitIntervall) = 0;

	// Standarddestruktor
	virtual ~Verhalten();
// protected für den Zugriff aus Subklassen
protected:
	Weg* p_pWeg;
};

#endif

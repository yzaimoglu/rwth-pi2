#ifndef FAHREN_H_
#define FAHREN_H_

#include "Verhalten.h"
class Weg;
class Fahrzeug;

// Erbt von Verhalten
class Fahren : public Verhalten {
public:
	// Standardkonstruktor
	Fahren();
	Fahren(Weg&);

	// Überschreiben der vererbten Methode dStrecke
	virtual double dStrecke(Fahrzeug& aFahrzeug, double dZeitintervall) override;

	// Destruktor
	~Fahren();
};

#endif

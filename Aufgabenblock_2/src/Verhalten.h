#include "Weg.h"
#include "Fahrzeug.h"

#ifndef VERHALTEN_H_
#define VERHALTEN_H_

class Verhalten {
public:
	Verhalten();
	Verhalten(Weg& weg);

	virtual double dStrecke(Fahrzeug& aFzg, double dZeitIntervall) = 0;
	virtual ~Verhalten();
protected:
	Weg* p_pWeg;
};

#endif

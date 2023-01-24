#include <iostream>
#include <list>
#include "Simulationsobjekt.h"
#include "Tempolimit.h"
#include "Fahrzeug.h"

#ifndef WEG_H_
#define WEG_H_

class Fahrzeug;

class Weg : public Simulationsobjekt {
private:
	double p_dLaenge;
	Tempolimit p_eTempolimit;
public:
	std::list<std::unique_ptr<Fahrzeug>> p_pFahrzeuge;
	// Standardkonstruktor
	Weg();

	// Konstruktor
	// 	sName : Name des Weges
	//	dLanege : Länge des Weges in km
	// 	dTempolimit : Tempolimit auf dem Weg in km/h (Standardmäßig keine Begrenzung)
	Weg(std::string sName, double dLaenge, Tempolimit eTempolimit = AUTOBAHN);

	// Methode zum Erhalten des Tempolimits als double
	double getTempolimit() {
		switch (p_eTempolimit) {
			case INNERORTS:
				return 50.0;
			case LANDSTRASSE:
				return 100.0;
			default:
				return std::numeric_limits<double>::max();
		}
	}

	// Methode zum Erhalten der Länge als double
	double getLaenge() {
		return p_dLaenge;
	}

	// Fahrzeuge als list
	std::list<std::unique_ptr<Fahrzeug>>* getFahrzeuge() {
		return &p_pFahrzeuge;
	}

	void vAnnahme(std::unique_ptr<Fahrzeug>);

	// Methode zum Simulieren aller Fahrzeuge;
	virtual void vSimulieren();

	// Ausgabemethode für die Kopfzeile
	virtual void vKopf();

	// Ausgabemethoden
	virtual void vAusgeben();
	virtual void vAusgeben(std::ostream& o) const;

	// Destruktor
	virtual ~Weg();
};

// Überladung des << Operators außerhalb der Klasse
std::ostream& operator<<(std::ostream&, const Weg&);

#endif

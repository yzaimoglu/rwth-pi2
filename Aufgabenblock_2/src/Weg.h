#include <iostream>
#include <list>
#include "Simulationsobjekt.h"
#include "vertagt_liste.h"
#include "Tempolimit.h"
#include "Fahrzeug.h"
#include "Kreuzung.h"

#ifndef WEG_H_
#define WEG_H_

class Fahrzeug;
class Kreuzung;

// Zur einfacheren Iterierung der Fahrzeugliste
typedef vertagt::VListe<std::unique_ptr<Fahrzeug>>::iterator vIterator;

class Weg : public Simulationsobjekt {
private:
	double p_dLaenge;
	Tempolimit p_eTempolimit;
	vertagt::VListe<std::unique_ptr<Fahrzeug>> p_pFahrzeuge;

	// Notwendig für die Implementierung der Kreuzungklasse
	bool p_bUeberholverbot;
	std::weak_ptr<Weg> p_pRueckweg;
	const std::weak_ptr<Kreuzung> p_pKreuzung;
public:
	// Standardkonstruktor
	Weg();

	// Konstruktor
	// 	sName : Name des Weges
	//	dLanege : Länge des Weges in km
	// 	dTempolimit : Tempolimit auf dem Weg in km/h (Standardmäßig keine Begrenzung)
	Weg(std::string sName, double dLaenge, Tempolimit eTempolimit = AUTOBAHN);

	// Konstruktor für die Kreuzungimplementierung
	Weg(std::string sName, double dLaenge, std::weak_ptr<Kreuzung> pKreuzung, Tempolimit eTempolimit = AUTOBAHN, bool bUeberholverbot = true);

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
	double getLaenge() const {
		return p_dLaenge;
	}

	// Returned einen bool für das Ueberholverbot
	bool getUeberholverbot() {
		return p_bUeberholverbot;
	}

	// Fahrzeuge als vertagt_liste
	vertagt::VListe<std::unique_ptr<Fahrzeug>>* getFahrzeuge() {
		return &p_pFahrzeuge;
	}

	// Hinzufügen eines Fahrzeuges in den Weg (Fahren & Parken)
	void vAnnahme(std::unique_ptr<Fahrzeug>);
	void vAnnahme(std::unique_ptr<Fahrzeug>, double dStartzeitpunkt);

	// Löschen eines Fahrzeuges aus dem Weg
	std::unique_ptr<Fahrzeug> pAbgabe(Fahrzeug&);

	// Returned den Rückweg
	Weg& getRueckweg() {
		return *p_pRueckweg.lock();
	}

	// Setzt den Rückweg
	void setRueckweg(std::weak_ptr<Weg> pRueckweg) {
		p_pRueckweg = pRueckweg;
	}

	// Returned die Kreuzung
	Kreuzung& getKreuzung() {
		return *p_pKreuzung.lock();
	}

	// Methode zum Simulieren aller Fahrzeuge;
	virtual void vSimulieren() override;

	// Ausgabemethode für die Kopfzeile
	virtual void vKopf();

	// Ausgabemethoden
	virtual void vAusgeben() override;
	virtual std::ostream& vAusgeben(std::ostream& o) override;

	// Destruktor
	virtual ~Weg();
};

// Überladung des << Operators außerhalb der Klasse
std::ostream& operator<<(std::ostream&, Weg&);

#endif

#include <iostream>
#include <iomanip>
#include "Fahrzeug.h"
#include "Verhalten.h"
#include "Parken.h"
#include "Fahren.h"
#include "Fahrausnahme.h"

// Standardkonstruktor
// Initialisierungsliste:
// 	Simulationsobjekt
Fahrzeug::Fahrzeug() : Simulationsobjekt() {
	//std::cout << "(+) " << "Fahrzeug mit dem Namen '" << p_sName << "' und der ID " << p_iID << " erzeugt." << std::endl;
}

// Konstruktor
// Initialisierungsliste:
// 	Simulationsobjekt
Fahrzeug::Fahrzeug(std::string sName) : Simulationsobjekt(sName) {
	//std::cout << "(+) " << "Fahrzeug mit dem Namen '" << p_sName << "' und der ID " << p_iID << " erzeugt." << std::endl;
}

// Konstruktor
// Initialisierungsliste:
// 	Simulationsobjekt
//	p_dMaxGeschwindigkeit wird zur dMaxGeschwindigkeit in dem Funktionsparameter, wenn es positiv ist ansonsten wird p_dMaxGeschwindigkeit auf 0 gesetzt
Fahrzeug::Fahrzeug(std::string sName, double dMaxGeschwindigkeit) :
		Simulationsobjekt(sName),
		p_dMaxGeschwindigkeit((dMaxGeschwindigkeit > 0) ? dMaxGeschwindigkeit : 0) {
	//std::cout << "(+) " << "Fahrzeug mit dem Namen '" << p_sName << "', der ID " << p_iID << " und der maximalen Geschwindigkeit von " << p_dMaxGeschwindigkeit << " erzeugt." << std::endl;
}

// Destruktor
Fahrzeug::~Fahrzeug() {
	//std::cout << "Fahrzeug mit dem Namen '" << p_sName << "' und der ID " << p_iID << " gelöscht." << std::endl;
}

// Definition der Memberfunktion vKopf()
void Fahrzeug::vKopf() {
	std::cout << std::resetiosflags(std::ios::adjustfield)
			<< std::setiosflags(std::ios::left)
			<< std::setw(6) << "ID"
			<< std::setw(10) << "Name"
			<< std::resetiosflags(std::ios::adjustfield)
			<< std::setiosflags(std::ios::right)
			<< std::setw(30) << "MaxGeschwindigkeit"
			<< std::setw(30) << "Geschwindigkeit"
			<< std::setw(30) << "Gesamtstrecke"
			<< std::setw(30) << "Abschnittstrecke"
			<< std::setw(30) << "Gesamtverbrauch"
			<< std::setw(30) << "Tankinhalt"
			<< std::endl
			<< std::setw(6+10+30*6)
			<< std::setfill('-')
			<< "-"
			<< std::setfill(' ')
			<< std::endl;
}


// Definition der Memberfunktion vAusgeben()
void Fahrzeug::vAusgeben() {
	std::cout << std::resetiosflags(std::ios::adjustfield)
			<< std::setiosflags(std::ios::right)
			<< std::setw(30) << p_dMaxGeschwindigkeit
			<< std::setw(30) << dGeschwindigkeit()
			<< std::setw(30) << p_dGesamtStrecke
			<< std::setw(30) << p_dAbschnittStrecke;
}

// Definition der Memberfunktion vSimulieren()
void Fahrzeug::vSimulieren() {
	// Gucken, ob die Simulation für diesen Zeitschritt bereits unternommen wurde
	if(p_dZeit == dGlobaleZeit) return;

	// Der Zeitraum, in welchem das Fahrzeug simuliert wird
	double dZeitraum = dGlobaleZeit - p_dZeit;

	// Exception Handling Fahrausnahme
	// Berechnung der Teilstrecke durch die dStrecke Methode in Verhalten
	double dTeilstrecke = p_pVerhalten->dStrecke(*this, dZeitraum);

	// --- Wird von dStrecke übernommen ---
	//	setAbschnittStrecke(dTeilstrecke);

	// Die neue Zeit der letzten Simulation zu der globalen Zeit setzen
	p_dGesamtZeit += dZeitraum;
	p_dZeit = dGlobaleZeit;
}

// Definition der Memberfunktion dTanken()
// 	Gibt standardmäßig 0L zurück
double Fahrzeug::dTanken(double dMenge) {
	return 0.0;
}

// Erzeugung eines geeigneten Objekts (Fahren) und Speichern in p_pVerhalten
void Fahrzeug::vNeueStrecke(Weg& weg) {
	// Bei Vorhandensein eines Verhaltens, Löschen des Verhaltens
	if(p_pVerhalten) {
		delete p_pVerhalten;
	}
	p_pVerhalten = new Fahren(weg);
}

// Erzeugung eines geeigneten Objekts (Parken) und Speichern in p_pVerhalten
void Fahrzeug::vNeueStrecke(Weg& weg, double dStartzeitpunkt) {
	// Bei Vorhandensein eines Verhaltens, Löschen des Verhaltens
	if(p_pVerhalten) {
		delete p_pVerhalten;
	}
	p_pVerhalten = new Parken(weg, dStartzeitpunkt);
}

// Definition der Memberfunktion vAusgeben()
std::ostream& Fahrzeug::vAusgeben(std::ostream& o) {
	o << std::resetiosflags(std::ios::adjustfield)
			<< std::setiosflags(std::ios::right)
			<< std::setw(30) << p_dMaxGeschwindigkeit
			<< std::setw(30) << p_dMaxGeschwindigkeit
			<< std::setw(30) << p_dGesamtStrecke;
	return o;
}

// Überladung des < Operators
// Überprüfen ob die GesamtStrecke des Fahrzeuges kleiner ist als die des Vergleichsobjekts
bool Fahrzeug::operator<(const Fahrzeug& fahrzeug) {
	return (p_dGesamtStrecke < fahrzeug.p_dGesamtStrecke);
}

// Überladung des = Operators
// Nur die Stammdaten (Daten bei der Erstellung) werden kopiert
// Wichtig, dass ID nicht mitkopiert wird, da die ID ein einzigartiges Merkmal sein soll
Fahrzeug& Fahrzeug::operator=(const Fahrzeug& fahrzeug) {
	p_sName = fahrzeug.p_sName;
	p_dGesamtStrecke = fahrzeug.p_dGesamtStrecke;
	p_dMaxGeschwindigkeit = fahrzeug.p_dMaxGeschwindigkeit;
	p_dGesamtZeit = fahrzeug.p_dGesamtZeit;
	p_dZeit = fahrzeug.p_dZeit;
	return *this;
}

// Überladung des << Operators
std::ostream& operator<<(std::ostream& o, Fahrzeug& fahrzeug) {
	fahrzeug.vAusgeben(o);
	return o;
}


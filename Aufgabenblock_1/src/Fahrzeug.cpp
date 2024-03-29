#include <iostream>
#include <iomanip>
#include "Fahrzeug.h"

// Das statische Datenelement Max ID am Anfang auf 0 setzen
int Fahrzeug::p_iMaxID = 0;

// Standardkonstruktor
// Initialisierungsliste:
// 	p_iID wird zu dem inkrementiertem p_iMaxID
Fahrzeug::Fahrzeug() :
		p_iID(++p_iMaxID) {
	std::cout << "(+) " << "Fahrzeug mit dem Namen '" << p_sName << "' und der ID " << p_iID << " erzeugt." << std::endl;
}

// Konstruktor
// Initialisierungsliste:
// 	p_sName wird zu sName in dem Funktionsparameter
//	p_iID wird zu dem inkrementiertem p_iMaxID
Fahrzeug::Fahrzeug(std::string sName) :
		p_sName(sName),
		p_iID(++p_iMaxID) {
	std::cout << "(+) " << "Fahrzeug mit dem Namen '" << p_sName << "' und der ID " << p_iID << " erzeugt." << std::endl;
}

// Konstruktor
// Initialisierungsliste:
// 	p_sName wird zu sName in dem Funktionsparameter
//	p_dMaxGeschwindigkeit wird zur dMaxGeschwindigkeit in dem Funktionsparameter, wenn es positiv ist ansonsten wird p_dMaxGeschwindigkeit auf 0 gesetzt
//	p_iID wird zu dem inkrementiertem p_iMaxID
Fahrzeug::Fahrzeug(std::string sName, double dMaxGeschwindigkeit) :
		p_sName(sName),
		p_iID(++p_iMaxID),
		p_dMaxGeschwindigkeit((dMaxGeschwindigkeit > 0) ? dMaxGeschwindigkeit : 0) {
	std::cout << "(+) " << "Fahrzeug mit dem Namen '" << p_sName << "', der ID " << p_iID << " und der maximalen Geschwindigkeit von " << p_dMaxGeschwindigkeit << " erzeugt." << std::endl;
}

// Destruktor
Fahrzeug::~Fahrzeug() {
	std::cout << "Fahrzeug mit dem Namen '" << p_sName << "' und der ID " << p_iID << " gelöscht." << std::endl;
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
			<< std::setw(30) << "Gesamtverbrauch"
			<< std::setw(30) << "Tankinhalt"
			<< std::endl
			<< std::setw(6+10+30*5)
			<< std::setfill('-')
			<< "-"
			<< std::setfill(' ')
			<< std::endl;
}


// Definition der Memberfunktion vAusgeben()
void Fahrzeug::vAusgeben() {
	std::cout << std::resetiosflags(std::ios::adjustfield)
			<< std::setiosflags(std::ios::left)
			<< std::setw(6) << p_iID
			<< std::setw(10) << p_sName
			<< std::resetiosflags(std::ios::adjustfield)
			<< std::setiosflags(std::ios::right)
			<< std::setw(30) << p_dMaxGeschwindigkeit
			<< std::setw(30) << dGeschwindigkeit()
			<< std::setw(30) << p_dGesamtStrecke;
}

// Definition der Memberfunktion vSimulieren()
void Fahrzeug::vSimulieren() {
	// Gucken, ob die Simulation für diesen Zeitschritt bereits unternommen wurde
	if(p_dZeit == dGlobaleZeit) return;

	// Der Zeitraum, in welchem das Fahrzeug simuliert wird
	double dZeitraum = dGlobaleZeit - p_dZeit;

	// Die Gesamtstrecke, die das Fahrzeug innerhalb des Zeitraums mit der Maximalgeschwindigkeit fährt
	p_dGesamtStrecke += dGeschwindigkeit() * dZeitraum;

	// Die neue Zeit der letzten Simulation zu der globalen Zeit setzen
	p_dGesamtZeit += dZeitraum;
	p_dZeit = dGlobaleZeit;
}

// Definition der Memberfunktion dTanken()
// 	Gibt standardmäßig 0L zurück
double Fahrzeug::dTanken(double dMenge) {
	return 0.0;
}

// Definition der Memberfunktion vAusgeben()
void Fahrzeug::vAusgeben(std::ostream& o) const {
	o << std::resetiosflags(std::ios::adjustfield)
			<< std::setiosflags(std::ios::left)
			<< std::setw(6) << p_iID
			<< std::setw(10) << p_sName
			<< std::resetiosflags(std::ios::adjustfield)
			<< std::setiosflags(std::ios::right)
			<< std::setw(30) << p_dMaxGeschwindigkeit
			<< std::setw(30) << p_dMaxGeschwindigkeit
			<< std::setw(30) << p_dGesamtStrecke;
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
std::ostream& operator<<(std::ostream& o, const Fahrzeug& fahrzeug) {
	fahrzeug.vAusgeben(o);
	return o;
}


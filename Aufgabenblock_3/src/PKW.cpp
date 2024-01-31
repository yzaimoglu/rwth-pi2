#include <iomanip>
#include <cmath>
#include "PKW.h"
#include "SimuClient.h"

// Standardkonstruktor
PKW::PKW() : Fahrzeug() {
	std::cout << "Das Fahrzeug ist ein PKW mit einem Verbrauch von " <<
			p_dVerbrauch <<
			" und einem Tankvolumen " <<
			p_dTankvolumen <<
			"." <<
			std::endl;
}

// Konstruktor
// Initialisierungsliste:
// 	p_sName kommt von dem Fahrzeugkonstruktor
PKW::PKW(std::string sName) : Fahrzeug(sName) {
	std::cout << "Das Fahrzeug ist ein PKW mit einem Verbrauch von " <<
			p_dVerbrauch <<
			" und einem Tankvolumen " <<
			p_dTankvolumen <<
			"." <<
			std::endl;
}

// Konstruktor
// Initialisierungsliste:
// 	p_sName und p_dMaxGeschwindigkeit kommen von dem Fahrzeugkonstruktor
PKW::PKW(std::string sName, double dMaxGeschwindigkeit) : Fahrzeug(sName, dMaxGeschwindigkeit) {
	std::cout << "Das Fahrzeug ist ein PKW mit einem Verbrauch von " <<
			p_dVerbrauch <<
			" und einem Tankvolumen " <<
			p_dTankvolumen <<
			"." <<
			std::endl;
}

// Konstruktor
// Initialisierungsliste:
// 	p_sName und p_dMaxGeschwindigkeit kommen von dem Fahrzeugkonstruktor
//	p_dVerbrauch wird zu dVerbrauch
//	p_dTankvolumen wird zu dTankvolumen
//	p_dTaninhalt wird zu der Hälfte des dTankvolumens
PKW::PKW(std::string sName, double dMaxGeschwindigkeit, double dVerbrauch, double dTankvolumen) :
		Fahrzeug(sName, dMaxGeschwindigkeit),
		p_dVerbrauch(dVerbrauch),
		p_dTankvolumen(dTankvolumen),
		p_dTankinhalt(dTankvolumen / 2) {
	std::cout << "Das Fahrzeug ist ein PKW mit einem Verbrauch von " <<
			p_dVerbrauch <<
			" und einem Tankvolumen " <<
			p_dTankvolumen <<
			"." <<
			std::endl;
}

// Destruktor
PKW::~PKW() {
	std::cout << "(-) " << "Das Fahrzeug ist ein PKW." << std::endl;
}

// Definition für die override Memberfunktion dTanken()
double PKW::dTanken(double dMenge) {
	if(p_dTankinhalt == p_dTankvolumen) return 0;
	if(dMenge >= p_dTankvolumen - p_dTankinhalt) {
		dMenge = p_dTankvolumen - p_dTankinhalt;
		p_dTankinhalt = p_dTankvolumen;
		return dMenge;
	}

	p_dTankinhalt += dMenge;
	return dMenge;
}

// Definition für die override Memberfunktion vSimulieren()
void PKW::vSimulieren() {
	// Wenn der Tank leer ist soll nicht simuliert werden
	if(p_dTankinhalt == 0) {
		p_dZeit = dGlobaleZeit;
		return;
	}

	// GesamtStrecke vor der Simulation notwendig, damit die Simulationsstrecke berechnet werden kann
	double dGesamtStreckeVorSim = p_dGesamtStrecke;
	Fahrzeug::vSimulieren();

	// Berechnung des verbleibenden Tankinhalts durch den Verbrauch und die Simulationsstrecke
	// Das ganze wird durch 100 geteilt, da der Verbrauch eine Einheit von Liter/100km hat
	double verbrauch = p_dVerbrauch * (p_dGesamtStrecke - dGesamtStreckeVorSim) / 100;
	p_dTankinhalt -= verbrauch;

	// Zur Vereinfachung soll der PKW die restliche Teilstrecke auch ohne Tankinhalt fahren können
	// Deswegen kann der Tankinhalt bei der Simulation negativ werden,
	// falls das der Fall ist wird der Tankinhalt auf 0 gesetzt
	if(p_dTankinhalt < 0) p_dTankinhalt = 0;
}

// Zeichnen des PKWs im Simuserver
void PKW::vZeichnen(const Weg& weg) const {
	double relPos = p_dAbschnittStrecke / weg.getLaenge();
	bZeichnePKW(p_sName, weg.getName(), relPos, dGeschwindigkeit(), p_dTankinhalt);
}

// Definition für die override Memberfunktion vAusgeben()
void PKW::vAusgeben() const {
	// Der Gesamtverbrauch wird durch die GesamtStrecke und den Verbrauch pro 100km berechnet
	double dGesamtverbrauch = p_dGesamtStrecke / 100 * p_dVerbrauch;
	Simulationsobjekt::vAusgeben();
	Fahrzeug::vAusgeben();
	std::cout << std::setw(30)
		<< std::round(dGesamtverbrauch * 1000.0) / 1000.0
		<< std::setw(30)
		<< std::round(p_dTankinhalt * 1000.0) / 1000.0
		<< std::endl;
}

// Definition für die override Memberfunktion vAusgeben()
std::ostream& PKW::vAusgeben(std::ostream& o) const {
	// Der Gesamtverbrauch wird durch die GesamtStrecke und den Verbrauch pro 100km berechnet
	double dGesamtverbrauch = p_dGesamtStrecke / 100 * p_dVerbrauch;
	Simulationsobjekt::vAusgeben(o);
	Fahrzeug::vAusgeben(o);
	o << std::setw(30)
		<< std::round(dGesamtverbrauch * 1000.0) / 1000.0
		<< std::setw(30)
		<< std::round(p_dTankinhalt * 1000.0) / 1000.0
		<< std::endl;

//	std::cout << p_sName << std::endl;
//	std::cout << p_dMaxGeschwindigkeit << std::endl;
//	std::cout << p_dVerbrauch << std::endl;
//	std::cout << p_dTankvolumen << std::endl;

	return o;
}

std::istream& PKW::vEinlesen(std::istream& is) {
	Fahrzeug::vEinlesen(is) >> p_dVerbrauch >> p_dTankvolumen;
	return is;
}

std::ostream& operator<<(std::ostream& os, const PKW& pkw) {
	pkw.vAusgeben(os);
	return os;
}

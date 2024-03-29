#pragma once
#include <iostream>

#ifndef FAHRZEUG_H_
#define FAHRZEUG_H_

extern double dGlobaleZeit;

// Klasse Fahrzeug
class Fahrzeug {
private:
	static int p_iMaxID;
protected:
	std::string p_sName = "";
	const int p_iID = 0;

	// Maximale Geschwindigkeit
	double p_dMaxGeschwindigkeit = 0;

	// Bisher zurückgelegte Gesamtstrecke
	double p_dGesamtStrecke = 0;

	// Gesamte Fahrtzeit des Objekts
	double p_dGesamtZeit = 0;

	// Zeit der letzten Simulation
	double p_dZeit = 0;
public:
	// Standardkonstruktor
	Fahrzeug();

	// Konstruktor mit dem Namen
	Fahrzeug(std::string sName);

	// Konstruktor mit dem Namen und der maximalen Geschwindigkeit
	Fahrzeug(std::string sName, double dMaxGeschwindkeit);

	// Funktion für die Überschrift der Tabelle für vAusgeben()
	static void vKopf();

	// Funktion zum Simulieren
	virtual void vSimulieren();

	// Funktion für die aktuelle Geschwindigkeit
	virtual double dGeschwindigkeit() {
		return p_dMaxGeschwindigkeit;
	};

	// Funktion zum Tanken
	// Standardwert so, dass der Tank vollgetankt wird
	virtual double dTanken(double dMenge = std::numeric_limits<double>::infinity());

	// Funktion zur tabellarischen Ausgabe der Spezifikationen des Fahrzeugs
	virtual void vAusgeben();

	// Funktion zur Ausgabe der Daten, genutzt zusammen mit der Überladung des Operators <<
	virtual void vAusgeben(std::ostream&) const;

	// Überladung von einigen Operatoren (< & =)
	bool operator<(const Fahrzeug& fahrzeug);
	Fahrzeug& operator=(const Fahrzeug& fahrzeug);

	// Verbieten des Copy-Konstruktors
	// Sinnvoll, da jedes Mal wenn eine Variable an eine Funktion nicht als Referenz übergegeben wird
	// der Copykonstruktor aufgerufen wird.
	// Es kann bei dynamischen Datenstrukturen oder eindeutigen Kennzeichnungen innerhalb einer Klasse zu sog. "wilden Zeigern" kommen
	Fahrzeug(const Fahrzeug&) = delete;

	// Destruktor
	virtual ~Fahrzeug();
};

// Überladung des << Operators außerhalb der Klasse
std::ostream& operator<<(std::ostream&, const Fahrzeug&);

#endif

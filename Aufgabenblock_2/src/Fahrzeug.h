#pragma once
#include <iostream>
#include "Weg.h"
#include "Verhalten.h"

#ifndef FAHRZEUG_H_
#define FAHRZEUG_H_

extern double dGlobaleZeit;

// Klasse Fahrzeug
class Fahrzeug : public Simulationsobjekt {
protected:
	// Maximale Geschwindigkeit
	double p_dMaxGeschwindigkeit = 0;

	// Bisher zurückgelegte Gesamtstrecke
	double p_dGesamtStrecke = 0;

	// Bisher zurückgelegte Strecke auf dem Abschnitt
	double p_dAbschnittStrecke = 0;

	// Gesamte Fahrtzeit des Objekts
	double p_dGesamtZeit = 0;

	// Zeit der letzten Simulation
	double p_dZeit = 0;

	// Verhalten Klasse, wo auch der Weg gespeichert ist
	Verhalten *p_pVerhalten;
public:
	// Standardkonstruktor
	Fahrzeug();

	// Konstruktor mit dem Namen
	Fahrzeug(std::string sName);

	// Konstruktor mit dem Namen und der maximalen Geschwindigkeit
	Fahrzeug(std::string sName, double dMaxGeschwindkeit);

	// Getter für die Gesamtstrecke
	double getGesamtStrecke() {
		return p_dGesamtStrecke;
	}

	// Setter für die Gesamtstrecke
	void setGesamtStrecke(double dGesamtStrecke) {
		p_dGesamtStrecke += dGesamtStrecke;
	}

	// Getter für die Abschnittstrecke
	double getAbschnittStrecke() {
		return p_dAbschnittStrecke;
	}

	// Setter für die Abschnittstrecke
	void setAbschnittStrecke(double dAbschnittStrecke) {
		p_dAbschnittStrecke += dAbschnittStrecke;
		// Aufrufen des Setters für die Gesamtstrecke
		setGesamtStrecke(dAbschnittStrecke);
	}

	// Setzt die Abschnittstrecke auf 0, genutzt bei Erreichen des Streckenendes
	void resetAbschnittStrecke() {
		p_dAbschnittStrecke = 0;
	}

	// Funktion für die Überschrift der Tabelle für vAusgeben()
	static void vKopf();

	// Funktion zur Speicherung des Verhaltens
	void vNeueStrecke(Weg& weg);
	void vNeueStrecke(Weg& weg, double dStartzeitpunkt);

	// Funktion zum Simulieren
	virtual void vSimulieren();

	// Funktion für die aktuelle Geschwindigkeit
	virtual double dGeschwindigkeit() const {
		return p_dMaxGeschwindigkeit;
	}

	// Funktion zum Tanken
	// Standardwert so, dass der Tank vollgetankt wird
	virtual double dTanken(double dMenge = std::numeric_limits<double>::infinity());

	// Funktion zur tabellarischen Ausgabe der Spezifikationen des Fahrzeugs
	virtual void vAusgeben();

	// Funktion zum Zeichnen in den Simulationsserver
	virtual void vZeichnen(const Weg&) const {};

	// Funktion zur Ausgabe der Daten, genutzt zusammen mit der Überladung des Operators <<
	virtual std::ostream& vAusgeben(std::ostream&);

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
std::ostream& operator<<(std::ostream&, Fahrzeug&);

#endif

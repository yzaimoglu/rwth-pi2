#pragma once
#pragma warning (disable:4786)
#include <string>

#define SIMUCLIENT_API 
//#define _WIN32_WINNT 0x0502
#define USE_GENERIC_BUT_CPU_INTENSIVE_SLEEP 1

// NUTZBARE FUNKTIONEN (offizielle Schnittstelle)
/* 
Verbindung zum Grafikserver wird mit Hilfe der Adresse hergestellt und die Groesse des Fensters wird mit Hilfe der Fenstergroesse X und Y bestimmt.
Beispiel: bInitialisiereGrafik(800,500);
*/
SIMUCLIENT_API bool bInitialisiereGrafik(int iFenstergroesseX, int iFenstergroesseY, const char* adresse = "127.0.0.1", const char* port = "7654");

/*
Es wird eine Kreuzung an den Koordinaten X und Y gezeichnet
*/
SIMUCLIENT_API bool bZeichneKreuzung(int koordinateX, int koordinateY);

/* 
Eine Strasse wird mit dem Hin- und Rueckweg der angegebenen Laenge gezeichnet. Die Strasse wird mit einer Reihe von Punkten erzeugt. 
Mindestens werden 2 Punkte (Gerade) benoetigt. Die Anzahl der Koordinaten ist immer ein X/Y-Paar.
Beispiel:	int feld[] = { 100 , 200 , 300 , 400 }; int anzahl = 2;
			bZeichneStrasse("Hin", "Rueck", 40, anzahl, feld);
*/
SIMUCLIENT_API bool bZeichneStrasse(const std::string& nameHinweg, const std::string& nameRueckweg, int iLaenge, int iAnzahlKoordinaten, int* pFeldKoordinaten);

/*
	Es wird ein PKW auf dem angegebenen Weg dargestellt. RelPosition ist die relativ zur Weglaenge zurueckgelegte Stelle (Wert zwischen 0 und 1).
	bZeichnePKW("Rennauto", "Rennstrecke" , AbschnittStrecke / WegLaenge, 250, 80);
}
*/
SIMUCLIENT_API bool bZeichnePKW(const std::string& namePKW, const std::string& nameWeg, double dRelPosition, double dGeschwindigkeit, double dTankinhalt);

/*
	Es wird ein Fahrrad auf dem angegebenen Weg dargestellt. RelPosition ist die relativ zur Weglaenge zurueckgelegte Stelle (Wert zwischen 0 und 1).
	bZeichneFahrrad("Drahtesel", "Fahrradstrasse" , AbschnittStrecke / WegLaenge, 15);
*/
SIMUCLIENT_API bool bZeichneFahrrad(const std::string& nameFahrrad, const std::string& nameWeg, double dRelPosition, double dGeschwindigkeit);

/*
Die Verbindung zum Grafikserver wird getrennt und das Fenster wird geschlossen.
*/
SIMUCLIENT_API void vBeendeGrafik();

/* Das uebergebene Fahrzeug wird aus der Grafikanwendung herausgenommen*/
SIMUCLIENT_API bool bLoescheFahrzeug(const std::string& name);

/* Die globale Zeit wird in der Titelzeile des Ausgabefensters angezeigt
*/
SIMUCLIENT_API void vSetzeZeit(const double globaleZeit);

// Wrapperfunktion fuer Sleep
/*
	Die Programmausfuerung wird um die anzahl Millisekunden verzoegert.
*/
SIMUCLIENT_API void vSleep(int anzahlMillisekunden);

// Zusätzliche Schnittstellen (wegen Konvertierungsproblemen bei char*/string)

SIMUCLIENT_API bool bZeichneStrasse(const char* nameHinweg, const char* nameRueckweg, int iLaenge, int iAnzahlKoordinaten, int* pFeldKoordinaten);
SIMUCLIENT_API bool bZeichneStrasse(const std::string& nameHinweg, const char* nameRueckweg, int iLaenge, int iAnzahlKoordinaten, int* pFeldKoordinaten);
SIMUCLIENT_API bool bZeichneStrasse(const char* nameHinweg, const std::string& nameRueckweg, int iLaenge, int iAnzahlKoordinaten, int* pFeldKoordinaten);

SIMUCLIENT_API bool bZeichnePKW(const char*  namePKW, const char* nameWeg, double dRelPosition, double dGeschwindigkeit, double dTankinhalt);
SIMUCLIENT_API bool bZeichnePKW(const std::string& namePKW, const char* nameWeg, double dRelPosition, double dGeschwindigkeit, double dTankinhalt);
SIMUCLIENT_API bool bZeichnePKW(const char*  namePKW, const std::string& nameWeg, double dRelPosition, double dGeschwindigkeit, double dTankinhalt);

SIMUCLIENT_API bool bZeichneFahrrad(const std::string& nameFahrrad, const char* nameWeg, double dRelPosition, double dGeschwindigkeit);
SIMUCLIENT_API bool bZeichneFahrrad(const char*  nameFahrrad, const char* nameWeg, double dRelPosition, double dGeschwindigkeit);
SIMUCLIENT_API bool bZeichneFahrrad(const char*  nameFahrrad, const std::string& nameWeg, double dRelPosition, double dGeschwindigkeit);

SIMUCLIENT_API bool bLoescheFahrzeug(const char* name);

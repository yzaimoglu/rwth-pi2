#include <iostream>
#include <memory>
#include <iomanip>
#include <vector>
#include <cmath>
#include <random>
#include "Fahrzeug.h"
#include "Fahrrad.h"
#include "PKW.h"
#include "Weg.h"
#include "Simulationsobjekt.h"
#include "Tempolimit.h"
#include "SimuClient.h"
#include "vertagt_liste.h"


// Die globale Variable dGlobaleZeit, damit die Fahrzeuge wissen, wie lange diese simulieren sollen
double dGlobaleZeit;

// using namespace std;

void vAufgabe_1() {
	// Standardkonstruktor -> statisches Erzeugen von fahrzeug1
	Fahrzeug fahrzeug1;

	// Konstruktor mit dem Namen -> statisches Erzeugen von fahrzeug2
	Fahrzeug fahrzeug2("VW");

	// Dynamisches Erzeugen von fahrzeug3 und fahrzeug4
	Fahrzeug* fahrzeug3 = new Fahrzeug();
	Fahrzeug* fahrzeug4 = new Fahrzeug("BMW");

	// Nutzung von Smart-Pointern für die Konstruktion von Fahrzeugen
	// unique_ptr = Zeiger auf nur ein einziges Objekt (Pointer hat Besitz des Objekts)
	//	Objekt wird zerstört, wenn Unique-Pointer zerstört wird
	//	Übergabe des Besitzes durch move()
	// shared_ptr = mehrere Zeiger auf ein geimeinsames Objekt (alle Pointer haben Besitz des Objekts)
	//	Objekt wird zerstört, wenn kein gemeinsamer Zeiger mehr auf das Objekt zeigt
	//	Overhead (Zähler)
	// weak_ptr = Zeiger erzeugt aus shared_ptr (ohne Besitz am Objekt)
	//	Objekt nur verwendbar, wenn shared_ptr auf Objekt besteht
	std::unique_ptr<Fahrzeug> fahrzeug5 = std::make_unique<Fahrzeug>("Mercedes");
	std::unique_ptr<Fahrzeug> fahrzeug6 = std::make_unique<Fahrzeug>("Chevrolet");
	std::shared_ptr<Fahrzeug> fahrzeug7 = std::make_shared<Fahrzeug>("Ford");
	std::shared_ptr<Fahrzeug> fahrzeug8 = std::make_shared<Fahrzeug>("Jaguar");

	// useCount() gibt die Anzahl der Referenzen eines Objekts an
	std::cout << "useCount() vor Konstruktion fahrzeug9 = " << fahrzeug8.use_count() << std::endl;
	std::shared_ptr<Fahrzeug> fahrzeug9 = fahrzeug8;
	std::cout << "useCount() vor Konstruktion fahrzeug10 = " << fahrzeug8.use_count() << std::endl;
	std::shared_ptr<Fahrzeug> fahrzeug10 = fahrzeug8;
	std::cout << "useCount() nach Konstruktion fahrzeug10 = " << fahrzeug8.use_count() << std::endl;

	// Erstellen eines Vektors für die Fahrzeuge konstruiert durch unique_ptr
	std::vector<std::unique_ptr<Fahrzeug>> vector1;

	// Speichern von fahrzeug5 und fahrzeug6 in dem vector1
	// Nur Fahrzeuge, die mit einem unique pointer konstruiert worden können in diesem Vektor gespeichert werden
	vector1.push_back(move(fahrzeug5));
	vector1.push_back(move(fahrzeug6));

	// Durch das Ausführen der clear()-Methode werden alle Objekte im Vektor schrittweise durch den eigenen Destruktor gelöscht -> fahrzeug6 und fahrzeug5 werden gelöscht
	std::cout << "Anfang vector1.clear()" << std::endl;
	vector1.clear();
	std::cout << "Ende vector1.clear()" << std::endl;

	// Erstellen eines Vektors für die Fahrzeuge konstruiert durch shared_ptr
	std::vector<std::shared_ptr<Fahrzeug>> vector2;

	// Speichern von fahrzeug8 und fahrzeug9 in dem vector2
	// Nur Fahrzeuge, die mit einem shared pointer konstruiert worden können in diesem Vektor gespeichert werden.
	// Durch das Hinzufügen eines Fahrzeugs in einen Vektor ohne move() erhöht sich die Anzahl der Referenzen um 1,
	// wohingegen beim Hinzufügen mit move() keine Erhöhung der Referenzenanzahl zu sehen ist.
	std::cout << "useCount() vor vector2.push_back(fahrzeug8) = " << fahrzeug8.use_count() << std::endl;
	vector2.push_back(fahrzeug8);
	std::cout << "useCount() vor vector2.push_back(fahrzeug9) = " << fahrzeug8.use_count() << std::endl;
	vector2.push_back(move(fahrzeug9));
	std::cout << "useCount() nach vector2.push_back(fahrzeug9) = " << fahrzeug8.use_count() << std::endl;


	// Durch das Ausführen der clear()-Methode werden keine Objekte gelöscht
	std::cout << "Anfang vector2.clear()" << std::endl;
	vector2.clear();
	std::cout << "Ende vector2.clear()" << std::endl;

	// Löschen der dynamisch erzeugten Elemente
	delete fahrzeug3;
	delete fahrzeug4;

	// Löschen der Fahrzeuge fahrzeug 8 und fahrzeug 7
}	// Löschen der statisch erzeugten Fahrzeuge fahrzeug1 und fahrzeug2, da deren Gültigkeitsbereich hier aufhört

void vAufgabe_1a() {
	// Definieren des Zeitschritts
	double dZeitschritt = 0.2;
	int iAnzahlZeitschritte = 5;

	// Erstellen des Vektors zum Abspeichern der drei Fahrzeuge und Abspeichern
	std::vector<std::unique_ptr<Fahrzeug>> fahrzeugVektor;

	// Die zu lesende Variablen
	std::string sName;
	double dMaxGeschwindigkeit;

	// Schleife zum Lesen von Fahrzeugen (3x)
	for(int i = 1; i < 3+1; i++) {
		// Einlesen des Namen und der Geschwindigkeit des Fahrzeugs
		std::cout << "(" << i << ") " << "Geben Sie bitte den Namen des " << i << ". Fahrzeugs an: " << std::endl;
		std::cin >> sName;
		std::cout << "(" << i << ") " << "Geben Sie bitte die maximale Geschwindigkeit des " << i << ". Fahrzeugs an: " << std::endl;
		std::cin >> dMaxGeschwindigkeit;

		// Erzeugen des Fahrzeugs mithilfe des unique_ptr
		std::unique_ptr<Fahrzeug> fahrzeug = std::make_unique<Fahrzeug>(sName, dMaxGeschwindigkeit);

		// Hinzufügen des Fahrzeugs in den fahrzeugVektor
		fahrzeugVektor.push_back(move(fahrzeug));
		std::cout << std::endl;
	}

	// Schleife zum Wiederholen der Zeitschritte bis es die dAnzahlZeitschritte erreicht
	for(int i = 1; i < iAnzahlZeitschritte+1; i++) {
		dGlobaleZeit += dZeitschritt;
		std::cout << std::setw(50) << std::setfill('-') << "-" << std::setfill(' ') << std::endl;
		std::cout << "Globale-Zeit: " << dGlobaleZeit << std::endl;
		std::cout << std::setw(50) << std::setfill('-') << "-" << std::setfill(' ') << std::endl;

		Fahrzeug::vKopf();
		// Schleife zum Iterieren vom fahrzeugVektor
		for(int j = 0; j < fahrzeugVektor.size(); j++) {
			fahrzeugVektor[j]->vSimulieren();
			fahrzeugVektor[j]->vAusgeben();
			std::cout << std::endl;
		}
	}
}

void vAufgabe_2() {
	// Vektor für die Fahrzeuge
	// unique_ptr Fahrzeug, da sowohl PKWs und Fahrräder von der Klasse Fahrzeug erben, somit sind sie vom Typ her Fahrzeug
	std::vector<std::unique_ptr<Fahrzeug>> fahrzeugVektor;

	// Anzahl der PKWs und der Fahrräder
	int iPKWAnzahl, iFahrradAnzahl;

	// Die zu lesenden Variablen
	std::string sName;
	double dMaxGeschwindigkeit, dVerbrauch, dTankvolumen;

	// Abfrage zur PKW Anzahl
	std::cout << "Wie viele PKWs sollen erzeugt werden? ";
	std::cin >> iPKWAnzahl;

	// Schleife zum Wiederholen des Einlesevorgangs bis die gewünschte PKW-Anzahl erreicht ist
	for(int i = 1; i < iPKWAnzahl+1; i++) {
		// Könnte auch in zwei Zeilen gemacht werden, sieht aber so ästhetischer aus
		// std::cout << "PKW #" << i << ": Geben Sie den Fahrzeugnamen, die Maximalgeschwindigkeit, den Verbrauch und das Tankvolumen ein: " << std::endl;
		// std::cin << sName << dMaxGeschwindigkeit << dVerbrauch << dTankvolumen;
		std::cout << "PKW #" << i << std::endl;
		std::cout << "Geben sie den Fahrzeugnamen ein: " << std::endl;
		std::cin >> sName;
		std::cout << "Geben sie die Maximalgeschwindigkeit ein: " << std::endl;
		std::cin >> dMaxGeschwindigkeit;
		std::cout << "Geben sie den Verbrauch ein: " << std::endl;
		std::cin >> dVerbrauch;
		std::cout << "Geben sie den Tankvolumen ein: " << std::endl;
		std::cin >> dTankvolumen;

		fahrzeugVektor.push_back(std::make_unique<PKW>(sName, dMaxGeschwindigkeit, dVerbrauch, dTankvolumen));
	}

	// Abfrage zur Fahrrad Anzahl
	std::cout << "Wie viele Fahrräder sollen erzeugt werden? ";
	std::cin >> iFahrradAnzahl;

	// Schleife zum Wiederholen des Einlesevorgangs bis die gewünschte PKW-Anzahl erreicht ist
	for(int i = 1; i < iFahrradAnzahl+1; i++) {
		// Könnte auch in zwei Zeilen gemacht werden, sieht aber so ästhetischer aus
		// std::cout << "PKW #" << i << ": Geben Sie den Fahrzeugnamen, die Maximalgeschwindigkeit, den Verbrauch und das Tankvolumen ein: " << std::endl;
		// std::cin << sName << dMaxGeschwindigkeit << dVerbrauch << dTankvolumen;
		std::cout << "Fahrrad #" << i << std::endl;
		std::cout << "Geben sie den Fahrzeugnamen ein: " << std::endl;
		std::cin >> sName;
		std::cout << "Geben sie die Maximalgeschwindigkeit ein: " << std::endl;
		std::cin >> dMaxGeschwindigkeit;

		std::unique_ptr<Fahrzeug> fahrzeug = std::make_unique<Fahrrad>(sName, dMaxGeschwindigkeit);

		fahrzeugVektor.push_back(move(fahrzeug));
	}

	// Definieren des Zeitschritts
	double dZeitschritt = 0.2;
	int iAnzahlZeitschritte = 500;
	double dTankzeit = 3.0;

	// Wiederholen des Ganzen, bis alle Zeitschritte gemacht wurden
	for(dGlobaleZeit = 0; dGlobaleZeit <= (dZeitschritt * iAnzahlZeitschritte); dGlobaleZeit += dZeitschritt) {
		std::cout << std::setw(50) << std::setfill('-') << "-" << std::setfill(' ') << std::endl;
		std::cout << "Globale-Zeit: " << dGlobaleZeit << std::endl;
		std::cout << std::setw(50) << std::setfill('-') << "-" << std::setfill(' ') << std::endl;
		Fahrzeug::vKopf();

		// Schleife zum Iterieren durch den fahrzeugVektor
		for(int i = 0; i < fahrzeugVektor.size(); i++) {
			fahrzeugVektor[i]->vSimulieren();
			fahrzeugVektor[i]->vAusgeben();
			std::cout << std::endl;

			// Volltanken der PKWs
			// Modulo Operator von den zwei doubles, da es sich hier um zwei doubles handelt und immer ein sehr kleiner Restwert entsteht
			// wird das Ergebnis durch epsilon 0.001 subtrahiert, da 0.001 genau genug ist für dieses Beispiel
			if(std::fmod(dGlobaleZeit, dTankzeit)-0.001 < 0) {
				fahrzeugVektor[i]->dTanken();
			}
		}
	}
}

void vAufgabe_3() {
	// Konstruieren von zwei Fahrzeugen: ein PKW, ein Fahrrad
	Fahrzeug* aPKW = new PKW("Porsche", 300, 10, 200.0);
	Fahrzeug* aFahrrad = new Fahrrad("BMX", 30);

	// Nutzung des überladenen Operators <<
	// Initiale Daten
	Fahrzeug::vKopf();
	std::cout << *aPKW << std::endl;
	std::cout << *aFahrrad << std::endl;

	// Initialisieren eines Fahrzeug-Arrays mit der Größe 2
	Fahrzeug* arrayFahrzeug[2] = {aPKW, aFahrrad};

	// Definieren des Zeitschritts
	double dZeitschritt = 0.2;
	int iAnzahlZeitschritte = 500;
	double dTankzeit = 3.0;

	// Wiederholen des Ganzen, bis alle Zeitschritte gemacht wurden
	for(dGlobaleZeit = 0; dGlobaleZeit <= (dZeitschritt * iAnzahlZeitschritte); dGlobaleZeit += dZeitschritt) {
		std::cout << std::setw(50) << std::setfill('-') << "-" << std::setfill(' ') << std::endl;
		std::cout << "Globale-Zeit: " << dGlobaleZeit << std::endl;
		std::cout << std::setw(50) << std::setfill('-') << "-" << std::setfill(' ') << std::endl;
		Fahrzeug::vKopf();

		// Schleife zum Iterieren durch den fahrzeugVektor
		for(int i = 0; i < 2; i++) {
			arrayFahrzeug[i]->vSimulieren();
			std::cout << *arrayFahrzeug[i] << std::endl;

			// Volltanken der PKWs
			// Modulo Operator von den zwei doubles, da es sich hier um zwei doubles handelt und immer ein sehr kleiner Restwert entsteht
			// wird das Ergebnis durch epsilon 0.001 subtrahiert, da 0.001 genau genug ist für dieses Beispiel
			if(std::fmod(dGlobaleZeit, dTankzeit)-0.001 < 0) {
				arrayFahrzeug[i]->dTanken();
			}
		}
	}

	// Nutzung des überladenen Operators <
	// Überprüfung, welches Fahrzeug weiter ist
	if(aPKW < aFahrrad) {
		std::cout << "Das Fahrrad ist von der Gesamtstrecke her weiter." << std::endl;
	} else {
		std::cout << "Der PKW ist von der Gesamtstrecke her weiter." << std::endl;
	}

	// Nutzung des überladenen Operators = und <<
	Fahrzeug aFahrrad2("Rennrad", 80);
	Fahrzeug aFahrrad3;
	aFahrrad3 = aFahrrad2;

	Fahrzeug::vKopf();
	std::cout << aFahrrad2 << std::endl;
	std::cout << aFahrrad3 << std::endl;
}

// Aufgabe für das Vortestat
/*double dEpsilon = 0.001;
void vAufgabe_AB1() {

    int l = 0; // Laufindex für gezielte AUsgabe
    vector<int> ausgabe{13};
    double dTakt = 0.4;

    std::vector<unique_ptr<Fahrzeug>> vecFahrzeuge;
    vecFahrzeuge.push_back(make_unique <PKW>("Audi", 229, 9.6));
    vecFahrzeuge.push_back(make_unique <Fahrrad>("BMX", 24.7));
    for (dGlobaleZeit = 0; dGlobaleZeit < 10; dGlobaleZeit += dTakt)
    {
        auto itL = find(ausgabe.begin(), ausgabe.end(), l);
        if (itL != ausgabe.end()) {
            std::cout << std::endl << l <<  " Globalezeit = " << dGlobaleZeit << std::endl;
            Fahrzeug::vKopf();
        }

        for (int i = 0; i < (int) vecFahrzeuge.size(); i++)
        {
            vecFahrzeuge[i]->vSimulieren();
            if (fabs(dGlobaleZeit - 3.0) < dTakt/2)
            {
                vecFahrzeuge[i]->dTanken();
            }
            if (itL != ausgabe.end()) {
                std::cout << *vecFahrzeuge[i] << endl;
            }
        }
        l++;
    }
    char c;
    std::cin >> c;
}*/

void vAufgabe_4() {
	// Erstellen eines Weges
	Weg* weg = new Weg("Teststraße", 100.0, INNERORTS);

	// Erstellen von vier Fahrzeugen
	std::unique_ptr<Fahrzeug> fahrzeug = std::make_unique<PKW>("PKW1", 100.0, 100.0, 55.0);
	std::unique_ptr<Fahrzeug> fahrzeug2 = std::make_unique<PKW>("PKW2", 100.0, 100.0, 55.0);
	std::unique_ptr<Fahrzeug> fahrzeug3 = std::make_unique<PKW>("PKW3", 100.0, 100.0, 55.0);
	std::unique_ptr<Fahrzeug> fahrzeug4 = std::make_unique<Fahrrad>("Fahrrad", 30);

	// Setzen der Fahrzeuge auf den weg, durch move(), da die Fahrzeuge unique_ptr sind
	weg->vAnnahme(std::move(fahrzeug));
	weg->vAnnahme(std::move(fahrzeug2));
	weg->vAnnahme(std::move(fahrzeug3));
	weg->vAnnahme(std::move(fahrzeug4));

	// Ausgabe des Weges
	weg->vKopf();
	std::cout << *weg << std::endl;

	// Code Snippet
	/*std::cout << *weg << std::endl;
	std::list<std::unique_ptr<Fahrzeug>>* p_pFahrzeuge = weg->getFahrzeuge();
	Fahrzeug::vKopf();
	for (auto const &fahrzeug : *p_pFahrzeuge) {
		fahrzeug->vAusgeben();
	}*/
}

void vAufgabe_5() {
	// Erstellen eines Weges
	Weg* weg = new Weg("Teststrasse", 20.0, INNERORTS);

	// Erstellen von vier Fahrzeugen
	std::unique_ptr<Fahrzeug> fahrzeug = std::make_unique<PKW>("PKW1", 100.0, 100.0, 55.0);
	std::unique_ptr<Fahrzeug> fahrzeug2 = std::make_unique<PKW>("PKW2", 100.0, 100.0, 55.0);
	std::unique_ptr<Fahrzeug> fahrzeug3 = std::make_unique<PKW>("PKW3", 100.0, 100.0, 55.0);
	std::unique_ptr<Fahrzeug> fahrzeug4 = std::make_unique<Fahrrad>("Fahrrad", 30);

	// Setzen der Fahrzeuge auf den weg, durch move(), da die Fahrzeuge unique_ptr sind
	weg->vAnnahme(std::move(fahrzeug));
	weg->vAnnahme(std::move(fahrzeug2));
	weg->vAnnahme(std::move(fahrzeug3));
	weg->vAnnahme(std::move(fahrzeug4));

	// Ausgabe des Weges
	weg->vKopf();
	std::cout << *weg << std::endl << std::endl;

	// Definieren des Zeitschritts
	double dZeitschritt = 0.2;
	int iAnzahlZeitschritte = 400;
	double dTankzeit = 2.5;

	// Wiederholen des Ganzen, bis alle Zeitschritte gemacht wurden
	for(dGlobaleZeit = 0; dGlobaleZeit <= (dZeitschritt * iAnzahlZeitschritte); dGlobaleZeit += dZeitschritt) {
		std::cout << std::setw(50) << std::setfill('-') << "-" << std::setfill(' ') << std::endl;
		std::cout << "Globale-Zeit: " << dGlobaleZeit << std::endl;
		std::cout << std::setw(50) << std::setfill('-') << "-" << std::setfill(' ') << std::endl;

		weg->vSimulieren();
		Fahrzeug::vKopf();
		// Schleife zum Iterieren durch den fahrzeugVektor
		for (auto const &fahrzeug : *weg->getFahrzeuge()) {
			fahrzeug->vAusgeben();
		}

		// Volltanken der PKWs
		// Modulo Operator von den zwei doubles, da es sich hier um zwei doubles handelt und immer ein sehr kleiner Restwert entsteht
		// wird das Ergebnis durch epsilon 0.001 subtrahiert, da 0.001 genau genug ist für dieses Beispiel
		if(std::fmod(dGlobaleZeit, dTankzeit)-0.001 < 0) {
			for (auto const &fahrzeug : *weg->getFahrzeuge()) {
				fahrzeug->dTanken();
			}
		}
	}
}

void vAufgabe_6() {
	// Erstellen von zwei Wegen
	Weg* wegI = new Weg("Test_1", 200.0, LANDSTRASSE);
	Weg* wegA = new Weg("Test_2", 500.0, AUTOBAHN);

	// Erstellen von fünf Fahrzeugen
	std::unique_ptr<Fahrzeug> fahrzeug = std::make_unique<PKW>("PKW1", 100.0, 15.0, 55.0);
	std::unique_ptr<Fahrzeug> fahrzeug2 = std::make_unique<PKW>("PKW2", 100.0, 15.0, 55.0);
	std::unique_ptr<Fahrzeug> fahrzeug3 = std::make_unique<PKW>("PKW3", 100.0, 30.0, 55.0);
	std::unique_ptr<Fahrzeug> fahrzeug4 = std::make_unique<Fahrrad>("Fahrrad", 30);
	std::unique_ptr<Fahrzeug> fahrzeug5 = std::make_unique<Fahrrad>("BMX", 30);

	// Intialisierung der Grafik auf dem SimuServer
	bInitialisiereGrafik(800, 500);

	// Setzen der Koordinaten für die Straße, gerade Linie
	int koordinaten[4] = { 700, 250, 10, 250 };

	// Zeichnen der Straße
	bZeichneStrasse(wegI->getName(), wegA->getName(), wegI->getLaenge(), 2, koordinaten);

	// Setzen der Fahrzeuge auf die Wege
	wegI->vAnnahme(std::move(fahrzeug));
	wegI->vAnnahme(std::move(fahrzeug2), 0.5);
	wegI->vAnnahme(std::move(fahrzeug3), 3);
	wegA->vAnnahme(std::move(fahrzeug4));
	wegI->vAnnahme(std::move(fahrzeug5));

	// Ausgabe der Wege
	wegI->vKopf();
	std::cout << *wegI << std::endl;
	std::cout << *wegA << std::endl << std::endl;

	// Definieren des Zeitschritts
	double dZeitschritt = 0.4;
	int iAnzahlZeitschritte = 100;
	double dTankzeit = 3.0;

	// Wiederholen des Ganzen, bis alle Zeitschritte gemacht wurden
	for(dGlobaleZeit = 0; dGlobaleZeit <= (dZeitschritt * iAnzahlZeitschritte); dGlobaleZeit += dZeitschritt) {
		vSetzeZeit(dGlobaleZeit);
		std::cout << std::setw(50) << std::setfill('-') << "-" << std::setfill(' ') << std::endl;
		std::cout << "Globale-Zeit: " << dGlobaleZeit << std::endl;
		std::cout << std::setw(50) << std::setfill('-') << "-" << std::setfill(' ') << std::endl;

		wegI->vSimulieren();
		wegA->vSimulieren();
		Fahrzeug::vKopf();
		// Schleife zum Iterieren durch den fahrzeugVektor
		for (auto const &fahrzeug : *wegI->getFahrzeuge()) {
			fahrzeug->vAusgeben();
		}
		for (auto const &fahrzeug : *wegA->getFahrzeuge()) {
			fahrzeug->vAusgeben();
		}

		// Volltanken der PKWs
		// Modulo Operator von den zwei doubles, da es sich hier um zwei doubles handelt und immer ein sehr kleiner Restwert entsteht
		// wird das Ergebnis durch epsilon 0.001 subtrahiert, da 0.001 genau genug ist für dieses Beispiel
		if(std::fmod(dGlobaleZeit, dTankzeit)-0.001 < 0) {
			for (auto const &fahrzeug : *wegI->getFahrzeuge()) {
				fahrzeug->dTanken();
			}
			for (auto const &fahrzeug : *wegA->getFahrzeuge()) {
				fahrzeug->dTanken();
			}
		}
		vSleep(1000);
	}
	vBeendeGrafik();
}

void vAufgabe_6a() {
	// Testen der vertagt_liste und vertagt_aktion Dateien
	using namespace vertagt;
	VListe<int> vListe;
	typedef VListe<int>::iterator vListeIntIterator;

	// Zufallszahlgeneration
	static std::mt19937 device(0);
	std::uniform_int_distribution<int> dist(1, 10);

	// 10 Zufallszahlen generieren
	for(int i = 1; i <= 10; i++) {
		vListe.push_back(dist(device));
	}
	vListe.vAktualisieren();

	// Generierten Zahlen ausgeben
	for(vListeIntIterator it = vListe.begin(); it != vListe.end(); it++) {
		std::cout << (*it) << " ";
	}

	// Alle Elemente > 5 löschen
	for(vListeIntIterator it = vListe.begin(); it != vListe.end(); it++) {
		if((*it) > 5) {
			vListe.erase(it);
		}
	}
	std::cout << std::endl << std::endl;

	// Ausgabe sollte die gleiche sein, da vAktualisieren noch nicht durchgeführt wurde
	for(vListeIntIterator it = vListe.begin(); it != vListe.end(); it++) {
		std::cout << (*it) << " ";
	}
	std::cout << std::endl << std::endl;
	vListe.vAktualisieren();

	// Ausgabe sollte sich geändert haben
	for(vListeIntIterator it = vListe.begin(); it != vListe.end(); it++) {
		std::cout << (*it) << " ";
	}
	std::cout << std::endl << std::endl;

	vListe.push_front(dist(device));
	vListe.push_back(dist(device));

	// Ausgabe sollte gleich sein
	for(vListeIntIterator it = vListe.begin(); it != vListe.end(); it++) {
		std::cout << (*it) << " ";
	}
	std::cout << std::endl << std::endl;
	vListe.vAktualisieren();

	// Ausgabe sollte verändert sein
	for(vListeIntIterator it = vListe.begin(); it != vListe.end(); it++) {
		std::cout << (*it) << " ";
	}
}

void vAufgabe_7() {
	// Erzeugung der vier gewünschten Kreuzungen
	std::shared_ptr<Kreuzung> kr1 = std::make_shared<Kreuzung>("kr1", 0);
	std::shared_ptr<Kreuzung> kr2 = std::make_shared<Kreuzung>("kr2", 1000);
	std::shared_ptr<Kreuzung> kr3 = std::make_shared<Kreuzung>("kr3", 0);
	std::shared_ptr<Kreuzung> kr4 = std::make_shared<Kreuzung>("kr4", 0);

	// Erzeugung der gewünschten Fahrzeuge
	std::unique_ptr<Fahrzeug> fahrzeug1 = std::make_unique<PKW>("PKW1", 15, 20, 600);
	std::unique_ptr<Fahrzeug> fahrzeug2 = std::make_unique<PKW>("PKW2", 20, 20, 600);
	std::unique_ptr<Fahrzeug> fahrzeug3 = std::make_unique<PKW>("PKW3", 20, 20, 600);
	std::unique_ptr<Fahrzeug> fahrzeug4 = std::make_unique<Fahrrad>("Fahrrad1", 10);

	// Initialisierung der Grafik auf dem SimuServer
	bInitialisiereGrafik(1000, 1000);

	// Zeichnen der Kreuzungen
	bZeichneKreuzung(680, 40);
	bZeichneKreuzung(680, 300);
	bZeichneKreuzung(680, 570);
	bZeichneKreuzung(320, 300);

	// Initialisierungen der Koordinaten
	int s1[] = { 680, 40, 680, 300 };
	int s2[] = { 680, 300, 850, 300, 970, 390, 970, 500, 850, 570, 680, 570 };
	int s3[] = { 680, 300, 680, 570 };
	int s4[] = { 680, 300, 320, 300 };
	int s5[] = { 680, 570, 500, 570, 350, 510, 320, 420, 320, 300 };
	int s6[] = { 320, 300, 170, 300, 70, 250, 80, 90, 200, 60, 320, 150, 320, 300 };

	// Zeichnen der Straßen
	bZeichneStrasse("W12", "W21", 40, 2, s1);
	bZeichneStrasse("W23a", "W32a", 115, 6, s2);
	bZeichneStrasse("W23b", "W32b", 40, 2, s3);
	bZeichneStrasse("W24", "W42", 55, 2, s4);
	bZeichneStrasse("W34", "W43", 85, 5, s5);
	bZeichneStrasse("W44a", "W44b", 130, 7, s6);

	// Verbindung der Straßen mit den Kreuzungen
	Kreuzung::vVerbinde("W12", "W21", 40, kr1, kr2, Tempolimit::INNERORTS, false);
	Kreuzung::vVerbinde("W23a", "W32a", 115, kr2, kr3, Tempolimit::AUTOBAHN, false);
	Kreuzung::vVerbinde("W23b", "W32b", 40, kr2, kr3, Tempolimit::INNERORTS, false);
	Kreuzung::vVerbinde("W24", "W42", 55, kr2, kr4, Tempolimit::INNERORTS, false);
	Kreuzung::vVerbinde("W34", "W43", 85, kr3, kr4, Tempolimit::AUTOBAHN, false);
	Kreuzung::vVerbinde("W44a", "W44b", 130, kr4, kr4, Tempolimit::LANDSTRASSE, false);

	// Setzen der Fahrzeuge auf die Kreuzungen
	kr2->vAnnahme(std::move(fahrzeug2), 0);
	kr1->vAnnahme(std::move(fahrzeug3), 1);
	kr1->vAnnahme(std::move(fahrzeug4), 0);
	kr1->vAnnahme(std::move(fahrzeug1), 0);

	// Definieren des Zeitschritts
	double dZeitschritt = 0.5;
	int iAnzahlZeitschritte = 30;
	//double dTankzeit = 3.0;

	// Wiederholen des Ganzen, bis alle Zeitschritte gemacht wurden
	for(dGlobaleZeit = 0; dGlobaleZeit <= (dZeitschritt * iAnzahlZeitschritte); dGlobaleZeit += dZeitschritt) {
		// Setzen der Globalzeit im SimuServer
		vSetzeZeit(dGlobaleZeit);
		std::cout << std::setw(50) << std::setfill('-') << "-" << std::setfill(' ') << std::endl;
		std::cout << "Globale-Zeit: " << dGlobaleZeit << std::endl;
		std::cout << std::setw(50) << std::setfill('-') << "-" << std::setfill(' ') << std::endl;

		// Simulation der Kreuzungen
		kr1->vSimulieren();
		kr2->vSimulieren();
		kr3->vSimulieren();
		kr4->vSimulieren();

		vSleep(1000);
	}
	std::cout << "Beendet" << std::endl;
	vBeendeGrafik();
}

void vAufgabe_8() {

}

int main() {
	dGlobaleZeit = 0.0;
	vAufgabe_7();
	return 0;
}

#include <iostream>
#include <memory>
#include <iomanip>
#include <vector>
#include <cmath>
#include "Fahrzeug.h"
#include "Fahrrad.h"
#include "PKW.h"


// Die globale Variable dGlobaleZeit, damit die Fahrzeuge wissen, wie lange diese simulieren sollen
double dGlobaleZeit;

// Genutzt beim Vortestat aber an sich nicht best-practices
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

int main() {
	dGlobaleZeit = 0.0;
	vAufgabe_3();
	return 0;
}

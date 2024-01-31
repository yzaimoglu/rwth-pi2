#include <iostream>
#include <iomanip>
#include <string>
#include "Simulationsobjekt.h"
#include "vertagt_liste.h"
#include "Weg.h"
#include "Tempolimit.h"
#include "Fahrausnahme.h"

Weg::Weg() :
	Simulationsobjekt(),
	p_dLaenge(15),
	p_eTempolimit(Tempolimit::AUTOBAHN),
	p_dVirtuelleSchranke(p_dLaenge),
	p_bUeberholverbot(true) {
}

// Konstruktor
// 	sName : Name des Weges
//	dLaenge : Länge des Weges in km
//	eTempolimit : Typ der Straße für das Tempolimit (bsp. AUTOBAHN)
Weg::Weg(std::string sName, double dLaenge, Tempolimit eTempolimit, bool bUeberholverbot) :
		Simulationsobjekt(sName),
		p_dLaenge(dLaenge),
		p_eTempolimit(eTempolimit),
		p_dVirtuelleSchranke(p_dLaenge),
		p_bUeberholverbot(bUeberholverbot),
		p_pKreuzung(std::make_shared<Kreuzung>()),
		p_pRueckweg(std::make_shared<Weg>()) {

}

Weg::Weg(std::string sName, double dLaenge, std::weak_ptr<Kreuzung> pKreuzung, Tempolimit eTempolimit, bool bUeberholverbot) :
	Simulationsobjekt(sName),
	p_dLaenge(dLaenge),
	p_pKreuzung(pKreuzung),
	p_eTempolimit(eTempolimit),
	p_bUeberholverbot(bUeberholverbot),
	p_dVirtuelleSchranke(p_dLaenge) {
}

// Destruktor
Weg::~Weg() {

}

// Kopfzeile
void Weg::vKopf() {
	std::cout << std::resetiosflags(std::ios::adjustfield)
			<< std::setiosflags(std::ios::left)
			<< std::setw(6) << "ID"
			<< std::setw(10) << "Name"
			<< std::resetiosflags(std::ios::adjustfield)
			<< std::setiosflags(std::ios::right)
			<< std::setw(30) << "Laenge"
			<< std::setw(30) << "Fahrzeuge"
			<< std::endl
			<< std::setw(6+10+30*2)
			<< std::setfill('-')
			<< "-"
			<< std::setfill(' ')
			<< std::endl;
}

// Simuliert alle auf dem Weg befindlichen Fahrzeuge durch eine range-based loop
void Weg::vSimulieren() {
	// Aktualisierung der Fahrzeuge
	p_pFahrzeuge.vAktualisieren();

	// Iteration über die Fahrzeuge
	for (vIterator it = p_pFahrzeuge.begin(); it != p_pFahrzeuge.end();) {
		try {
			// Simulation und Zeichnen des Fahrzeugs
			(*it)->vSimulieren();
			(*it)->vZeichnen(*this);
			it++;
		} catch (Fahrausnahme *pFahrausnahme) {
			it++;
			// Bearbeitung der Fahrausnahme
			pFahrausnahme->vBearbeiten();
		}
	}

	// Aktualisieren der Fahrzeuge
	p_pFahrzeuge.vAktualisieren();
	this->p_dVirtuelleSchranke = p_dLaenge;
}

// Definition der Memberfunktion vAusgeben()
void Weg::vAusgeben() const {
  Simulationsobjekt::vAusgeben();
  std::cout << std::resetiosflags(std::ios::adjustfield)
			<< std::setiosflags(std::ios::right)
		    << std::setw(30) << p_dLaenge
		    << std::setw(30) << "( ";
  for (auto it = p_pFahrzeuge.begin(); it != p_pFahrzeuge.end(); it++) {
	  std::cout << (*it)->getName() << " ";
  }
  std::cout << ")" << std::endl;
}


// Definition der Memberfunktion vAusgeben() mit ostream
std::ostream& Weg::vAusgeben(std::ostream& o) const {
  Simulationsobjekt::vAusgeben(o);
  o << std::resetiosflags(std::ios::adjustfield)
      << std::setiosflags(std::ios::right)
      << std::setw(30) << p_dLaenge
      << std::setw(30) << "( ";
  for (auto it = p_pFahrzeuge.begin(); it != p_pFahrzeuge.end(); it++) {
	  o << (*it)->getName() << " ";
  }
  o << ")" << std::endl;
  return o;
}



// Hinzufügen eines neuen Fahrzeugs in die Fahrzeugliste eines Weges (Fahren)
void Weg::vAnnahme(std::unique_ptr<Fahrzeug> fahrzeug) {
	// Setzen des Fahrzeugs auf den neuen Weg
	fahrzeug->vNeueStrecke(*this);

	// Setzen des Fahrzeugs auf die Fahrzeugliste des Weges
	p_pFahrzeuge.push_back(std::move(fahrzeug));

	// Aktualisieren der Liste
	p_pFahrzeuge.vAktualisieren();
}

// Hinzufügen eines neuen Fahrzeugs in die Fahrzeugliste eines Weges (Parken)
void Weg::vAnnahme(std::unique_ptr<Fahrzeug> fahrzeug, double dStartzeitpunkt) {
	// Setzen des Fahrzeugs auf den neuen Weg
	fahrzeug->vNeueStrecke(*this, dStartzeitpunkt);

	// Setzen des Fahrzeugs auf die Fahrzeugliste des Weges
	p_pFahrzeuge.push_front(std::move(fahrzeug));

	// Aktualisieren der Liste
	p_pFahrzeuge.vAktualisieren();
}

// Löschen eines Fahrzeugs aus dem Weg
std::unique_ptr<Fahrzeug> Weg::pAbgabe(Fahrzeug& pFahrzeug) {
	// Iteration über die Fahrzeugsliste zum Finden des gewünschten Fahrzeugs
	for(auto it = p_pFahrzeuge.begin(); it != p_pFahrzeuge.end(); it++) {
		// Überprüfen des Iterationselementes mit gewünschtem Fahrzeug
		if((*it).get() == &pFahrzeug) {
			// Lokale Variable zur Zwischenspeicherung
			std::unique_ptr<Fahrzeug> lokal = std::move(*it);
			// Löschen des Fahrzeugs aus der Liste
			p_pFahrzeuge.erase(it);
			p_pFahrzeuge.vAktualisieren();
			return lokal;
		}
	}
	return nullptr;
}

// Überladung des << Operators
std::ostream& operator<<(std::ostream& o, const Weg& weg) {
	weg.vAusgeben(o);
	return o;
}


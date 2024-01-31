#include "SimuClient.h"
#include "SimuClientSocket.h"
#include <boost/thread/thread.hpp>
#include <map>
#include <string>
#include <sstream>
#include <iomanip>
#include <iostream>
#include <thread>
#include <chrono>

#if !USE_GENERIC_BUT_CPU_INTENSIVE_SLEEP

#endif

using namespace std;

#define CString std::string
#define CSocket SimuClientSocket

static CSocket* ClientSocket ;
static CString InetAddress;
static CString Port;
static bool initialized = false;
static int iXSize=0, iYSize=0;
static std::map<string,int> sWege;
//static double dLastTime=-1.0;
static double dTime=0.0;
static string sFzName;
static string sHName;
static string sRName;
static string sSName;

void AfxMessageBox(CString aMsg, bool send=true) {
	std::cout << "### SimuClient MESSAGE: " << aMsg << std::endl;
	stringstream msg;
	msg << "msg Simuclient MESSAGE: " << aMsg << "#";
	if (send) {
		ClientSocket->Send(msg);
	}
}

bool bStreetOk(const string& sName, bool bNeu)
{
   if (sName.empty())
   {
      AfxMessageBox(CString("Wegname ist leer."));
      return false;
   }
   int iPos = sName.find_first_not_of("ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz1234567890_-");
   if (iPos > 0)
   {
      AfxMessageBox(CString("Wegname darf nur Buchstaben, Ziffern, -_ und keine Blanks enthalten."));
      return false;
   }
   if (bNeu)
   {
      if (sName.size() > 10)
      {
         // max. 10 Zeichen
         AfxMessageBox(CString("Wegname zu lang (max. 10 Zeichen): "));
         return false;
      }
      if (sWege.find(sName) != sWege.end())
      {
         // Name schon vorhanden
         AfxMessageBox(CString("Wegname wurde schon verwendet."));
         return false;
      }
      else
      {
         // Name o.k., eintragen
         sWege[sName] = 0;
      }
   }
   else
   {
      if (sWege.find(sName) != sWege.end())
      {
         // Name o.k., Zugriffszaehler erhoehen
         ++sWege[sName];
      }
      else
      {
         // Name nicht vorhanden
         AfxMessageBox(CString("Wegname ist undefiniert."));
         return false;
      }
   }
   return true;
}

void executeProgram(std::string programName) {
    system(programName.c_str());
}

SIMUCLIENT_API bool bInitialisiereGrafik(int sizeX, int sizeY, const char* address, const char* port) {

   initialized = false;
   if ((sizeX < 100) || (sizeX > 2000))
   {
      AfxMessageBox(CString("Groesse des Verkehrsplans < 100 oder > 2000."));
      return false;
   }
   if ((sizeY < 100) || (sizeY > 2000))
   {
      AfxMessageBox(CString("Groesse des Verkehrsplans < 100 oder > 2000."));
      return false;
   }

   InetAddress = address;

   // fuer CIP-Pool dynamische Ports
   Port = port;
   std::stringstream s;
   s <<  (int) (time(0) % 1000 + 8000);
   Port = s.str();

   string programName = "java -jar SimuServer.jar " + Port;
   std::thread worker (executeProgram, programName);
   worker.detach();
   //std::this_thread::sleep_for (std::chrono::seconds(2));
   vSleep(2000);

   ClientSocket = new CSocket();
   if (!ClientSocket->Create()) {
      AfxMessageBox(CString("TCP/IP-Verbindung nicht moeglich!"), false);
      return false;
   }

   int iCount = 0;
   while (iCount < 4)
   {
      if (ClientSocket->Connect(InetAddress, Port))
      {
         iCount = 0;
         break;
      }
      iCount++;
      vSleep(300);
   }
   if (iCount < 0) {
         AfxMessageBox(CString("Connect nicht moeglich! (Firewall?) Grafikausgaben werden unterdrueckt."), false);
         return false;
   }
   stringstream msg;
   msg << "init " << sizeX << " " << sizeY << "#";
   ClientSocket->Send(msg);
   //AfxMessageBox(msg);
   vSleep(100);

   initialized = true;
   iXSize = sizeX;
   iYSize = sizeY;
   return true;
}

SIMUCLIENT_API bool bZeichneKreuzung(int posX, int posY) {

   if (!initialized)
      return false;
   if ((posX > 0) && (posX < iXSize)) {
      if ((posY > 0) && (posY < iYSize))
      {
         stringstream msg;
         msg << "crossing " << posX << " " << posY << "#";
         ClientSocket->Send(msg);
         return true;
      }
      else
      {
         AfxMessageBox(CString("Kreuzung ausserhalb des Verkehrsplans."));
         return false;
      }
   }
   return false;
}

SIMUCLIENT_API void vBeendeGrafik() {

   if (initialized)
   {
      AfxMessageBox(CString("Simulation beendet."), false);
      stringstream msg;
      msg << "close#";
      ClientSocket->Send(msg);
      ClientSocket->Close();
      delete ClientSocket;
      sWege.clear();
      initialized = false;
   }
}

SIMUCLIENT_API bool bLoescheFahrzeug(const std::string& name) {
	return true;
}

SIMUCLIENT_API void vSetzeZeit(const double dZeit) {
	if (dZeit > 0.0)
		 dTime = dZeit;
	if (initialized) {
		stringstream msg;
		msg << "time " << dTime << "#";;
		ClientSocket->Send(msg);
	}
	return;
}

#if !USE_GENERIC_BUT_CPU_INTENSIVE_SLEEP
SIMUCLIENT_API void vSleep(int mSec) {
	if (mSec > 0)
		std::this_thread::sleep_for(std::chrono::milliseconds(mSec));
	return;
}
#else
SIMUCLIENT_API void vSleep(int mSec) {
    typedef boost::posix_time::ptime system_time;
    system_time current, start;
    if (mSec > 0 && mSec < 10000) {

        start = boost::get_system_time();
        current = start;
        while ((current - start).total_milliseconds() < mSec) {
            current = boost::get_system_time();
        }
    }
	return;
}
#endif

SIMUCLIENT_API bool bLoescheFahrzeug(const char* name) {
	return true;
}

bool x_bSetStreet(int length, int numPoints, int* points_xy) {

   if (!initialized)
      return false;
   if (length < 0)
   {
      AfxMessageBox(CString("Laenge des Weges kleiner 0."));
      return false;
   }
   if (numPoints < 2)
   {
      AfxMessageBox(CString("Mindestens 2 Punkte fuer Strasse erforderlich."));
      return false;
   }
   if (bStreetOk(sHName,true) && bStreetOk(sRName,true))
   {
      stringstream msg;
      msg << "street " << sHName << " " << sRName << " ";
      msg << length << " " << numPoints;
      for (int i=0; i < numPoints*2; i+=2) {
         int iX = points_xy[i];
         int iY = points_xy[i+1];
         if ((iX > 0) && (iX < iXSize))
            if ((iY > 0) && (iY < iYSize))
            {
               msg << " " << iX << " " << iY;
            }
            else
            {
               AfxMessageBox(CString("Strassenpunkt ausserhalb des Verkehrsplans."));
               return false;
            }
         else
         {
            AfxMessageBox(CString("Strassenpunkt ausserhalb des Verkehrsplans oder falsche Anzahl."));
            return false;
         }
      }
      msg << "#";
      ClientSocket->Send(msg);
      return true;
   }
   else
      return false;
}

bool x_bSet(char cTyp, double rel_position, double speed, double tank=0.0) {

   if (!initialized)
      return false;

   if (sFzName.empty())
   {
      AfxMessageBox(CString("Fahrzeugname ist leer."));
      return false;
   }
   int iPos = sFzName.find_first_not_of("ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz1234567890_-");
   if (iPos > 0)
   {
      AfxMessageBox(CString("Fahrzeugname darf nur Buchstaben, Ziffern, -_ und keine Blanks enthalten."));
      return false;
   }

   if (speed < 0.0)
   {
      AfxMessageBox(CString("Geschwindigkeit < 0."));
      return false;
   }
   if (speed > 300.0)
   {
      AfxMessageBox(CString("PKW sind keine Formel1-Fahrzeuge. Geschwindigkeit > 300 km/h"));
      return false;
   }
   if (tank < 0.0)
   {
      AfxMessageBox(CString("Tank < 0.0"));
      return false;
   }
   if (tank > 999.9)
   {
      AfxMessageBox(CString("Versteckte Tanks nicht erlaubt. Tankinhalt nur < 1000 l"));
      return false;
   }

   stringstream msg;
   if ((rel_position >= 0.0) && (rel_position <= 1.0))
   {
      if (bStreetOk(sSName, false))
      {
         if (cTyp == 'c')
         {
            msg << "sc " << sFzName << " " << sSName
                << setiosflags(ios::fixed)
                << " " << setw(7) << setprecision(4) << rel_position
                << " " << setw(6) << setprecision(1) << speed
                << " " << setw(6) << setprecision(1) << tank
                << "#";
         }
         else if (cTyp == 'b')
         {
            msg << "sb " << sFzName << " " << sSName
                << setiosflags(ios::fixed)
                << " " << setw(7) << setprecision(4) << rel_position
                << " " << setw(6) << setprecision(1) << speed
                << "#";
         }
         else
            return false;
         ClientSocket->Send(msg);
         vSleep(50);
         CString sText;
         // if (dTime-dLastTime > 0.09)
         {
					 // TODO Reformat and send time string
            /*sText.Format(CString("%s %8.2f"),CString(" // Aktuelle Zeit:"),dTime);
            vNewTitle(sText);
            dLastTime = dTime;*/
         }
         return true;
      }
      else
      {
         return false;
      }
   }
   else
   {
      AfxMessageBox(CString("Relative Position ausserhalb [0,1]."));
      return false;
   }
}

SIMUCLIENT_API bool bZeichneStrasse(const char* way_to_name, const char* way_back_name, int length, int numPoints, int* points_xy) {
   sHName = string(way_to_name);
   sRName = string(way_back_name);
   return x_bSetStreet(length, numPoints, points_xy);
}

SIMUCLIENT_API bool bZeichneStrasse(const string& way_to_name, const char* way_back_name, int length, int numPoints, int* points_xy) {
   sHName = way_to_name;
   sRName = string(way_back_name);
   return x_bSetStreet(length, numPoints, points_xy);
}

SIMUCLIENT_API bool bZeichneStrasse(const char* way_to_name, const string& way_back_name, int length, int numPoints, int* points_xy) {
   sHName = string(way_to_name);
   sRName = way_back_name;
   return x_bSetStreet(length, numPoints, points_xy);
}

SIMUCLIENT_API bool bZeichneStrasse(const string& way_to_name, const string& way_back_name, int length, int numPoints, int* points_xy) {
   sHName = way_to_name;
   sRName = way_back_name;
   return x_bSetStreet(length, numPoints, points_xy);
}

SIMUCLIENT_API bool bZeichnePKW(const string& carname, const char* streetname, double rel_position, double speed, double tank) {
   sFzName = carname;
   sSName = string(streetname);
   return x_bSet('c',rel_position,speed,tank);
}

SIMUCLIENT_API bool bZeichnePKW(const string& carname, const string& streetname, double rel_position, double speed, double tank) {
   sFzName = carname;
   sSName = streetname;
   return x_bSet('c',rel_position,speed,tank);
}

SIMUCLIENT_API bool bZeichneFahrrad(const string& bikename, const string& streetname, double rel_position, double speed) {
   sFzName = bikename;
   sSName = streetname;
   return x_bSet('b',rel_position,speed);
}

SIMUCLIENT_API bool bZeichneFahrrad(const string& bikename, const char* streetname, double rel_position, double speed) {
   sFzName = bikename;
   sSName = string(streetname);
   return x_bSet('b',rel_position,speed);
}

SIMUCLIENT_API bool bZeichnePKW(const char* carname, const char* streetname, double rel_position, double speed, double tank) {
   sFzName = string(carname);
   sSName = string(streetname);
   return x_bSet('c',rel_position,speed,tank);
}

SIMUCLIENT_API bool bZeichnePKW(const char* carname, const string& streetname, double rel_position, double speed, double tank) {
   sFzName = string(carname);
   sSName = streetname;
   return x_bSet('c',rel_position,speed,tank);
}

SIMUCLIENT_API bool bZeichneFahrrad(const char* bikename, const char* streetname, double rel_position, double speed) {
   sFzName = string(bikename);
   sSName = string(streetname);
   return x_bSet('b',rel_position,speed);
}

SIMUCLIENT_API bool bZeichneFahrrad(const char* bikename, const string& streetname, double rel_position, double speed) {
   sFzName = string(bikename);
   sSName = streetname;
   return x_bSet('b',rel_position,speed);
}

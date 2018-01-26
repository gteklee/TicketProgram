#include "radios.h"

Radios::Radios()
{
    ubnt.append("");
    ubnt.append("NanoBridge M5");
    ubnt.append("NanoBridge M2");
    ubnt.append("NanoBeam M5");
    ubnt.append("NanoBeam M2");
    ubnt.append("NanoStation M5");
    ubnt.append("NanoStation M2");
    ubnt.append("NanoStation M365");
    ubnt.append("NanoStation Loco M5");
    ubnt.append("AirGrid M5");
    ubnt.append("AirGrid M2");
    ubnt.append("Rocket");

    canopy.append("");
    canopy.append("5.4/5.7GHz MIMO OFDM");
    canopy.append("5.4GHz MIMO OFDM");
    canopy.append("2.4 Omni");
    canopy.append("3.6GHz MIMO OFDM");
    canopy.append("3692");
    canopy.append("3693");
    canopy.append("5792");
    canopy.append("900MHz");
    canopy.append("5.7 Omni");
    canopy.append("5.2GHz [Legacy]");
    canopy.append("5.4GHz [Legacy]");
    canopy.append("2.4GHz [Legacy]");

    telrad.append("");
    telrad.append("CPE8000 - Pro");
    telrad.append("WLTXCS - 100");
    telrad.append("WLTXCS - 100");
    telrad.append("WLTXFSR - 105GN");
}

Radios::~Radios()
{

}

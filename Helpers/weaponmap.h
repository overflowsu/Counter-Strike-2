#pragma once
#include <unordered_map>
#include <string>

std::unordered_map<int, std::string> weaponmap = {
    {1, "Desert Eagle"},
    {2, "Dual Berettas"},
    {3, "Five-SeveN"},
    {4, "Glock-18"},
    {7, "AK-47"},
    {8, "AUG"},
    {9, "AWP"},
    {10, "FAMAS"},
    {11, "G3SG1"},
    {13, "Galil AR"},
    {14, "M249"},
    {16, "M4A4"},
    {17, "MAC-10"},
    {19, "P90"},
    {23, "MP5-SD"},
    {24, "UMP-45"},
    {25, "XM1014"},
    {26, "PP-Bizon"},
    {27, "MAG-7"},
    {28, "Negev"},
    {29, "Sawed-Off"},
    {30, "Tec-9"},
    {31, "Zeus x27"},
    {32, "P2000"},
    {33, "MP7"},
    {34, "MP9"},
    {35, "Nova"},
    {36, "P250"},
    {38, "SCAR-20"},
    {39, "SG 553"},
    {40, "SSG 08"},
    {42, "Knife"},
    {43, "Flashbang"},
    {44, "HE Grenade"},
    {45, "Smoke Grenade"},
    {46, "Molotov"},
    {47, "Decoy"},
    {48, "Incendiary"},
    {49, "C4"},
    {60, "M4A1-S"},
    {61, "USP-S"},
    {63, "CZ75-Auto"},
    {64, "R8 Revolver"},
};

inline std::string GetWeaponName(int weaponID) {
    auto it = weaponmap.find(weaponID);
    if (it != weaponmap.end()) {
        return it->second;
    }
    return "Unknown";
}
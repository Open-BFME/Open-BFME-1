// ?parseUpgradeKeyVector@Rva000BCFA0@@SAXPAVINI@@PAX1PBX@Z
// partial score=0.7 date=2026-09-24
// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHs-c- /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/ini /Ireference/shims/sweep /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad /FAsc /Fabuild/parseUpgradeKeyVector-headers.cod
// stlport

#include "Precompiled/PreRTS.h"
#include <vector>
#include "Common/INI.h"
#include "Common/NameKeyGenerator.h"
#include "Common/Upgrade.h"
#include "Common/Errors.h"

struct Gen_t_000bc840_m4pod { int a[1]; };
bool operator==(const Gen_t_000bc840_m4pod&, const Gen_t_000bc840_m4pod&);
bool operator<(const Gen_t_000bc840_m4pod&, const Gen_t_000bc840_m4pod&);

class Rva000BCFA0
{
public:
    static void parseUpgradeKeyVector(INI *ini, void *instance, void *store, const void *userData);
};

void Rva000BCFA0::parseUpgradeKeyVector(INI *ini, void *, void *store, const void *)
{
    if (TheUpgradeCenter == 0)
        throw ERROR_BUG;

    _STL::vector<Gen_t_000bc840_m4pod> *upgrades = (_STL::vector<Gen_t_000bc840_m4pod> *)store;
    for (const char *token = ini->getNextTokenOrNull(); token != 0; token = ini->getNextTokenOrNull()) {
        const UpgradeTemplate *upgrade = TheUpgradeCenter->findUpgradeByKey(
            TheNameKeyGenerator->nameToKey(token));
        if (upgrade != 0)
            upgrades->push_back(*(const Gen_t_000bc840_m4pod *)&upgrade);
    }
}

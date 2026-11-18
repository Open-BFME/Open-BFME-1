// cl: /DNDEBUG /MD /EHs-c- /D_STLP_USE_STATIC_LIB /Igame/GameEngine/Include /Igame/Libraries/Source/WWVegas/WWLib /Iinputs/reference/shims/zhcanonascii /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include
// stlport
// The callback appends resolved upgrade pointers to the decoded vector.
#define _STLP_NO_EXCEPTIONS 1
#include <vector>
#include "Common/Errors.h"
#include "Common/INI/INI.h"

#include "../../../Include/Common/NameKeyType.h"



class NameKeyGenerator
{
public:
    NameKeyType nameToKey(const char *);
};

class UpgradeTemplate;
class UpgradeCenter
{
public:
    const UpgradeTemplate *findUpgradeByKey(NameKeyType) const;
};

extern NameKeyGenerator *TheNameKeyGenerator;
extern UpgradeCenter *TheUpgradeCenter;

class Rva000BCFA0
{
public:
    static void parseUpgradeKeyVector(INI *ini, void *instance, void *store, const void *userData);
};

// ?parseUpgradeKeyVector@Rva000BCFA0@@SAXPAVINI@@PAX1PBX@Z
void Rva000BCFA0::parseUpgradeKeyVector(INI *ini, void *, void *store, const void *)
{
    _STL::vector<UpgradeTemplate *> *upgrades = (_STL::vector<UpgradeTemplate *> *)store;
    if (!TheUpgradeCenter)
    {
        throw ERROR_BUG;
    }

    for (const char *token = ini->getNextTokenOrNull(); token; token = ini->getNextTokenOrNull())
    {
        UpgradeTemplate *upgrade = const_cast<UpgradeTemplate *>(TheUpgradeCenter->findUpgradeByKey(TheNameKeyGenerator->nameToKey(token)));
        if (upgrade)
            upgrades->push_back(upgrade);
    }
}

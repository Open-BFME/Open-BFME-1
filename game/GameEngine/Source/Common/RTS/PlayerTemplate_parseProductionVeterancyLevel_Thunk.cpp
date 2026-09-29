// cl: /DNDEBUG /MD /EHsc /Igame/Libraries/Source/WWVegas/WWLib
// stlport
// Open-BFME5: canonical production-veterancy parser with BFME retail layouts.

enum NameKeyType { NAME_KEY_INVALID = 0 };
enum VeterancyLevel { VETERANCY_INVALID = 0 };

class AsciiString;

#include "string_base.h"

#include "ascii_string.h"

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/INI.h
class INI
{
public:
    const char *getNextToken(const char *separators = 0);
    static int scanIndexList(const char *token, const char *const *names);
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/NameKeyGenerator.h
class NameKeyGenerator
{
public:
    NameKeyType nameToKey(const char *name);
};

extern "C" NameKeyGenerator *g_theNameKeyGenerator;
extern "C" const char *g_theVeterancyNames[];

namespace _STL
{
template <typename T> struct less;
template <typename T> class allocator;
template <typename First, typename Second> struct pair;

template <typename Key, typename Value, typename Compare,
          typename Allocator>
class map
{
public:
    Value &operator[](const Key &key);
};
}

typedef _STL::map<NameKeyType, VeterancyLevel, _STL::less<NameKeyType>,
                  _STL::allocator<_STL::pair<const NameKeyType,
                                              VeterancyLevel> > >
    ProductionVeterancyMap;

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/PlayerTemplate.h
class PlayerTemplate
{
protected:
    static void parseProductionVeterancyLevel(INI *ini, void *instance,
                                               void *store,
                                               const void *userData);
};

void PlayerTemplate::parseProductionVeterancyLevel(INI *ini, void *instance,
                                                    void *, const void *)
{
    AsciiString templateName(ini->getNextToken());
    NameKeyType templateKey =
        g_theNameKeyGenerator->nameToKey(templateName.str());
    VeterancyLevel startLevel = (VeterancyLevel)INI::scanIndexList(
        ini->getNextToken(), g_theVeterancyNames);

    (*(ProductionVeterancyMap *)((char *)instance + 0x80))[templateKey] =
        startLevel;
}

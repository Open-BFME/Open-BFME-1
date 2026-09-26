// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/iniexception /ICode/Libraries/Source/WWVegas/WWLib
// stlport
// AIUpdateModuleData::parseLocomotorSet, retail 0x0027EC80/412B. Identity: the
// three INIException strings at VA010BA738/010BA6F4/010BA6D4 and "None" are the
// Zero Hour twin's parseLocomotorSet messages, and the body walks the same
// friend_getAIModuleInfo -> scanIndexList(TheLocomotorSetNames) -> map[set].clear
// -> NAMEKEY/findLocomotorTemplate/push_back sequence. The ledger once carried
// this address as findLocomotorTemplateVector (an __emit lift); that name was wrong.
// BFME throws INIException objects and also accepts loadType 4 as an override pass.
// Layout follows the landed sibling Common/INI/Rva001BD0D0LocomotorBinding.cpp.
#include "Common/INIException.h"
#include "ascii_string.h"
#include <stl/_config.h>
#undef _STLP_DEFAULT_CONSTRUCTOR_BUG
#include <map>
#include <vector>
#include <string.h>

template<> inline const char *StringBase<char>::str() const
{ return m_data ? m_data->data : ""; }

enum LocomotorSetType { LOCOMOTORSET_INVALID = -1 };
enum NameKeyType { NAMEKEY_INVALID = 0 };
class LocomotorTemplate;
typedef std::vector<const LocomotorTemplate *> LocomotorTemplateVector;
typedef std::map<LocomotorSetType, LocomotorTemplateVector> LocomotorTemplateMap;

class INI
{
public:
    const char *getNextToken(const char *seps = 0);
    const char *getNextTokenOrNull(const char *seps = 0);
    static int scanIndexList(const char *token, const char *const *nameList);
    int getLoadType() const { return m_loadType; }
    unsigned char m_prefix08[8];
    int m_loadType;
};

class AIUpdateModuleData
{
public:
    static void parseLocomotorSet(INI *ini, void *instance, void *store, const void *userData);
    unsigned char m_prefix08[8];
    LocomotorTemplateMap m_locomotorTemplates;
};

class ThingTemplate
{
public:
    AIUpdateModuleData *friend_getAIModuleInfo();
    const AsciiString &getName() const { return m_nameString; }
    unsigned char m_prefix20[0x20];
    AsciiString m_nameString;
};

class NameKeyGenerator
{
public:
    NameKeyType nameToKey(const char *name);
};
extern NameKeyGenerator *TheNameKeyGenerator;
#define NAMEKEY(s) TheNameKeyGenerator->nameToKey(s)

class LocomotorStore
{
public:
    LocomotorTemplate *findLocomotorTemplate(NameKeyType namekey);
};
extern LocomotorStore *TheLocomotorStore;   // VA012EF504: GameEngine init passes "TheLocomotorStore"

extern const char *TheLocomotorSetNames[];   // VA012B1220: SET_NORMAL..SET_COMBO3, NULL

/*static*/ void AIUpdateModuleData::parseLocomotorSet(INI *ini, void *instance, void * /*store*/, const void * /*userData*/)
{
    ThingTemplate *tt = (ThingTemplate *)instance;
    AIUpdateModuleData *self = tt->friend_getAIModuleInfo();
    if (!self)
        throw INIException(3, "Attempted to specify a locomotor for object %s without an AIUpdate block.", tt->getName().str());

    LocomotorSetType set = (LocomotorSetType)INI::scanIndexList(ini->getNextToken(), TheLocomotorSetNames);
    if (!self->m_locomotorTemplates[set].empty())
    {
        // 2 is Zero Hour's INI_LOAD_CREATE_OVERRIDES; 4 is a BFME load type.
        if (ini->getLoadType() != 2 && ini->getLoadType() != 4)
            throw INIException(3, "re-specifying a LocomotorSet is no longer allowed\n");
    }

    self->m_locomotorTemplates[set].clear();
    for (const char *locoName = ini->getNextToken(); locoName; locoName = ini->getNextTokenOrNull())
    {
        if (!*locoName || !_stricmp(locoName, "None"))
            continue;

        NameKeyType locoKey = NAMEKEY(locoName);
        const LocomotorTemplate *lt = TheLocomotorStore->findLocomotorTemplate(locoKey);
        if (!lt)
            throw INIException(3, "Locomotor %s not found!\n", locoName);
        self->m_locomotorTemplates[set].push_back(lt);
    }
}

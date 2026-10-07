// Retail001BD0D0/240B. EA's LocomotorSet::setLocomotorAndBaseSpeed
// (ea_evidence.csv, chain/strong); the ILT oracle fits only the
// (INI *, ThingTemplate *) spelling. The matched initializer in BfmeConv412.cpp
// calls it.
// FieldParse table VA0109E038 names Locomotor(+18), Condition(+1C), Speed(+20).
// The first two use parseAsciiString00851EE0; Speed uses parseReal00852B20.
// The initializer passes INI* first and ThingTemplate* second. In retail+99,
// ESP includes a late saved EBP: [ESP+1C] is the FIRST argument, not the second.
// Its loadType+8 accepts2/4. The old bank read the ThingTemplate there.
// Native LocomotorTemplateMap operator[] is independently214B exact at147070;
// its key is one four-byte enum, not the old bank's two-word wrapper.
// Setter147560 takes set then template; setter146270 takes set then the VALUE
// of Speed. The old bank swapped the former and passed an address to the latter.
// Native INIException has two fields/eight bytes and is thrown as a C++ object.
// Existing setter spellings bfmeResetANB/bfmeGoDST are preserved; their
// ThingTemplate receiver and argument types are corrected from the call sites.
// Store lookup001B70E0 accepts one string reference and RET4. This caller supplies
// ECX from VA012EF504, although its optimized body reloads that global itself.

// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Iinputs/reference/shims/iniexception /Igame/Libraries/Source/WWVegas/WWLib
// stlport
#include "Common/INIException.h"
#include "ascii_string.h"
#include <stl/_config.h>
#undef _STLP_DEFAULT_CONSTRUCTOR_BUG
#include <map>
#include <vector>

enum LocomotorSetType { LOCOMOTORSET_INVALID = -1 };
class LocomotorTemplate;

// This constructor has a ledgered retail thunk in
// LocomotorTemplateVectorBaseConstructorThunk.cpp.  Keep the header's inline
// template body available for layout and the other vector operations, but use
// that external specialization for this constructor.
namespace _STL
{
template <>
_Vector_base<LocomotorTemplate const *, allocator<LocomotorTemplate const *> >::_Vector_base(
    size_t, const allocator<LocomotorTemplate const *> &);
}

typedef std::map<LocomotorSetType, std::vector<const LocomotorTemplate *> > LocomotorTemplateMap;
class AIUpdateModuleData
{
public:
    unsigned char m_prefix08[8];
    LocomotorTemplateMap m_locomotorTemplates;
};
class ThingTemplate
{
public:
    AIUpdateModuleData *friend_getAIModuleInfo();
    void bfmeResetANB(LocomotorSetType set, const LocomotorTemplate *locomotor);
    void bfmeGoDST(LocomotorSetType set, float speed);
    unsigned char m_prefix20[0x20];
    AsciiString m_name;
};
class INI
{
public:
    static int scanIndexList(const char *text, const char *const *names);
    unsigned char m_prefix08[8];
    int m_loadType;
};
class Rva001B70E0LocomotorStore
{
public:
    const LocomotorTemplate *lookup(const AsciiString &name);
};
// 0x012EF504 is retail's TheLocomotorStore; the class and the global are
// declared by GameLogic/Locomotor.h, which this TU does not include (and whose
// LocomotorStore carries no `lookup` member, so the layout view above has to
// stay TU-local). Only the global is respelled here; the call keeps going
// through the view.
class LocomotorStore;
extern LocomotorStore *TheLocomotorStore;
class LocomotorSet
{
public:
    void setLocomotorAndBaseSpeed(INI *ini, ThingTemplate *thing);
    unsigned char m_prefix18[0x18];
    AsciiString m_locomotor;
    AsciiString m_condition;
    float m_speed;
};
extern const char *TheLocomotorSetNames[];

void LocomotorSet::setLocomotorAndBaseSpeed(INI *ini, ThingTemplate *thing)
{
    AIUpdateModuleData *data = thing->friend_getAIModuleInfo();
    if (!data)
        throw INIException(3, "Attempted to specify a locomotor for object %s without an AIUpdate\tblock.", thing->m_name.str());
    LocomotorSetType set = (LocomotorSetType)INI::scanIndexList(m_condition.str(),
        TheLocomotorSetNames);
    const LocomotorTemplate *locomotor = reinterpret_cast<Rva001B70E0LocomotorStore *>(TheLocomotorStore)->lookup(m_locomotor);
    if (!data->m_locomotorTemplates[set].empty() && ini->m_loadType != 2 && ini->m_loadType != 4)
        throw INIException(3, "re-specifying a LocomotorSet\tis no longer allowed");
    thing->bfmeResetANB(set, locomotor);
    thing->bfmeGoDST(set, m_speed);
}

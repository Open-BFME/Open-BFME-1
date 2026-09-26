// cl: /DNDEBUG /DWIN32 /MD /EHsc /D_STLP_USE_STATIC_LIB /Igame/Libraries/Source/WWVegas/WWLib
// RVA 00326490: dispatcher-proven condition; the older lost-object name is
// not supported by this body. It resolves a type-name list and player, then
// compares the player's 000C7C30 getter against each resolved template+4B4.
// The String returned by getNthInList is a native temporary: its lifetime ends
// after findTemplate and before the null/value test, exactly as in retail.
// stlport
#include <vector>
#include "ascii_string.h"

typedef bool Bool;
typedef int Int;
typedef unsigned int UnsignedInt;
typedef unsigned short UnsignedShort;

inline AsciiString::~AsciiString()
{
	((StringBase<char> *)this)->releaseBuffer();
}

class Parameter;
class ThingTemplate;
class ObjectTypes {
public:
    ObjectTypes();
    virtual ~ObjectTypes();
    // By-value return uses the MSVC hidden return buffer ahead of index.
    AsciiString getNthInList(Int index) const;
    AsciiString m_listName;              // +04
    std::vector<AsciiString> m_names;    // +08: begin/end/cap at +08/+0c/+10
};

class ObjectTypesTemp {
public:
    ObjectTypes *m_types;
    ObjectTypesTemp() : m_types(0) { m_types = new ObjectTypes; }
    ~ObjectTypesTemp() { if (m_types) delete m_types; }
};

class ScriptEngine {
public:
    UnsignedShort unidentified_0034DB40(Parameter *);
};
class Rva000C7C30Holder {
public:
    Int get(Int) const;
};
class Player {
public:
    char pad00[0x30];
    Rva000C7C30Holder m_at030;
};
class PlayerList { public: Player *getPlayerFromMask(UnsignedShort); };
class ThingFactory { public: ThingTemplate *findTemplate(const AsciiString &); };
class ScriptConditions {
public:
    friend class Rva00326490Condition;
protected:
    static void objectTypesFromParam(Parameter *, ObjectTypes *);
};
class Rva00326490Condition {
public:
    Bool evaluate(Parameter *, Parameter *);
};

extern ScriptEngine *TheScriptEngine;
extern PlayerList *ThePlayerList;
extern ThingFactory *TheThingFactory;

// ?evaluate@Rva00326490Condition@@QAE_NPAVParameter@@0@Z
Bool Rva00326490Condition::evaluate(Parameter *playerParameter,
    Parameter *typeParameter)
{
    ObjectTypesTemp types;
    ScriptConditions::objectTypesFromParam(typeParameter, types.m_types);

    ObjectTypes *set = types.m_types;
    UnsignedInt count = (UnsignedInt)set->m_names.size();
    if (!count) return false;

    UnsignedShort mask = TheScriptEngine->unidentified_0034DB40(playerParameter);
    if (!mask) return false;
    Player *player = ThePlayerList->getPlayerFromMask(mask);
    if (!player) return false;

    Int result = player->m_at030.get(1);
    for (UnsignedInt index = 0; index < count; ++index) {
        ThingTemplate *thing = TheThingFactory->findTemplate(set->getNthInList((Int)index));
        if (thing && result <= *(Int *)((char *)thing + 0x4b4)) return true;
    }
    return false;
}

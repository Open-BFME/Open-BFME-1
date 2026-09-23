// ?evaluateRva00327A00@ScriptConditionsRva00327A00@@QAE_NPAVCondition@@PAVParameter@@1@Z
// partial score=0.21 date=2026-09-23
// ?evaluateRva00327A00@ScriptConditionsRva00327A00@@QAE_NPAVCondition@@PAVParameter@@1@Z
// cl: /DNDEBUG /DWIN32 /MD /EHsc
// stlport
#include <vector>

typedef bool Bool;
typedef int Int;
typedef unsigned short PlayerMaskType;

class AsciiString;
class ThingTemplate;

class Parameter
{
public:
    const AsciiString &getString() const
    {
        return *(const AsciiString *)((const char *)this + 0x10);
    }
};

class Condition
{
public:
    Int getCustomData() const { return m_customData; }
    void setCustomData(Int value) { m_customData = value; }
    Int getCustomFrame() const { return m_customFrame; }
    void setCustomFrame(Int value) { m_customFrame = value; }

private:
    char m_padding[0x44];
    Int m_customData;
    Int m_customFrame;
};

class ObjectTypes
{
public:
    ObjectTypes();
    virtual ~ObjectTypes();
    Int prepForPlayerCounting(std::vector<const ThingTemplate *> &templates,
        std::vector<Int> &counts);

private:
    void *m_listName;
    void *m_objectTypesBegin;
    void *m_objectTypesEnd;
    void *m_objectTypesCapacity;
};

class ObjectTypesTemp
{
public:
    ObjectTypes *m_types;
    ObjectTypesTemp();
    ~ObjectTypesTemp()
    {
        if (m_types) delete m_types;
    }
};

class ScriptConditions
{
protected:
    static void objectTypesFromParam(Parameter *parameter, ObjectTypes *types);
};

class BfmeThingFactory
{
public:
    const ThingTemplate *findTemplate(const AsciiString &name);
};
extern BfmeThingFactory *TheThingFactory;

class Player
{
public:
    void countObjectsByThingTemplate(Int count,
        const ThingTemplate *const *templates, Bool ignoreDead,
        Int *counts, Bool ignoreUnderConstruction) const;
};

class PlayerList
{
public:
    Player *getEachPlayerFromMask(PlayerMaskType &mask);
};

extern PlayerList *ThePlayerList;

class ScriptEngine
{
public:
    PlayerMaskType unidentified_0034DB40(Parameter *parameter);
    Int getFrameObjectCountChanged() const
    {
        return *(const Int *)((const char *)this + 0x170d8);
    }
};
extern ScriptEngine *TheScriptEngine;

namespace rts
{
template <typename T>
T sum(std::vector<T> &values)
{
    typename std::vector<T>::iterator current = values.begin();
    typename std::vector<T>::iterator end = values.end();
    T total = 0;
    while (current != end) {
        total += *current;
        ++current;
    }
    return total;
}
}

class ScriptConditionsRva00327A00 : public ScriptConditions
{
public:
    Bool evaluateRva00327A00(Condition *condition, Parameter *typeParameter,
        Parameter *playerParameter);
};

Bool ScriptConditionsRva00327A00::evaluateRva00327A00(Condition *condition,
    Parameter *typeParameter, Parameter *playerParameter)
{
    const ThingTemplate *thingTemplate =
        TheThingFactory->findTemplate(typeParameter->getString());
    if (!thingTemplate) return false;

    if (condition->getCustomData() != 0) {
        if (TheScriptEngine->getFrameObjectCountChanged() ==
            condition->getCustomFrame()) {
            if (condition->getCustomData() == 1) return true;
            if (condition->getCustomData() == -1) return false;
        }
    }

    std::vector<Int> counts;
    std::vector<const ThingTemplate *> templates;
    ObjectTypesTemp types;
    objectTypesFromParam(typeParameter, types.m_types);

    Int numTemplates = types.m_types->prepForPlayerCounting(templates, counts);
    if (numTemplates == 0) return false;

    PlayerMaskType playerMask =
        TheScriptEngine->unidentified_0034DB40(playerParameter);
    while (playerMask) {
        Player *player = ThePlayerList->getEachPlayerFromMask(playerMask);
        player->countObjectsByThingTemplate(numTemplates,
            &(*templates.begin()), false, &(*counts.begin()), true);
        condition->setCustomFrame(TheScriptEngine->getFrameObjectCountChanged());
        if (rts::sum(counts) != 0) {
            condition->setCustomData(1);
            return true;
        }
    }

    condition->setCustomData(-1);
    return false;
}

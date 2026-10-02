// ?rva001F7B10@ClickReactionBehavior@@UAEXXZ
// partial score=0.5156 date=2026-10-02
// cl: /O2 /DNDEBUG /DWIN32 /MD /EHsc /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /I.
// stlport
#include <algorithm>
#define OBJECT_TU_MEMBERS void notifyModelConditionChanged();
#include "game/GameEngine/Source/GameLogic/Object/object.h"
class Rva001BEF20FieldAddress { public: char *get(); };
class ClickReactionBehavior;
class Drawable {
    friend class ClickReactionBehavior;
    void applyPendingModelConditionFlags(bool);
};
class Rva001F7B10AI {
public:
    virtual void slot0();
    virtual void slot1();
    virtual void slot2();
    virtual void slot3();
    virtual void slot4();
    virtual void slot5();
    virtual void slot6();
    virtual void slot7();
    virtual void slot8();
    virtual void slot9();
    virtual void slot10();
    virtual void slot11();
    virtual void slot12();
    virtual void slot13();
    virtual void slot14();
    virtual void slot15();
    virtual void slot16();
    virtual void slot17();
    virtual void slot18();
    virtual void slot19();
    virtual void slot20();
    virtual void slot21();
    virtual void slot22();
    virtual void slot23();
    virtual void slot24();
    virtual void slot25();
    virtual void slot26();
    virtual void slot27();
    virtual void slot28();
    virtual void slot29();
    virtual void slot30();
    virtual void slot31();
    virtual void slot32();
    virtual void slot33();
    virtual void slot34();
    virtual void slot35();
    virtual void slot36();
    virtual void slot37();
    virtual void slot38();
    virtual void slot39();
    virtual void slot40();
    virtual void slot41();
    virtual void slot42();
    virtual void slot43();
    virtual void slot44();
    virtual void slot45();
    virtual void slot46();
    virtual void slot47();
    virtual void slot48();
    virtual void slot49();
    virtual void slot50();
    virtual void slot51();
    virtual void slot52();
    virtual void slot53();
    virtual void slot54();
    virtual void slot55();
    virtual void slot56();
    virtual void slot57();
    virtual void slot58();
    virtual void slot59();
    virtual void slot60();
    virtual void slot61();
    virtual void slot62();
    virtual void slot63();
    virtual void slot64();
    virtual void slot65();
    virtual void slot66();
    virtual void slot67();
    virtual void slot68();
    virtual void slot69();
    virtual void slot70();
    virtual void slot71();
    virtual void slot72();
    virtual void slot73();
    virtual void slot74();
    virtual void slot75();
    virtual void slot76();
    virtual void slot77();
    virtual void slot78();
    virtual void slot79();
    virtual void slot80();
    virtual void slot81();
    virtual void slot82();
    virtual void slot83();
    virtual void slot84();
    virtual void slot85();
    virtual void slot86();
    virtual void slot87();
    virtual void slot88();
    virtual void slot89();
    virtual void slot90();
    virtual void slot91();
    virtual void slot92();
    virtual void slot93();
    virtual void slot94();
    virtual void slot95();
    virtual bool query();
};
struct Rva001F7B10Data {
    unsigned char m_unmodelled00[8];
    int m_unmodelled08;
    int m_unmodelled0C[5];
};
class Rva001F7B10Primary {
public:
    virtual void slot0() = 0;
protected:
    Rva001F7B10Data *m_moduleData;
    Object *m_object;
    unsigned char m_unmodelled0C[0x14];
};
class Rva001F7B10Interface {
public:
    virtual void slot0() = 0;
    virtual void rva001F7B10() = 0;
};
class ClickReactionBehavior : public Rva001F7B10Primary, public Rva001F7B10Interface {
public:
    virtual void rva001F7B10();
private:
    int m_unmodelled24;
    int m_unmodelled28;
};
extern int GetGameLogicRandomValue(int,int,char*,int);
void ClickReactionBehavior::rva001F7B10()
{
    Object *object = m_object;
    Rva001F7B10Data *data = m_moduleData;
    if (!object) return;
    Drawable *drawable = object->getDrawable();
    if (!drawable) return;
    if (*(unsigned int *)((Rva001BEF20FieldAddress *)object)->get() & 0x100) return;
    if (object->m_modelConditionFlags[4] & 0x01000000) return;
    if (object->m_modelConditionFlags[5] & 4) return;
    Rva001F7B10AI *ai = (Rva001F7B10AI *)object->m_ai;
    if (!ai || !ai->query()) return;
    int timer = data->m_unmodelled08;
    if (timer <= 0) return;
    m_unmodelled24 += timer;
    int limit = timer*5;
    m_unmodelled24 = _STL::min(m_unmodelled24,limit);
    if (m_unmodelled28 > 0) return;
    int reaction = m_unmodelled24/timer;
    if (reaction <= 3) reaction=GetGameLogicRandomValue(1,3,"F:\\bfme\\Code\\gameengine\\Source\\GameLogic\\Object\\Behavior\\ClickReactionBehavior.cpp",0x74);
    if (reaction <= 0) return;
    int index = reaction - 1;
    unsigned int condition;
    switch(index) {
    case 0: condition=0x04000000; break;
    case 1: condition=0x08000000; break;
    case 2: condition=0x10000000; break;
    case 3: condition=0x20000000; break;
    case 4: condition=0x40000000; break;
    default: condition=0x40000000; break;
    }
    if (!(object->m_modelConditionFlags[4]&condition)) {
        object->m_modelConditionFlags[4] |= condition;
        object->notifyModelConditionChanged();
    }
    drawable->applyPendingModelConditionFlags(false);
    if (index >= 0 && index < 5) m_unmodelled28=data->m_unmodelled0C[index];
}

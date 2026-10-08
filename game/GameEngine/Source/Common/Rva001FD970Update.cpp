// cl: /DNDEBUG /MD /EHsc /O2 /Ob2 /I. /D_STLP_USE_STATIC_LIB
// stlport
// Retail 0x001FD970 uses the update-interface receiver at full object +0x14.
#define _STLP_NO_EXCEPTIONS 1
#include <bitset>
class ModelConditionFlags
{
public:
    // ?test@ModelConditionFlags@@QBE_NH@Z absent-from-retail
    __forceinline bool test(int i) const { return m_bits.test(i); }
    // ?set@ModelConditionFlags@@QAEXHH@Z absent-from-retail
    void set(int i, int value) { m_bits.set(i, value); }

private:
    _STL::bitset<320> m_bits;
};
#define BFME_HAVE_MODELCONDITIONFLAGS

class CountermeasuresBehaviorInterface;
class Rva001BF670Interface
{
public:
    virtual void slot00() = 0;
    virtual void slot04() = 0;
    virtual void slot08() = 0;
};

#define OBJECT_TU_MEMBERS \
    const CountermeasuresBehaviorInterface *getCountermeasuresBehaviorInterface() const; \
    void notifyModelConditionChanged();
#include "game/GameEngine/Source/GameLogic/Object/object.h"
#undef OBJECT_TU_MEMBERS

class BfmeStrF9 { public: void *m_data; };
class BfmeObjF9 { public: void setFlag(const BfmeStrF9 &, char); };
class BfmeHostCL { public: void bfmeResetCL(char); };
class Rva001BEEE0GuardedVCall { public: void forward(int); };
class Pathfinder { public: void addObjectToPathfindMap(Object *); };
class AI { public: unsigned char m_pad00[0xc]; Pathfinder *m_pathfinder; };
extern AI *TheAI;
class GameLogic;
extern GameLogic *TheGameLogic;
struct Rva001FD970Frame { unsigned char m_pad00[0x3c]; int m_frame; };
class Rva001FD970Audio
{
public:
    virtual void slot00(); virtual void slot04(); virtual void slot08();
    virtual void slot0c(); virtual void slot10(); virtual void slot14();
    virtual void slot18(); virtual void slot1c(); virtual void slot20();
    virtual void slot24(); virtual void slot28(); virtual void slot2c();
    virtual void slot30(); virtual void slot34(); virtual void slot38();
    virtual void slot3c(); virtual void slot40(); virtual void slot44();
    virtual void slot48(); virtual void removeAudioEvent(unsigned int);
};
class AudioManager;
extern AudioManager *TheAudio;
extern unsigned int g_sentinel012ADC38;
extern void j_00048d6a();
extern void j_00013d95();
class BfmeThingYD { public: void bfmeSetYD(int); };
class GateOpenAndCloseBehavior { public: void playSound(); };
class Rva001FD5F0Owner { public: void update(); };

struct Rva001FD970Data
{
    unsigned char m_pad00[0xc];
    unsigned int m_field0c;
    unsigned int m_field10;
    unsigned char m_pad14[0x14];
    BfmeStrF9 *m_first;
    BfmeStrF9 *m_second;
    unsigned char m_pad30[4];
    BfmeStrF9 *m_third;
    BfmeStrF9 *m_fourth;
    unsigned char m_pad3c[4];
    unsigned int m_field40;
    unsigned int m_field44;
};

class Rva001FD970Owner
{
public:
    virtual void slot00(); virtual void slot04(); virtual void slot08();
    virtual void slot0c(); virtual void slot10(); virtual void slot14();
    virtual bool slot18(); virtual void slot1c(); virtual void slot20();
    virtual void slot24(); virtual bool slot28();
    void *m_field04;
    Rva001FD970Data *m_data;
    Object *m_object;
    unsigned char m_pad10[0x1c];
    int m_field2c;

    // ?close@Rva001FD970Owner@@QAEX_N@Z absent-from-retail
    __forceinline void close(bool enabled)
    {
        if (m_field2c == 2 && !enabled) return;
        typedef void (Rva001FD970Owner::*Step)();
        union { void *pointer; Step member; } step;
        step.pointer = (void *)j_00048d6a;
        (this->*step.member)();
        Object *object = m_object;
        typedef void (Pathfinder::*Remove)(Object *);
        union { void *pointer; Remove member; } remove;
        // The wrapper forwards live ECX to Pathfinder::updateAt003FA5B0.
        remove.pointer = (void *)j_00013d95;
        (TheAI->m_pathfinder->*remove.member)(object);
        m_field2c = 2;
        reinterpret_cast<Rva001BEEE0GuardedVCall *>(object)->forward(9);
        Rva001FD970Data *data = m_data;
        BfmeObjF9 *flags = reinterpret_cast<BfmeObjF9 *>((unsigned char *)object + 0xac);
        for (BfmeStrF9 *entry = data->m_first; entry != data->m_second; ++entry)
            flags->setFlag(*entry, 1);
        for (BfmeStrF9 *entry = data->m_third; entry != data->m_fourth; ++entry)
            flags->setFlag(*entry, 0);
        reinterpret_cast<BfmeHostCL *>(object)->bfmeResetCL(1);
        TheAI->m_pathfinder->addObjectToPathfindMap(object);
    }
};

class Rva001FD970
{
public:
    int update();
    // ?owner@Rva001FD970@@QAEPAVRva001FD970Owner@@XZ absent-from-retail
    Rva001FD970Owner *owner() { return reinterpret_cast<Rva001FD970Owner *>((unsigned char *)this - 0x14); }
    unsigned char m_pad00[0x14];
    int m_field14;
    int m_field18;
    bool m_field1c;
    unsigned char m_pad1d[3];
    float m_field20;
    float m_field24;
    int m_field28;
    int m_field2c;
    unsigned int m_field30;
    bool m_field34;
};

// ?update@Rva001FD970@@QAEHXZ
int Rva001FD970::update()
{
    Object *object = owner()->m_object;
    if (object == 0) return 1;
    if (object->getCountermeasuresBehaviorInterface())
        const_cast<Rva001BF670Interface *>(reinterpret_cast<const Rva001BF670Interface *>(object->getCountermeasuresBehaviorInterface()))->slot08();
    if (object->m_status[0] & 4) m_field1c = false;
    if (object->m_privateStatus & 1)
    {
        if (m_field14 != 1)
        {
            m_field14 = 0;
            m_field20 = 100.0f;
        }
        owner()->close(false);
        reinterpret_cast<Rva001FD970Audio *>(TheAudio)->removeAudioEvent(m_field30);
        m_field1c = false;
        return 1;
    }
    const Rva001FD970Data *data = owner()->m_data;
    if (m_field2c >= 0 && owner()->slot28() && owner()->slot18() != (m_field2c > 0))
    {
        owner()->slot24();
        if (m_field2c == 0) m_field2c = -1;
    }
    switch (m_field14)
    {
    case 0:
    {
        int elapsed = reinterpret_cast<Rva001FD970Frame *>(TheGameLogic)->m_frame - m_field28;
        m_field20 = float(elapsed) / float(data->m_field0c) * 100.0f;
        if (m_field20 >= 100.0f) reinterpret_cast<BfmeThingYD *>(owner())->bfmeSetYD(1);
        if (m_field20 > float(data->m_field10)) owner()->close(false);
        unsigned int duration = data->m_field40 == g_sentinel012ADC38 ? data->m_field0c : data->m_field40;
        if ((unsigned int)elapsed > duration && !m_field34)
            reinterpret_cast<GateOpenAndCloseBehavior *>(owner())->playSound();
        m_field1c = false;
        if ((object->m_modelConditionFlags.test(22)) || !(object->m_modelConditionFlags.test(21)))
        {
            object->m_modelConditionFlags.set(22, 0);
            object->m_modelConditionFlags.set(21, 1);
            object->notifyModelConditionChanged();
        }
        break;
    }
    case 1:
        m_field20 = 100.0f;
        m_field1c = true;
        if ((object->m_modelConditionFlags.test(22)) || !(object->m_modelConditionFlags.test(21)))
        {
            object->m_modelConditionFlags.set(22, 0);
            object->m_modelConditionFlags.set(21, 1);
            object->notifyModelConditionChanged();
        }
        owner()->close(false);
        break;
    case 2:
    {
        int elapsed = reinterpret_cast<Rva001FD970Frame *>(TheGameLogic)->m_frame - m_field28;
        m_field20 = float(elapsed) / float(data->m_field0c) * 100.0f;
        if (m_field20 >= 100.0f) reinterpret_cast<BfmeThingYD *>(owner())->bfmeSetYD(3);
        if (m_field20 > float(100u - data->m_field10))
            reinterpret_cast<Rva001FD5F0Owner *>(owner())->update();
        unsigned int duration = data->m_field44 == g_sentinel012ADC38 ? data->m_field0c : data->m_field44;
        if ((unsigned int)elapsed > duration && !m_field34)
            reinterpret_cast<GateOpenAndCloseBehavior *>(owner())->playSound();
        m_field1c = false;
        if ((object->m_modelConditionFlags.test(21)) || !(object->m_modelConditionFlags.test(22)))
        {
            object->m_modelConditionFlags.set(21, 0);
            object->m_modelConditionFlags.set(22, 1);
            object->notifyModelConditionChanged();
        }
        break;
    }
    case 3:
        m_field20 = 100.0f;
        m_field1c = true;
        if ((object->m_modelConditionFlags.test(21)) || !(object->m_modelConditionFlags.test(22)))
        {
            object->m_modelConditionFlags.set(21, 0);
            object->m_modelConditionFlags.set(22, 1);
            object->notifyModelConditionChanged();
        }
        reinterpret_cast<Rva001FD5F0Owner *>(owner())->update();
        break;
    }
    if (object->m_status[0] & 4) m_field1c = false;
    return 1;
}

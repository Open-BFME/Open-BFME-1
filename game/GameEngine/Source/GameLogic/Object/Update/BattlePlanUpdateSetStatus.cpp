// cl: /DNDEBUG /MD /EHsc /Igame/Libraries/Source/WWVegas/WWLib /Igame/GameEngine/Source/GameLogic/Object
// stlport
#define _STLP_NO_EXCEPTIONS 1
// Native template definitions are required: explicit specializations let VC7.1
// infer a narrower callee register-clobber set and change this caller.
#include "string_base.h"
template <typename T> bool StringBase<T>::isEmpty() const
{
    return m_data == 0 || m_data->length == 0;
}
template <typename T> bool StringBase<T>::isNotEmpty() const
{
    return !isEmpty();
}
// This caller uses the out-of-line AsciiString copy constructor at ILT 0x416af.
// ascii_string.h makes that constructor inline; adopting it changes the
// saved-ESP/ECX ordering at +0x285 and selects the StringBase constructor.
// Keep the canonical base and the same derived layout, with this one ctor
// declared out of line. The emitted AsciiStringNative.cpp body proves the ABI.
class AsciiString : public StringBase<char>
{
  public:
    AsciiString(const AsciiString &);
    ~AsciiString();
    bool isEmpty() const
    {
        return StringBase<char>::isEmpty();
    }
    bool isNotEmpty() const
    {
        return StringBase<char>::isNotEmpty();
    }
};
#include "unicode_string.h"
#include <bitset>

struct Coord3D
{
    float x, y, z;
};
class BattleStatusFlags
{
    _STL::bitset<320> bits;

  public:
    bool test(int b) const
    {
        return bits.test(b);
    }
    void set(int b)
    {
        bits.set(b);
    }
    void reset(int b)
    {
        bits.reset(b);
    }
};
class Player;
#define BFME_HAVE_COORD3D
#define BFME_HAVE_MODELCONDITIONFLAGS
#define OBJECT_TU_MEMBERS                                                                          \
    void notifyModelConditionChanged();                                                            \
    Player *getControllingPlayer() const;                                                          \
    unsigned getID() const                                                                         \
    {                                                                                              \
        return m_id;                                                                               \
    }                                                                                              \
    const Coord3D *getPosition() const                                                             \
    {                                                                                              \
        return &m_cachedPos;                                                                       \
    }
#define ModelConditionFlags BattleStatusFlags
#include "object.h"
#undef ModelConditionFlags
class Drawable
{
  public:
    void setAnimationLoopDuration(unsigned);
};
static __forceinline void clearCondition(Object *o, int bit)
{
    if (o->m_modelConditionFlags.test(bit))
    {
        o->m_modelConditionFlags.reset(bit);
        o->notifyModelConditionChanged();
    }
}
static __forceinline void setCondition(Object *o, int bit)
{
    if (!o->m_modelConditionFlags.test(bit))
    {
        o->m_modelConditionFlags.set(bit);
        o->notifyModelConditionChanged();
    }
}
extern void j_00019a6a();
extern void j_00040a52();
extern void j_00001e88();
extern void j_0002d5c4();
extern void j_00018b4c();
extern void j_0002a53b();
extern void j_00037ab0();
class AudioEventRTS
{
  public:
    virtual ~AudioEventRTS();
    char pad04[8];
    unsigned handle;
    char pad10[4];
    AsciiString name;
    char pad18[0x58];
    void setObjectID(unsigned id);
    void setPlayingHandle(unsigned id)
    {
        typedef void (AudioEventRTS::*Fn)(unsigned);
        union {
            void (*raw)();
            Fn member;
        } c;
        c.raw = j_00040a52;
        (this->*c.member)(id);
    }
    unsigned getPlayingHandle()
    {
        return handle;
    }
    const AsciiString &getEventName() const
    {
        return name;
    }
    void setPosition(const Coord3D *p)
    {
        typedef void (AudioEventRTS::*Fn)(const Coord3D *);
        union {
            void (*raw)();
            Fn member;
        } c;
        c.raw = j_00001e88;
        (this->*c.member)(p);
    }
};
class AudioManager
{
  public:
    virtual void slot00();
    virtual void slot04();
    virtual void slot08();
    virtual void slot0c();
    virtual void slot10();
    virtual void slot14();
    virtual void slot18();
    virtual void slot1c();
    virtual void slot20();
    virtual void slot24();
    virtual void slot28();
    virtual void slot2c();
    virtual void slot30();
    virtual void slot34();
    virtual void slot38();
    virtual void slot3c();
    virtual void slot40();
    virtual unsigned addAudioEvent(const AudioEventRTS *);
    virtual void slot48();
    virtual void removeAudioEvent(unsigned);
};
class GameLogic;
extern GameLogic *TheGameLogic;
struct RvaBattlePlanLogicView
{
    char pad[0x3c];
    unsigned frame;
};
class Radar
{
};
class GameTextInterface
{
  public:
    virtual void slot00();
    virtual void slot04();
    virtual void slot08();
    virtual void slot0c();
    virtual void slot10();
    virtual void slot14();
    virtual void slot18();
    virtual void slot1c();
    virtual void slot20();
    virtual UnicodeString fetch(AsciiString, bool *);
};
class InGameUI
{
  public:
    virtual void slot00();
    virtual void slot04();
    virtual void slot08();
    virtual void slot0c();
    virtual void slot10();
    virtual void slot14();
    virtual void slot18();
    virtual void slot1c();
    virtual void slot20();
    virtual void slot24();
    virtual void slot28();
    virtual void slot2c();
    virtual void slot30();
    virtual void __cdecl message(UnicodeString, ...);
};
extern AudioManager *TheAudio;
extern Radar *TheRadar;
extern GameTextInterface *TheGameText;
extern InGameUI *TheInGameUI;
struct BattlePlanUpdateModuleData
{
    char pad[0xc];
    unsigned m_bombardmentPlanAnimationFrames, m_holdTheLinePlanAnimationFrames,
        m_searchAndDestroyPlanAnimationFrames, m_transitionIdleFrames;
    AsciiString m_bombardmentUnpackName, m_bombardmentPackName, m_bombardmentMessageLabel,
        m_bombardmentAnnouncementName;
    AsciiString m_searchAndDestroyUnpackName, m_searchAndDestroyIdleName,
        m_searchAndDestroyPackName, m_searchAndDestroyMessageLabel,
        m_searchAndDestroyAnnouncementName;
    AsciiString m_holdTheLineUnpackName, m_holdTheLinePackName, m_holdTheLineMessageLabel;
};
enum TransitionStatus
{
    IDLE,
    UNPACKING,
    ACTIVE,
    PACKING
};
enum BattlePlanStatus
{
    NONE,
    BOMBARDMENT,
    HOLDTHELINE,
    SEARCHANDDESTROY
};
class BattlePlanUpdate
{
    void *vtable;
    BattlePlanUpdateModuleData *data;
    Object *object;
    char pad0c[0x18];
    BattlePlanStatus m_currentPlan;
    int pad28[2];
    TransitionStatus m_status;
    unsigned m_nextReadyFrame;
    char pad38[0xc];
    // Retail event banks: +0x44, +0x204, +0x3c4 and +0x584; stride 0x70.
    AudioEventRTS unpack[4], pack[4], announcement[4], idle[4];
    void createVisionObject()
    {
        typedef void (BattlePlanUpdate::*Fn)();
        union {
            void (*raw)();
            Fn member;
        } c;
        c.raw = j_0002a53b;
        (this->*c.member)();
    }
    void setBattlePlan(BattlePlanStatus s)
    {
        typedef void (BattlePlanUpdate::*Fn)(BattlePlanStatus);
        union {
            void (*raw)();
            Fn member;
        } c;
        c.raw = j_00037ab0;
        (this->*c.member)(s);
    }

  protected:
    void setStatus(TransitionStatus newStatus);
};
void BattlePlanUpdate::setStatus(TransitionStatus newStatus)
{
    const BattlePlanUpdateModuleData *modData = data;
    Object *obj = object;
    if (m_status == newStatus)
        return;
    TransitionStatus oldStatus = m_status;
    switch (oldStatus)
    {
    case UNPACKING:
        switch (m_currentPlan)
        {
        case BOMBARDMENT:
            clearCondition(obj, 21);
            break;
        case HOLDTHELINE:
            clearCondition(obj, 25);
            break;
        case SEARCHANDDESTROY:
            clearCondition(obj, 29);
            break;
        }
        TheAudio->removeAudioEvent(unpack[m_currentPlan].getPlayingHandle());
        break;
    case ACTIVE:
        switch (m_currentPlan)
        {
        case BOMBARDMENT:
            clearCondition(obj, 24);
            break;
        case HOLDTHELINE:
            clearCondition(obj, 28);
            break;
        case SEARCHANDDESTROY:
            clearCondition(obj, 32);
            break;
        }
        TheAudio->removeAudioEvent(idle[m_currentPlan].getPlayingHandle());
        break;
    case PACKING:
        switch (m_currentPlan)
        {
        case BOMBARDMENT:
            clearCondition(obj, 22);
            break;
        case HOLDTHELINE:
            clearCondition(obj, 26);
            break;
        case SEARCHANDDESTROY:
            clearCondition(obj, 30);
            break;
        }
        TheAudio->removeAudioEvent(pack[m_currentPlan].getPlayingHandle());
        break;
    }
    unsigned now = ((RvaBattlePlanLogicView *)TheGameLogic)->frame;
    switch (newStatus)
    {
    case IDLE:
        m_currentPlan = NONE;
        m_nextReadyFrame = now + modData->m_transitionIdleFrames;
        break;
    case UNPACKING: {
        typedef void (Radar::*Fn)(Player *, const Coord3D *, int, float);
        union {
            void (*raw)();
            Fn member;
        } call;
        call.raw = j_00018b4c;
        (TheRadar->*call.member)(obj->getControllingPlayer(), obj->getPosition(), 7, 4.0f);
    }
        createVisionObject();
        switch (m_currentPlan)
        {
        case BOMBARDMENT:
            setCondition(obj, 21);
            obj->getDrawable()->setAnimationLoopDuration(modData->m_bombardmentPlanAnimationFrames);
            m_nextReadyFrame = now + modData->m_bombardmentPlanAnimationFrames;
            TheInGameUI->message(TheGameText->fetch(modData->m_bombardmentMessageLabel, 0));
            break;
        case HOLDTHELINE:
            setCondition(obj, 25);
            obj->getDrawable()->setAnimationLoopDuration(modData->m_holdTheLinePlanAnimationFrames);
            m_nextReadyFrame = now + modData->m_holdTheLinePlanAnimationFrames;
            TheInGameUI->message(TheGameText->fetch(modData->m_holdTheLineMessageLabel, 0));
            break;
        case SEARCHANDDESTROY:
            setCondition(obj, 29);
            obj->getDrawable()->setAnimationLoopDuration(
                modData->m_searchAndDestroyPlanAnimationFrames);
            m_nextReadyFrame = now + modData->m_searchAndDestroyPlanAnimationFrames;
            TheInGameUI->message(TheGameText->fetch(modData->m_searchAndDestroyMessageLabel, 0));
            break;
        }
        {
            if (unpack[m_currentPlan].getEventName().isNotEmpty())
            {
                unpack[m_currentPlan].setObjectID(obj->getID());
                unpack[m_currentPlan].setPlayingHandle(
                    TheAudio->addAudioEvent(&unpack[m_currentPlan]));
            }
        }
        {
            if (announcement[m_currentPlan].getEventName().isEmpty() == false)
            {
                announcement[m_currentPlan].setPosition(obj->getPosition());
                TheAudio->addAudioEvent(&announcement[m_currentPlan]);
            }
        }
        break;
    case ACTIVE:
        setBattlePlan(m_currentPlan);
        switch (m_currentPlan)
        {
        case BOMBARDMENT:
            setCondition(obj, 24);
            break;
        case HOLDTHELINE:
            setCondition(obj, 28);
            break;
        case SEARCHANDDESTROY:
            setCondition(obj, 32);
            break;
        }
        {
            if (idle[m_currentPlan].getEventName().isNotEmpty())
            {
                idle[m_currentPlan].setObjectID(obj->getID());
                idle[m_currentPlan].setPlayingHandle(TheAudio->addAudioEvent(&idle[m_currentPlan]));
            }
        }
        break;
    case PACKING:
        setBattlePlan(NONE);
        switch (m_currentPlan)
        {
        case BOMBARDMENT:
            setCondition(obj, 22);
            obj->getDrawable()->setAnimationLoopDuration(modData->m_bombardmentPlanAnimationFrames);
            m_nextReadyFrame = now + modData->m_bombardmentPlanAnimationFrames;
            break;
        case HOLDTHELINE:
            setCondition(obj, 26);
            obj->getDrawable()->setAnimationLoopDuration(modData->m_holdTheLinePlanAnimationFrames);
            m_nextReadyFrame = now + modData->m_holdTheLinePlanAnimationFrames;
            break;
        case SEARCHANDDESTROY:
            setCondition(obj, 30);
            obj->getDrawable()->setAnimationLoopDuration(
                modData->m_searchAndDestroyPlanAnimationFrames);
            m_nextReadyFrame = now + modData->m_searchAndDestroyPlanAnimationFrames;
            break;
        }
        {
            if (pack[m_currentPlan].getEventName().isNotEmpty())
            {
                pack[m_currentPlan].setObjectID(obj->getID());
                pack[m_currentPlan].setPlayingHandle(TheAudio->addAudioEvent(&pack[m_currentPlan]));
            }
        }
        break;
    }
    m_status = newStatus;
}

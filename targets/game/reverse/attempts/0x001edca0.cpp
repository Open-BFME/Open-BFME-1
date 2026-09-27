// ??1AutoAbilityBehaviorModuleData@@UAE@XZ
// partial score=0.9660493827160493 date=2026-09-27
// cl: /DNDEBUG /DWIN32 /MD /EHsc /D_STLP_USE_STATIC_LIB /Igame/Libraries/Source/WWVegas/WWLib /Igame/GameEngine/Source/GameLogic
// stlport
#define _STLP_NO_EXCEPTIONS 1
#define BFME_STLP_NODE_ALLOC 1
#include <vector>
#include "ascii_string.h"

// Retail 001EDCA0, 1944 bytes, is NOT a ModuleData destructor.
// Incoming ECX is a secondary receiver: Object* at -8; command string at +10.
// It returns sleep delays 6/50/3fffffff, searches targets, and dispatches commands.
// No Zero Hour AutoAbility twin exists in the vendored GeneralsMD tree.
// Identity: constructor 001ED8A0 installs 010A1AF4 at primary +10.
// That interface's slot zero -> ILT 00010A2D -> 001EDCA0. The ZH
// UpdateModuleInterface slot zero is update(). ModuleData's real destructor
// instead routes through 00003C51 to 001ED890. This view uses the update
// interface receiver, like the landed DelayedLuaEventUpdate.cpp.
// Remaining mismatch: loop-invariant constants at +27B/+280. Retail keeps
// EBX=100 and EDI=400; ours keeps EDI=100 and EBX=800. 66 masked bytes.
// Independently verified visible helpers: player filter ctor 39B at 160CE0;
// command-target filter ctor 46B at 1ED510; iterator next 25B at C44D0.
// Do not land without resolving REL32s and checking vtable DIR32 identities.
// Candidate vtable ObjectFilter010956B0 is address-labelled deliberately:
// the existing DistLODPrototypeClass claim on this table conflicts with its
// use as a partition filter and must not be reused as identity evidence.
typedef unsigned int UInt;
class Object;
class Player;
struct Coord3D { float x,y,z; };
#include "command_source_type.h"
enum KindOfType { KINDOF_89 = 89 };
enum IterOrderType { ITER_FASTEST = 0 };

struct MaskWords001EDCA0 { UInt words[10]; };
class Rva001ED9A0Mask {
public:
    bool intersects(const UInt *);
};
class CommandButton {
public:
    char pad000[0x18];
    UInt m_options;
    char pad01c[0x174-0x1c];
    bool m_174;
    bool m_175;
    char pad176[2];
    float m_178;
    float m_17c;
    bool m_180;
    char pad181[0x1b0-0x181];
    MaskWords001EDCA0 m_1b0;
};
class ControlBar {
public:
    const CommandButton *findCommandButton(const AsciiString &);
};
extern ControlBar *TheControlBar;

class BfmePartitionThingTemplate {
public:
    BfmePartitionThingTemplate *getFinalOverride();
    void *m_00;
    BfmePartitionThingTemplate *m_nextOverride;
    char pad008[0xc8-8];
    UInt m_kindof[6];
};
class Body001EDCA0 {
public:
    virtual void slot0(); virtual void slot1(); virtual void slot2();
    virtual void slot3(); virtual void slot4(); virtual float fraction001EDCA0();
};
struct AI001EDCA0 {
    char pad000[0x48];
    int m_48;
};
class Thing { public: bool isKindOf(KindOfType) const; };
class Object : public Thing {
public:
    Player *getControllingPlayer() const;
    float getVisionRange() const;
    void doCommandButtonAtObject(const CommandButton *, Object *, CommandSourceType, bool);
    void doCommandButtonAtPosition(const CommandButton *, const Coord3D *, CommandSourceType, bool);
    void doCommandButton(const CommandButton *, int, int);
    __forceinline BfmePartitionThingTemplate *getTemplate001EDCA0() const {
        BfmePartitionThingTemplate *p = m_04;
        if (!p) return 0;
        if (p->m_nextOverride) return p->m_nextOverride->getFinalOverride();
        return p;
    }
    __forceinline UInt hasKind001EDCA0(int bit) const {
        return getTemplate001EDCA0()->m_kindof[bit/32] & (1U << (bit%32));
    }
    void *m_00;
    BfmePartitionThingTemplate *m_04;
    char pad008[0x38-8];
    Coord3D m_position;
    char pad044[0x110-0x44];
    MaskWords001EDCA0 m_110;
    char pad138[0x200-0x138];
    Body001EDCA0 *m_200;
    AI001EDCA0 *m_204;
    char pad208[0x344-0x208];
    UInt m_privateStatus;
};

class PartitionFilter {
public:
    PartitionFilter() : m_next(0) {}
    virtual ~PartitionFilter() {}
    virtual bool allow(Object *) = 0;
    virtual int getPlayerMask();
    PartitionFilter *link(PartitionFilter *);
    PartitionFilter *m_next;
};
class Rva0025ED50ObjectFilter : public PartitionFilter {
public:
    Rva0025ED50ObjectFilter(Object *p) : m_object(p) {}
    virtual ~Rva0025ED50ObjectFilter() {}
    virtual bool allow(Object *);
    Object *m_object;
};
class ObjectFilter010956B0 : public PartitionFilter {
public:
    ObjectFilter010956B0(Object *p) : m_object(p) {}
    virtual ~ObjectFilter010956B0() {}
    virtual bool allow(Object *);
    virtual int getPlayerMask();
    Object *m_object;
};
class Rva0025ED50RootFilter : public PartitionFilter {
public:
    Rva0025ED50RootFilter() {}
    virtual ~Rva0025ED50RootFilter() {}
    virtual bool allow(Object *);
};
class Rva00260180SelfFilter : public PartitionFilter {
public:
    Rva00260180SelfFilter(Object *p) : m_object(p) {}
    virtual ~Rva00260180SelfFilter() {}
    virtual bool allow(Object *);
    Object *m_object;
};
class PartitionFilterValidCommandButtonTarget : public PartitionFilter {
public:
    __declspec(noinline) PartitionFilterValidCommandButtonTarget(Object *source,
        const CommandButton *button, bool match, CommandSourceType sourceType)
        : m_source(source), m_commandButton(button), m_match(match), m_commandSource(sourceType) {}
    virtual bool allow(Object *);
    Object *m_source;
    const CommandButton *m_commandButton;
    bool m_match;
    CommandSourceType m_commandSource;
};
class PartitionFilterPlayerAffiliation : public PartitionFilter {
public:
    __declspec(noinline) PartitionFilterPlayerAffiliation(Player *player, int flags, bool match)
        : m_player(player), m_match(match), m_flags(flags) {}
    virtual bool allow(Object *);
    virtual int getPlayerMask();
    Player *m_player;
    bool m_match;
    int m_flags;
};
struct Rva0025ED50Entry { Object *object; UInt unknown04; };
struct Rva0025ED50ResultData {
    std::vector<Rva0025ED50Entry> entries;
    Rva0025ED50Entry *current;
    int references;
};
struct Rva0025ED50WideResult {
    Rva0025ED50ResultData *value;
    Rva0025ED50WideResult();
    Rva0025ED50WideResult(const Rva0025ED50WideResult &);
    ~Rva0025ED50WideResult() { if (--value->references == 0) delete value; }
    Object *next(Object *&object) {
        if (value->current == value->entries.end()) { object = 0; return 0; }
        object = (value->current++)->object;
        return object;
    }
    __declspec(noinline) Object *next() {
        if (value->current == value->entries.end()) return 0;
        return (value->current++)->object;
    }
};
class PartitionManager {
public:
    Rva0025ED50WideResult iterate(const Coord3D *, float, IterOrderType, PartitionFilter *, bool);
};
extern PartitionManager *ThePartitionManager;
enum UpdateSleepTime { UPDATE_SLEEP_FOREVER = 0x3fffffff };
class AutoAbilityBehavior {
public:
    virtual UpdateSleepTime update();
    bool bfmeCanAutoFire() const;
};

UpdateSleepTime AutoAbilityBehavior::update()
{
    Object *object = *(Object **)((char *)this - 8);
    AsciiString &command = *(AsciiString *)((char *)this + 0x10);
    const CommandButton *button = TheControlBar->findCommandButton(command);
    if (!button || (object->m_privateStatus & 1)) {
        command.StringBase<char>::set("", 0);
        return UPDATE_SLEEP_FOREVER;
    }
    {
    MaskWords001EDCA0 mask = button->m_1b0;
    if (((Rva001ED9A0Mask *)&object->m_110)->intersects(mask.words)) {
        command.StringBase<char>::set("", 0);
        return UPDATE_SLEEP_FOREVER;
    }
    }
    bool state = (object->m_110.words[6] >> 11) & 1;
    if (((button->m_options & 0x4000000) && !state) ||
        ((button->m_options & 0x8000000) && state)) {
        command.StringBase<char>::set("", 0);
        return UPDATE_SLEEP_FOREVER;
    }
    if (((AutoAbilityBehavior *)((char *)this - 0x10))->bfmeCanAutoFire()) {
        int delay = 50;
        if (button->m_17c > 0.0f) delay = (int)(button->m_17c * 5.0f);
        if (button->m_175) {
            object->doCommandButton(button, CMD_FROM_AI, false);
            return (UpdateSleepTime)delay;
        }
        int relationship = 4;
        if (button->m_174) relationship = 2;
        float range = object->getVisionRange();
        if (button->m_178 > 0.0f) range = button->m_178;
        if (button->m_options & 7) {
            Rva0025ED50WideResult iterator = ThePartitionManager->iterate(
                &object->m_position, range, ITER_FASTEST,
                PartitionFilterPlayerAffiliation(object->getControllingPlayer(), relationship, true).link(
                    PartitionFilterValidCommandButtonTarget(object, button, true, CMD_FROM_AI).link(
                        Rva00260180SelfFilter(object).link(
                            Rva0025ED50RootFilter().link(
                                ObjectFilter010956B0(object).link(&Rva0025ED50ObjectFilter(object)))))), true);
            Object *target;
            while (iterator.next(target)) {
                if (!(target->hasKind001EDCA0(8) || target->hasKind001EDCA0(10) || target->hasKind001EDCA0(9) || target->hasKind001EDCA0(11))) continue;
                if (target->hasKind001EDCA0(53)) continue;
                if (target->hasKind001EDCA0(108)) continue;
                if (target->hasKind001EDCA0(129)) continue;
                if (object->m_204) object->m_204->m_48 = 2;
                object->doCommandButtonAtObject(button, target, CMD_FROM_AI, true);
                return (UpdateSleepTime)delay;
            }
        } else {
            Rva0025ED50WideResult iterator = ThePartitionManager->iterate(
                &object->m_position, range, ITER_FASTEST,
                PartitionFilterPlayerAffiliation(object->getControllingPlayer(), relationship, true).link(
                    Rva00260180SelfFilter(object).link(
                        Rva0025ED50RootFilter().link(&Rva0025ED50ObjectFilter(object)))), true);
            Object *target = 0;
            if (button->m_180) {
                for (Object *other = iterator.next(); other; other = iterator.next()) {
                    if (other->isKindOf(KINDOF_89)) {
                        Body001EDCA0 *body = other->m_200;
                        if (body && body->fraction001EDCA0() < 0.8f) { target = other; break; }
                    }
                }
            } else {
                Object *other;
                while (iterator.next(other)) {
                    if (!(other->hasKind001EDCA0(8) || other->hasKind001EDCA0(10) || other->hasKind001EDCA0(9) || other->hasKind001EDCA0(11))) continue;
                    if (other->hasKind001EDCA0(53)) continue;
                    if (other->hasKind001EDCA0(108)) continue;
                    if (other->hasKind001EDCA0(129)) continue;
                    target = other; break;
                }
            }
            if (target) {
                if (object->m_204) object->m_204->m_48 = 2;
                if ((bool)((button->m_options >> 5) & 1))
                    object->doCommandButtonAtPosition(button, &target->m_position, CMD_FROM_AI, true);
                else object->doCommandButton(button, CMD_FROM_AI, true);
                return (UpdateSleepTime)delay;
            }
        }
    }
    return (UpdateSleepTime)6;
}

// Retail RVA 0x0041EBD0, 812 bytes, thiscall with one event-info pointer.
// Original method identity is unproved; field names retain observed offsets.
// The info +0x0C mask is 16 bits, +0x10 is a discriminator, +0x50 a float.
// Native STLport list lifetime, push_back(this), and explicit scalar argument
// copies preserve both register allocation and the exception-cleanup sequence.
// The 391-byte timing sibling is called through retail ILT 0x0002F84C.
// Radar::notify00108A60 is an ABI view of the independently decoded 37-byte
// bfmeGoEZF body. It reads its Object stack argument, uses position +0x38,
// calls the radar-event helper with 3, then the control-bar helper, and RET 4.
// Its receiver is unused by the callee but is explicitly supplied by retail.
// Coord3D retains the struct ABI of the existing Eva callee contracts;
// the canonical WWMath header instead declares a nontrivial class Coord3D.
// stlport
#define _STLP_USE_STATIC_LIB 1
#define _STLP_NO_EXCEPTIONS 1
#include <list>
class Object;
class Drawable;
class Team;
class Module;
struct Coord3D
{
    float x, y, z;
};
enum KindOfType
{
    K7 = 7,
    K37 = 37,
    K89 = 89
};
enum NameKeyType
{
    NK0 = 0
};
enum Relationship
{
    REL2 = 2
};
enum EvaMessage
{
    EVA1 = 1,
    EVA2 = 2
};
enum ObjectStatusTypes
{
    STATUS37 = 37
};
class ThingTemplate
{
  public:
    char m_00[0x438];
    unsigned m_438;
    char m_43c[0x458 - 0x43c];
    EvaMessage m_458;
};
class Thing
{
  public:
    bool isKindOf(KindOfType) const;
    const ThingTemplate *getTemplate() const;
};
class Player
{
  public:
    bool isLocalPlayer() const;
    Relationship getRelationship(const Team *) const;
    char m_00[0x24];
    int m_playerIndex;
};
class PlayerList
{
  public:
    char m_00[12];
    Player *m_local;
};
extern PlayerList *ThePlayerList;
class Object
{
  public:
    virtual void s0();
    virtual void s1();
    virtual void s2();
    virtual void s3();
    virtual void s4();
    virtual void s5();
    virtual void s6();
    virtual void s7();
    virtual void s8();
    virtual void s9();
    virtual Drawable *getDrawable() const;
    char m_04[0x38 - 4];
    Coord3D m_position;
    char m_44[0x20c - 0x44];
    void *m_20c;
    char m_210[0x23c - 0x210];
    Team *m_team;
    Player *getControllingPlayer() const;
    Module *findModule(NameKeyType) const;
    bool testStatus(ObjectStatusTypes) const;
    bool query(Object *, int);
};
class BFMESelectionStatusBits
{
  public:
    bool test(unsigned) const;
};
struct RvaC4390First;
class RvaC4390Second
{
  public:
    RvaC4390First *resolve(int);
};
class Module
{
  public:
    char m_00[0x18];
    int m_18;
};
class Rva0036CF70Selection
{
  public:
    int firstValue() const;
    int secondValue() const;
};
class NameKeyGenerator
{
  public:
    NameKeyType nameToKey(const char *);
};
extern NameKeyGenerator *TheNameKeyGenerator;
class GameLogic
{
  public:
    char m_00[0x3c];
    unsigned m_frame;
    Object *findObjectByID(int);
};
extern GameLogic *TheGameLogic;
class Eva
{
  public:
    bool setShouldPlay(EvaMessage, const Coord3D *);
    void setShouldPlay(EvaMessage);
};
extern Eva *TheEva;
class Radar
{
  public:
    void notify00108A60(const Object *);
};
extern Radar *TheRadar;
struct Rva0058D8E0Target;
class Rva0058D8E0SlotLookup
{
  public:
    void selectMatchingSlot(Rva0058D8E0Target *);
};
struct Global0041EBD0
{
    char m_00[0x2b8];
    Rva0058D8E0SlotLookup m_2b8;
};
extern Global0041EBD0 *g_012F4B98;
class DrawableTiming0041E9E0
{
  public:
    void update();
};
class PickAndPlayInfo;
class GameMessage
{
  public:
    enum Type
    {
        MSG_7E3 = 0x7e3
    };
};
bool pickAndPlayUnitVoiceResponse(const std::list<Drawable *> *, GameMessage::Type,
                                  PickAndPlayInfo *);
struct ReactionInfo0041EBD0
{
    char m_00[8];
    int m_08;
    unsigned short m_0c;
    char m_0e[2];
    int m_10;
    char m_14[0x21 - 0x14];
    bool m_21;
    char m_22[0x50 - 0x22];
    float m_50;
};
class Drawable : public Thing
{
  public:
    char m_00[0xfc];
    Object *m_object;
    char m_100[0x210];
    unsigned m_310;
    void react0041EBD0(const ReactionInfo0041EBD0 *);
};
void Drawable::react0041EBD0(const ReactionInfo0041EBD0 *info)
{
    Object *object = m_object;
    if (!object)
        return;
    Player *player = object->getControllingPlayer();
    if (!(info->m_50 > 0.0f) || info->m_10 == 10 || info->m_10 == 7 ||
        (info->m_0c & (unsigned short)(1 << player->m_playerIndex)))
        return;
    if (isKindOf(K7))
    {
        bool eligible = false;
        EvaMessage first = EVA1, second = EVA2;
        if (isKindOf(K37))
            eligible = true;
        static NameKeyType key = TheNameKeyGenerator->nameToKey("CastleMemberBehavior");
        Module *member = object->findModule(key);
        if (member && member->m_18)
        {
            first = (EvaMessage)((Rva0036CF70Selection *)member)->firstValue();
            second = (EvaMessage)((Rva0036CF70Selection *)member)->secondValue();
            eligible = true;
        }
        if (eligible)
        {
            if (player->isLocalPlayer())
                TheEva->setShouldPlay(first, &object->m_position);
            else
            {
                Team *team = object->m_team;
                Player *local = ThePlayerList->m_local;
                if (local->getRelationship(team) == REL2)
                    TheEva->setShouldPlay(second, &object->m_position);
            }
        }
    }
    if (!((BFMESelectionStatusBits *)object)->test(0x93) &&
        !((BFMESelectionStatusBits *)object)->test(0x3e) && !object->testStatus(STATUS37))
    {
        Object *source = TheGameLogic->findObjectByID(info->m_08);
        if (source && !source->query((Object *)player, 1))
        {
            bool played = true;
            unsigned now = TheGameLogic->m_frame;
            if (m_310 <= now)
            {
                Object *related = (Object *)((RvaC4390Second *)object)->resolve(0);
                Drawable *other = related ? related->getDrawable() : 0;
                if (!other || other->m_310 <= TheGameLogic->m_frame)
                {
                    std::list<Drawable *> list;
                    list.push_back(this);
                    if (pickAndPlayUnitVoiceResponse(&list, GameMessage::MSG_7E3, 0))
                    {
                        EvaMessage message = getTemplate()->m_458;
                        TheEva->setShouldPlay(message);
                    }
                    else
                        played = false;
                }
            }
            if (played)
                ((DrawableTiming0041E9E0 *)this)->update();
        }
    }
    const ThingTemplate *t = getTemplate();
    if (t)
    {
        unsigned duration = t->m_438;
        m_310 = duration + TheGameLogic->m_frame;
    }
    if (player->isLocalPlayer())
    {
        if (info->m_21)
        {
            if (object->m_20c)
                TheRadar->notify00108A60(object);
            if (getTemplate())
                TheEva->setShouldPlay(getTemplate()->m_458, &object->m_position);
        }
        if (isKindOf(K89))
            g_012F4B98->m_2b8.selectMatchingSlot((Rva0058D8E0Target *)object);
    }
}

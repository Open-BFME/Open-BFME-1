// Retail RVA 0x00419F00, 647 bytes. Original method identity is unproved.
// Enumerates the matched 0x00419E40 predicate with {Drawable*, message} context,
// schedules EVA/radar events, then handles CastleMemberBehavior/CastleBehavior.
// Object::nearest004182A0 is a niladic thiscall returning the nearest Object;
// its full 271-byte body and both aligned caller sites establish its ABI.
// The 0x00410C90 callback is a 30-byte cdecl body: test Object, virtual getDrawable,
// OR drawable status with 0x40, return 1; its second callback argument is unused.
// Player::iterateObjects is declared with the void-predicate/int-result ABI
// established by the matched body at 0x000CDCF0 (retail call via ILT 0x0002F1CB);
// the predicate return value is discarded and the int result compared to 1.
// The source-visible message and castle-ID locals preserve retail's evaluation
// order; removing them also causes the compiler to hoist constant 1 into EBX.
// Coord3D retains the struct ABI of the existing Radar/Eva callee contracts;
// the canonical WWMath header instead declares a nontrivial class Coord3D.
class Player;
class Module;
class Drawable;

#include "../../../Libraries/Include/Lib/Coord3D.h"

enum KindOfType
{
    K7 = 7,
    K47 = 47
};
enum NameKeyType
{
    NK0 = 0
};
enum EvaMessage
{
    EVA8 = 8
};
enum RadarEventType
{
    RADAR10 = 10
};

class Overridable
{
  public:
    const Overridable *getFinalOverride() const;
    void *m_vtable;
    Overridable *m_nextOverride;
};

class ThingTemplate : public Overridable
{
  public:
    char m_08[0x45c - 8];
    int m_45c;

    bool bfmeTemplatePredicate() const;
    bool isKindOf(KindOfType) const;
};

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
    char m_44[0x344 - 0x44];
    unsigned m_privateStatus;

    bool query(Object *, int);
    Player *getControllingPlayer() const;
    Module *findModule(NameKeyType) const;

    const Coord3D *getPosition() const
    {
        return &m_position;
    }
    Object *nearest004182A0();
};

class Player
{
  public:
    int iterateObjects(void (*)(Object *, void *), void *) const;
};

class PlayerList
{
  public:
    char m_00[12];
    Object *m_local;
};
extern PlayerList *ThePlayerList;

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
};
extern Eva *TheEva;

class Radar
{
  public:
    void createEvent(const Coord3D *, RadarEventType, float);
};
extern Radar *TheRadar;

class NameKeyGenerator
{
  public:
    NameKeyType nameToKey(const char *);
};
extern NameKeyGenerator *TheNameKeyGenerator;

class Module
{
  public:
    char m_00[0x18];
    int m_18;
};

class Rva0036ff70Module
{
  public:
    int query(int (*)(void *, void *), void *);
};

int mark00410C90(void *, void *);

class Drawable
{
  public:
    void *m_00;
    ThingTemplate *m_template;
    char m_08[0xfc - 8];
    Object *m_object;
    char m_100[0x10];
    unsigned m_status;

    void notify00419F00();

    const ThingTemplate *finalTemplate() const
    {
        ThingTemplate *p = m_template;
        if (!p)
            return 0;
        return p->m_nextOverride ? (const ThingTemplate *)p->m_nextOverride->getFinalOverride() : p;
    }
};

class Rva00419E40Context
{
  public:
    Drawable *m_drawable;
    unsigned m_field04;
};

int bfmeDrawableFilter00419E40(Object *, Rva00419E40Context *);

void Drawable::notify00419F00()
{
    const ThingTemplate *t = finalTemplate();
    Object *object = m_object;
    Object *local = ThePlayerList ? ThePlayerList->m_local : 0;

    if (t && object && local && TheGameLogic && TheGameLogic->m_frame > 5 &&
        object->query(local, 1))
    {

        if (!(object->m_privateStatus & 1) && t->bfmeTemplatePredicate() && t->m_45c != -1 &&
            !t->isKindOf(K47))
        {
            Player *p = object->getControllingPlayer();
            if (p)
            {
                Rva00419E40Context context;
                unsigned message = t->m_45c;
                context.m_drawable = this;
                context.m_field04 = message;

                if (p->iterateObjects((void (*)(Object *, void *))bfmeDrawableFilter00419E40,
                                      &context) == 1)
                {
                    Object *nearby = object->nearest004182A0();
                    if (nearby)
                    {
                        EvaMessage message = (EvaMessage)t->m_45c;
                        if (TheEva->setShouldPlay(message, nearby->getPosition()))
                        {
                            TheRadar->createEvent(object->getPosition(), RADAR10, 4.0f);
                        }
                    }
                }
            }
        }
        if (t->isKindOf(K7) && !(m_status & 0x40))
        {
            static NameKeyType memberKey = TheNameKeyGenerator->nameToKey("CastleMemberBehavior");

            Module *member = object->findModule(memberKey);
            if (!member)
                return;

            int castleID = member->m_18;
            Object *castle = TheGameLogic->findObjectByID(castleID);
            if (!castle)
                return;

            Drawable *d = castle->getDrawable();
            if (!d)
                return;

            if (!(d->m_status & 0x40))
            {
                Object *nearby = object->nearest004182A0();
                if (nearby && TheEva->setShouldPlay(EVA8, nearby->getPosition()))
                {
                    TheRadar->createEvent(object->getPosition(), RADAR10, 4.0f);
                }
            }
            static NameKeyType castleKey = TheNameKeyGenerator->nameToKey("CastleBehavior");

            Module *behavior = castle->findModule(castleKey);
            if (!behavior)
            {
                d->m_status |= 0x40;
                return;
            }
            ((Rva0036ff70Module *)behavior)->query(mark00410C90, 0);
        }
    }
}

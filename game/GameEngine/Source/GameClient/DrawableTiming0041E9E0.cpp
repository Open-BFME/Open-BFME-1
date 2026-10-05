// Retail RVA 0x0041E9E0, 391 bytes. Called by the reaction at 0x0041EBD0.
// The original method name is unproved. The receiver has Drawable's witnessed
// Object pointer at +0xFC; returned objects expose Drawable through slot +0x28.
// Template +0x400 is passed as a float radius. +0x438 contributes to +0x310's
// deadline. These BFME-only fields have no name-oracle witness.
// Filter vtables are 0x01097144 (player payload at +8) and 0x010C995C.
// The iterator owns a five-word vector/cursor/refcount block; native STLport
// cleanup and lexical filter lifetimes reproduce retail's EH state sequence.
// Coord3D is forward-declared with the struct ABI used by this pinned callee.
// stlport
#define _STLP_USE_STATIC_LIB 1
#define _STLP_NO_EXCEPTIONS 1
#define BFME_STLP_NODE_ALLOC 1
#define __PLACEMENT_VEC_NEW_INLINE
#include <vector>
class Player;
class Overridable
{
  public:
    const Overridable *getFinalOverride() const;
};
class DrawableTiming0041E9E0;
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
    virtual DrawableTiming0041E9E0 *s28();
    Player *getControllingPlayer() const;
};
class PartitionFilter
{
  public:
    PartitionFilter() : m_next(0)
    {
    }
    virtual ~PartitionFilter()
    {
    }
    virtual bool allow(Object *) = 0;
    virtual int getPlayerMask();
    PartitionFilter *link(PartitionFilter *);
    PartitionFilter *m_next;
};
class PlayerFilter0041E9E0 : public PartitionFilter
{
  public:
    PlayerFilter0041E9E0(Player *p) : m_08(p)
    {
    }
    virtual ~PlayerFilter0041E9E0()
    {
    }
    virtual bool allow(Object *);
    virtual int getPlayerMask();
    Player *m_08;
};
class RootFilter0041E9E0 : public PartitionFilter
{
  public:
    RootFilter0041E9E0()
    {
    }
    virtual ~RootFilter0041E9E0()
    {
    }
    virtual bool allow(Object *);
};
struct Entry0041E9E0
{
    Object *object;
    unsigned m_04;
};
struct Data0041E9E0
{
    std::vector<Entry0041E9E0> entries;
    Entry0041E9E0 *current;
    int references;
};
struct BfmeWideResult
{
    Data0041E9E0 *value;
    BfmeWideResult();
    BfmeWideResult(const BfmeWideResult &);
    ~BfmeWideResult()
    {
        if (--value->references == 0)
            delete value;
    }
    Object *next()
    {
        if (value->current == value->entries.end())
            return 0;
        return (value->current++)->object;
    }
};
class BfmeWideForwardC
{
  public:
    BfmeWideResult bfmeForwardWideC(int, int, int, int, int);
};
class PartitionManager;
extern PartitionManager *ThePartitionManager;

class GameLogic
{
  public:
    char m_00[0x3c];
    unsigned m_frame;
};
extern GameLogic *TheGameLogic;
struct Coord3D;
class BFMERopeDrawable
{
  public:
    const Coord3D *getPosition() const;
};
class DrawableTiming0041E9E0
{
  public:
    char m_00[4];
    Overridable *m_04;
    char m_08[0xfc - 8];
    Object *m_object;
    char m_100[0x310 - 0x100];
    unsigned m_310;
    void update();
    const Overridable *finalTemplate() const
    {
        const Overridable *p = m_04;
        if (!p)
            return 0;
        const Overridable *n = *(const Overridable **)((char *)p + 4);
        return n ? n->getFinalOverride() : p;
    }
};
void DrawableTiming0041E9E0::update()
{
    if (m_object)
    {
        Player *player = m_object->getControllingPlayer();
        const Overridable *t = finalTemplate();
        if (player && t)
        {
            PlayerFilter0041E9E0 f1(player);
            RootFilter0041E9E0 f2;
            f1.link(&f2);
            float radius = *(float *)((char *)t + 0x400);
            BfmeWideResult iterator = (*reinterpret_cast<BfmeWideForwardC **>(&ThePartitionManager))->bfmeForwardWideC(
                (int)((BFMERopeDrawable *)this)->getPosition(),
                *(int *)&radius, 1, (int)&f1, 0);
            Object *obj;
            while ((obj = iterator.next()) != 0)
            {
                DrawableTiming0041E9E0 *d = obj->s28();
                if (d)
                {
                    const Overridable *t2 = d->finalTemplate();
                    if (t2 && TheGameLogic)
                        d->m_310 = *(unsigned *)((char *)t2 + 0x438) + TheGameLogic->m_frame;
                }
            }
        }
    }
}

// ?onEnter@AIFollowPathAsTeamState@@UAE?AW4StateReturnType@@XZ
// partial score=0.45 date=2026-09-20
// cl: /DNDEBUG /MD /EHsc
#include <math.h>

typedef bool Bool;
enum StateReturnType { STATE_FAILURE = -2 };
struct Coord3D { float x, y, z; };

extern unsigned char Glo012F0239;
extern void *TheCRCParameterCheck;
extern float BfmeZeroRange;
extern float g_bfmePathExtraDistance;
void __cdecl _bfmeRetailCritterDesyncLog(void *, const char *, ...);

class Rva0016FFD0PathOwner
{
public:
    Coord3D *getPoint(int index);
};

class Rva0026FE90DwordSlot
{
public:
    void set(int value);
};

class BfmePath
{
public:
    unsigned char m_unmodelled00[0x44];
    Coord3D *m_begin;
    Coord3D *m_end;
};

class BfmeFollowAI
{
public:
    unsigned char m_unmodelled000[0x194];
    int m_rva194;
    unsigned char m_unmodelled198[8];
    int m_rva1A0;

    Coord3D *currentPosition()
    {
        typedef Coord3D *(__fastcall *Proc)(BfmeFollowAI *, void *);
        return ((Proc)(*(void ***)this)[128])(this, 0);
    }

    Coord3D *getPoint(int index)
    {
        return ((Rva0016FFD0PathOwner *)this)->getPoint(index);
    }

    void setPathDistance(float value)
    {
        union { float f; int i; } bits;
        bits.f = value;
        ((Rva0026FE90DwordSlot *)this)->set(bits.i);
    }
};

class BfmeObject
{
public:
    unsigned char m_unmodelled000[0x38];
    Coord3D m_position;
    unsigned char m_unmodelled044[0x204 - 0x44];
    BfmeFollowAI *m_ai;
};

class BfmeStateMachine
{
public:
    unsigned char m_unmodelled00[0x10];
    BfmeObject *m_owner;
};

class BfmeAttackMoveMachine
{
public:
    void resetForFollow()
    {
        typedef void (__fastcall *NoArg)(BfmeAttackMoveMachine *, void *);
        typedef void (__fastcall *OneArg)(BfmeAttackMoveMachine *, void *, int);
        ( (NoArg)(*(void ***)this)[5] )(this, 0);
        ( (OneArg)(*(void ***)this)[8] )(this, 0, 0);
    }
};

class AIInternalMoveToState
{
public:
    virtual ~AIInternalMoveToState();
    virtual void crc();
    virtual void xfer();
    virtual void loadPostProcess();
    virtual StateReturnType onEnter();

protected:
    unsigned char m_unmodelled04[0x18];
    BfmeStateMachine *m_machine;
    Coord3D m_goalPosition;
    unsigned char m_unmodelled2C[0x4c - 0x2c];
    Bool m_adjustDestination;
};

class AIFollowPathAsTeamState : public AIInternalMoveToState
{
public:
    virtual StateReturnType onEnter();

private:
    int m_pathIndex;
    int m_retryCount;
    Bool m_rva58;
    Bool m_rva59;
    Bool m_rva5A;
    Bool m_rva5B;
    Coord3D *m_currentPosition;
    BfmeAttackMoveMachine *m_attackMoveMachine;
    int m_rva64;
    Bool m_rva68;
};

static int pathCount(const BfmePath *path)
{
    return (int)(path->m_end - path->m_begin);
}

StateReturnType AIFollowPathAsTeamState::onEnter()
{
    BfmeObject *owner = m_machine->m_owner;
    BfmeAttackMoveMachine *attackMoveMachine = m_attackMoveMachine;
    BfmeFollowAI *ai = owner->m_ai;
    m_pathIndex = 0;

    if (attackMoveMachine)
        attackMoveMachine->resetForFollow();

    m_currentPosition = ai->currentPosition();
    m_rva68 = false;
    m_rva5B = false;
    BfmePath *path = *(BfmePath **)((char *)ai + 0x30);

    Coord3D *point = (m_pathIndex >= 0 && m_pathIndex < pathCount(path))
        ? path->m_begin + m_pathIndex : 0;
    if (!point)
        return STATE_FAILURE;

    ++m_pathIndex;
    m_rva64 = ai->m_rva1A0;
    m_goalPosition = *point;

    Coord3D *next = (m_pathIndex >= 0 && m_pathIndex < pathCount(path))
        ? path->m_begin + m_pathIndex : 0;
    m_rva58 = true;

    while (next) {
        Coord3D toGoal;
        Coord3D toNext;
        toGoal.x = m_goalPosition.x - owner->m_position.x;
        toGoal.y = m_goalPosition.y - owner->m_position.y;
        toNext.x = next->x - m_goalPosition.x;
        toNext.y = next->y - m_goalPosition.y;
        if (toGoal.x * toNext.x + toGoal.y * toNext.y <= BfmeZeroRange)
            break;
        ++m_pathIndex;
        m_goalPosition = *next;
        next = (m_pathIndex + 1 >= 0 && m_pathIndex + 1 < pathCount(path))
            ? path->m_begin + m_pathIndex + 1 : 0;
    }

    ai->m_rva194 = m_pathIndex;
    if (Glo012F0239 && TheCRCParameterCheck)
        _bfmeRetailCritterDesyncLog(TheCRCParameterCheck,
            "CritterDesync: setAdjustDestination(nextPos=%s) 44", next ? "TRUE" : "FALSE");

    m_adjustDestination = next != 0;
    m_rva58 = true;
    StateReturnType result = AIInternalMoveToState::onEnter();

    if (next) {
        float dx = next->x - point->x;
        float dy = next->y - point->y;
        float distance = (float)sqrt(dx * dx + dy * dy);
        if (ai->getPoint(m_pathIndex + 2))
            distance += g_bfmePathExtraDistance;
        ai->setPathDistance(distance);
        if (Glo012F0239 && TheCRCParameterCheck)
            _bfmeRetailCritterDesyncLog(TheCRCParameterCheck,
                "CritterDesync: setAdjustDestination(FALSE) 45");
        m_adjustDestination = false;
    } else {
        if (Glo012F0239 && TheCRCParameterCheck)
            _bfmeRetailCritterDesyncLog(TheCRCParameterCheck,
                "CritterDesync: setAdjustDestination(m_adjustFinal=%s) 46",
                m_rva58 ? "TRUE" : "FALSE");
        m_adjustDestination = m_rva58;
        ai->setPathDistance(0);
    }
    return result;
}

// cl: /O2 /Ob1 /DNDEBUG /MD /EHsc
// Retail 00176580..001766A5: ECX receiver, no arguments, EAX state result.
// Layout/callee witnesses: docs/analysis/0x00172600.md, Neighbour notes.
// Method identity is unproved; the address is retained deliberately.
extern void j_0000432c();
extern void j_0000e570();
extern void j_00006eec();
extern void j_00031a7f();
extern void j_0002e85c();
extern void j_000065e1();
extern void j_0003a17a();
struct Position00176580 { float x, y, z; };
struct Owner00176580;
struct Weapon00176580 {
    bool inRange(const Owner00176580* a, const Owner00176580* b, int c) const {
        typedef bool (Weapon00176580::*Call)(const Owner00176580*, const Owner00176580*, int) const;
        union { void* raw; Call method; } u; u.raw=(void*)j_0002e85c;
        return (this->*u.method)(a,b,c);
    }
};
struct Flag00176580 { bool query() const {
    typedef bool (Flag00176580::*Call)() const;
    union { void* raw; Call method; } u; u.raw=(void*)j_00006eec;
    return (this->*u.method)();
} };
struct Update00176580 { void destroyPath() {
    typedef void (Update00176580::*Call)();
    union { void* raw; Call method; } u; u.raw=(void*)j_000065e1;
    (this->*u.method)();
} };
struct Owner00176580 {
    unsigned char pad000[0x38];
    Position00176580 position;
    unsigned char pad044[0x30];
    unsigned int id;
    unsigned char pad078[0x18c];
    Update00176580* ai;
    Flag00176580* flag208;
    Weapon00176580* currentWeapon(void* slot) {
        typedef Weapon00176580* (Owner00176580::*Call)(void*);
        union { void* raw; Call method; } u; u.raw=(void*)j_00031a7f;
        return (this->*u.method)(slot);
    }
};
struct Machine00176580 {
    unsigned char pad000[0x10];
    Owner00176580* owner;
    bool goalDestroyed() const {
        typedef bool (Machine00176580::*Call)() const;
        union { void* raw; Call method; } u; u.raw=(void*)j_0000432c;
        return (this->*u.method)();
    }
    Owner00176580* goal() {
        typedef Owner00176580* (Machine00176580::*Call)();
        union { void* raw; Call method; } u; u.raw=(void*)j_0000e570;
        return (this->*u.method)();
    }
};
enum StateReturnType { STATE_CONTINUE=0, STATE_SUCCESS=-1, STATE_FAILURE=-2 };
class AIInternalMoveToState { public: virtual StateReturnType onEnter(); };
class RangeCheckedMove00176580 {
public:
    virtual void slot00(); virtual void slot04(); virtual void slot08();
    virtual void slot0c(); virtual void slot10(); virtual void slot14();
    virtual void slot18(); virtual void slot1c(); virtual void slot20();
    virtual void slot24(); virtual void slot28(); virtual void slot2c();
    virtual void slot30(); virtual void slot34(); virtual void slot38();
    virtual void slot3c(); virtual void slot40();
    virtual bool computePath();
    unsigned char pad004[0x18];
    Machine00176580* machine;
    unsigned char pad020[0x2c];
    bool adjustsDestination;
    unsigned char pad04d[3];
    int field050;
    Position00176580 position054;
    unsigned char pad060[8];
    unsigned int field068;
    int enterHub() { return ((AIInternalMoveToState*)this)->AIInternalMoveToState::onEnter(); }
    int enter();
};
extern bool Glo012F0239;
class CRCParameterCheck;
extern CRCParameterCheck* TheCRCParameterCheck;
typedef void (__cdecl *Log00176580)(CRCParameterCheck*, const char*, ...);
#define log00176580 ((Log00176580)j_0003a17a)

int RangeCheckedMove00176580::enter()
{
    Owner00176580* source = machine->owner;
    if (machine->goalDestroyed()) return -2;
    if (Glo012F0239 && TheCRCParameterCheck)
        log00176580(TheCRCParameterCheck, "CritterDesync: setAdjustDestination(FALSE) 28");
    adjustsDestination = false;
    field050 = 0;
    Owner00176580* target = machine->goal();
    if (target) {
        field068 = target->id;
        if (!target->flag208 || !target->flag208->query()) {
            Weapon00176580* weapon = source->currentWeapon(0);
            if (weapon) {
                if (weapon->inRange(source, target, 0)) return -1;
                position054 = target->position;
                source->ai->destroyPath();
                if (Glo012F0239 && TheCRCParameterCheck)
                    log00176580(TheCRCParameterCheck, "CritterDesync: ComputePath16");
                if (!computePath()) return -1;
                int result = enterHub();
                if (Glo012F0239 && TheCRCParameterCheck)
                    log00176580(TheCRCParameterCheck, "CritterDesync: setAdjustDestination(TRUE) 29");
                adjustsDestination = true;
                return result;
            }
        }
    }
    return -2;
}

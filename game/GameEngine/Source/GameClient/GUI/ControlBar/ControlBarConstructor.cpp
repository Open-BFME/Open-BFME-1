// readable body of 0x0049D660 (was game/gen_asm/d_00495de0.asm dump ?d_0049d660@@YAXXZ)
// cl: /DNDEBUG /DWIN32 /MD /EHsc /O2 /Ob2
// ??0ControlBar@@QAE@XZ -- ControlBar constructor, 787 B.
//
// Identity evidence: matched callers ?createReplayControl@InGameUI@@IAEXXZ and
// ?recreateControlBar@InGameUI@@UAEXXZ name this ctor; the body installs
// vtable 0x010FB888 (tools/vtable_lookup.py: ControlBar). Base-class ctor
// callee is ??0SubsystemInterface@@QAE@XZ (0x009A1A30); the tail calls
// operator new (0x00881F30) + ??0Gen_004B1670@@QAE@XZ (via thunk 0x0002307E)
// and resetContainData via thunk 0x0001A73F, matching the ZH twin
// ControlBar::ControlBar() store-for-store in
// inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source/
// GameClient/GUI/ControlBar/ControlBar.cpp (line 865), at BFME offsets.
//
// Member names keep their retail offsets (layout of this synthetic view was
// read off the retail stores; name_oracle has no witness for most slots).
// Two levers this body needed against MSVC 7.1 /O2:
//  - the m_contextParent zeroing must be a single for-loop over the array
//    (if-converted to ten straight stores); spelling them as ten individual
//    stores re-hoists the loop constants (blocker=codegen-order, see
//    targets/game/reverse/re_attempts.log).
//  - the new-expression tail must go through a local pointer so the member
//    store precedes the dispatch receiver build.

typedef unsigned int UnsignedInt;
inline UnsignedInt GameMakeColor(int r, int g, int b, int a) { return (a << 24) | (r << 16) | (g << 8) | b; }

class SubsystemInterface
{
public:
    SubsystemInterface(void);
    virtual ~SubsystemInterface(void);
private:
    int m_name;
};

class Gen_004B1670
{
public:
    Gen_004B1670(void);
    virtual ~Gen_004B1670(void);
    virtual void init(void);
private:
    char m_unreconstructed[0x4c];
};

template <class T> class OwnedPointer
{
public:
    OwnedPointer(void) : m_pointer(0) {}
    ~OwnedPointer(void);
    OwnedPointer &operator=(T *pointer) { m_pointer = pointer; return *this; }
    T *operator->(void) const { return m_pointer; }
private:
    T *m_pointer;
};

template <class T> class WeakPointer
{
public:
    WeakPointer(void) : m_pointer(0) {}
    WeakPointer &operator=(T *pointer) { m_pointer = pointer; return *this; }
    T *operator->(void) const { return m_pointer; }
private:
    T *m_pointer;
};

class ControlBar : public SubsystemInterface
{
public:
    ControlBar(void);
    virtual ~ControlBar(void);
    virtual void init(void);
    virtual void postProcessLoad(void);
    virtual void reset(void);
    virtual void update(void);
    virtual void draw(void);
    virtual void slot7(void);
    virtual void slot8(int);

protected:
    void resetContainData(void);

private:
    int f008, f00c, f010, f014;
    int f018, f01c;
    char pad020[0x24 - 0x20];
    unsigned char f024;
    char pad025[0x28 - 0x25];
    void *f028, *f02c, *f030;
    int a034[10];
    int f05c, f060, f064;
    float f068;
    int f06c, f070, f074, f078;
    char pad07c[0x90 - 0x7c];
    int f090, f094, f098;
    int a09c[12];
    int a0cc[5];
    int a0e0[5];
    char pad0f4[0xf8 - 0xf4];
    int f0f8, f0fc;
    int a100[20];
    int a150[20];
    int a1a0[20];
    int a1f0[20];
    unsigned char f240;
    char pad241[0x244 - 0x241];
    void *f244, *f248, *f24c, *f250, *f254, *f258, *f25c, *f260, *f264, *f268;
    UnsignedInt f26c;
    unsigned char f270;
    char pad271[0x274 - 0x271];
    void *f274, *f278;
    unsigned char f27c;
    char pad27d[0x280 - 0x27d];
    UnsignedInt f280, f284, f288, f28c, f290, f294;
    int f298, f29c;
    int f2a0, f2a4, f2a8, f2ac, f2b0, f2b4;
    char pad2b8[0x2bc - 0x2b8];
    int f2bc, f2c0, f2c4;
    unsigned char f2c8;
    char pad2c9[0x2e0 - 0x2c9];
    unsigned char f2e0;
    char pad2e1[0x2e4 - 0x2e1];
    int f2e4, f2e8, f2ec;
    WeakPointer<Gen_004B1670> f2f0;
    OwnedPointer<int> f2f4;
};

ControlBar::ControlBar(void)
{
    f028 = 0;
    f02c = 0;
    f030 = 0;
    f270 = 0;
    f274 = 0;
    f278 = 0;
    f27c = 0;
    f258 = 0;
    f254 = 0;
    f248 = 0;
    f244 = 0;
    f260 = 0;
    f25c = 0;
    f250 = 0;
    f24c = 0;
    f264 = 0;
    f268 = 0;
    int i;
    for (i = 0; i < 20; ++i)
        a1f0[i] = 0;
    f060 = 0;
    f01c = 0;
    f018 = 0;
    f2c8 = 0;
    f29c = 0;
    f298 = 0;
    f024 = 0;
    f26c = GameMakeColor(0, 0, 0, 100);
    f294 = GameMakeColor(0, 0, 0, 100);
    for (i = 0; i < 10; ++i)
        a034[i] = 0;
    for (i = 0; i < 20; ++i) {
        a100[i] = 0;
        a1a0[i] = 0;
        a150[i] = 0;
    }
    for (i = 0; i < 12; ++i)
        a09c[i] = 0;
    for (i = 0; i < 5; ++i) {
        a0cc[i] = 0;
        a0e0[i] = 0;
    }
    f0fc = 0;
    f0f8 = 0;
    f098 = 0;
    f074 = 0;
    f078 = 0;
    f090 = 0;
    f094 = 0;
    f05c = 0;
    f060 = 0;
    f064 = 0;
    f068 = -1.0f;
    f06c = 0;
    resetContainData();
    f070 = 0;
    f008 = 0;
    f00c = 0;
    f014 = 0;
    f010 = 0;
    f2a0 = 0;
    f2a4 = 0;
    f2a8 = 0;
    f2ac = 0;
    f2b0 = 0;
    f2b4 = 0;
    f2c0 = 0;
    f2c4 = 0;
    f2bc = 0;
    f240 = 0;
    f280 = 0xffffff;
    f284 = 0xffffff;
    f288 = 0xffffff;
    f28c = 0xffffff;
    f290 = 0xffffff;
    f2e0 = 0;
    f2e4 = 0;
    f2e8 = 0;
    f2ec = 0;
    Gen_004B1670 *p = new Gen_004B1670;
    f2f0 = p;
    p->init();
}

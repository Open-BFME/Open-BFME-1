// cl: /O2 /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc
class Rva003BB970Manager
{
public:
    virtual void m0();
    virtual void m1();
    virtual void m2();
    virtual void m3();
    virtual void m4();
    virtual void m5();
    virtual void m6();
    virtual void m7();
    virtual void m8();
    virtual void m9();
    virtual void m10();
    virtual void m11();
    virtual void m12();
    virtual void m13();
    virtual void m14();
    virtual void m15();
    virtual void m16();
    virtual void m17();
    virtual void m18();
    virtual void m19();
    virtual void m20();
    virtual void m21();
    virtual void m22();
    virtual void m23();
    virtual void dispatch(void *, float, int);
};
// Retail global at 0x012F7048 is Rva006092D0State *
// g_rva012F7048LivingWorld (defined once in LivingWorld.cpp).  This TU calls it
// through the local Rva003BB970Manager view, so the view stays and the global
// uses the canonical spelling.
class Rva006092D0State;
extern Rva006092D0State *g_rva012F7048LivingWorld;

static inline Rva003BB970Manager *localGlo012F7048(void)
{
    return reinterpret_cast<Rva003BB970Manager *>(g_rva012F7048LivingWorld);
}
extern const float g_01075954;
class Rva003BB970Input
{
public:
    unsigned char emit(void);
    char m_before[0x0c];
    char m_position[0x0c];
    volatile float m_value;
    int m_count;
};
unsigned char Rva003BB970Input::emit(void)
{
    Rva003BB970Manager *state = localGlo012F7048();
    state->dispatch(m_position, m_value * g_01075954, m_count);
    return 1;
}

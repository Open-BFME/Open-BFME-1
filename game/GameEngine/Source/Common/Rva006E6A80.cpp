// cl: /DNDEBUG /MD /EHsc
// Retail RVA 0x006E6A80, 309 bytes: slot 5 (the SubsystemInterface update
// slot) of the Gen006E2310 table at VA 0x0111E250, through ILT 0x0001511D.
// Slots 2 and 3 of that table are SubsystemInterface::loadIniFilesFromLegend
// and postProcessLoad.  The class is the owner of Rva006E2540::update (its
// field layout is the one landed in Rva006E2540.cpp), which this body
// tail-calls; neither the class nor this override has a proven name.

struct Triple006E2540 { float x, y, z; void set(float a, float b, float c) { x = a; y = b; z = c; } };
class Open2Triple5;
class Gen_0039B020 { public: unsigned char bfmeFlag() const; };
extern Gen_0039B020 *g_012F0FE0;
class Sink006E2540
{
public:
    void write(const Open2Triple5 *);
    void adjust(Triple006E2540 *, bool);
};
extern Sink006E2540 *g_012F8058;
struct State006E2540 { int pad; unsigned color; };
extern State006E2540 *g_01306EEC;
class Client006E2540
{
public:
    virtual void p00(); virtual void p04(); virtual void p08(); virtual void p0c();
    virtual void p10(); virtual void p14(); virtual void p18(); virtual void p1c();
    virtual void p20(); virtual void p24(); virtual void p28(); virtual void p2c();
    virtual void p30(); virtual void p34(); virtual void p38(); virtual void p3c();
    virtual void p40(); virtual void p44(); virtual void p48(); virtual void p4c();
    virtual void p50(); virtual void p54(); virtual void p58(); virtual void p5c();
    virtual void p60(); virtual void p64(); virtual unsigned slot68();
};
// Retail 0x012F1464 is recorded as ClientAt012F1464 (dir32_addresses.csv).
// This TU's vtable-ABI view of it is Client006E2540; the slot68() virtual
// slot is identical, so the cast is free and bytes match.
class Client0009A580;
extern Client0009A580 *ClientAt012F1464;
static inline Client006E2540 *clientAt() { return (Client006E2540 *)ClientAt012F1464; }

class Rva006E2540
{
public:
    virtual ~Rva006E2540();
    virtual void slot04();
    virtual bool slot08();
    virtual void slot0c();
    virtual void slot10();
    virtual void rva006E6A80();
    virtual void slot18();
    virtual void slot1c();
    virtual void slot20(unsigned);
    virtual void slot24();
    void update();

    char pad04[0x28];
    Triple006E2540 f2c;
    char pad38[0x14];
    bool f4c;
    char pad4d[0x5f];
    int fac;
    int fb0, fb4;
    bool fb8;
    char padb9[3];
    int fbc;
    float fc0;
    Triple006E2540 fc4, fd0, fdc;
    unsigned fe8;
    const void *fec;
    unsigned m_lastUpdateFrame;
    int ff4;
};

// ?rva006E6A80@Rva006E2540@@UAEXXZ
void Rva006E2540::rva006E6A80()
{
    unsigned frame = clientAt()->slot68();
    bool unchanged = false;
    if (m_lastUpdateFrame == frame)
        unchanged = true;
    m_lastUpdateFrame = frame;
    if (unchanged)
        return;

    int mode = *(const int *)((const char *)g_012F0FE0 + 0xc);
    if (mode == 1 || mode == 2)
    {
        if (fac != 1 && fac != 2)
        {
            slot24();
            fb0 = 1;
            fac = mode;
        }
    }
    else if (fac == 1 || fac == 2)
    {
        fb0 = 3;
        fac = mode;
    }

    unsigned char on = g_012F0FE0 ? g_012F0FE0->bfmeFlag() : 0;
    if (!on && fb8)
    {
        fb8 = false;
        fbc = 0;
        fc0 = 0;
        ff4 = 0;
        fc4.set(0, 0, 0);
        if (f4c)
        {
            g_012F8058->write((const Open2Triple5 *)&fd0);
            if (g_01306EEC)
                g_01306EEC->color = fe8;
        }
        g_012F8058->adjust(&fdc, true);
        fd0.x = 0;
        fd0.y = 0;
        fd0.z = 0;
        fdc.set(0, 0, 0);
    }
    update();
}

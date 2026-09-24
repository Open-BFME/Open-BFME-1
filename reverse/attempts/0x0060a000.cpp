// ??0Rva006092D0State@@QAE@XZ
// partial score=0.806 date=2026-09-24
// ??0Rva006092D0State@@QAE@XZ
// Partial reconstruction only. Retail 0x0060A000 is 237 bytes; this compiles
// to 237 bytes with 46 non-relocation differences and one misaligned relocation.
// The matched 0x00609E30 destructor and 0x006092D0 mode method, plus vtable
// 0x01115AD0, support the address-derived owner. The class's virtual interface
// below is deliberately incomplete and must be checked before a strict claim.
// Remaining shape: retail saves ESI/EDI before clearing EBX and installing the
// vtable; this compiler build moves those saves/clear around the initializers.
// At +0xA1 retail passes the copy iterator in ECX and tag address in EDX,
// while this build exchanges those registers. The curve stores from +0x47
// through +0x85 otherwise line up after a volatile finish reload and barrier.
// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB
// stlport
#define _STLP_NO_EXCEPTIONS 1
extern "C" void _ReadWriteBarrier(void);
#pragma intrinsic(_ReadWriteBarrier)

struct GarrisonContain
{
    struct StationPointData { float m_key; int m_value[3]; };
};

namespace _STL
{
    struct random_access_iterator_tag {};
    template <class InputIterator, class OutputIterator, class Distance>
    __declspec(nothrow) OutputIterator __copy(InputIterator first, InputIterator last,
        OutputIterator result, const random_access_iterator_tag &, Distance *);
    template <>
    GarrisonContain::StationPointData *__copy<
        GarrisonContain::StationPointData *,
        GarrisonContain::StationPointData *, int>(
        GarrisonContain::StationPointData *, GarrisonContain::StationPointData *,
        GarrisonContain::StationPointData *, const random_access_iterator_tag &, int *);
}

class Rva0006A3C0
{
public:
    Rva0006A3C0() : m_field0(0), m_field4(0), m_start(0), m_finish(0), m_end(0)
    { _ReadWriteBarrier(); m_current = *(GarrisonContain::StationPointData * volatile *)&m_finish; m_extra4 = 0; m_extra3 = 0; m_extra2 = 0; m_extra1 = 0; }
    ~Rva0006A3C0();
    int m_field0;
    int m_field4;
    GarrisonContain::StationPointData *m_start;
    GarrisonContain::StationPointData *m_finish;
    GarrisonContain::StationPointData *m_end;
    int m_field14;
    GarrisonContain::StationPointData *m_current;
    int m_extra1;
    int m_extra2;
    int m_extra3;
    int m_extra4;
};

class Rva0006AB10Curve
{
public:
    void set(float time, float value, int inTangent, int outTangent);
};

class BfmeLivingWorldManager
{
public:
    void rva006157c0();
};
class Gen_00609320 {};
extern BfmeLivingWorldManager *g_bfmeGameCW;
extern Gen_00609320 *g_bfmeStateDF;

class Rva006092D0State
{
public:
    Rva006092D0State();
    virtual ~Rva006092D0State();
    virtual void slot00() = 0;
private:
    int m_mode;
    unsigned char m_flag08;
    unsigned char m_flag09;
    unsigned char m_flag0a;
    unsigned char m_flag0b;
    int m_field0c;
    int m_field10;
    unsigned char m_flag14;
    unsigned char m_flag15;
    unsigned char m_pad16[2];
    Rva0006A3C0 m_curve;
    int m_tail44;
    int m_tail48;
    int m_tail4c;
    int m_tail50;
    int m_tail54;
    int m_tail58;
    int m_tail5c;
    unsigned char m_flag60;
    unsigned char m_pad61[3];
    int m_tail64;
    int m_tail68;
    int m_tail6c;
};

Rva006092D0State::Rva006092D0State() :
    m_mode(0), m_flag08(0), m_flag09(0), m_flag0a(0), m_flag0b(0),
    m_field0c(0), m_field10(0), m_flag14(0), m_flag15(0)
{
    m_tail44 = 0;
    m_tail48 = 0;
    m_tail4c = 0;
    m_tail50 = 0;
    m_tail54 = 0;
    m_tail58 = 0;
    m_tail5c = 0;
    m_flag60 = 0;
    m_tail64 = 0;
    m_tail68 = 0;
    m_tail6c = 0;
    g_bfmeStateDF = (Gen_00609320 *)this;
    if (g_bfmeGameCW) g_bfmeGameCW->rva006157c0();
    _STL::random_access_iterator_tag tag;
    int *none = 0;
    m_curve.m_finish = _STL::__copy(m_curve.m_finish, m_curve.m_finish,
        m_curve.m_start, tag, none);
    Rva0006AB10Curve *curve = (Rva0006AB10Curve *)&m_curve;
    curve->set(0.0f, 0.0f, 0, 0);
    curve->set(1.0f, 1.0f, 0, 0);
}

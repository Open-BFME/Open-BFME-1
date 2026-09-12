// Open-BFME5: HorseHordeContainModuleData constructor reconstruction.
// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /D_STLP_USE_STATIC_LIB
// stlport

#include <list>
#include <set>
#include <vector>

extern "C" void _ReadWriteBarrier(void);
#pragma intrinsic(_ReadWriteBarrier)

class BFMERetailAsciiString
{
public:
    BFMERetailAsciiString() : m_data(0) {}
    ~BFMERetailAsciiString() { releaseBuffer(); }
    void releaseBuffer();
    void set(const BFMERetailAsciiString &);
private:
    void *m_data;
};

#pragma comment(linker, "/alternatename:?set@BFMERetailAsciiString@@QAEXABV1@@Z=?set@?$StringBase@D@@QAEXABV1@@Z")

class AsciiString
{
public:
    AsciiString() : m_data(0) {}
    ~AsciiString() { ((BFMERetailAsciiString *)this)->releaseBuffer(); }
    AsciiString &operator=(const AsciiString &that)
    {
        ((BFMERetailAsciiString *)this)->set(*(const BFMERetailAsciiString *)&that);
        return *this;
    }
private:
    void *m_data;
};

class BfmeHordeContainSplitResultList
{
public:
    virtual void slot0();
    ~BfmeHordeContainSplitResultList();
};
#pragma comment(linker, "/alternatename:??1BfmeHordeContainSplitResultList@@QAE@XZ=?j_00017657@@YAXXZ")

class AudioEventRTS
{
public:
    ~AudioEventRTS();
private:
    unsigned char m_data[0x70];
};
#pragma comment(linker, "/alternatename:??1AudioEventRTS@@QAE@XZ=?j_00026f35@@YAXXZ")

class Rva002472D0AudioEntry
{
private:
    BFMERetailAsciiString m_00;
    BFMERetailAsciiString m_04;
    AudioEventRTS m_08;
    AudioEventRTS m_78;
};
class Rva002472D0TwoAsciiEntry
{
private:
    BFMERetailAsciiString m_00;
    BFMERetailAsciiString m_04;
};
class Rva002472D0OneAsciiEntry
{
private:
    BFMERetailAsciiString m_00;
};

struct Gen_t_002360c0_k4
{
    int m_00[1];
};
bool operator==(const Gen_t_002360c0_k4 &, const Gen_t_002360c0_k4 &);
bool operator<(const Gen_t_002360c0_k4 &, const Gen_t_002360c0_k4 &);
typedef _STL::_Rb_tree<Gen_t_002360c0_k4, Gen_t_002360c0_k4,
    _STL::_Identity<Gen_t_002360c0_k4>, _STL::less<Gen_t_002360c0_k4>,
    _STL::allocator<Gen_t_002360c0_k4> > Rva002472D0TreeK4;

// The constructor calls this shared ICF-folded base body through its named
// ILT.  The Horse identity is established by the factory/vtable path; this
// base spelling only selects the existing 0x3D055 constructor candidate.
class HordeGarrisonContainModuleDataBase
{
public:
    HordeGarrisonContainModuleDataBase();
    virtual ~HordeGarrisonContainModuleDataBase();
private:
    unsigned char m_004_to_223[0x220];
};
struct Rva002472D0Config
{
    unsigned int m_268;
    unsigned int m_26c;
    unsigned char m_270;
    unsigned char m_pad271[3];
    unsigned int m_274;
    unsigned int m_278;
    float m_27c;
    float m_280;
    float m_284;
    unsigned int m_288;

    Rva002472D0Config()
    {
        m_268 = 0;
        m_26c = 0;
        m_274 = 2;
        m_278 = 15;
        m_27c = 3.0f;
        m_280 = 5.0f;
        m_284 = 0.5f;
        m_288 = 0;
        m_270 = 1;
    }
};

typedef char Rva002472D0ConfigSizeCheck[(sizeof(Rva002472D0Config) == 0x24) ? 1 : -1];

struct Rva002472D0Pod298
{
    unsigned int m_298;
    unsigned int m_29c;
    unsigned int m_2a0;

    Rva002472D0Pod298()
    {
        m_298 = 0;
        m_29c = 0;
        m_2a0 = 0;
    }
};

struct Rva002472D0Tail
{
    volatile unsigned char m_2c8;
    unsigned char m_pad2c9[3];
    unsigned int m_2cc;
    volatile unsigned char m_2d0;
    unsigned char m_pad2d1[3];
    volatile unsigned int m_2d4;
    unsigned char m_2d8;
    unsigned char m_pad2d9[3];
    float m_2dc;
    float m_2e0;
    unsigned int m_2e4;
    unsigned char m_2e8;
    unsigned char m_pad2e9[3];
    unsigned int m_2ec;
    unsigned char m_2f0;
    unsigned char m_2f1;
    unsigned char m_2f2;
    unsigned char m_2f3;

    Rva002472D0Tail()
    {
        unsigned int minusOne = 0xffffffff;
        m_2cc = minusOne;
        m_2c8 = 0;
        _ReadWriteBarrier();
        m_2d0 = 0;
        m_2d4 = 0;
        _ReadWriteBarrier();
        m_2e4 = minusOne;
        m_2d8 = 1;
        m_2e8 = 0;
        m_2ec = 0;
        m_2f0 = 0;
        m_2f1 = 0;
        m_2f2 = 0;
        m_2dc = 0.4f;
        m_2e0 = 60.0f;
    }
};
typedef char Rva002472D0TailSizeCheck[(sizeof(Rva002472D0Tail) == 0x2c) ? 1 : -1];

class HorseHordeContainModuleData : public HordeGarrisonContainModuleDataBase
{
public:
    HorseHordeContainModuleData();
    virtual ~HorseHordeContainModuleData();
private:
    std::vector<BfmeHordeContainSplitResultList *> m_224;
    std::vector<Rva002472D0AudioEntry *> m_230;
    std::vector<Rva002472D0TwoAsciiEntry *> m_23c;
    AsciiString m_248;
    std::list<int> m_24c;
    Rva002472D0TreeK4 m_250;
    Rva002472D0TreeK4 m_25c;
    Rva002472D0Config m_config;
    std::vector<AsciiString> m_28c;
    Rva002472D0Pod298 m_pod298;
    std::vector<Rva002472D0OneAsciiEntry *> m_2a4;
    std::vector<AsciiString> m_2b0;
    std::vector<AsciiString> m_2bc;
    Rva002472D0Tail m_tail;
};
typedef char Rva002472D0SizeCheck[(sizeof(HorseHordeContainModuleData) == 0x2f4) ? 1 : -1];

HorseHordeContainModuleData::HorseHordeContainModuleData()
{
}

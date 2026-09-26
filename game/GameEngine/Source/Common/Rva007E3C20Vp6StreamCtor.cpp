// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc
// ??0Rva007E3C20Vp6Stream@@QAE@HH@Z
// Open-BFME: VP6 stream constructor, retail 0x007E3B40, 144 bytes.
//
// Identity: the body installs vtable 0x01128DA8 (pinned
// ??_7Rva007E3C20Vp6Stream@@6B@), the same vtable the landed destructor
// 0x007E3C20 stores; the field extent (+0x14..+0x60) and the +0x1C member
// match that destructor's layout. The only caller, 0x007E5080, reaches this
// body through ILT 0x0001A2FD. Base is the Gen_0081E480 class (ctor 0x0081E480,
// the lone EH unwind state); the +0x1C member is built by the zeroing
// constructor 0x007E3430 through ILT 0x0003B115.
//
// Shape: every member initialised in declaration order. MSVC hoists the three
// stores of 1 and keeps -1 in ECX across +0x48/+0x4C, which defers the SEH
// chain reload past them exactly as retail does; the reordered or volatile
// spellings of earlier attempts did not.

class Gen_0081E480
{
public:
    Gen_0081E480(int first, int second);
    virtual ~Gen_0081E480(void);
    int m_count; int m_first; int m_second; int m_flags;
};

// real, already-matched zeroing constructor (R2ZeroingConstructors.cpp)
class Rva007E3430
{
public:
    Rva007E3430(void);

private:
    int m_word0;
    int m_word1;
    int m_word2;
    int m_word3;
};

class Rva007E3C20Vp6Stream : public Gen_0081E480
{
public:
    Rva007E3C20Vp6Stream(int first, int second);
    virtual ~Rva007E3C20Vp6Stream(void);

private:
    void *m_at14;
    void *m_at18;
    Rva007E3430 m_parser;
    void *m_at2c;
    int m_at30;
    int m_at34;
    unsigned char m_at38;
    int m_at3c;
    int m_at40;
    int m_at44;
    int m_at48;
    int m_at4c;
    int m_at50;
    char *m_at54;
    int m_at58;
    int m_at5c;
    int m_at60;
};

Rva007E3C20Vp6Stream::Rva007E3C20Vp6Stream(int first, int second)
    : Gen_0081E480(first, second),
      m_at14(0),
      m_at18(0),
      m_at2c(0),
      m_at30(0),
      m_at34(0),
      m_at38(0),
      m_at3c(0),
      m_at40(0),
      m_at44(1),
      m_at48(-1),
      m_at4c(-1),
      m_at50(0),
      m_at54(0),
      m_at58(0),
      m_at5c(1),
      m_at60(1)
{
}

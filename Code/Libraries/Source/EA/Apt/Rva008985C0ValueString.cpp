// cl: /O2 /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc
// Probe symbol: ?getName@Rva8CD130Value@@QAEXPAVRva8CD130String@@@Z
// Retail RVA 0x008985C0, 1740 bytes. See ANALYSIS.md for all contracts.
// The existing address-derived pin is retained, not an original name claim.
// Required retail frame: EH registration (12), 0xBC local bytes (128-byte
// buffer + 15 four-byte full-expression string temporaries), saved ESI,
// and saved EDI only in the defined-value dispatch. Compiler emits the EH.

struct BfmeStringData3AF0
{
    unsigned short m_refCount;
    unsigned short m_length;
    unsigned short m_capacity;
    unsigned short m_flags;
};

struct BfmeStringPool3AF0
{
    void *m_unknown00;
    void (__cdecl *free)(void *);
};

extern BfmeStringData3AF0 g_bfmeDefaultString1284;
extern BfmeStringPool3AF0 *g_bfmeStringPool1284;
extern const float BfmeZeroRange;
extern double g_bfmeSubB3;

extern "C" int __cdecl sprintf(char *, const char *, ...);
extern "C" double __cdecl fmod(double, double);
#pragma intrinsic(fmod)

class BfmeStrVKI
{
public:
    BfmeStrVKI(const char *text) { bfmeSetVKI(text); }
    void __declspec(nothrow) bfmeSetVKI(const char *text);
    __forceinline ~BfmeStrVKI()
    {
        BfmeStringData3AF0 *old = m_data;
        if (--old->m_refCount == 0)
            g_bfmeStringPool1284->free(old);
    }
    BfmeStringData3AF0 *m_data;
};

class Rva8CD130String
{
public:
    __forceinline void clear()
    {
        BfmeStringData3AF0 *old = m_data;
        if (--old->m_refCount == 0)
            g_bfmeStringPool1284->free(old);
        m_data = &g_bfmeDefaultString1284;
        ++m_data->m_refCount;
    }
    __forceinline void assign(const Rva8CD130String &source)
    {
        ++source.m_data->m_refCount;
        BfmeStringData3AF0 *old = m_data;
        if (--old->m_refCount == 0)
            g_bfmeStringPool1284->free(old);
        m_data = source.m_data;
    }
    __forceinline Rva8CD130String &operator=(const BfmeStrVKI &source)
    {
        ++source.m_data->m_refCount;
        BfmeStringData3AF0 *old = m_data;
        if (--old->m_refCount == 0)
            g_bfmeStringPool1284->free(old);
        m_data = source.m_data;
        return *this;
    }
    BfmeStringData3AF0 *m_data;
};

class BfmeString1284;
class BfmeStringWriter1284
{
public:
    // Existing pin at 008B8E70 uses int for the separator pointer's bits.
    void bfmeBuildString1284(BfmeString1284 *output, int separator);
};

class Rva008B6880
{
public:
    // Opaque thiscall contract: hub +0434..0437; callee +01A,+0DC,+0280.
    // No claim about the original proprietary class or method name.
    void invoke(Rva8CD130String *output);
};

extern void bfmeResetEVF(void *, BfmeStrVKI *);

class Rva8CD130Value
{
public:
    void getName(Rva8CD130String *output);
    bool isUndefined() const { return ((m_flags >> 15) & 1) == 0; }
    void *m_unknown00;
    unsigned int m_flags;
    union
    {
        unsigned char m_boolean;
        int m_integer;
        float m_float;
        Rva8CD130String m_string;
    };
    unsigned char m_unknown0C[0x14];
    union
    {
        Rva8CD130Value *m_indirect;
        unsigned int m_raw20;
        Rva8CD130String m_string20;
    };
};

void Rva8CD130Value::getName(Rva8CD130String *output)
{
    char buffer[128];
    if (isUndefined())
    {
        output->clear();
        return;
    }

    unsigned int type = m_flags & 0x3F;
    switch (type)
    {
    case 1:
    case 42:
    {
        Rva8CD130Value *value = this;
        if (type != 1)
            value = m_indirect;
        output->assign(value->m_string);
        break;
    }
    case 5:
        if (m_boolean)
            output->assign(*reinterpret_cast<Rva8CD130String *>(0x01338720));
        else
            output->assign(*reinterpret_cast<Rva8CD130String *>(0x01338550));
        break;
    case 7:
    {
        int number = m_integer;
        sprintf(buffer, reinterpret_cast<const char *>(0x0107C7B4), number);
        *output = BfmeStrVKI(buffer); // T0
        break;
    }
    case 6:
    {
        union { unsigned bits; float number; } copy;
        copy.bits = static_cast<unsigned>(m_integer);
        if (fmod(static_cast<double>(copy.number), g_bfmeSubB3) == BfmeZeroRange)
            sprintf(buffer, reinterpret_cast<const char *>(0x0107C7B4),
                static_cast<int>(m_float));
        else
            sprintf(buffer, reinterpret_cast<const char *>(0x01082F4C),
                static_cast<double>(m_float));
        *output = BfmeStrVKI(buffer); // T1: both float arms join first
        break;
    }
    case 22:
        reinterpret_cast<BfmeStringWriter1284 *>(this)->bfmeBuildString1284(
            reinterpret_cast<BfmeString1284 *>(output), 0x01076FE8);
        break;
    case 21:
        *output = BfmeStrVKI(reinterpret_cast<const char *>(0x01136028)); // T2
        break;
    case 9:
        sprintf(buffer, reinterpret_cast<const char *>(0x0113600C), m_raw20);
        *output = BfmeStrVKI(buffer); // T3
        break;
    case 10:
        *output = BfmeStrVKI(reinterpret_cast<const char *>(0x01136000)); // T4
        break;
    case 23: case 24: case 25: case 26: case 27:
    case 31: case 35: case 36: case 39:
        *output = BfmeStrVKI(reinterpret_cast<const char *>(0x01135FF0)); // T5
        break;
    case 32: case 33: case 34:
        *output = BfmeStrVKI(reinterpret_cast<const char *>(0x01135FE4)); // T6
        break;
    case 28:
        *output = BfmeStrVKI(reinterpret_cast<const char *>(0x01135FCC)); // T7
        break;
    case 29:
        reinterpret_cast<Rva008B6880 *>(this)->invoke(output);
        break;
    case 30:
        *output = BfmeStrVKI(reinterpret_cast<const char *>(0x01135FC0)); // T8
        break;
    case 4:
        *output = BfmeStrVKI(reinterpret_cast<const char *>(0x01135FB4)); // T9
        break;
    case 8:
        *output = BfmeStrVKI(reinterpret_cast<const char *>(0x01135FA8)); // T10
        break;
    case 11:
        *output = BfmeStrVKI(reinterpret_cast<const char *>(0x01135F9C)); // T11
        break;
    case 20:
        *output = BfmeStrVKI(reinterpret_cast<const char *>(0x01135F8C)); // T12
        break;
    case 37:
        *output = BfmeStrVKI(reinterpret_cast<const char *>(0x01135F80)); // T13
        break;
    case 38:
        *output = BfmeStrVKI(reinterpret_cast<const char *>(0x01135F6C)); // T14
        break;
    case 41:
        output->assign(m_string20);
        break;
    default:
        bfmeResetEVF(this, reinterpret_cast<BfmeStrVKI *>(output));
        break;
    }
}

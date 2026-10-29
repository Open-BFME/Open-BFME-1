// cl: /DNDEBUG /MD /EHsc /Igame/Libraries/Source/WWVegas/WWLib
// Address-derived cdecl message-box text update at RVA 0x00522110.
#include "ascii_string.h"
#include "unicode_string.h"

inline UnicodeString::UnicodeString(const wchar_t *text)
{
    ((StringBase<unsigned short> *)this)->StringBase<unsigned short>::StringBase(text);
}

inline UnicodeString::~UnicodeString()
{
    ((StringBase<unsigned short> *)this)->releaseBuffer();
}

template <typename T>
inline bool StringBase<T>::isEmpty() const
{
    return m_data == 0 || m_data->length == 0;
}

struct Rva00522110State
{
    char m_lead[0x34];
    int m_34;
    int m_38;
};

class BfmeThingCB;
extern BfmeThingCB *g_bfmeThingCB;

class WindowManager
{
public:
    void bfme_setAptText(const AsciiString &name, const UnicodeString &text);
};
// Retail 0x012F19E8 is ?g_rva012F19E8WindowManager@@3PAVWindowManager@@A
// (data_rows.csv, GUI/WindowManager.cpp); g_theWindowManager was only a pin.
extern WindowManager *g_rva012F19E8WindowManager;
#define g_theWindowManager g_rva012F19E8WindowManager

// ?rva00522110@@YA_NHABVUnicodeString@@0@Z
bool rva00522110(int mode, const UnicodeString &title, const UnicodeString &body)
{
    if (g_bfmeThingCB == 0)
        return false;
    if (reinterpret_cast<Rva00522110State *>(g_bfmeThingCB)->m_38 == 4)
        return false;
    reinterpret_cast<Rva00522110State *>(g_bfmeThingCB)->m_34 = 4;
    reinterpret_cast<Rva00522110State *>(g_bfmeThingCB)->m_38 = mode;
    if (title.isEmpty())
        g_theWindowManager->bfme_setAptText(AsciiString("APT:MessageBoxGenericTitle"), UnicodeString(L" "));
    else
        g_theWindowManager->bfme_setAptText(AsciiString("APT:MessageBoxGenericTitle"), title);
    g_theWindowManager->bfme_setAptText(AsciiString("APT:MessageBoxGenericText"), body);
    return true;
}

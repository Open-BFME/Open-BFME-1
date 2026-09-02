// stlport
// STLport 4.5.3 narrow filebuf input-error transition.

extern "C" {
__declspec(dllimport) int __stdcall UnmapViewOfFile(const void *base);
__declspec(dllimport) int __stdcall CloseHandle(void *handle);
}

namespace _STL {

template <class T> class char_traits {};

struct Rva0084A5D0GetArea
{
    char *eback;
    char *gptr;
    char *egptr;
};

template <class CharT, class Traits>
class basic_filebuf
{
private:
    int _M_input_error();

    void setg(char *begin, char *next, char *end)
    {
        Rva0084A5D0GetArea *area = m_getArea;
        area->egptr = end;
        area->eback = begin;
        area->gptr = next;
    }

    char m_pad0[4];
    Rva0084A5D0GetArea * volatile m_getArea;
    char m_pad1[0x58 - 8];
    void *m_view;
    char m_pad2[0x67 - 0x5c];
    volatile unsigned char m_inInputMode;
    volatile unsigned char m_inOutputMode;
    volatile unsigned char m_inErrorMode;
    char m_pad3[0x8c - 0x6a];
    void *m_mapBase;
};

template <class CharT, class Traits>
int basic_filebuf<CharT, Traits>::_M_input_error()
{
    if (m_mapBase != 0)
    {
        UnmapViewOfFile(m_mapBase);
        if (m_view != 0)
            CloseHandle(m_view);
        m_view = 0;
    }
    m_inInputMode = false;
    *(void * volatile *)&m_mapBase = 0;
    m_inOutputMode = false;
    m_inErrorMode = true;
    setg(0, 0, 0);
    return -1;
}

template int basic_filebuf<char, char_traits<char> >::_M_input_error();

}

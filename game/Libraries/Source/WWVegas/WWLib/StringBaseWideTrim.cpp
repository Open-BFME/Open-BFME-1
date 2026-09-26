// cl: /DNDEBUG /MD /EHs-c- /Igame/GameEngine/Source/Common/System
//
// Source model for StringBase<wchar_t>::trim(), retail RVA
// 0x00888ED0, complete body 147 bytes with the final ret at +0x92
// (end-exclusive 0x00888F63).
//
// The leading helper is included from the actual visible TU body rather than
// declared as an ordinary external cdecl function.  SkipWhitespaceW.c defines
// file-static skipWhitespace(unsigned short*) and its visible keep-alive call;
// MSVC 7.1 consequently uses the private EAX-incoming convention seen at
// retail 0x008872B0.  The same helper body is therefore available to this
// StringBase trim TU without an ABI-cast or a fabricated wrapper.

// Keep the helper out of line: retail trim has a direct REL32 to the
// file-static helper body rather than inlining its scan.
#define static __declspec(noinline) static
extern "C" {
#include "SkipWhitespaceW.c"
}
#undef static

typedef unsigned short WideChar;

template <typename T>
class StringBase
{
private:
    struct Header
    {
        int ref_count;
        unsigned short length;
        unsigned short capacity;
        unsigned short data[1];
    };

    Header *m_data;

public:
    void trim();
    T *peek() const { return &m_data->data[0]; }
    T getCharAt(int index) const { return m_data ? m_data->data[index] : 0; }
private:
    void ensureUniqueBufferOfSize(int newLen, bool keepData,
                                  const T *src1, int src1Len,
                                  const T *src2, int src2Len);
    void releaseBuffer();
public:
    void removeLastChar();
};

template <>
void StringBase<WideChar>::trim()
{
    if (m_data)
    {
        // This call is intentionally to the actual file-static helper above;
        // its pointer arrives in EAX under MSVC's private static convention.
        const unsigned int c = (unsigned int)skipWhitespace(peek());

        if ((const WideChar *)c != peek())
        {
            int len = m_data ? m_data->length : 0;
            int skipped = c - (unsigned int)m_data - 8;
            skipped = skipped >> 1;
            len -= skipped;
            if (len != 0)
            {
                ensureUniqueBufferOfSize(
                    len, false, (const WideChar *)c, len,
                    0, 0);
            }
            else
            {
                releaseBuffer();
            }
        }

        if (m_data)
        {
            int index = m_data->length;
            while (index > 0)
            {
                --index;
                if (iswspace((int)(unsigned short)(m_data ? m_data->data[index] : 0)))
                {
                    removeLastChar();
                }
                else
                {
                    break;
                }
            }
        }
    }
}

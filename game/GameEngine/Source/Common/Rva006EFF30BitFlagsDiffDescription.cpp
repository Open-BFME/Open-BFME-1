// cl: /DNDEBUG /DWIN32 /MD /EHsc /D_STLP_USE_STATIC_LIB
// stlport
// Address-derived owner for the decoded model-condition difference formatter.
#include "../../../Libraries/Source/WWVegas/WWLib/ascii_string.h"
#include <bitset>

extern const char *const ModelConditionNames[];

class Rva006EFF30
{
public:
    void buildDescription(AsciiString *str, const Rva006EFF30 &other, bool includeSame, int maxPerLine) const;
    // ?test@Rva006EFF30@@QBE_NH@Z absent-from-retail
    bool test(int index) const { return m_bits._Unchecked_test(index); }

private:
    _STL::bitset<304> m_bits;
};

// ?buildDescription@Rva006EFF30@@QBEXPAVAsciiString@@ABV1@_NH@Z
void Rva006EFF30::buildDescription(AsciiString *str, const Rva006EFF30 &other, bool includeSame, int maxPerLine) const
{
    AsciiString description;
    if (str == 0)
        return;
    str->clear();
    int count = 0;
    bool first = true;
    for (int i = 0; i < 304; ++i)
    {
        bool oldSet = other.test(i);
        bool newSet = test(i);
        if (oldSet != newSet || (newSet && includeSame))
        {
            if (!first)
                static_cast<StringBase<char> *>(str)->concat(", ", 2);
            if (count >= maxPerLine)
            {
                count = 0;
                static_cast<StringBase<char> *>(str)->concat("\n", 1);
            }
            if (newSet && !oldSet)
            {
                description.format(AsciiString("+%s"), ModelConditionNames[i]);
                static_cast<StringBase<char> *>(str)->concat(description.str(), description.getLength());
            }
            else if (includeSame && newSet)
            {
                description.format(AsciiString("%s"), ModelConditionNames[i]);
                static_cast<StringBase<char> *>(str)->concat(description.str(), description.getLength());
            }
            else
            {
                description.format(AsciiString("-%s"), ModelConditionNames[i]);
                static_cast<StringBase<char> *>(str)->concat(description.str(), description.getLength());
            }
            first = false;
            ++count;
        }
    }
}

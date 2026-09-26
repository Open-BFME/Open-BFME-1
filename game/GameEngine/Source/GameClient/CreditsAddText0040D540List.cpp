// cl: /O2 /EHsc /DNDEBUG /MD /D_STLP_USE_STATIC_LIB
// stlport
#define _STLP_NO_EXCEPTIONS 1
#include <list>

template <typename T> class StringBase
{
private:
    StringBase() : m_data(0) {}
    StringBase(const StringBase &other);
    ~StringBase() { releaseBuffer(); }
    void releaseBuffer();
public:
    void set(const StringBase &other);
private:
    void *m_data;
    friend class AsciiString;
    friend class UnicodeString;
};

class AsciiString : private StringBase<char>
{
public:
    AsciiString() {}
    AsciiString(const AsciiString &other) : StringBase<char>(other) {}
    ~AsciiString() {}
};

class UnicodeString : private StringBase<unsigned short>
{
public:
    UnicodeString() {}
    UnicodeString(const UnicodeString &other) : StringBase<unsigned short>(other) {}
    ~UnicodeString() {}
    UnicodeString &operator=(const UnicodeString &other)
    {
        StringBase<unsigned short>::set(other);
        return *this;
    }
};

class CreditsLine
{
public:
    CreditsLine() : style(4), text(), secondText(), useSecond(0), done(0),
        display(0), secondDisplay(0), posX(0), posY(0), height(0), color(0) {}
    ~CreditsLine();

    int style;
    UnicodeString text;
    UnicodeString secondText;
    unsigned char useSecond;
    unsigned char done;
    unsigned char pad0E[2];
    void *display;
    void *secondDisplay;
    int posX;
    int posY;
    int height;
    int color;
};

class CreditsManager
{
public:
    void addText(AsciiString text);

private:
    UnicodeString getUnicodeString(AsciiString text);
    char pad00[8];
    std::list<CreditsLine *> lines;
    char pad0C[0x20];
    int currentStyle;
};

void CreditsManager::addText(AsciiString text)
{
    CreditsLine *line = new CreditsLine;
    switch (currentStyle)
    {
    case 0:
    case 1:
    case 2:
        line->text = getUnicodeString(text);
        line->style = currentStyle;
        lines.push_back(line);
        break;
    case 3:
        {
            std::list<CreditsLine *>::reverse_iterator it = lines.rbegin();
            CreditsLine *last = *it;
            if (it == lines.rend() || last->style != 3 || last->done == 1)
            {
                line->text = getUnicodeString(text);
                line->style = 3;
                line->useSecond = 1;
                lines.push_back(line);
            }
            else
            {
                last->secondText = getUnicodeString(text);
                last->done = 1;
                delete line;
            }
        }
        break;
    default:
        delete line;
    }
}

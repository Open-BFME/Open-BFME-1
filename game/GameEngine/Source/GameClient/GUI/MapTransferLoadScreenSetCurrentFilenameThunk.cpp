// cl: /DNDEBUG /MD /EHsc
// MapTransferLoadScreen::setCurrentFilename(AsciiString), legacy GUI body.
// Matches the readable LoadScreen method and MapTransfer vtable family;
// no direct retail caller is asserted. The ret 4 at RVA 0x00492097 ends
// the full 250-byte body, followed by int3 at 0x0049209A.
// The retail object uses the BFME eight-byte string header and keeps the
// filename text window at this+0xB0, rather than the ZH header's offset.

typedef int Int;
typedef unsigned short WideChar;

class AsciiString;
class UnicodeString;

class BFMERetailAsciiString
{
    friend class AsciiString;

private:
    void releaseBuffer();
};

template <typename T>
class StringBase
{
    friend class UnicodeString;

protected:
    StringBase() : m_data(0) {}
    StringBase(const StringBase &other);
    ~StringBase() {}

    void *m_data;

private:
    void releaseBuffer();
};

class AsciiString : private StringBase<char>
{
public:
    AsciiString() : StringBase<char>() {}
    AsciiString(const AsciiString &other)
        : StringBase<char>(*reinterpret_cast<const StringBase<char> *>(&other)) {}
    ~AsciiString()
    {
        reinterpret_cast<BFMERetailAsciiString *>(this)->releaseBuffer();
    }

    const char *str() const
    {
        if (m_data)
            return reinterpret_cast<const char *>(m_data) + 8;
        return reinterpret_cast<const char *>(0x0107388B);
    }
};

class UnicodeString : private StringBase<WideChar>
{
public:
    UnicodeString() : StringBase<WideChar>() {}
    UnicodeString(const UnicodeString &other)
        : StringBase<WideChar>(*reinterpret_cast<const StringBase<WideChar> *>(&other)) {}
    ~UnicodeString()
    {
        StringBase<WideChar>::releaseBuffer();
    }

    void translate(const AsciiString &);
    void format(UnicodeString, ...);

    const WideChar *str() const
    {
        if (m_data)
            return reinterpret_cast<const WideChar *>(reinterpret_cast<const char *>(m_data) + 8);
        return reinterpret_cast<const WideChar *>(0x0107388C);
    }
};

class GameState
{
public:
    AsciiString getMapLeafName(const AsciiString &) const;
};

class GameTextInterface
{
public:
    virtual void slot00();
    virtual void slot01();
    virtual void slot02();
    virtual void slot03();
    virtual void slot04();
    virtual void slot05();
    virtual void slot06();
    virtual void slot07();
    virtual void slot08();
    virtual void slot09();
    virtual UnicodeString fetch(const char *, bool *exists = 0);
};

class GameWindow;

extern GameState *TheGameState;
extern GameTextInterface *TheGameText;
extern void j_0002c16f();

class MapTransferLoadScreen
{
public:
    void setCurrentFilename(AsciiString filename);

private:
    char m_padding[0xB0];
    GameWindow *m_fileNameText;
};

void MapTransferLoadScreen::setCurrentFilename(AsciiString filename)
{
    if (m_fileNameText)
    {
        UnicodeString txt;
        txt.translate(TheGameState->getMapLeafName(filename));
        txt.format(TheGameText->fetch("MapTransfer:CurrentFile"), txt.str());

        typedef void (*TextFn)(GameWindow *, UnicodeString);
        (reinterpret_cast<TextFn>(j_0002c16f))(m_fileNameText, txt);
    }
}

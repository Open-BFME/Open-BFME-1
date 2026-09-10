// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /D_STLP_USE_STATIC_LIB /Ireference/shims/sweep /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWDebug /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad
// Real 519-byte saveReplay, RVA 0x004DE8E0..0x004DEAE7.
// PopupReplaySystem names the caller; StringBase owns copies and cleanup.
// Shared state is defined once in PopupReplay.cpp (never TU-local copies).
// stlport

#include <string>
#include <string.h>

typedef bool Bool;

class AsciiString;
class UnicodeString;

template <typename T> struct BfmeStringHeader
{
    int references;
    unsigned short length;
    unsigned short capacity;
    T data[1];
};

template <typename T> class StringBase
{
    friend class AsciiString;
    friend class UnicodeString;

private:
    StringBase() : m_data(0) {}
    StringBase(const StringBase<T> &other);
    ~StringBase();
    void releaseBuffer();

public:
    void set(const StringBase<T> &source);
    void concat(const T *text, int length);
    int compare(const StringBase<T> &other) const throw();

    void *m_data;
};

class UnicodeString : private StringBase<unsigned short>
{
public:
    UnicodeString() : StringBase<unsigned short>() {}
    UnicodeString(const UnicodeString &other)
        : StringBase<unsigned short>(other)
    {
    }
    ~UnicodeString() {}
};

inline bool operator==(const UnicodeString &left, const UnicodeString &right)
{
    return ((const StringBase<unsigned short> *)&left)->compare(
        *(const StringBase<unsigned short> *)&right) == 0;
}

class AsciiString : private StringBase<char>
{
public:
    AsciiString() : StringBase<char>() {}
    AsciiString(const AsciiString &other) : StringBase<char>(other) {}
    ~AsciiString() {}

    AsciiString &operator=(const AsciiString &other)
    {
        ((StringBase<char> *)this)->set(
            *(const StringBase<char> *)&other);
        return *this;
    }

    void translate(const UnicodeString &source);

    void concat(const AsciiString &source)
    {
        BfmeStringHeader<char> *data =
            (BfmeStringHeader<char> *)source.m_data;
        int length = data ? data->length : 0;
        const char *text = source.str();
        ((StringBase<char> *)this)->concat(text, length);
    }

    const char *str() const
    {
        return m_data ? (const char *)m_data + 8 : "";
    }
};

class GameTextInterface
{
public:
    virtual void slot00() = 0;
    virtual void slot01() = 0;
    virtual void slot02() = 0;
    virtual void slot03() = 0;
    virtual void slot04() = 0;
    virtual void slot05() = 0;
    virtual void slot06() = 0;
    virtual void slot07() = 0;
    virtual void slot08() = 0;
    virtual void slot09() = 0;
    virtual UnicodeString fetch(const char *label, Bool *exists = 0);
};

class RecorderClass
{
public:
    AsciiString getLastReplayFileName();
    static AsciiString getReplayDir();
    static AsciiString getReplayExtention();
};

class FileSystem
{
public:
    Bool doesFileExist(const char *filename) const;
};

class GameWindow;
typedef void (*GameWinMsgBoxFunc)(void);

extern GameTextInterface *TheGameText;
extern RecorderClass *TheRecorder;
extern FileSystem *TheLocalFileSystem;
namespace PopupReplayState
{
extern GameWindow *messageBoxWin;
extern std::string replayPath;
}
using namespace PopupReplayState;
extern void reallySaveReplay(void);
extern GameWindow *MessageBoxYesNo(UnicodeString title, UnicodeString body,
    GameWinMsgBoxFunc okCallback, GameWinMsgBoxFunc cancelCallback);

// ?saveReplay@@YAXVUnicodeString@@@Z
void saveReplay(UnicodeString filename)
{
    AsciiString translated;
    if (filename == TheGameText->fetch("GUI:LastReplay"))
    {
        translated = TheRecorder->getLastReplayFileName();
    }
    else
    {
        translated.translate(filename);
    }

    AsciiString fullPath = TheRecorder->getReplayDir();
    fullPath.concat(translated);
    fullPath.concat(TheRecorder->getReplayExtention());

    const char *pathText = fullPath.str();
    replayPath.assign(pathText, pathText + strlen(pathText));
    messageBoxWin = 0;
    if (TheLocalFileSystem->doesFileExist(fullPath.str()))
    {
        MessageBoxYesNo(TheGameText->fetch("GUI:OverwriteReplayTitle"),
            TheGameText->fetch("GUI:OverwriteReplay"), reallySaveReplay, 0);
    }
    else
    {
        reallySaveReplay();
    }
}

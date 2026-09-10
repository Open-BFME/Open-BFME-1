// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /D_STLP_USE_STATIC_LIB /Ireference/shims/sweep /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWDebug /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad
// Real 922-byte reallySaveReplay, RVA 0x004DE460..0x004DE7FA.
// saveReplay passes this actual callback and calls it directly.
// Shared state is defined once in PopupReplay.cpp; retail uses two distinct
// 1024-wide-character error buffers and the original FormatMessage byte count.
// stlport

#include <string>
#include <string.h>
#include <windows.h>

typedef bool Bool;

class AsciiString;
class UnicodeString;

enum NameKeyType
{
    NAMEKEY_INVALID = 0,
    FORCE_NAMEKEYTYPE_LONG = 0x7fffffff
};

typedef long time_t;

template <typename BfmeChar>
struct BfmeStringHeader
{
    int references;
    unsigned short length;
    unsigned short capacity;
    BfmeChar data[1];
};

template <typename BfmeChar>
class StringBase
{
    friend class AsciiString;
    friend class UnicodeString;

private:
    StringBase() : m_data(0) {}
    StringBase(const StringBase<BfmeChar> &source);
    ~StringBase();

public:
    void set(const StringBase<BfmeChar> &source);
    void set(const BfmeChar *source);
    void set(const BfmeChar *source, int length);
    void concat(const BfmeChar *text, int length);
    int compare(const StringBase<BfmeChar> &other) const throw();
    void trim();

private:
    void *m_data;
};

class UnicodeString : private StringBase<unsigned short>
{
public:
    UnicodeString() : StringBase<unsigned short>() {}

    void set(const wchar_t *source)
    {
        ((StringBase<unsigned short> *)this)->set(
            (const unsigned short *)source);
    }

    void set(const wchar_t *source, int length)
    {
        ((StringBase<unsigned short> *)this)->set(
            (const unsigned short *)source, length);
    }

    void trim()
    {
        ((StringBase<unsigned short> *)this)->trim();
    }
};

class AsciiString : private StringBase<char>
{
public:
    AsciiString() : StringBase<char>() {}
    AsciiString(const char *source);

    AsciiString &operator=(const AsciiString &source)
    {
        ((StringBase<char> *)this)->set(
            *(const StringBase<char> *)&source);
        return *this;
    }

    void concat(const AsciiString &source)
    {
        BfmeStringHeader<char> *data =
            (BfmeStringHeader<char> *)source.m_data;
        int length = data ? data->length : 0;
        const char *text = source.str();
        ((StringBase<char> *)this)->concat(text, length);
    }

    void concat(const char *text)
    {
        int length = text ? (int)strlen(text) : 0;
        ((StringBase<char> *)this)->concat(text, length);
    }

    const char *str() const
    {
        return m_data ? (const char *)m_data + 8
                      : "";
    }
};

inline bool operator==(const AsciiString &left, const AsciiString &right)
{
    return ((const StringBase<char> *)&left)->compare(
        *(const StringBase<char> *)&right) == 0;
}

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

class GameWindow
{
public:
    int winHide(Bool hide);
};

class GameWindowManager
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
    virtual void slot10() = 0;
    virtual void slot11() = 0;
    virtual void slot12() = 0;
    virtual void slot13() = 0;
    virtual void slot14() = 0;
    virtual void slot15() = 0;
    virtual void slot16() = 0;
    virtual void slot17() = 0;
    virtual void slot18() = 0;
    virtual void slot19() = 0;
    virtual void slot20() = 0;
    virtual void slot21() = 0;
    virtual void slot22() = 0;
    virtual void slot23() = 0;
    virtual void slot24() = 0;
    virtual void slot25() = 0;
    virtual void slot26() = 0;
    virtual void slot27() = 0;
    virtual void slot28() = 0;
    virtual void slot29() = 0;
    virtual void slot30() = 0;
    virtual void slot31() = 0;
    virtual void slot32() = 0;
    virtual void slot33() = 0;
    virtual void slot34() = 0;
    virtual void slot35() = 0;
    virtual void slot36() = 0;
    virtual void slot37() = 0;
    virtual void slot38() = 0;
    virtual void slot39() = 0;
    virtual void slot40() = 0;
    virtual void slot41() = 0;
    virtual void slot42() = 0;
    virtual void slot43() = 0;
    virtual void slot44() = 0;
    virtual void slot45() = 0;
    virtual void slot46() = 0;
    virtual void slot47() = 0;
    virtual void slot48() = 0;
    virtual void slot49() = 0;
    virtual void slot50() = 0;
    virtual void slot51() = 0;
    virtual void slot52() = 0;
    virtual void slot53() = 0;
    virtual void slot54() = 0;
    virtual GameWindow *winGetWindowFromId(GameWindow *window, int id);
    virtual int slot56(GameWindow *) = 0;
    virtual int slot57(GameWindow *) = 0;
    virtual GameWindow *slot58();
    virtual int slot59(GameWindow *) = 0;
    virtual int winUnsetModal(GameWindow *window);
};

class RecorderClass
{
public:
    static AsciiString getReplayDir();
    static AsciiString getReplayExtention();
};

class FileSystem
{
public:
    Bool doesFileExist(const char *filename) const;
};

__declspec(dllimport) unsigned int bfmeLenVGI(const unsigned short *source);

typedef void (*GameWinMsgBoxFunc)(void);

extern GameTextInterface *TheGameText;
extern RecorderClass *TheRecorder;
extern FileSystem *TheLocalFileSystem;
extern GameWindowManager *TheWindowManager;
extern std::string LastReplayFileName;
extern void PopulateReplayFileListbox(GameWindow *listbox);
extern GameWindow *MessageBoxOk(UnicodeString title, UnicodeString body,
    GameWinMsgBoxFunc callback);

namespace PopupReplayState
{
extern GameWindow *parent;
extern GameWindow *replaySavedParent;
extern NameKeyType listboxGamesKey;
extern time_t s_fileSavePopupStartTime;
extern GameWindow *messageBoxWin;
extern std::string replayPath;
}
using namespace PopupReplayState;

static void showReplaySavedPopup(Bool show)
{
    if (replaySavedParent != 0)
    {
        if (show)
        {
            replaySavedParent->winHide(FALSE);
        }
        else
        {
            replaySavedParent->winHide(TRUE);
        }
    }
}

void reallySaveReplay(void)
{
    struct ReplayErrorBuffers
    {
        wchar_t copyErrorBuffer[1024];
        wchar_t deleteErrorBuffer[1024];
    } errorBuffers;
    AsciiString filename = replayPath.c_str();

    AsciiString oldFilename;
    oldFilename = TheRecorder->getReplayDir();
    oldFilename.concat(LastReplayFileName.c_str());
    oldFilename.concat(TheRecorder->getReplayExtention());

    if (oldFilename == filename)
        return;

    if (TheLocalFileSystem->doesFileExist(filename.str()))
    {
        if (DeleteFileA(filename.str()) == 0)
        {
            FormatMessageW(FORMAT_MESSAGE_FROM_SYSTEM, 0, GetLastError(), 0,
                errorBuffers.deleteErrorBuffer,
                sizeof(errorBuffers.deleteErrorBuffer), 0);
            UnicodeString errorStr;
            errorStr.set(errorBuffers.deleteErrorBuffer);
            errorStr.trim();
            if (messageBoxWin)
            {
                TheWindowManager->winUnsetModal(messageBoxWin);
                messageBoxWin = 0;
            }
            MessageBoxOk(TheGameText->fetch("GUI:Error"), errorStr, 0);

            GameWindow *listboxGames =
                TheWindowManager->winGetWindowFromId(parent, listboxGamesKey);
            PopulateReplayFileListbox(listboxGames);
            return;
        }
    }

    if (CopyFileA(oldFilename.str(), filename.str(), FALSE) == 0)
    {
        FormatMessageW(FORMAT_MESSAGE_FROM_SYSTEM, 0, GetLastError(), 0,
            errorBuffers.copyErrorBuffer,
            sizeof(errorBuffers.copyErrorBuffer), 0);
        UnicodeString errorStr;
        errorStr.set(errorBuffers.copyErrorBuffer,
            bfmeLenVGI((const unsigned short *)errorBuffers.copyErrorBuffer));
        errorStr.trim();
        if (messageBoxWin)
        {
            TheWindowManager->winUnsetModal(messageBoxWin);
            messageBoxWin = 0;
        }
        MessageBoxOk(TheGameText->fetch("GUI:Error"), errorStr, 0);
        return;
    }

    GameWindow *listboxGames =
        TheWindowManager->winGetWindowFromId(parent, listboxGamesKey);
    PopulateReplayFileListbox(listboxGames);

    showReplaySavedPopup(TRUE);
    s_fileSavePopupStartTime = timeGetTime();
}

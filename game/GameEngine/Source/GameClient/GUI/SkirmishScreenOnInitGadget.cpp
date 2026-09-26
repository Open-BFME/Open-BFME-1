// cl: /O2 /Ob2 /DNDEBUG /MD /EHsc
// BFME Skirmish selector callback for the three APT controls.

extern "C" int strcmp(const char *left, const char *right);

class GameWindow
{
public:
    void *winGetUserData();
};

class WinInstanceData
{
private:
    char m_unmodelled[0x10];

public:
    unsigned short m_controlID;
};

template <typename T> struct StringData
{
    int m_refCount;
    unsigned short m_length;
    unsigned short m_max;
    T m_text[1];
};

class UnicodeString;

template <typename T> class StringBase
{
    friend class UnicodeString;

private:
    StringBase() : m_data(0) {}
    StringBase(const StringBase &other);
    void releaseBuffer();

    StringData<T> *m_data;
};

class UnicodeString : private StringBase<unsigned short>
{
public:
    static UnicodeString TheEmptyString;

    __forceinline UnicodeString(const UnicodeString &other)
        : StringBase<unsigned short>(other) {}

    __forceinline ~UnicodeString()
    {
        ((StringBase<unsigned short> *)this)->releaseBuffer();
    }
};

void GadgetTextEntrySetText(GameWindow *window, UnicodeString text);

class BfmeOwnerEJ
{
public:
    char m_unmodelled[0x1dc];
    int m_back;
};

class Gen_00479A60
{
public:
    void bfmeAttach(BfmeOwnerEJ *owner);

private:
    int *m_table;
    int m_value;

public:
    GameWindow *m_owner;
};

__forceinline GameWindow *ownerWindow(Gen_00479A60 *entry)
{
    return entry->m_owner;
}

class BfmeAptScreenSkirmish
{
public:
    void _bfme_onInitGadget(const char *name, void *argument, GameWindow *window);
    void _bfme_refreshProfile();

private:
    char m_unmodelled_00[0x40c];
    GameWindow *m_gameInfo;
    char m_unmodelled_410[0x10];
    GameWindow *m_playerProfile;
    Gen_00479A60 m_createPersonaEntry;
    char m_unmodelled_430[0xc];
};

// ?_bfme_onInitGadget@BfmeAptScreenSkirmish@@QAEXPBDPAXPAVGameWindow@@@Z
void BfmeAptScreenSkirmish::_bfme_onInitGadget(
    const char *name, void *, GameWindow *window)
{
    if (window == 0)
        return;

    if (strcmp(name, "Skirmish::GameInfo") == 0)
    {
        m_gameInfo = window;
        return;
    }

    if (strcmp(name, "Skirmish::CreatePersonaEntry") == 0)
    {
        m_createPersonaEntry.bfmeAttach((BfmeOwnerEJ *)window);
        UnicodeString emptyString = UnicodeString::TheEmptyString;
        if (m_createPersonaEntry.m_owner != 0)
        {
            WinInstanceData *instanceData =
                (WinInstanceData *)((GameWindow *)m_createPersonaEntry.m_owner)->winGetUserData();
            if (instanceData != 0)
                instanceData->m_controlID = 11;
        }
        GadgetTextEntrySetText(
            ownerWindow(&m_createPersonaEntry), emptyString);
        return;
    }

    if (strcmp(name, "Skirmish::PlayerProfile") == 0)
    {
        m_playerProfile = window;
        _bfme_refreshProfile();
    }
}

// cl: /DNDEBUG /MD /EHsc /Ireference/shims/stringinline
// Open-BFME: Shell::shutdownComplete, retail 0x0057FD80.
//
// The BFME Shell stores its pending push and pop flags at +0x4c and +0x4d,
// its pending AsciiString at +0x54, and its AnimateWindowManager at +0x5c.
// Those offsets match Shell_ctor_Thunk.cpp and the method body in Shell.cpp.

typedef bool Bool;

template <typename T> class StringBase
{
    friend class AsciiString;

private:
    StringBase(const StringBase<T> &other);
    ~StringBase();

public:
    void set(const T *text, int length);

    void *m_data;
};

class AsciiString : private StringBase<char>
{
public:
    AsciiString(const AsciiString &other) : StringBase<char>(other) {}
    ~AsciiString() {}

    void set(const char *text, int length)
    {
        ((StringBase<char> *)this)->set(text, length);
    }
};

class WindowLayout;

class AnimateWindowManager
{
public:
    virtual void slot00() = 0;
    virtual void slot04() = 0;
    virtual void slot08() = 0;
    virtual void slot0c() = 0;
    virtual void reset() = 0;
};

class Shell
{
public:
    void shutdownComplete(WindowLayout *screen, Bool impendingPush);

protected:
    void doPush(AsciiString layoutFile);
    void doPop(Bool impendingPush);

private:
    char m_unreconstructed_00[0x4c];
    Bool m_bfmeState4c;
    Bool m_pendingPop;
    char m_unreconstructed_4e[0x06];
    AsciiString m_pendingPushName;
    char m_unreconstructed_58[0x04];
    AnimateWindowManager *m_animateWindowManager;
};

#pragma comment(linker, "/alternatename:?doPush@Shell@@IAEXVAsciiString@@@Z=?j_00026792@@YAXXZ")

void Shell::shutdownComplete(WindowLayout *, Bool impendingPush)
{
    m_animateWindowManager->reset();

    if (m_bfmeState4c)
    {
        doPush(m_pendingPushName);
        m_bfmeState4c = false;
        m_pendingPushName.set("", 0);
    }
    else if (m_pendingPop)
    {
        doPop(impendingPush);
        m_pendingPop = false;
    }
}

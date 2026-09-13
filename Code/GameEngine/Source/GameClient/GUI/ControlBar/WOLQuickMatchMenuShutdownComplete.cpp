// cl: /DNDEBUG /MD /EHsc

// The 0x00507E10 WOLQuickMatchMenu shutdown callback calls the 0x00048E73
// incremental-link thunk with its WindowLayout receiver in ecx. The thunk
// reaches this 0x005057C0 body, which completes the shutdown and pushes the
// pending screen name when one exists.

typedef bool Bool;

template <typename T> class StringBase
{
    friend class AsciiString;

private:
    StringBase(const T *text);
    StringBase(const StringBase<T> &other);
    ~StringBase();

    void *m_data;
};

class AsciiString : private StringBase<char>
{
public:
    AsciiString(const char *text) : StringBase<char>(text) {}
    AsciiString(const AsciiString &other) : StringBase<char>(other) {}
    ~AsciiString() {}
};

class WindowLayout
{
public:
    virtual void slot0(void);
    virtual void slot1(void);
    virtual void slot2(void);
    virtual void slot3(void);
    virtual void slot4(bool);
    void shutdownComplete(void);
};

class Shell
{
public:
    void shutdownComplete(WindowLayout *layout, Bool hasPending);
    void push(AsciiString filename, Bool shutdownImmediate);
};

static Bool isShuttingDown = false;

void WindowLayout::shutdownComplete(void)
{
    isShuttingDown = false;
    slot4(true);
    (*(Shell **)0x012F4B58)->shutdownComplete(
        this, *(const char **)0x012F4804 != 0);
    if (*(const char **)0x012F4804 != 0)
        (*(Shell **)0x012F4B58)->push(
            AsciiString(*(const char **)0x012F4804), false);
    *(const char **)0x012F4804 = 0;
}

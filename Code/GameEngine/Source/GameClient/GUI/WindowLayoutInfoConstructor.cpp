// stlport
// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB
// BFME widens WindowLayoutInfo with one scalar and two AsciiString members.

#include <list>

typedef unsigned int UnsignedInt;

class WindowLayout;
class GameWindow;

typedef void (*WindowLayoutInitFunc)(WindowLayout *, void *);
typedef void (*WindowLayoutUpdateFunc)(WindowLayout *, void *);
typedef void (*WindowLayoutShutdownFunc)(WindowLayout *, void *);

template <typename T>
class StringBase
{
    friend class AsciiString;

private:
    StringBase() : m_data(0) {}
    StringBase(const StringBase<T> &other);
    ~StringBase();

    struct Data
    {
        int m_refCount;
        unsigned short m_length;
        unsigned short m_capacity;
        T m_text[1];
    };

    Data *m_data;
};

class AsciiString : private StringBase<char>
{
public:
    static AsciiString TheEmptyString;
    AsciiString() : StringBase<char>() {}
    AsciiString(const AsciiString &other) : StringBase<char>(other) {}
    ~AsciiString() {}
};

typedef std::list<GameWindow *> GameWindowList;

class WindowLayoutInfo
{
public:
	WindowLayoutInfo();

	UnsignedInt version;
	WindowLayoutInitFunc init;
	WindowLayoutUpdateFunc update;
	WindowLayoutShutdownFunc shutdown;
	void *_bfme_unk_10;
	AsciiString initNameString;
	AsciiString updateNameString;
	AsciiString shutdownNameString;
	AsciiString _bfme_unk_20;
	AsciiString _bfme_unk_24;
	GameWindowList windows;
};

WindowLayoutInfo::WindowLayoutInfo() :
	version(0),
	init(0),
	update(0),
	shutdown(0),
	_bfme_unk_10(0),
	initNameString(AsciiString::TheEmptyString),
	updateNameString(AsciiString::TheEmptyString),
	shutdownNameString(AsciiString::TheEmptyString)
{
	windows.clear();
}

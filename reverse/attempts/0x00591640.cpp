// ?d_00591640@@YAXXZ
// partial score=0.84 date=2026-09-18
// ??1Rva00591640GameClient68@@QAE@XZ
// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Ireference/shims/stringinline /D_STLP_USE_STATIC_LIB
// stlport

#include <hash_map>

template <typename T> class StringBase
{
	friend class AsciiString;

public:
	void concat(const T *text, int length);

private:
	StringBase() : m_data(0) {}
	StringBase(const T *text);
	StringBase(const StringBase<T> &other);
	~StringBase();

	void *m_data;
};

class AsciiString : private StringBase<char>
{
public:
	AsciiString() : StringBase<char>() {}
	AsciiString(const char *text) : StringBase<char>(text) {}
	AsciiString(const AsciiString &other) : StringBase<char>(other) {}
	~AsciiString() {}
};

struct Rva0046AF20Mapped
{
	void *m_callback;
};

namespace rts
{
	template <class T> struct hash;
	template <class T> struct equal_to;

	template <> struct hash<AsciiString>
	{
		unsigned int operator()(AsciiString value) const;
	};

	template <> struct equal_to<AsciiString>
	{
		int operator()(const AsciiString &left, const AsciiString &right) const;
	};
}

typedef std::hash_map<AsciiString, Rva0046AF20Mapped,
	rts::hash<AsciiString>, rts::equal_to<AsciiString> > Rva0046AF20Map;

class WindowManager
{
public:
	void removeAptObject(const AsciiString &name);

private:
	unsigned char m_padding[0x94];
	Rva0046AF20Map m_callbacks;
};

extern WindowManager *g_theWindowManager;
extern void j_00001f32();
extern void j_0003d54b();

class BfmeLayoutVHH
{
};

extern void bfmeGoVHH(char index, BfmeLayoutVHH *name);
AsciiString operator+(AsciiString left, const AsciiString &right);

typedef void (WindowManager::*WindowManagerStringMember)(const AsciiString *);

union WindowManagerStringCast
{
	void (*raw)();
	WindowManagerStringMember member;
};

static __forceinline void callWindowManagerString(
	WindowManager *manager, void (*function)(), AsciiString *name)
{
	WindowManagerStringCast cast;
	cast.raw = function;
	(manager->*cast.member)(name);
}

class Rva00591640GameClient68
{
public:
	~Rva00591640GameClient68();

private:
	unsigned char m_padding[8];
	bool m_active;
};

Rva00591640GameClient68::~Rva00591640GameClient68()
{
	int index;

	if (g_theWindowManager != 0)
	{
		{
			AsciiString name("Palantir/CommandUI/PortraitBackground");
			g_theWindowManager->removeAptObject(name);
		}

		index = 0;
		do
		{
			AsciiString name;
			char separator;
			bfmeGoVHH((char)index, (BfmeLayoutVHH *)&name);
			separator = '/';
			((StringBase<char> *)&name)->concat(&separator, 1);
			g_theWindowManager->removeAptObject(
				AsciiString("Palantir/") + name);
			((StringBase<char> *)&name)->concat("Timer", 5);
			callWindowManagerString(g_theWindowManager, j_0003d54b, &name);
			++index;
		} while (index < 6);
	}

	if (m_active)
	{
		j_00001f32();
		m_active = false;
	}
}

// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /D_STLP_USE_STATIC_LIB
// stlport
// WindowManager, retail 0x0046E170 (ILT 0x0000364D, called by WindowManager::update 0x0046E850):
// once +0x1A4 is set, formats the focused APT level path and sends "OnFocus" 1/0 to each
// loaded window record whose focus bit differs from the level on top of the +0x198 vector.

#include <hash_map>
#include <vector>

typedef int Int;
typedef bool Bool;

template <typename T> class StringBase
{
	friend class AsciiString;

private:
	StringBase() : m_data(0) {}
	StringBase(const T *text);
	~StringBase() { releaseBuffer(); }

	void releaseBuffer();

	void *m_data;
};

class AsciiString : private StringBase<char>
{
public:
	AsciiString() : StringBase<char>() {}
	AsciiString(const char *text) : StringBase<char>(text) {}
	~AsciiString() {}

	void __cdecl format(AsciiString format, ...);
};

namespace rts
{
	template <class T>
	struct hash
	{
		unsigned int operator()(T value) const;
	};
}

inline bool operator==(const AsciiString &left, const AsciiString &right)
{
	return *(const void * const *)&left == *(const void * const *)&right;
}

enum Rva00469D20Mapped
{
	Rva00469D20MappedZero = 0
};

// The movie-file map WindowManager::loadAptWindow fills; _M_find is pinned at ILT 0x00014D49.
typedef _STL::hash_map<AsciiString, Rva00469D20Mapped,
	rts::hash<AsciiString>, _STL::equal_to<AsciiString>,
	_STL::allocator<_STL::pair<const AsciiString, Rva00469D20Mapped> > >
	Rva00469D20Map;

class Rva0036CA00Str
{
private:
	void *m_item;
};

// Flag byte of an APT window record: loadAptWindow sets bit 0, this body tests bit 1 and syncs bit 3.
struct Rva004666C0Flags
{
	Bool m_bit0 : 1;
	Bool m_bit1 : 1;
	Bool m_bit2 : 1;
	Bool m_hasFocus : 1;
};

// One of the twelve 0x14-byte APT window records at WindowManager+0xA8.
struct Rva004666C0
{
	Rva0036CA00Str m_directory;
	Rva0036CA00Str m_file;
	Int m_parameter;
	Int m_index;
	Rva004666C0Flags m_flags;
};

class WindowManager
{
public:
	void bfmeRva0046E170();

	// TU-local lookup for this body's file-to-window map.
	Int lookupFileWindowIndex(const AsciiString &movie)
	{
		Rva00469D20Map::iterator it = m_fileToWindow.find(movie);
		if (it == m_fileToWindow.end())
			return -1;
		return (*it).second;
	}

	void unidentified_00015235(int movie, const char *function, int argumentCount,
		const void *argument1, const void *argument2 = 0, int unused1 = 0,
		int unused2 = 0, int unused3 = 0);

private:
	void *m_vtable;
	unsigned int m_name;
	unsigned char m_unreconstructed08[0x58 - 0x08];
	Rva00469D20Map m_fileToWindow;
	unsigned char m_unreconstructed6C[0xA8 - 0x6C];
	Rva004666C0 m_aptWindows[12];
	_STL::vector<Int> m_at198;
	Bool m_needsRefresh;
};

void WindowManager::bfmeRva0046E170()
{
	if (!m_needsRefresh)
		return;
	m_needsRefresh = false;

	Int &focus = m_at198.back();
	if (focus != 12)
	{
		if (focus == -1)
		{
			AsciiString path;
			path.format("/_level%d", lookupFileWindowIndex(AsciiString("AptLevel0.apt")));
		}
		else
		{
			AsciiString path;
			path.format("/_level%d", focus);
		}
	}

	for (Int i = 0; i < 12; ++i)
	{
		Rva004666C0Flags &flags = m_aptWindows[i].m_flags;
		if (flags.m_bit1)
		{
			Bool focused = focus != 12 ? (focus != -1 ? focus == i : false) : true;
			if (focused != flags.m_hasFocus)
			{
				flags.m_hasFocus = focused;
				unidentified_00015235(i, "OnFocus", 1, focused ? "1" : "0", 0, 0, 0, 0);
			}
		}
	}
}

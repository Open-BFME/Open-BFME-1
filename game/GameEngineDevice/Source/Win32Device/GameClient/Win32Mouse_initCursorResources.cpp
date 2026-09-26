// cl: /O2 /DNDEBUG /DWIN32 /MD /EHsc /Igame/Libraries/Source/WWVegas/WWLib
//
// Win32Mouse::initCursorResources, retail 0x006BC360 (367 bytes).
//
// The reference implementation is Win32Mouse.cpp in
// inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD.  BFME retains its resource
// table walk but copies the texture name, accepts a trailing .cur, strips it,
// and selects the cur/ani extension before calling the Win32 loader.

typedef int Int;
typedef bool Bool;

// This is the BFME StringBase layout used by the already matched WWLib bodies.
// Keeping the wrapper local makes the copy and release lifetimes explicit while
// leaving the shared StringBase implementation and headers untouched.
class BFMERetailAsciiString;

template <typename T>
class StringBase
{
	friend class BFMERetailAsciiString;

private:
	struct Header
	{
		int ref_count;
		unsigned short length;
		unsigned short capacity;
		T data[1];
	};

	StringBase() : m_data(0) {}
	StringBase(const StringBase<T> &source);
	void releaseBuffer();
	Header *m_data;

public:
	bool endsWithNoCase(const T *text, Int length) const;
	void removeLastChar();
};

class BFMERetailAsciiString : private StringBase<char>
{
public:
	BFMERetailAsciiString() : StringBase<char>() {}
	BFMERetailAsciiString(const BFMERetailAsciiString &source)
		: StringBase<char>(source)
	{
	}
	~BFMERetailAsciiString() { releaseBuffer(); }

	Bool isEmpty() const
	{
		return m_data == 0 || m_data->length == 0;
	}

	const char *str() const
	{
		return m_data ? &m_data->data[0] : "";
	}

	Bool endsWithNoCase(const char *text, Int length) const
	{
		return StringBase<char>::endsWithNoCase(text, length);
	}

	void removeLastChar()
	{
		StringBase<char>::removeLastChar();
	}
};

struct RGBAColorInt
{
	Int component[4];
};

struct ICoord2D
{
	Int x;
	Int y;
};

// CursorInfo's field order and 0x54 stride are from the named upstream
// Mouse.h.  Only textureName (+0x28) and numDirections (+0x50) are consumed by
// this body; the intervening fields are retained to make those offsets real.
struct CursorInfo
{
	BFMERetailAsciiString cursorName;
	BFMERetailAsciiString cursorText;
	RGBAColorInt cursorTextColor;
	RGBAColorInt cursorTextDropColor;
	BFMERetailAsciiString textureName;
	BFMERetailAsciiString imageName;
	BFMERetailAsciiString W3DModelName;
	BFMERetailAsciiString W3DAnimName;
	float W3DScale;
	Bool loop;
	ICoord2D hotSpotPosition;
	Int numFrames;
	float fps;
	Int numDirections;
};

// SubsystemInterface contributes the vptr and its one AsciiString member,
// putting Mouse::m_cursorInfo at +0x8.  Mouse::NUM_MOUSE_CURSORS is 50 in
// BFME; the first real cursor is slot 1.  The pure slot keeps this TU from
// emitting a replacement vtable for a class whose table is owned elsewhere.
class Mouse
{
public:
	enum
	{
		FIRST_CURSOR = 1,
		NUM_MOUSE_CURSORS = 50,
	};

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
	BFMERetailAsciiString m_name;
	CursorInfo m_cursorInfo[NUM_MOUSE_CURSORS];
};

class Win32Mouse : public Mouse
{
public:
	virtual void initCursorResources(void);
};

extern "C" void *g_cursorResources[][8];
extern "C" __declspec(dllimport) int __cdecl sprintf(char *buffer, const char *format, ...);
extern "C" __declspec(dllimport) void *__stdcall LoadCursorFromFileA(const char *path);

void Win32Mouse::initCursorResources(void)
{
	for (Int cursor = FIRST_CURSOR; cursor < NUM_MOUSE_CURSORS; ++cursor)
	{
		for (Int direction = 0; direction < m_cursorInfo[cursor].numDirections; ++direction)
		{
			if (!g_cursorResources[cursor][direction] && !m_cursorInfo[cursor].textureName.isEmpty())
			{
				char resourcePath[256];
				const char *extension = "ani";
				BFMERetailAsciiString textureName(m_cursorInfo[cursor].textureName);

				if (textureName.endsWithNoCase(".cur", 4))
				{
					extension = "cur";
					textureName.removeLastChar();
					textureName.removeLastChar();
					textureName.removeLastChar();
					textureName.removeLastChar();
				}

				if (m_cursorInfo[cursor].numDirections > 1)
					sprintf(resourcePath, "data\\cursors\\%s%d.%s", textureName.str(), direction, extension);
				else
					sprintf(resourcePath, "data\\cursors\\%s.%s", textureName.str(), extension);

				g_cursorResources[cursor][direction] = LoadCursorFromFileA(resourcePath);
			}
		}
	}
}

// ?resetGrid@Rva006D23C0Owner@@QAEXXZ
// The retail 0x006CCDB0 body is reached with the same owner in ECX.  Its
// first buffer call is the already matched +184 offset-tail member at
// 0x007326F0, and its owned +0x30BC object is the matched TaintBuffer
// destructor.  Keep the strings as real one-pointer, by-value narrow string views;
// their update methods are the two existing BFME bodies at 0x006CBA30 and
// 0x006CB8D0.

template <typename T> struct StringInlineData
{
	int m_refCount;
	unsigned short m_length;
	unsigned short m_capacity;
	T m_text[1];
};

template <typename T> class StringBase
{
public:
	StringBase(const StringBase &other);
	~StringBase();

private:
	StringInlineData<T> *m_data;
	friend class AsciiString;
	friend class BaseHeightMapResetAsciiString;
};

class AsciiString : private StringBase<char>
{
public:
	AsciiString(const AsciiString &other)
		: StringBase<char>(other)
	{
	}
	~AsciiString() {}
};

class BaseHeightMapResetAsciiString : private StringBase<char>
{
public:
	BaseHeightMapResetAsciiString(const BaseHeightMapResetAsciiString &other)
		: StringBase<char>(other)
	{
	}
	~BaseHeightMapResetAsciiString() {}
};

class Rva007326F0
{
public:
	void invoke();
};

class TaintBuffer
{
public:
	~TaintBuffer();
};

void __cdecl operator delete(void *);

struct Rva006D23C0GlobalData
{
	char m_prefix[0x38];
	bool m_38;
	char m_betweenFlags[0x44 - 0x39];
	bool m_44;
	char m_unmodeled[0xcf5 - 0x45];
	bool m_taintOn;
};

struct Rva006D23C0Cell { char m_bytes[0xc4]; };

class Rva006D23C0Owner
{
public:
	void refreshTerrainState();
	void resetGrid();
	void updateTexture(AsciiString textureName);
	void updateMacroTexture(BaseHeightMapResetAsciiString textureName, bool force);

private:
	char m_prefix[0x306c];
	bool m_force;
	BaseHeightMapResetAsciiString m_macroTextureName;
	AsciiString m_textureName;
	char m_unmodeledBeforeBuffers[0x3094 - 0x3078];
	Rva007326F0 *m_buffer3094;
	Rva007326F0 *m_buffer3098;
	char m_unmodeledBeforeTaint[0x30bc - 0x309c];
	TaintBuffer *m_taintBuffer;
	char m_unmodeledBeforeCells[0x30d8 - 0x30c0];
	Rva006D23C0Cell *m_cells;
	int m_30dc;
	int m_width;
	int m_height;
};

class BfmeThingBKF { public: void bfmeGoBKF(); };
extern Rva006D23C0GlobalData* TheWritableGlobalData;

void Rva006D23C0Owner::refreshTerrainState()
{
	if (m_buffer3094)
		m_buffer3094->invoke();
	if (m_buffer3098)
		m_buffer3094->invoke();
	TheWritableGlobalData->m_taintOn = false;
	if (m_taintBuffer) {
		delete m_taintBuffer;
		m_taintBuffer = 0;
	}
	updateTexture(m_textureName);
	updateMacroTexture(m_macroTextureName, m_force);
}

void Rva006D23C0Owner::resetGrid()
{
	refreshTerrainState();
	TheWritableGlobalData->m_38 = false;
	TheWritableGlobalData->m_44 = false;
	for (int x = 0; x < m_width; ++x) {
		for (int y = 0; y < m_height; ++y)
			((BfmeThingBKF*)&m_cells[y * m_width + x])->bfmeGoBKF();
	}
}

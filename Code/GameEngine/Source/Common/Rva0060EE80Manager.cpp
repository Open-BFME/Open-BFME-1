// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc
//
// Scratch reconstruction of retail RVA 0x0060EE80.  The manager receiver is
// proven by the direct ILT call from BfmeLivingWorldManager::update at
// 0x006174D0.  Keep the unproven method and fields address-qualified.
//
// The explicit else scope is intentional.  It reproduces retail's false-path
// EH marker at [esp+0x18]; spelling this as an early return emits [esp+0x14].

typedef bool Bool;

template <typename T> class StringBase
{
	friend class AsciiString;
	friend class UnicodeString;

private:
	StringBase() : m_data(0) {}
	StringBase(const T *text);
	StringBase(const StringBase &other);
	void releaseBuffer();
	void *m_data;
};

class AsciiString : private StringBase<char>
{
public:
	AsciiString() : StringBase<char>() {}
	AsciiString(const char *text)
		: StringBase<char>(text) {}
	AsciiString(const AsciiString &other)
		: StringBase<char>(other) {}
	~AsciiString() { releaseBuffer(); }
	void __cdecl format(AsciiString format, ...);
};

class UnicodeString : private StringBase<unsigned short>
{
public:
	static UnicodeString TheEmptyString;
	UnicodeString() : StringBase<unsigned short>() {}
	UnicodeString(const UnicodeString &other)
		: StringBase<unsigned short>(other) {}
	~UnicodeString() { releaseBuffer(); }
	void translate(const AsciiString &text);
};

struct Rva0060EE80Coord3D
{
	float x;
	float y;
	float z;
};

struct RGBAColorInt
{
	unsigned int red;
	unsigned int green;
	unsigned int blue;
	unsigned int alpha;
};

class Rva0060EE80State
{
public:
	virtual void slot00() = 0;
	virtual void slot04() = 0;
	virtual void slot08() = 0;
	virtual void slot0C() = 0;
	virtual void slot10() = 0;
	virtual void slot14() = 0;
	virtual void slot18() = 0;
	virtual void slot1C() = 0;
	virtual void buildFramePoint(void *source, Rva0060EE80Coord3D *point) = 0;
};

extern Rva0060EE80State *g_bfmeStateDF;

struct Rva0060EE80Global
{
	unsigned char m_prefix[0x20];
};

extern Rva0060EE80Global *g_rva0060EE80Global;

class Mouse
{
public:
	void setMouseText(UnicodeString text,
		const RGBAColorInt *color,
		const RGBAColorInt *dropColor);
};

extern Mouse *TheMouse;

class Rva0060EE80Manager
{
public:
	void rva0060ee80();

private:
	unsigned char m_prefix[0x295];
	Bool m_flag295;
};

void Rva0060EE80Manager::rva0060ee80()
{
	if (!m_flag295)
	{
		TheMouse->setMouseText(
			UnicodeString::TheEmptyString, 0, 0);
		return;
	}
	else
	{
	Rva0060EE80Coord3D point;
	g_bfmeStateDF->buildFramePoint(
		reinterpret_cast<unsigned char *>(g_rva0060EE80Global) + 0x20,
		&point);

	AsciiString text;
	text.format("X:%d, Y:%d <<< World position coordinate >>",
		(int)point.x, (int)point.y);

	UnicodeString translated;
	translated.translate(text);

	RGBAColorInt color = { 255, 32, 255, 255 };
	RGBAColorInt dropColor = { 0, 0, 0, 255 };
	TheMouse->setMouseText(translated, &color, &dropColor);
}

}

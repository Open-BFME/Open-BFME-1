// ?init@W3DBridge@@QAEXVVector3@@0VAsciiString@@@Z
// partial score=0.93 date=2026-09-02
// cl: /DNDEBUG /MD /EHsc
// W3DBridge::init, retail 0x006D8920 (131 bytes).
// Three-float start, three-float end, AsciiString name copied to +0x108,
// enabled byte at +0x110. ret 0x1C.

template <typename T> struct StringInlineData
{
	int m_refCount;
	int m_length;
	T m_text[1];
};

template <typename T> class StringBase
{
	friend class AsciiString;

private:
	StringBase() : m_data(0) {}
	StringBase(const StringBase<T> &other);
	~StringBase();

	StringInlineData<T> *m_data;
};

class AsciiString : private StringBase<char>
{
public:
	AsciiString() : StringBase<char>() {}
	AsciiString(const AsciiString &other) : StringBase<char>(other) {}
	~AsciiString() {}
	void set(const AsciiString &other);
	AsciiString &operator=(const AsciiString &other)
	{
		set(other);
		return *this;
	}
};

class Vector3
{
public:
	float X, Y, Z;
};

class W3DBridge
{
public:
	void init(Vector3 fromLoc, Vector3 toLoc, AsciiString bridgeTemplateName);

private:
	float m_startX;
	float m_startY;
	float m_startZ;
	float m_endX;
	float m_endY;
	float m_endZ;
	unsigned char m_unmodelled_018[0x108 - 0x18];
	AsciiString m_templateName;
	unsigned char m_unmodelled_10C[0x110 - 0x10C];
	unsigned char m_enabled;
};

void W3DBridge::init(Vector3 fromLoc, Vector3 toLoc, AsciiString bridgeTemplateName)
{
	m_startX = fromLoc.X;
	m_startY = fromLoc.Y;
	m_startZ = fromLoc.Z;
	m_endX = toLoc.X;
	m_endY = toLoc.Y;
	m_endZ = toLoc.Z;
	m_templateName = bridgeTemplateName;
	m_enabled = true;
}

// cl: /DNDEBUG /MD /EHsc

template <typename T>
class StringBase
{
	friend class AsciiString;

private:
	StringBase(const T *text);
	StringBase(const StringBase<T> &other);
	~StringBase(void);

	unsigned char *m_data;
};

class AsciiString : private StringBase<char>
{
public:
	AsciiString(const char *text) : StringBase<char>(text) {}
	AsciiString(const AsciiString &other) : StringBase<char>(other) {}
	~AsciiString(void) {}

	bool isNotEmpty(void) const
	{
		return m_data != 0 && *(const unsigned short *)(m_data + 4) != 0;
	}
};

AsciiString operator+(AsciiString left, const AsciiString &right);

class Image;

class ImageCollection
{
public:
	const Image *findImageByName(const AsciiString &name);
};

extern ImageCollection *TheMappedImageCollection;

// The only retail caller reaches this body through ILT 0x0004A7F5 from
// 0x00598D61.  Its receiver is the subobject at caller-this+0x460, and the
// result is written at subobject+0x1C.  The neighbouring 0x00592A90 body does
// the same ResourceBar_ lookup for the caller-this+0x488 subobject, but writes
// its result at +0x2C.  The original helper type name is not recoverable from
// those facts, so keep the owner address-derived.
class Rva00592570ResourceImageSlot
{
public:
	void cacheResourceImage(const AsciiString &suffix);

private:
	unsigned char m_beforeResourceImage[0x1c];
	const Image *m_resourceImage;
};

// ?cacheResourceImage@Rva00592570ResourceImageSlot@@QAEXABVAsciiString@@@Z
void Rva00592570ResourceImageSlot::cacheResourceImage(const AsciiString &suffix)
{
	if (suffix.isNotEmpty())
		m_resourceImage = TheMappedImageCollection->findImageByName(AsciiString("ResourceBar_") + suffix);
	else
		m_resourceImage = 0;
}

class Rva00592A90ResourceImageSlot
{
public:
	void cacheResourceImage(const AsciiString &suffix);

private:
	bool m_helpBoxShown;
	unsigned char m_beforeResourceImage[0x2b];
	const Image *m_resourceImage;
};

class Rva00564A10
{
public:
	static void go();
};

// ?cacheResourceImage@Rva00592A90ResourceImageSlot@@QAEXABVAsciiString@@@Z
void Rva00592A90ResourceImageSlot::cacheResourceImage(const AsciiString &suffix)
{
	if (m_helpBoxShown)
	{
		Rva00564A10::go();
		m_helpBoxShown = false;
	}

	if (suffix.isNotEmpty())
		m_resourceImage = TheMappedImageCollection->findImageByName(AsciiString("ResourceBar_") + suffix);
	else
		m_resourceImage = 0;
}

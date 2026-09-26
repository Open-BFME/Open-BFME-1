// cl: /DNDEBUG /MD /EHsc /O2 /Ob2 /Igame/Libraries/Source/WWVegas/WWLib
//
// Vtable 0x010F9BBC slot 2 of the three-string object whose constructor
// (0x00491880) and destructor (0x00491940) are matched; the method identity
// stays address-derived.

#include "ascii_string.h"
#include "unicode_string.h"

// Retail inlines the emptiness test (cmp word ptr [data+4],0) and the
// destructor (a direct StringBase<char>::releaseBuffer call) at these sites;
// the bodies are StringBase.cpp's and ascii_string.cpp's.
template <> inline bool StringBase<char>::isEmpty() const
{
	return m_data == 0 || m_data->length == 0;
}
template <> inline bool StringBase<char>::isNotEmpty() const
{
	return !isEmpty();
}
inline AsciiString::~AsciiString() { ((StringBase<char> *)this)->releaseBuffer(); }

// Retail copies the by-value text with a direct StringBase<unsigned short>
// copy-constructor call and destroys it with a direct releaseBuffer call, so
// both are inline here (unicode_string.h declares them out of line).
inline UnicodeString::UnicodeString(const UnicodeString &that)
{
	((StringBase<unsigned short> *)this)->StringBase<unsigned short>::StringBase(
		*(const StringBase<unsigned short> *)&that);
}
inline UnicodeString::~UnicodeString() { ((StringBase<unsigned short> *)this)->releaseBuffer(); }

struct ICoord2D
{
	int x;
	int y;
};

// name_oracle: Image+0x28 is m_imageSize.y (layout witness).
class Image
{
private:
	char m_unmodelled00[0x24];

public:
	int getImageHeight() const { return m_imageSize.y; }

	ICoord2D m_imageSize;
};

class ImageCollection
{
public:
	const Image *findImageByName(const AsciiString &name);
};

class GameFont;
class FontLibrary
{
public:
	GameFont *getFont(AsciiString *name, float pointSize, unsigned char bold);
};

class Display
{
public:
	virtual void slot00(); virtual void slot04(); virtual void slot08(); virtual void slot0C();
	virtual void slot10(); virtual void slot14(); virtual void slot18(); virtual void slot1C();
	virtual void slot20(); virtual void slot24(); virtual void slot28(); virtual void slot2C();
	virtual void slot30(); virtual void slot34(); virtual void slot38(); virtual void slot3C();
	virtual void slot40(); virtual void slot44(); virtual void slot48(); virtual void slot4C();
	virtual void slot50(); virtual void slot54(); virtual void slot58(); virtual void slot5C();
	virtual void slot60(); virtual void slot64(); virtual void slot68(); virtual void slot6C();
	virtual void slot70(); virtual void slot74(); virtual void slot78(); virtual void slot7C();
	virtual void slot80(); virtual void slot84(); virtual void slot88(); virtual void slot8C();
	virtual void slot90(); virtual void slot94(); virtual void slot98(); virtual void slot9C();
	virtual void slotA0(); virtual void slotA4(); virtual void slotA8(); virtual void slotAC();
	virtual void slotB0(); virtual void slotB4(); virtual void slotB8(); virtual void slotBC();
	virtual void slotC0(); virtual void slotC4(); virtual void slotC8(); virtual void slotCC();
	virtual void slotD0(); virtual void slotD4(); virtual void slotD8(); virtual void slotDC();
	virtual void slotE0(); virtual void slotE4(AsciiString name, int a, int b, int c);
	virtual void slotE8(); virtual void slotEC(); virtual void slotF0(); virtual void slotF4();
	virtual void slotF8(); virtual void slotFC(AsciiString name, int value);

	void rva002ED2E0(float a, float b, float c, float d);
};

// Receiver is TheDisplay. The callee at 0x0040E0D0 multiplies its four
// trailing dwords by the receiver's width and height, so they are floats.
class BfmeThingVMZ
{
public:
	void bfmeGo1VMZ(int image, int index, float a, float b, float c, float d);
};

class BfmeObjEE
{
public:
	void bfmeSetF0B0(UnicodeString text, int a, int b, int c, int d, int e);
};

struct Rva005A00B0AudioClient
{
public:
	virtual void slot00(); virtual void slot04(); virtual void slot08(); virtual void slot0C();
	virtual void slot10(); virtual void slot14(); virtual void slot18(); virtual void slot1C();
	virtual void slot20(); virtual void slot24(); virtual void slot28(); virtual void slot2C();
	virtual void slot30(); virtual void slot34(); virtual void slot38(); virtual void slot3C(int value);
};

class GameLogic
{
private:
	char m_unmodelled00[0x74];

public:
	unsigned char m_byte74;
};

class GlobalData
{
private:
	char m_unmodelled0000[0x1278];

public:
	unsigned char m_byte1278;
};

class GameTextInterface
{
public:
	virtual void slot00(); virtual void slot04(); virtual void slot08(); virtual void slot0C();
	virtual void slot10(); virtual void slot14(); virtual void slot18(); virtual void slot1C();
	virtual void slot20(); virtual UnicodeString fetch(AsciiString label, bool *exists);
};

class Rva00491110
{
public:
	void startAudio();
};

class Rva00490470
{
public:
	virtual ~Rva00490470();

private:
	char m_unmodelled04[0xC];
};

class Gen_00491880 : public Rva00490470
{
public:
	virtual ~Gen_00491880(void);
	virtual void rva00491A40(int unused);

private:
	AsciiString m_bfmeFirst;	// +0x10, the first string the matched constructor copies
};

extern ImageCollection *TheMappedImageCollection;
extern Display *TheDisplay;
extern Rva005A00B0AudioClient *TheAudioClientUpdate;
extern GameLogic *TheBfmeGameLogic;
extern GlobalData *TheWritableGlobalData;
extern FontLibrary *TheFontLibrary;
extern GameTextInterface *TheGameText;

// ?rva00491A40@Gen_00491880@@UAEXH@Z
void Gen_00491880::rva00491A40(int unused)
{
	TheAudioClientUpdate->slot3C(2);
	TheAudioClientUpdate->slot14();

	AsciiString foreground("LoadScreenForeground");
	const Image *image = TheMappedImageCollection->findImageByName(foreground);
	if (image != 0)
		((BfmeThingVMZ *)TheDisplay)->bfmeGo1VMZ((int)image, 2, 0.0f, 0.0f, 1.0f, 1.0f);

	if (m_bfmeFirst.isNotEmpty())
	{
		const Image *picture = TheMappedImageCollection->findImageByName(m_bfmeFirst);
		if (picture != 0)
		{
			int height = picture->getImageHeight();
			((BfmeThingVMZ *)TheDisplay)->bfmeGo1VMZ((int)picture, 0, 0.0f, 0.1640625f, 1.0f,
				(float)height / 768.0f + 0.1640625f);
		}
	}

	TheBfmeGameLogic->m_byte74 = 1;
	TheDisplay->rva002ED2E0(0.46826171875f, 0.8756510615f, 0.53076171875f, 0.958984375f);

	AsciiString smallRing("SmallRing");
	if (TheWritableGlobalData->m_byte1278 == 0)
	{
		if (TheDisplay != 0)
			TheDisplay->slotFC(smallRing, 0x14);
	}
	else
	{
		TheDisplay->slotE4(smallRing, 0x14, -1, -1);
	}

	// The body at 0x00491110 works on this object's +0x14/+0x18 strings.
	((Rva00491110 *)this)->startAudio();

	bool exists = false;
	GameFont *font;
	{
		AsciiString fontName("SachaWynter");
		font = TheFontLibrary->getFont(&fontName, 18.0f, 0);
	}

	UnicodeString text = TheGameText->fetch("GUI:Loading", &exists);
	((BfmeObjEE *)TheDisplay)->bfmeSetF0B0(text, 0x3f000000, 0x3d000000, (int)font, 0xffffd554, 0);
}

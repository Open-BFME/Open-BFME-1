// ?d_00491a40@@YAXXZ
// partial score=0.9 date=2026-09-22
// cl: /DNDEBUG /MD /EHsc /O2 /Ob2 /ICode/Libraries/Source/WWVegas/WWLib
// Retail slot-2 method on the three-string object at 0x00491A40.

class AsciiString
{
private:
	void *m_data;
};

#include "string_base.h"

class UnicodeString : private StringBase<unsigned short>
{
public:
	UnicodeString();
	UnicodeString(const UnicodeString &other);
	~UnicodeString();
};

class BFMERetailAsciiString
{
private:
	struct StringData
	{
		int m_refCount;
		unsigned short m_length;
		unsigned short m_capacity;
		char m_text[1];
	};

public:
	BFMERetailAsciiString(const char *text);
	BFMERetailAsciiString(const BFMERetailAsciiString &other);
	~BFMERetailAsciiString() { releaseBuffer(); }

	bool isNotEmpty() const
	{
		const StringData *data = *(const StringData * const *)this;
		return data != 0 && data->m_length != 0;
	}

private:
	void releaseBuffer();
	void *m_data;
};

class BfmeStringArgBase
{
	friend class BfmeAsciiStringArg;

private:
	BfmeStringArgBase(const BfmeStringArgBase &other);
	~BfmeStringArgBase();
};

class BfmeAsciiStringArg
{
public:
	BfmeAsciiStringArg(const BFMERetailAsciiString &that)
	{
		((BfmeStringArgBase *)this)->BfmeStringArgBase::BfmeStringArgBase(
			*(const BfmeStringArgBase *)&that);
	}
	~BfmeAsciiStringArg();

private:
	char *m_text;
};

class Image
{
private:
	char m_padding[0x28];

public:
	int m_height;
};
class ImageCollection
{
public:
	const Image *findImageByName(const AsciiString &name);
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
	virtual void slotE0(); virtual void slotE4(BfmeAsciiStringArg name, int a, int b, int c);
	virtual void slotE8(); virtual void slotEC(); virtual void slotF0(); virtual void slotF4();
	virtual void slotF8(); virtual void slotFC(BfmeAsciiStringArg name, int value);

	void rva002ED2E0(float a, float b, float c, float d);
};

class AudioClientUpdate
{
public:
	virtual void slot00(); virtual void slot04(); virtual void slot08(); virtual void slot0C();
	virtual void slot10(); virtual void slot14(); virtual void slot18(); virtual void slot1C();
	virtual void slot20(); virtual void slot24(); virtual void slot28(); virtual void slot2C();
	virtual void slot30(); virtual void slot34(); virtual void slot38(); virtual void slot3C(int value);
};

class BfmeThingVMZ
{
public:
	void bfmeGo1VMZ(int image, int index, int left, float top, float scale, float height);
};

class GameLogic
{
public:
	char m_padding[0x74];
	unsigned char m_flag;
};

class GlobalData
{
public:
	char m_padding[0x1278];
	unsigned char m_flag;
};

class FontLibrary
{
public:
	class GameFont;
	GameFont *getFont(BFMERetailAsciiString *name, float pointSize, unsigned char bold);
};

class GameTextInterface
{
public:
	virtual void slot00(); virtual void slot04(); virtual void slot08(); virtual void slot0C();
	virtual void slot10(); virtual void slot14(); virtual void slot18(); virtual void slot1C();
	virtual void slot20(); virtual UnicodeString fetch(BFMERetailAsciiString label, bool *exists = 0);
};

class BfmeObjEE
{
public:
	void bfmeSetF0B0(UnicodeString text, int a, int b, int c, int d, int e);
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
	Rva00490470 *m_next;
	int m_count;
	bool m_armed;
	char m_padding[3];
};

class Gen_00491880 : public Rva00490470
{
public:
	virtual ~Gen_00491880();
	virtual void rva00491A40(int unused);

private:
	BFMERetailAsciiString m_imageName;
	BFMERetailAsciiString m_firstEventName;
	BFMERetailAsciiString m_secondEventName;
	int m_firstHandle;
	int m_secondHandle;
};

extern ImageCollection *TheMappedImageCollection;
extern Display *TheDisplay;
extern AudioClientUpdate *TheAudioClientUpdate;
extern GameLogic *TheBfmeGameLogic;
extern GlobalData *TheWritableGlobalData;
extern FontLibrary *TheFontLibrary;
extern GameTextInterface *TheGameText;

// ?rva00491A40@Gen_00491880@@UAEXH@Z
void Gen_00491880::rva00491A40(int unused)
{
	TheAudioClientUpdate->slot3C(2);
	TheAudioClientUpdate->slot14();

	int height;
	BFMERetailAsciiString foreground("LoadScreenForeground");
	int foregroundImage = (int)TheMappedImageCollection->findImageByName(
		*(const AsciiString *)&foreground);
	if (foregroundImage != 0)
	{
		((BfmeThingVMZ *)TheDisplay)->bfmeGo1VMZ(
			foregroundImage, 2, 0, 0, 1.0f, 1.0f);
	}

	if (m_imageName.isNotEmpty())
	{
		int image = (int)TheMappedImageCollection->findImageByName(
			*(const AsciiString *)&m_imageName);
		if (image != 0)
		{
			height = *(int *)(image + 0x28);
			((BfmeThingVMZ *)TheDisplay)->bfmeGo1VMZ(
				image, 0, 0, 0.1640625f, 1.0f,
				(float)height * *(float *)0x010f1620 + *(float *)0x010f9be8);
		}
	}

	TheBfmeGameLogic->m_flag = 1;
	TheDisplay->rva002ED2E0(0.46826171875f, 0.8756510615f,
		0.53076171875f, 0.958984375f);

	BFMERetailAsciiString smallRing("SmallRing");
	if (TheWritableGlobalData->m_flag == 0)
	{
		if (TheDisplay != 0)
			TheDisplay->slotFC(smallRing, 0x14);
	}
else
	{
		TheDisplay->slotE4(smallRing, 0x14, -1, -1);
	}

	((Rva00491110 *)this)->startAudio();

	BFMERetailAsciiString fontName("SachaWynter");
	class FontLibrary::GameFont *font = TheFontLibrary->getFont(&fontName, 18.0f, 0);

	BFMERetailAsciiString loading("GUI:Loading");
	UnicodeString text = TheGameText->fetch(loading);
	((BfmeObjEE *)TheDisplay)->bfmeSetF0B0(text,
		0x3f000000, 0x3d000000, (int)font, 0xffffd554, 0);
}

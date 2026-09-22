// Open-BFME5: opaque slot-2 method at retail 0x004916D0.
// Vtable 0x010F9B94 and the matched 0x00491580 constructor establish the receiver.
// The address-derived method name preserves the unresolved semantic identity.

// cl: /DNDEBUG /MD /EHsc /O2 /Ob2

class AsciiString
{
private:
	void *m_data;
};

struct StringData
{
	int m_refCount;
	unsigned short m_length;
	unsigned short m_capacity;
	char m_text[1];
};

class BFMERetailAsciiString
{
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

class Image;
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
	void bfmeGo1VMZ(int a0, int i, int a2, int a3, int a4, int a5);
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

class Gen_00491580 : public Rva00490470
{
public:
	virtual ~Gen_00491580();
	virtual void rva004916D0(int unused);

private:
	BFMERetailAsciiString m_first;
	BFMERetailAsciiString m_second;
};

extern ImageCollection *TheMappedImageCollection;
extern Display *TheDisplay;
extern AudioClientUpdate *TheAudioClientUpdate;
extern GameLogic *TheBfmeGameLogic;
extern GlobalData *TheWritableGlobalData;

// ?rva004916D0@Gen_00491580@@UAEXH@Z
void Gen_00491580::rva004916D0(int unused)
{
	if (m_first.isNotEmpty())
	{
		TheDisplay->rva002ED2E0(0.4677734375f, 0.8411458135f,
			0.5302734375f, 0.9244791865f);
		TheAudioClientUpdate->slot3C(2);
		TheAudioClientUpdate->slot14();
	}

	if (m_second.isNotEmpty())
	{
		((BfmeThingVMZ *)TheDisplay)->bfmeGo1VMZ(
			(int)TheMappedImageCollection->findImageByName(
				*(const AsciiString *)&m_second),
			2, 0, 0, 0x3f800000, 0x3f800000);
	}

	TheBfmeGameLogic->m_flag = 1;

	if (m_first.isNotEmpty())
	{
		BFMERetailAsciiString smallRing("SmallRing");
		if (TheWritableGlobalData->m_flag == 0)
		{
			if (TheDisplay != 0)
				TheDisplay->slotFC(smallRing, 4);
		}
		else
		{
			TheDisplay->slotE4(smallRing, 4, -1, -1);
		}
	}
}

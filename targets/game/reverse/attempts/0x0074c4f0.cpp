// ?rva0074C4F0@Rva0074C4F0Owner@@QAE?AVRva0074C4F0Handle@@HHHHI@Z
// partial score=0.824074 date=2026-09-24
// cl: /DNDEBUG /MD /EHsc

struct Rva006C9270GlobalData
{
	char pad[0x68];
	int textureReductionFactor;
};
extern Rva006C9270GlobalData *TheWritableGlobalData;

class WorldHeightMap;

class TextureBaseClass
{
public:
	void Release_Ref();
	char pad00[4];
	unsigned short refCount;
};

class Rva006D5280
{
public:
	Rva006D5280(unsigned width, unsigned height, unsigned format);
	~Rva006D5280()
	{
		if (m_texture)
			m_texture->Release_Ref();
	}
	TextureBaseClass *m_texture;
};

class Rva006D53A0TextureClass : public Rva006D5280
{
public:
	int Rva006D53A0Update(WorldHeightMap *, int, int, int, int);
};

class Rva006D5750TextureClass : public Rva006D5280
{
public:
	int Rva006D5750Update(WorldHeightMap *, int, int, int, int);
};

// This is scratch-only. tools/build.py does not honor /alternatename, so the
// masked probe is not a strict relocation gate. The three ILT routes below
// need independently validated resolver candidates before this can land.
#pragma comment(linker, "/alternatename:??0Rva006D5280@@QAE@III@Z=?j_000279ee@@YAXXZ")
#pragma comment(linker, "/alternatename:?Rva006D53A0Update@Rva006D53A0TextureClass@@QAEHPAVWorldHeightMap@@HHHH@Z=?j_0000c761@@YAXXZ")
#pragma comment(linker, "/alternatename:?Rva006D5750Update@Rva006D5750TextureClass@@QAEHPAVWorldHeightMap@@HHHH@Z=?j_00031e30@@YAXXZ")

class Rva0074C4F0Handle
{
public:
	explicit Rva0074C4F0Handle(TextureBaseClass *texture) : m_texture(texture)
	{
		if (texture)
			++texture->refCount;
	}
	TextureBaseClass *m_texture;
};

class Rva0074C4F0DebugMessage
{
public:
	virtual void slot00();
	virtual void slot04();
	virtual void slot08();
	virtual void slot0c();
	virtual void slot10();
	virtual void slot14();
	virtual void slot18();
	virtual void slot1c();
	virtual void slot20();
	virtual void slot24();
	virtual void slot28();
	virtual void slot2c();
	virtual void slot30();
	virtual void slot34();
	virtual Rva0074C4F0DebugMessage *slot38(const void *);
	virtual void slot3c();
	virtual void slot40();
	virtual void slot44();
	virtual void slot48();
	virtual void slot4c(int);
};

class BfmeAwakenDebug
{
public:
	virtual void slot00();
	virtual void slot04();
	virtual void slot08();
	virtual void slot0c();
	virtual void slot10();
	virtual void slot14();
	virtual void slot18();
	virtual void slot1c();
	virtual void slot20();
	virtual void slot24();
	virtual void slot28();
	virtual void slot2c();
	virtual void slot30();
	virtual void slot34();
	virtual void slot38();
	virtual void slot3c();
	virtual void slot40();
	virtual void slot44();
	virtual void slot48();
	virtual void slot4c();
	virtual void slot50();
	virtual void slot54();
	virtual void slot58();
	virtual void slot5c();
	virtual void slot60();
	virtual void slot64();
	virtual void slot68();
	virtual Rva0074C4F0DebugMessage *slot6c(int, int);
};

extern BfmeAwakenDebug *TheBfmeAwakenDebug;
extern bool _bfme_debugReportingEnabled();
extern void _bfme_debugRecordCallsite(int);

class Rva0074C4F0Owner
{
public:
	Rva0074C4F0Handle rva0074C4F0(int xCell, int yCell,
		int cellWidth, int pixelsPerCell, unsigned format);
};

Rva0074C4F0Handle Rva0074C4F0Owner::rva0074C4F0(int xCell, int yCell,
	int cellWidth, int pixelsPerCell, unsigned format)
{
	volatile int state = 0;
	int reduction = TheWritableGlobalData->textureReductionFactor;
	if (reduction)
	{
		if (reduction > 1)
			pixelsPerCell /= 4;
		else
			pixelsPerCell /= 2;
	}

	int powerOfTwo = 1;
	while (powerOfTwo < cellWidth * pixelsPerCell)
		powerOfTwo *= 2;

	Rva006D5280 texture(powerOfTwo, powerOfTwo, format);
	if (format == 0x19)
	{
		reinterpret_cast<Rva006D53A0TextureClass *>(&texture)->Rva006D53A0Update(
			reinterpret_cast<WorldHeightMap *>(this), xCell, yCell, cellWidth, pixelsPerCell);
	}
	else if (format == 0x31545844)
	{
		reinterpret_cast<Rva006D5750TextureClass *>(&texture)->Rva006D5750Update(
			reinterpret_cast<WorldHeightMap *>(this), xCell, yCell, cellWidth, pixelsPerCell);
	}
	else if (_bfme_debugReportingEnabled())
	{
		_bfme_debugRecordCallsite(1);
		TheBfmeAwakenDebug->slot60();
		TheBfmeAwakenDebug->slot6c(0, 0)->slot38(
			"Unsupported format for terrain texture")->slot4c(2);
	}
	return Rva0074C4F0Handle(texture.m_texture);
}

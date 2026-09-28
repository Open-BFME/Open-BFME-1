// cl: /DNDEBUG /MD /EHsc /Iinputs/reference/shims/sweep /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/debug /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib
// stlport

struct Rva001C4CC0Version
{
	unsigned char data[2];
	unsigned char padding[2];
};

class AsciiString;

class Rva001C4CC0XferView
{
public:
	virtual void slot00();
	virtual bool IsLoading();
	virtual bool IsStoring();
	virtual bool IsCRC();
	virtual bool IsLightCRC();
	virtual void slot05();
	virtual void slot06();
	virtual void slot07();
	virtual void slot08();
	virtual Rva001C4CC0XferView &xferUser(void *, unsigned int);
	virtual Rva001C4CC0XferView &xferVersion(Rva001C4CC0Version &);
	virtual void slot11();
	virtual void xferSnapshot(void *);
	virtual void slot13();
	virtual void slot14();
	virtual void slot15();
	virtual void slot16();
	virtual void slot17();
	virtual void slot18();
	virtual void slot19();
	virtual void slot20();
	virtual void slot21();
	virtual void slot22();
	virtual void slot23();
	virtual void slot24();
	virtual void slot25();
	virtual Rva001C4CC0XferView &xferAsciiString(AsciiString &);
	virtual void slot27();
	virtual void slot28();
	virtual Rva001C4CC0XferView &xferUnsignedInt(unsigned int &);
	virtual Rva001C4CC0XferView &xferInt(int &);
	virtual Rva001C4CC0XferView &xferUnsignedShort(unsigned short &);
	virtual void slot32();
	virtual void slot33();
	virtual void slot34();
	virtual Rva001C4CC0XferView &xferBool(bool &);
};

class Xfer;

template <unsigned int NUMBITS>
class BitFlags
{
public:
	void xfer(Xfer *xfer);
};

class BFMERetailAsciiString
{
public:
	BFMERetailAsciiString() { m_data = 0; }
	BFMERetailAsciiString(const char *text);
	~BFMERetailAsciiString() { releaseBuffer(); }

	void *m_data;

private:
	void releaseBuffer();
};

struct Rva001C4CC0FormattedText
{
	char *text;
	int tag;
};

extern unsigned char g_bfmeTableDH[];
extern int g_bfmeTableDJa[];
extern "C" Rva001C4CC0FormattedText *__cdecl bfmeFormatText(
	Rva001C4CC0FormattedText *, int, const char *, ...);
extern int __cdecl bfmeLookupA(void *name);
extern void __declspec(noreturn) __stdcall _CxxThrowException(void *, void *);
extern char Rva006A16B0Empty[];
extern int g_guardTargetTypeThrowInfo;

#pragma comment(linker, "/alternatename:?xfer@?$BitFlags@$0L@@@QAEXPAVXfer@@@Z=?j_00042ac3@@YAXXZ")

class Rva001C4CC0
{
public:
	void xfer(Rva001C4CC0XferView *xfer);

	unsigned int bits;
};

// ?xfer@Rva001C4CC0@@QAEXPAVRva001C4CC0XferView@@@Z
void Rva001C4CC0::xfer(Rva001C4CC0XferView *xfer)
{
	Rva001C4CC0Version version;
	version.data[0] = 1;
	version.data[1] = 1;
	xfer->xferVersion(version);
	if (xfer->IsLightCRC())
	{
		reinterpret_cast<BitFlags<11> *>(this)->xfer(reinterpret_cast<Xfer *>(xfer));
		return;
	}

	if (xfer->IsStoring())
	{
		const unsigned char *cursor = reinterpret_cast<const unsigned char *>(this);
		const unsigned char *end = cursor + 4;
		int total = 0;
		while (cursor < end)
		{
			total += g_bfmeTableDH[*cursor];
			++cursor;
		}
		int checksum = total;
		xfer->xferInt(checksum);

		for (int bit = 0; bit < 11; ++bit)
		{
			if ((bits & (1 << (bit & 31))) != 0)
			{
				const char *name = reinterpret_cast<const char *>(g_bfmeTableDJa[bit]);
				if (name != 0)
				{
					BFMERetailAsciiString string(name);
					xfer->xferAsciiString(reinterpret_cast<AsciiString &>(string));
					--checksum;
				}
			}
		}
	}
	else
	{
		bits = 0;
		int count;
		xfer->xferInt(count);
		BFMERetailAsciiString string;
		for (int bit = 0; bit < count; ++bit)
		{
			xfer->xferAsciiString(reinterpret_cast<AsciiString &>(string));
			void *data = string.m_data;
			void *lookupName;
			if (data != 0)
				lookupName = reinterpret_cast<unsigned char *>(data) + 8;
			else
				lookupName = Rva006A16B0Empty;
			int flag = bfmeLookupA(lookupName);
			if (flag < 0)
			{
				Rva001C4CC0FormattedText error;
				bfmeFormatText(&error, 0, 0);
				_CxxThrowException(&error, &g_guardTargetTypeThrowInfo);
			}
			bits |= 1 << (flag & 31);
		}
	}
}

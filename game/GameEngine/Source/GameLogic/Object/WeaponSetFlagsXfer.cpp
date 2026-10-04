// cl: /DNDEBUG /MD /EHsc /Iinputs/reference/shims/sweep /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib
// stlport

struct BfmeWeaponVersion
{
	unsigned char data[2];
	unsigned char padding[2];
};

struct BfmeWeaponFormattedText
{
	char *text;
	int tag;
};

class AsciiString;

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

extern "C" BfmeWeaponFormattedText *__cdecl bfmeFormatText(
	BfmeWeaponFormattedText *, int, const char *, ...);
extern void __declspec(noreturn) __stdcall _CxxThrowException(void *, void *);
extern int g_guardTargetTypeThrowInfo;

class BfmeWeaponSetXferView
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
	virtual BfmeWeaponSetXferView &xferUser(void *, unsigned int);
	virtual BfmeWeaponSetXferView &xferVersion(BfmeWeaponVersion &);
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
	virtual BfmeWeaponSetXferView &xferAsciiString(AsciiString &);
	virtual void slot27();
	virtual void slot28();
	virtual BfmeWeaponSetXferView &xferUnsignedInt(unsigned int &);
	virtual BfmeWeaponSetXferView &xferInt(int &);
	virtual BfmeWeaponSetXferView &xferUnsignedShort(unsigned short &);
	virtual void slot32();
	virtual void slot33();
	virtual void slot34();
	virtual BfmeWeaponSetXferView &xferBool(bool &);
};

class Xfer;

template <unsigned int NUMBITS>
class BitFlags
{
public:
	void xfer(Xfer *xfer);
};

extern unsigned char g_bfmeTableDH[];
extern int g_bfmeTableDJc[];
int __cdecl bfmeLookupB(void *name);

// Retail routes this BitFlags<29>::xfer call through ILT thunk 0x000335BE
// (5-byte j_ thunk), so the call site names the thunk directly.
extern void j_000335be();

class BfmeWeaponSetFlags
{
public:
	void xfer(BfmeWeaponSetXferView *xfer);

	unsigned int bits;
};

// ?xfer@BfmeWeaponSetFlags@@QAEXPAVBfmeWeaponSetXferView@@@Z
void BfmeWeaponSetFlags::xfer(BfmeWeaponSetXferView *xfer)
{
	BfmeWeaponVersion version;
	version.data[0] = 1;
	version.data[1] = 1;
	xfer->xferVersion(version);
	if (xfer->IsLightCRC())
	{
		typedef void (BitFlags<29>::*Fn)(Xfer *);
		union { void (*fn)(); Fn call; } u = { j_000335be };
		(reinterpret_cast<BitFlags<29> *>(this)->*u.call)(reinterpret_cast<Xfer *>(xfer));
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

		for (int bit = 0; bit < 29; ++bit)
		{
			if ((bits & (1 << (bit & 31))) != 0)
			{
				const char *name = reinterpret_cast<const char *>(g_bfmeTableDJc[bit]);
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
				lookupName = "";
			int flag = bfmeLookupB(lookupName);
			if (flag < 0)
			{
				BfmeWeaponFormattedText error;
				bfmeFormatText(&error, 0, 0);
				_CxxThrowException(&error, &g_guardTargetTypeThrowInfo);
			}
			bits |= 1 << (flag & 31);
		}
	}
}

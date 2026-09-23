// ?xfer@Rva001CB270ModelConditionFlags@@QAEXPAVXfer@@@Z
// partial score=0.74 date=2026-09-23
// Scratch source for the 304-name Xfer body at 0x001CB270.
// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/sweep /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/debug /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main /ICode/Libraries/Source/WWVegas/WWMath
// stlport

#include <bitset>

typedef int Int;
typedef unsigned char UnsignedByte;
struct XferVersion
{
	UnsignedByte m_version;
	UnsignedByte m_currentVersion;
};
typedef bool Bool;

class BFMERetailAsciiString
{
public:
	BFMERetailAsciiString() : m_data(0) {}
	BFMERetailAsciiString(const char *text);
	~BFMERetailAsciiString() { releaseBuffer(); }
	const char *str() const
	{
		return m_data ? (const char *)((const unsigned char *)m_data + 8)
			: (const char *)0x0107388B;
	}
private:
	void releaseBuffer();
	void *m_data;
};

class Xfer
{
public:
	virtual void slot00();
	virtual void slot01();
	virtual Bool isSaving();
	virtual void slot03();
	virtual Bool isLightCRC();
	virtual void slot05();
	virtual void slot06();
	virtual void slot07();
	virtual void slot08();
	virtual void xferUser(void *data, Int size);
	virtual Xfer &xferVersion(XferVersion &version);
	virtual void slot11();
	virtual void slot12();
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
	virtual void xferAsciiString(BFMERetailAsciiString *value);
	virtual void slot27();
	virtual void slot28();
	virtual void slot29();
	virtual void xferInt(Int *value);
};

template <size_t N>
class BitFlags
{
public:
	Bool test(Int bit) const { return m_bits._Unchecked_test(bit); }
	void set(Int bit) { m_bits._Unchecked_set(bit); }
	void clear() { m_bits.reset(); }
	void xfer(Xfer *xfer);
private:
	_STL::bitset<N> m_bits;
};

struct XferException
{
	char *text;
	int tagValue;
};

extern "C" XferException *__cdecl bfmeFormatText(
	XferException *result, int tag, const char *format, ...);
extern void __declspec(noreturn) __stdcall _CxxThrowException(
	void *object, void *throwInfo);
extern int _g_xferExceptionThrowInfo;


extern "C" const char *const _bfmeGlobalTable12A6918[];
extern unsigned char g_bfmeTableDH[];
extern Int __cdecl Rva001CB270FindName(const char *text);

class Rva001CB270ModelConditionFlags
{
public:
	void xfer(Xfer *xfer);
private:
	BitFlags<304> m_flags;
};

void Rva001CB270ModelConditionFlags::xfer(Xfer *xfer)
{
	union VersionStorage
	{
		XferVersion version;
		UnsignedByte padding[4];
	} versionStorage;
	versionStorage.version.m_version = 1;
	versionStorage.version.m_currentVersion = 1;
	xfer->xferVersion(versionStorage.version);

	if (xfer->isLightCRC())
	{
		m_flags.xfer(xfer);
		return;
	}

	Bool saving = xfer->isSaving();
	Int population = 0;
	const unsigned char *point = (const unsigned char *)&m_flags;
	if (saving)
	{
		const unsigned char *end = point + 0x28;
		while (point < end)
			population += g_bfmeTableDH[*point++];
		Int count = population;
		xfer->xferInt(&count);
		for (register Int i = 0; i < 304; ++i)
		{
			if (m_flags.test(i))
			{
				const char *name = _bfmeGlobalTable12A6918[i];
				if (name != 0)
				{
					BFMERetailAsciiString bitName(name);
					xfer->xferAsciiString(&bitName);
				}
			}
		}
	}
	else
	{
		Int count;
		m_flags.clear();
		xfer->xferInt(&count);
		BFMERetailAsciiString name;
		for (Int i = 0; i < count; ++i)
		{
			xfer->xferAsciiString(&name);
			Int index = Rva001CB270FindName(name.str());
			if (index < 0)
			{
				XferException error;
				bfmeFormatText(&error, 0, 0);
				_CxxThrowException(&error, &_g_xferExceptionThrowInfo);
			}
			m_flags.set(index);
		}
	}
}

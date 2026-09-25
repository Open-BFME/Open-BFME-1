// ?xfer@Rva001CB270ModelConditionFlags@@QAEXPAVXfer@@@Z
// partial score=0.985887 date=2026-09-25
// Address-derived identity: the semantic owner of this model-condition flag
// transfer is not established by the available caller evidence.
// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/sweep /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/debug /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main /ICode/Libraries/Source/WWVegas/WWMath
// stlport

#include <bitset>

#include "../Code/Libraries/Source/WWVegas/WWLib/ascii_string.h"

typedef int Int;
typedef unsigned char UnsignedByte;
typedef bool Bool;

#include "../Code/GameEngine/Source/Common/System/xfer.h"

class XferException
{
public:
	XferException(Int tag, const char *format, ...);
	XferException(const XferException &that);
	~XferException();
	char *text;
	Int tagValue;
};

template <size_t N>
class BitFlags
{
public:
	Int count() const { return m_bits.count(); }
	Bool test(Int bit) const { return m_bits._Unchecked_test(bit); }
	void set(Int bit) { m_bits._Unchecked_set(bit); }
	void clear() { m_bits.reset(); }
	void xfer(Xfer *xfer);
private:
	_STL::bitset<N> m_bits;
};

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

inline AsciiString::~AsciiString()
{
	((StringBase<char> *)this)->releaseBuffer();
}

template <>
inline const char *StringBase<char>::str() const
{
	return m_data ? m_data->data : "";
}

void Rva001CB270ModelConditionFlags::xfer(Xfer *xfer)
{
	Xfer::Version version;
	version.data[0] = 1;
	version.data[1] = 1;
	*xfer == version;

	if (xfer->IsLightCRC())
	{
		m_flags.xfer(xfer);
		return;
	}

	Bool saving = xfer->IsStoring();
	if (saving)
	{
		Int count = m_flags.count();
		*xfer == count;
		for (register Int i = 0; i < 304; ++i)
		{
			if (m_flags.test(i))
			{
				const char *name = _bfmeGlobalTable12A6918[i];
				if (name != 0)
				{
					AsciiString bitName(name);
					*xfer == bitName;
					--count;
				}
			}
		}
	}
	else
	{
		Int count;
		m_flags.clear();
		*xfer == count;
		AsciiString name;
		for (Int i = 0; i < count; ++i)
		{
			*xfer == name;
			Int index = Rva001CB270FindName(name.str());
			if (index < 0)
				throw XferException(0, 0);
			m_flags.set(index);
		}
	}
}

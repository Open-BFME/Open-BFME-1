// cl: /DNDEBUG /MD /EHsc /Ireference/shims/sweep /Ireference/shims/languagefilter /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /ICode/Libraries/Source/WWVegas/WWLib

#include "string_base.h"

extern int g_bfmeDirtyBG;

// The retail value and member slots are narrow shared-buffer strings.  Keep
// this local view one word wide, but use the real StringBase<char> member
// functions so both calls carry the canonical object symbols.
class AsciiString
{
public:
	AsciiString(const AsciiString &other); // Real copy retains the shared buffer.
	~AsciiString()
	{
		((StringBase<char> *)this)->releaseBuffer();
	}

	AsciiString &operator=(const AsciiString &other)
	{
		((StringBase<char> *)this)->set(*(const StringBase<char> *)&other);
		return *this;
	}

private:
	void *m_data;
};

class Rva00190590
{
public:
	void rva00190590(AsciiString value, unsigned int index);

private:
	unsigned char m_pad[0x48];
	AsciiString m_values[6];
};

// ?rva00190590@Rva00190590@@QAEXVAsciiString@@I@Z
void Rva00190590::rva00190590(AsciiString value, unsigned int index)
{
	if (index >= 6)
		return;

	int dirty = g_bfmeDirtyBG;
	*reinterpret_cast<volatile int *>(&g_bfmeDirtyBG) = dirty | 1;
	m_values[index] = value;
}

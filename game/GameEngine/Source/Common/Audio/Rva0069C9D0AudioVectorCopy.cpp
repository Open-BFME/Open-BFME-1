// cl: /O2 /Ob2 /DNDEBUG /MD /Iinputs/reference/shims/sweep /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main
// stlport

// Retail 0x0069C9D0, 89 bytes.  This is the forward copy loop for a 0x78-byte
// audio-side record.  The first 0x70 bytes use the already identified base
// assignment reached through ILT 0x0001F753 (retail 0x000B2690); the derived
// record then copies its dword at +0x70 and byte at +0x74.  The address-derived
// record name keeps the source bounded to the observed layout and operations.

#include "PreRTS.h"
#include "Common/AudioEventRTS.h"

class Rva00698DD0Base
{
public:
private:
	char m_pad[0x70];
};

class Rva0069C9D0Element : public Rva00698DD0Base
{
public:
	Rva0069C9D0Element &operator=(const Rva0069C9D0Element &other)
	{
		reinterpret_cast<AudioEventRTS *>(this)->operator=(
			*reinterpret_cast<const AudioEventRTS *>(&other));
		m_word70 = other.m_word70;
		m_byte74 = other.m_byte74;
		return *this;
	}

private:
	unsigned int m_word70;
	unsigned char m_byte74;
	char m_pad75[3];
};

namespace _STL
{
	template Rva0069C9D0Element *__copy<
		Rva0069C9D0Element *, Rva0069C9D0Element *, int>(
		Rva0069C9D0Element *, Rva0069C9D0Element *, Rva0069C9D0Element *,
		const random_access_iterator_tag &, int *);
}

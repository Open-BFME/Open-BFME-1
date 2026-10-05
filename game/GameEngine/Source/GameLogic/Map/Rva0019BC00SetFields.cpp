// cl: /DNDEBUG /MD /EHsc /Iinputs/reference/shims/stringbaseascii /Iinputs/reference/shims/sweep /Igame/Libraries/Source/WWVegas/WWLib /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas
// stlport
#define __PLACEMENT_VEC_NEW_INLINE
#include "Common/Dict.h"
#include "Common/WellKnownKeys.h"

class Rva0019BC00Owner
{
public:
	void apply(int index, const AsciiString &a, const AsciiString &b);
	void prepare(int index);
	void finish(int index);

private:
	char m_head[0xC];
	char *m_data;
};

void Rva0019BC00Owner::apply(int index, const AsciiString &a, const AsciiString &b)
{
	prepare(index);
	Dict *field = (Dict *)(m_data + (index << 4) + 0xC);
	field->setAsciiString(TheKey_teamOwner.key(), a);
	field->setAsciiString(TheKey_teamName.key(), b);
	finish(index);
}

// cl: /O2 /Ob1

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/AsciiString.h
#include "../../../Libraries/Source/WWVegas/WWLib/ascii_string.h"

// AsciiString adds no members to StringBase<char>; its inline copy constructor
// calls the retail StringBase copy constructor at 0x00887B60.

class Rva0042F400
{
	AsciiString m_str;
	short m_04;

public:
	Rva0042F400(const Rva0042F400 &other);
};

Rva0042F400::Rva0042F400(const Rva0042F400 &other)
	: m_str(other.m_str)
	, m_04(other.m_04)
{
}

// cl: /O2 /Ob0

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/AsciiString.h
class AsciiString
{
public:
	AsciiString(const AsciiString &other);

private:
	void *m_item;
};

class Rva003877A0
{
	AsciiString m_str;
	short m_04;

public:
	Rva003877A0(const Rva003877A0 &other);
};

Rva003877A0::Rva003877A0(const Rva003877A0 &other)
	: m_str(other.m_str)
	, m_04(other.m_04)
{
}

// cl: /O2 /Ob0

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/AsciiString.h
class AsciiString
{
public:
	AsciiString(const AsciiString &other);

private:
	void *m_item;
};

class Rva003A89F0
{
	virtual void handle();
	AsciiString m_04;
	char m_08;

public:
	Rva003A89F0(const Rva003A89F0 &other);
};

Rva003A89F0::Rva003A89F0(const Rva003A89F0 &other)
	: m_04(other.m_04)
	, m_08(other.m_08)
{
}

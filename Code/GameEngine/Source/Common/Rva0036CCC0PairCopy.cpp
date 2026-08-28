// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/AsciiString.h
class AsciiString
{
public:
	AsciiString(const AsciiString &other);
	~AsciiString();

private:
	void *m_data;
};

class Rva0036CCC0Pair
{
public:
	Rva0036CCC0Pair(const Rva0036CCC0Pair &other);

private:
	AsciiString m_first;
	AsciiString m_second;
	int m_value;
};

Rva0036CCC0Pair::Rva0036CCC0Pair(const Rva0036CCC0Pair &other)
	: m_first(other.m_first),
	  m_second(other.m_second),
	  m_value(other.m_value)
{
}

// @??0Rva0036CCC0Pair@@QAE@ABV0@@Z 0x0036CCC0

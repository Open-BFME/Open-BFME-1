// cl: /O2 /Ob0 /EHsc

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/AsciiString.h
class AsciiString
{
public:
	AsciiString(const AsciiString &other);
	~AsciiString();

private:
	void *m_data;
};

class BfmeSortElem20Tail
{
public:
	BfmeSortElem20Tail(const BfmeSortElem20Tail &other);
	~BfmeSortElem20Tail();

private:
	int m_bfmeBody[3];
};

class Rva002E8FC0
{
	AsciiString m_00;
	char m_04;
	BfmeSortElem20Tail m_08;

public:
	Rva002E8FC0(const Rva002E8FC0 &other);
};

Rva002E8FC0::Rva002E8FC0(const Rva002E8FC0 &other)
	: m_00(other.m_00)
	, m_04(other.m_04)
	, m_08(other.m_08)
{
}

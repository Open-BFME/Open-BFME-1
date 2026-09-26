// cl: /O2 /Ob0 /EHsc

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/AsciiString.h
// Retail's AsciiString adds no members of its own to StringBase<char> and this
// file only copies one, which retail encodes as a direct call to the base copy
// ctor at 0x00887B60. This TU is compiled /Ob0, so nothing here may rely on a
// forwarder being inlined away: the member is spelled as the base it copies.
template <typename T>
class StringBase
{
public:
	StringBase(const StringBase<T> &src);
	~StringBase();

private:
	void *m_data;
};

typedef StringBase<char> AsciiString;

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

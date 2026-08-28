// cl: /DNDEBUG /MD /EHsc
// Open-BFME: the anonymous retail destructor at 0x002DE780, 89 bytes,
// converted from the Code/gen_asm naked dump to real C++.
//
// The class is NOT identified and the earlier SubObjectsUpgradeModuleData lead
// was refuted (that name is already claimed at 0x002D8A60 by a 343-byte body
// destroying five 12-byte members).  What the bytes do fix is the ABI:
// a polymorphic base whose virtual destructor is the body behind the thunk at
// 0x0004A430 (retail 0x002DAB10), sized 0x60, followed by exactly two 4-byte
// AsciiString members at this+0x60 and this+0x64, both released through
// 0x00887940.  The name here is address-derived on purpose -- it disclaims
// identity rather than asserting one.

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/AsciiString.h
class AsciiString
{
public:
	~AsciiString();

private:
	char *m_data;
};

class __declspec(novtable) Gen_dtor_002dabe0
{
public:
	virtual ~Gen_dtor_002dabe0();

private:
	char m_opaque[0x5C];
};

class __declspec(novtable) Gen_002de780 : public Gen_dtor_002dabe0
{
public:
	virtual ~Gen_002de780();

private:
	AsciiString m_60;
	AsciiString m_64;
};

Gen_002de780::~Gen_002de780()
{
}

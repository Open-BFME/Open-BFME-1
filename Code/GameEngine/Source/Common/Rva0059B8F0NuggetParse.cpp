// cl: /DNDEBUG /MD /EHsc
// Open-BFME5 near-twin conversion.
// Twin: ?parse@AttackNugget@@SAXPAVINI@@PAX1PBX@Z @ 0x001D8770,
//       Code/GameEngine/Source/Common/AttackNugget_parse_Thunk.cpp
// Same INI-parse boilerplate (SEH frame, allocate, init from a static
// FieldParse table, add to the owning ObjectCreationList) as AttackNugget's
// parse(), but the new'd object is BfmeA1140 (56 bytes, ctor landed at
// 0x0059B860, BfmeConv1140.cpp) instead of AttackNugget/RadiusDecalTemplate.
// Class identity of the nugget itself is not recovered -- address-derived
// naming per IDENTITY POLICY.

class INI;
typedef void (*INIFieldParseProc)(INI *, void *, void *, const void *);

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/INI.h
struct FieldParse
{
	const char *token;
	INIFieldParseProc parse;
	const void *userData;
	int offset;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/INI.h
class INI
{
public:
	void initFromINI(void *, const FieldParse *);
	static void parseInt(INI *, void *, void *, const void *);
	static void parseReal(INI *, void *, void *, const void *);
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/ObjectCreationList.h
class ObjectCreationNugget
{
public:
	virtual void create();
};

// retail does NOT call ObjectCreationList::addObjectCreationNugget here --
// the third-arg "instance" gets a plain field store at +0x10 instead, landed
// as the gen-shim setter Gen_00489270::m (Code/gen_small/fun_003.cpp,
// RVA 0x00489270). Reuse that landed callee rather than pinning the wrong
// (real, 106-byte) addObjectCreationNugget.
struct Gen_00489270
{
	void m(int a);
};

// same layout as BfmeConv1140.cpp's BfmeA1140 -- duplicated here (TU-scoped
// shim) rather than shared, per repo convention for these small state objects.
class BfmeBase1140A
{
public:
	BfmeBase1140A(void) throw();
	char *volatile m_bfme00;
	volatile int m_bfme04;
};

class BfmeA1140 : public BfmeBase1140A
{
public:
	BfmeA1140(void);
	char m_bfme08;
	volatile char m_bfme09;
	char m_bfmePad[2];
	volatile int m_bfme0c;
	volatile int m_bfme10;
	volatile int m_bfme14;
	volatile int m_bfme18;
	volatile int m_bfme1c;
	volatile int m_bfme20;
	volatile int m_bfme24;
	volatile int m_bfme28;
	volatile int m_bfme2c;
	volatile int m_bfme30;
	volatile int m_bfme34;
};

class Rva0059B8F0Nugget : public ObjectCreationNugget
{
public:
	Rva0059B8F0Nugget();
	virtual void create();

	static void parse(INI *, void *, void *, const void *);

private:
	BfmeA1140 m_bfme;
};

// ?parse@Rva0059B8F0Nugget@@SAXPAVINI@@PAX1PBX@Z
void Rva0059B8F0Nugget::parse(INI *ini, void *instance, void *, const void *)
{
	static const FieldParse myFieldParse[] =
	{
		{ "NumberOfShots", INI::parseInt, 0, 0x38 },
		{ "Radius", INI::parseReal, 0, 0x34 },
		{ 0, 0, 0, 0 }
	};

	BfmeA1140 *nugget = new BfmeA1140;
	ini->initFromINI(nugget, myFieldParse);
	((Gen_00489270 *)instance)->m((int)nugget);
}

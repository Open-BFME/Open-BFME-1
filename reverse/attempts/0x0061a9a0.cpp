// ??0Rva0061A5F0@@QAE@ABVAsciiString@@@Z
// partial score=0.68 date=2026-09-10
// cl: /DNDEBUG /MD /EHsc
// stlport
//
// The Region field table registers this callback for LivingWorldRegion.  The
// parser allocates the 0xF4-byte Rva0061A780 whose constructor installs
// vtable 0x01117258, calls BfmeThingDCG::bfmeGoDCG, then appends the pointer
// to the campaign vector at instance+0x30.

#include <new>

#pragma intrinsic(_ReadWriteBarrier)
extern "C" void _ReadWriteBarrier(void);

template <typename Type>
class StringBase
{
	friend class AsciiString;
	friend class BFMERetailAsciiString;

	StringBase() : m_data(0) {}
	StringBase(const Type *text);
	StringBase(const StringBase &other);
	void releaseBuffer();

private:
	void *m_data;
};

class AsciiString : private StringBase<char>
{
public:
	AsciiString(const char *text) : StringBase<char>(text) {}
	AsciiString(const AsciiString &other)
		: StringBase<char>(*(const StringBase<char> *)&other) {}
	~AsciiString()
	{
		((StringBase<char> *)this)->releaseBuffer();
	}
};

class BFMERetailAsciiString : private StringBase<char>
{
public:
	BFMERetailAsciiString() : StringBase<char>() {}
	BFMERetailAsciiString(const char *text) : StringBase<char>(text) {}
	BFMERetailAsciiString(const AsciiString &other)
		: StringBase<char>(*(const StringBase<char> *)&other) {}

	void releaseBuffer()
	{
		((StringBase<char> *)this)->releaseBuffer();
	}
};

class Rva0076F980Mid
{
public:
	Rva0076F980Mid() : m_begin(0), m_end(0), m_capacity(0) {}
	~Rva0076F980Mid();

	AsciiString *erase(AsciiString *first, AsciiString *last);

	void clear()
	{
		erase(m_begin, m_end);
	}

private:
	AsciiString *m_begin;
	AsciiString *m_end;
	AsciiString *m_capacity;
};

class Rva0061A5F0VectorHolder
{
public:
	Rva0061A5F0VectorHolder() : m_start(0), m_finish(0), m_capacity(0) {}
	~Rva0061A5F0VectorHolder();

private:
	char *m_start;
	char *m_finish;
	char *m_capacity;
};

// The existing destructor at 0x0061A5F0 proves this aggregate's member
// offsets and the three vector clear calls.  Keeping its constructor in the
// same TU lets the owning constructor call a real named body at +0x04.
class Rva0061A5F0
{
public:
	Rva0061A5F0(const AsciiString &name);
	~Rva0061A5F0();

private:
	BFMERetailAsciiString m_str00;
	BFMERetailAsciiString m_str04;
	BFMERetailAsciiString m_str08;
	BFMERetailAsciiString m_str0C;
	BFMERetailAsciiString m_str10;
	BFMERetailAsciiString m_str14;
	BFMERetailAsciiString m_str18;
	BFMERetailAsciiString m_str1C;
	BFMERetailAsciiString m_str20;
	BFMERetailAsciiString m_str24;
	unsigned char m_unreconstructed28[0x2C - 0x28];
	Rva0076F980Mid m_member2C;
	BFMERetailAsciiString m_str38;
	BFMERetailAsciiString m_str3C;
	Rva0061A5F0VectorHolder m_vector40;
	unsigned char m_flag4C;
	Rva0076F980Mid m_member50;
	Rva0076F980Mid m_member5C;
	int m_value68;
	int m_value6C;
	unsigned char m_value70;
	int m_value74;
	int m_value78;
	int m_value7C;
	unsigned char m_value80;
	int m_value84;
	unsigned char m_value88;
	int m_value8C;
	int m_value90;
	BFMERetailAsciiString m_str94;
};

Rva0061A5F0::Rva0061A5F0(const AsciiString &name)
	: m_str00(name),
	  m_str04(),
	  m_str08((const char *)0x01117284),
	  m_str0C(),
	  m_str10(),
	  m_str14(),
	  m_str18(),
	  m_str1C(),
	  m_str20(),
	  m_str24(),
	  m_unreconstructed28(),
	  m_member2C(),
	  m_str38(),
	  m_str3C(),
	  m_vector40(),
	  m_flag4C(1),
	  m_member50(),
	  m_member5C(),
	  m_value68(0),
	  m_value6C(0),
	  m_value70(0),
	  m_value74(0),
	  m_value78(0),
	  m_value7C(0),
	  m_value80(0),
	  m_value84(0),
	  m_value88(0),
	  m_value8C(0),
	  m_value90(0),
	  m_str94()
{
	m_member2C.clear();
	m_member50.clear();
	m_member5C.clear();
}

class INI
{
public:
	const char *getNextToken(const char *separators = 0);
};

class BfmeOtherDCG;

class BfmeThingDCG
{
public:
	void bfmeGoDCG(BfmeOtherDCG *other);

private:
	void *m_vtable;
};

class Gen_0061A3D0 : public StringBase<char>
{
public:
	Gen_0061A3D0(const StringBase<char> &source);

private:
	char m_body[0x28];
};

class Rva0061A780
{
public:
	Rva0061A780(const AsciiString &name);

private:
	unsigned int m_vtable;
	char m_field04[0x98];
	unsigned int m_value9C;
	unsigned int m_valueA0;
	unsigned int m_valueA4;
	unsigned char m_valueA8;
	unsigned char m_unreconstructedA9[0xB4 - 0xA9];
	void *m_madeBNG;
	char m_fieldB8[4];
	unsigned int m_valueBC;
	unsigned int m_valueC0;
	unsigned int m_valueC4;
	unsigned int m_valueC8;
	unsigned int m_valueCC;
	unsigned char m_valueD0;
	unsigned char m_valueD1;
	unsigned char m_unreconstructedD2[2];
	char m_fieldD4[0xC];
	unsigned int m_valueE0;
	unsigned int m_valueE4;
	unsigned char m_valueE8;
	unsigned char m_valueE9;
	unsigned char m_unreconstructedEA[3];
	Gen_0061A3D0 *m_ptrEC;
};

void *bfmeMakeBNG(void *one, void *two);
void *operator new(unsigned int bytes);

Rva0061A780::Rva0061A780(const AsciiString &name)
{
	*(unsigned int *)this = 0x01117258;
	_ReadWriteBarrier();
	Rva0061A5F0 *field = (Rva0061A5F0 *)((unsigned char *)this + 4);
	__assume(field != 0);
	new (field) Rva0061A5F0(name);
	_ReadWriteBarrier();
	*(volatile unsigned int *)((unsigned char *)this + 0x9C) = 0;
	*(volatile unsigned int *)((unsigned char *)this + 0xA0) = 0;
	*(volatile unsigned int *)((unsigned char *)this + 0xA4) = 0;
	*(volatile unsigned char *)((unsigned char *)this + 0xA8) = 0;
	*(void *volatile *)((unsigned char *)this + 0xB4) =
		bfmeMakeBNG((void *)0, (void *)0);
	*(volatile unsigned int *)((unsigned char *)this + 0xB8) = 0;
	*(volatile unsigned int *)((unsigned char *)this + 0xBC) = 0;
	*(volatile unsigned int *)((unsigned char *)this + 0xC0) = 0;
	*(volatile unsigned int *)((unsigned char *)this + 0xC4) = 0;
	*(volatile unsigned int *)((unsigned char *)this + 0xC8) = 0;
	*(volatile unsigned int *)((unsigned char *)this + 0xCC) = 0;
	*(volatile unsigned char *)((unsigned char *)this + 0xD0) = 0;
	*(volatile unsigned char *)((unsigned char *)this + 0xD1) = 0;
	*(volatile unsigned int *)((unsigned char *)this + 0xD4) = 0;
	*(volatile unsigned int *)((unsigned char *)this + 0xD8) = 0;
	*(volatile unsigned int *)((unsigned char *)this + 0xDC) = 0;
	*(volatile unsigned int *)((unsigned char *)this + 0xE0) = 0;
	*(volatile unsigned int *)((unsigned char *)this + 0xE4) = 0;
	*(volatile unsigned char *)((unsigned char *)this + 0xE8) = 0;
	*(volatile unsigned char *)((unsigned char *)this + 0xE9) = 0;

	Gen_0061A3D0 *p = (Gen_0061A3D0 *)operator new(0x2C);
	if (p)
	{
		new (p) Gen_0061A3D0(
			*(const StringBase<char> *)&name);
	}
	*(Gen_0061A3D0 *volatile *)((unsigned char *)this + 0xEC) = p;
	*(unsigned char *)((unsigned char *)p + 0x18) = 0;

	((BFMERetailAsciiString *)((unsigned char *)this + 0xB8))
		->releaseBuffer();
	((Rva0076F980Mid *)((unsigned char *)this + 0xD4))->clear();
}

#include <vector>

class LivingWorldRegionManager
{
public:
	static void parseNamedSubBlock(INI *ini, void *instance, void *, const void *);
};

class LivingWorldRegionStore
{
public:
	char m_pad[0x30];
	std::vector<Rva0061A780 *> m_regions;
};

// ?parseNamedSubBlock@LivingWorldRegionManager@@SAXPAVINI@@PAX1PBX@Z
void LivingWorldRegionManager::parseNamedSubBlock(
	INI *ini, void *instance, void *, const void *)
{
	Rva0061A780 *region = 0;
	const char *token = ini->getNextToken();
	region = new Rva0061A780(AsciiString(token));
	reinterpret_cast<BfmeThingDCG *>(region)->bfmeGoDCG(
		reinterpret_cast<BfmeOtherDCG *>(ini));

	LivingWorldRegionStore *store =
		reinterpret_cast<LivingWorldRegionStore *>(instance);
	store->m_regions.push_back(region);
}

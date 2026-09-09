// cl: /EHs-c-
// ??0Rva005EBD40@@QAE@ABV0@@Z
//
// The clone factory at 0x005EBCC0 calls this constructor.  Retail copies two
// 90-element arrays of three dwords, then copies the eleven dwords at +0x8B8.

class V3Head14
{
public:
	virtual ~V3Head14();
	int m_a, m_b, m_c, m_d;
};

class V3Vt0110F97C
{
public:
	virtual void s0();
};

class Rva005EB7B0 : public V3Head14, public V3Vt0110F97C
{
public:
	Rva005EB7B0( const Rva005EB7B0 & );
};

class Rva005EBD40Middle : public Rva005EB7B0
{
};

namespace FXParticleSystem
{

class LightningDrawModuleInfo
{
public:
	LightningDrawModuleInfo( const LightningDrawModuleInfo & );
	virtual ~LightningDrawModuleInfo();
	char m_storage[ 0x2c ];
};

}

struct Rva005EBD40Triple
{
	int m_a, m_b, m_c;
};

struct Rva005EBD40Tail
{
	int m_a0, m_a1, m_a2, m_a3, m_a4, m_a5;
	int m_a6, m_a7, m_a8, m_a9, m_a10;
};

class Rva005EBD40
	: public Rva005EBD40Middle, public FXParticleSystem::LightningDrawModuleInfo
{
public:
	Rva005EBD40( const Rva005EBD40 & );

	Rva005EBD40Triple m_first[ 90 ];
	Rva005EBD40Triple m_second[ 90 ];
	Rva005EBD40Tail m_tail;
};

Rva005EBD40::Rva005EBD40( const Rva005EBD40 &o )
	: Rva005EBD40Middle( o ), FXParticleSystem::LightningDrawModuleInfo( o )
{
	Rva005EBD40Triple *destination = m_first;
	const Rva005EBD40Triple *source = o.m_first;
	for ( int i = 0; i < 90; ++i )
	{
		destination->m_a = source->m_a;
		destination->m_b = source->m_b;
		destination->m_c = source->m_c;
		++destination;
		++source;
	}

	destination = m_second;
	source = o.m_second;
	for ( int i = 0; i < 90; ++i )
	{
		destination->m_a = source->m_a;
		destination->m_b = source->m_b;
		destination->m_c = source->m_c;
		++destination;
		++source;
	}

	m_tail.m_a0 = o.m_tail.m_a0;
	m_tail.m_a1 = o.m_tail.m_a1;
	m_tail.m_a2 = o.m_tail.m_a2;
	m_tail.m_a3 = o.m_tail.m_a3;
	m_tail.m_a4 = o.m_tail.m_a4;
	m_tail.m_a5 = o.m_tail.m_a5;
	m_tail.m_a6 = o.m_tail.m_a6;
	m_tail.m_a7 = o.m_tail.m_a7;
	m_tail.m_a8 = o.m_tail.m_a8;
	m_tail.m_a9 = o.m_tail.m_a9;
	m_tail.m_a10 = o.m_tail.m_a10;
}

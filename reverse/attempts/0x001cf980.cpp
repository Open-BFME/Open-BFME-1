// ?query@Rva001CF980@@QAEPAXXZ
// partial score=0.92 date=2026-09-02
// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHs-c-
// Walk OVERRIDE at +4, test bit 0x1000 of dword +0xD4.  If clear, switch to
// the Object* at +0x214 when it isKindOf(0x6C).  Tail-call vtable +0x68 on
// the object's pointer at +0x1FC.

enum KindOfType
{
	KINDOF_0x6C = 0x6C
};

class Overridable
{
public:
	const Overridable *getFinalOverride( void ) const;
	void *m_head;
	Overridable *m_nextOverride;
};

class Rva001CF980Thing : public Overridable
{
public:
	char m_gap[ 0xD4 - 8 ];
	unsigned m_flags_d4;
};

class Rva001CF980Iface
{
public:
	virtual void *slot00();
	virtual void *slot01();
	virtual void *slot02();
	virtual void *slot03();
	virtual void *slot04();
	virtual void *slot05();
	virtual void *slot06();
	virtual void *slot07();
	virtual void *slot08();
	virtual void *slot09();
	virtual void *slot10();
	virtual void *slot11();
	virtual void *slot12();
	virtual void *slot13();
	virtual void *slot14();
	virtual void *slot15();
	virtual void *slot16();
	virtual void *slot17();
	virtual void *slot18();
	virtual void *slot19();
	virtual void *slot20();
	virtual void *slot21();
	virtual void *slot22();
	virtual void *slot23();
	virtual void *slot24();
	virtual void *slot25();
	virtual void *slot26();
};

class Thing
{
public:
	bool isKindOf( KindOfType t ) const;

private:
	virtual ~Thing();
	Rva001CF980Thing *m_template;
	friend class Rva001CF980;
};

class Rva001CF980 : public Thing
{
public:
	void *query();

private:
	char m_gap_1fc[ 0x1FC - 8 ];
	Rva001CF980Iface *m_iface;
	char m_gap_214[ 0x214 - 0x200 ];
	Rva001CF980 *m_other;
};

void *Rva001CF980::query()
{
	Rva001CF980Thing *thing = m_template;
	if ( thing )
	{
		if ( thing->m_nextOverride )
			thing = (Rva001CF980Thing *)thing->m_nextOverride->getFinalOverride();
	}
	Rva001CF980 *obj;
	if ( thing->m_flags_d4 & 0x1000 )
		obj = this;
	else
	{
		obj = m_other;
		if ( !obj )
			return 0;
		if ( !obj->isKindOf( KINDOF_0x6C ) )
			return 0;
	}
	void *candidateAddress = obj;
	if ( candidateAddress )
	{
		Rva001CF980 *candidate = (Rva001CF980 *)candidateAddress;
		Rva001CF980Iface *iface = candidate->m_iface;
		if ( iface )
			return iface->slot26();
	}
	return 0;
}

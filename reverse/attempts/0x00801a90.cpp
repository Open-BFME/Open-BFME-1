// ?findFree@Rva00801A90Owner@@QAEPAVRva00801A90Elem@@XZ
// partial score=0.77 date=2026-09-04
// ?findFree@Rva00801A90Owner@@QAEPAVRva00801A90Elem@@XZ
// partial score=0.77 date=2026-09-04
// cl: /GX-
// Find first free 0x38-stride slot: bounds ternary yields NULL past count,
// virtual probe at vtbl+0x1c, stamp index at elem+0x10.
// Near-miss: 53/69 — this in ebx not edi; index in edi not ebx (register swap).

class Rva00801A90Elem
{
public:
	virtual void v0();
	virtual void v1();
	virtual void v2();
	virtual void v3();
	virtual void v4();
	virtual void v5();
	virtual void v6();
	virtual int probe();

	char m_pad04[0x0C];
	int m_index;
	char m_rest[0x38 - 0x14];
};

class Rva00801A90Owner
{
public:
	Rva00801A90Elem *findFree();

	char m_pad[0x20];
	void *m_array;
	int m_count;
};

Rva00801A90Elem *Rva00801A90Owner::findFree()
{
	for( int i = 0; i < m_count; ++i )
	{
		Rva00801A90Elem *slot = ( i >= m_count )
			? 0
			: (Rva00801A90Elem *)( (char *)m_array + i * 0x38 );
		if( !slot->probe() )
		{
			slot->m_index = i;
			return slot;
		}
	}
	return 0;
}

// cl: /DNDEBUG /MD
// Address-derived template-kind dispatch at retail RVA 0x00210BA0.

class BfmeSubInnerEFF
{
public:
	void *bfmeGetFinalOverride();
};

struct Rva00210BA0Template
{
	void *m_vtable;
	BfmeSubInnerEFF *m_nextOverride;
	char m_unmodelled_008[ 0xc8 - 8 ];
	unsigned int m_kindOf;
};

struct Rva00210BA0Object
{
	void *m_vtable;
	Rva00210BA0Template *m_template;
};

class Rva00210BA0Owner
{
public:
	virtual void slot00();
	virtual void slot01();
	virtual void slot02();
	virtual void slot03();
	virtual void slot04();
	virtual void slot05();
	virtual void slot06();
	virtual void slot07();
	virtual void slot08();
	virtual void slot09();
	virtual void slot10();
	virtual void slot11();
	virtual void slot12();
	virtual void slot13();
	virtual void slot14();
	virtual void slot15();
	virtual void slot16();
	virtual void slot17();
	virtual void slot18();
	virtual void slot19();

	void dispatch00210BA0();
private:
	unsigned int m_unmodelled_004;
	Rva00210BA0Object *m_object;
};

void Rva00210BA0Owner::dispatch00210BA0()
{
	Rva00210BA0Template *const volatile *templateSlot = &m_object->m_template;
	Rva00210BA0Template *tmpl = *templateSlot;
	if( tmpl != 0 && tmpl->m_nextOverride != 0 )
		tmpl = (Rva00210BA0Template *)tmpl->m_nextOverride->bfmeGetFinalOverride();
	if( (tmpl->m_kindOf & 0x02000000) == 0 )
		slot19();
	slot17();
}

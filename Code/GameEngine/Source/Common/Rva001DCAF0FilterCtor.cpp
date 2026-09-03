// cl: /DNDEBUG /MD /EHsc
// Constructor installing vtable 0x0109FB54. Arg is an Object; if it has a
// module at +0x200, virtual slot +0x3C is called and the returned record's
// +8 pointer is stored at this+8.

class VptrZeroHead
{
public:
	VptrZeroHead() : m_unmodelled_04(0) {}
	virtual ~VptrZeroHead();
	unsigned int m_unmodelled_04;
};

VptrZeroHead::~VptrZeroHead()
{
}

struct Rva001DCAF0Rec
{
	unsigned char m_unreconstructed_00[8];
	void *m_value;
};

class Rva001DCAF0Module
{
public:
#define BFME_VIRTUAL_SLOT(n) virtual void _v##n(void) = 0
	BFME_VIRTUAL_SLOT(00); BFME_VIRTUAL_SLOT(01); BFME_VIRTUAL_SLOT(02); BFME_VIRTUAL_SLOT(03);
	BFME_VIRTUAL_SLOT(04); BFME_VIRTUAL_SLOT(05); BFME_VIRTUAL_SLOT(06); BFME_VIRTUAL_SLOT(07);
	BFME_VIRTUAL_SLOT(08); BFME_VIRTUAL_SLOT(09); BFME_VIRTUAL_SLOT(10); BFME_VIRTUAL_SLOT(11);
	BFME_VIRTUAL_SLOT(12); BFME_VIRTUAL_SLOT(13); BFME_VIRTUAL_SLOT(14);
#undef BFME_VIRTUAL_SLOT
	virtual Rva001DCAF0Rec *getRecord(void) = 0;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Object.h
class Object
{
public:
	unsigned char m_unreconstructed_00[0x200];
	Rva001DCAF0Module *m_module;
};

class Rva001DCAF0Filter : public VptrZeroHead
{
public:
	Rva001DCAF0Filter(Object *object);

	void *m_value;
};

Rva001DCAF0Filter::Rva001DCAF0Filter(Object *object)
{
	if (object)
	{
		Rva001DCAF0Module *module = object->m_module;
		if (module)
		{
			Rva001DCAF0Rec *record = module->getRecord();
			m_value = record->m_value;
			return;
		}
	}
	m_value = 0;
}

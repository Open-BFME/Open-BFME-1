// cl: /DNDEBUG /MD /EHsc

// A refcount base, an array of eight, then four fields.
//
// The base's constructor is inlined and is just the count at +4 set to one,
// which is what a reference-counted object starts life with. ??_L gives the
// array outright: base +8, eight elements, four bytes each, with a constructor
// and a destructor -- so the element is a class holding one pointer, not a raw
// pointer, or there would be no iterator call at all.
//
// The tail is written in the order retail has it rather than in address order:
// +0x28, +0x2C, +0x34, then the byte at +0x30 last.
// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib/refcount.h
class RefCountClass
{
public:
	RefCountClass() : m_numRefs(1) {}

	virtual ~RefCountClass();

	int m_numRefs;
};

class MaterialPassStage
{
public:
	MaterialPassStage();
	~MaterialPassStage();

private:
	void *m_ptr;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2/matpass.h
class MaterialPassClass : public RefCountClass
{
public:
	MaterialPassClass();

private:
	MaterialPassStage m_stages[8];
	int m_28;
	int m_2c;
	bool m_30;
	int m_34;
};

// ??0MaterialPassClass@@QAE@XZ
MaterialPassClass::MaterialPassClass()
{
	m_28 = 0;
	m_2c = 0;
	m_34 = 0;
	m_30 = true;
}

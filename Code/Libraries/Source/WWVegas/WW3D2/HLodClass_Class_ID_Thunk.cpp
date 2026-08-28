// cl: /DNDEBUG /MD /EHsc

// hlod.h declares `virtual int Class_ID(void) const { return CLASSID_HLOD; }`,
// and this body returns 0x19. Counting rendobj.h's ClassID enum from
// CLASSID_MESH = 0 puts CLASSID_HLOD at 25, which is 0x19 -- so the constant
// identifies the class outright, independently of the slot it sits in.
//
// That matters here because the vtable it belongs to carries names from several
// classes across its slots, ICF having folded the inherited methods. The enum
// value does not depend on any of that, and it agrees with the HLodClass methods
// that populate the rest of the table.
// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2/hlod.h
class HLodClass
{
public:
	virtual ~HLodClass();
	virtual int Class_ID(void) const;
};

// ?Class_ID@HLodClass@@UBEHXZ
int HLodClass::Class_ID(void) const
{
	return 25;
}

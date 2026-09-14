// cl: /DNDEBUG /MD /EHsc
//
// Open-BFME: HLodPrototypeClass scalar-deleting destructor at retail RVA
// 0x0014ABA0 (30 bytes). The exact constructor at 0x00149F60 installs vtable
// 0x010956F4, whose slot zero routes through ILT 0x00017E68 to this wrapper.
// The HLod loader's concrete allocation corroborates identity; the complete
// destructor is called through ILT 0x000390F9.

class HLodPrototypeClass
{
public:
	virtual ~HLodPrototypeClass();
};

void forceHLodPrototypeClassDeletingDestructor()
{
	HLodPrototypeClass value;
}

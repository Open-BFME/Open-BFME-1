// cl: /DNDEBUG /MD /EHsc
//
// Open-BFME5: GarrisonContain scalar-deleting destructor at retail RVA
// 0x0021E310 (30 bytes). The exact constructor at 0x0021D820 and complete
// destructor at 0x0021D9C0 share the class vtables; typed factories and the
// extensive landed GarrisonContain method family corroborate the identity.

class GarrisonContain
{
public:
	virtual ~GarrisonContain();
};

void forceGarrisonContainDeletingDestructor()
{
	GarrisonContain value;
}

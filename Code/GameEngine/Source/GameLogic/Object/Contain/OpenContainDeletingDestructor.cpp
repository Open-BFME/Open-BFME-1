// cl: /DNDEBUG /MD /EHsc
//
// Open-BFME5: OpenContain scalar-deleting destructor at retail RVA 0x00227B30
// (30 bytes). The exact constructor at 0x002277A0 and complete destructor at
// 0x002262E0 share vtable 0x00CAC2B8; typed factories and the extensive landed
// OpenContain method family corroborate the identity. The dtor ILT is 0x00039D6A.

class OpenContain
{
public:
	virtual ~OpenContain();
};

void forceOpenContainDeletingDestructor()
{
	OpenContain value;
}

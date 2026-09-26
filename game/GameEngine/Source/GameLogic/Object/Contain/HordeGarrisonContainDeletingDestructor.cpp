// cl: /DNDEBUG /MD /EHsc
//
// Open-BFME: public scalar-deleting destructor for HordeGarrisonContain.
// The exact constructor at 0x00248F90 installs dedicated vtable 0x010AFDC0;
// slot zero routes through ILT 0x00006528 to this 30-byte wrapper, whose
// complete destructor is reached through ILT 0x00038622.

class HordeGarrisonContain
{
public:
	virtual ~HordeGarrisonContain();
};

void forceHordeGarrisonContainDeletingDestructor()
{
	HordeGarrisonContain value;
}

// cl: /DNDEBUG /MD /EHsc
//
// Open-BFME5: AODHordeContain scalar-deleting destructor at retail RVA
// 0x00231BB0 (30 bytes). The exact constructor at 0x00230580, complete
// destructor at 0x00230980, unique factories, base/array layout, and vtable
// 0x00CAE7A0 establish the class. The destructor ILT is 0x00012E13.

class AODHordeContain
{
public:
	virtual ~AODHordeContain();
};

void forceAODHordeContainDeletingDestructor()
{
	AODHordeContain value;
}

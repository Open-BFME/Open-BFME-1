// cl: /DNDEBUG /MD /EHsc
//
// Open-BFME: public scalar-deleting destructor for HordeTransportContain.
// The exact constructor at 0x0024B6F0 installs dedicated vtable 0x010B0688;
// slot zero routes through ILT 0x00001ADC to this 30-byte wrapper, whose
// complete destructor is reached through ILT 0x00037E6B.

class HordeTransportContain
{
public:
	virtual ~HordeTransportContain();
};

void forceHordeTransportContainDeletingDestructor()
{
	HordeTransportContain value;
}

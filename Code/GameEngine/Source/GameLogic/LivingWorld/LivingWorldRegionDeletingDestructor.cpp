// cl: /DNDEBUG /MD /EHsc
//
// Open-BFME: LivingWorldRegion scalar-deleting destructor at retail RVA
// 0x0061AB30 (30 bytes). The region constructor at 0x0061AF80 installs vtable
// 0x01117258; slot zero routes through ILT 0x00040B6A to this wrapper, while
// slot two returns the literal class name "LivingWorldRegion". The wrapper's
// destructor call routes through ILT 0x0001C990 to the exact 0x0061A780 body.

class LivingWorldRegion
{
public:
	virtual ~LivingWorldRegion();
};

void forceLivingWorldRegionDeletingDestructor()
{
	LivingWorldRegion value;
}

// cl: /DNDEBUG /MD /EHsc
//
// Open-BFME5: PassiveAreaEffectBehavior scalar-deleting destructor at retail
// RVA 0x00202390 (30 bytes). Its exact constructor at 0x00202100, complete
// destructor at 0x002022B0, factories, module name, and vtable 0x010A5304 all
// establish the class. The wrapper calls the destructor via ILT 0x000116E4.

class PassiveAreaEffectBehavior
{
public:
	virtual ~PassiveAreaEffectBehavior();
};

void forcePassiveAreaEffectBehaviorDeletingDestructor()
{
	PassiveAreaEffectBehavior value;
}

// cl: /DNDEBUG /MD /EHsc
//
// Open-BFME: AttackNugget scalar-deleting destructor at retail RVA
// 0x001D6D50 (30 bytes). AttackNugget's exact constructor at 0x001D6CD0
// installs vtable 0x0109F5D0, whose slot zero routes through ILT 0x00010816
// to this wrapper. The wrapper calls the complete destructor through ILT
// 0x00013C2D (body 0x001D6D80) before the retail operator-delete call.

class AttackNugget
{
public:
	virtual ~AttackNugget();
};

void forceAttackNuggetDeletingDestructor()
{
	AttackNugget value;
}

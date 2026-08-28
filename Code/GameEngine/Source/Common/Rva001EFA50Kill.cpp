// cl: /O2 /Ob0

enum DamageType { DAMAGE_UNRESISTABLE = 8 };
enum DeathType { DEATH_NORMAL = 0 };

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Object.h
class Object
{
public:
	void kill(DamageType, DeathType);
};

class Rva001EFA50
{
public:
	void run(int unused);
};

void Rva001EFA50::run(int)
{
	Object *o = *(Object **)((char *)this - 0x18);
	o->kill(DAMAGE_UNRESISTABLE, DEATH_NORMAL);
}

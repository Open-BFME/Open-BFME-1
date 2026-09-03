// cl: /DNDEBUG /MD /EHsc
//
// Retail 0x0029B310: PhysicsBehavior thiscall that builds a zero Coord3D and
// passes it to applyMotiveForce. ecx is forwarded as this.

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include/Lib/BaseType.h
struct Coord3D
{
	Coord3D()
	{
		x = 0;
		y = 0;
		z = 0;
	}
	float x;
	float y;
	float z;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/PhysicsUpdate.h
class PhysicsBehavior
{
public:
	void applyMotiveForce(const Coord3D *force);
	void applyZeroMotiveForce();
};

// ?applyZeroMotiveForce@PhysicsBehavior@@QAEXXZ
void PhysicsBehavior::applyZeroMotiveForce()
{
	applyMotiveForce(&Coord3D());
}

// cl: /DNDEBUG /MD /EHsc
//
// Retail 0x0029B310: PhysicsBehavior thiscall that builds a zero Coord3D and
// passes it to applyMotiveForce. ecx is forwarded as this.

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

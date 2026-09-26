// cl: /DNDEBUG /MD /EHsc
//
// Rva003EEB50::run, retail 0x003EEB50, 50 bytes.
//
// Two-arg thiscall forwarder on d_003d5070: reload Pathfinder* at +0 and the
// cached checkForTarget operands from +4..+0x1C, pass (cellX,cellY) through.

struct Coord3D;
class Object;
class Weapon;

class Pathfinder
{
public:
	bool checkForTarget( const Object * obj, int cellX, int cellY,
		const Weapon * weapon, const Object * victim, const Coord3D * victimPos,
		int iRadius, bool center, Coord3D * dest );
};

class Rva003EEB50
{
public:
	bool run( int cellX, int cellY );

private:
	Pathfinder * m_pf;       // +0x00
	const Object * m_obj;    // +0x04
	bool m_center;           // +0x08
	char m_pad09[ 3 ];
	int m_radius;            // +0x0C
	Coord3D * m_dest;        // +0x10
	const Object * m_victim; // +0x14
	const Coord3D * m_victimPos; // +0x18
	const Weapon * m_weapon; // +0x1C
};

// ?run@Rva003EEB50@@QAE_NHH@Z
bool Rva003EEB50::run( int cellX, int cellY )
{
	return m_pf->checkForTarget( m_obj, cellX, cellY, m_weapon, m_victim,
		m_victimPos, m_radius, m_center, m_dest );
}

// cl: /DNDEBUG /MD /EHsc
// readable body of ?getPosition@ParticleSystem@@QAEXPAUCoord3D@@@Z: Code/GameEngine/Source/GameClient/System/ParticleSys.cpp
// Open-BFME5: ParticleSystem::getPosition, retail 0x005BDDB0, 63 bytes.
//
// The three components are read out of three 0x10-strided members into a local
// Coord3D and copied out only when the caller passed one. MSVC keeps x on the
// x87 stack across the null test, which is why the miss path has a bare
// fstp st(0).

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include/Lib/BaseType.h
struct Coord3D
{
	float x;
	float y;
	float z;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameClient/ParticleSys.h
class ParticleSystem
{
public:
	void getPosition(Coord3D *pos);

private:
	unsigned char m_unmodelled_000[0xcc];
	float m_posX;						// this+0xCC
	unsigned char m_unmodelled_0d0[0xc];
	float m_posY;						// this+0xDC
	unsigned char m_unmodelled_0e0[0xc];
	float m_posZ;						// this+0xEC
};

// ?getPosition@ParticleSystem@@QAEXPAUCoord3D@@@Z
void ParticleSystem::getPosition(Coord3D *pos)
{
	Coord3D p;

	p.x = m_posX;
	p.y = m_posY;
	p.z = m_posZ;

	if (pos)
	{
		pos->x = p.x;
		pos->y = p.y;
		pos->z = p.z;
	}
}

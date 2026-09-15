// ?attachParticleSystem@Gen0060C510Target@@QAEXPAVBfmeParticleSystemHandle@@UCoord3D@@@Z
// The first Living World target list calls this method through thunk 0x00037BCD.
// The method adopts the handle, then stores the target origin at this+0xA0.

struct Coord3D
{
	float x;
	float y;
	float z;
};

class BfmeParticleSystemHandle;

class Gen0060C510Target
{
public:
	void adoptParticleSystem(BfmeParticleSystemHandle *handle);
	void attachParticleSystem(BfmeParticleSystemHandle *handle, Coord3D origin);

private:
	unsigned char m_pad00[0x14];
	unsigned char m_particleSystem[0x0c];
	unsigned char m_particleSystemID[4];
	unsigned char m_pad24[0x7c];
	Coord3D m_origin;
};

void Gen0060C510Target::attachParticleSystem(BfmeParticleSystemHandle *handle, Coord3D origin)
{
	adoptParticleSystem(handle);
	m_origin = origin;
}

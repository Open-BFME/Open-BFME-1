// cl: /O2
// Open-BFME: ParticleSystem::setPosition, retail 0x005BDE00 (40 bytes).
// The reviewed ILT pin at 0x00021832 targets this body.  The field stores are
// the three Matrix3D translation components at +0xCC/+0xDC/+0xEC followed by
// the reference source's local-identity invalidation at +0x1A4.

struct Coord3D
{
	float x;
	float y;
	float z;
};

class Matrix3D
{
public:
	__forceinline void Set_X_Translation(float x) { m_row0[3] = x; }
	__forceinline void Set_Y_Translation(float y) { m_row1[3] = y; }
	__forceinline void Set_Z_Translation(float z) { m_row2[3] = z; }

private:
	float m_row0[4];
	float m_row1[4];
	float m_row2[4];
};

class ParticleSystem
{
public:
	void setPosition(const Coord3D *pos);

private:
	unsigned char m_beforeLocalTransform[0xC0];
	Matrix3D m_localTransform;
	unsigned char m_afterLocalTransform[0x1A4 - 0xF0];
	bool m_isLocalIdentity;
};

void ParticleSystem::setPosition(const Coord3D *pos)
{
	m_localTransform.Set_X_Translation(pos->x);
	m_localTransform.Set_Y_Translation(pos->y);
	m_localTransform.Set_Z_Translation(pos->z);
	m_isLocalIdentity = false;
}

// Open-BFME: ParticleSystem::rotateLocalTransformZ, retail 0x005BE060
// (152 bytes).  This is the Z member of the adjacent transform family: its
// Matrix3D starts at +0xC0 and the local-identity flag is at +0x1A4.

extern "C" double sin(double x);
extern "C" double cos(double x);

#pragma intrinsic(sin, cos)

class Matrix3D
{
public:
	__forceinline void Rotate_Z(float theta)
	{
		float c = (float)cos(theta);
		float s = (float)sin(theta);
		float xComponent;
		float yComponent;

		xComponent = m_row[0][0];
		yComponent = m_row[0][1];
		m_row[0][0] = c * xComponent + s * yComponent;
		m_row[0][1] = c * yComponent - s * xComponent;

		xComponent = m_row[1][0];
		yComponent = m_row[1][1];
		m_row[1][0] = c * xComponent + s * yComponent;
		m_row[1][1] = c * yComponent - s * xComponent;

		xComponent = m_row[2][0];
		yComponent = m_row[2][1];
		m_row[2][0] = c * xComponent + s * yComponent;
		m_row[2][1] = c * yComponent - s * xComponent;
	}

private:
	volatile float m_row[3][4];
};

class ParticleSystem
{
public:
	void rotateLocalTransformZ(float z);

private:
	unsigned char m_beforeLocalTransform[0xC0];
	Matrix3D m_localTransform;
	unsigned char m_afterLocalTransform[0x1A4 - 0xF0];
	volatile unsigned char m_isLocalIdentity;
};

void ParticleSystem::rotateLocalTransformZ(float z)
{
	m_localTransform.Rotate_Z(z);
	m_isLocalIdentity = false;
}

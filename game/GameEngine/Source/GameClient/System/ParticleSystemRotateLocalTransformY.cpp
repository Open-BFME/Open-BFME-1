// Open-BFME: ParticleSystem::rotateLocalTransformY, retail 0x005BDFA0
// (152 bytes).  This is the Y member of the adjacent transform family: its
// Matrix3D starts at +0xC0 and the local-identity flag is at +0x1A4.

extern "C" double sin(double x);
extern "C" double cos(double x);

#pragma intrinsic(sin, cos)

class Matrix3D
{
public:
	__forceinline void Rotate_Y(float theta)
	{
		float s = (float)sin(theta);
		float c = (float)cos(theta);
		float tmp1;
		float tmp2;

		tmp1 = m_row[0][0];
		tmp2 = m_row[0][2];
		m_row[0][0] = c * tmp1 - s * tmp2;
		m_row[0][2] = c * tmp2 + s * tmp1;

		tmp1 = m_row[1][0];
		tmp2 = m_row[1][2];
		m_row[1][0] = c * tmp1 - s * tmp2;
		m_row[1][2] = c * tmp2 + s * tmp1;

		tmp1 = m_row[2][0];
		tmp2 = m_row[2][2];
		m_row[2][0] = c * tmp1 - s * tmp2;
		m_row[2][2] = c * tmp2 + s * tmp1;
	}

private:
	volatile float m_row[3][4];
};

class ParticleSystem
{
public:
	void rotateLocalTransformY(float y);

private:
	unsigned char m_beforeLocalTransform[0xC0];
	Matrix3D m_localTransform;
	unsigned char m_afterLocalTransform[0x1A4 - 0xF0];
	volatile unsigned char m_isLocalIdentity;
};

void ParticleSystem::rotateLocalTransformY(float y)
{
	m_localTransform.Rotate_Y(y);
	m_isLocalIdentity = false;
}

// Open-BFME: ParticleSystem::rotateLocalTransformX, retail 0x005BDEE0
// (152 bytes).  This is the X member of the adjacent transform family: its
// Matrix3D starts at +0xC0 and the local-identity flag is at +0x1A4.

extern "C" double sin(double x);
extern "C" double cos(double x);

#pragma intrinsic(sin, cos)

class Matrix3D
{
public:
	__forceinline void Rotate_X(float theta)
	{
		float s = (float)sin(theta);
		float c = (float)cos(theta);
		float tmp1;
		float tmp2;

		tmp1 = m_row[0][1];
		tmp2 = m_row[0][2];
		m_row[0][1] = c * tmp1 + s * tmp2;
		m_row[0][2] = c * tmp2 - s * tmp1;

		tmp1 = m_row[1][1];
		tmp2 = m_row[1][2];
		m_row[1][1] = c * tmp1 + s * tmp2;
		m_row[1][2] = c * tmp2 - s * tmp1;

		tmp1 = m_row[2][1];
		tmp2 = m_row[2][2];
		m_row[2][1] = c * tmp1 + s * tmp2;
		m_row[2][2] = c * tmp2 - s * tmp1;
	}

private:
	volatile float m_row[3][4];
};

class ParticleSystem
{
public:
	void rotateLocalTransformX(float x);

private:
	unsigned char m_beforeLocalTransform[0xC0];
	Matrix3D m_localTransform;
	unsigned char m_afterLocalTransform[0x1A4 - 0xF0];
	volatile unsigned char m_isLocalIdentity;
};

void ParticleSystem::rotateLocalTransformX(float x)
{
	m_localTransform.Rotate_X(x);
	m_isLocalIdentity = false;
}

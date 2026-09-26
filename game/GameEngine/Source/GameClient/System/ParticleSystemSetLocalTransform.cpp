// cl: /O2
// Open-BFME: ParticleSystem::setLocalTransform, retail 0x005BDE40
// (121 bytes).  It is the reference ParticleSys.cpp method immediately after
// the reviewed setPosition body: copy the 3x4 Matrix3D at +0xC0 and clear the
// same local-identity flag at +0x1A4.

class Matrix3D
{
public:
	__forceinline Matrix3D &operator=(const Matrix3D &that)
	{
		m_elements[0] = that.m_elements[0];
		m_elements[1] = that.m_elements[1];
		m_elements[2] = that.m_elements[2];
		m_elements[3] = that.m_elements[3];
		m_elements[4] = that.m_elements[4];
		m_elements[5] = that.m_elements[5];
		m_elements[6] = that.m_elements[6];
		m_elements[7] = that.m_elements[7];
		m_elements[8] = that.m_elements[8];
		m_elements[9] = that.m_elements[9];
		m_elements[10] = that.m_elements[10];
		m_elements[11] = that.m_elements[11];
		return *this;
	}

	unsigned int m_elements[12];
};

class ParticleSystem
{
public:
	void setLocalTransform(const Matrix3D *matrix);

private:
	unsigned char m_beforeLocalTransform[0xC0];
	Matrix3D m_localTransform;
	unsigned char m_afterLocalTransform[0x1A4 - 0xF0];
	bool m_isLocalIdentity;
};

void ParticleSystem::setLocalTransform(const Matrix3D *matrix)
{
	m_localTransform = *matrix;
	m_isLocalIdentity = false;
}

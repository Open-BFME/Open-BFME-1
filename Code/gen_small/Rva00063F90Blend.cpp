// cl: /DNDEBUG /MD /EHs-c-
// 0x00063F90: (1-t)*(0.5*(1-t) + (7/6)*t) + t*t over the image float pool.

class Rva00063F90Blend
{
public:
	float eval(void) const;

private:
	unsigned char m_pad[0x10];
	float m_t;											///< this+0x10
};

// ?eval@Rva00063F90Blend@@QBEMXZ
float Rva00063F90Blend::eval(void) const
{
	float t = m_t;
	float u = 1.0f - t;
	return u * (0.5f * u + (7.0f / 6.0f) * t) + t * t;
}

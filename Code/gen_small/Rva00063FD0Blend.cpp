// cl: /DNDEBUG /MD /EHs-c-
// 0x00063FD0: sibling of 0x00063F90. Computes u=1-s then s=1-u so the
// evaluator is s*(0*s + (5/6)*u) + 0.5*u*u over the image float pool.

class Rva00063FD0Blend
{
public:
	float eval(void) const;

private:
	unsigned char m_pad[0x14];
	float m_s;											///< this+0x14
};

// ?eval@Rva00063FD0Blend@@QBEMXZ
float Rva00063FD0Blend::eval(void) const
{
	float u = 1.0f - m_s;
	float s = 1.0f - u;
	return s * (0.0f * s + (5.0f / 6.0f) * u) + 0.5f * u * u;
}

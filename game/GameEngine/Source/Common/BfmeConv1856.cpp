extern "C" double __cdecl sqrt(double x);

extern const float g_bfmeZeroXY;

struct BfmeVecXY
{
	float m_bfmeXXY;
	float m_bfmeYXY;
	float m_bfmeZXY;
};

float bfmeDistXY(BfmeVecXY *a, float az, float ashrink, BfmeVecXY *b, float bz, float bshrink)
{
	float dx = a->m_bfmeXXY - b->m_bfmeXXY;
	float dy = a->m_bfmeYXY - b->m_bfmeYXY;
	float dz = az + a->m_bfmeZXY - b->m_bfmeZXY - bz;
	float d = (float)sqrt(dz * dz + dy * dy + dx * dx) - ashrink - bshrink;

	if (d < g_bfmeZeroXY)
		return g_bfmeZeroXY;

	return d * d;
}

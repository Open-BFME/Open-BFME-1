// Open-BFME5 conversions.

extern "C" double sqrt(double value);
#pragma intrinsic(sqrt)

struct BfmePt951
{
	float m_bfmeX;
	float m_bfmeY;
};

class BfmeGap951
{
public:
	float bfmeGapA951(const BfmePt951 *a, const BfmePt951 *b) const;
	float bfmeGapB951(const BfmePt951 *other) const;
private:
	int m_bfmeGap[14];
	float m_bfmeX;
	float m_bfmeY;
	int m_bfmeGap2[31];
	float m_bfmeRadius;
};

float BfmeGap951::bfmeGapA951(const BfmePt951 *a, const BfmePt951 *b) const
{
	float dx = a->m_bfmeX - b->m_bfmeX;
	float dy = a->m_bfmeY - b->m_bfmeY;

	float gap = (float)sqrt(dx * dx + dy * dy) - m_bfmeRadius;
	if (gap < 0.0f)
		return 0.0f;
	return gap * gap;
}

float BfmeGap951::bfmeGapB951(const BfmePt951 *other) const
{
	float dx = m_bfmeX - other->m_bfmeX;
	float dy = m_bfmeY - other->m_bfmeY;

	float gap = (float)sqrt(dx * dx + dy * dy) - m_bfmeRadius;
	if (gap < 0.0f)
		return 0.0f;
	return gap * gap;
}

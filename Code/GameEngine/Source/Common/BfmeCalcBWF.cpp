// BFME coordinate transform at RVA 0x0087E0D0; callers carry the angle as float bits.
extern "C" double __cdecl sin(double);
extern "C" double __cdecl cos(double);
extern const float BfmeZeroRange;
class BfmeRetBWF { public: float x; float y; float z; };
class BfmeCalcBWF
{
public:
	bool bfmeCalcBWF(BfmeRetBWF *one, float value, BfmeRetBWF *two);
private:
	char pad[8]; float m_field0x8; float m_field0xc;
};
bool BfmeCalcBWF::bfmeCalcBWF(BfmeRetBWF *one, float angle, BfmeRetBWF *two)
{
	BfmeRetBWF *source = *(BfmeRetBWF * volatile *)&one;
	const float firstZero = BfmeZeroRange;
	*two = *source;
	if (m_field0x8 == firstZero && m_field0xc == BfmeZeroRange) return false;
	float sine=(float)sin(angle); float cosine=(float)cos(angle);
	two->x += cosine*m_field0x8 + sine*m_field0xc;
	two->y += sine*m_field0x8 + cosine*m_field0xc;
	return true;
}


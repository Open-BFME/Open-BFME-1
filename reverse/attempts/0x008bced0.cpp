// ?d_008bced0@@YAXXZ
// partial score=0.96 date=2026-08-30
struct BfmeTransform1236;

struct BfmeMatrix1236
{
	float m_values[16];
};

void bfmeCombine1236(BfmeTransform1236 *result, BfmeTransform1236 *left, BfmeTransform1236 *right)
{
	BfmeMatrix1236 a = *(BfmeMatrix1236 *)left;
	BfmeMatrix1236 b = *(BfmeMatrix1236 *)right;
	float *output = (float *)result;
	output[0] = a.m_values[0] * b.m_values[0] + a.m_values[4] * b.m_values[1];
	output[1] = a.m_values[1] * b.m_values[0] + a.m_values[5] * b.m_values[1];
	float value = b.m_values[5] * a.m_values[4];
	value += b.m_values[4] * a.m_values[0];
	output[4] = value;
	value = b.m_values[5] * a.m_values[5];
	value += b.m_values[4] * a.m_values[1];
	output[5] = value;
	value = b.m_values[13] * a.m_values[4];
	value += b.m_values[12] * a.m_values[0];
	value += a.m_values[12];
	output[12] = value;
	value = b.m_values[13] * a.m_values[5];
	value += b.m_values[12] * a.m_values[1];
	value += a.m_values[13];
	output[13] = value;
}

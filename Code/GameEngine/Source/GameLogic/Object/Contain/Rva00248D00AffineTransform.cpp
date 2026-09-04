// cl: /DNDEBUG /MD /EHsc
// 0x00248D00 -- transform a point through the 3x4 matrix at +0x08.

struct BfmeRva48D00Coord
{
	float m_x;
	float m_y;
	float m_z;
};

extern "C" void _ReadWriteBarrier();
#pragma intrinsic(_ReadWriteBarrier)

class Rva00248D00
{
public:
	void transform(const BfmeRva48D00Coord *input,
		BfmeRva48D00Coord *output);

	char m_head[8];
	float *m_matrix;
};

// @?transform@Rva00248D00@@QAEXPBUBfmeRva48D00Coord@@PAU2@@Z 0x00248D00
void Rva00248D00::transform(const BfmeRva48D00Coord *input,
	BfmeRva48D00Coord *output)
{
	BfmeRva48D00Coord point = *input;
	float x = point.m_x;
	float y = point.m_y;
	float z = point.m_z;
	float *matrix = m_matrix + 2;

	float third = z * matrix[2] + y * matrix[1] +
		x * matrix[0] + matrix[3];
	float second = z * matrix[6] + y * matrix[5] +
		x * matrix[4] + matrix[7];
	float first = z * matrix[10] + y * matrix[9] +
		x * matrix[8] + matrix[11];

	_ReadWriteBarrier();

	output->m_x = third;
	output->m_y = second;
	output->m_z = first;
}

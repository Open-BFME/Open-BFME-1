// ?d_00248d00@@YAXXZ
// partial score=0.98 date=2026-09-03
// cl: /DNDEBUG /MD /EHsc

struct BfmeRva48D00Coord
{
	void set(float z, float y, float x)
	{
		m_x = z;
		m_y = x;
		m_z = y;
	}

	float m_x;
	float m_y;
	float m_z;
};

class Rva00248D00
{
public:
	void transform(const BfmeRva48D00Coord *input,
		BfmeRva48D00Coord *output);

	char m_head[8];
	float *m_matrix;
};

void Rva00248D00::transform(const BfmeRva48D00Coord *input,
	BfmeRva48D00Coord *output)
{
	BfmeRva48D00Coord point = *input;
	float x = point.m_x;
	float y = point.m_y;
	float z = point.m_z;
	float *matrix = m_matrix + 2;

	output->set(
		z * matrix[10] + y * matrix[9] +
		x * matrix[8] + matrix[11],
		z * matrix[6] + y * matrix[5] +
		x * matrix[4] + matrix[7],
		z * matrix[2] + y * matrix[1] +
		x * matrix[0] + matrix[3]);
}

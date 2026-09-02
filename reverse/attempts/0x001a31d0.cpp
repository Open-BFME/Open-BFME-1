// ?consider@Rva001A31D0Candidate@@QAEXPAURva001A31D0Point@@0@Z
// partial score=0.82 date=2026-09-01
// cl: /O2

struct Rva001A31D0Vector
{
	float m_x;
	float m_y;
	int m_z;
};

struct Rva001A31D0Point
{
	Rva001A31D0Vector m_position;
	int m_tag;
};

class Rva001A31D0Candidate
{
public:
	void consider(Rva001A31D0Point *point, Rva001A31D0Point *other);

private:
	Rva001A31D0Vector m_point;
	int m_tag;
	float m_score;
	Rva001A31D0Point *m_source;
};

void Rva001A31D0Candidate::consider(Rva001A31D0Point *point, Rva001A31D0Point *other)
{
	volatile float *pointX = &point->m_position.m_x;
	volatile float *pointY = &point->m_position.m_y;
	volatile float *otherY = &other->m_position.m_y;
	float y = *otherY;
	float x = *pointX;
	if (m_tag != 0)
		x -= *pointX;

	float dy = y - *pointY;
	float score = dy * dy + x * x;
	if (m_tag == 0 || score < m_score)
	{
		m_tag = point->m_tag;
		m_point = point->m_position;
		m_score = score;
		m_source = point;
	}
}

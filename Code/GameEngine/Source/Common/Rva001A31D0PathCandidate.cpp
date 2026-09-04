// cl: /O2

struct Rva001A31D0Position
{
	float m_x;
	float m_y;
	int m_z;
	};

struct Rva001A31D0Point
	{
	Rva001A31D0Position m_position;
	int m_tag;
};

class Rva001A31D0Candidate
{
public:
	void consider(Rva001A31D0Point *candidate, Rva001A31D0Point *query);

private:
	Rva001A31D0Position m_position;
	int m_tag;
	float m_score;
	Rva001A31D0Point *m_source;
};

static inline float Rva001A31D0Square(float value)
{
	return value * value;
}

void Rva001A31D0Candidate::consider(Rva001A31D0Point *candidate,
	Rva001A31D0Point *query)
{
	volatile Rva001A31D0Point *orderedQuery = query;
	float dy = orderedQuery->m_position.m_y;
	Rva001A31D0Point *point = candidate;
	float dx = orderedQuery->m_position.m_x;
	int tag = m_tag;
	dx -= point->m_position.m_x;
	volatile float work[3];
	work[0] = dx;
	dy -= point->m_position.m_y;
	float score = dy * dy;
	score += work[0] * work[0];
	if (tag == 0 || score < m_score)
	{
		m_tag = candidate->m_tag;
		m_position = candidate->m_position;
		m_score = score;
		m_source = candidate;
	}
}

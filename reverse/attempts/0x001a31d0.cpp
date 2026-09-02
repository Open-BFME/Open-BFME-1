// ?consider@Rva001A31D0Candidate@@QAEXPAURva001A31D0Point@@0@Z
// partial score=0.78 date=2026-09-02
// cl: /O2

struct Rva001A31D0Point
{
	float m_x;
	float m_y;
	int m_z;
	int m_tag;
};

class Rva001A31D0Candidate
{
public:
	void consider(Rva001A31D0Point *candidate, Rva001A31D0Point *query);

private:
	float m_x;
	float m_y;
	int m_z;
	int m_tag;
	float m_score;
	Rva001A31D0Point *m_source;
};

void Rva001A31D0Candidate::consider(Rva001A31D0Point *candidate, Rva001A31D0Point *query)
{
	float y = query->m_y;
	float x = query->m_x;
	int tag = m_tag;
	x -= candidate->m_x;
	y -= candidate->m_y;
	float score = y * y + x * x;
	if (tag == 0 || score < m_score)
	{
		m_tag = candidate->m_tag;
		m_x = candidate->m_x;
		m_y = candidate->m_y;
		m_z = candidate->m_z;
		m_score = score;
		m_source = candidate;
	}
}

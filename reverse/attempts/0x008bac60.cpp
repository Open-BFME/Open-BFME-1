// ?bfmeContains1283@BfmeTriangle1283@@QBEHMM@Z
// partial score=0.99 date=2026-08-30
class BfmeTriangle1283
{
public:
	int bfmeContains1283(float x, float y) const;

private:
	float m_x0;
	float m_y0;
	float m_x1;
	float m_y1;
	float m_x2;
	float m_y2;
};

int BfmeTriangle1283::bfmeContains1283(float x, float y) const
{
	int inside = 0;
	if (((m_y0 <= y && y < m_y2) || (m_y2 <= y && y < m_y0)) &&
		m_x0 + (m_x2 - m_x0) * (y - m_y0) / (m_y2 - m_y0) > x)
		inside = 1;

	if (((m_y1 <= y && y < m_y0) || (m_y0 <= y && y < m_y1)) &&
		m_x1 + (m_x0 - m_x1) * (y - m_y1) / (m_y0 - m_y1) > x)
		inside = !inside;

	if (((m_y2 <= y && y < m_y1) || (m_y1 <= y && y < m_y2)) &&
		m_x2 + (m_x1 - m_x2) * (y - m_y2) / (m_y1 - m_y2) > x)
		inside = !inside;

	return inside;
}
// cl: /O2 /DNDEBUG /DWIN32 /D_WINDOWS /MD

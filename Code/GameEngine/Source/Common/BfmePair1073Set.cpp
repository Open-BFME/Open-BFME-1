// cl: /DNDEBUG /MD /EHsc

// retail 0x004AFA10, 75 bytes. If the cached float pair changed, format it
// through bfmeGo1073B (0x00565DF0) and store the new values.

struct BfmeN1073
{
	char *m_bfme00;
};

void bfmeGo1073B(BfmeN1073 *n, float b, float c);

class BfmePair1073
{
public:
	void set(float x, float y);

private:
	char m_pad[8];
	BfmeN1073 m_node;			// +0x08
	float m_x;				// +0x0C
	float m_y;				// +0x10
};

void BfmePair1073::set(float x, float y)
{
	if (x != m_x || y != m_y)
	{
		bfmeGo1073B(&m_node, x, y);
		m_x = x;
		m_y = y;
	}
}

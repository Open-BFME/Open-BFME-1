// Clean reconstruction of the two-stage guarded release at retail RVA
// 0x0093C400.  The owning type and imported routine identities are not
// recovered; the field offsets and stdcall call boundaries are observed.

typedef void (__stdcall *Gen_0093C400_Pair)(void *, void *);
typedef void (__stdcall *Gen_0093C400_One)(void *);

extern Gen_0093C400_Pair g_pair;
extern Gen_0093C400_One g_release;
extern Gen_0093C400_One g_destroy;

class Gen_0093C400
{
public:
	void process();

private:
	unsigned char m_pad[4];
	void *m_first;
	void *m_second;
	unsigned char m_gap[4];
	void *m_third;
};

void Gen_0093C400::process()
{
	if (m_second != 0) {
		g_pair(m_third, m_first);
		g_release(m_second);
		m_second = 0;
	}
	if (m_third != 0) {
		g_destroy(m_third);
		m_third = 0;
	}
}

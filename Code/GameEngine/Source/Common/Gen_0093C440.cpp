// Clean reconstruction of the guarded release and optional cleanup at retail
// RVA 0x0093C440.  Its first three fields share the observed layout of the
// related release body at 0x0093C400.

extern "C" void cleanup(void *);

typedef void (__stdcall *Gen_0093C440_Pair)(void *, void *);
typedef void (__stdcall *Gen_0093C440_One)(void *);

extern Gen_0093C440_Pair g_pair;
extern Gen_0093C440_One g_release;
extern Gen_0093C440_One g_destroy;

class Gen_0093C440
{
public:
	Gen_0093C440 *process(int flags);

private:
	unsigned char m_pad[4];
	void *m_first;
	void *m_second;
	unsigned char m_gap[4];
	void *m_third;
};

Gen_0093C440 *Gen_0093C440::process(int flags)
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
	if ((flags & 1) != 0)
		cleanup(this);
	return this;
}

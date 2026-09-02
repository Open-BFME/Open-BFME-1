// ??1Gen00809750@@QAE@XZ
// partial score=0.82 date=2026-09-02
// cl: /DNDEBUG /MD /EHs-c-
class BfmeSub1045 {
public:
	void bfmeDone1045();
	int m_gap[4];
	int m_id;
};
void bfmeFreeSizedVF(void *block, unsigned int size);

class GenAlloc {
public:
	virtual void v0();
	virtual void v1();
	virtual void *allocate(unsigned int size, int flags);
	virtual void release(void *block, int flags);
};
GenAlloc *Gen007EFFC0();

class Gen00809750 {
public:
	~Gen00809750();
	int m_gap00;
	int m_count;
	BfmeSub1045 **m_array;
};

Gen00809750::~Gen00809750()
{
	int i;
	BfmeSub1045 *elem;

	for (i = 0; i < m_count; i++)
	{
		elem = m_array[i];
		if (elem != 0)
		{
			elem->bfmeDone1045();
			bfmeFreeSizedVF(elem, 0x38);
			m_array[i] = 0;
		}
	}
	Gen007EFFC0()->release(m_array, 0);
	m_array = 0;
}

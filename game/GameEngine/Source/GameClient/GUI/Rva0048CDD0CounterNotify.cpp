// cl: /DNDEBUG /MD /EHsc
// Open-BFME5: address-derived counter/notification method at 0x0048CDD0.

extern void *Rva012ED238Global;
void __stdcall Rva009F8878Notify(void *, void *);

class Rva0048CDD0CounterNotify
{
public:
	void decrementAndNotify();
	void incrementAndNotify();
	int  test() const;
	bool isMatch(int id) const;

private:
	unsigned char m_unknown00[0x0C];
	int  m_id;
	void *m_value;
	unsigned char m_unknown14[4];
	int  m_count;
};

void Rva0048CDD0CounterNotify::decrementAndNotify()
{
	if (--m_count <= 0) {
		m_count = 0;
		Rva009F8878Notify(Rva012ED238Global, m_value);
	}
}

void Rva0048CDD0CounterNotify::incrementAndNotify()
{
	++m_count;
	Rva009F8878Notify(Rva012ED238Global, 0);
}

int Rva0048CDD0CounterNotify::test() const
{
	if (m_value && !m_count)
		return 1;
	return 0;
}

bool Rva0048CDD0CounterNotify::isMatch(int id) const
{
	return m_id == id;
}

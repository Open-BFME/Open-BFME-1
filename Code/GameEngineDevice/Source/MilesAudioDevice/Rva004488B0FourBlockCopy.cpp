struct Rva004488B0Block
{
	void *first;
	void *second;
	void *third;
};

class BfmeSubBQC
{
public:
	void bfmeStepBQC();
};

class Rva004488B0FourBlockRecord
{
public:
	void copy(const Rva004488B0Block &a,
		const Rva004488B0Block &b, const Rva004488B0Block &c,
		const Rva004488B0Block &d);

private:
	Rva004488B0Block m_a;
	Rva004488B0Block m_b;
	Rva004488B0Block m_c;
	Rva004488B0Block m_d;
	BfmeSubBQC m_bqc;
};

void Rva004488B0FourBlockRecord::copy(
	const Rva004488B0Block &a, const Rva004488B0Block &b,
	const Rva004488B0Block &c, const Rva004488B0Block &d)
{
	m_a = b;
	m_b = a;
	m_c = c;
	m_d = d;
	m_bqc.bfmeStepBQC();
}

// ??1Gen_dtor_0007ba60@@UAE@XZ
// partial score=0.78 date=2026-09-01
// cl: /O2 /Ob2 /G6
// Open-BFME5: clean C++ conversion of the reference-owning destructor.

class Rva0007B8B0Reference
{
public:
	virtual void deleteThis(unsigned int deleting) = 0;

	unsigned int m_references;
};

class Gen_dtor_0007ba60
{
public:
	virtual ~Gen_dtor_0007ba60();

private:
	unsigned int m_unused;
	Rva0007B8B0Reference *m_reference;
};

Gen_dtor_0007ba60::~Gen_dtor_0007ba60()
{
	if (m_reference)
	{
		unsigned int references = m_reference->m_references - 1;
		m_reference->m_references = references;
		if (static_cast<int>(references) <= 0)
			m_reference->deleteThis(1);
	}
}

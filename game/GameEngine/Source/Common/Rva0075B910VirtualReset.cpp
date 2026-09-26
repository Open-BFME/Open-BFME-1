// Open-BFME: null-guarded virtual reset reconstructed from retail RVA 0x0075B910.

class Rva0075B910Target
{
public:
	virtual void slot0(void);
	virtual void slot1(void);
	virtual void release(void);
};

class Rva0075B910Object
{
public:
	void reset(void);

private:
	char m_pad0[0x3C];
	Rva0075B910Target *m_target;
};

void Rva0075B910Object::reset(void)
{
	Rva0075B910Target *target = m_target;
	if (target != 0)
		target->release();
	m_target = 0;
}

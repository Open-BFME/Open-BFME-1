// cl: /DNDEBUG /MD /EHsc

struct Rva0060A1D0State
{
	Rva0060A1D0State(const Rva0060A1D0State &that)
		: m_a(that.m_a), m_b(that.m_b), m_c(that.m_c) {}
	~Rva0060A1D0State() {}

	int m_a;
	int m_b;
	int m_c;
};

class Rva0060A1D0Target
{
public:
	virtual void slot00(); virtual void slot04(); virtual void slot08(); virtual void apply();
	virtual void slot10(); virtual void slot14(); virtual void slot18();
	virtual void setState(Rva0060A1D0State state);
};

class BfmeSubDGE
{
public:
	void bfmeRunDGE(void *data);

private:
	char m_pad00[4];
	Rva0060A1D0Target *m_target;
	char m_pad08[0x14];
	Rva0060A1D0State m_state;
};

// ?bfmeRunDGE@BfmeSubDGE@@QAEXPAX@Z
void BfmeSubDGE::bfmeRunDGE(void *data)
{
	const Rva0060A1D0State &state = *static_cast<Rva0060A1D0State *>(data);
	m_state = state;
	if (m_target != 0)
	{
		m_target->setState(state);
		m_target->apply();
	}
}

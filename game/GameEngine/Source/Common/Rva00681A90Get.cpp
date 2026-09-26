// cl: /DNDEBUG /MD /O2

class Gen_0066b120
{
public:
	int m(void);
};

class Rva00681A90Target
{
public:
	char m_pad0[0x120e0];
	Gen_0066b120 *m_value;
};

class Rva00681A90Owner
{
public:
	int get(void);

private:
	char m_pad0[8];
	Rva00681A90Target *m_target;
};

int Rva00681A90Owner::get(void)
{
	if (m_target != 0) {
		Gen_0066b120 *value = m_target->m_value;
		if (value != 0)
			return value->m();
	}
	return 0;
}

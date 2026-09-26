// cl: /DNDEBUG /MD /EHsc

class Rva0056C090
{
public:
	int helper();
	void update(int unused);

private:
	unsigned char m_pad[0x258];
	int m_state;
};

void Rva0056C090::update(int unused)
{
	if (m_state == 0)
	{
		if (helper())
			m_state = 12;
	}
}

// cl: /O2 /Ob0 /DNDEBUG /DWIN32 /D_WINDOWS /MD

struct Rva00409570State
{
	char m_pad[0x40];
	volatile int m_value;
};

class Rva00409570Owner
{
public:
	int check(void);

private:
	char m_pad[4];
	Rva00409570State *m_state;
};

int Rva00409570Owner::check(void)
{
	int value = m_state->m_value;
	if (value == 1)
		return value;
	return value;
}

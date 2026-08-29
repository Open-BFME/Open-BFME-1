// Clean reconstruction of the 21-byte retail leaf at RVA 0x007287E0.
// The final EAX value is the returned state, not dead register residue.

class Rva007287E0StateReset
{
public:
	int setAndClear(unsigned char *flag);

private:
	unsigned char m_opaque[0x80];
	int m_state;
};

int Rva007287E0StateReset::setAndClear(unsigned char *flag)
{
	m_state = 1;
	*flag = 0;
	return 1;
}

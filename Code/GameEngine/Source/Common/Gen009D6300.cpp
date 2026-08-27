// cl: /DNDEBUG /MD /O2
// Clean C++ conversion of the optional activation helper at retail RVA 0x009D6300.

extern "C" bool __stdcall bfmeTryActivate(void *value, int enabled, int flags);

class Gen009D6300
{
public:
	bool bfmeActivate(void *value);

private:
	unsigned char m_pad[0x44];
	int m_state;
};

bool Gen009D6300::bfmeActivate(void *value)
{
	if (value != 0 && !bfmeTryActivate(value, 1, 0))
		return false;

	m_state = 0;
	return true;
}

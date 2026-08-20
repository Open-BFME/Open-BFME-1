// cl: /DNDEBUG /MD /EHsc

// Retail 0x006EFC10. Sibling setter of the +0x178 byte getter at 0x006EFC00.

class Gen_006efc10
{
public:
	void set(unsigned char v);

private:
	unsigned char m_pad[0x178];
	unsigned char m_value;
};

// ?set@Gen_006efc10@@QAEXE@Z
void Gen_006efc10::set(unsigned char v)
{
	m_value = v;
}

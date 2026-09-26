// cl: /DNDEBUG /MD /O2
// Clean C++ conversion of the buffer reset and close helper at retail RVA 0x009D1A40.
extern "C" void __cdecl bfmeDeleteBlock(void *);

class Gen009D1A40
{
public:
	void bfmeClose();
	void bfmeReset();

private:
	unsigned char m_pad[0x14];
	void *m_buffer;
};

void Gen009D1A40::bfmeReset()
{
	if (m_buffer != 0)
	{
		bfmeDeleteBlock(m_buffer);
		m_buffer = 0;
	}
	bfmeClose();
}

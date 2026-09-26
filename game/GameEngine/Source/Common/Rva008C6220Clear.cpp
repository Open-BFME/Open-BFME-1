// cl: /O2 /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc-
// Clear the score buffers at retail RVA 0x008C6220.

extern void (__cdecl *TheBfmeFree)(void *storage, unsigned int bytes);

class Rva008C6220ScoreBuffers
{
public:
	void clear();

private:
	volatile int m_head;
	volatile int m_count1;
	void * volatile m_buffer1;
	volatile int m_pad1;
	volatile int m_count2;
	void * volatile m_buffer2;
	volatile int m_pad2;
	volatile int m_count3;
	void * volatile m_buffer3;
	volatile int m_pad3;
	volatile int m_count4;
	void * volatile m_buffer4;
	volatile int m_pad4;
	volatile int m_count5;
	void * volatile m_buffer5;
	volatile int m_pad5;
	volatile int m_count6;
	void * volatile m_buffer6;
	int m_pad6;
	int m_width;
	int m_count7;
	void * volatile m_buffer7;
};

void Rva008C6220ScoreBuffers::clear()
{
	int zero = 0;
	void *buffer = m_buffer1;

	if (buffer != 0)
		TheBfmeFree(buffer, m_count1 << 2);
	m_count1 = zero;
	m_head = zero;
	m_buffer1 = 0;

	buffer = m_buffer2;
	if (buffer != 0)
		TheBfmeFree(buffer, m_count2 << 2);
	m_count2 = zero;
	m_pad1 = zero;
	m_buffer2 = 0;

	buffer = m_buffer3;
	if (buffer != 0)
		TheBfmeFree(buffer, m_count3 << 2);
	m_count3 = zero;
	m_pad2 = zero;
	m_buffer3 = 0;

	buffer = m_buffer4;
	if (buffer != 0)
		TheBfmeFree(buffer, m_count4 << 2);
	m_count4 = zero;
	m_pad3 = zero;
	m_buffer4 = 0;

	buffer = m_buffer5;
	if (buffer != 0)
		TheBfmeFree(buffer, m_count5 << 2);
	m_count5 = zero;
	m_pad4 = zero;
	m_buffer5 = 0;

	buffer = m_buffer6;
	if (buffer != 0)
		TheBfmeFree(buffer, m_count6 << 2);
	m_count6 = zero;
	m_pad5 = zero;
	m_buffer6 = 0;

	buffer = m_buffer7;
	if (buffer != 0)
		TheBfmeFree(buffer, m_width * m_count7 << 2);
	m_width = zero;
	m_count7 = zero;
	m_pad6 = zero;
	m_buffer7 = 0;
}

// cl: /DNDEBUG /MD /O2
// Clean C++ conversion of the buffer reset and close helper at retail RVA 0x009D1A40.
void __cdecl operator delete[](void *);

class File
{
public:
	virtual void close(void);
};

class Gen009D1A40
{
public:
	void bfmeReset();

private:
	unsigned char m_pad[0x14];
	void *m_buffer;
};

void Gen009D1A40::bfmeReset()
{
	if (m_buffer != 0)
	{
		::operator delete[](m_buffer);
		m_buffer = 0;
	}
	reinterpret_cast<File *>(this)->File::close();
}

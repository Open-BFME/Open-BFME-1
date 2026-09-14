// cl: /DNDEBUG /MD /EHsc-

class Rva001DB120
{
public:
	void advance();

private:
	void *m_cursor;
};

extern "C" void _ReadWriteBarrier(void);
#pragma intrinsic(_ReadWriteBarrier)

void Rva001DB120::advance()
{
	void *cursor = m_cursor;
	if (cursor == 0)
	{
		_ReadWriteBarrier();
		return;
	}
	m_cursor = *(void **)((char *)cursor + 0x10);
}

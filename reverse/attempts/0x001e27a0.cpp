// ?d_001e27a0@@YAXXZ
// partial score=0.9 date=2026-09-12
// cl: /O2 /Ob0

extern "C" void _ReadWriteBarrier();
#pragma intrinsic(_ReadWriteBarrier)

class Rva001E27A0
{
public:
	void run();

private:
	unsigned char m_pad[8];
	int *m_begin;
	int * volatile m_end;
};

void Rva001E27A0::run()
{
	int *begin = m_begin;
	unsigned count = (unsigned)(m_end - begin);
	unsigned i = 0;
	if (count)
	{
		count = (unsigned)(m_end - begin);
		do
		{
			_ReadWriteBarrier();
			++i;
		} while (i < count);
	}
}

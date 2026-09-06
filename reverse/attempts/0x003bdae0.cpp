// ?find@Rva003BDAE0@@QAEPAVGen003BDAE0Node@@H@Z
// partial score=0.85 date=2026-09-03
// cl: /DNDEBUG /MD /O2
// Open-BFME5: first pointer in the +0x38/+0x3C vector whose payload dword at
// +8 equals the argument. Retail 0x003BDAE0, 73 bytes. this stays in ecx;
// end then begin; unsigned <=0 empty check; index in eax, cursor in edx.

class Gen003BDAE0Node
{
public:
	int m_at00;
	int m_at04;
	int m_at08;
};

class Rva003BDAE0
{
public:
	Gen003BDAE0Node *find(int key);

private:
	char m_pad00[0x38];
	Gen003BDAE0Node **m_at38;
	Gen003BDAE0Node **m_at3C;
};

// ?find@Rva003BDAE0@@QAEPAVGen003BDAE0Node@@H@Z
Gen003BDAE0Node *Rva003BDAE0::find(int key)
{
	unsigned n = (unsigned)(m_at3C - m_at38);
	unsigned i = 0;
	if (n > 0)
	{
		Gen003BDAE0Node **cursor = m_at38;
		do
		{
			Gen003BDAE0Node *node = *cursor;
			if (node->m_at08 == key)
				return m_at38[i];
			++cursor;
			++i;
		} while (i < (unsigned)(m_at3C - m_at38));
	}
	return 0;
}

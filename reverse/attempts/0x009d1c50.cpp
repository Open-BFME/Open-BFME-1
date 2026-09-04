// ?bfmeNextToken@Gen009D1C50@@QAEDPAVBfmeLayoutVHH@@@Z
// partial score=0.91 date=2026-09-02
// cl: /DNDEBUG /MD /O2
// Clean C++ conversion of the classifier tokeniser at retail RVA 0x009D1C50.

extern "C" void _ReadWriteBarrier(void);
#pragma intrinsic(_ReadWriteBarrier)

extern "C" int (__cdecl *g_bfmeFn1182)(int c);

class BfmeLayoutVHH
{
public:
	void releaseBuffer();
	void bfmeCatVHH(const char *s, int n);
};

class Gen009D1C50
{
public:
	char bfmeNextToken(BfmeLayoutVHH *out);

private:
	unsigned char m_pad[0x14];
	const char *m_buf;
	int m_pos;
	int m_end;
};

char Gen009D1C50::bfmeNextToken(BfmeLayoutVHH *out)
{
	BfmeLayoutVHH &output = *out;
	_ReadWriteBarrier();
	Gen009D1C50 *self = this;
	output.releaseBuffer();
	int (__cdecl *classify)(int) = g_bfmeFn1182;
	while (self->m_pos < self->m_end)
	{
		if (classify(static_cast<signed char>(self->m_buf[self->m_pos])) == 0)
			break;
		++self->m_pos;
	}
	if (self->m_pos >= self->m_end)
	{
		self->m_pos = self->m_end;
		return 0;
	}
	do
	{
		char ch = self->m_buf[self->m_pos];
		output.bfmeCatVHH(&ch, 1);
		++self->m_pos;
		if (self->m_pos >= self->m_end)
			break;
	}
	while (classify(static_cast<signed char>(self->m_buf[self->m_pos])) == 0);
	return 1;
}

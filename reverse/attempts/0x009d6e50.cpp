// ?bfmeBaseUpdate@Gen009D6330@@QAEXPAXPBXI@Z
// partial score=0.89 date=2026-09-02
// cl: /DNDEBUG /MD /O2
// Clean C++ conversion of the byte-block stream writer at retail RVA 0x009D6E50.

struct XferException
{
	void *text;
	int tag;
};

extern "C" XferException *__cdecl bfmeFormatText(
	XferException *result, int tag, const char *format, ...);
__declspec(noreturn) void __stdcall _CxxThrowException(void *object, void *throwInfo);
extern int g_guardTargetTypeThrowInfo;

class BfmeByteStream
{
public:
	virtual void slot0();
	virtual void slot1();
	virtual void slot2();
	virtual void slot3();
	virtual int write(const void *buffer, int size);
};

class Gen009D6330
{
public:
	void bfmeBaseUpdate(void *context, const void *bytes, unsigned int count);

private:
	unsigned char m_pad[4];
	BfmeByteStream *m_stream;
	bool m_flag;
};

void Gen009D6330::bfmeBaseUpdate(void *context, const void *bytes, unsigned int count)
{
	if (m_stream == 0)
		return;

	const void *block = bytes;
	unsigned int n = count;
	if (n != 0 && block == 0)
		return;

	if (m_flag && context != 0)
	{
		if (m_stream->write(&bytes, 4) != 4)
		{
			XferException error;
			bfmeFormatText(&error, 1, 0);
			_CxxThrowException(&error, &g_guardTargetTypeThrowInfo);
		}
	}

	if (n != 0)
	{
		if (m_stream->write(block, static_cast<int>(n)) != static_cast<int>(n))
		{
			XferException error;
			bfmeFormatText(&error, 1, 0);
			_CxxThrowException(&error, &g_guardTargetTypeThrowInfo);
		}
	}
}

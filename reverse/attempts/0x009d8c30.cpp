// ?bfmeSkipPrefixed@Gen009D8C30@@QAEXXZ
// partial score=0.82 date=2026-09-02
// cl: /DNDEBUG /MD /O2
// Clean C++ conversion of the length-prefixed skip helper at retail RVA 0x009D8C30.

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
	virtual int read(void *buffer, int size);
	virtual void slot4();
	virtual int skip(int count, int flag);
};

class Gen009D8C30
{
public:
	void bfmeSkipPrefixed();

private:
	unsigned char m_pad[0x14];
	BfmeByteStream *m_stream;
};

void Gen009D8C30::bfmeSkipPrefixed()
{
	unsigned char length;
	if (m_stream->read(&length, 1) != 1)
	{
		XferException error;
		bfmeFormatText(&error, 1, 0);
		_CxxThrowException(&error, &g_guardTargetTypeThrowInfo);
	}

	if (length == 0)
		return;
	switch (length)
	{
	case 0xff:
		{
			int count = 4;
			m_stream->skip(count, 1);
			return;
		}
	default:
		m_stream->skip(static_cast<int>(length), 1);
		return;
	}
}

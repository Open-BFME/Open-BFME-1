// cl: /DNDEBUG /MD /O2
// Clean C++ conversion of the skip-bad-block helper at retail RVA 0x009D8B60.

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

typedef void (__cdecl *BfmeSkipCallback)(void *snapshot, void *ctx, int extra);

class BlockStreamReader
{
public:
	void skipBadBlock(void *snapshot, int size);

private:
	unsigned char m_pad0[8];
	BfmeSkipCallback m_callback;
	void *m_ctx;
	unsigned char m_pad1[4];
	BfmeByteStream *m_stream;
	int m_count;
	int m_extra;
};

void BlockStreamReader::skipBadBlock(void *snapshot, int size)
{
	if (m_stream->skip(size, 0) != size)
	{
		XferException error;
		bfmeFormatText(&error, 0, "Could not skip over BAD block to %i", size);
		_CxxThrowException(&error, &g_guardTargetTypeThrowInfo);
	}

	if (m_callback)
		m_callback(snapshot, m_ctx, m_extra);
	m_extra = -1;
	--m_count;
}

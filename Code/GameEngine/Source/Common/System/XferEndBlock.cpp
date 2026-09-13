// cl: /DNDEBUG /MD /O2
// Clean C++ conversion of the BFME Xfer endBlock body at retail RVA 0x009D8AB0.

typedef bool Bool;

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

class Xfer
{
public:
	virtual void slot00();
	virtual void slot01();
	virtual void slot02();
	virtual void slot03();
	virtual void slot04();
	virtual void beginBlock(const char *name);
	virtual void endBlock();

private:
	unsigned char m_pad04[0x0c];
	Bool m_isLoading;
	unsigned char m_pad11[3];
	BfmeByteStream *m_stream;
	int m_blockCount;
	int m_currentBlock;
};

void Xfer::endBlock()
{
	if (m_stream == 0 || m_blockCount == 0)
		return;

	if (m_isLoading)
	{
		int marker;
		if (m_stream->read(&marker, 4) != 4)
		{
			XferException error;
			bfmeFormatText(&error, 1, 0);
			_CxxThrowException(&error, &g_guardTargetTypeThrowInfo);
		}

		if (marker != 0x45424c4b)
		{
			int position = m_stream->skip(0, 1) - 4;
			XferException error;
			bfmeFormatText(&error, 0,
				"Block end expected but EBLK ID was not found at %i", position);
			_CxxThrowException(&error, &g_guardTargetTypeThrowInfo);
		}
	}

	m_currentBlock = -1;
	--m_blockCount;
}

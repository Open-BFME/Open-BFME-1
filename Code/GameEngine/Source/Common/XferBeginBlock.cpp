// cl: /DNDEBUG /MD /O2
// Clean C++ conversion of the BFME Xfer beginBlock body at retail RVA 0x009D8D10.

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
	virtual void slot6();
	virtual void slot7();
	virtual void slot8();
	virtual void slot9();
	virtual void slot10();
	virtual void slot11();
	virtual int current();
};

class Gen009D8C30
{
public:
	void bfmeSkipPrefixed();
};

class Xfer
{
public:
	virtual void slot00();
	virtual void slot01();
	virtual void slot02();
	virtual void slot03();
	virtual void slot04();
	virtual int beginBlock(const char *name);
	virtual void endBlock();
	virtual void skipBlock(const char *name);

private:
	unsigned char m_pad04[0x0c];
	Bool m_isLoading;
	unsigned char m_pad11[3];
	BfmeByteStream *m_stream;
	int m_blockCount;
	int m_currentBlock;
};

int Xfer::beginBlock(const char *name)
{
	if (m_stream == 0)
		return 0;

	int marker;
	if (m_stream->read(&marker, 4) != 4)
	{
		XferException error;
		bfmeFormatText(&error, 1, 0);
		_CxxThrowException(&error, &g_guardTargetTypeThrowInfo);
	}

	if (marker == 0x44534352)
	{
		reinterpret_cast<Gen009D8C30 *>(this)->bfmeSkipPrefixed();
		if (m_stream->read(&marker, 4) != 4)
		{
			XferException error;
			bfmeFormatText(&error, 1, 0);
			_CxxThrowException(&error, &g_guardTargetTypeThrowInfo);
		}
	}

	if (marker != 0x424c4f4b)
	{
		int position = m_stream->skip(0, 1) - 4;
		XferException error;
		bfmeFormatText(&error, 0,
			"Block '%s' expected but BLOK ID was not found at %i", name, position);
		_CxxThrowException(&error, &g_guardTargetTypeThrowInfo);
	}

	if (m_isLoading)
		reinterpret_cast<Gen009D8C30 *>(this)->bfmeSkipPrefixed();

	if (m_stream->read(&marker, 4) != 4)
	{
		XferException error;
		bfmeFormatText(&error, 1, 0);
		_CxxThrowException(&error, &g_guardTargetTypeThrowInfo);
	}

	m_currentBlock = m_stream->current();
	++m_blockCount;
	return marker;
}

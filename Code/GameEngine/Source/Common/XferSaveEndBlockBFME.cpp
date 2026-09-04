// cl: /DNDEBUG /MD /O2
// ?endBlock@XferSave@@UAEXXZ
// Clean C++ conversion of the save-side Xfer endBlock body at retail RVA 0x009D7460.

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
	virtual int skip(int count, int flag);
};

class BfmePositionVector
{
public:
	int *m_begin;
	int *m_end;
	int *m_capacity;

	int &back()
	{
		return m_end[-1];
	}

	void pop_back()
	{
		--m_end;
	}
};

class XferSave
{
public:
	virtual void endBlock();

private:
	BfmeByteStream * volatile m_stream;
	bool m_flag;
	unsigned char m_pad09[3];
	BfmePositionVector m_positions;
};

void XferSave::endBlock()
{
	if (m_stream == 0)
		return;
	if (m_positions.m_begin == m_positions.m_end)
		return;

	if (m_flag)
	{
		int marker = 0x45424c4b;
		if (m_stream->write(&marker, 4) != 4)
		{
			XferException error;
			bfmeFormatText(&error, 1, 0);
			_CxxThrowException(&error, &g_guardTargetTypeThrowInfo);
		}
	}

	int blockSize = m_positions.back();
	m_positions.pop_back();

	int position = m_stream->skip(0, 1);
	if (position == -1)
	{
		XferException error;
		bfmeFormatText(&error, 1, 0);
		_CxxThrowException(&error, &g_guardTargetTypeThrowInfo);
	}

	if (m_stream->skip(blockSize, 0) != blockSize)
	{
		XferException error;
		bfmeFormatText(&error, 1, 0);
		_CxxThrowException(&error, &g_guardTargetTypeThrowInfo);
	}

	if (m_stream->write(&position, 4) != 4)
	{
		XferException error;
		bfmeFormatText(&error, 1, 0);
		_CxxThrowException(&error, &g_guardTargetTypeThrowInfo);
	}

	if (m_stream->skip(position, 0) != position)
	{
		XferException error;
		bfmeFormatText(&error, 1, 0);
		_CxxThrowException(&error, &g_guardTargetTypeThrowInfo);
	}
}

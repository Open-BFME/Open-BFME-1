// cl: /DNDEBUG /MD /O2
// Clean C++ conversion of the save-side XferEnum body at retail RVA 0x009D6E50.

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

class XferSave
{
public:
	virtual void XferEnum(void *context, const void *bytes, unsigned int count);

private:
	BfmeByteStream *m_stream;
	bool m_flag;
};

void XferSave::XferEnum(void *context, const void *bytes, unsigned int count)
{
	if (m_stream == 0)
		return;

	register const void *block = bytes;
	register unsigned int n = count;
	if (n != 0 && block == 0)
		return;

	if (m_flag && context != 0)
	{
		if (m_stream->write(&context, 4) != 4)
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

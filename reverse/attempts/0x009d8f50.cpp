// ?transfer@Rva009D8F50TransferView@@UAEXPBDPAXI@Z
// partial score=0.33 date=2026-09-22
// Transfer implementation at retail RVA 0x009D8F50.
// The +0x94 slot is reached by Xfer::XferEnum.

typedef bool Bool;

class XferException
{
	public:
	XferException(int tag, const char *format, ...);

	private:
	void *text;
	int tag;
};

__declspec(noreturn) void __stdcall _CxxThrowException(
	void *object, void *throwInfo);
extern int g_guardTargetTypeThrowInfo;

class BfmeByteStream
{
public:
	virtual void slot0();
	virtual void slot1();
	virtual void slot2();
	virtual int read(void *buffer, int size);
};

class Gen009D8C30
{
public:
	void bfmeSkipPrefixed();
};

class Rva009D8F50TransferView
{
public:
	virtual void slot00();
	virtual void slot01();
	virtual void slot02();
	virtual void slot03();
	virtual void slot04();
	virtual void slot05();
	virtual void slot06();
	virtual void slot07();
	virtual void slot08();
	virtual void slot09();
	virtual void slot10();
	virtual void slot11();
	virtual void slot12();
	virtual void slot13();
	virtual void slot14();
	virtual void slot15();
	virtual void slot16();
	virtual void slot17();
	virtual void slot18();
	virtual void slot19();
	virtual void slot20();
	virtual void slot21();
	virtual void slot22();
	virtual void slot23();
	virtual void slot24();
	virtual void slot25();
	virtual void slot26();
	virtual void slot27();
	virtual void slot28();
	virtual void slot29();
	virtual void slot30();
	virtual void slot31();
	virtual void slot32();
	virtual void slot33();
	virtual void slot34();
	virtual void slot35();
	virtual void slot36();
	virtual void transfer(const char *context, void *data, unsigned int size);

private:
	unsigned char m_pad0[0x0c];
	Bool m_isLoading;
	unsigned char m_pad1[3];
	BfmeByteStream *m_stream;
};

void Rva009D8F50TransferView::transfer(
	const char *context, void *data, unsigned int size)
{
	register void *block = data;
	register unsigned int count = size;
	if (count != 0 && block == 0)
		return;
	if (m_stream == 0)
		return;

	if (m_isLoading && context != 0)
	{
		int marker;
		if (m_stream->read(&marker, 4) != 4)
		{
			XferException error(1, 0);
			_CxxThrowException(&error, &g_guardTargetTypeThrowInfo);
		}
		while (marker == 0x44534352)
		{
			reinterpret_cast<Gen009D8C30 *>(this)->bfmeSkipPrefixed();
			if (m_stream->read(&marker, 4) != 4)
			{
				XferException error(1, 0);
				_CxxThrowException(&error, &g_guardTargetTypeThrowInfo);
			}
		}
		if (marker != reinterpret_cast<int>(context))
		{
			char expected[5];
			char found[5];
			*reinterpret_cast<int *>(expected) = reinterpret_cast<int>(context);
			*reinterpret_cast<int *>(found) = marker;
			expected[4] = 0;
			found[4] = 0;
			XferException error(0, "Expected '%s' but found '%s'",
				expected, found);
			_CxxThrowException(&error, &g_guardTargetTypeThrowInfo);
		}
	}

	if (count != 0 && m_stream->read(block, static_cast<int>(count)) !=
		static_cast<int>(count))
	{
		XferException error(1, 0);
		_CxxThrowException(&error, &g_guardTargetTypeThrowInfo);
	}
}

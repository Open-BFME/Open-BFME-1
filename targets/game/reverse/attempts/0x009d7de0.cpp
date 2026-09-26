// ??8XferSave@@UAEAAVXfer@@AAUXferReservedTag@@@Z
// partial score=0.7 date=2026-09-07
// scratch probe for the XferSave reserved-tag virtual at 0x009D7DE0

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

struct SelfPair
{
	SelfPair(void *value, void *owner) : m_value(value), m_owner(owner) {}
	void *m_value;
	void *m_owner;
};

class Gen009D76F0
{
public:
	void *evaluate(void *argument);
	void *bfmeAt(void **key);
	unsigned char m_pad[0x10];
};

class Rva009D7A40Maker : public Gen009D76F0
{
public:
	SelfPair make(void *argument);
};

struct XferReservedTag
{
	char *m_name;
};

class Xfer
{
public:
	virtual ~Xfer();
};

class XferSave : public Xfer
{
public:
	virtual Xfer &operator==(XferReservedTag &value);

private:
	BfmeByteStream *m_stream;
	bool m_flag;
	unsigned char m_pad09[0x1f];
	int m_count;
	Rva009D7A40Maker m_map;
	int m_total;
};

Xfer &XferSave::operator==(XferReservedTag &value)
{
	if (m_stream == 0)
		return *this;
	if (!m_flag)
		return *this;
	XferReservedTag *tag = &value;
	if (tag->m_name == 0 || *tag->m_name == 0)
		return *this;

	int marker = 0x44534352;
	if (m_stream->write(&marker, 4) != 4)
	{
		XferException error;
		bfmeFormatText(&error, 1, 0);
		_CxxThrowException(&error, &g_guardTargetTypeThrowInfo);
	}

	register char *name = tag->m_name;
	char *key = name;
	SelfPair pair = m_map.make(&key);
	void *found = pair.m_value;
	if (found == 0)
		return *this;

	unsigned char prefix = 0xff;
	if (m_stream->write(&prefix, 1) != 1)
	{
		XferException error;
		bfmeFormatText(&error, 1, 0);
		_CxxThrowException(&error, &g_guardTargetTypeThrowInfo);
	}

	char *payload = static_cast<char *>(found) + 8;
	if (m_stream->write(payload, 4) != 4)
	{
		XferException error;
		bfmeFormatText(&error, 1, 0);
		_CxxThrowException(&error, &g_guardTargetTypeThrowInfo);
	}

	const char *cursor = name;
	while (*cursor != 0)
		++cursor;
	unsigned int length = static_cast<unsigned int>(cursor - name);
	if (length > 0xfe)
		length = 0xfe;

	if (m_stream->write(&length, 1) != 1)
	{
		XferException error;
		bfmeFormatText(&error, 1, 0);
		_CxxThrowException(&error, &g_guardTargetTypeThrowInfo);
	}

	if (m_stream->write(name, static_cast<int>(length)) !=
		static_cast<int>(length))
	{
		XferException error;
		bfmeFormatText(&error, 1, 0);
		_CxxThrowException(&error, &g_guardTargetTypeThrowInfo);
	}

	void *slot = m_map.bfmeAt(reinterpret_cast<void **>(&key));
	*reinterpret_cast<int *>(slot) = m_count + m_total;
	return *this;
}

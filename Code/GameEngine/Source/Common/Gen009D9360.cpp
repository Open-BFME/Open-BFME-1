// cl: /DNDEBUG /MD /O2
// Clean C++ conversion of the byte formatter at retail RVA 0x009D9360.
#include <stdarg.h>
#include <string.h>

extern "C" __declspec(dllimport) int __cdecl _vsnprintf(char *, unsigned int,
	const char *, va_list);
extern const char g_bfmeByteFormat[];

struct BfmeByteValue
{
	unsigned char kind;
	unsigned char value;
};

struct BfmeAppendEntry
{
	unsigned char data[12];
};

class Gen009D9360
{
public:
	Gen009D9360 *bfmeEmit(const BfmeByteValue *value);

private:
	unsigned char m_pad[4];
	bool m_pending;
};

class BfmeAppendSink
{
public:
	virtual void _slot00() = 0;
	virtual void _slot04() = 0;
	virtual void _slot08() = 0;
	virtual void _slot0c() = 0;
	virtual void append(const char *text, int length) = 0;
};

class BfmeAppendStream
{
public:
	unsigned char m_pad[8];
	BfmeAppendSink *m_sink;
	BfmeAppendEntry *m_begin;
	BfmeAppendEntry *m_end;
};

extern "C" void __cdecl bfmeAppend(BfmeAppendStream *stream,
	const char *format, ...)
{
	char buffer[1024];

	if (format == 0)
	{
		int count = stream->m_end - stream->m_begin;
		for (int remaining = count; remaining != 0; --remaining)
			stream->m_sink->append(reinterpret_cast<const char *>(0x010E8B00), 2);
	}
	else
	{
		va_list args;
		va_start(args, format);
		_vsnprintf(buffer, sizeof(buffer), format, args);
		va_end(args);

		int length = strlen(buffer);
		BfmeAppendSink *sink = stream->m_sink;
		sink->append(buffer, length);
	}
}

Gen009D9360 *Gen009D9360::bfmeEmit(const BfmeByteValue *value)
{
	if (!m_pending)
		bfmeAppend(reinterpret_cast<BfmeAppendStream *>(this), 0);
	bfmeAppend(reinterpret_cast<BfmeAppendStream *>(this), g_bfmeByteFormat,
			static_cast<unsigned int>(value->value));
	m_pending = false;
	return this;
}

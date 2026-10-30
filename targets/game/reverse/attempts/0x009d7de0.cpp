// ?rva009D7DE0@XferSave@@UAEAAV1@AAUXferReservedTag@@@Z
// partial score=0.7443 date=2026-10-30
// cl: /DNDEBUG /MD /O2
// Save-side stream transfer and block finalization recovered under their
// reciprocal WorldBuilder TU.

class XferException
{
public:
	XferException(int tag, const char *format, ...);
	XferException(const XferException &that);
	~XferException(void);
	char *text;
	int tag;
};

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

struct SelfPair
{
	void *m_value;
	void *m_owner;
};

class Gen009D76F0
{
public:
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
	char *m_text;
};

class XferSave
{
public:
	virtual void XferEnum(void *context, const void *bytes, unsigned int count);
	virtual void endBlock();
	virtual XferSave &rva009D7DE0(XferReservedTag &str);

private:
	BfmeByteStream * volatile m_stream;
	bool m_flag;
	unsigned char m_pad09[3];
	BfmePositionVector m_positions;
	unsigned char m_pad18[0x10];
	int m_28;
	Rva009D7A40Maker m_table;
	int m_count;
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
			throw XferException(1, 0);
		}
	}

	if (n != 0)
	{
		if (m_stream->write(block, static_cast<int>(n)) != static_cast<int>(n))
		{
			throw XferException(1, 0);
		}
	}
}

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
			throw XferException(1, 0);
		}
	}

	int blockSize = m_positions.back();
	m_positions.pop_back();

	int position = m_stream->skip(0, 1);
	if (position == -1)
	{
		throw XferException(1, 0);
	}

	if (m_stream->skip(blockSize, 0) != blockSize)
	{
		throw XferException(1, 0);
	}

	if (m_stream->write(&position, 4) != 4)
	{
		throw XferException(1, 0);
	}

	if (m_stream->skip(position, 0) != position)
	{
		throw XferException(1, 0);
	}
}

extern "C" unsigned int __cdecl strlen(const char *);
#pragma intrinsic(strlen)

// Retail 0x009D7DE0 (438 B, ret 4), XferSave's interned-string writer: with a
// stream and the tagged flag set, a non-empty string is written after the
// 'RCSD' marker either as 0xFF plus the offset already recorded for it in the
// +0x2C table, or as a length byte (at most 254) and its characters,
// recording +0x28 plus +0x3C as its offset.  Ported from the BFME 2 donor
// Code/GameEngine/Source/Common/System/XferSave.cpp rva0060CE41
// (open-bfme-2 20a0cb6173); the method name is unknown, so it keeps the address.
XferSave &XferSave::rva009D7DE0(XferReservedTag &str)
{
	if (m_stream == 0)
		return *this;
	if (m_flag && str.m_text != 0 && *str.m_text != 0)
	{
		{
			int marker = 0x44534352;
			if (m_stream->write(&marker, 4) != 4)
				throw XferException(1, 0);
		}

		char *name = str.m_text;
		char *key = name;
		SelfPair pair = m_table.make(&key);
		void *found = pair.m_value;
		if (found != 0)
		{
			unsigned char escape = 0xFF;
			if (m_stream->write(&escape, 1) != 1)
				throw XferException(1, 0);
			if (m_stream->write((char *)found + 8, 4) != 4)
				throw XferException(1, 0);
		}
		else
		{
			unsigned int length = strlen(name);
			if (length > 0xFE)
				length = 0xFE;
			if (m_stream->write(&length, 1) != 1)
				throw XferException(1, 0);
			if (m_stream->write(name, length) != (int)length)
				throw XferException(1, 0);
			int count = m_count;
			int base = m_28;
			*(int *)m_table.bfmeAt((void **)&key) = base + count;
		}
	}
	return *this;
}

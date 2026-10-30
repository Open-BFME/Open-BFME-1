// cl: /DNDEBUG /MD /O2
// Load-side block traversal recovered under its reciprocal WorldBuilder TU.

typedef bool Bool;

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
	virtual int read(void *buffer, int size);
	virtual void slot4();
	virtual int skip(int count, int flag = 0);
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

private:
	unsigned char m_pad[0x14];
	BfmeByteStream *m_stream;
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
		throw XferException(1, 0);
	}

	if (marker == 0x44534352)
	{
		reinterpret_cast<Gen009D8C30 *>(this)->bfmeSkipPrefixed();
		if (m_stream->read(&marker, 4) != 4)
		{
			throw XferException(1, 0);
		}
	}

	if (marker != 0x424c4f4b)
	{
		int position = m_stream->skip(0, 1) - 4;
		throw XferException(0, "Block '%s' expected but BLOK ID was not found at %i", name, position);
	}

	if (m_isLoading)
		reinterpret_cast<Gen009D8C30 *>(this)->bfmeSkipPrefixed();

	if (m_stream->read(&marker, 4) != 4)
	{
		throw XferException(1, 0);
	}

	m_currentBlock = m_stream->current();
	++m_blockCount;
	return marker;
}

void Xfer::endBlock()
{
	if (m_stream == 0 || m_blockCount == 0)
		return;

	if (m_isLoading)
	{
		int marker;
		if (m_stream->read(&marker, 4) != 4)
		{
			throw XferException(1, 0);
		}

		if (marker != 0x45424c4b)
		{
			int position = m_stream->skip(0, 1) - 4;
			throw XferException(0, "Block end expected but EBLK ID was not found at %i", position);
		}
	}

	m_currentBlock = -1;
	--m_blockCount;
}

void Xfer::skipBlock(const char *name)
{
	if (m_stream == 0)
		return;

	int marker;
	if (m_stream->read(&marker, 4) != 4)
	{
		throw XferException(1, 0);
	}

	if (marker != 0x424c4f4b)
	{
		int position = m_stream->skip(0, 1) - 4;
		throw XferException(0, "Block '%s' expected but BLOK ID was not found at %i", name, position);
	}

	if (m_isLoading)
		reinterpret_cast<Gen009D8C30 *>(this)->bfmeSkipPrefixed();

	if (m_stream->read(&marker, 4) != 4)
	{
		throw XferException(1, 0);
	}

	if (m_stream->skip(marker) != marker)
	{
		throw XferException(0, "Could not skip over block '%s' to %i", name, marker);
	}
}

typedef void (__cdecl *BfmeSkipCallback)(void *snapshot, void *ctx, int extra);

class XferLoad
{
public:
	void SkipBadBlock(void *snapshot, int size);
	virtual void XferImpl(unsigned int type, void *data, unsigned int size);

private:
	unsigned char m_pad4[4];
	BfmeSkipCallback m_callback;
	void *m_ctx;
	Bool m_isLoading;
	unsigned char m_pad11[3];
	BfmeByteStream *m_stream;
	int m_count;
	int m_extra;
};

void XferLoad::SkipBadBlock(void *snapshot, int size)
{
	if (m_stream->skip(size, 0) != size)
	{
		throw XferException(0, "Could not skip over BAD block to %i", size);
	}

	if (m_callback)
		m_callback(snapshot, m_ctx, m_extra);
	m_extra = -1;
	--m_count;
}

// EA name XferLoad::XferImpl (ea_evidence chain+direct, strong; file wb1).
// Ported from Open BFME 2 Code/Libraries/Source/xfer/xfer_load.cpp
// (open-bfme-2 20a0cb6173): read and check the four-byte tag, skipping
// 'RCSD' prefixed records, then read the payload.
void XferLoad::XferImpl(unsigned int type, void *data, unsigned int size)
{
	if ((size && !data) || !m_stream)
		return;

	if (m_isLoading && type)
	{
		unsigned int marker;
		for (;;)
		{
			if (m_stream->read(&marker, 4) != 4)
			{
				throw XferException(1, 0);
			}
			if (marker != 0x44534352)
				break;
			reinterpret_cast<Gen009D8C30 *>(this)->bfmeSkipPrefixed();
		}
		if (marker != type)
		{
			const unsigned char *markerBytes = reinterpret_cast<const unsigned char *>(&marker);
			char found[5] = {char(markerBytes[3]), char(markerBytes[2]),
				char(markerBytes[1]), char(markerBytes[0]), 0};
			const unsigned char *typeBytes = reinterpret_cast<const unsigned char *>(&type);
			char expected[5] = {char(typeBytes[3]), char(typeBytes[2]),
				char(typeBytes[1]), char(typeBytes[0]), 0};
			throw XferException(0, "Expected '%s' but found '%s'", expected, found);
		}
	}
	if (size && m_stream->read(data, size) != int(size))
	{
		throw XferException(1, 0);
	}
}

// Ported from Open BFME 2 Code/Libraries/Source/xfer/xfer_load.cpp.
// ?bfmeSkipPrefixed@Gen009D8C30@@QAEXXZ
void Gen009D8C30::bfmeSkipPrefixed()
{
	unsigned char length;
	if (m_stream->read(&length, 1) != 1)
	{
		throw XferException(1, 0);
	}

	if (length == 0)
		return;
	int count = (length == 0xff) ? 4 : length;
	m_stream->skip(count, 1);
}

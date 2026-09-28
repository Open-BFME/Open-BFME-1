// cl: /DNDEBUG /MD /O2
// Clean C++ conversion of the raw-byte formatter at retail RVA 0x009D9220.
extern "C" void __cdecl bfmeAppend(void *stream, const char *format, ...);

class Gen009D9220
{
public:
	Gen009D9220 *bfmeEmit(const void *data, unsigned int length);

private:
	unsigned char m_pad[4];
	bool m_pending;
};

Gen009D9220 *Gen009D9220::bfmeEmit(const void *data, unsigned int length)
{
	if (length != 0 && data == 0)
		return this;

	if (m_pending)
	{
		bfmeAppend(this, "\n");
		m_pending = false;
	}

	if (length == 0)
	{
		bfmeAppend(this, 0);
		bfmeAppend(this, "--- 0 raw bytes\n");
		return this;
	}

	for (unsigned int row = 0; row < length; row += 16)
	{
		bfmeAppend(this, 0);
		bfmeAppend(this, "%04x", row);

		for (unsigned int col = 0; col < 16; ++col)
		{
			if ((col & 7) == 0)
				bfmeAppend(this, " ");

			if (col + row < length)
				bfmeAppend(this, " %02x", static_cast<unsigned int>(static_cast<const unsigned char *>(data)[col + row]));
			else
				bfmeAppend(this, "   ");
		}

		bfmeAppend(this, "  ");

		for (unsigned int col = 0; col < 16 && col + row < length; ++col)
		{
			unsigned char raw = static_cast<const unsigned char *>(data)[col + row];
			bfmeAppend(this, "%c",
				raw > 0x20 ? raw : '.');
		}

		bfmeAppend(this, "\n");
	}

	return this;
}

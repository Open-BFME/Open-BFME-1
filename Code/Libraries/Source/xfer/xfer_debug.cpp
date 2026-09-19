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
		bfmeAppend(this, reinterpret_cast<const char *>(0x01080294));
		m_pending = false;
	}

	if (length == 0)
	{
		bfmeAppend(this, 0);
		bfmeAppend(this, reinterpret_cast<const char *>(0x01144284));
		return this;
	}

	for (unsigned int row = 0; row < length; row += 16)
	{
		bfmeAppend(this, 0);
		bfmeAppend(this, reinterpret_cast<const char *>(0x0114427C), row);

		for (unsigned int col = 0; col < 16; ++col)
		{
			if ((col & 7) == 0)
				bfmeAppend(this, reinterpret_cast<const char *>(0x0108ED1C));

			if (col + row < length)
				bfmeAppend(this, reinterpret_cast<const char *>(0x01144274), static_cast<unsigned int>(static_cast<const unsigned char *>(data)[col + row]));
			else
				bfmeAppend(this, reinterpret_cast<const char *>(0x01142704));
		}

		bfmeAppend(this, reinterpret_cast<const char *>(0x010E8B00));

		for (unsigned int col = 0; col < 16 && col + row < length; ++col)
		{
			unsigned char raw = static_cast<const unsigned char *>(data)[col + row];
			bfmeAppend(this, reinterpret_cast<const char *>(0x01140290),
				raw > 0x20 ? raw : '.');
		}

		bfmeAppend(this, reinterpret_cast<const char *>(0x01080294));
	}

	return this;
}

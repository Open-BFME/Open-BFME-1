// ?bfmeEmit@Gen009D9220@@QAEPAV1@PBXI@Z
// partial score=0.55 date=2026-09-05
// cl: /DNDEBUG /MD /O2
// Clean C++ conversion of the raw-bytes hex dumper at retail RVA 0x009D9220.
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
	unsigned int len = length;
	Gen009D9220 *self = this;

	if (len != 0 && data == 0)
		return self;

	if (self->m_pending)
	{
		bfmeAppend(self, "\n");
		self->m_pending = false;
	}

	if (len == 0)
	{
		bfmeAppend(self, 0);
		bfmeAppend(self, "--- 0 raw bytes\n");
		return self;
	}

	const unsigned char *bytes = static_cast<const unsigned char *>(data);

	for (unsigned int row = 0; row < len; row += 16)
	{
		bfmeAppend(self, 0);
		bfmeAppend(self, "%04x", row);

		for (unsigned int col = 0; col < 16; ++col)
		{
			if ((col & 7) == 0)
				bfmeAppend(self, " ");

			unsigned int index = col + row;
			if (index < len)
				bfmeAppend(self, " %02x", static_cast<unsigned int>(bytes[index]));
			else
				bfmeAppend(self, "   ");
		}

		bfmeAppend(self, "  ");

		for (unsigned int col = 0; col < 16; ++col)
		{
			unsigned int index = col + row;
			if (index < len)
			{
				unsigned char raw = bytes[index];
				unsigned int ch = raw;
				if (!(raw > 0x20))
					ch = '.';
				bfmeAppend(self, "%c", ch);
			}
		}

		bfmeAppend(self, "\n");
	}

	return self;
}

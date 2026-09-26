// ?d_009a8c50@@YAXXZ
// partial score=0.15 date=2026-09-10
// cl: /O2 /Ob0 /DNDEBUG /DWIN32 /D_WINDOWS /MD
//
// Scoped reconstruction of the anonymous codec edge-extension helper at
// retail 0x009A8C50.  The two callers at 0x009A9070 and 0x009AA8F0 pass the
// same image context and an integer byte offset through a cdecl call.

extern "C" void * __cdecl memset(void *, int, unsigned int);
extern "C" void * __cdecl memcpy(void *, const void *, unsigned int);
#pragma intrinsic(memset)
#pragma intrinsic(memcpy)

struct Rva009A8C50Context
{
	unsigned char m_pad0[0x78];
	unsigned char *m_plane0;
	unsigned char *m_plane1;
	unsigned char *m_plane2;
	unsigned char m_pad1[0x90 - 0x84];
	unsigned int m_width;
	unsigned int m_height;
	unsigned int m_stride0;
	unsigned int m_stride1;
	unsigned char m_pad2[0xB4 - 0xA0];
	unsigned int m_border;
};

extern "C" void Rva009A8C50CopyPlanes(
	Rva009A8C50Context *self, int offset)
{
	unsigned char *plane0 = self->m_plane0 + offset;
	unsigned char *plane1 = self->m_plane1 + offset;
	unsigned char *plane2 = self->m_plane2 + offset;
	unsigned int width = self->m_width;
	unsigned int height = self->m_height;
	unsigned int stride0 = self->m_stride0;
	unsigned int stride1 = self->m_stride1;
	unsigned int border = self->m_border;

	for (unsigned int row = 0; row < height; ++row)
	{
		unsigned char *line = plane0 + row * stride0;
		memset(line - border, line[0], border);
		memset(line + width * 8, line[width * 8 - 1], border);
	}

	for (unsigned int row = 0; row < height; ++row)
	{
		unsigned char *source = plane0 + row * stride0;
		unsigned char *destination = source - height * stride0;
		memcpy(destination, source, stride0);
		memcpy(destination + height * stride0, source + height * stride0,
			stride0);
	}

	for (unsigned int row = 0; row < height; ++row)
	{
		unsigned char *line = plane1 + row * stride1;
		memset(line - (border >> 1), line[0], border >> 1);
		memset(line + (width * 4), line[width * 4 - 1], border >> 1);
	}

	for (unsigned int row = 0; row < height; ++row)
	{
		unsigned char *source = plane1 + row * stride1;
		unsigned char *destination = source - height * stride1 / 2;
		memcpy(destination, source, stride1);
		memcpy(destination + height * stride1 / 2,
			source + height * stride1 / 2, stride1);
	}

	for (unsigned int row = 0; row < height; ++row)
	{
		unsigned char *line = plane2 + row * stride1;
		memset(line - (border >> 1), line[0], border >> 1);
		memset(line + (width * 4), line[width * 4 - 1], border >> 1);
	}

	for (unsigned int row = 0; row < height; ++row)
	{
		unsigned char *source = plane2 + row * stride1;
		unsigned char *destination = source - height * stride1 / 2;
		memcpy(destination, source, stride1);
		memcpy(destination + height * stride1 / 2,
			source + height * stride1 / 2, stride1);
	}
}

// ?bfmeInitD70@@YAXPAX0@Z
// partial score=0.86 date=2026-09-12
extern "C" void *__cdecl memcpy(void *destination, const void *source,
	unsigned int bytes);

class BfmeInitD70Record
{
public:
	unsigned char m_pad00[0x40];
	unsigned int m_field40;
	unsigned int m_field44;
	unsigned int m_field48;
	unsigned int m_field4c;
	unsigned int m_copied[10];
	unsigned int m_field78;
	unsigned int m_field7c;
	unsigned int m_field80;
	unsigned int m_field84;
	unsigned int m_field88;
	unsigned int m_field8c;
	unsigned int m_field90;
	unsigned int m_field94;
	volatile unsigned int m_field98;
	unsigned int m_field9c;
	unsigned char m_padA0[0x14];
	unsigned int m_fieldB4;
};

// ?bfmeInitD70@@YAXPAX0@Z
// Retail copies fourteen source words into the codec record, then stores its derived sizes.
void __cdecl bfmeInitD70(void *selfRaw, void *sourceRaw)
{
	BfmeInitD70Record *self = (BfmeInitD70Record *)selfRaw;
	unsigned int *source = (unsigned int *)sourceRaw;

	memcpy(&self->m_field40, source, 14 * 4);

	unsigned int width = self->m_field40;
	unsigned int rawHeight = self->m_field44;
	const unsigned int plane = self->m_field48;
	volatile unsigned int &field98 = self->m_field98;

	width >>= 3;
	unsigned int height = rawHeight >> 3;

	self->m_field94 = height;

	unsigned int pixels = height * width;

	self->m_field84 = pixels;
	const unsigned int *strideField = &self->m_field4c;
	register unsigned int stride = *strideField;

	unsigned int quarterPixels = pixels >> 2;

	self->m_field8c = pixels + quarterPixels * 2;
	self->m_field90 = width;

	unsigned int chromaSpan = (plane - width * 8) >> 1;

	self->m_field78 = (plane + 1) * chromaSpan;

	const unsigned int planeBytes = (rawHeight + chromaSpan * 2) * plane;

	field98 = plane;

	const unsigned int halfChromaSpan = chromaSpan >> 1;

	self->m_fieldB4 = chromaSpan;
	self->m_field88 = quarterPixels;
	self->m_field7c = (stride + 1) * halfChromaSpan + planeBytes;
	self->m_field9c = stride;
	self->m_field80 = halfChromaSpan * stride
		+ ((rawHeight >> 1) + chromaSpan) * stride
		+ halfChromaSpan + planeBytes;
}

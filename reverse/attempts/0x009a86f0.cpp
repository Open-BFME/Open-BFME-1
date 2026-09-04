// ?Rva009A86F0Initialize@@YAHPAURva009A86F0Context@@@Z
// partial score=0.93 date=2026-09-04
// ?Rva009A86F0Initialize@@YAXPAURva009A86F0Context@@@Z
// partial score=0.93 date=2026-09-03
// Open-BFME5 conversion of the codec workspace initializer.

class Bucket
{
public:
	enum BucketMagicEnum { Bucket_GLUE_NOT_IMPLEMENTED = 0 };
	static void *__cdecl operator new(unsigned int bytes, BucketMagicEnum tag);
};

void __cdecl d_009a85f0(void *what);

struct Rva009A86F0Context
{
	void *m_at00;
	void *m_at04;
	unsigned char m_pad0[0x10 - 0x08];
	unsigned char m_pad1[0x10c - 0x10];
	void *m_at10c;
	void *m_at110;
	void *m_at114;
	void *m_at118;
	void *m_at11c;
	void *m_at120;
	unsigned char m_pad3[0x148 - 0x124];
	void *m_at148;
	void *m_at14c;
	unsigned char m_pad4[0x1f8 - 0x150];
	volatile unsigned int m_count;
	unsigned int m_count2;
	unsigned char m_pad6[0x228 - 0x200];
	unsigned int m_bufferSize;
	unsigned char m_pad7[0x6ec - 0x22c];
	void *m_at6ec;
	void *m_at6f0;
	void *m_at6f4;
	void *m_at6f8;
	void *m_at6fc;
	void *m_at700;
};

// ?Rva009A86F0Initialize@@YAHPAURva009A86F0Context@@@Z
int __cdecl Rva009A86F0Initialize(Rva009A86F0Context *self)
{
	unsigned int planeSize;
	unsigned int halfCount;
	unsigned int halfCount2;
	unsigned int tailSize;
	unsigned int bufferSize;
	unsigned int bufferSize2;
	d_009a85f0(self);

	void *first = Bucket::operator new(0x320, Bucket::Bucket_GLUE_NOT_IMPLEMENTED);
	self->m_at00 = first;
	if (first == 0)
		goto failure;
	self->m_at04 = (void *)(((unsigned int)self->m_at00 + 0x1f) & ~0x1f);

	void *second = Bucket::operator new(
		(self->m_count + 0xa) << 4, Bucket::Bucket_GLUE_NOT_IMPLEMENTED);
	self->m_at118 = second;
	if (second == 0)
		goto failure;
	halfCount = self->m_count >> 1;
	self->m_at10c = (void *)(((unsigned int)self->m_at118 + 0x1f) & ~0x1f);

	void *third = Bucket::operator new(
		(halfCount + 0xa) << 4, Bucket::Bucket_GLUE_NOT_IMPLEMENTED);
	self->m_at11c = third;
	if (third == 0)
		goto failure;
	halfCount2 = self->m_count >> 1;
	halfCount2 += 0;
	self->m_at110 = (void *)(((unsigned int)self->m_at11c + 0x1f) & ~0x1f);

	void *fourth = Bucket::operator new(
		(halfCount2 + 0xa) << 4, Bucket::Bucket_GLUE_NOT_IMPLEMENTED);
	self->m_at120 = fourth;
	if (fourth == 0)
		goto failure;
	self->m_at114 = (void *)(((unsigned int)self->m_at120 + 0x1f) & ~0x1f);

	bufferSize = self->m_bufferSize + 0x20;
	void *fifth = Bucket::operator new(
		bufferSize, Bucket::Bucket_GLUE_NOT_IMPLEMENTED);
	self->m_at6f8 = fifth;
	if (fifth == 0)
		goto failure;
	bufferSize2 = self->m_bufferSize + 0x20;
	self->m_at6ec = (void *)(((unsigned int)self->m_at6f8 + 0x1f) & ~0x1f);

	void *sixth = Bucket::operator new(
		bufferSize2, Bucket::Bucket_GLUE_NOT_IMPLEMENTED);
	self->m_at6fc = sixth;
	if (sixth == 0)
		goto failure;
	self->m_at6f0 = (void *)(((unsigned int)self->m_at6fc + 0x1f) & ~0x1f);

	planeSize = self->m_bufferSize * 4 + 0x20;
	self->m_at700 = Bucket::operator new(
		planeSize,
		Bucket::Bucket_GLUE_NOT_IMPLEMENTED);
	if (self->m_at700 == 0)
		goto failure;
	tailSize = self->m_count2 * 4 + 0x20;
	self->m_at6f4 = (void *)(((unsigned int)self->m_at700 + 0x1f) & ~0x1f);

	void *eighth = Bucket::operator new(
		tailSize,
		Bucket::Bucket_GLUE_NOT_IMPLEMENTED);
	self->m_at14c = eighth;
	if (eighth == 0)
		goto failure;
	self->m_at148 = (void *)(((unsigned int)self->m_at14c + 0x1f) & ~0x1f);
	return 1;

failure:
	d_009a85f0(self);
	return 0;
}

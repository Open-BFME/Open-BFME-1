// Open-BFME5 conversion of the codec buffer initializer.

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/NameKeyGenerator.h
class Bucket
{
public:
	enum BucketMagicEnum { Bucket_GLUE_NOT_IMPLEMENTED = 0 };
	static void *__cdecl operator new(unsigned int bytes, BucketMagicEnum tag);
};

void __cdecl bfmeOneBZB(void *what);

struct Rva009A5C40Context
{
	unsigned char m_pad0[0x24];
	void *m_at24;
	void *m_at28;
	void *m_at2c;
	unsigned char m_pad1[0x34 - 0x30];
	void *m_at34;
	unsigned char m_pad2[0x3c - 0x38];
	void *m_at3c;
	unsigned char m_pad3[0x44 - 0x40];
	unsigned int m_rows;
	unsigned char m_pad4[0x8c - 0x48];
	unsigned int m_count;
	unsigned char m_pad5[0x98 - 0x90];
	unsigned int m_stride;
	unsigned char m_pad6[0xa0 - 0x9c];
	void *m_atA0;
	void *m_atA4;
	void *m_atA8;
	void *m_atAC;
	void *m_atB0;
	unsigned int m_factorB4;
	void *m_atB8;
	void *m_atBC;
};

// ?Rva009A5C40Initialize@@YAHPAURva009A5C40Context@@@Z
int __cdecl Rva009A5C40Initialize(Rva009A5C40Context *self)
{
	bfmeOneBZB(self);

	self->m_atB8 = Bucket::operator new(
		((((self->m_factorB4 * 2 + self->m_rows) * self->m_stride) * 3 >> 1) + 0x20),
		Bucket::Bucket_GLUE_NOT_IMPLEMENTED);
	if (self->m_atB8 == 0)
		goto failure;
	self->m_atBC = (void *)(((unsigned int)self->m_atB8 + 0x1f) & ~0x1f);

	self->m_atA0 = Bucket::operator new(
		0x820, Bucket::Bucket_GLUE_NOT_IMPLEMENTED);
	if (self->m_atA0 == 0)
		goto failure;
	self->m_at34 = (void *)(((unsigned int)self->m_atA0 + 0x1f) & ~0x1f);

	self->m_atA4 = Bucket::operator new(
		0x820, Bucket::Bucket_GLUE_NOT_IMPLEMENTED);
	if (self->m_atA4 == 0)
		goto failure;
	self->m_at3c = (void *)(((unsigned int)self->m_atA4 + 0x1f) & ~0x1f);

	self->m_atA8 = Bucket::operator new(
		self->m_count * 4 + 0x20, Bucket::Bucket_GLUE_NOT_IMPLEMENTED);
	if (self->m_atA8 == 0)
		goto failure;
	self->m_at24 = (void *)(((unsigned int)self->m_atA8 + 0x1f) & ~0x1f);

	self->m_atAC = Bucket::operator new(
		self->m_count * 4 + 0x20, Bucket::Bucket_GLUE_NOT_IMPLEMENTED);
	if (self->m_atAC == 0)
		goto failure;
	unsigned int byteSize = self->m_count + 0x20;
	self->m_at28 = (void *)(((unsigned int)self->m_atAC + 0x1f) & ~0x1f);

	self->m_atB0 = Bucket::operator new(
		byteSize, Bucket::Bucket_GLUE_NOT_IMPLEMENTED);
	if (self->m_atB0 == 0)
		goto failure;
	self->m_at2c = (void *)(((unsigned int)self->m_atB0 + 0x1f) & ~0x1f);
	return 1;

failure:
	bfmeOneBZB(self);
	return 0;
}

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/NameKeyGenerator.h
class Bucket
{
public:
	enum BucketMagicEnum { Bucket_GLUE_NOT_IMPLEMENTED = 0 };
	static void *__cdecl operator new(unsigned int bytes, BucketMagicEnum tag);
};

void Rva009A8880Release(void *what);

struct Rva009A8910Context
{
	unsigned char m_pad0[0x1B8];
	unsigned int m_size;
	unsigned char m_pad1[0x244 - 0x1BC];
	void *m_at244;
	void *m_at248;
	void *m_at24C;
	void *m_at250;
	void *m_at254;
	void *m_at258;
};

int __cdecl Rva009A8910Initialize(
	Rva009A8910Context *self,
	int extra)
{
	Rva009A8880Release(self);

	void *first = Bucket::operator new(
		(unsigned int)extra + self->m_size + 0x20,
		Bucket::Bucket_GLUE_NOT_IMPLEMENTED);
	self->m_at248 = first;
	if (first == 0)
	{
		Rva009A8880Release(self);
		return 0;
	}
	self->m_at244 = (void *)(((unsigned int)first + 0x1F) & ~0x1F);

	void *second = Bucket::operator new(
		(unsigned int)extra + self->m_size + 0x20,
		Bucket::Bucket_GLUE_NOT_IMPLEMENTED);
	self->m_at250 = second;
	if (second == 0)
	{
		Rva009A8880Release(self);
		return 0;
	}
	self->m_at24C = (void *)(((unsigned int)second + 0x1F) & ~0x1F);

	void *third = Bucket::operator new(
		(unsigned int)extra + self->m_size + 0x20,
		Bucket::Bucket_GLUE_NOT_IMPLEMENTED);
	self->m_at258 = third;
	if (third == 0)
	{
		Rva009A8880Release(self);
		return 0;
	}
	self->m_at254 = (void *)(((unsigned int)third + 0x1F) & ~0x1F);
	return 1;
}

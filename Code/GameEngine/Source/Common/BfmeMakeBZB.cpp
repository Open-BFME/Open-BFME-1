// cl: /DNDEBUG /MD /O2

extern "C" void *__cdecl memset(void *block, int value, unsigned int bytes);
#pragma intrinsic(memset)

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/NameKeyGenerator.h
class Bucket
{
public:
	enum BucketMagicEnum { Bucket_GLUE_NOT_IMPLEMENTED = 0 };
	static void *__cdecl operator new(unsigned int bytes, BucketMagicEnum tag);
};

void __cdecl bfmeInitD70(void *self, void *src);

struct BfmeHolderE20
{
	unsigned char m_lead[0xC4];
	int m_flag;
};

// ?bfmeMakeBZB@@YAPAXPAX@Z
void *__cdecl bfmeMakeBZB(void *src)
{
	BfmeHolderE20 *self = (BfmeHolderE20 *)Bucket::operator new(0xC8, Bucket::Bucket_GLUE_NOT_IMPLEMENTED);
	void *result = 0;

	if (self)
	{
		memset(self, 0, 0xC8);
		bfmeInitD70(self, src);
		self->m_flag = 1;
		result = self;
	}

	return result;
}

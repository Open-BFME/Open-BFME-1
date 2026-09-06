// ?d_009a4c20@@YAXXZ
// partial score=0.95 date=2026-09-06
// cl: /DNDEBUG /MD /EHsc
// Open-BFME5 conversion of the codec state allocator at retail 0x009A4C20.

extern "C" void * __cdecl memset(void *, int, unsigned int);
#pragma intrinsic(memset)

class Bucket
{
public:
	 enum BucketMagicEnum { Bucket_GLUE_NOT_IMPLEMENTED = 0 };
	 static void *__cdecl operator new(unsigned int bytes, BucketMagicEnum tag);
};

extern void __cdecl d_009a4b10(void);
void __cdecl freeCodecMemory(void *memory);
extern "C" void * __cdecl memcpy(void *, const void *, unsigned int);
#pragma intrinsic(memcpy)

// ?Rva009A4C20Create@@YAPAXXZ
void *__cdecl Rva009A4C20Create(void)
{
	unsigned int initial[14] = { 0, 0, 0, 0, 8, 8, 0, 0, 0, 0, 0, 0, 0, 0 };
	void *state = Bucket::operator new(0x4954, Bucket::Bucket_GLUE_NOT_IMPLEMENTED);

	if (state == 0)
		return 0;

	memset(state, 0, 0x4954);
	memcpy((unsigned char *)state + 0x1b0, initial, sizeof(initial));

	if (((int (__cdecl *)(void *))d_009a4b10)(state) == 0)
	{
		freeCodecMemory(state);
		return 0;
	}

	*(unsigned int *)((unsigned char *)state + 0x1a8) = 0x46;
	*(void **)((unsigned char *)state + 0x294) = (void *)0x01356b60;
	memset((unsigned char *)state + 0x3a0, 0, 0x14);
	*(unsigned short *)((unsigned char *)state + 0x3b4) = 0;
	memset((unsigned char *)state + 0x3b6, 0, 0x18c);
	return state;
}

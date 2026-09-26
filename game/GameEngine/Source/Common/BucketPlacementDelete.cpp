// cl: /DNDEBUG /MD /EHsc

// BFME's Bucket placement delete is the shared 12-byte pool-glue body at
// 0x007EFFF0.  Keep this declaration local: the NameKeyGenerator shadow
// header also owns Bucket's allocator, whose retail target is a separate
// unresolved identity at 0x009A5920.
extern "C" void __cdecl free(void *);

class Bucket
{
public:
	enum BucketMagicEnum { Bucket_GLUE_NOT_IMPLEMENTED = 0 };

	inline void operator delete(void *p, BucketMagicEnum)
	{
		free(p);
	}
};

void (*bfme_bucket_placement_delete)(void *, Bucket::BucketMagicEnum) =
	&Bucket::operator delete;

// cl: /DNDEBUG /MD /EHsc

// Bucket's pool-placement allocator is a distinct 14-byte wrapper around the
// proven BFME block allocator at 0x009A5920.  Keep this ABI declaration local:
// the class itself is owned by a header in NameKeyGenerator.cpp, but the
// allocator wrapper can be emitted without importing that header's other
// inline bodies.
void *__cdecl bfmeAllocBlock(unsigned int bytes);

class Bucket
{
public:
	enum BucketMagicEnum { Bucket_GLUE_NOT_IMPLEMENTED = 0 };

	inline static void *operator new(unsigned int size, BucketMagicEnum)
	{
		return bfmeAllocBlock(size);
	}
};

void *(*bfme_bucket_placement_new)(unsigned int, Bucket::BucketMagicEnum) =
	&Bucket::operator new;

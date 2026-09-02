// Copy construction for a vector-like owner of 12-byte records.  Retail
// reuses the incoming argument's stack slot for the allocator temporary.

struct BfmeRecord12DK
{
	int words[3];
};

struct BfmeAllocatorDK
{
	int state;
};

class BfmeVector12DK
{
public:
	BfmeVector12DK(const BfmeVector12DK &other);
	BfmeAllocatorDK *bfmeGetAllocator(BfmeAllocatorDK *result) const;
	void bfmeInitialize(int count, const BfmeAllocatorDK *allocator);

private:
	BfmeRecord12DK *m_start;
	BfmeRecord12DK *m_finish;
	BfmeRecord12DK *m_end;
};

BfmeRecord12DK *__cdecl bfmeCopyRecords12DK(
	BfmeRecord12DK *first,
	BfmeRecord12DK *last,
	BfmeRecord12DK *result,
	BfmeAllocatorDK *allocator);

// ??0BfmeVector12DK@@QAE@ABV0@@Z
BfmeVector12DK::BfmeVector12DK(const BfmeVector12DK &other)
{
	BfmeAllocatorDK allocator;
	BfmeAllocatorDK *allocatorPtr = other.bfmeGetAllocator(&allocator);
	bfmeInitialize(other.m_finish - other.m_start, allocatorPtr);
	m_finish = bfmeCopyRecords12DK(
		other.m_start, other.m_finish, m_start, &allocator);
}

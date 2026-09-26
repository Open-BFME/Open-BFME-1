// cl: /DNDEBUG /MD /EHsc
// RVA 0x009CBCC0: two null fields and an allocator proxy at +8.
// The 11-byte callee at 0x009CBC00 stores its second argument at the
// proxy address and returns with two stack arguments consumed.

class Rva009CBC00AllocatorProxy
{
public:
	Rva009CBC00AllocatorProxy(const void *allocator, unsigned int value);

	void *m_value;
};

class Rva009CBCC0Owner
{
public:
	Rva009CBCC0Owner(const void *allocator);

private:
	void *m_start;
	void *m_finish;
	Rva009CBC00AllocatorProxy m_storage;
};

Rva009CBCC0Owner::Rva009CBCC0Owner(const void *allocator)
	: m_start(0), m_finish(0), m_storage(allocator, 0)
{
}

// Retail RVA 0x00126460 constructs a three-field STLport base object.
// The allocator proxy callee identifies the Relationship node family.

class Rva00124F60AllocatorProxy
{
public:
	Rva00124F60AllocatorProxy(const void *allocator, unsigned int value);

	void *m_value;
};

class Rva00126460
{
public:
	Rva00126460(const void *allocator);

private:
	void *m_start;
	void *m_finish;
	Rva00124F60AllocatorProxy m_storage;
};

Rva00126460::Rva00126460(const void *allocator)
	: m_start(0), m_finish(0), m_storage(allocator, 0)
{
}

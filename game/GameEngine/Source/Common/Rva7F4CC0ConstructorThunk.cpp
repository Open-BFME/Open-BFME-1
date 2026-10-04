// 0x011296B0 is the vftable Rva007F6D60ChildConstructor.cpp emits (ledger
// dir32 row ??_7Rva007F6D60Member2C@@6B@); bfmeVftRva007F6D60Member2C was a
// stand-in spelling, now named directly.
extern "C" void *__identifier("??_7Rva007F6D60Member2C@@6B@")[];

class SnapshotDupReplica
{
	public:
	SnapshotDupReplica();
	virtual void crc() {}

	private:
	int m_reserved;
};

struct Rva7F4CC0Primary
{
	Rva7F4CC0Primary() : first(0), second(0), third(0), fourth(0), enabled(false) {}

	unsigned int first;
	unsigned int second;
	unsigned int third;
	unsigned int fourth;
	bool enabled;
};

struct Rva7F4CC0ConstructorThunk : Rva7F4CC0Primary
{
	Rva7F4CC0ConstructorThunk();

	SnapshotDupReplica m_replica;
	volatile unsigned int second;
	volatile unsigned int third;
};

// ?d_007f4cc0@@YAXXZ
	Rva7F4CC0ConstructorThunk::Rva7F4CC0ConstructorThunk() : m_replica()
{
	volatile unsigned int *replica = (volatile unsigned int *)&m_replica;
	replica[2] = 0;
	replica[3] = 0;
	replica[1] = 0;
	replica[0] = (unsigned int)__identifier("??_7Rva007F6D60Member2C@@6B@");
}

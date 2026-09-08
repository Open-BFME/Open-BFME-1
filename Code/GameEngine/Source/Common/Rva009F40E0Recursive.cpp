// Neutral raw-ABI reconstruction for retail RVA 0x009F40E0 (72 bytes).
// The retail boundary is a thiscall with two stack arguments: a pointer to a
// pointer-sized slot and an unsigned count.  No named caller survives in the
// current reverse inventory, so the address-derived owner is intentional.

class Rva009F40E0Owner
{
public:
	void run(void **slot, unsigned int count);
};


void Rva009F40E0Owner::run(void **slot, unsigned int count)
{
	if (*slot == 0)
		return;

	*slot = 0;
	unsigned int childCount = count;
	slot += 2;
	childCount >>= 2;
	unsigned int stride = count * 8;
	unsigned int remaining = 4;
	while (remaining != 0)
	{
		run(slot, childCount);
		slot = (void **)((char *)slot + stride);
		--remaining;
	}
}

// Open-BFME5: fixed-width uninitialised fill at retail 0x0013DA40.
// The 0xEC-byte value is copied into each destination slot; keeping the loop
// counter scoped to the guarded block reproduces retail's register schedule.
struct Rva13DA40Record
{
	unsigned char bytes[236];
};

void __cdecl rva_13da40_copy_records(
	Rva13DA40Record *destination,
	unsigned int count,
	const Rva13DA40Record &source)
{
	Rva13DA40Record *current = destination;

	if (count > 0)
	{
		unsigned int remaining = count;

		do
		{
			if (current != 0)
				*current = source;
			++current;
		}
		while (--remaining != 0);
	}
}

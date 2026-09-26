// cl: /DNDEBUG /MD /EHsc
// Structural BFME recovery, retail 0x0094C690 (31 bytes).

struct Rva0094C690Pair
{
	unsigned *value;
	unsigned *refs;
};

class Rva0094C690
{
public:
	static void copy(Rva0094C690Pair *destination, Rva0094C690Pair *source);
};

void Rva0094C690::copy(Rva0094C690Pair *destination,
	Rva0094C690Pair *source)
{
	if (destination == 0)
		return;
	destination->value = source->value;
	destination->refs = source->refs;
	if (destination->refs != 0)
		++*reinterpret_cast<unsigned short *>(reinterpret_cast<unsigned char *>(destination->refs) + 4);
}

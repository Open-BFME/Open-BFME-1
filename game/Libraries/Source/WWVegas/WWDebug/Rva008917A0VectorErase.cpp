// cl: /DNDEBUG /MD /EHs-c-
// Open-BFME: pointer-vector erase at index. Decrements count at +4, memmove
// of the tail, then zeros the slot past the new end.

extern "C" void *memmove(void *dest, const void *src, unsigned count);

class Rva008917A0Vector
{
	void *unused;
	unsigned count;
	void **data;

public:
	void erase(unsigned index);
};

// ?erase@Rva008917A0Vector@@QAEXI@Z
void Rva008917A0Vector::erase(unsigned index)
{
	unsigned n = count - 1;
	count = n;
	if (n && index != n)
		memmove(data + index, data + index + 1, (n - index) * 4);
	data[count] = 0;
}

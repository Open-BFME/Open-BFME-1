// Open-BFME5 conversions.

class BfmeE1242;

class BfmeN1242
{
public:
	void bfmeReserve1242(int n);
	void bfmePut1242(int i, BfmeE1242 *e);
	unsigned m_bfme00;
	unsigned m_bfme04;
	char m_bfmePad08[0x20 - 0x08];
	BfmeE1242 **m_elements;
	char m_bfmePad24[4];
	int m_length;
};

// Rva00C6DCC0StaticInit.cpp owns the 88-byte stack at VA 0x01338748;
// the argument array at VA 0x01338750 is its member at +8.
struct Rva008AE770Stack {
	int m_count;
	char m_pad04[4];
	BfmeE1242 **m_08;
};
extern Rva008AE770Stack Rva008AE770TheStack;
class AptValue;
extern AptValue *g_bfmeFallbackDB;

// Retail's memmove import thunk, with its ledger spelling.
void ji_009f6ec6();
class AptInteger
{
public:
	static AptInteger *Create(int n);
};

void *bfmeInsert1242(BfmeN1242 *array, int k)
{
	int i;
	int n;
	BfmeE1242 *element;

	if ((array->m_bfme04 & 0x3f) == 0x16 && !((unsigned char)(~(array->m_bfme04 >> 15)) & 1)) {
		array->bfmeReserve1242(array->m_length + k);
		if (k) {
			((void *(__cdecl *)(void *, const void *, unsigned int))ji_009f6ec6)(
				array->m_elements + k, array->m_elements, array->m_length * 4);
			array->m_length += k;
			for (i = 0; i < k; ++i) {
				array->m_elements[i] = 0;
				element = Rva008AE770TheStack.m_08[Rva008AE770TheStack.m_count - i - 1];
				if (i >= 0) {
					array->bfmeReserve1242(i + 1);
					array->bfmePut1242(i, element);
					n = array->m_length;
					if (i + 1 > n)
						n = i + 1;
					array->m_length = n;
				}
			}
		}
		return AptInteger::Create(array->m_length);
	}
	return g_bfmeFallbackDB;
}

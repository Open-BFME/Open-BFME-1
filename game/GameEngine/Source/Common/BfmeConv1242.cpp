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
	BfmeE1242 **m_bfme20;
	char m_bfmePad24[4];
	int m_bfme28;
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

void *bfmeInsert1242(BfmeN1242 *a, int k)
{
	int i;
	int n;
	BfmeE1242 *e;

	if ((a->m_bfme04 & 0x3f) == 0x16 && !((unsigned char)(~(a->m_bfme04 >> 15)) & 1)) {
		a->bfmeReserve1242(a->m_bfme28 + k);
		if (k) {
			((void *(__cdecl *)(void *, const void *, unsigned int))ji_009f6ec6)(
				a->m_bfme20 + k, a->m_bfme20, a->m_bfme28 * 4);
			a->m_bfme28 += k;
			for (i = 0; i < k; ++i) {
				a->m_bfme20[i] = 0;
				e = Rva008AE770TheStack.m_08[Rva008AE770TheStack.m_count - i - 1];
				if (i >= 0) {
					a->bfmeReserve1242(i + 1);
					a->bfmePut1242(i, e);
					n = a->m_bfme28;
					if (i + 1 > n)
						n = i + 1;
					a->m_bfme28 = n;
				}
			}
		}
		return AptInteger::Create(a->m_bfme28);
	}
	return g_bfmeFallbackDB;
}

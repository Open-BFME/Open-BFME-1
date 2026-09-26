// cl: /DNDEBUG /DWIN32 /MD /EHsc /D_STLP_USE_STATIC_LIB
// Open-BFME: address-derived self accessor at retail RVA 0x003B7340, 3 bytes.
// The only reference is an unnamed thunk, so no semantic owner is proven.

class Rva003B7340
{
public:
	void *self(void);
};

void *Rva003B7340::self(void)
{
	return this;
}

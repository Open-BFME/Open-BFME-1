// cl: /DNDEBUG /DWIN32 /MD /EHsc /D_STLP_USE_STATIC_LIB
// Open-BFME: address-derived self accessor at retail RVA 0x0014A880, 3 bytes.
// The carved body has no semantic identity evidence beyond returning this.

class Rva0014A880
{
public:
	void *self(void);
};

void *Rva0014A880::self(void)
{
	return this;
}

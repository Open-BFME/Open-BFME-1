extern "C" int __identifier("?g_BfmeVftZQ@@3PAPAXA")[];

// Declaration-only call view of the existing six-DWORD constructor at
// retail RVA0090CF90. No instance, base layout or vtable is asserted here.
class Rva006D51B0TextureBase
{
public:
	Rva006D51B0TextureBase(unsigned, unsigned, unsigned, unsigned, unsigned, unsigned);
};

class BfmeOwnerZQ
{
public:
	BfmeOwnerZQ *bfmeInitZQ(void *first, void *second, void *third, void *fourth);

	void *m_bfmeVfZQ;
};

BfmeOwnerZQ *BfmeOwnerZQ::bfmeInitZQ(void *first, void *second, void *third, void *fourth)
{
	reinterpret_cast<Rva006D51B0TextureBase *>(this)->Rva006D51B0TextureBase::Rva006D51B0TextureBase(
		reinterpret_cast<unsigned>(first), reinterpret_cast<unsigned>(second),
		reinterpret_cast<unsigned>(third), reinterpret_cast<unsigned>(fourth), 1, 0);
	m_bfmeVfZQ = __identifier("?g_BfmeVftZQ@@3PAPAXA");

	return this;
}

// cl: /DNDEBUG /MD
// Guarded forwarder, RVA 0x002DF500, 15 bytes:
//   mov ecx,[ecx+58h]; test ecx,ecx; je ret; jmp ILT 0x00040412; ret 8
// If the object at this+0x58 exists, pass both arguments on to it through
// ILT 0x00040412 -> 0x001D6860, the matched BfmeThingHF::bfmeTellHF that tells
// every listener in a pointer range (virtual slot 4) about the pair. Its ?dup_
// row used to borrow W3DModelDraw::setTerrainDecalSize, whose call reaches
// Shadow::setSize instead. Identity not recovered: the owner is named for the
// address.

class BfmeThingHF
{
public:
	void bfmeTellHF(void *first, void *second);
};

class Rva002DF500Owner
{
public:
	void rva002DF500(void *first, void *second);

private:
	char m_unknown00[0x58];
	BfmeThingHF *m_listeners;				// +0x58
};

void Rva002DF500Owner::rva002DF500(void *first, void *second)
{
	if (m_listeners != 0)
	{
		m_listeners->bfmeTellHF(first, second);
	}
}

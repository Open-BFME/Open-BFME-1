// cl: /DNDEBUG /MD /EHsc
// ?Rva009AABB0CodecDispatch@@YAXPAURva009AABB0Context@@@Z
// Open-BFME5: codec dispatch argument marshaler at retail 0x009AABB0.

extern unsigned char g_rva011426A0[];

void __cdecl Rva009B4390CodecCall(
	void *, int, void *, int, int, int, int, int,
	int, int, int, int, int, int, int);

struct Rva009AABB0Context
{
	unsigned char m_pad0[0x13C];
	int *m_at13C;
	unsigned char m_pad140[0x160 - 0x140];
	int m_at160;
	unsigned char m_pad164[0x19C - 0x164];
	unsigned char m_at19C;
	unsigned char m_pad19D[0x1A0 - 0x19D];
	int m_at1A0;
	unsigned char m_at1A4[0x1AC - 0x1A4];
	unsigned char m_at1AC;
	unsigned char m_pad1AD[0x1B8 - 0x1AD];
	int m_at1B8;
	unsigned char m_pad1BC[0x1E8 - 0x1BC];
	int m_at1E8;
	int m_at1EC;
	unsigned char m_pad1F0[0x1F4 - 0x1F0];
	int m_at1F4;
	int m_at1F8;
	unsigned char m_pad1FC[0x698 - 0x1FC];
	int m_at698;
	unsigned char m_pad69C[0x914 - 0x69C];
	int m_at914;
	unsigned char m_pad918[0x938 - 0x918];
	int m_at938;
	int m_at93C;
	unsigned int m_at940;
};

void Rva009AABB0CodecDispatch(Rva009AABB0Context *self)
{
	Rva009B4390CodecCall(
		self,
		((self->m_at1B8 + 1) * 3) << 4,
		g_rva011426A0,
		self->m_at1AC,
		self->m_at698,
		*self->m_at13C,
		self->m_at1E8,
		self->m_at160,
		self->m_at1F8,
		self->m_at1F4,
		self->m_at19C,
		self->m_at914,
		self->m_at940,
		self->m_at938,
		self->m_at1A0);
}

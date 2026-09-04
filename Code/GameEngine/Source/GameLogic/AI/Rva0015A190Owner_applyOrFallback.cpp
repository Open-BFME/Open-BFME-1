// cl: /DNDEBUG /MD /EHsc
// Open-BFME: leftover of d_00153d10.asm at 0x0015A190, 87 bytes.
// Same-dump sibling of the 0x0015A130 contain-query bank: first the 5-arg
// group helper at ILT 0x00046876 (body 0x001599A0), and on a false return a
// 16-byte stack packet {arg1, 0, 0, 0} through the shared apply helper at
// ILT 0x00048C43 (body 0x00159AD0). Four stack args, ret 10h.

struct Rva0015A190Packet
{
	void *m_first;					// +0
	unsigned char m_flag;			// +4
	void *m_objA;					// +8
	void *m_objB;					// +12
};

class Rva0015A190Owner
{
public:
	bool tryGroupSpecial(void *a, int b, int zero, void *c, void *d);
	void applyPacket(Rva0015A190Packet *packet, int b);
	void applyOrFallback(void *a, int b, void *c, void *d);
};

// ?applyOrFallback@Rva0015A190Owner@@QAEXPAXHPAX1@Z
void Rva0015A190Owner::applyOrFallback(void *a, int b, void *c, void *d)
{
	if (tryGroupSpecial(a, b, 0, c, d))
		return;

	Rva0015A190Packet packet;
	packet.m_first = a;
	packet.m_flag = 0;
	packet.m_objA = 0;
	packet.m_objB = 0;
	applyPacket(&packet, b);
}

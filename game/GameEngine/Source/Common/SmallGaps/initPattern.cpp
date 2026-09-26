// ?initPattern@@YAXPAURva009C2930Owner@@I@Z
struct Rva009C2930Owner { char m_pad[0x34]; unsigned char* m_buffer; };
void initPattern(Rva009C2930Owner* owner, unsigned int v)
{
	unsigned int* p = (unsigned int*)(((unsigned int)owner->m_buffer + 0x400) & ~0x1f);
	p[0] = p[1] = v * 0x10001;
	p[2] = p[3] = 0x10001;
	p[4] = p[5] = 0x40004;
}

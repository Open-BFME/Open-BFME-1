// ?aptPackLo@@YAPAVAptValue@@PAURva008B6B40Self@@H@Z
// partial score=0.9 date=2026-09-06
// 31/31 B, 7 diff bytes: retail keeps self in ecx and the first pushed field in eax (register colour); stdcall 3-arg packer then AptInteger::Create.
// cl: /DNDEBUG /MD /EHsc
class AptValue;
class AptInteger { public: static AptValue* Create(int value); };
void __cdecl d_008b66b0();
typedef int (__stdcall* Rva008B6B40Pack)(int, int, int);
struct Rva008B6B40Self { char m_pad[0x30]; int m_a; int m_b; int m_c; };
AptValue* aptPackLo(Rva008B6B40Self* self, int argc)
{
	return AptInteger::Create(((Rva008B6B40Pack)d_008b66b0)(self->m_c, self->m_b, self->m_a));
}
// ?aptThirdLo@@YAPAVAptValue@@PAURva008B6B40Self@@H@Z
AptValue* aptThirdLo(Rva008B6B40Self* self, int argc)
{
	return AptInteger::Create(self->m_c);
}

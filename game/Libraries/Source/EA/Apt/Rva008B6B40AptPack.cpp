// ?aptThirdLo@@YAPAVAptValue@@PAURva008B6B40Self@@H@Z
// cl: /DNDEBUG /MD /EHsc
class AptValue;
class AptInteger { public: static AptValue* Create(int value); };
struct Rva008B6B40Self { char m_pad[0x30]; int m_a; int m_b; int m_c; };
AptValue* aptThirdLo(Rva008B6B40Self* self, int argc)
{
	return AptInteger::Create(self->m_c);
}

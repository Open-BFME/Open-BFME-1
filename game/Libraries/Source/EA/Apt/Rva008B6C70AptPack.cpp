// ?aptThirdHi@@YAPAVAptValue@@PAURva008B6C70Self@@H@Z
// cl: /DNDEBUG /MD /EHsc
class AptValue;
class AptInteger { public: static AptValue* Create(int value); };
struct Rva008B6C70Self { char m_pad[0x50]; int m_a; int m_b; int m_c; };
AptValue* aptThirdHi(Rva008B6C70Self* self, int argc)
{
	return AptInteger::Create(self->m_c);
}

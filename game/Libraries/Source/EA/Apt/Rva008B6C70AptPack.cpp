// ?aptWeekday50At008B6C70@@YAPAVAptInteger@@PAXH@Z
// ?aptThirdHi@@YAPAVAptValue@@PAURva008B6C70Self@@H@Z
// cl: /DNDEBUG /MD /EHsc
class AptValue;
class AptInteger { public: static AptInteger* Create(int value); };
// Opaque receiver of the matched weekday helper at 0x008B66B0, here read
// through its second date block at +0x50..+0x58.
class Rva008B6880 {
public:
	int rva008B66B0(int, int, int);
	unsigned char m_unknown00[0x50];
	int m_day, m_month, m_year;
};
// RVA 0x008B6C70: weekday of the fields at +0x50..+0x58 as an Apt integer.
AptInteger *aptWeekday50At008B6C70(void *self, int argc)
{
	Rva008B6880 *date = (Rva008B6880 *)self;
	return AptInteger::Create(date->rva008B66B0(date->m_year, date->m_month, date->m_day));
}
struct Rva008B6C70Self { char m_pad[0x50]; int m_a; int m_b; int m_c; };
AptValue* aptThirdHi(Rva008B6C70Self* self, int argc)
{
	return (AptValue*)AptInteger::Create(self->m_c);
}

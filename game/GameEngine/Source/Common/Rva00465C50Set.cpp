// cl: /O2 /Ob0

class Rva00465C50
{
public:
	bool set(unsigned i);
};

bool Rva00465C50::set(unsigned i)
{
	if (i >= 12)
		return false;
	unsigned char *s = (unsigned char *)this + 0xA8 + i * 20;
	unsigned char v = s[16];
	if (v & 2)
		return false;
	s[16] = (unsigned char)(v | 1);
	*((unsigned char *)this + 0x1AD) = 1;
	return true;
}

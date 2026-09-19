// The carved boundary at 0x00458220 loads one byte from this+0x1c and returns.
// No caller or class table proves the semantic owner.
class Rva00458220Owner
{
public:
	unsigned char byteAt1C(void) const;
};

unsigned char Rva00458220Owner::byteAt1C(void) const
{
	return *(const unsigned char *)((const unsigned char *)this + 0x1c);
}

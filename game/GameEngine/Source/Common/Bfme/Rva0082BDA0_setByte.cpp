// cl: /DNDEBUG /MD /EHsc
// Structural BFME recovery, retail 0x0082BDA0 (24 bytes).
// Retail stores one byte argument at this+0 and returns this.

class Rva0082BDA0
{
public:
	void *setByte(unsigned char value);
};

#pragma optimize("y", off)
void *Rva0082BDA0::setByte(unsigned char value)
{
	Rva0082BDA0 * volatile self = this;
	*reinterpret_cast<unsigned char *>(self) = value;
	return const_cast<Rva0082BDA0 *>(self);
}
#pragma optimize("y", on)

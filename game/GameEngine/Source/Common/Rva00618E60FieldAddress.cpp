// Retail 0x00618E60: lea eax, [ecx+0x14]; ret, then INT3 padding.
// Caller 0x003C3760 reaches this body through ILT 0x00040D31 on a
// LivingWorldRegion receiver. The AudioEventRTS alias previously occupying
// this address was a byte-pattern reuse; its semantic owner is unsupported.
// Keep this standalone leaf's owner and return type opaque.

class Rva00618E60FieldAddress
{
public:
	const void *get() const;

private:
	char m_pad00[0x14];
	unsigned char m_at14;
};

const void *Rva00618E60FieldAddress::get() const
{
	return &m_at14;
}

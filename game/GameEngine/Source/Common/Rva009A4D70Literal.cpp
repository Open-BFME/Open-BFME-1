// mov eax,<.rdata address> / ret at 0x009A4D70 (6 bytes).
//
// The immediate is the only reference anywhere in the image to the .rdata
// string "6.1.0.5" at 0x011416B8, so the body returns that literal.  The start
// is 16-byte aligned after an int3 pad run and the ret is followed by int3
// padding; nothing calls it and no table holds it.  The build checks the
// literal against the retail bytes at the referenced address.
//
// IDENTITY IS NOT RECOVERED.  The name is derived from the address.

class Rva009A4D70Literal
{
public:
	const char *text() const;
};

const char *Rva009A4D70Literal::text() const
{
	return "6.1.0.5";
}

// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc
//
// Retail 0x00092900 returns its receiver unchanged.

class Rva00092900Self
{
public:
	Rva00092900Self *returnThis();
};

Rva00092900Self *Rva00092900Self::returnThis()
{
	return this;
}

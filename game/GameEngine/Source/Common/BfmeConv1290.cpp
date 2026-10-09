// Open-BFME5 conversions.
// Callees (tools/callees.py 0x78AC20 43): ILT 0x4A183 -> bfmeOneSGA,
// ILT 0xA15A -> 0x00465B30 BfmeA991::bfmeGo991A, ILT 0xAF33 -> 0x00783010 Rva00783010.

extern unsigned char g_006fc8d0;

void Rva00783010(void);

class BfmeA991
{
public:
	void bfmeGo991A();
};

class BfmeThingSGA
{
public:
	void bfmeGoSGA();
	void bfmeOneSGA();
};

void BfmeThingSGA::bfmeGoSGA()
{
	char saved = g_006fc8d0;
	g_006fc8d0 = 0;
	bfmeOneSGA();
	reinterpret_cast<BfmeA991 *>(this)->bfmeGo991A();
	Rva00783010();
	g_006fc8d0 = (unsigned char)saved;
}

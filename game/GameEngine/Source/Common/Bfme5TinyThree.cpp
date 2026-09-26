// Three more tiny ones: a masked flag read through two guards, an unsigned
// count turned into a scaled double, and a sign written as plus or minus one.
//
// The last one keeps a frame pointer, which is what the pragma around it is
// for: retail builds that body without omitting the frame, and everything
// else about it matches.

class BfmeThingBW
{
public:
	char m_bfmeHead[0x48];					// +0x00
	int m_bfmeReady;					// +0x48
	char m_bfmeGap[0x18];					// +0x4C
	int m_bfmeFlags;					// +0x64
};

// ?bfmeMask@@YAHPAVBfmeThingBW@@@Z
int __cdecl bfmeMask(BfmeThingBW *thing)
{
	if (!thing)
		return 0;

	if (!thing->m_bfmeReady)
		return 0;

	return thing->m_bfmeFlags & 0x20;
}

extern double g_bfmeFactorBW;					// retail 0x01075D80

// ?bfmeScale@@YANI@Z
double __cdecl bfmeScale(unsigned int value)
{
	return value * g_bfmeFactorBW;
}

class Gen_0088A5D0
{
public:
	void bfmeSetSign(unsigned char value);

private:
	char m_bfmeHead[0x9F49];				// +0x0000
	char m_bfmeSign;					// +0x9F49
};

#pragma optimize("y", off)

// ?bfmeSetSign@Gen_0088A5D0@@QAEXE@Z
void Gen_0088A5D0::bfmeSetSign(unsigned char value)
{
	m_bfmeSign = value ? 1 : -1;
}

#pragma optimize("y", on)

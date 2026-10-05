// cl: /DNDEBUG /MD /EHsc

// Retail 0x006FB9C0. Store (int)float into a global via __ftol2.

extern int TheW3DFrameLengthInMsec;

// ?set_006fb9c0@@YGXM@Z
void __stdcall set_006fb9c0(float v)
{
	TheW3DFrameLengthInMsec = (int)v;
}

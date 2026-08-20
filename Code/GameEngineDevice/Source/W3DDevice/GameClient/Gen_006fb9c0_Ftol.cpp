// cl: /DNDEBUG /MD /EHsc

// Retail 0x006FB9C0. Store (int)float into a global via __ftol2.

int g_006fb9c0;

// ?set_006fb9c0@@YGXM@Z
void __stdcall set_006fb9c0(float v)
{
	g_006fb9c0 = (int)v;
}

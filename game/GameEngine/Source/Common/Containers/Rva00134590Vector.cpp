// cl: /DNDEBUG /DWIN32 /MD /EHsc /D_STLP_USE_STATIC_LIB /Igame/Libraries/Source/WWVegas/WWLib
// stlport
// Three STLport destroy-range helpers over the observed 20-byte element whose
// destructor body is 0x00134590.  The original class identity is unknown;
// Gen00134590 is the address-qualified element name already used by the
// matching no-exceptions vector destructor family.

struct Gen00134590
{
	unsigned char m_body[0x14];
	~Gen00134590();
};

// The three retail copies are separate helpers, despite sharing the same
// element width and destructor route through ILT 0x0003B589.
void Rva001362D0Destroy(Gen00134590 *first, Gen00134590 *last)
{
	while (first != last)
	{
		first->~Gen00134590();
		++first;
	}
}

void Rva001369D0Destroy(Gen00134590 *first, Gen00134590 *last)
{
	while (first != last)
	{
		first->~Gen00134590();
		++first;
	}
}

void Rva00137660Destroy(Gen00134590 *first, Gen00134590 *last)
{
	while (first != last)
	{
		first->~Gen00134590();
		++first;
	}
}

// cl: /DNDEBUG /MD /EHsc
// Open-BFME: Glo012F7048Type::test, retail 0x00609350, 12 bytes.
//
// Three instructions: load the global at 0x012F706C and hand back the byte at
// +0x288. The method is a thiscall by its decorated name but never touches
// `this' -- the answer comes entirely out of the global.

typedef bool Bool;

// retail 0x012F706C: the singleton whose COFF name is
// ?g_bfmeGameCW@@3PAVBfmeGameCW@@A (symbols.csv); only the byte at +0x288 is
// read here.
class BfmeGameCW
{
public:
	unsigned char m_unmodelled_000[0x288];
	Bool m_flag;						// +0x288
};

extern BfmeGameCW *g_bfmeGameCW;

class Glo012F7048Type
{
public:
	Bool test(void);
};

Bool Glo012F7048Type::test(void)
{
	return g_bfmeGameCW->m_flag;
}

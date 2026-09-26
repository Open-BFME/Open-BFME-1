// cl: /DNDEBUG /MD /EHsc
// Open-BFME: Glo012F7048Type::test, retail 0x00609350, 12 bytes.
//
// Three instructions: load the global at 0x012F706C and hand back the byte at
// +0x288. The method is a thiscall by its decorated name but never touches
// `this' -- the answer comes entirely out of the global.

typedef bool Bool;

class BfmeGlobal012F706C
{
public:
	unsigned char m_unmodelled_000[0x288];
	Bool m_flag;						// +0x288
};

extern BfmeGlobal012F706C *TheBfmeGlobal012F706C;

class Glo012F7048Type
{
public:
	Bool test(void);
};

Bool Glo012F7048Type::test(void)
{
	return TheBfmeGlobal012F706C->m_flag;
}

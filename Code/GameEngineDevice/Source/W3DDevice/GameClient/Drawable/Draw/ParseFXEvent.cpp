// cl: /DNDEBUG /MD /EHsc
// Open-BFME: the FXEvent INI field parser, retail 0x00776A90, 35 bytes.
//
// The animation-state FieldParse table at 0x012BB650 pairs the string
// "FXEvent" with this body at row 0x012BB6C0. The same table pairs
// "ParticleSysBone" with the landed parseParticleSysBone at 0x0076E7B0 and
// "Animation" with the landed parseAnimation at 0x00774FD0, so the table reads
// one animation state block and the field names this function.
//
// The body only forwards. It rejects a null state block, then tail-calls the
// shared reader at 0x007764E0 with three interior pointers of that block. The
// landed bfmeGoCHG at 0x00776A50 sits directly above and forwards to the same
// reader with the same three-slot shape at offsets 0x9C, 0xA0 and 0xAC.
class INI;

struct BfmeAnimationStateFXE
{
	unsigned char m_bfmeHead[0x50];
	unsigned char m_bfmeA[4];
	unsigned char m_bfmeB[0xc];
	unsigned char m_bfmeC[4];
};

void bfmeTailCHG( void *one, void *two, void *three, void *four );

void parseFXEvent( INI *ini, void *instance, void *store, const void *userData )
{
	BfmeAnimationStateFXE *state = (BfmeAnimationStateFXE *)instance;
	if( state == 0 )
		return;
	bfmeTailCHG( ini, state->m_bfmeB, state->m_bfmeC, state->m_bfmeA );
}

// cl: /DNDEBUG /MD /EHsc
// Open-BFME: the ParticleSysBone INI field parser, retail 0x0076E7B0, 23 bytes.
//
// The animation-state FieldParse table at 0x012BB650 pairs the string
// "ParticleSysBone" with this body, and the same table pairs "Animation" with
// the landed parseAnimation at 0x00B74FD0. Zero Hour spells the callback
// parseParticleSysBone in W3DModelDraw.cpp, where it appends to
// ModelConditionInfo::m_particleSysBones.
//
// BFME moved the work into the shared function at 0x0076E4F0, which the ledger
// pins as bfmeCallEMA. This body only forwards, handing that function the INI
// reader, the state block and the list at offset 0x50 of the state block.
class INI;
struct BfmeThingEMA;
struct BfmeSubEMA;

void __cdecl bfmeCallEMA( void *a, BfmeThingEMA *b, BfmeSubEMA *s );

void parseParticleSysBone( INI *ini, void *instance, void *store, const void *userData )
{
	bfmeCallEMA( ini, (BfmeThingEMA *)instance, (BfmeSubEMA *)( (char *)instance + 0x50 ) );
}

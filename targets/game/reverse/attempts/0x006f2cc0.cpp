// ?gatherAnimationDebuggingInfo@W3DDisplay@@IAEXXZ
// partial score=0.03 date=2026-09-02
// cl: /DNDEBUG /MD /EHsc
// Partial reconstruction of retail 0x006F2CC0. String xrefs identify this as
// W3DDisplay::gatherAnimationDebuggingInfo; the routine is BFME-only and the
// Zero Hour W3DDisplay source has no corresponding body.
// The protected-member spelling is consistent with gatherDebugStats in the ZH
// W3DDisplay header. Retail has a 0x5c-byte local frame and an SEH unwind frame.
// Unique strings cover old/current animation names and frames, condition-flag
// deltas, subobject status, weapon state, forced EnterLogic desync, and the
// shift+mouse locked-object debugger. High-confidence direct callees include
// UnicodeString construction/concat/destruction and FontLibrary::getFont.

class AnimationDebugUnwind
{
public:
	~AnimationDebugUnwind();
};

class W3DDisplay
{
protected:
	void gatherAnimationDebuggingInfo();
};

volatile int g_animationDebugPartialUnwind;
void bfmeAnimationDebugPartialStep();

void W3DDisplay::gatherAnimationDebuggingInfo()
{
	AnimationDebugUnwind unwind;
	bfmeAnimationDebugPartialStep();
	volatile unsigned long controlFlowSkeleton[23];
	for (int i = 0; i != 23; ++i)
		controlFlowSkeleton[i] = 0;
}

void bfmeAnimationDebugPartialStep()
{
}

AnimationDebugUnwind::~AnimationDebugUnwind()
{
	++g_animationDebugPartialUnwind;
}

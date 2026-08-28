// cl: /DNDEBUG /MD /EHs-c-
// readable body of ?ReAcquireResources@W3DShadowManager@@QAE_NXZ: Code/GameEngineDevice/Source/W3DDevice/GameClient/Shadow/W3DShadow.cpp
// Open-BFME5: W3DShadowManager::ReAcquireResources, retail 0x007B7620,
// converted out of a machine byte dump.
//
// Zero Hour asks two shadow managers to reacquire; BFME asks three, and all
// three keep address-derived names here because none of them is settled:
//
//   0x01306F18  -> ILT 0x000443A0 -> 0x007B9810   (a dump)
//   0x01307178  -> ILT 0x0000F9B6 -> 0x007C1180   (a dump)
//   0x01306DF0  -> ILT 0x00026D1E -> 0x007AE890   (a dump)
//
// The reference calls volumetric first and projected second, which would make
// 0x000443A0 the volumetric one -- but functions.csv already claims
// ?ReAcquireResources@W3DVolumetricShadowManager@@QAE_NXZ at 0x0000F9B6, the
// SECOND of these, and claims it on the five-byte thunk rather than on a body.
// Two readings, one of them wrong, and this body cannot say which; spending
// either name here would bury the disagreement.
//
// The third test is folded: retail answers the failure by falling through to
// `pop ebx; ret` with al already zero rather than clearing bl and reloading it,
// which is the same `ok = FALSE; return ok` the other two arms spell out.

typedef bool Bool;

#define TRUE true
#define FALSE false

class Gen_01306F18
{
public:
	Bool ReAcquireResources( void );
};

class Gen_01307178
{
public:
	Bool ReAcquireResources( void );
};

class Gen_01306DF0
{
public:
	Bool ReAcquireResources( void );
};

extern Gen_01306F18 *g_01306F18;
extern Gen_01307178 *g_01307178;
extern Gen_01306DF0 *g_01306DF0;

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include/W3DDevice/GameClient/W3DShadow.h
class W3DShadowManager
{
public:
	Bool ReAcquireResources( void );
};

// ?ReAcquireResources@W3DShadowManager@@QAE_NXZ
Bool W3DShadowManager::ReAcquireResources( void )
{
	Bool ok = TRUE;

	if (g_01306F18 && !g_01306F18->ReAcquireResources())
		ok = FALSE;

	if (g_01307178 && !g_01307178->ReAcquireResources())
		ok = FALSE;

	if (g_01306DF0 && !g_01306DF0->ReAcquireResources())
		ok = FALSE;

	return ok;
}

// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc
// Complete reconstruction of the complete retail entry 0x007B7500..0x007B755C
// (93 bytes).  This is the callable start; 0x007B751E is only the interior
// continuation containing the second and third pairs.

typedef bool Bool;

// The first two BFME shadow submanager identities are intentionally kept
// address-derived.  Their constructor and reacquire-body names disagree, but
// the three physical globals and all six direct targets are established.
class Gen_01306F18
{
public:
	Bool rva007B9920(void);
	Bool ReAcquireResources(void);
};

class Gen_01307178
{
public:
	Bool rva007C19E0(void);
	Bool ReAcquireResources(void);
};

class Gen_01306DF0
{
public:
	Bool rva007AF630(void);
	Bool ReAcquireResources(void);
};

extern Gen_01306F18 *g_01306F18;
extern Gen_01307178 *g_01307178;
extern Gen_01306DF0 *g_01306DF0;

class W3DShadowManager
{
public:
	Bool init(void);
};

Bool W3DShadowManager::init(void)
{
	if (g_01306F18 && g_01306F18->rva007B9920())
		g_01306F18->ReAcquireResources();

	if (g_01307178 && g_01307178->rva007C19E0())
		g_01307178->ReAcquireResources();

	if (g_01306DF0 && g_01306DF0->rva007AF630())
		g_01306DF0->ReAcquireResources();

	return true;
}

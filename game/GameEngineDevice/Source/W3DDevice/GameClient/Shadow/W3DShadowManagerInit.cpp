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
class W3DProjectedShadowManager;
extern W3DProjectedShadowManager *TheW3DProjectedShadowManager;

// 0x01307178 is W3DShadow.cpp's TheW3DShadowHelperManager, so the global is
// spelled by its defining name here.  No header declares the class, so only a
// forward declaration is needed: the two bodies this TU calls are still
// ledger-named Gen_01307178, and that view is kept for the member calls.
class W3DShadowHelperManager;
extern W3DShadowHelperManager *TheW3DShadowHelperManager;

class W3DShadowManager
{
public:
	Bool init(void);
};

Bool W3DShadowManager::init(void)
{
	if (g_01306F18 && g_01306F18->rva007B9920())
		g_01306F18->ReAcquireResources();

	if ((Gen_01307178 *)TheW3DShadowHelperManager && ((Gen_01307178 *)TheW3DShadowHelperManager)->rva007C19E0())
		((Gen_01307178 *)TheW3DShadowHelperManager)->ReAcquireResources();

	if (TheW3DProjectedShadowManager && reinterpret_cast<Gen_01306DF0 *>(TheW3DProjectedShadowManager)->rva007AF630())
		reinterpret_cast<Gen_01306DF0 *>(TheW3DProjectedShadowManager)->ReAcquireResources();

	return true;
}

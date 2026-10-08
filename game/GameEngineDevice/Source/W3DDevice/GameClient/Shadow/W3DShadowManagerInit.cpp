// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc
// Complete reconstruction of the complete retail entry 0x007B7500..0x007B755C
// (93 bytes).  This is the callable start; 0x007B751E is only the interior
// continuation containing the second and third pairs.

class W3DVolumetricShadowManager;
extern W3DVolumetricShadowManager *TheW3DVolumetricShadowManager;

typedef bool Bool;

// The first two BFME shadow submanager identities are intentionally kept
// address-derived.  Their constructor and reacquire-body names disagree, but
// the three physical globals and all six direct targets are established.
// callees.py 0x7B7500: each call reaches the ledger row named below (ILT ->
// body).  The class views follow those rows' spellings; which global owns
// which body is the evidence recorded above, not these names.
class Gen_007b9920
{
public:
	Bool m(void);					// ILT 0x000269FE -> 0x007B9920
};

class W3DShadowHelperManager
{
public:
	Bool ReAcquireResources(void);			// ILT 0x000443A0 -> 0x007B9810
};

class W3DVolumetricShadowManager
{
public:
	Bool init(void);				// ILT 0x0001EAA6 -> 0x007C19E0
};

class Gen_01307178
{
public:
	Bool ReAcquireResources(void);			// ILT 0x0000F9B6 -> 0x007C1180
};

class W3DProjectedShadowManager
{
public:
	Bool init(void);				// ILT 0x0003F93B -> 0x007AF630
	Bool ReAcquireResources(void);			// ILT 0x00026D1E -> 0x007AE890
};

extern W3DProjectedShadowManager *TheW3DProjectedShadowManager;

// 0x01307178 is W3DShadow.cpp's TheW3DShadowHelperManager, so the global is
// spelled by its defining name here.  No header declares the class, so only a
// forward declaration is needed: the two bodies this TU calls are still
// ledger-named Gen_01307178, and that view is kept for the member calls.
extern W3DShadowHelperManager *TheW3DShadowHelperManager;

class W3DShadowManager
{
public:
	Bool init(void);
};

Bool W3DShadowManager::init(void)
{
	if (TheW3DVolumetricShadowManager && ((Gen_007b9920 *)TheW3DVolumetricShadowManager)->m())
		((W3DShadowHelperManager *)TheW3DVolumetricShadowManager)->ReAcquireResources();

	if (TheW3DShadowHelperManager && ((W3DVolumetricShadowManager *)TheW3DShadowHelperManager)->init())
		((Gen_01307178 *)TheW3DShadowHelperManager)->ReAcquireResources();

	if (TheW3DProjectedShadowManager && TheW3DProjectedShadowManager->init())
		TheW3DProjectedShadowManager->ReAcquireResources();

	return true;
}

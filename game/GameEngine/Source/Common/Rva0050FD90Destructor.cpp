// cl: /DNDEBUG /MD /EHsc
// Open-BFME5: near-twin of ??1W3DDisplayString (0x006F4C50, W3DDisplayString.cpp);
// same single-vtable shape, but this body reports through the shared manager
// global at 0x012F19E8, g_rva012F19E8WindowManager (same global as the
// 0x00470360 neighbour), before zeroing a
// separate global and chaining to the already-landed base destructor
// S4Owner::~S4Owner (0x00464E20 via ILT 0x00021FC1).

class GenActionSink
{
public:
	void add(void *a, const char *b, int c, const char *d, int e, int f, int g, int h);
};

// Retail 0x012F19E8 is the game-wide manager pointer EA defines as
// `WindowManager *g_rva012F19E8WindowManager` in
// game/GameEngine/Source/GameClient/GUI/WindowManager.cpp. This TU only needs
// the sink add() through it, so the pointee stays the local GenActionSink view
// and the access is cast at the use.
class WindowManager;

extern WindowManager *g_rva012F19E8WindowManager;
class BfmeAptScreenMapTransfer;

extern BfmeAptScreenMapTransfer *g_rva012F496CBfmeAptScreenMapTransfer;

class S4Owner
{
public:
	virtual ~S4Owner();
};

class Rva0050FD90 : public S4Owner
{
public:
	virtual ~Rva0050FD90();
};

// ??1Rva0050FD90@@UAE@XZ
Rva0050FD90::~Rva0050FD90()
{
	((GenActionSink *)g_rva012F19E8WindowManager)->add((void *)0xb, "FileTransferPopUpClose", 0, 0, 0, 0, 0, 0);
	g_rva012F496CBfmeAptScreenMapTransfer = 0;
}

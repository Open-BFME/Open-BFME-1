// cl: /DNDEBUG /MD /EHsc /D_STLP_NO_EXCEPTIONS /Ireference/shims/stringinline
// Real C++ reconstruction of ?update@GameState@@UAEXXZ.
//
// The BFME GameState headers declare update inline as an empty override.
// Retail's primary GameState vtable at 0x010893E0 routes slot 5 through the
// matched ILT 0x00043586 to the standalone one-byte body at 0x00111070.
// This TU keeps only the ABI declarations needed to emit that named method;
// all GameState data layout remains established by the neighboring landed
// constructors and save/load bodies.

class SubsystemInterface
{
public:
	virtual ~SubsystemInterface();
	virtual void init() = 0;
	virtual void postProcessLoad() {}
	virtual void reset() = 0;
	virtual void update() = 0;
	virtual void draw() {}
};

class Snapshot
{
public:
	virtual ~Snapshot() {}
	virtual void crc(void *xfer) = 0;
	virtual void xfer(void *xfer) = 0;
	virtual void loadPostProcess() = 0;
};

class __declspec(novtable) GameState : public SubsystemInterface,
	public Snapshot
{
public:
	virtual void init();
	virtual void reset();
	virtual void update();
};

// ?update@GameState@@UAEXXZ
void GameState::update()
{
}

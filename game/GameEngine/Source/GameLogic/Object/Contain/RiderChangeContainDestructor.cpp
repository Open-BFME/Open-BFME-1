// cl: /O2 /DNDEBUG /MD /EHsc
//
// Retail 0x0022A540: RiderChangeContain's complete destructor. The matched
// scalar-deleting wrapper at 0x0022A510 reaches it through ILT 0x0001CA80;
// tools/ilt_oracle.py confirms the public spelling (??1RiderChangeContain@@UAE@XZ
// exact, the protected MAE spelling contradicted). The class adds nothing to
// destroy and the base destructor re-seats the vptrs at once, so retail drops
// this class's own stores (novtable here): the body is a single tail jump to
// the SiegeEngineContain destructor (ILT 0x0004AB47 -> matched 0x0022B870).

class SiegeEngineContain
{
protected:
	virtual ~SiegeEngineContain();
};

class __declspec(novtable) RiderChangeContain : public SiegeEngineContain
{
public:
	virtual ~RiderChangeContain();
};

RiderChangeContain::~RiderChangeContain()
{
}

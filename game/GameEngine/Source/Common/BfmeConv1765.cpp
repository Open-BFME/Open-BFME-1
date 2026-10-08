class SubsystemInterface
{
public:
	virtual ~SubsystemInterface(void);

	unsigned char m_bfmeHeadCE[4];
};

// Second base: the cleanup funclet 0x00BFDF78 destroys this+8 through
// ??1Snapshot@@UAE@XZ (ILT 0x00001C80, named by the PE export table).
#include "System/snapshot.h"

class BfmeOwnCE : public SubsystemInterface, public Snapshot
{
public:
	virtual ~BfmeOwnCE(void);

	void bfmeShutdownCE(void);
};

BfmeOwnCE::~BfmeOwnCE(void)
{
	bfmeShutdownCE();
}

// cl: /DNDEBUG /MD /EHsc

// Clean facade for BFME's permanent reveal path.  The public
// PartitionManager stores its implementation at +0x0C; this operation shares
// the implementation body used by the adjacent BFME cell sweep, whose clean
// declaration is BfmeMgrVNR::bfmeUpdateVNR.

typedef int Int;

class BfmeMgrVNR
{
public:
	void bfmeUpdateVNR(Int playerIndex);
};

class PartitionManagerImpl008F8D60
{
};

class PartitionManager
{
public:
	void revealMapForPlayerPermanently(Int playerIndex);

private:
	char m_bfmeHead[0x0c];
	PartitionManagerImpl008F8D60 *m_impl;
};

void PartitionManager::revealMapForPlayerPermanently(Int playerIndex)
{
	reinterpret_cast<BfmeMgrVNR *>(m_impl)->bfmeUpdateVNR(playerIndex);
}

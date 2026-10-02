class BfmeSinkBMD
{
public:
	void *bfmeMakeBMD(void *what);
};

// The sink global at dir32 0x012EF188 is TheUpgradeCenter, declared
// UpgradeCenter* by the registration site in GameEngine::init.
class UpgradeCenter;

extern UpgradeCenter *TheUpgradeCenter;

class BfmeThingBMD
{
public:
	void bfmeGoBMD();
	unsigned char m_bfmeHead[4];
	void *m_bfmeWhat;
	unsigned char m_bfmeGap[0x24];
	void *m_bfmeGot;
};

void BfmeThingBMD::bfmeGoBMD()
{
	m_bfmeGot = reinterpret_cast<BfmeSinkBMD *>(TheUpgradeCenter)
		->bfmeMakeBMD((char *)m_bfmeWhat + 0x18);
}

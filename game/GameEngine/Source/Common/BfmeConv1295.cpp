// Open-BFME5 conversions.

extern float g_bfmeK1SMA;
extern float g_bfmeK2SMA;
extern float g_bfmeK3SMA;

class BfmeThingSMA
{
public:
	virtual void bfmeV0SMA() = 0;
	virtual void bfmeV1SMA() = 0;
	virtual void bfmeV2SMA() = 0;
	virtual void bfmeV3SMA() = 0;
	virtual void bfmeV4SMA() = 0;
	virtual void bfmeV5SMA() = 0;
	virtual void bfmeV6SMA() = 0;
	virtual void bfmeV7SMA() = 0;
	virtual void bfmeV8SMA() = 0;
	virtual void bfmeV9SMA() = 0;
	virtual void bfmeV10SMA() = 0;
	virtual void bfmeV11SMA() = 0;
	virtual void bfmeV12SMA() = 0;
	virtual void bfmeV13SMA() = 0;
	virtual void bfmeV14SMA() = 0;
	virtual void bfmeV15SMA() = 0;
	virtual void bfmeV16SMA() = 0;
	virtual void bfmeV17SMA() = 0;
	virtual void bfmeV18SMA() = 0;
	virtual void bfmeV19SMA() = 0;
	virtual void bfmeV20SMA() = 0;
	virtual void bfmeV21SMA() = 0;
	virtual void bfmeV22SMA() = 0;
	virtual void bfmeV23SMA() = 0;
	virtual void bfmeV24SMA() = 0;
	virtual void bfmeV25SMA() = 0;
	virtual void bfmeV26SMA() = 0;
	virtual void bfmeV27SMA() = 0;
	virtual void bfmeV28SMA() = 0;
	virtual void bfmeV29SMA() = 0;
	virtual void bfmeV30SMA() = 0;
	virtual void bfmeV31SMA() = 0;
	virtual void bfmeV32SMA() = 0;
	virtual void bfmeV33SMA() = 0;
	virtual void bfmeV34SMA() = 0;
	virtual void bfmeV35SMA() = 0;
	virtual void bfmeV36SMA() = 0;
	virtual void bfmeV37SMA() = 0;
	virtual void bfmeV38SMA() = 0;
	virtual void bfmeV39SMA() = 0;
	virtual void bfmeV40SMA() = 0;
	virtual void bfmeV41SMA() = 0;
	virtual void bfmeV42SMA() = 0;
	virtual void bfmeV43SMA() = 0;
	virtual void bfmeV44SMA() = 0;
	virtual void bfmeV45SMA() = 0;
	virtual void bfmeV46SMA() = 0;
	virtual void bfmeV47SMA() = 0;
	virtual void bfmeV48SMA() = 0;
	virtual void bfmeV49SMA() = 0;
	virtual void bfmeV50SMA() = 0;
	virtual void bfmeV51SMA() = 0;
	virtual void bfmeV52SMA() = 0;
	virtual void bfmeV53SMA() = 0;
	virtual void bfmeV54SMA() = 0;
	virtual void bfmeV55SMA() = 0;
	virtual void bfmeV56SMA() = 0;
	virtual void bfmeV57SMA() = 0;
	virtual void bfmeV58SMA() = 0;
	virtual void bfmeV59SMA() = 0;
	virtual void bfmeV60SMA() = 0;
	virtual void bfmeV61SMA() = 0;
	virtual void bfmeV62SMA() = 0;
	virtual void bfmeV63SMA() = 0;
	virtual void bfmeV64SMA() = 0;
	virtual void bfmeV65SMA() = 0;
	virtual void bfmeV66SMA() = 0;
	virtual void bfmeV67SMA() = 0;
	virtual void bfmeV68SMA() = 0;
	virtual void bfmeV69SMA() = 0;
	virtual void bfmeV70SMA() = 0;
	virtual void bfmeV71SMA() = 0;
	virtual void bfmeV72SMA() = 0;
	virtual void bfmeV73SMA() = 0;
	virtual float bfmeGetSMA() = 0;
	virtual void bfmeSetSMA(float v) = 0;
	void bfmeOneSMA();
	void bfmeTwoSMA();
};

void BfmeThingSMA::bfmeOneSMA()
{
	bfmeSetSMA(bfmeGetSMA() * g_bfmeK1SMA - g_bfmeK3SMA);
}

void BfmeThingSMA::bfmeTwoSMA()
{
	bfmeSetSMA(bfmeGetSMA() * g_bfmeK2SMA + g_bfmeK3SMA);
}

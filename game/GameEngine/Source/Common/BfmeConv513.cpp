extern int g_bfmeFlagBRA;

class BfmeThingBRA
{
public:
	void bfmeOneBRA();
	bool bfmeTwoBRA();
	bool bfmeGoBRA();
};

bool BfmeThingBRA::bfmeGoBRA()
{
	if (g_bfmeFlagBRA == 0)
		return false;
	bfmeOneBRA();
	return bfmeTwoBRA();
}

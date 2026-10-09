class BfmeThingCBB
{
public:
	void bfmeOneCBB(void *what);
	void bfmeTwoCBB(void *what, int value);
	void bfmeThreeCBB(void *what);
	void bfmeGoCBB(void *what);
};

class SkirmishScreenState
{
public:
	void refreshPlayerTypeCombo00527220(int value);
	void rva005294F0(int value);
	void rebuildTeamCombo005268F0(int value, bool flag);
};

void BfmeThingCBB::bfmeGoCBB(void *what)
{
	((SkirmishScreenState *)this)->refreshPlayerTypeCombo00527220((int)what);
	((SkirmishScreenState *)this)->rebuildTeamCombo005268F0((int)what, false);
	((SkirmishScreenState *)this)->rva005294F0((int)what);
}

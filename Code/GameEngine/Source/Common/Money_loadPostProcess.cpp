// cl: /DNDEBUG /MD /EHsc
// Money::loadPostProcess, retail 0x000CBAC0: slot 1 of Money's vftable
// 0x01083d18, BFME's Snapshot loadPostProcess slot. The retail body is a lone
// ret; Zero Hour declares the method protected.
class Money
{
protected:
	virtual void loadPostProcess(void);
};

// ?loadPostProcess@Money@@MAEXXZ
void Money::loadPostProcess(void)
{
}  // end loadPostProcess

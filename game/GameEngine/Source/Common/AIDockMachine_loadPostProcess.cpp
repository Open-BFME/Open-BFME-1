// cl: /DNDEBUG /MD /EHsc
// AIDockMachine::loadPostProcess, retail 0x0014E6A0: slot 1 of AIDockMachine's vftable
// 0x01095a38, BFME's Snapshot loadPostProcess slot. The retail body is a lone
// ret; Zero Hour declares the method protected.
class AIDockMachine
{
protected:
	virtual void loadPostProcess(void);
};

// ?loadPostProcess@AIDockMachine@@MAEXXZ
void AIDockMachine::loadPostProcess(void)
{
}  // end loadPostProcess

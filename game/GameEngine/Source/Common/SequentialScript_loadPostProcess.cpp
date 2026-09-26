// cl: /DNDEBUG /MD /EHsc
// SequentialScript::loadPostProcess, retail 0x00339A60: slot 1 of SequentialScript's vftable
// 0x010e7660, BFME's Snapshot loadPostProcess slot. The retail body is a lone
// ret; Zero Hour declares the method protected.
class SequentialScript
{
protected:
	virtual void loadPostProcess(void);
};

// ?loadPostProcess@SequentialScript@@MAEXXZ
void SequentialScript::loadPostProcess(void)
{
}  // end loadPostProcess

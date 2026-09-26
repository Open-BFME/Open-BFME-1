// cl: /DNDEBUG /MD /EHsc
// Weapon::loadPostProcess, retail 0x001E53A0: slot 1 of Weapon's vftable
// 0x010a13f4, BFME's Snapshot loadPostProcess slot. The retail body is a lone
// ret; Zero Hour declares the method protected.
class Weapon
{
protected:
	virtual void loadPostProcess(void);
};

// ?loadPostProcess@Weapon@@MAEXXZ
void Weapon::loadPostProcess(void)
{
}  // end loadPostProcess

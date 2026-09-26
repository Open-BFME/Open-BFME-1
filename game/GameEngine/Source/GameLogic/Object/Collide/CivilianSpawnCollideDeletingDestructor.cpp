// cl: /DNDEBUG /MD /EHsc
//
// Open-BFME: protected scalar-deleting destructor for CivilianSpawnCollide.
// Vtable 0x00CAA21C slots name this class (?getModuleNameKey@CivilianSpawnCollide@@UBE?AW4NameKeyType@@XZ); its slot zero routes
// through ILT 0x0003F927 to this 30-byte wrapper, whose complete destructor
// route ILT 0x0003A6B1 reaches cleanup body 0x00217320.

class CivilianSpawnCollide
{
protected:
	virtual ~CivilianSpawnCollide();
private:
	friend void forceCivilianSpawnCollideDeletingDestructor();
};

void forceCivilianSpawnCollideDeletingDestructor()
{
	CivilianSpawnCollide value;
}

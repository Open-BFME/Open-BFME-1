// cl: /DNDEBUG /MD /EHsc
//
// Open-BFME5: CrateTemplate protected scalar-deleting destructor at retail
// RVA 0x0037A2F0 (30 bytes). Its exact constructor at 0x00379DC0, complete
// destructor at 0x00379EC0, and recovered CrateSystem/parser method family
// establish the class. The destructor ILT is 0x0002FC70.

class CrateTemplate
{
	friend void forceCrateTemplateDeletingDestructor();

protected:
	virtual ~CrateTemplate();
};

void forceCrateTemplateDeletingDestructor()
{
	CrateTemplate value;
}

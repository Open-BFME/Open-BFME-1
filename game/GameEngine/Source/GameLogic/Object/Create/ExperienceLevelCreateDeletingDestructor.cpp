// cl: /DNDEBUG /MD /EHsc
//
// Open-BFME: protected scalar-deleting destructor for ExperienceLevelCreate.
// Vtable 0x00CB151C slots name this class (?getModuleNameKey@ExperienceLevelCreate@@UBE?AW4NameKeyType@@XZ); its slot zero routes
// through ILT 0x0000236F to this 30-byte wrapper, whose complete destructor
// route ILT 0x00008058 reaches cleanup body 0x0024F400.

class ExperienceLevelCreate
{
protected:
	virtual ~ExperienceLevelCreate();
private:
	friend void forceExperienceLevelCreateDeletingDestructor();
};

void forceExperienceLevelCreateDeletingDestructor()
{
	ExperienceLevelCreate value;
}

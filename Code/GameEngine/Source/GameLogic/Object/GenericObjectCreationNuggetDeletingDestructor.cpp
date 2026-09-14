// cl: /DNDEBUG /MD /EHsc
//
// Open-BFME5: GenericObjectCreationNugget protected scalar-deleting destructor
// at retail RVA 0x001D81F0 (30 bytes). Its exact constructor at 0x001D7D70,
// complete destructor at 0x001D8220, and recovered parser and asset-method
// family establish the class. The destructor ILT is 0x0004706E.

class GenericObjectCreationNugget
{
	friend void forceGenericObjectCreationNuggetDeletingDestructor();

protected:
	virtual ~GenericObjectCreationNugget();
};

void forceGenericObjectCreationNuggetDeletingDestructor()
{
	GenericObjectCreationNugget value;
}

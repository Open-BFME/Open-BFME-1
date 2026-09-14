// cl: /DNDEBUG /MD /EHsc
//
// Open-BFME: protected scalar-deleting destructor for EntEnragedUpdate.
// Vtable 0x00CBE8AC slots name this class (?getModuleNameKey@EntEnragedUpdate@@UBE?AW4NameKeyType@@XZ); its slot zero routes
// through ILT 0x00018B6A to this 30-byte wrapper, whose complete destructor
// route ILT 0x0002D35D reaches cleanup body 0x00291890.

class EntEnragedUpdate
{
protected:
	virtual ~EntEnragedUpdate();
private:
	friend void forceEntEnragedUpdateDeletingDestructor();
};

void forceEntEnragedUpdateDeletingDestructor()
{
	EntEnragedUpdate value;
}

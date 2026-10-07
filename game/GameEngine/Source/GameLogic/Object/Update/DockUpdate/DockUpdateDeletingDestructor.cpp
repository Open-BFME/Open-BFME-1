// cl: /DNDEBUG /MD /EHsc
//
// Open-BFME5: DockUpdate scalar-deleting destructor at retail RVA 0x002CD180
// (30 bytes).  Its exact complete destructor is ??1DockUpdate@@MAE@XZ at
// 0x002CCD10, reached through ILT 0x0004418E.  The matched base constructor at
// 0x002CD4B0 installs vtable 0x010CA934, whose slot zero reaches this wrapper
// through ILT 0x00046EDE; the recovered DockUpdate interface methods corroborate
// the class identity.

class DockUpdate
{
protected:
	virtual ~DockUpdate();

private:
	friend void forceDockUpdateDeletingDestructor();
};

void forceDockUpdateDeletingDestructor()
{
	DockUpdate value;
}

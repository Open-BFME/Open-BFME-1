// cl: /DNDEBUG /MD /EHsc
// Open-BFME5: LaserUpdate scalar-deleting destructor.
// LaserUpdate's complete destructor is emitted by
// LaserUpdateDestructorAndRadius.cpp.  This declaration-only TU makes MSVC
// emit the exact retail scalar wrapper while binding its dtor call to that
// matched class body.

class LaserUpdate
{
public:
	virtual ~LaserUpdate();
};

// ??_GLaserUpdate@@UAEPAXI@Z
void forceLaserUpdateDeletingDestructor()
{
	LaserUpdate value;
}

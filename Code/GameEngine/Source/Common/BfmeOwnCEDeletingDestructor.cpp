// cl: /DNDEBUG /MD /EHsc
// Open-BFME5: BfmeOwnCE scalar-deleting destructor.
// The complete two-base destructor is emitted by BfmeConv1765.cpp.  This
// declaration-only TU makes MSVC emit the exact scalar wrapper and binds its
// direct call to that matched class destructor.

class BfmeOwnCE
{
public:
	virtual ~BfmeOwnCE();
};

// ??_GBfmeOwnCE@@UAEPAXI@Z
void forceBfmeOwnCEDeletingDestructor()
{
	BfmeOwnCE value;
}

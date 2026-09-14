// cl: /DNDEBUG /MD /EHsc
// Open-BFME5: BfmeVolumetricShadowBufferOwner scalar-deleting destructor.
// The matched complete destructor is emitted by
// W3DVolumetricShadowBufferOwnerDtor.cpp.  This declaration-only TU makes
// MSVC emit the exact retail scalar wrapper and binds its direct call to that
// named class destructor.

class BfmeVolumetricShadowBufferOwner
{
public:
	virtual ~BfmeVolumetricShadowBufferOwner();
};

// ??_GBfmeVolumetricShadowBufferOwner@@UAEPAXI@Z
void forceBfmeVolumetricShadowBufferOwnerDeletingDestructor()
{
	BfmeVolumetricShadowBufferOwner value;
}

// cl: /DNDEBUG /MD /EHsc
//
// Open-BFME: MultiPlayerLoadScreen scalar-deleting destructor at retail RVA
// 0x00491260 (30 bytes).  The exact constructor at 0x00490790 installs
// vtable 0x010F9B28, and the matched complete virtual destructor at 0x00490890
// owns the four per-slot tables before chaining through the window base.

class MultiPlayerLoadScreen
{
public:
	virtual ~MultiPlayerLoadScreen();
};

void forceMultiPlayerLoadScreenDeletingDestructor()
{
	MultiPlayerLoadScreen value;
}

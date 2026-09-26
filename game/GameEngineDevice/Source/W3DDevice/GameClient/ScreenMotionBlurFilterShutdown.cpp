// cl: /DNDEBUG /MD /EHsc
// Retail 0x007D8870, ScreenMotionBlurFilter vtable 0x01128BD0 slot 1.
// The slot-1 body is the standalone TRUE-returning shutdown; its identical
// bytes are also claimed by the independently named parseNoLogOrCrash ICF
// owner already present at this address.

typedef int Int;

class ScreenMotionBlurFilter
{
public:
	virtual Int shutdown();
};

// ?shutdown@ScreenMotionBlurFilter@@UAEHXZ
Int ScreenMotionBlurFilter::shutdown(void)
{
	return true;
}

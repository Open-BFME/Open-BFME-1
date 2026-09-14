// cl: /DNDEBUG /MD /EHsc

// Open-BFME: GiantBirdSlowDeathBehavior scalar-deleting destructor at retail
// 0x001FFDE0 (30 bytes).  The matched behavior constructor at 0x001FFB40 and
// complete virtual destructor at 0x001FFC10, together with the named behavior
// factory, establish the authentic class identity.

class GiantBirdSlowDeathBehavior
{
public:
	__declspec(noinline) virtual ~GiantBirdSlowDeathBehavior();
};

GiantBirdSlowDeathBehavior::~GiantBirdSlowDeathBehavior()
{
}

void Force_GiantBirdSlowDeathBehavior_Deleting_Destructor(
	GiantBirdSlowDeathBehavior *value)
{
	delete value;
}

// cl: /DNDEBUG /MD /EHsc
//
// Open-BFME: scalar-deleting destructor for SpecialPowerCompletionDie.
// Its unique primary vtable (0x010B3414) is installed by the named
// constructor at 0x00255E30; slot zero routes through ILT 0x00023FF1 to
// this 30-byte wrapper.  Retail teardown evidence includes the class's
// complete destructor at 0x00255FD0 and nested/base teardown at 0x00255DD0.

// The retail slot calls the compiler's complete-destructor ILT at 0x00033866,
// whose object symbol is the generated placeholder name below.  Keep that
// TU-local spelling so the relocation resolves to retail nested teardown;
// the typedef carries the recovered class identity used by the force site.
class Gen_dtor_00255f30
{
public:
	virtual ~Gen_dtor_00255f30();

private:
	friend void forceSpecialPowerCompletionDieDeletingDestructor();
};

typedef Gen_dtor_00255f30 SpecialPowerCompletionDie;

void forceSpecialPowerCompletionDieDeletingDestructor()
{
	SpecialPowerCompletionDie value;
}

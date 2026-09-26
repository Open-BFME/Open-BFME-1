// cl: /DNDEBUG /MD /EHsc
//
// Open-BFME: scalar-deleting destructor for CreateCrateDie.
// Its unique primary vtable (0x010B29CC) is installed by the named
// constructor at 0x00253E70; slot zero routes through ILT 0x0004142A to
// this 30-byte wrapper.  Retail teardown evidence includes the class's
// complete destructor at 0x00379440 and nested/base teardown at 0x00253D30.

// Retail's slot calls the compiler's complete-destructor ILT at 0x0004142A,
// whose TU-local object symbol remains the generated placeholder spelling.
// The recovered typedef preserves the named class identity at the force site.
class Gen_dtor_00253f60
{
public:
	virtual ~Gen_dtor_00253f60();

private:
	friend void forceCreateCrateDieDeletingDestructor();
};

typedef Gen_dtor_00253f60 CreateCrateDie;

void forceCreateCrateDieDeletingDestructor()
{
	CreateCrateDie value;
}

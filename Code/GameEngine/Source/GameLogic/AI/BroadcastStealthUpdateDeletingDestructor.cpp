// cl: /DNDEBUG /MD /EHsc
//
// Open-BFME: scalar-deleting destructor for BroadcastStealthUpdate.
// Its unique primary vtable (0x010BCC0C) is installed by the named
// constructor at 0x00289880; slot zero routes through ILT 0x00018156 to
// this 30-byte wrapper.  Retail teardown evidence includes the class's
// complete destructor at 0x00289E50 and nested/base teardown at 0x00289B00.

// Retail's slot calls the compiler's complete-destructor ILT at 0x00018156,
// whose TU-local object symbol remains the generated placeholder spelling.
// The recovered typedef preserves the named class identity at the force site.
class Gen_dtor_00289bb0
{
public:
	virtual ~Gen_dtor_00289bb0();

private:
	friend void forceBroadcastStealthUpdateDeletingDestructor();
};

typedef Gen_dtor_00289bb0 BroadcastStealthUpdate;

void forceBroadcastStealthUpdateDeletingDestructor()
{
	BroadcastStealthUpdate value;
}

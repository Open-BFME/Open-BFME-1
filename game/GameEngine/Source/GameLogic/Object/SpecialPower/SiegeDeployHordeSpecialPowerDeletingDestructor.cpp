// cl: /DNDEBUG /MD /EHsc
//
// Open-BFME: scalar-deleting destructor for SiegeDeployHordeSpecialPower.
// Its unique primary vtable (0x010B71FC) is installed by the named
// constructor at 0x00265B20; slot zero routes through ILT 0x00025612 to
// this 30-byte wrapper.  Retail teardown evidence includes the class's
// complete destructor at 0x00265ED0 and nested/base teardown at 0x00265BF0.

// Retail's slot calls the compiler's complete-destructor ILT at 0x0000DFB7,
// whose TU-local object symbol remains the generated placeholder spelling.
// The recovered typedef preserves the named class identity at the force site.
class Gen_dtor_00265cd0
{
public:
	virtual ~Gen_dtor_00265cd0();

private:
	friend void forceSiegeDeployHordeSpecialPowerDeletingDestructor();
};

typedef Gen_dtor_00265cd0 SiegeDeployHordeSpecialPower;

void forceSiegeDeployHordeSpecialPowerDeletingDestructor()
{
	SiegeDeployHordeSpecialPower value;
}

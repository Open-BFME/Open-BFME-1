// cl: /DNDEBUG /MD /EHsc
// Scalar-deleting destructor at retail 0x0077C830.
// The vtable slot and the matched complete destructor at 0x0077C1F0 establish
// the address-derived S4Base0077C1F0 identity without borrowing a W3D name.

class S4Base0077C1F0
{
public:
	__declspec(noinline) virtual ~S4Base0077C1F0();
};

S4Base0077C1F0::~S4Base0077C1F0()
{
}

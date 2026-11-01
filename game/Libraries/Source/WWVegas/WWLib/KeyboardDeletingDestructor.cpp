// cl: /DNDEBUG /MD /EHsc
//
// Open-BFME5: Keyboard scalar-deleting destructor at retail RVA 0x005A3D80
// (30 bytes). The matched constructor at 0x005A3AC0 and complete destructor
// at 0x005A3B20 both install vtable 0x0110CD60. The matched DirectInputKeyboard
// destructor also calls this base destructor through ILT 0x0002208E, which is
// the same callee used by this wrapper before scalar operator delete.

class Keyboard
{
public:
	virtual ~Keyboard();
};

// The implicit copy constructor (no retail twin) emits the vftable and with
// it ??_G without a second, non-retail copy of the default constructor.
void forceKeyboardDeletingDestructor(const Keyboard &that)
{
	Keyboard value(that);
}

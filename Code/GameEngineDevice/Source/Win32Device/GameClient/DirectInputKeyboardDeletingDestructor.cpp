// cl: /DNDEBUG /MD /EHsc
//
// Open-BFME5: DirectInputKeyboard scalar-deleting destructor at retail RVA
// 0x006BB650 (30 bytes). The exact constructor at 0x006BB410, complete
// destructor at 0x006BB460, and vtable store 0x0111CDCC establish the class;
// Win32DIKeyboard's matched layout places its two owned interfaces at
// +0xE1C/+0xE20 before the base Keyboard destructor.

class DirectInputKeyboard
{
public:
	virtual ~DirectInputKeyboard();
};

void forceDirectInputKeyboardDeletingDestructor()
{
	DirectInputKeyboard value;
}

// cl: /DNDEBUG /MD /EHsc
//
// Open-BFME: public scalar-deleting destructor for InactiveBody.
// The exact constructor at 0x00213BF0 installs dedicated vtable 0x010A8B74;
// slot zero routes through ILT 0x0003648A to this 30-byte wrapper, whose
// complete destructor is reached through ILT 0x0003C867.

class InactiveBody
{
public:
	virtual ~InactiveBody();
};

void forceInactiveBodyDeletingDestructor()
{
	InactiveBody value;
}

// cl: /DNDEBUG /MD /EHsc
//
// Open-BFME: scalar-deleting destructor for ClientUpdateModule. The exact
// constructor at 0x00602ED0 installs vtable 0x01115210; slot zero routes
// through ILT 0x00045A7A to this 30-byte wrapper. The wrapper calls the
// complete destructor through ILT 0x0002EDCA.

class ClientUpdateModule
{
public:
	virtual ~ClientUpdateModule();
};

void forceClientUpdateModuleDeletingDestructor()
{
	ClientUpdateModule value;
}

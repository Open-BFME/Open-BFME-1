// cl: /DNDEBUG /MD /EHsc
//
// Open-BFME: ObjectModule scalar-deleting destructor at retail RVA 0x00113F20
// (30 bytes). The exact constructor at 0x00113C60 installs vtable 0x01089774,
// whose slot zero routes through ILT 0x00002C9D to this wrapper. The many named
// derived module constructors corroborate identity; the wrapper calls the
// already pinned ObjectModule destructor through ILT 0x00047C53.

class ObjectModule
{
public:
	virtual ~ObjectModule();
};

void forceObjectModuleDeletingDestructor()
{
	ObjectModule value;
}

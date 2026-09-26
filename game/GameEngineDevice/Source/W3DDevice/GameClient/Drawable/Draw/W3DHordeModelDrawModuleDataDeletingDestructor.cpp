// cl: /DNDEBUG /MD /EHsc
//
// Open-BFME: W3DHordeModelDrawModuleData scalar-deleting destructor at retail
// RVA 0x00752DD0 (30 bytes). The exact constructor at 0x00751C30 installs
// vtable 0x01122348, whose slot zero routes through ILT 0x000444AE to this
// wrapper. The named module-data factory at 0x006BFC60 corroborates identity;
// the wrapper calls the complete destructor through ILT 0x00026B6B.

class W3DHordeModelDrawModuleData
{
public:
	virtual ~W3DHordeModelDrawModuleData();
};

void forceW3DHordeModelDrawModuleDataDeletingDestructor()
{
	W3DHordeModelDrawModuleData value;
}

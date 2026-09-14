// cl: /DNDEBUG /MD /EHsc
//
// Open-BFME: W3DSupplyDrawModuleData scalar-deleting destructor at retail RVA
// 0x0077DFD0 (30 bytes). The exact constructor at 0x0077DD50 installs vtable
// 0x01125808, whose slot zero routes through ILT 0x00014132 to this wrapper.
// The named module-data factory at 0x006BF3E0 corroborates identity; the
// wrapper calls the complete destructor through ILT 0x00037CB8.

class W3DSupplyDrawModuleData
{
public:
	virtual ~W3DSupplyDrawModuleData();
};

void forceW3DSupplyDrawModuleDataDeletingDestructor()
{
	W3DSupplyDrawModuleData value;
}

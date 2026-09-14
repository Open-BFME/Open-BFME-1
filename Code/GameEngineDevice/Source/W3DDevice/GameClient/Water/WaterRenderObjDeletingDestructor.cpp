// cl: /DNDEBUG /MD /EHsc
//
// Open-BFME: WaterRenderObjClass scalar-deleting destructor at retail RVA
// 0x007A60F0 (30 bytes).  The exact constructor at 0x007A46E0 installs the
// primary vtable at 0x01128148; slot zero is the 5-byte ILT 0x0004614B whose
// first jump reaches this wrapper.  Its complete destructor is the matched
// water-object cleanup body at 0x007A5D10 through ILT 0x00032DCB.

class WaterRenderObjClass
{
public:
	virtual ~WaterRenderObjClass();
};

void forceWaterRenderObjClassDeletingDestructor()
{
	WaterRenderObjClass value;
}

// cl: /DNDEBUG /MD /EHsc
//
// Open-BFME5: DynamicVectorClass<PointerRemapClass::PtrRemapStruct> scalar-
// deleting destructor at retail RVA 0x00930D30.  The matched specialization
// constructor at 0x00930C50 installs vtable 0x0113C644; PointerRemap's reserve
// and remap operations independently establish the element type.

class PointerRemapClass
{
public:
	struct PtrRemapStruct;
};

template <class T>
class DynamicVectorClass
{
public:
	virtual ~DynamicVectorClass();
};

void forcePtrRemapDynamicVectorDeletingDestructor()
{
	DynamicVectorClass<PointerRemapClass::PtrRemapStruct> value;
}

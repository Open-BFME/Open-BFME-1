// cl: /DNDEBUG /MD /EHsc
//
// Open-BFME5: DynamicVectorClass<void *> scalar-deleting destructor at retail
// RVA 0x00907570.  The matched specialization constructor at 0x00907440
// installs vtable 0x0113A3A0, whose Resize/Clear/ID slots have the canonical
// DynamicVectorClass layout.

template <class T>
class DynamicVectorClass
{
public:
	virtual ~DynamicVectorClass();
};

void forceDynamicVectorVoidDeletingDestructor()
{
	DynamicVectorClass<void *> value;
}

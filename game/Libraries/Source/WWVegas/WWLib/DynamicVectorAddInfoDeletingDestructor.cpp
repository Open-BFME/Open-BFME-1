// cl: /DNDEBUG /MD /EHsc
//
// WWLib DynamicVectorClass<MixFileFactoryClass::AddInfoStruct> deleting
// destructor.  Retail's matched specialization constructor at 0x0093E660
// installs vtable 0x0113CE5C, whose slot zero is the body at 0x0093FD60.

class MixFileFactoryClass
{
public:
	struct AddInfoStruct
	{
	};
};

template <class T>
class DynamicVectorClass
{
public:
	virtual ~DynamicVectorClass();
};

template <class T>
__declspec(noinline) DynamicVectorClass<T>::~DynamicVectorClass()
{
}

template class DynamicVectorClass<MixFileFactoryClass::AddInfoStruct>;

void Force_DynamicVector_AddInfo_Deleting_Destructor(
	DynamicVectorClass<MixFileFactoryClass::AddInfoStruct> *vector)
{
	delete vector;
}

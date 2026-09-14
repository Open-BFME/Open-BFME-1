// cl: /DNDEBUG /MD /EHsc
//
// Open-BFME5: DynamicVectorClass<TextureClass *> scalar-deleting destructor
// at retail RVA 0x0093E840.  The matched specialization constructor at
// 0x0093D5E0 installs vtable 0x0113CDDC, and MaterialInfo's vector operations
// establish the TextureClass pointer element type.

class TextureClass;

template <class T>
class DynamicVectorClass
{
public:
	virtual ~DynamicVectorClass();
};

void forceDynamicVectorTextureDeletingDestructor()
{
	DynamicVectorClass<TextureClass *> value;
}

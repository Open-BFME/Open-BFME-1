// cl: /DNDEBUG /MD /EHsc
// DrawableModule scalar-deleting destructor at retail 0x00113F50.
// Its primary vtable is installed by the matched DrawableModule constructor
// at 0x00113DA0; slot zero reaches this wrapper through ILT 0x00005DAD.

class DrawableModule
{
protected:
	__declspec(noinline) virtual ~DrawableModule();
};

DrawableModule::~DrawableModule()
{
}

// cl: /DNDEBUG /MD /EHsc

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2/bmp2d.h
class Bitmap2DObjClass
{
public:
	virtual ~Bitmap2DObjClass();
};

__declspec(noinline) Bitmap2DObjClass::~Bitmap2DObjClass() {}

void Force_Bitmap2DObj_Deleting_Destructor(Bitmap2DObjClass *bitmap)
{
	delete bitmap;
}

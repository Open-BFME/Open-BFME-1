// cl: /DNDEBUG /MD /EHsc

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

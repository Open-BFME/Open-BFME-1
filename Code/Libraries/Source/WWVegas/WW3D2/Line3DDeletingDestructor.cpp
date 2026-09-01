// cl: /DNDEBUG /MD /EHsc

class Line3DClass
{
public:
	virtual ~Line3DClass();
};

__declspec(noinline) Line3DClass::~Line3DClass() {}

void Force_Line3D_Deleting_Destructor(Line3DClass *line)
{
	delete line;
}

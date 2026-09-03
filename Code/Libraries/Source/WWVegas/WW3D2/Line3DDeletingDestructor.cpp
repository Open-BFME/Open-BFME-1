// cl: /DNDEBUG /MD /EHsc

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2/line3d.h
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

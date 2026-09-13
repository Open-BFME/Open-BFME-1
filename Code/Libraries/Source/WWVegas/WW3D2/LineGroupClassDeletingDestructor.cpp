// cl: /DNDEBUG /MD /EHsc

class LineGroupClass
{
public:
	virtual ~LineGroupClass();
};

__declspec(noinline) LineGroupClass::~LineGroupClass() {}

void Force_LineGroupClass_Deleting_Destructor(LineGroupClass *p)
{
	delete p;
}

// cl: /DNDEBUG /MD /EHsc

class StreakLineClass
{
public:
	virtual ~StreakLineClass();
};

__declspec(noinline) StreakLineClass::~StreakLineClass() {}

void Force_StreakLineClass_Deleting_Destructor(StreakLineClass *p)
{
	delete p;
}

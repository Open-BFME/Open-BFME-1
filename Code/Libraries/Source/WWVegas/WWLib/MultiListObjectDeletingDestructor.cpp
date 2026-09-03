// cl: /DNDEBUG /MD /EHsc

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib/multilist.h
class MultiListObjectClass
{
public:
	virtual ~MultiListObjectClass();
};

__declspec(noinline) MultiListObjectClass::~MultiListObjectClass() {}

void Force_MultiListObject_Deleting_Destructor(MultiListObjectClass *object)
{
	delete object;
}

// cl: /DNDEBUG /MD /EHsc

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

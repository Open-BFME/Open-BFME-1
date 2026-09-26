// cl: /DNDEBUG /MD /EHsc

template <class T> class SimpleDynVecClass
{
public:
	virtual ~SimpleDynVecClass();
};

template <class T> __declspec(noinline) SimpleDynVecClass<T>::~SimpleDynVecClass() {}

template class SimpleDynVecClass<unsigned long>;

void Force_SimpleDynVecUnsignedLong_Deleting_Destructor(
	SimpleDynVecClass<unsigned long> *vector)
{
	delete vector;
}

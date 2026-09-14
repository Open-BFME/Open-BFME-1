// cl: /DNDEBUG /MD /EHsc
//
// Open-BFME: SimpleDynVecClass<float> scalar-deleting destructor at retail RVA
// 0x00918AD0 (30 bytes). Its exact copy and sized constructors, matched vector
// method family, and Bitmap2D/Streak ownership establish the specialization.
// The wrapper directly calls the complete destructor at 0x00918500 before
// conditionally invoking operator delete.

template <class T>
class SimpleDynVecClass
{
public:
	virtual ~SimpleDynVecClass();
};

void forceSimpleDynVecFloatDeletingDestructor()
{
	SimpleDynVecClass<float> value;
}

// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB
// stlport
//
// Open-BFME5: AIGroup scalar-deleting destructor at retail 0x00152690
// (30 bytes).  The matched AIGroup constructor at 0x00151BF0 and complete
// virtual destructor at 0x00151D10 establish the class identity; this TU
// emits the compiler-owned deleting wrapper while the complete destructor
// remains in AIGroupDestructor.cpp.

class AIGroup
{
public:
	virtual ~AIGroup();
};

void forceAIGroupDeletingDestructor()
{
	AIGroup value;
}

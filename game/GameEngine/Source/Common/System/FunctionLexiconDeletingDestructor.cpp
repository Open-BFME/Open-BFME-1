// cl: /DNDEBUG /MD /EHsc
//
// Open-BFME: FunctionLexicon scalar-deleting destructor at retail RVA
// 0x00105540 (30 bytes). The exact FunctionLexicon constructor at 0x00105300
// installs vtable 0x01087AC0, whose slot-zero ILT 0x000133E0 routes here.
// The wrapper calls the complete destructor through ILT 0x00028763, which
// reaches the matched 0x00105350 tail destructor before the SubsystemInterface
// base destructor.

class FunctionLexicon
{
public:
	virtual ~FunctionLexicon();
};

void forceFunctionLexiconDeletingDestructor()
{
	FunctionLexicon value;
}

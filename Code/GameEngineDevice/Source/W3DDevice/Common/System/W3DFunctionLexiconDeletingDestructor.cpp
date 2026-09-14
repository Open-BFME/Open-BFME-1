// cl: /DNDEBUG /MD /EHsc
//
// Open-BFME: W3DFunctionLexicon scalar-deleting destructor at retail RVA
// 0x006C0670 (30 bytes). The exact constructor at 0x006C05D0 installs vtable
// 0x0111D740, whose slot zero routes through ILT 0x0002B17F to this wrapper.
// The wrapper calls the complete destructor through ILT 0x0001830E.

class W3DFunctionLexicon
{
public:
	virtual ~W3DFunctionLexicon();
};

void forceW3DFunctionLexiconDeletingDestructor()
{
	W3DFunctionLexicon value;
}

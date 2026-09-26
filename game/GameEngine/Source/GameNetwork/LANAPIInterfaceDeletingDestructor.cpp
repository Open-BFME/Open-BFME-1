// cl: /DNDEBUG /MD /EHsc
// stlport
//
// Open-BFME5: LANAPIInterface scalar-deleting destructor at retail RVA
// 0x00684CA0 (30 bytes). The matched constructor/destructor pair at
// 0x00684CD0/0x00684C90 and base vtable 0x0111AE50 establish the identity;
// LANAPI::~LANAPI restores that table before chaining to SubsystemInterface.

class LANAPIInterface
{
public:
	virtual ~LANAPIInterface();
};

void forceLANAPIInterfaceDeletingDestructor()
{
	LANAPIInterface value;
}

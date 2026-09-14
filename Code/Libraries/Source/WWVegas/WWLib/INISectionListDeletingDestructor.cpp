// cl: /DNDEBUG /MD /EHsc
//
// Open-BFME5: List<INISection *> scalar-deleting destructor at retail RVA
// 0x009E3860.  The matched constructor at 0x009E3440 installs the single-slot
// vtable 0x011454A0, and INIClass::Initialize allocates this exact list type.

struct INISection;

template <class T>
class List
{
public:
	virtual ~List();
};

void forceINISectionListDeletingDestructor()
{
	List<INISection *> value;
}

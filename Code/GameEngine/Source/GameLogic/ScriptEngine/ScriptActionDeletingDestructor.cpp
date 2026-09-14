// cl: /DNDEBUG /MD /EHsc
//
// Open-BFME5: ScriptAction scalar-deleting destructor at retail RVA
// 0x00356010 (30 bytes). Its exact constructors at 0x0034FF60/0x00356040,
// complete destructor at 0x00354330, landed method family, and vtable
// 0x010E84E0 establish the class. The destructor ILT is 0x0003492D.

class ScriptAction
{
public:
	virtual ~ScriptAction();
};

void forceScriptActionDeletingDestructor()
{
	ScriptAction value;
}

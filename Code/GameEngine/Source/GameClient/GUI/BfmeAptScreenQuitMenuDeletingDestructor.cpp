// cl: /DNDEBUG /MD /EHsc
//
// Open-BFME: BfmeAptScreenQuitMenu scalar-deleting destructor at retail RVA
// 0x00569DE0 (30 bytes). The exact QuitMenu.apt constructor at 0x0056A2F0
// installs primary vtable 0x0110A388, whose slot zero reaches this wrapper.
// The wrapper calls the matched complete destructor at 0x00569720 through
// ILT 0x000271F6 before conditionally invoking operator delete.

class BfmeAptScreenQuitMenu
{
public:
	virtual ~BfmeAptScreenQuitMenu();
};

void forceBfmeAptScreenQuitMenuDeletingDestructor()
{
	BfmeAptScreenQuitMenu value;
}

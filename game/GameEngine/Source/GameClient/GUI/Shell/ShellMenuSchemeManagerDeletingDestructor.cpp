// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc
// stlport
//
// Open-BFME: ShellMenuSchemeManager scalar-deleting destructor at retail
// RVA 0x0057F070 (30 bytes).  The matched constructor at 0x005810E0 and
// complete destructor at 0x005813D0 establish this manager's identity; the
// manager owns the ShellMenuScheme list used by Shell's scheme subsystem.

class ShellMenuSchemeManager
{
public:
	~ShellMenuSchemeManager();
};

void forceShellMenuSchemeManagerDeletingDestructor(ShellMenuSchemeManager *value)
{
	delete value;
}

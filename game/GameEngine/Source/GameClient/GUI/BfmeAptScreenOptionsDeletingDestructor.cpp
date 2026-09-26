// cl: /DNDEBUG /MD /EHsc
//
// Open-BFME: BfmeAptScreenOptions scalar-deleting destructor at retail RVA
// 0x0055EF60 (30 bytes). The exact Options.apt constructor at 0x00563370
// installs primary vtable 0x0110912C and secondary vtable 0x01109128; the
// matched complete destructor at 0x0055E320 resets both views and tears down
// the option-screen state.

class BfmeAptScreenOptions
{
public:
	virtual ~BfmeAptScreenOptions();
};

void forceBfmeAptScreenOptionsDeletingDestructor()
{
	BfmeAptScreenOptions value;
}

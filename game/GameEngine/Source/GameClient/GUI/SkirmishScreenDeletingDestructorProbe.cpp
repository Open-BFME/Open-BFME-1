// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc
// Open-BFME5: BfmeAptScreenSkirmish scalar-deleting destructor at retail
// 0x00566AE0 (30 bytes).  The Skirmish options vtable at 0x0110A314 routes
// its primary deleting slot here; the complete destructor at 0x005668C0 and
// the matched Skirmish screen callbacks establish the class identity.

class BfmeAptScreenSkirmish
{
public:
	~BfmeAptScreenSkirmish();
};

void Force_BfmeAptScreenSkirmish_Deleting_Destructor(
	BfmeAptScreenSkirmish *value)
{
	delete value;
}

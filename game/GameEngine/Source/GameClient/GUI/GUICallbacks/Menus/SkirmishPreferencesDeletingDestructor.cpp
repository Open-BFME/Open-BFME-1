// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc
// Open-BFME5: SkirmishPreferences scalar-deleting destructor at retail
// 0x0009FA30 (30 bytes).  The BFME vtable at 0x010806B0 routes slot zero
// here; matched constructor 0x0009F850 and complete destructor 0x0009F7A0,
// plus the authored pinputs/reference/list layout, establish the identity.

class SkirmishPreferences
{
public:
	virtual ~SkirmishPreferences();
};

void Force_SkirmishPreferences_Deleting_Destructor()
{
	SkirmishPreferences value;
}

// cl: /DNDEBUG /MD /EHsc
//
// Open-BFME5: RainOfFireUpdate scalar-deleting destructor at retail RVA
// 0x002A1170 (30 bytes). Its exact constructor at 0x002A0920, complete
// destructor at 0x002A0C90, and unique module factories establish the class.
// The wrapper calls the destructor through ILT 0x0002F162.

class RainOfFireUpdate
{
public:
	virtual ~RainOfFireUpdate();
};

void forceRainOfFireUpdateDeletingDestructor()
{
	RainOfFireUpdate value;
}

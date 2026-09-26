// cl: /DNDEBUG /MD /EHsc
//
// Open-BFME: protected scalar-deleting destructor for the abstract TurretState
// base at retail RVA 0x0018E4F0 (30 bytes). Its exact protected constructor at
// 0x0018D890 installs vtable 0x0109BC18, whose slot zero routes through ILT
// 0x0003BCDC; the wrapper calls the complete destructor via ILT 0x00032BF5.

class TurretState
{
protected:
	virtual ~TurretState();
private:
	friend void forceTurretStateDeletingDestructor();
};

void forceTurretStateDeletingDestructor()
{
	TurretState value;
}

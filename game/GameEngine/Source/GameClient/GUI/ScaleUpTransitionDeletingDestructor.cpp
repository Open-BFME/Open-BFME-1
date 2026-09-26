// cl: /DNDEBUG /MD /EHsc
//
// Open-BFME: protected scalar-deleting destructor for ScaleUpTransition.
// Vtable 0x00D0CAF4 slots name this class (?init@ScaleUpTransition@@UAEXPAVGameWindow@@@Z and ?update@ScaleUpTransition@@UAEXH@Z); its slot zero routes
// through ILT 0x00001D34 to this 30-byte wrapper, whose complete destructor
// route ILT 0x0002581F reaches cleanup body 0x0059EF90.

class ScaleUpTransition
{
protected:
	virtual ~ScaleUpTransition();
private:
	friend void forceScaleUpTransitionDeletingDestructor();
};

void forceScaleUpTransitionDeletingDestructor()
{
	ScaleUpTransition value;
}

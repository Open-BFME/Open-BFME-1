// cl: /DNDEBUG /MD /EHsc
//
// Open-BFME: protected scalar-deleting destructor for FloatUpdate.
// Vtable 0x00CBF454 slots name this class (?getClassMemoryPool@FloatUpdate@@CAPAVMemoryPool@@XZ); its slot zero routes
// through ILT 0x00008314 to this 30-byte wrapper, whose complete destructor
// route ILT 0x00025842 reaches cleanup body 0x00294EA0.

class FloatUpdate
{
protected:
	virtual ~FloatUpdate();
private:
	friend void forceFloatUpdateDeletingDestructor();
};

void forceFloatUpdateDeletingDestructor()
{
	FloatUpdate value;
}

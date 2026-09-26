// cl: /DNDEBUG /MD /EHsc
//
// Open-BFME: protected scalar-deleting destructor for CreateObjectDie.
// Vtable 0x00CB2B2C slots name this class (?getClassMemoryPool@CreateObjectDie@@CAPAVMemoryPool@@XZ); its slot zero routes
// through ILT 0x0000523B to this 30-byte wrapper, whose complete destructor
// route ILT 0x00025B1C reaches cleanup body 0x002545E0.

class CreateObjectDie
{
protected:
	virtual ~CreateObjectDie();
private:
	friend void forceCreateObjectDieDeletingDestructor();
};

void forceCreateObjectDieDeletingDestructor()
{
	CreateObjectDie value;
}

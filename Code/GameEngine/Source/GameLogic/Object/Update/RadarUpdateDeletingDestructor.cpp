// cl: /DNDEBUG /MD /EHsc
//
// Open-BFME: protected scalar-deleting destructor for RadarUpdate.
// Vtable 0x00CC154C slots name this class (?getClassMemoryPool@RadarUpdate@@CAPAVMemoryPool@@XZ); its slot zero routes
// through ILT 0x0002231D to this 30-byte wrapper, whose complete destructor
// route ILT 0x0000B037 reaches cleanup body 0x002A0180.

class RadarUpdate
{
protected:
	virtual ~RadarUpdate();
private:
	friend void forceRadarUpdateDeletingDestructor();
};

void forceRadarUpdateDeletingDestructor()
{
	RadarUpdate value;
}

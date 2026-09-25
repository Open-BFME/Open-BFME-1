// cl: /DNDEBUG /MD /EHsc
//
// The exact constructor at 0x001804B0 passes the AIBackAwayState literal and
// installs vtable 0x0109AE00. Its slot-zero ILT 0x00025E19 identifies the
// retail scalar-deleting wrapper at 0x00185890; the wrapper calls complete-
// destructor ILT 0x0004915C.

class AIBackAwayState
{
protected:
	virtual ~AIBackAwayState();

private:
	friend void forceAIBackAwayStateDeletingDestructor();
};

void forceAIBackAwayStateDeletingDestructor()
{
	AIBackAwayState value;
}

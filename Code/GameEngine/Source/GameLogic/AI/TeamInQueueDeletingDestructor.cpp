// cl: /DNDEBUG /MD /EHsc
//
// Open-BFME: protected scalar-deleting destructor for TeamInQueue.
// Vtable 0x00C96940 slots name this class (?xfer@TeamInQueue@@MAEXPAVXfer@@@Z); its slot zero routes
// through ILT 0x000475AA to this 30-byte wrapper, whose complete destructor
// route ILT 0x0002C1B5 reaches cleanup body 0x00160ED0.

class TeamInQueue
{
protected:
	virtual ~TeamInQueue();
private:
	friend void forceTeamInQueueDeletingDestructor();
};

void forceTeamInQueueDeletingDestructor()
{
	TeamInQueue value;
}

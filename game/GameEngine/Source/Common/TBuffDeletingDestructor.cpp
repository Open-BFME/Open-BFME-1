// cl: /DNDEBUG /MD /EHsc
//
// Open-BFME: protected scalar-deleting destructor for TBuff.
// Vtable 0x00D1E134 slots name this class (?xfer@TBuff@@UAEXPAVXfer@@@Z); its slot zero routes
// through ILT 0x00009444 to this 30-byte wrapper, whose complete destructor
// route ILT 0x0003AF5D reaches cleanup body 0x006DABB0.

class TBuff
{
protected:
	virtual ~TBuff();
private:
	friend void forceTBuffDeletingDestructor();
};

void forceTBuffDeletingDestructor()
{
	TBuff value;
}

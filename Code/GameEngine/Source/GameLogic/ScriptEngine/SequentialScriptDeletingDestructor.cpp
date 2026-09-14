// cl: /DNDEBUG /MD /EHsc
//
// Open-BFME: protected scalar-deleting destructor for SequentialScript.
// Vtable 0x00CE7660 slots name this class (?xfer@SequentialScript@@UAEXPAVXfer@@@Z); its slot zero routes
// through ILT 0x0003C5FB to this 30-byte wrapper, whose complete destructor
// route ILT 0x00033429 reaches cleanup body 0x0033B2A0.

class SequentialScript
{
protected:
	virtual ~SequentialScript();
private:
	friend void forceSequentialScriptDeletingDestructor();
};

void forceSequentialScriptDeletingDestructor()
{
	SequentialScript value;
}

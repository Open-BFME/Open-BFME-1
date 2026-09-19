// cl: /DNDEBUG /MD /EHsc

// Open-BFME: protected scalar-deleting destructor for RefundDie.
// Constructor 0x00255A80 installs vtable 0x00CB331C whose slot zero routes
// through ILT 0x0000DB4D to this 30-byte wrapper, whose complete destructor
// route ILT 0x00001B4F reaches cleanup body 0x00255A40.

class RefundDie
{
protected:
	virtual ~RefundDie();
private:
	friend void forceRefundDieDeletingDestructor();
};

void forceRefundDieDeletingDestructor()
{
	RefundDie value;
}

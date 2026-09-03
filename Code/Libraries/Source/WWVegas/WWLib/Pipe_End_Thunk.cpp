// cl: /DNDEBUG /MD /EHsc

// Slot 2 of Pipe's vtable, between Flush at slot 1 and Put_To at slot 3, and the
// body is a tail-call through the vtable to slot 1. PIPE.H declares it inline as
//     virtual int End(void) {return(Flush());}
// The declaration order below is what puts Flush in slot 1 so the tail call
// lands on it. Defined out of line here rather than in the class body: an inline
// virtual is only emitted when something forces it, and with nothing in this
// translation unit constructing a Pipe the symbol never appeared at all.
// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib/PIPE.H
class Pipe
{
public:
	virtual ~Pipe();
	virtual int Flush();
	virtual int End(void);
	virtual void Put_To(Pipe *pipe);
	virtual int Put(const void *source, int slen);
};

// ?End@Pipe@@UAEHXZ
int Pipe::End(void)
{
	return Flush();
}

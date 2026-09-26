// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB
//
// Open-BFME: scalar-deleting destructor for the BFME game-results queue.
// Its named constructor at 0x00642300 and matching 237-byte destructor at
// 0x00641C60 install/use vtable 0x01119380; slot zero routes through ILT
// 0x0001E3DF to this 30-byte wrapper.  The wrapper's complete-dtor call uses
// ILT 0x00012A2B, which reaches the named queue destructor body.

class Rva00641C60Queue
{
public:
	virtual ~Rva00641C60Queue();

private:
	friend void forceRva00641C60QueueDeletingDestructor();
};

void forceRva00641C60QueueDeletingDestructor()
{
	Rva00641C60Queue value;
}

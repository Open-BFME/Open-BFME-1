// cl: /DNDEBUG /MD /EHsc

// Open-BFME: W3DTreeBuffer scalar-deleting destructor at retail
// 0x007207F0 (30 bytes).  The matched complete destructor at 0x007206E0,
// W3DTreeBuffer's matched BFME methods, and the paired TTreeType lifecycle
// establish the authentic class identity and expanded layout.

class W3DTreeBuffer
{
public:
	~W3DTreeBuffer();
};

void Force_W3DTreeBuffer_Deleting_Destructor(W3DTreeBuffer *value)
{
	delete value;
}

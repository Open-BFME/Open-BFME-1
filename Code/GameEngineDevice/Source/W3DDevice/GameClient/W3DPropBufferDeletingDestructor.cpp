// cl: /DNDEBUG /MD /EHsc

// Open-BFME: W3DPropBuffer scalar-deleting destructor at retail 0x00702FC0
// (30 bytes).  The matched constructor at 0x00702FF0 and complete destructor
// at 0x00702E50, together with the BFME prop/type array implementation,
// establish the authentic class identity.

class W3DPropBuffer
{
public:
	~W3DPropBuffer();
};

void Force_W3DPropBuffer_Deleting_Destructor(W3DPropBuffer *value)
{
	delete value;
}

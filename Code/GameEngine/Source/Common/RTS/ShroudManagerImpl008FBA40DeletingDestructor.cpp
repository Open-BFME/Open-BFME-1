// cl: /DNDEBUG /MD /EHsc

// Open-BFME5: ShroudManagerImpl008FBA40 scalar-deleting destructor at retail
// 0x008F7320 (30 bytes).  The matched constructor at 0x008FB960 and complete
// destructor at 0x008FBA40, together with the named pimpl methods in the
// neighboring ShroudManagerImpl TUs, establish the class identity.

class ShroudManagerImpl008FBA40
{
public:
	~ShroudManagerImpl008FBA40();
};

void Force_ShroudManagerImpl_Deleting_Destructor(
	ShroudManagerImpl008FBA40 *value)
{
	delete value;
}

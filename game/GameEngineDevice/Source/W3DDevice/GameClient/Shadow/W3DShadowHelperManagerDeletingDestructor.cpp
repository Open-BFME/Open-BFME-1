// cl: /DNDEBUG /MD /EHsc
//
// Open-BFME: W3DShadowHelperManager scalar-deleting destructor at retail RVA
// 0x007B74A0 (30 bytes). Its exact constructor at 0x007C10D0, matched complete
// destructor at 0x007C19A0, and W3DShadowManager ownership establish the
// non-virtual helper. The wrapper calls the destructor through ILT 0x00025BDA
// before conditionally invoking operator delete.

class W3DShadowHelperManager
{
public:
	~W3DShadowHelperManager();
};

void forceW3DShadowHelperManagerDelete(W3DShadowHelperManager *manager)
{
	delete manager;
}

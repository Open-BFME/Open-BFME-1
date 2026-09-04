// Candidate for the BFME resource-release body at retail 0x006C6140.
// The object has the two terrain-buffer pointers at the observed offsets;
// the other classes are deliberately opaque so this TU only fixes the call
// and guard shape of this body.

extern void j_0004add1(void);
extern void j_0000a2c2(void);
extern void j_00018403(void);
extern void j_0004a07f(void);

class Gen006C6140Water
{
public:
	void ReleaseResources(void)
	{
		typedef void (Gen006C6140Water::*MemberThunk)(void);
		union {
			void (*function)(void);
			MemberThunk member;
		} thunk;
		thunk.function = j_0004add1;
		(this->*thunk.member)();
	}
};

class Gen006C6140TreeBuffer
{
public:
	void freeTreeBuffers(void)
	{
		typedef void (Gen006C6140TreeBuffer::*MemberThunk)(void);
		union {
			void (*function)(void);
			MemberThunk member;
		} thunk;
		thunk.function = j_0000a2c2;
		(this->*thunk.member)();
	}
};

class Gen006C6140PropBuffer
{
public:
	void freePropBuffers(void)
	{
		typedef void (Gen006C6140PropBuffer::*MemberThunk)(void);
		union {
			void (*function)(void);
			MemberThunk member;
		} thunk;
		thunk.function = j_00018403;
		(this->*thunk.member)();
	}
};

extern Gen006C6140Water *TheWaterRenderObj;

class Gen006C6140Owner
{
public:
	void releaseResources(void);

private:
	char m_before3094[0x3094];
	Gen006C6140PropBuffer *m_propBuffer;
	Gen006C6140TreeBuffer *m_treeBuffer;
};

void Gen006C6140Owner::releaseResources(void)
{
	if (TheWaterRenderObj != 0)
		TheWaterRenderObj->ReleaseResources();
	if (m_treeBuffer != 0)
		m_treeBuffer->freeTreeBuffers();
	if (m_propBuffer != 0)
		m_propBuffer->freePropBuffers();
	j_0004a07f();
}

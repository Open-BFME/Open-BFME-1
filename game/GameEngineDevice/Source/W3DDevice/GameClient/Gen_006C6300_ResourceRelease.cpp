// Candidate for the BFME resource-release body at retail 0x006C6300.

extern void j_000320fb(void);
extern void j_00014dee(void);
extern void j_00006a5f(void);
extern void j_00022822(void);

class Gen006C6300Owner;

class Gen006C6300Water
{
public:
	void release(void)
	{
		typedef void (Gen006C6300Water::*MemberThunk)(void);
		union {
			void (*function)(void);
			MemberThunk member;
		} thunk;
		thunk.function = j_00014dee;
		(this->*thunk.member)();
	}
};

class Gen006C6300Buffer
{
public:
	void release(void)
	{
		typedef void (Gen006C6300Buffer::*MemberThunk)(void);
		union {
			void (*function)(void);
			MemberThunk member;
		} thunk;
		thunk.function = j_00006a5f;
		(this->*thunk.member)();
	}
};

extern Gen006C6300Water *TheWaterRenderObj;

class Gen006C6300Owner
{
public:
	void releaseResources(void);

private:
	char m_before3094[0x3094];
	Gen006C6300Buffer *m_firstBuffer;
	Gen006C6300Buffer *m_secondBuffer;
};

void Gen006C6300Owner::releaseResources(void)
{
	typedef void (Gen006C6300Owner::*MemberThunk)(void);
	union {
		void (*function)(void);
		MemberThunk member;
	} ownerThunk;
	ownerThunk.function = j_000320fb;
	(this->*ownerThunk.member)();

	if (TheWaterRenderObj != 0)
		TheWaterRenderObj->release();
	if (m_firstBuffer != 0)
		m_firstBuffer->release();
	if (m_secondBuffer != 0)
	{
		typedef void (Gen006C6300Buffer::*MemberThunk)(void);
		union {
			void (*function)(void);
			MemberThunk member;
		} tail;
		tail.function = j_00022822;
		(m_secondBuffer->*tail.member)();
	}
}

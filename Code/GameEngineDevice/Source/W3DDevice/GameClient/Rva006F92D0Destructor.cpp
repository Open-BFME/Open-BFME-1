// cl: /DNDEBUG /MD /EHsc
// Destructor of the class already given a constructor+layout at retail
// 0x006F92D0 (Code/GameEngineDevice/Source/W3DDevice/GameClient/Rva006F92D0Constructor.cpp,
// pinned symbol ??1Rva006F92D0@@UAE@XZ per the brief). This TU redeclares its
// own local copy of the layout (file policy: never edit an existing tracked
// file) with two corrections proven by the retail disassembly of this body:
//   - a leading explicit call (ecx = whole object, offset 0) into the same
//     ILT thunk (0x000315F2 -> thunks_023.cpp) the sibling destructor at
//     0x006F7350 also reaches -- a shared cleanup routine, not a sub-object
//     dtor, so it is modeled as an explicit member-pointer-thunk call at the
//     top of the body (same trick as Gen_006C6140_ResourceRelease.cpp).
//   - the two RefPtr members at +0x10/+0x1C are real TextureClass* refs
//     whose destructor calls Release_Ref (the ctor TU's placeholder RefPtr
//     dtor just zeroes the pointer; this body proves the real behavior).
// Destruction order observed: cleanup350() explicit call, then automatic
// member teardown in reverse declaration order (list @ +0x20, texture ref
// @ +0x1C, texture ref @ +0x10), then the base installs its own vtable.

extern void j_000315f2(void);
extern void j_0003cc9f(void);

class TextureClass
{
public:
	void Release_Ref();
};

class BFMETextureRef
{
public:
	TextureClass *m_texture;

	~BFMETextureRef()
	{
		if (m_texture)
			m_texture->Release_Ref();
	}
};

class Rva006F92D0List
{
public:
	~Rva006F92D0List()
	{
		typedef void (Rva006F92D0List::*MemberThunk)(void);
		union {
			void (*function)(void);
			MemberThunk member;
		} thunk;
		thunk.function = j_0003cc9f;
		(this->*thunk.member)();
	}

private:
	void *m_head;
};

class Rva006F92D0Base
{
public:
	virtual ~Rva006F92D0Base() {}
};

class Rva006F92D0 : public Rva006F92D0Base
{
public:
	virtual ~Rva006F92D0();
	virtual void run();
	virtual char *get();
	virtual void render();

private:
	void cleanup350(void)
	{
		typedef void (Rva006F92D0::*MemberThunk)(void);
		union {
			void (*function)(void);
			MemberThunk member;
		} thunk;
		thunk.function = j_000315f2;
		(this->*thunk.member)();
	}

	void *m_04;
	void *m_08;
	void *m_0c;
	BFMETextureRef m_10;
	void *m_14;
	void *m_18;
	BFMETextureRef m_1c;
	Rva006F92D0List m_list;
	void *m_24;
	unsigned char m_28;
	unsigned char m_29;
	unsigned char m_2a;
};

// ??1Rva006F92D0@@UAE@XZ
Rva006F92D0::~Rva006F92D0()
{
	cleanup350();
}

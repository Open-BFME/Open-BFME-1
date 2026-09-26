// cl: /DNDEBUG /MD /EHsc

// Open-BFME5: ten constructors that zero one owned member and hand their
// argument to an initialiser.
//
// The exception frame is the whole tell.  A constructor that only stored a
// zero and made a call would need no EH at all; this one saves `this` into a
// frame slot, sets state 0 across the call and restores fs:[0] afterwards,
// which is MSVC arranging to destroy an ALREADY-CONSTRUCTED member if the
// call throws.  So the class owns a member with a non-trivial destructor
// whose default constructor is inline and does nothing but zero a pointer --
// `mov dword ptr [esi], 0` is that member's constructor, inlined, and not a
// field assignment in the body.
//
// Written as a field assignment (`m_x = 0;` on a plain pointer) the body
// comes out with no frame at all, because nothing would need unwinding.
//
// Each initialiser sits a little before its constructor and is private to it;
// none is shared.  The argument is one dword and the constructor returns
// `this` in eax, as every MSVC constructor does.
//
// IDENTITY IS NOT RECOVERED.  Owner and initialiser are named for the
// constructor's address; the owned member is modelled as one pointer because
// that is all these bodies touch, and its destructor is pinned provisionally
// at the string-release fold.  This file has not verified the unwind funclet
// as the only code that would use it.

class TextureClass
{
public:
	virtual void slot00();
	virtual void slot04();
	virtual void slot08();
	virtual void slot0c();
	virtual void slot10();
	virtual void slot14();
	virtual void slot18();
	virtual void slot1c();
	virtual void slot20();
	virtual void slot24();
	virtual void slot28();
	virtual void slot2c();
	virtual void slot30();
	virtual unsigned int classId();

	unsigned short m_refCount;
	void Release_Ref();
};

class BfmeOwnedMember
{
public:
	BfmeOwnedMember() : m_bfmeData( 0 ) {}
	~BfmeOwnedMember();
	TextureClass *m_bfmeData;
};

class Rva006C07A0
{
public:
	void go();
};

class Gen008FF1B0
{
public:
	Gen008FF1B0( void *source );

private:
	Gen008FF1B0 *bfmeInit( void *source );		// retail 0x008FEC90

	BfmeOwnedMember m_bfmeOwned;
};

class Gen0090BE20
{
public:
	Gen0090BE20( void *source );

private:
	void bfmeInit( void *source );		// retail 0x0090BCF0

	BfmeOwnedMember m_bfmeOwned;
};

class Gen0090DB70
{
public:
	Gen0090DB70( void *source );

private:
	void bfmeInit( void *source );		// retail 0x0090DB10

	BfmeOwnedMember m_bfmeOwned;
};

class Gen00970940
{
public:
	Gen00970940( void *source );

private:
	void bfmeInit( void *source );		// retail 0x00970800

	BfmeOwnedMember m_bfmeOwned;
};

class Gen00970F80
{
public:
	Gen00970F80( void *source );

private:
	void bfmeInit( void *source );		// retail 0x00970E40

	BfmeOwnedMember m_bfmeOwned;
};

class Gen00971360
{
public:
	Gen00971360( void *source );

private:
	void bfmeInit( void *source );		// retail 0x00971220

	BfmeOwnedMember m_bfmeOwned;
};

class Gen00971730
{
public:
	Gen00971730( void *source );

private:
	void bfmeInit( void *source );		// retail 0x00971600

	BfmeOwnedMember m_bfmeOwned;
};

class Gen00971E40
{
public:
	Gen00971E40( void *source );

private:
	void bfmeInit( void *source );		// retail 0x00971C60

	BfmeOwnedMember m_bfmeOwned;
};

class Gen00972540
{
public:
	Gen00972540( void *source );

private:
	void bfmeInit( void *source );		// retail 0x00972340

	BfmeOwnedMember m_bfmeOwned;
};

class Gen00972AA0
{
public:
	Gen00972AA0( void *source );

private:
	void bfmeInit( void *source );		// retail 0x009729D0

	BfmeOwnedMember m_bfmeOwned;
};

// ??0Gen008FF1B0@@QAE@PAX@Z		73B, unwind table 0x00C5AC48
Gen008FF1B0::Gen008FF1B0( void *source )
{
	bfmeInit( source );
}

// ?bfmeInit@Gen008FF1B0@@AAEPAV1@PAX@Z
Gen008FF1B0 *Gen008FF1B0::bfmeInit( void *source )
{
	if ( *(TextureClass **)source != 0 )
	{
		if ( (*(TextureClass **)source)->classId() == 0x50415254u ||
			  (*(TextureClass **)source)->classId() == 0x00424F58u ||
			  (*(TextureClass **)source)->classId() == 0x4D455348u ||
			  (*(TextureClass **)source)->classId() == 0x41474752u ||
			  (*(TextureClass **)source)->classId() == 0x484C4F44u ||
				(*(TextureClass **)source)->classId() == 0x4E554C4Cu ||
				(*(TextureClass **)source)->classId() == 0x6D6F6472u )
			goto addref;
		((Rva006C07A0 *)this)->go();
		return this;
	}
	goto release;

addref:
	if ( *(volatile TextureClass **)source )
		++(*(TextureClass **)source)->m_refCount;

release:
	if ( m_bfmeOwned.m_bfmeData )
		m_bfmeOwned.m_bfmeData->Release_Ref();
	m_bfmeOwned.m_bfmeData = *(TextureClass **)source;
	return this;
}

// ??0Gen0090BE20@@QAE@PAX@Z		73B, unwind table 0x00C5B7E8
Gen0090BE20::Gen0090BE20( void *source )
{
	bfmeInit( source );
}

// ??0Gen0090DB70@@QAE@PAX@Z		73B, unwind table 0x00C5B978
Gen0090DB70::Gen0090DB70( void *source )
{
	bfmeInit( source );
}

// ??0Gen00970940@@QAE@PAX@Z		73B, unwind table 0x00C5EF18
Gen00970940::Gen00970940( void *source )
{
	bfmeInit( source );
}

// ??0Gen00970F80@@QAE@PAX@Z		73B, unwind table 0x00C5F018
Gen00970F80::Gen00970F80( void *source )
{
	bfmeInit( source );
}

// ??0Gen00971360@@QAE@PAX@Z		73B, unwind table 0x00C5F0C8
Gen00971360::Gen00971360( void *source )
{
	bfmeInit( source );
}

// ??0Gen00971730@@QAE@PAX@Z		73B, unwind table 0x00C5F178
Gen00971730::Gen00971730( void *source )
{
	bfmeInit( source );
}

// ??0Gen00971E40@@QAE@PAX@Z		73B, unwind table 0x00C5F298
Gen00971E40::Gen00971E40( void *source )
{
	bfmeInit( source );
}

// ??0Gen00972540@@QAE@PAX@Z		73B, unwind table 0x00C5F3B8
Gen00972540::Gen00972540( void *source )
{
	bfmeInit( source );
}

// ??0Gen00972AA0@@QAE@PAX@Z		73B, unwind table 0x00C5F488
Gen00972AA0::Gen00972AA0( void *source )
{
	bfmeInit( source );
}

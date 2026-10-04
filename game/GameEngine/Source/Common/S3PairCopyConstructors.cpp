// Seven 27-byte bodies with one shape:
//
//     push the argument straight back
//     call a constructor with ecx untouched -- still this
//     copy one word from the argument's +0x08 to ours
//     return this
//
// Returning this is what says constructor rather than assignment, and the
// callee's ILT is pinned as a copy constructor, so these are copy
// constructors of classes whose eight-byte base is that one. The single
// member copied by hand sits right after the base at +0x08.
//
// All seven share the same base and the same thunk, so no new pin is needed;
// only their own names are derived from their addresses.

// Retail calls the base copy constructor through its ILT stub 0x0001AB86
// (body 0x00193760, a gen-tgrid _STL::pair copy constructor), so the call is
// spelled through that stub and the eight base bytes are carried as a member.
extern void j_0001ab86();
class Route00193760 {};

struct Gen_00193bd0
{
	Gen_00193bd0(const Gen_00193bd0 &other);

	char m_bfmeBody[0x08];
	int m_bfme0008;							// +0x08
};

struct Gen_00194fa0
{
	Gen_00194fa0(const Gen_00194fa0 &other);

	char m_bfmeBody[0x08];
	int m_bfme0008;							// +0x08
};

struct Gen_0033a520
{
	Gen_0033a520(const Gen_0033a520 &other);

	char m_bfmeBody[0x08];
	int m_bfme0008;							// +0x08
};

struct Gen_0033a550
{
	Gen_0033a550(const Gen_0033a550 &other);

	char m_bfmeBody[0x08];
	int m_bfme0008;							// +0x08
};

struct Gen_0033a5c0
{
	Gen_0033a5c0(const Gen_0033a5c0 &other);

	char m_bfmeBody[0x08];
	int m_bfme0008;							// +0x08
};

struct Gen_0033ad00
{
	Gen_0033ad00(const Gen_0033ad00 &other);

	char m_bfmeBody[0x08];
	int m_bfme0008;							// +0x08
};

struct Gen_0033ad30
{
	Gen_0033ad30(const Gen_0033ad30 &other);

	char m_bfmeBody[0x08];
	int m_bfme0008;							// +0x08
};

// ??0Gen_00193bd0@@QAE@ABU0@@Z
Gen_00193bd0::Gen_00193bd0(const Gen_00193bd0 &other)
{
	typedef void (Route00193760::*CopyCtor)(const void *);
	union { void (*fn)(); CopyCtor call; } base = { j_0001ab86 };
	(((Route00193760 *)this)->*base.call)(&other);
	m_bfme0008 = other.m_bfme0008;
}

// ??0Gen_00194fa0@@QAE@ABU0@@Z
Gen_00194fa0::Gen_00194fa0(const Gen_00194fa0 &other)
{
	typedef void (Route00193760::*CopyCtor)(const void *);
	union { void (*fn)(); CopyCtor call; } base = { j_0001ab86 };
	(((Route00193760 *)this)->*base.call)(&other);
	m_bfme0008 = other.m_bfme0008;
}

// ??0Gen_0033a520@@QAE@ABU0@@Z
Gen_0033a520::Gen_0033a520(const Gen_0033a520 &other)
{
	typedef void (Route00193760::*CopyCtor)(const void *);
	union { void (*fn)(); CopyCtor call; } base = { j_0001ab86 };
	(((Route00193760 *)this)->*base.call)(&other);
	m_bfme0008 = other.m_bfme0008;
}

// ??0Gen_0033a550@@QAE@ABU0@@Z
Gen_0033a550::Gen_0033a550(const Gen_0033a550 &other)
{
	typedef void (Route00193760::*CopyCtor)(const void *);
	union { void (*fn)(); CopyCtor call; } base = { j_0001ab86 };
	(((Route00193760 *)this)->*base.call)(&other);
	m_bfme0008 = other.m_bfme0008;
}

// ??0Gen_0033a5c0@@QAE@ABU0@@Z
Gen_0033a5c0::Gen_0033a5c0(const Gen_0033a5c0 &other)
{
	typedef void (Route00193760::*CopyCtor)(const void *);
	union { void (*fn)(); CopyCtor call; } base = { j_0001ab86 };
	(((Route00193760 *)this)->*base.call)(&other);
	m_bfme0008 = other.m_bfme0008;
}

// ??0Gen_0033ad00@@QAE@ABU0@@Z
Gen_0033ad00::Gen_0033ad00(const Gen_0033ad00 &other)
{
	typedef void (Route00193760::*CopyCtor)(const void *);
	union { void (*fn)(); CopyCtor call; } base = { j_0001ab86 };
	(((Route00193760 *)this)->*base.call)(&other);
	m_bfme0008 = other.m_bfme0008;
}

// ??0Gen_0033ad30@@QAE@ABU0@@Z
Gen_0033ad30::Gen_0033ad30(const Gen_0033ad30 &other)
{
	typedef void (Route00193760::*CopyCtor)(const void *);
	union { void (*fn)(); CopyCtor call; } base = { j_0001ab86 };
	(((Route00193760 *)this)->*base.call)(&other);
	m_bfme0008 = other.m_bfme0008;
}

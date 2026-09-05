// 90 empty destructors of classes with MORE THAN ONE vftable, or with a
// non-polymorphic base that is not the first thing in the object.  Companion to
// VptrTailJumpDestructors.cpp, which lands the single-vftable case; read its
// header first.  Two shapes:
//
//     mov [ecx],<vftable> / mov [ecx+<N>],<vftable> ... / jmp <base dtor>
//     mov [ecx],<vftable> / add ecx,<N> / jmp <base dtor>
//
// WHAT THE EXTRA STORES ARE.  A destructor re-seats one vptr per polymorphic
// sub-object of the class being destroyed, so the count of stores is the count
// of vftables and their displacements are where those sub-objects sit.  The
// displacements observed are 0, 4, 8, 12, 16 and 32, in ascending order, which
// fixes the sizes between them.  Only ONE destructor is jumped to, so exactly
// one of those sub-objects has a non-trivial destructor and the rest contribute
// a vftable and nothing else -- they are declared here as mixins with one
// virtual function and the right amount of padding, which is all the bytes say
// about them.
//
// WHY `add ecx` IS THE OTHER CASE.  Where retail adjusts `this` before jumping,
// the destroyed class's own vptr is at +0x00 and the base being destroyed sits
// AFTER it -- which is MSVC 7.1 placing the vptr first when the derived class
// declares the first virtual, and means that base is NOT polymorphic and its
// destructor is not virtual.  Whatever the adjustment exceeds four is base
// sub-objects ahead of it, declared here as padding bases of exactly that size.
//
// BASES AND PINS.  As in VptrTailJumpDestructors.cpp, each jump target is an
// address decoded from the retail displacement and gets an address-derived base
// declared here plus a `reverse/symbols.csv` pin -- `??1...@@UAE@XZ` where the
// base is polymorphic, `??1...@@QAE@XZ` where the `add ecx` shape proves it is
// not.  23 distinct targets over 90 bodies; several derived classes share a
// base, which is what a base class is for.
//
// IDENTITY IS NOT RECOVERED.  Every name is derived from an address.

class TailMixinA
{
public:
	virtual void tailMixinA();
};

class TailMixinB
{
public:
	virtual void tailMixinB();
};

class TailMixinWide
{
public:
	virtual void tailMixinWide();

	unsigned int m_pad[ 3 ];
};

class TailPad4
{
public:
	char m_pad[ 4 ];
};

class TailPad8
{
public:
	char m_pad[ 8 ];
};

class TailPad24
{
public:
	char m_pad[ 24 ];
};

class TailPad72
{
public:
	char m_pad[ 72 ];
};

class Rva00008D32MultiBase
{
public:
	virtual ~Rva00008D32MultiBase();
};

class Rva00013994MultiBase
{
public:
	~Rva00013994MultiBase();
};

class Rva00017EEAMultiBase
{
public:
	virtual ~Rva00017EEAMultiBase();

	unsigned int m_pad[ 2 ];
};

class Rva0001AA9BMultiBase
{
public:
	virtual ~Rva0001AA9BMultiBase();

	unsigned int m_pad[ 2 ];
};

class Rva0001C657MultiBase
{
public:
	virtual ~Rva0001C657MultiBase();

	unsigned int m_pad[ 2 ];
};

class Rva0002041EMultiBase
{
public:
	virtual ~Rva0002041EMultiBase();

	unsigned int m_pad[ 2 ];
};

class Rva00020F40MultiBase
{
public:
	virtual ~Rva00020F40MultiBase();

	unsigned int m_pad[ 2 ];
};

class Rva000243A7MultiBase
{
public:
	virtual ~Rva000243A7MultiBase();

	unsigned int m_pad[ 2 ];
};

class Rva0002514EMultiBase
{
public:
	virtual ~Rva0002514EMultiBase();

	unsigned int m_pad[ 2 ];
};

class Rva00026AB2MultiBase
{
public:
	~Rva00026AB2MultiBase();
};

class Rva00026F35MultiBase
{
public:
	~Rva00026F35MultiBase();
};

class Rva00027D81MultiBase
{
public:
	virtual ~Rva00027D81MultiBase();

	unsigned int m_pad[ 1 ];
};

class Rva0002FF31MultiBase
{
public:
	virtual ~Rva0002FF31MultiBase();

	unsigned int m_pad[ 2 ];
};

class Rva0004418EMultiBase
{
public:
	virtual ~Rva0004418EMultiBase();

	unsigned int m_pad[ 2 ];
};

class Rva0004634EMultiBase
{
public:
	virtual ~Rva0004634EMultiBase();

	unsigned int m_pad[ 3 ];
};

class Rva00047C53MultiBase
{
public:
	virtual ~Rva00047C53MultiBase();

	unsigned int m_pad[ 2 ];
};

class Rva000486C1MultiBase
{
public:
	virtual ~Rva000486C1MultiBase();
};

class Rva0004B68CMultiBase
{
public:
	virtual ~Rva0004B68CMultiBase();

	unsigned int m_pad[ 2 ];
};

class Rva00832170MultiBase
{
public:
	~Rva00832170MultiBase();
};

class Rva00887940MultiBase
{
public:
	~Rva00887940MultiBase();
};

class Rva008881D0MultiBase
{
public:
	~Rva008881D0MultiBase();
};

class Rva0091FC10MultiBase
{
public:
	virtual ~Rva0091FC10MultiBase();

	unsigned int m_pad[ 1 ];
};

class Rva0093BE00MultiBase
{
public:
	virtual ~Rva0093BE00MultiBase();

	unsigned int m_pad[ 1 ];
};

class Rva000659E0MultiTailDtor : public Rva00026AB2MultiBase
{
public:
	virtual ~Rva000659E0MultiTailDtor();
};

Rva000659E0MultiTailDtor::~Rva000659E0MultiTailDtor()
{
}

class Rva0008F840MultiTailDtor : public TailPad8, public Rva00887940MultiBase
{
public:
	virtual ~Rva0008F840MultiTailDtor();
};

Rva0008F840MultiTailDtor::~Rva0008F840MultiTailDtor()
{
}

class Rva000B9AD0MultiTailDtor : public Rva00026F35MultiBase
{
public:
	virtual ~Rva000B9AD0MultiTailDtor();
};

Rva000B9AD0MultiTailDtor::~Rva000B9AD0MultiTailDtor()
{
}

class Rva00102E40MultiTailDtor : public TailPad4, public Rva00887940MultiBase
{
public:
	virtual ~Rva00102E40MultiTailDtor();
};

Rva00102E40MultiTailDtor::~Rva00102E40MultiTailDtor()
{
}

class Rva001B2AA0MultiTailDtor : public Rva00047C53MultiBase, public TailMixinA
{
public:
	virtual ~Rva001B2AA0MultiTailDtor();
};

Rva001B2AA0MultiTailDtor::~Rva001B2AA0MultiTailDtor()
{
}

class Rva0020D930MultiTailDtor : public Rva00047C53MultiBase, public TailMixinA
{
public:
	virtual ~Rva0020D930MultiTailDtor();
};

Rva0020D930MultiTailDtor::~Rva0020D930MultiTailDtor()
{
}

class Rva00212880MultiTailDtor : public Rva00020F40MultiBase, public TailMixinA, public TailMixinB
{
public:
	virtual ~Rva00212880MultiTailDtor();
};

Rva00212880MultiTailDtor::~Rva00212880MultiTailDtor()
{
}

class Rva002132B0MultiTailDtor : public Rva00020F40MultiBase, public TailMixinA, public TailMixinB
{
public:
	virtual ~Rva002132B0MultiTailDtor();
};

Rva002132B0MultiTailDtor::~Rva002132B0MultiTailDtor()
{
}

class Rva00214CC0MultiTailDtor : public Rva00017EEAMultiBase, public TailMixinA, public TailMixinB
{
public:
	virtual ~Rva00214CC0MultiTailDtor();
};

Rva00214CC0MultiTailDtor::~Rva00214CC0MultiTailDtor()
{
}

class Rva00217B20MultiTailDtor : public Rva0004B68CMultiBase, public TailMixinA, public TailMixinB
{
public:
	virtual ~Rva00217B20MultiTailDtor();
};

Rva00217B20MultiTailDtor::~Rva00217B20MultiTailDtor()
{
}

class Rva00217D60MultiTailDtor : public Rva0004B68CMultiBase, public TailMixinA, public TailMixinB
{
public:
	virtual ~Rva00217D60MultiTailDtor();
};

Rva00217D60MultiTailDtor::~Rva00217D60MultiTailDtor()
{
}

class Rva00218090MultiTailDtor : public Rva0004B68CMultiBase, public TailMixinA, public TailMixinB
{
public:
	virtual ~Rva00218090MultiTailDtor();
};

Rva00218090MultiTailDtor::~Rva00218090MultiTailDtor()
{
}

class Rva00218670MultiTailDtor : public Rva0004B68CMultiBase, public TailMixinA, public TailMixinB
{
public:
	virtual ~Rva00218670MultiTailDtor();
};

Rva00218670MultiTailDtor::~Rva00218670MultiTailDtor()
{
}

class Rva002188C0MultiTailDtor : public Rva0004B68CMultiBase, public TailMixinA, public TailMixinB
{
public:
	virtual ~Rva002188C0MultiTailDtor();
};

Rva002188C0MultiTailDtor::~Rva002188C0MultiTailDtor()
{
}

class Rva00218C30MultiTailDtor : public Rva0004B68CMultiBase, public TailMixinA, public TailMixinB
{
public:
	virtual ~Rva00218C30MultiTailDtor();
};

Rva00218C30MultiTailDtor::~Rva00218C30MultiTailDtor()
{
}

class Rva0024FC70MultiTailDtor : public Rva0001C657MultiBase, public TailMixinA, public TailMixinB
{
public:
	virtual ~Rva0024FC70MultiTailDtor();
};

Rva0024FC70MultiTailDtor::~Rva0024FC70MultiTailDtor()
{
}

class Rva003A8A50MultiTailDtor : public Rva00887940MultiBase
{
public:
	virtual ~Rva003A8A50MultiTailDtor();
};

Rva003A8A50MultiTailDtor::~Rva003A8A50MultiTailDtor()
{
}

class Rva003B7B80MultiTailDtor : public Rva00887940MultiBase
{
public:
	virtual ~Rva003B7B80MultiTailDtor();
};

Rva003B7B80MultiTailDtor::~Rva003B7B80MultiTailDtor()
{
}

class Rva0043F4B0MultiTailDtor : public Rva008881D0MultiBase
{
public:
	virtual ~Rva0043F4B0MultiTailDtor();
};

Rva0043F4B0MultiTailDtor::~Rva0043F4B0MultiTailDtor()
{
}

class Rva004671F0MultiTailDtor : public Rva008881D0MultiBase
{
public:
	virtual ~Rva004671F0MultiTailDtor();
};

Rva004671F0MultiTailDtor::~Rva004671F0MultiTailDtor()
{
}

class Rva004734B0MultiTailDtor : public TailPad4, public Rva00887940MultiBase
{
public:
	virtual ~Rva004734B0MultiTailDtor();
};

Rva004734B0MultiTailDtor::~Rva004734B0MultiTailDtor()
{
}

class Rva00490550MultiTailDtor : public Rva0004634EMultiBase, public TailMixinA
{
public:
	virtual ~Rva00490550MultiTailDtor();
};

Rva00490550MultiTailDtor::~Rva00490550MultiTailDtor()
{
}

class Rva0059C2F0MultiTailDtor : public Rva0001AA9BMultiBase, public TailMixinA
{
public:
	virtual ~Rva0059C2F0MultiTailDtor();
};

Rva0059C2F0MultiTailDtor::~Rva0059C2F0MultiTailDtor()
{
}

class Rva0059C940MultiTailDtor : public Rva0001AA9BMultiBase, public TailMixinA
{
public:
	virtual ~Rva0059C940MultiTailDtor();
};

Rva0059C940MultiTailDtor::~Rva0059C940MultiTailDtor()
{
}

class Rva0059D400MultiTailDtor : public Rva0001AA9BMultiBase, public TailMixinA
{
public:
	virtual ~Rva0059D400MultiTailDtor();
};

Rva0059D400MultiTailDtor::~Rva0059D400MultiTailDtor()
{
}

class Rva0059DFF0MultiTailDtor : public Rva0001AA9BMultiBase, public TailMixinA
{
public:
	virtual ~Rva0059DFF0MultiTailDtor();
};

Rva0059DFF0MultiTailDtor::~Rva0059DFF0MultiTailDtor()
{
}

class Rva0059E4C0MultiTailDtor : public Rva0001AA9BMultiBase, public TailMixinA
{
public:
	virtual ~Rva0059E4C0MultiTailDtor();
};

Rva0059E4C0MultiTailDtor::~Rva0059E4C0MultiTailDtor()
{
}

class Rva0059E8F0MultiTailDtor : public Rva0001AA9BMultiBase, public TailMixinA
{
public:
	virtual ~Rva0059E8F0MultiTailDtor();
};

Rva0059E8F0MultiTailDtor::~Rva0059E8F0MultiTailDtor()
{
}

class Rva0059EDF0MultiTailDtor : public Rva0001AA9BMultiBase, public TailMixinA
{
public:
	virtual ~Rva0059EDF0MultiTailDtor();
};

Rva0059EDF0MultiTailDtor::~Rva0059EDF0MultiTailDtor()
{
}

class Rva0059EF90MultiTailDtor : public Rva0001AA9BMultiBase, public TailMixinA
{
public:
	virtual ~Rva0059EF90MultiTailDtor();
};

Rva0059EF90MultiTailDtor::~Rva0059EF90MultiTailDtor()
{
}

class Rva0059F340MultiTailDtor : public Rva0001AA9BMultiBase, public TailMixinA
{
public:
	virtual ~Rva0059F340MultiTailDtor();
};

Rva0059F340MultiTailDtor::~Rva0059F340MultiTailDtor()
{
}

class Rva0059F700MultiTailDtor : public Rva0001AA9BMultiBase, public TailMixinA
{
public:
	virtual ~Rva0059F700MultiTailDtor();
};

Rva0059F700MultiTailDtor::~Rva0059F700MultiTailDtor()
{
}

class Rva005A01D0MultiTailDtor : public Rva0001AA9BMultiBase, public TailMixinA
{
public:
	virtual ~Rva005A01D0MultiTailDtor();
};

Rva005A01D0MultiTailDtor::~Rva005A01D0MultiTailDtor()
{
}

class Rva005DD320MultiTailDtor : public Rva00013994MultiBase
{
public:
	virtual ~Rva005DD320MultiTailDtor();
};

Rva005DD320MultiTailDtor::~Rva005DD320MultiTailDtor()
{
}

class Rva006BC560MultiTailDtor : public Rva000486C1MultiBase, public TailMixinA
{
public:
	virtual ~Rva006BC560MultiTailDtor();
};

Rva006BC560MultiTailDtor::~Rva006BC560MultiTailDtor()
{
}

class Rva006BE0C0MultiTailDtor : public Rva00008D32MultiBase, public TailMixinA
{
public:
	virtual ~Rva006BE0C0MultiTailDtor();
};

Rva006BE0C0MultiTailDtor::~Rva006BE0C0MultiTailDtor()
{
}

class Rva006F5BE0MultiTailDtor : public Rva0093BE00MultiBase, public TailMixinA
{
public:
	virtual ~Rva006F5BE0MultiTailDtor();
};

Rva006F5BE0MultiTailDtor::~Rva006F5BE0MultiTailDtor()
{
}

class Rva006FBAD0MultiTailDtor : public Rva00027D81MultiBase, public TailMixinA
{
public:
	virtual ~Rva006FBAD0MultiTailDtor();
};

Rva006FBAD0MultiTailDtor::~Rva006FBAD0MultiTailDtor()
{
}

class Rva00759770MultiTailDtor : public Rva0002FF31MultiBase, public TailMixinA
{
public:
	virtual ~Rva00759770MultiTailDtor();
};

Rva00759770MultiTailDtor::~Rva00759770MultiTailDtor()
{
}

class Rva0077DBE0MultiTailDtor : public Rva0002FF31MultiBase, public TailMixinA
{
public:
	virtual ~Rva0077DBE0MultiTailDtor();
};

Rva0077DBE0MultiTailDtor::~Rva0077DBE0MultiTailDtor()
{
}

class Rva0081D7B0MultiTailDtor : public Rva008881D0MultiBase
{
public:
	virtual ~Rva0081D7B0MultiTailDtor();
};

Rva0081D7B0MultiTailDtor::~Rva0081D7B0MultiTailDtor()
{
}

class Rva0083FB50MultiTailDtor : public TailPad72, public Rva00832170MultiBase
{
public:
	virtual ~Rva0083FB50MultiTailDtor();
};

Rva0083FB50MultiTailDtor::~Rva0083FB50MultiTailDtor()
{
}

class Rva0083FEC0MultiTailDtor : public TailPad24, public Rva00832170MultiBase
{
public:
	virtual ~Rva0083FEC0MultiTailDtor();
};

Rva0083FEC0MultiTailDtor::~Rva0083FEC0MultiTailDtor()
{
}

class Rva0093BE00MultiTailDtor : public Rva0091FC10MultiBase, public TailMixinA
{
public:
	virtual ~Rva0093BE00MultiTailDtor();
};

Rva0093BE00MultiTailDtor::~Rva0093BE00MultiTailDtor()
{
}

class Rva00950FC0MultiTailDtor : public Rva0091FC10MultiBase, public TailMixinA
{
public:
	virtual ~Rva00950FC0MultiTailDtor();
};

Rva00950FC0MultiTailDtor::~Rva00950FC0MultiTailDtor()
{
}

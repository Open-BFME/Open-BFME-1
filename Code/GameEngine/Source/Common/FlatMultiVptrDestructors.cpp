// 17 more empty destructors of the multi-vftable family, with their stores in
// ASCENDING displacement order -- the flat case that
// MultiVptrTailJumpDestructors.cpp lands for the common shapes and this file
// finishes for the rest.  Read that header for the reading; read
// NestedInlineDestructors.cpp for why an order that is NOT ascending means
// something different.
//
// Ascending means every polymorphic sub-object is a direct base of the class
// being destroyed, so the whole layout is one inheritance list and the gaps
// between consecutive displacements are the widths.  The shapes here run from
// five sub-objects to nine, with gaps up to 796 bytes; each width is spelled as
// padding inside the mixin it belongs to, because the bytes witness the spacing
// and nothing about what fills it.
//
// 8 distinct destructors are jumped to across the 17 bodies -- unlike the
// nested family, which shares one -- and each is an address decoded from the
// retail REL32 and pinned in `reverse/symbols.csv` under an address-derived
// name.  The first store of every body is at +0x00 and the second at +0x0C, so
// each base is twelve bytes wide.
//
// IDENTITY IS NOT RECOVERED.  Every name is derived from an address.

class Rva00017EEAFlatBase
{
public:
	virtual ~Rva00017EEAFlatBase();

	unsigned int m_pad[ 2 ];
};

class Rva00019565FlatBase
{
public:
	virtual ~Rva00019565FlatBase();

	unsigned int m_pad[ 2 ];
};

class Rva0001C774FlatBase
{
public:
	virtual ~Rva0001C774FlatBase();

	unsigned int m_pad[ 2 ];
};

class Rva000243A7FlatBase
{
public:
	virtual ~Rva000243A7FlatBase();

	unsigned int m_pad[ 2 ];
};

class Rva00032691FlatBase
{
public:
	virtual ~Rva00032691FlatBase();

	unsigned int m_pad[ 2 ];
};

class Rva00033A37FlatBase
{
public:
	virtual ~Rva00033A37FlatBase();

	unsigned int m_pad[ 2 ];
};

class Rva00039D6AFlatBase
{
public:
	virtual ~Rva00039D6AFlatBase();

	unsigned int m_pad[ 2 ];
};

class Rva0004418EFlatBase
{
public:
	virtual ~Rva0004418EFlatBase();

	unsigned int m_pad[ 2 ];
};

class Rva001F6EE0FlatDtorM0 { public: virtual void anchor(); };
class Rva001F6EE0FlatDtorM1 { public: virtual void anchor(); unsigned int m_pad[ 3 ]; };
class Rva001F6EE0FlatDtorM2 { public: virtual void anchor(); };
class Rva001F6EE0FlatDtorM3 { public: virtual void anchor(); unsigned int m_pad[ 10 ]; };
class Rva001F6EE0FlatDtorM4 { public: virtual void anchor(); };
class Rva001F6EE0FlatDtor : public Rva00032691FlatBase, public Rva001F6EE0FlatDtorM0, public Rva001F6EE0FlatDtorM1, public Rva001F6EE0FlatDtorM2, public Rva001F6EE0FlatDtorM3, public Rva001F6EE0FlatDtorM4
{
public:
	virtual ~Rva001F6EE0FlatDtor();
};

Rva001F6EE0FlatDtor::~Rva001F6EE0FlatDtor()
{
}

class Rva00212D30FlatDtorM0 { public: virtual void anchor(); };
class Rva00212D30FlatDtorM1 { public: virtual void anchor(); unsigned int m_pad[ 51 ]; };
class Rva00212D30FlatDtorM2 { public: virtual void anchor(); };
class Rva00212D30FlatDtor : public Rva00017EEAFlatBase, public Rva00212D30FlatDtorM0, public Rva00212D30FlatDtorM1, public Rva00212D30FlatDtorM2
{
public:
	virtual ~Rva00212D30FlatDtor();
};

Rva00212D30FlatDtor::~Rva00212D30FlatDtor()
{
}

class Rva00220240FlatDtorM0 { public: virtual void anchor(); };
class Rva00220240FlatDtorM1 { public: virtual void anchor(); unsigned int m_pad[ 3 ]; };
class Rva00220240FlatDtorM2 { public: virtual void anchor(); };
class Rva00220240FlatDtorM3 { public: virtual void anchor(); };
class Rva00220240FlatDtorM4 { public: virtual void anchor(); };
class Rva00220240FlatDtorM5 { public: virtual void anchor(); };
class Rva00220240FlatDtorM6 { public: virtual void anchor(); };
class Rva00220240FlatDtorM7 { public: virtual void anchor(); };
class Rva00220240FlatDtor : public Rva00039D6AFlatBase, public Rva00220240FlatDtorM0, public Rva00220240FlatDtorM1, public Rva00220240FlatDtorM2, public Rva00220240FlatDtorM3, public Rva00220240FlatDtorM4, public Rva00220240FlatDtorM5, public Rva00220240FlatDtorM6, public Rva00220240FlatDtorM7
{
public:
	virtual ~Rva00220240FlatDtor();
};

Rva00220240FlatDtor::~Rva00220240FlatDtor()
{
}

class Rva0022EF90FlatDtorM0 { public: virtual void anchor(); };
class Rva0022EF90FlatDtorM1 { public: virtual void anchor(); unsigned int m_pad[ 3 ]; };
class Rva0022EF90FlatDtorM2 { public: virtual void anchor(); };
class Rva0022EF90FlatDtorM3 { public: virtual void anchor(); };
class Rva0022EF90FlatDtorM4 { public: virtual void anchor(); };
class Rva0022EF90FlatDtorM5 { public: virtual void anchor(); };
class Rva0022EF90FlatDtorM6 { public: virtual void anchor(); };
class Rva0022EF90FlatDtorM7 { public: virtual void anchor(); };
class Rva0022EF90FlatDtor : public Rva00039D6AFlatBase, public Rva0022EF90FlatDtorM0, public Rva0022EF90FlatDtorM1, public Rva0022EF90FlatDtorM2, public Rva0022EF90FlatDtorM3, public Rva0022EF90FlatDtorM4, public Rva0022EF90FlatDtorM5, public Rva0022EF90FlatDtorM6, public Rva0022EF90FlatDtorM7
{
public:
	virtual ~Rva0022EF90FlatDtor();
};

Rva0022EF90FlatDtor::~Rva0022EF90FlatDtor()
{
}

class Rva0025A390FlatDtorM0 { public: virtual void anchor(); };
class Rva0025A390FlatDtorM1 { public: virtual void anchor(); unsigned int m_pad[ 3 ]; };
class Rva0025A390FlatDtorM2 { public: virtual void anchor(); };
class Rva0025A390FlatDtorM3 { public: virtual void anchor(); unsigned int m_pad[ 4 ]; };
class Rva0025A390FlatDtorM4 { public: virtual void anchor(); };
class Rva0025A390FlatDtor : public Rva00019565FlatBase, public Rva0025A390FlatDtorM0, public Rva0025A390FlatDtorM1, public Rva0025A390FlatDtorM2, public Rva0025A390FlatDtorM3, public Rva0025A390FlatDtorM4
{
public:
	virtual ~Rva0025A390FlatDtor();
};

Rva0025A390FlatDtor::~Rva0025A390FlatDtor()
{
}

class Rva00265BF0FlatDtorM0 { public: virtual void anchor(); };
class Rva00265BF0FlatDtorM1 { public: virtual void anchor(); unsigned int m_pad[ 3 ]; };
class Rva00265BF0FlatDtorM2 { public: virtual void anchor(); };
class Rva00265BF0FlatDtorM3 { public: virtual void anchor(); };
class Rva00265BF0FlatDtor : public Rva00019565FlatBase, public Rva00265BF0FlatDtorM0, public Rva00265BF0FlatDtorM1, public Rva00265BF0FlatDtorM2, public Rva00265BF0FlatDtorM3
{
public:
	virtual ~Rva00265BF0FlatDtor();
};

Rva00265BF0FlatDtor::~Rva00265BF0FlatDtor()
{
}

class Rva002675F0FlatDtorM0 { public: virtual void anchor(); };
class Rva002675F0FlatDtorM1 { public: virtual void anchor(); unsigned int m_pad[ 3 ]; };
class Rva002675F0FlatDtorM2 { public: virtual void anchor(); unsigned int m_pad[ 49 ]; };
class Rva002675F0FlatDtorM3 { public: virtual void anchor(); };
class Rva002675F0FlatDtor : public Rva000243A7FlatBase, public Rva002675F0FlatDtorM0, public Rva002675F0FlatDtorM1, public Rva002675F0FlatDtorM2, public Rva002675F0FlatDtorM3
{
public:
	virtual ~Rva002675F0FlatDtor();
};

Rva002675F0FlatDtor::~Rva002675F0FlatDtor()
{
}

class Rva0026C550FlatDtorM0 { public: virtual void anchor(); };
class Rva0026C550FlatDtorM1 { public: virtual void anchor(); unsigned int m_pad[ 3 ]; };
class Rva0026C550FlatDtorM2 { public: virtual void anchor(); unsigned int m_pad[ 49 ]; };
class Rva0026C550FlatDtorM3 { public: virtual void anchor(); };
class Rva0026C550FlatDtor : public Rva000243A7FlatBase, public Rva0026C550FlatDtorM0, public Rva0026C550FlatDtorM1, public Rva0026C550FlatDtorM2, public Rva0026C550FlatDtorM3
{
public:
	virtual ~Rva0026C550FlatDtor();
};

Rva0026C550FlatDtor::~Rva0026C550FlatDtor()
{
}

class Rva002B2AB0FlatDtorM0 { public: virtual void anchor(); };
class Rva002B2AB0FlatDtorM1 { public: virtual void anchor(); unsigned int m_pad[ 3 ]; };
class Rva002B2AB0FlatDtorM2 { public: virtual void anchor(); };
class Rva002B2AB0FlatDtorM3 { public: virtual void anchor(); };
class Rva002B2AB0FlatDtor : public Rva00019565FlatBase, public Rva002B2AB0FlatDtorM0, public Rva002B2AB0FlatDtorM1, public Rva002B2AB0FlatDtorM2, public Rva002B2AB0FlatDtorM3
{
public:
	virtual ~Rva002B2AB0FlatDtor();
};

Rva002B2AB0FlatDtor::~Rva002B2AB0FlatDtor()
{
}

class Rva002B2F60FlatDtorM0 { public: virtual void anchor(); };
class Rva002B2F60FlatDtorM1 { public: virtual void anchor(); unsigned int m_pad[ 3 ]; };
class Rva002B2F60FlatDtorM2 { public: virtual void anchor(); };
class Rva002B2F60FlatDtorM3 { public: virtual void anchor(); unsigned int m_pad[ 198 ]; };
class Rva002B2F60FlatDtorM4 { public: virtual void anchor(); };
class Rva002B2F60FlatDtor : public Rva0001C774FlatBase, public Rva002B2F60FlatDtorM0, public Rva002B2F60FlatDtorM1, public Rva002B2F60FlatDtorM2, public Rva002B2F60FlatDtorM3, public Rva002B2F60FlatDtorM4
{
public:
	virtual ~Rva002B2F60FlatDtor();
};

Rva002B2F60FlatDtor::~Rva002B2F60FlatDtor()
{
}

class Rva002B43C0FlatDtorM0 { public: virtual void anchor(); };
class Rva002B43C0FlatDtorM1 { public: virtual void anchor(); unsigned int m_pad[ 3 ]; };
class Rva002B43C0FlatDtorM2 { public: virtual void anchor(); };
class Rva002B43C0FlatDtorM3 { public: virtual void anchor(); unsigned int m_pad[ 198 ]; };
class Rva002B43C0FlatDtorM4 { public: virtual void anchor(); };
class Rva002B43C0FlatDtor : public Rva0001C774FlatBase, public Rva002B43C0FlatDtorM0, public Rva002B43C0FlatDtorM1, public Rva002B43C0FlatDtorM2, public Rva002B43C0FlatDtorM3, public Rva002B43C0FlatDtorM4
{
public:
	virtual ~Rva002B43C0FlatDtor();
};

Rva002B43C0FlatDtor::~Rva002B43C0FlatDtor()
{
}

class Rva002C4190FlatDtorM0 { public: virtual void anchor(); };
class Rva002C4190FlatDtorM1 { public: virtual void anchor(); unsigned int m_pad[ 3 ]; };
class Rva002C4190FlatDtorM2 { public: virtual void anchor(); };
class Rva002C4190FlatDtorM3 { public: virtual void anchor(); unsigned int m_pad[ 198 ]; };
class Rva002C4190FlatDtorM4 { public: virtual void anchor(); };
class Rva002C4190FlatDtor : public Rva0001C774FlatBase, public Rva002C4190FlatDtorM0, public Rva002C4190FlatDtorM1, public Rva002C4190FlatDtorM2, public Rva002C4190FlatDtorM3, public Rva002C4190FlatDtorM4
{
public:
	virtual ~Rva002C4190FlatDtor();
};

Rva002C4190FlatDtor::~Rva002C4190FlatDtor()
{
}

class Rva002C4980FlatDtorM0 { public: virtual void anchor(); };
class Rva002C4980FlatDtorM1 { public: virtual void anchor(); unsigned int m_pad[ 3 ]; };
class Rva002C4980FlatDtorM2 { public: virtual void anchor(); };
class Rva002C4980FlatDtorM3 { public: virtual void anchor(); unsigned int m_pad[ 198 ]; };
class Rva002C4980FlatDtorM4 { public: virtual void anchor(); };
class Rva002C4980FlatDtor : public Rva00033A37FlatBase, public Rva002C4980FlatDtorM0, public Rva002C4980FlatDtorM1, public Rva002C4980FlatDtorM2, public Rva002C4980FlatDtorM3, public Rva002C4980FlatDtorM4
{
public:
	virtual ~Rva002C4980FlatDtor();
};

Rva002C4980FlatDtor::~Rva002C4980FlatDtor()
{
}

class Rva002C5390FlatDtorM0 { public: virtual void anchor(); };
class Rva002C5390FlatDtorM1 { public: virtual void anchor(); unsigned int m_pad[ 3 ]; };
class Rva002C5390FlatDtorM2 { public: virtual void anchor(); };
class Rva002C5390FlatDtorM3 { public: virtual void anchor(); };
class Rva002C5390FlatDtor : public Rva0001C774FlatBase, public Rva002C5390FlatDtorM0, public Rva002C5390FlatDtorM1, public Rva002C5390FlatDtorM2, public Rva002C5390FlatDtorM3
{
public:
	virtual ~Rva002C5390FlatDtor();
};

Rva002C5390FlatDtor::~Rva002C5390FlatDtor()
{
}

class Rva002C7080FlatDtorM0 { public: virtual void anchor(); };
class Rva002C7080FlatDtorM1 { public: virtual void anchor(); unsigned int m_pad[ 3 ]; };
class Rva002C7080FlatDtorM2 { public: virtual void anchor(); };
class Rva002C7080FlatDtorM3 { public: virtual void anchor(); };
class Rva002C7080FlatDtor : public Rva0001C774FlatBase, public Rva002C7080FlatDtorM0, public Rva002C7080FlatDtorM1, public Rva002C7080FlatDtorM2, public Rva002C7080FlatDtorM3
{
public:
	virtual ~Rva002C7080FlatDtor();
};

Rva002C7080FlatDtor::~Rva002C7080FlatDtor()
{
}

class Rva002C7580FlatDtorM0 { public: virtual void anchor(); };
class Rva002C7580FlatDtorM1 { public: virtual void anchor(); unsigned int m_pad[ 3 ]; };
class Rva002C7580FlatDtorM2 { public: virtual void anchor(); };
class Rva002C7580FlatDtorM3 { public: virtual void anchor(); };
class Rva002C7580FlatDtor : public Rva0001C774FlatBase, public Rva002C7580FlatDtorM0, public Rva002C7580FlatDtorM1, public Rva002C7580FlatDtorM2, public Rva002C7580FlatDtorM3
{
public:
	virtual ~Rva002C7580FlatDtor();
};

Rva002C7580FlatDtor::~Rva002C7580FlatDtor()
{
}

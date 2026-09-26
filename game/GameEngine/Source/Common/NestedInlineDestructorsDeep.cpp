// 7 more destructors of the family landed in NestedInlineDestructors.cpp,
// with deeper or wider chains.  Read that header first: the highest
// displacement written first and the rest ascending behind it is an
// intermediate class with an inline destructor, and the run of ascending
// displacements at each position is one level of that chain.
//
// Splitting each body's store order into ascending runs gives the levels
// directly, outermost run first:
//
//     0x10, 0x14, 0x18, 0x0, 0xC  ->  {0x0, 0xC}  {0x10, 0x14, 0x18}
//     0x1C, 0x10, 0x18, 0x0, 0xC  ->  {0x0, 0xC}  {0x10, 0x18}  {0x1C}
//     0x20, 0x24, 0x10, 0x0, 0xC  ->  {0x0, 0xC}  {0x10}  {0x20, 0x24}
//     0x20, 0x28, 0x10, 0x0, 0xC  ->  {0x0, 0xC}  {0x10}  {0x20, 0x28}
//
// Every one tail-jumps to the same 0x00047C53 the shallower bodies do -- the
// seven-byte `mov [ecx],<vftable> / ret` -- so the base is the one already
// pinned for that family, declared again here for this translation unit.
// Mixin widths come from the spacing inside a run; the padding inside each
// intermediate is what carries the next run's first displacement.
//
// IDENTITY IS NOT RECOVERED.  Every name is derived from an address.

class NestedInlineBase
{
public:
	virtual ~NestedInlineBase();

	unsigned int m_pad[ 2 ];
};

class Rva001EE790DeepDtorL0M0 { public: virtual void anchor(); };
class Rva001EE790DeepDtorL0 : public NestedInlineBase, public Rva001EE790DeepDtorL0M0
{
public:
	virtual ~Rva001EE790DeepDtorL0() {}
};

class Rva001EE790DeepDtorL1M0 { public: virtual void anchor(); };
class Rva001EE790DeepDtorL1 : public Rva001EE790DeepDtorL0, public Rva001EE790DeepDtorL1M0
{
public:
	virtual ~Rva001EE790DeepDtorL1() {}

	unsigned int m_pad[ 3 ];
};

class Rva001EE790DeepDtorL2M0 { public: virtual void anchor(); unsigned int m_pad[ 1 ]; };
class Rva001EE790DeepDtorL2M1 { public: virtual void anchor(); };
class Rva001EE790DeepDtor : public Rva001EE790DeepDtorL1, public Rva001EE790DeepDtorL2M0, public Rva001EE790DeepDtorL2M1
{
public:
	virtual ~Rva001EE790DeepDtor();
};

Rva001EE790DeepDtor::~Rva001EE790DeepDtor()
{
}

class Rva001F5F70DeepDtorL0M0 { public: virtual void anchor(); };
class Rva001F5F70DeepDtorL0 : public NestedInlineBase, public Rva001F5F70DeepDtorL0M0
{
public:
	virtual ~Rva001F5F70DeepDtorL0() {}
};

class Rva001F5F70DeepDtorL1M0 { public: virtual void anchor(); };
class Rva001F5F70DeepDtorL1M1 { public: virtual void anchor(); };
class Rva001F5F70DeepDtorL1M2 { public: virtual void anchor(); };
class Rva001F5F70DeepDtor : public Rva001F5F70DeepDtorL0, public Rva001F5F70DeepDtorL1M0, public Rva001F5F70DeepDtorL1M1, public Rva001F5F70DeepDtorL1M2
{
public:
	virtual ~Rva001F5F70DeepDtor();
};

Rva001F5F70DeepDtor::~Rva001F5F70DeepDtor()
{
}

class Rva001FBFC0DeepDtorL0M0 { public: virtual void anchor(); };
class Rva001FBFC0DeepDtorL0 : public NestedInlineBase, public Rva001FBFC0DeepDtorL0M0
{
public:
	virtual ~Rva001FBFC0DeepDtorL0() {}
};

class Rva001FBFC0DeepDtorL1M0 { public: virtual void anchor(); };
class Rva001FBFC0DeepDtorL1 : public Rva001FBFC0DeepDtorL0, public Rva001FBFC0DeepDtorL1M0
{
public:
	virtual ~Rva001FBFC0DeepDtorL1() {}

	unsigned int m_pad[ 3 ];
};

class Rva001FBFC0DeepDtorL2M0 { public: virtual void anchor(); unsigned int m_pad[ 1 ]; };
class Rva001FBFC0DeepDtorL2M1 { public: virtual void anchor(); };
class Rva001FBFC0DeepDtor : public Rva001FBFC0DeepDtorL1, public Rva001FBFC0DeepDtorL2M0, public Rva001FBFC0DeepDtorL2M1
{
public:
	virtual ~Rva001FBFC0DeepDtor();
};

Rva001FBFC0DeepDtor::~Rva001FBFC0DeepDtor()
{
}

class Rva002077A0DeepDtorL0M0 { public: virtual void anchor(); };
class Rva002077A0DeepDtorL0 : public NestedInlineBase, public Rva002077A0DeepDtorL0M0
{
public:
	virtual ~Rva002077A0DeepDtorL0() {}
};

class Rva002077A0DeepDtorL1M0 { public: virtual void anchor(); };
class Rva002077A0DeepDtorL1 : public Rva002077A0DeepDtorL0, public Rva002077A0DeepDtorL1M0
{
public:
	virtual ~Rva002077A0DeepDtorL1() {}

	unsigned int m_pad[ 3 ];
};

class Rva002077A0DeepDtorL2M0 { public: virtual void anchor(); };
class Rva002077A0DeepDtorL2M1 { public: virtual void anchor(); };
class Rva002077A0DeepDtor : public Rva002077A0DeepDtorL1, public Rva002077A0DeepDtorL2M0, public Rva002077A0DeepDtorL2M1
{
public:
	virtual ~Rva002077A0DeepDtor();
};

Rva002077A0DeepDtor::~Rva002077A0DeepDtor()
{
}

class Rva0026A710DeepDtorL0M0 { public: virtual void anchor(); };
class Rva0026A710DeepDtorL0 : public NestedInlineBase, public Rva0026A710DeepDtorL0M0
{
public:
	virtual ~Rva0026A710DeepDtorL0() {}
};

class Rva0026A710DeepDtorL1M0 { public: virtual void anchor(); };
class Rva0026A710DeepDtorL1 : public Rva0026A710DeepDtorL0, public Rva0026A710DeepDtorL1M0
{
public:
	virtual ~Rva0026A710DeepDtorL1() {}

	unsigned int m_pad[ 3 ];
};

class Rva0026A710DeepDtorL2M0 { public: virtual void anchor(); };
class Rva0026A710DeepDtorL2M1 { public: virtual void anchor(); };
class Rva0026A710DeepDtor : public Rva0026A710DeepDtorL1, public Rva0026A710DeepDtorL2M0, public Rva0026A710DeepDtorL2M1
{
public:
	virtual ~Rva0026A710DeepDtor();
};

Rva0026A710DeepDtor::~Rva0026A710DeepDtor()
{
}

class Rva002B2100DeepDtorL0M0 { public: virtual void anchor(); };
class Rva002B2100DeepDtorL0 : public NestedInlineBase, public Rva002B2100DeepDtorL0M0
{
public:
	virtual ~Rva002B2100DeepDtorL0() {}
};

class Rva002B2100DeepDtorL1M0 { public: virtual void anchor(); };
class Rva002B2100DeepDtorL1 : public Rva002B2100DeepDtorL0, public Rva002B2100DeepDtorL1M0
{
public:
	virtual ~Rva002B2100DeepDtorL1() {}

	unsigned int m_pad[ 3 ];
};

class Rva002B2100DeepDtorL2M0 { public: virtual void anchor(); };
class Rva002B2100DeepDtorL2M1 { public: virtual void anchor(); };
class Rva002B2100DeepDtor : public Rva002B2100DeepDtorL1, public Rva002B2100DeepDtorL2M0, public Rva002B2100DeepDtorL2M1
{
public:
	virtual ~Rva002B2100DeepDtor();
};

Rva002B2100DeepDtor::~Rva002B2100DeepDtor()
{
}

class Rva002D44E0DeepDtorL0M0 { public: virtual void anchor(); };
class Rva002D44E0DeepDtorL0 : public NestedInlineBase, public Rva002D44E0DeepDtorL0M0
{
public:
	virtual ~Rva002D44E0DeepDtorL0() {}
};

class Rva002D44E0DeepDtorL1M0 { public: virtual void anchor(); unsigned int m_pad[ 1 ]; };
class Rva002D44E0DeepDtorL1M1 { public: virtual void anchor(); };
class Rva002D44E0DeepDtorL1 : public Rva002D44E0DeepDtorL0, public Rva002D44E0DeepDtorL1M0, public Rva002D44E0DeepDtorL1M1
{
public:
	virtual ~Rva002D44E0DeepDtorL1() {}
};

class Rva002D44E0DeepDtorL2M0 { public: virtual void anchor(); };
class Rva002D44E0DeepDtor : public Rva002D44E0DeepDtorL1, public Rva002D44E0DeepDtorL2M0
{
public:
	virtual ~Rva002D44E0DeepDtor();
};

Rva002D44E0DeepDtor::~Rva002D44E0DeepDtor()
{
}


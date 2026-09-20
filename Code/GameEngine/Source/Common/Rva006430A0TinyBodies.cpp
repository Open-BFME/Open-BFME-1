// Address-derived tiny bodies recovered from carved retail boundaries.
// Owners and method names remain opaque where callers do not prove identity.

class Rva006430A0Self
{
public:
	Rva006430A0Self *self();
};

// ?self@Rva006430A0Self@@QAEPAV1@XZ
Rva006430A0Self *Rva006430A0Self::self()
{
	return this;
}

class Rva006430C0Self
{
public:
	Rva006430C0Self *self();
};

// ?self@Rva006430C0Self@@QAEPAV1@XZ
Rva006430C0Self *Rva006430C0Self::self()
{
	return this;
}

class Rva00643120PtrOffset
{
public:
	char *get() const;

private:
	char *m_base;
};

// ?get@Rva00643120PtrOffset@@QBEPADXZ
char *Rva00643120PtrOffset::get() const
{
	return m_base + 0x10;
}

class Rva006431A0DwordField
{
public:
	unsigned int get() const;

private:
	unsigned int m_value;
};

// ?get@Rva006431A0DwordField@@QBEIXZ
unsigned int Rva006431A0DwordField::get() const
{
	return m_value;
}

class Rva006431B0DwordField
{
public:
	unsigned int get() const;

private:
	unsigned int m_value;
};

// ?get@Rva006431B0DwordField@@QBEIXZ
unsigned int Rva006431B0DwordField::get() const
{
	return m_value;
}

class Rva00643280DwordField
{
public:
	unsigned int get() const;

private:
	unsigned int m_value;
};

// ?get@Rva00643280DwordField@@QBEIXZ
unsigned int Rva00643280DwordField::get() const
{
	return m_value;
}

class Rva00643680DwordField
{
public:
	unsigned int get() const;

private:
	char m_prefix[ 4 ];
	unsigned int m_value;
};

// ?get@Rva00643680DwordField@@QBEIXZ
unsigned int Rva00643680DwordField::get() const
{
	return m_value;
}

class Rva006436B0DwordField
{
public:
	unsigned int get() const;

private:
	char m_prefix[ 4 ];
	unsigned int m_value;
};

// ?get@Rva006436B0DwordField@@QBEIXZ
unsigned int Rva006436B0DwordField::get() const
{
	return m_value;
}

class Rva00643750False
{
public:
	bool get() const;
};

// ?get@Rva00643750False@@QBE_NXZ
bool Rva00643750False::get() const
{
	return false;
}

class Rva00643920False
{
public:
	bool get() const;
};

// ?get@Rva00643920False@@QBE_NXZ
bool Rva00643920False::get() const
{
	return false;
}

class Rva00643930False
{
public:
	bool get() const;
};

// ?get@Rva00643930False@@QBE_NXZ
bool Rva00643930False::get() const
{
	return false;
}

class Rva00643940False
{
public:
	bool get() const;
};

// ?get@Rva00643940False@@QBE_NXZ
bool Rva00643940False::get() const
{
	return false;
}

class Rva00643A10False
{
public:
	bool get() const;
};

// ?get@Rva00643A10False@@QBE_NXZ
bool Rva00643A10False::get() const
{
	return false;
}

class Rva00643A30False
{
public:
	bool get() const;
};

// ?get@Rva00643A30False@@QBE_NXZ
bool Rva00643A30False::get() const
{
	return false;
}

class Rva00643A40False
{
public:
	bool get() const;
};

// ?get@Rva00643A40False@@QBE_NXZ
bool Rva00643A40False::get() const
{
	return false;
}

class Rva00643AC0False
{
public:
	bool get() const;
};

// ?get@Rva00643AC0False@@QBE_NXZ
bool Rva00643AC0False::get() const
{
	return false;
}

class Rva00643B40False
{
public:
	bool get() const;
};

// ?get@Rva00643B40False@@QBE_NXZ
bool Rva00643B40False::get() const
{
	return false;
}

extern const float BfmeZeroRange;

class Rva0073A6C0Thing
{
public:
	float getHeightAboveTerrainOrWater() const;
	bool isAboveTerrainOrWater() const;
};

#pragma comment(linker, "/alternatename:?getHeightAboveTerrainOrWater@Rva0073A6C0Thing@@QBEMXZ=?j_00005948@@YAXXZ")

// ?isAboveTerrainOrWater@Rva0073A6C0Thing@@QBE_NXZ
bool Rva0073A6C0Thing::isAboveTerrainOrWater() const
{
	return getHeightAboveTerrainOrWater() > BfmeZeroRange;
}

class Rva007460C0ByteField
{
public:
	unsigned char get() const;

private:
	char m_prefix[ 0x248D ];
	unsigned char m_value;
};

// ?get@Rva007460C0ByteField@@QBEEXZ
unsigned char Rva007460C0ByteField::get() const
{
	return m_value;
}

class Rva007EA6A0FieldAddress
{
public:
	char *get();
};

// ?get@Rva007EA6A0FieldAddress@@QAEPADXZ
char *Rva007EA6A0FieldAddress::get()
{
	return ((char *)this) + 0x70;
}

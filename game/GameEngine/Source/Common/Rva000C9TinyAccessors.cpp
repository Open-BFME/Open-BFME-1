// cl: /O2 /DNDEBUG /MD
// Address-derived leaf accessors from the carved 0x000C9xxx-0x000CAxxx cluster.

class Rva000C9D60Self { public: Rva000C9D60Self *get(); };
Rva000C9D60Self *Rva000C9D60Self::get() { return this; }

class Rva000C9D90Self { public: Rva000C9D90Self *get(); };
Rva000C9D90Self *Rva000C9D90Self::get() { return this; }

class Rva000C9DC0Self { public: Rva000C9DC0Self *get(); };
Rva000C9DC0Self *Rva000C9DC0Self::get() { return this; }

class Rva000C9E10FirstPointer { public: void *get(); private: void *m_value; };
void *Rva000C9E10FirstPointer::get() { return m_value; }

class Rva000C9E20Self { public: Rva000C9E20Self *get(); };
Rva000C9E20Self *Rva000C9E20Self::get() { return this; }

class Rva000C9E30NoOp { public: void noop(); };
// ?noop@Rva000C9E30NoOp@@QAEXXZ
void Rva000C9E30NoOp::noop() { }

class Rva000C9EC0FirstPointer { public: void *get(); private: void *m_value; };
void *Rva000C9EC0FirstPointer::get() { return m_value; }

class Rva000C9F20FirstPointer { public: void *get(); private: void *m_value; };
void *Rva000C9F20FirstPointer::get() { return m_value; }

class Rva000C9F30FirstPointer { public: void *get(); private: void *m_value; };
void *Rva000C9F30FirstPointer::get() { return m_value; }

class Rva000C9F60FieldAt4 { public: void *get(); private: char m_pad00[4]; void *m_value; };
void *Rva000C9F60FieldAt4::get() { return m_value; }

class Rva000C9FA0Self { public: Rva000C9FA0Self *get(); };
Rva000C9FA0Self *Rva000C9FA0Self::get() { return this; }

class Rva000C9FC0Self { public: Rva000C9FC0Self *get(); };
Rva000C9FC0Self *Rva000C9FC0Self::get() { return this; }

class Rva000C9FE0Self { public: Rva000C9FE0Self *get(); };
Rva000C9FE0Self *Rva000C9FE0Self::get() { return this; }

class Rva000CA000Self { public: Rva000CA000Self *get(); };
Rva000CA000Self *Rva000CA000Self::get() { return this; }

class Rva000CA070Self { public: Rva000CA070Self *get(); };
Rva000CA070Self *Rva000CA070Self::get() { return this; }

class Rva000CA0C0PointerPlus8 { public: void *get(); private: void *m_base; };
void *Rva000CA0C0PointerPlus8::get() { return static_cast<unsigned char *>(m_base) + 8; }

class Rva000CA100PointerPlus8 { public: void *get(); private: void *m_base; };
void *Rva000CA100PointerPlus8::get() { return static_cast<unsigned char *>(m_base) + 8; }

class Rva000CA1B0PointerPlus8 { public: void *get(); private: void *m_base; };
void *Rva000CA1B0PointerPlus8::get() { return static_cast<unsigned char *>(m_base) + 8; }

class Rva000CA230Self { public: Rva000CA230Self *get(); };
Rva000CA230Self *Rva000CA230Self::get() { return this; }

class Rva000CA2D0FirstPointer { public: void *get(); private: void *m_value; };
void *Rva000CA2D0FirstPointer::get() { return m_value; }

class Rva000CA3C0Self { public: Rva000CA3C0Self *get(); };
Rva000CA3C0Self *Rva000CA3C0Self::get() { return this; }

class Rva000CA3E0FieldAt10 { public: void *get(); private: char m_pad00[0x10]; void *m_value; };
void *Rva000CA3E0FieldAt10::get() { return m_value; }

class Rva000CA3F0Self { public: Rva000CA3F0Self *get(); };
Rva000CA3F0Self *Rva000CA3F0Self::get() { return this; }

class Rva000CA5B0FirstPointer { public: void *get(); private: void *m_value; };
void *Rva000CA5B0FirstPointer::get() { return m_value; }

class Rva000CA5C0FirstPointer { public: void *get(); private: void *m_value; };
void *Rva000CA5C0FirstPointer::get() { return m_value; }

class Rva000CA5D0Self { public: Rva000CA5D0Self *get(); };
Rva000CA5D0Self *Rva000CA5D0Self::get() { return this; }

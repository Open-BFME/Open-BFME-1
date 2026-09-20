// cl: /O2 /DNDEBUG /MD
// Address-derived C++ leaves recovered from carved boundaries.

void Rva0007F670()
{
}

class Rva0006C6C0Self { public: void *get(); };
// ?get@Rva0006C6C0Self@@QAEPAXXZ
void *Rva0006C6C0Self::get() { return this; }

class Rva0006C750Self { public: void *get(); };
// ?get@Rva0006C750Self@@QAEPAXXZ
void *Rva0006C750Self::get() { return this; }

class Rva0006CC10NoOp { public: void consume(unsigned int); };
// ?consume@Rva0006CC10NoOp@@QAEXI@Z
void Rva0006CC10NoOp::consume(unsigned int) {}

class Rva0006CD90Self { public: void *get(); };
// ?get@Rva0006CD90Self@@QAEPAXXZ
void *Rva0006CD90Self::get() { return this; }

class Rva0006D590Self { public: void *get(); };
// ?get@Rva0006D590Self@@QAEPAXXZ
void *Rva0006D590Self::get() { return this; }

class Rva0006E6F0Null { public: void *get(); };
// ?get@Rva0006E6F0Null@@QAEPAXXZ
void *Rva0006E6F0Null::get() { return 0; }

class Rva0006E700Null { public: void *get(); };
// ?get@Rva0006E700Null@@QAEPAXXZ
void *Rva0006E700Null::get() { return 0; }

class Rva00075CC0Null { public: void *get(); };
// ?get@Rva00075CC0Null@@QAEPAXXZ
void *Rva00075CC0Null::get() { return 0; }

class Rva00075CD0Null { public: void *get(); };
// ?get@Rva00075CD0Null@@QAEPAXXZ
void *Rva00075CD0Null::get() { return 0; }

class Rva00075D10False { public: unsigned char get(); };
// ?get@Rva00075D10False@@QAEEXZ
unsigned char Rva00075D10False::get() { return 0; }

class Rva00075D20False { public: unsigned char get(); };
// ?get@Rva00075D20False@@QAEEXZ
unsigned char Rva00075D20False::get() { return 0; }

class Rva0007B590Field { public: void *get(); private: char m_pad[0x14]; void *m_value; };
// ?get@Rva0007B590Field@@QAEPAXXZ
void *Rva0007B590Field::get() { return m_value; }

class Rva0007B5E0Field { public: void *get(); private: char m_pad[4]; void *m_value; };
// ?get@Rva0007B5E0Field@@QAEPAXXZ
void *Rva0007B5E0Field::get() { return m_value; }

class Rva0007B680Field { public: void *get(); private: void *m_value; };
// ?get@Rva0007B680Field@@QAEPAXXZ
void *Rva0007B680Field::get() { return m_value; }

class Rva0007B6A0Counter { public: void increment(); private: char m_pad[4]; unsigned int m_value; };
// ?increment@Rva0007B6A0Counter@@QAEXXZ
void Rva0007B6A0Counter::increment() { ++m_value; }

class Rva0007C6F0Field { public: void *get(); private: char m_pad[4]; void *m_value; };
// ?get@Rva0007C6F0Field@@QAEPAXXZ
void *Rva0007C6F0Field::get() { return m_value; }

class Rva0007F430Field { public: void *get(); private: char m_pad[4]; void *m_value; };
// ?get@Rva0007F430Field@@QAEPAXXZ
void *Rva0007F430Field::get() { return m_value; }

class Rva0007F610Self { public: void *get(); };
// ?get@Rva0007F610Self@@QAEPAXXZ
void *Rva0007F610Self::get() { return this; }

class Rva0007F660PointerPlus16 { public: void *get(); private: void *m_value; };
// ?get@Rva0007F660PointerPlus16@@QAEPAXXZ
void *Rva0007F660PointerPlus16::get() { return static_cast<unsigned char *>(m_value) + 0x10; }

class Rva0007F850Field { public: void *get(); private: char m_pad[4]; void *m_value; };
// ?get@Rva0007F850Field@@QAEPAXXZ
void *Rva0007F850Field::get() { return m_value; }

class Rva00083440Self { public: void *get(); };
// ?get@Rva00083440Self@@QAEPAXXZ
void *Rva00083440Self::get() { return this; }

class Rva00083460Field { public: void *get(); private: char m_pad[8]; void *m_value; };
// ?get@Rva00083460Field@@QAEPAXXZ
void *Rva00083460Field::get() { return m_value; }

class Rva00086370Field { public: void *get(); private: char m_pad[4]; void *m_value; };
// ?get@Rva00086370Field@@QAEPAXXZ
void *Rva00086370Field::get() { return m_value; }

class Rva0008A190Field { public: void *get(); private: char m_pad[8]; void *m_value; };
// ?get@Rva0008A190Field@@QAEPAXXZ
void *Rva0008A190Field::get() { return m_value; }

class Rva0008A1A0Field { public: void *get(); private: char m_pad[0x10]; void *m_value; };
// ?get@Rva0008A1A0Field@@QAEPAXXZ
void *Rva0008A1A0Field::get() { return m_value; }

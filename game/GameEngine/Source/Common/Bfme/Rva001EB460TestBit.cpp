// cl: /DNDEBUG /MD /EHsc
class Rva001EB460 { public: bool test(unsigned bit) const; private: unsigned m_unused; unsigned m_flags; };
bool Rva001EB460::test(unsigned bit) const { return (m_flags & (1u << (bit & 31))) != 0; }

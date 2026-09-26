// cl: /O2
// Address-derived preservation for two identical +0x26C dword getters that
// previously carried an incompatible ParticleSystem attached-drawable alias.

#define BFME_DWORD_GETTER(NAME) \
	class NAME { public: unsigned int get(); private: char pad[0x26C]; unsigned int value; }; \
	unsigned int NAME::get() { return value; }

BFME_DWORD_GETTER(Rva0049C960DwordGetter)
BFME_DWORD_GETTER(Rva005886A0DwordGetter)

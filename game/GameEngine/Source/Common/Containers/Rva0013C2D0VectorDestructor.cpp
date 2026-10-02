// RVA 0x0013C2D0: 227-byte STLport vector destructor.
// Evidence: targets/game/reverse/identity_evidence/rva0013c2d0.md
// cl: -GX /Igame/Libraries/Source/WWVegas/WWLib
// stlport

#include <vector>

#include "ascii_string.h"

class Rva0013C2D0Ref
{
public:
	virtual void slot00(int flag);

	int m_count;
    int rva0013c322() { return --m_count; }
    void rva0013c31c() { if (rva0013c322() <= 0) slot00(1); }
};

class Rva0013C2D0Target
{
public:
	char m_lead[0x24];
	Rva0013C2D0Ref m_ref;
};

struct Rva0013AD20View {
    char m_lead[0xc];
    AsciiString m_name;
};

struct Rva0013C2D0Record : public Rva0013AD20View
{
	Rva0013C2D0Target *m_target;

	Rva0013C2D0Record();
	Rva0013C2D0Record(const Rva0013C2D0Record &other);
	Rva0013C2D0Record &operator=(const Rva0013C2D0Record &other);

	~Rva0013C2D0Record()
	{
		if (m_target != 0)
		{
			m_target->m_ref.rva0013c31c();
		}
	}
};

template class _STL::vector<Rva0013C2D0Record>;

// ?method@Rva005FDC70Owner@@QAEXXZ
// partial score=0.95 date=2026-09-16
// Full 293-byte boundary 0x005FDC70..0x005FDD95; no stack arguments.
// Primary slot 1 via ILT 0x37A6 in tables 0x0111282C and 0x01112BAC;
// matched constructors/factories 0x005E8150 and 0x005FE010 install them.
// Complete native handle-copy/cleanup and three-vector update. Canonical
// Coord3D addition plus scalar member multiplies gives 293/293, 14 differing
// operand bytes, 9 aligned relocations. /Op was neutral. Original name unknown.
// cl: /DNDEBUG /MD /EHsc /ICode/Libraries/Source/WWVegas/WWMath

#include "coord3d.h"

inline Coord3D &Coord3D::operator+=(const Coord3DBase &that)
{
    x += that.x;
    y += that.y;
    z += that.z;
    return *this;
}

class BfmeHandleERU;

class BfmeHandleERUOwner
{
public:
	char m_pad[0x98];
	BfmeHandleERU *m_head;
	BfmeHandleERU *m_tail;
};

// This is the proven 12-byte tracked-handle ABI.  Its destructor is the
// existing BfmeHandleERU::~BfmeHandleERU at the shared 0x00013994 ILT.
class BfmeHandleERU
{
public:
	BfmeHandleERU(const BfmeHandleERU &that)
	{
		BfmeHandleERUOwner *owner = that.m_bfmePtrERU;
		m_bfmePtrERU = owner;
		if (m_bfmePtrERU != 0)
		{
			m_previous = m_bfmePtrERU->m_tail;
			m_next = 0;
			m_bfmePtrERU->m_tail = this;
			if (m_previous != 0)
				m_previous->m_next = this;
			else
				m_bfmePtrERU->m_head = this;
		}
		else
		{
			m_next = 0;
			m_previous = 0;
		}
	}

	~BfmeHandleERU() throw();

	BfmeHandleERUOwner *m_bfmePtrERU;
	BfmeHandleERU *m_previous;
	BfmeHandleERU *m_next;
};

class Rva005FDC70Particle
{
public:
	char m_prefix[0x4];
	Coord3D m_at04;
	Coord3D m_at10;
	Coord3D m_at1C;
	char m_pad28[0x24];
	BfmeHandleERU m_handle;
};

class Rva005C34D0Owner
{
public:
	float Rva005C34D0() const;
};

class Rva005C34F0
{
public:
	int dispatch() const;
};

class ParticleSystemZA;
ParticleSystemZA *bfmeNullSystemZA();

class Rva005FDC70Owner
{
public:
	void method();

	char m_pad0[4];
	Rva005FDC70Particle *m_particle;
	char m_pad8[8];
	float m_scale;
};

void Rva005FDC70Owner::method()
{
	BfmeHandleERU handle(m_particle->m_handle);
	Rva005FDC70Particle *particle = m_particle;

	Rva005C34D0Owner *source =
		(Rva005C34D0Owner *)handle.m_bfmePtrERU;
	if (source == 0)
		source = (Rva005C34D0Owner *)bfmeNullSystemZA();
	particle->m_at04.z = source->Rva005C34D0();
	particle->m_at10 += particle->m_at04;
	particle->m_at10.x *= m_scale;
	particle->m_at10.y *= m_scale;
	particle->m_at10.z *= m_scale;

	Rva005C34F0 *dispatch =
		(Rva005C34F0 *)handle.m_bfmePtrERU;
	if (dispatch == 0)
		dispatch = (Rva005C34F0 *)bfmeNullSystemZA();
	float *vector = (float *)dispatch->dispatch();
	if (vector != 0)
	{
		particle->m_at1C.x =
			vector[0] + particle->m_at1C.x + particle->m_at10.x;
		particle->m_at1C.y =
			vector[1] + particle->m_at1C.y + particle->m_at10.y;
		particle->m_at1C.z =
			vector[2] + particle->m_at10.z + particle->m_at1C.z;
	}

	particle->m_at04.x = 0;
	particle->m_at04.y = 0;
	particle->m_at04.z = 0;
}

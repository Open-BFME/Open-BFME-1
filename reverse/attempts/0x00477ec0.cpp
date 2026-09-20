// carved dump placeholder: d_00477ec0
// partial score=0.22 date=2026-09-20
// cl: /DNDEBUG /MD /EHsc
//
// Carved body at retail 0x00477EC0. Reuses the same tree-node layout the
// adjacent Rva00477E20/Rva00477E60 walkers prove (+0x1f8, +0x1fc, +0x200,
// +0x204), plus a status word at +0x08 whose bit 0x100 the code tests
// directly (GameWindow::findNextLeaf at 0x00477FB0 tests the identical bit
// on the identical struct region, WIN_STATUS_TAB_STOP). When the m_200
// ("parent") walk-up is exhausted, this body tail-calls the proven
// Rva00477E60::walk() helper (through the same ILT thunk 0x00021B4D). The
// m_1fc ("next") sub-search reads as the SAME sequence written twice, not a
// factored-out call: every early `return` with no cleanup converges on one
// shared trailing `ret`, which MSVC does naturally for a single function
// with several same-shape exits.

class Rva00477E60
{
public:
	char pad0[8];
	unsigned int m_status;			// +0x08, bit 0x100 tested directly
	char pad1[0x1f8 - 0x0c];
	Rva00477E60 *m_1f8;				// +0x1f8
	Rva00477E60 *m_1fc;				// +0x1fc
	Rva00477E60 *m_200;				// +0x200
	Rva00477E60 *m_204;				// +0x204

	Rva00477E60 *walk();
	Rva00477E60 *findFirstOrWalk();
};

Rva00477E60 *Rva00477E60::findFirstOrWalk()
{
	Rva00477E60 *next = m_1fc;
	if ( next )
	{
		Rva00477E60 *child = next->m_204;
		if ( !child )
			return next;
		if ( next->m_status & 0x100 )
			return next;

		Rva00477E60 *leaf = child;
		for ( ;; )
		{
			while ( leaf->m_1f8 )
				leaf = leaf->m_1f8;

			Rva00477E60 *nextChild = leaf->m_204;
			if ( !nextChild )
				return leaf;
			if ( leaf->m_status & 0x100 )
				return leaf;
			leaf = nextChild;
		}
	}

	Rva00477E60 *p = m_200;
	if ( !p )
		return walk();

	for ( ;; )
	{
		Rva00477E60 *gp = p->m_200;
		if ( !gp )
			return p->walk();

		if ( p->m_1fc )
		{
			Rva00477E60 *next2 = p->m_1fc;
			Rva00477E60 *child = next2->m_204;
			if ( !child )
				return next2;
			if ( next2->m_status & 0x100 )
				return next2;

			Rva00477E60 *leaf = child;
			for ( ;; )
			{
				while ( leaf->m_1f8 )
					leaf = leaf->m_1f8;

				Rva00477E60 *nextChild = leaf->m_204;
				if ( !nextChild )
					return leaf;
				if ( leaf->m_status & 0x100 )
					return leaf;
				leaf = nextChild;
			}
		}

		p = gp;
	}
}

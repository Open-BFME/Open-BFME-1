// ?test@Rva00221960Owner@@QAEHPAURva00221960Point@@0@Z
// partial score=0.45 date=2026-09-10
// cl: /DNDEBUG /MD /EHsc
// Open-BFME5: address-derived. Retail 0x00221960, 159B, HordeGarrisonContain's
// +0x20 secondary-interface vtable slot 43 (+0xac). No header source or
// matched caller names this BFME-only virtual (reverse/re_attempts.log
// 0x00221960).
//
// Two-object coordinate test: reads an info pointer at primary+0x4 (this-0x1c)
// for a zero-checked threshold at +0x138, and the owning Object* at primary+0x8
// (this-0x18, same field HordeGarrisonContain slot 17 at 0x0021F850 reads)
// for its x/y/z at +0x38/+0x3c/+0x40. Compares the owner-vs-candidate-A height
// delta against the threshold, then the dot product of (B-A) and (owner-A) in
// the XY plane against zero.

struct Rva00221960Point
{
	unsigned char m_head[0x38];
	float m_x;   // +0x38
	float m_y;   // +0x3c
	float m_z;   // +0x40
};

struct Rva00221960Info
{
	unsigned char m_head[0x138];
	float m_threshold;   // +0x138
};

class Rva00221960Owner
{
public:
	int test( Rva00221960Point *a, Rva00221960Point *b );
};

// ?d_00221960@@YAXXZ -- address-derived; the real virtual name is not
// recovered.
int Rva00221960Owner::test( Rva00221960Point *a, Rva00221960Point *b )
{
	if ( a != 0 )
	{
		if ( b != 0 )
		{
			char *primary = reinterpret_cast<char *>( this ) - 0x20;
			Rva00221960Info *info = *reinterpret_cast<Rva00221960Info **>( primary + 4 );

			if ( 0.0f < info->m_threshold )
			{
				Rva00221960Point *owner = *reinterpret_cast<Rva00221960Point **>( primary + 8 );
				float dz = a->m_z - owner->m_z;

				if ( info->m_threshold >= dz )
				{
					float dx = b->m_x - a->m_x;
					float dy = b->m_y - a->m_y;
					float dx2 = owner->m_x - a->m_x;
					float dy2 = owner->m_y - a->m_y;
					float dot = dx2 * dx + dy2 * dy;

					if ( dot > 0.0f )
						return 1;
				}
			}
		}
	}

	return 0;
}

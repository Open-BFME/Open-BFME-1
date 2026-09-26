// cl: /DNDEBUG /MD /EHsc

// Open-BFME5: U4Notify::noteOwner, retail 0x004090C0, 103 bytes. The body
// carried only a machine byte-dump row; targets/game/reverse/reloc_names.csv holds the name
// with identity=real.
//
// The same move-to-front Gen_00409040Registry::m at 0x00409040 performs, over a
// different pair of offsets: the two ends live at +0x10 and +0x14 and the two
// cursors at +0x08 and +0x0C, while the owners are threaded through +0x14 and
// +0x18. Nothing happens if the owner is already at either end; otherwise each
// cursor sitting on it is stepped off, it is unlinked from both sides, and it
// goes on the front.
//
// The front is read twice, once to repair the old first owner and once to
// become the new owner's next, because the store in between could have changed
// it as far as the compiler knows.

class U4Owner00604C00
{
public:
	char m_bfmeHead[0x14];
	U4Owner00604C00 *m_bfmeNext;				// +0x14
	U4Owner00604C00 *m_bfmePrev;				// +0x18
};

class U4Notify
{
public:
	void noteOwner(U4Owner00604C00 *owner);

private:
	char m_bfmeHead[0x08];
	U4Owner00604C00 *m_bfmeCursorA;				// +0x08
	U4Owner00604C00 *m_bfmeCursorB;				// +0x0C
	U4Owner00604C00 *m_bfmeFront;				// +0x10
	U4Owner00604C00 *m_bfmeBack;				// +0x14
};

// ?noteOwner@U4Notify@@QAEXPAVU4Owner00604C00@@@Z
void U4Notify::noteOwner(U4Owner00604C00 *owner)
{
	if (m_bfmeFront == owner)
		return;

	if (m_bfmeBack == owner)
		return;

	if (m_bfmeCursorA == owner)
		m_bfmeCursorA = owner->m_bfmeNext;

	if (m_bfmeCursorB == owner)
		m_bfmeCursorB = owner->m_bfmePrev;

	if (owner->m_bfmeNext)
		owner->m_bfmeNext->m_bfmePrev = owner->m_bfmePrev;

	if (owner->m_bfmePrev)
		owner->m_bfmePrev->m_bfmeNext = owner->m_bfmeNext;

	if (m_bfmeFront)
		m_bfmeFront->m_bfmePrev = owner;

	owner->m_bfmeNext = m_bfmeFront;
	m_bfmeFront = owner;
	owner->m_bfmePrev = 0;

	if (!m_bfmeBack)
		m_bfmeBack = owner;
}

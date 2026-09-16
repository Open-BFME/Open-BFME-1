// cl: /DNDEBUG /MD /EHsc
// Retail RVA 0x000D5110. A two-flag permission test: the byte at this+0x295
// and the byte at this+0x294 against bit 0x80 of the argument's byte at +0xC8.
// The bodies either side of it are Player methods, but nothing names this one,
// so the class keeps the address-derived name the ledger already carries.

class BfmeThingEM
{
public:
	unsigned char m_bfmePad000[0xC8];
	unsigned char m_bfmeFlagsEM;
};

class Gen_000D5110
{
public:
	bool bfmeAllows(const BfmeThingEM *thing) const;

	unsigned char m_bfmePad000[0x294];
	unsigned char m_bfmeFlag294;
	unsigned char m_bfmeFlag295;
};

bool Gen_000D5110::bfmeAllows(const BfmeThingEM *thing) const
{
	if (m_bfmeFlag295 == 0 && (thing->m_bfmeFlagsEM & 0x80) != 0)
		return false;

	if (m_bfmeFlag294 != 0 || (thing->m_bfmeFlagsEM & 0x80) != 0)
		return true;

	return false;
}

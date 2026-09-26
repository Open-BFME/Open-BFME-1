// ?predicate@Rva0090E2E0Owner@@QAE_NXZ
// partial score=0.6 date=2026-09-06
// ?predicate@Rva0090E2E0Owner@@QAE_NXZ
// Open-BFME7: split from a merged 126-byte listing -- true size is 0x50 (80)
// bytes; the remainder at 0x0090E330 is an unrelated allocator helper.
class BfmeThingGN
{
public:
	int bfmeAskGN(void);
};

struct Rva0090E2E0Sub
{
	unsigned char m_pad[0x24];
	int m_flag24;
};

struct Rva0090E2E0Item
{
	virtual void v00(); virtual void v01(); virtual void v02(); virtual void v03();
	virtual void v04(); virtual void v05(); virtual void v06(); virtual void v07();
	virtual void v08(); virtual void v09(); virtual bool v10(); virtual void v11();
	virtual void v12(); virtual void v13(); virtual void v14(); virtual void v15();
	virtual bool v16();

	unsigned char m_pad4[0x14 - 4];
	Rva0090E2E0Sub* m_sub;
};

struct Rva0090E2E0Owner
{
	Rva0090E2E0Item* m_item;

	bool predicate();
};

bool Rva0090E2E0Owner::predicate()
{
	Rva0090E2E0Item* obj = m_item;
	if (obj == 0)
		return true;

	if (obj->v16())
		return true;

	if (!obj->v10())
		obj->v11();

	Rva0090E2E0Sub* sub = obj->m_sub;
	if (sub != 0) {
		if (sub->m_flag24 != 1)
			return false;
	}

	if (reinterpret_cast<BfmeThingGN*>(this)->bfmeAskGN() != 1)
		return false;

	return true;
}

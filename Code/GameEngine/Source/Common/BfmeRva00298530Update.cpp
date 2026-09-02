// cl: /DNDEBUG /DWIN32 /MD /D_STLP_USE_STATIC_LIB
#define _STLP_NO_EXCEPTIONS 1
#include <bitset>

typedef int Int;
typedef bool Bool;

template<int NUMBITS>
class BfmeBitFlagsVNI
{
public:
	Bool test(Int bit) const { return m_bits.test(bit); }
	void set(Int bit) { m_bits.set(bit); }

private:
	std::bitset<NUMBITS> m_bits;
};

struct BfmeUpdateDataVNI
{
	char m_pad[0x254];
	int m_mode;
};

class BfmeOwnerVNI
{
public:
	void bfmeApply1VNI();
	void bfmeApply2VNI();
	void bfmeApply3VNI();

	char m_pad[0x128];
	BfmeBitFlagsVNI<32> m_flags;
};

class BfmeUpdateVNI
{
public:
	void bfmePrepVNI();
	void bfmeUpdateVNI();

private:
	char m_pad00[4];
	BfmeUpdateDataVNI *m_data;
	BfmeOwnerVNI *m_owner;
	char m_pad0c[0x24 - 0x0c];
	int m_guard;
};

void BfmeUpdateVNI::bfmeUpdateVNI()
{
	bfmePrepVNI();
	if (m_guard != 0)
		return;

	BfmeOwnerVNI *owner = m_owner;
	switch (m_data->m_mode)
	{
		case 1:
			if (!owner->m_flags.test(8))
			{
				owner->m_flags.set(8);
				owner->bfmeApply1VNI();
			}
			return;

		case 2:
			if (!owner->m_flags.test(9))
			{
				owner->m_flags.set(9);
				owner->bfmeApply2VNI();
			}
			return;

		case 3:
			if (!owner->m_flags.test(10))
			{
				owner->m_flags.set(10);
				owner->bfmeApply3VNI();
			}
			return;

		default: return;
	}
}

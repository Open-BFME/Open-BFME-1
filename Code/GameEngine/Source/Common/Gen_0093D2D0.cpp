// Clean reconstruction of the lookup-and-compare predicate at retail RVA
// 0x0093D2D0.  The owning type and imported lookup identity are not recovered;
// the field offsets and comparison order are directly byte-verified.

typedef void *(__cdecl *Gen_0093D2D0_Lookup)(void *, void *);
extern Gen_0093D2D0_Lookup g_lookup;

class Gen_0093D2D0
{
public:
	bool process(void *key, float value, unsigned char flag, int id);

private:
	unsigned char m_pad[0x3C];
	float m_value;
	int m_id;
	void *m_table;
	unsigned char m_gap[0x460 - 0x48];
	unsigned char m_flag;
};

bool Gen_0093D2D0::process(void *key, float value, unsigned char flag, int id)
{
	if (g_lookup(m_table, key) == 0 && value == m_value &&
		id == m_id && flag == m_flag)
		return true;
	return false;
}

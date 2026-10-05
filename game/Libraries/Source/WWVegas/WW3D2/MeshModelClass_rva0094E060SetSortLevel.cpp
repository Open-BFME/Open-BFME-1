// ?rva0094E060SetSortLevel@MeshModelClass@@QAEX_N@Z
// Address-derived: thiscall(this, bool flag) on MeshModelClass. Picks an
// override level (AlternateMatDesc) over the base level (DefMatDesc) only when flag requests
// it and the override is non-zero; if that differs from the cached level
// (CurMatDesc) it updates the cache, optionally recomputes static sort levels, and
// tail-calls TheDX8MeshRenderer->Invalidate(false).
class DX8MeshRendererClass
{
public:
	void Invalidate(bool clear);
};

extern DX8MeshRendererClass *TheDX8MeshRenderer;

class WW3D
{
public:
	static bool Is_Munge_Sort_On_Load_Enabled() { return MungeSortOnLoad; }

private:
	static bool MungeSortOnLoad;
};

class MeshModelClass
{
public:
	unsigned char m_pad0[0x18];
	unsigned char m_18flags;
	unsigned char m_pad1[0x94 - 0x19];
	int DefMatDesc;
	int AlternateMatDesc;
	int CurMatDesc;

	void rva0094E060SetSortLevel(bool flag);

protected:
	void compute_static_sort_levels();
};

void MeshModelClass::rva0094E060SetSortLevel(bool flag)
{
	int level;
	if (flag == 1)
	{
		level = AlternateMatDesc;
		if (level == 0)
			level = DefMatDesc;
	}
	else
	{
		level = DefMatDesc;
	}

	if (CurMatDesc != level)
	{
		CurMatDesc = level;
		if ((m_18flags & 0x10) && WW3D::Is_Munge_Sort_On_Load_Enabled())
			compute_static_sort_levels();

		TheDX8MeshRenderer->Invalidate(false);
	}
}

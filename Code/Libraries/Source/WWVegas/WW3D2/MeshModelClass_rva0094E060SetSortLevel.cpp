// ?rva0094E060SetSortLevel@MeshModelClass@@QAEX_N@Z
// Address-derived: thiscall(this, bool flag) on MeshModelClass. Picks an
// override level (m_98) over the base level (m_94) only when flag requests
// it and the override is non-zero; if that differs from the cached level
// (m_9c) it updates the cache, optionally recomputes static sort levels, and
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
	static bool IsMungeSortOnLoadEnabled;
};

class MeshModelClass
{
public:
	unsigned char m_pad0[0x18];
	unsigned char m_18flags;
	unsigned char m_pad1[0x94 - 0x19];
	int m_94;
	int m_98;
	int m_9c;

	void rva0094E060SetSortLevel(bool flag);

protected:
	void compute_static_sort_levels();
};

void MeshModelClass::rva0094E060SetSortLevel(bool flag)
{
	int level;
	if (flag == 1)
	{
		level = m_98;
		if (level == 0)
			level = m_94;
	}
	else
	{
		level = m_94;
	}

	if (m_9c != level)
	{
		m_9c = level;
		if ((m_18flags & 0x10) && WW3D::IsMungeSortOnLoadEnabled)
			compute_static_sort_levels();

		TheDX8MeshRenderer->Invalidate(false);
	}
}

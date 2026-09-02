// cl: /DNDEBUG /MD /EHsc

// Retail 0x003F68F0: attach a child at this+4 and write this into the child's
// +0xA4 slot, or detach by storing 0 and clearing the pointer. The +0xA4 store
// is the already-matched Rva001A1DE0Owner::setValue.

class Rva001A1DE0Owner
{
public:
	void setValue(int value);
};

class Gen_003F68F0
{
public:
	void bfmeAttach(Rva001A1DE0Owner *child);

private:
	void *m_unused;
	Rva001A1DE0Owner *m_child;
};

void Gen_003F68F0::bfmeAttach(Rva001A1DE0Owner *child)
{
	if (child)
	{
		if (!m_child)
		{
			m_child = child;
			child->setValue((int)this);
		}
	}
	else
	{
		if (m_child)
			m_child->setValue(0);
		m_child = 0;
	}
}

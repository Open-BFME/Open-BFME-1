// cl: /DNDEBUG /MD
// Retail 0x007ADB80: release references in eighteen chains and one auxiliary chain.

class Rva007ADB80Ref
{
public:
	virtual void deleteThis();
	int m_refCount;
};

struct Rva007ADB80MainNode
{
	char m_padding[0x10];
	Rva007ADB80MainNode *m_next;
	Rva007ADB80Ref *m_reference;
};

struct Rva007ADB80AuxNode
{
	char m_padding[0x0C];
	Rva007ADB80AuxNode *m_next;
	Rva007ADB80Ref *m_reference;
};

class Rva007ADB80Owner
{
private:
	char m_padding[0x9000];
	Rva007ADB80MainNode *m_chains[18];
	char m_padding2[0x1D388];
	Rva007ADB80AuxNode *m_auxiliary;

public:
	void releaseReferences();
};

void Rva007ADB80Owner::releaseReferences()
{
	for ( int i = 0; i < 18; ++i )
	{
		Rva007ADB80MainNode *node = m_chains[i];
		while ( node != 0 )
		{
			Rva007ADB80Ref *reference = node->m_reference;
			if ( reference != 0 )
			{
				if ( --reference->m_refCount == 0 )
					reference->deleteThis();
				node->m_reference = 0;
			}
			node = node->m_next;
		}
	}

	Rva007ADB80AuxNode *node = m_auxiliary;
	while ( node != 0 )
	{
		Rva007ADB80Ref *reference = node->m_reference;
		if ( reference != 0 )
		{
			if ( --reference->m_refCount == 0 )
				reference->deleteThis();
			node->m_reference = 0;
		}
		node = node->m_next;
	}
}

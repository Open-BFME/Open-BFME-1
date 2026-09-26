// Open-BFME5: clean C++ conversion of the state reset at 0x003F7380.

extern int TheMixFileInfoPool;

class MixFileInfoBuffer
{
public:
	void releaseInto(void *pool);
};

struct Rva003F7380Node
{
	unsigned char m_padding[0x20];
	int m_value;
	unsigned int m_nodeFlags;
	unsigned char m_tailPadding[8];
	void *m_link;
};

struct Rva003F7380Argument
{
	unsigned char m_padding[0x74];
	int m_value;
};

class Rva003F7380State
{
public:
	void resetIfMatching(const Rva003F7380Argument *argument);
	void finishReset();

private:
	Rva003F7380Node *m_node;
	unsigned char m_padding[8];
	unsigned int m_flags;
};

void Rva003F7380State::resetIfMatching(const Rva003F7380Argument *argument)
{
	unsigned int flags = m_flags;
	if ((flags & 7) == 3) {
		m_flags = flags & ~7u;
	}

	Rva003F7380Node *node = m_node;
	if (node != 0 && node->m_value == argument->m_value) {
		m_flags &= ~7u;
		node->m_value = 0;
		finishReset();
	}
}

void Rva003F7380State::finishReset()
{
	unsigned int flags = m_flags;
	if ((flags & 7) != 4 && (flags & 0x38) == 0 &&
		(flags & 0x80000) == 0 && m_node != 0 &&
		m_node->m_link == 0 && (m_node->m_nodeFlags & 0x18) == 0) {
		reinterpret_cast<MixFileInfoBuffer *>(m_node)->releaseInto(&TheMixFileInfoPool);
		m_node = 0;
	}
}

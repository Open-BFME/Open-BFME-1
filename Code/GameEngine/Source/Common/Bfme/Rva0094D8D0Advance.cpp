// Structural recovery of the two-output iterator body at 0x0094D8D0.

void d_0094d450(void);

class TextureBaseClass
{
public:
	unsigned char m_prefix[4];
	unsigned short m_refs;
	void Release_Ref(void);
};

struct Rva0094D8D0Node
{
	unsigned char m_prefix[0x10];
	TextureBaseClass *m_resource;
	unsigned char m_record[0x10];
};

struct Rva0094D8D0Handle
{
	TextureBaseClass *m_value;
};

struct Rva0094D8D0Record
{
	unsigned char m_bytes[0x10];
};

class Rva0094D8D0
{
public:
	bool advance(Rva0094D8D0Handle *handle, Rva0094D8D0Record *record);

private:
	unsigned char m_prefix[8];
	Rva0094D8D0Node *m_end;
	unsigned char m_gap[8];
	Rva0094D8D0Node *m_current;
	TextureBaseClass *m_guard;
	unsigned char m_refresh;
};

bool Rva0094D8D0::advance(Rva0094D8D0Handle *handle, Rva0094D8D0Record *record)
{
	if (m_refresh != 0)
		d_0094d450();
	register Rva0094D8D0Node *current = m_current;
	if (current == m_end)
		return false;
	if (m_guard == 0)
		return false;

	if (current->m_resource != 0)
		++current->m_resource->m_refs;

	TextureBaseClass *old = handle->m_value;
	if (old != 0)
		old->Release_Ref();
	handle->m_value = current->m_resource;

	*record = *(Rva0094D8D0Record *)((unsigned char *)m_current + 0x14);
	return true;
}

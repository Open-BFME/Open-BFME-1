// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc

struct Rva0061E980Inner
{
	char m_pad[4];
	int m_kind;
	char m_pad2[0x28];
	int m_id;
	unsigned short m_sub;
};

class Rva0061E980Obj
{
public:
	bool matches() const;

private:
	char m_pad[0xC];
	unsigned char m_on;
	char m_pad2[7];
	Rva0061E980Inner *m_inner;
	char m_pad3[0x1C];
	int m_id;
	unsigned short m_sub;
};

bool Rva0061E980Obj::matches() const
{
	if (!m_on)
		return false;
	Rva0061E980Inner *inner = m_inner;
	return inner->m_kind == 5 && inner->m_id == m_id && inner->m_sub == m_sub;
}

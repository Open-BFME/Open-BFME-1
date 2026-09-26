extern const char g_Rva0107301CEmptyString[];

class BfmeStrEBC
{
public:
	BfmeStrEBC(const char *text);
	~BfmeStrEBC();

	void *m_bfmeDataEBC;
};

class LocalFileSystem
{
public:
	virtual void bfmeSlot00EBC();
	virtual void bfmeSlot01EBC();
	virtual void bfmeSlot02EBC();
	virtual void bfmeSlot03EBC();
	virtual void bfmeSlot04EBC();
	virtual void bfmeListEBC(const BfmeStrEBC &dir, const BfmeStrEBC &a,
		const BfmeStrEBC &b, void *out, int flag);
};

class ArchiveFileSystem
{
public:
	void bfmeListEBC(const BfmeStrEBC &dir, const BfmeStrEBC &a,
		const BfmeStrEBC &b, void *out, int flag);
};

extern LocalFileSystem *TheLocalFileSystem;
extern ArchiveFileSystem *TheArchiveFileSystem;

void __stdcall bfmeListAllEBC(const BfmeStrEBC &a, const BfmeStrEBC &b, void *out, int flag)
{
	{
		BfmeStrEBC dir(g_Rva0107301CEmptyString);

		TheLocalFileSystem->bfmeListEBC(dir, a, b, out, flag);
	}

	{
		BfmeStrEBC dir2(g_Rva0107301CEmptyString);

		TheArchiveFileSystem->bfmeListEBC(dir2, a, b, out, flag);
	}
}

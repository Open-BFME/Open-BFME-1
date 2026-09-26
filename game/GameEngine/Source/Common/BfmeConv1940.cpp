extern "C" char g_bfmeSideNameA1294[];
extern "C" char g_bfmeSideNameB1294[];
extern "C" char g_bfmeSideNameC1294[];
extern "C" char g_bfmeSideNameD1294[];

extern const char g_Rva0107301CEmptyString[];

class BFMERetailAsciiString
{
public:
	BFMERetailAsciiString(const char *text);

	~BFMERetailAsciiString() { releaseBuffer(); }

	void *m_bfmeBufDL;

private:
	void releaseBuffer();
};

extern "C" void *__cdecl bfmeFindDL(void *ctx, const BFMERetailAsciiString &name);

void *__cdecl bfmeLookupDL(void *ctx, int side)
{
	const char *name;

	switch (side)
	{
	case 0:
		name = g_bfmeSideNameB1294;
		break;

	case 1:
		name = g_bfmeSideNameA1294;
		break;

	case 2:
		name = g_bfmeSideNameC1294;
		break;

	case 3:
		name = g_bfmeSideNameD1294;
		break;

	default:
		name = g_Rva0107301CEmptyString;
		break;
	}

	{
		const BFMERetailAsciiString &text = BFMERetailAsciiString(name);

		return bfmeFindDL(ctx, text);
	}
}

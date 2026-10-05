
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
		name = "Rohan";
		break;

	case 1:
		name = "Gondor";
		break;

	case 2:
		name = "Mordor";
		break;

	case 3:
		name = "Isengard";
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

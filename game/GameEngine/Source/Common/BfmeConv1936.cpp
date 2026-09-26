class BfmeImageDE;

class BFMERetailAsciiString
{
public:
	BFMERetailAsciiString(const char *text);

	~BFMERetailAsciiString() { releaseBufferDE(); }

	void releaseBufferDE();

	void *m_bfmeBufDE;
};

class MappedImageCollection
{
public:
	BfmeImageDE *bfmeFindDE(const BFMERetailAsciiString &name);
};

extern MappedImageCollection *TheMappedImageCollection;

BfmeImageDE *__stdcall bfmeFindImageDE(const char *name)
{
	if (TheMappedImageCollection != 0)
	{
		const BFMERetailAsciiString &text = BFMERetailAsciiString(name);

		return TheMappedImageCollection->bfmeFindDE(text);
	}

	return 0;
}

// cl: /DNDEBUG /MD
//
// Retail 0x00728BC0: setFlip-shaped wrapper with a second stack argument.
// REF_PTR_SET the map at +0x4C, then if m_initialized at +0x50 call
// the four-arg body at 0x007282A0 with (0, 0, m_width, extra).

class RefCountClass
{
public:
	virtual void Delete_This(void);
	void Add_Ref(void) { NumRefs++; }
	void Release_Ref(void)
	{
		NumRefs--;
		if (NumRefs == 0)
			Delete_This();
	}
private:
	int NumRefs;
};

#define REF_PTR_SET(dst, src) \
	{ if (src) (src)->Add_Ref(); if (dst) (dst)->Release_Ref(); (dst) = (src); }

class WorldHeightMap : public RefCountClass
{
};

class W3DTerrainBackground
{
public:
	void setFlip(WorldHeightMap *htMap, int extra);

protected:
	void setFlipRecursive(int xOffset, int yOffset, int width, int extra);

private:
	unsigned char m_pad00[0x48];
	int m_width;
	WorldHeightMap *m_map;
	bool m_initialized;
};

void W3DTerrainBackground::setFlip(WorldHeightMap *htMap, int extra)
{
	if (m_map == 0)
		return;
	if (htMap)
	{
		REF_PTR_SET(m_map, htMap);
	}
	if (!m_initialized)
		return;
	setFlipRecursive(0, 0, m_width, extra);
}

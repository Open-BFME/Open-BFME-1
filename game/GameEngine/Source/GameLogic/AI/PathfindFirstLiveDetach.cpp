// Advances the Pathfinder-side slot watermark and detaches the first live
// payload before returning it.

class Gen_003F69E0
{
public:
	void bfmeDetach(void);
};

struct BfmePathfindLiveEntry
{
	char m_bfmeHead[0x28];
	Gen_003F69E0 *m_bfmePayload;
};

class Gen_003D6490
{
public:
	Gen_003F69E0 *bfmeTakeFirstLive(void);

private:
	char m_bfmeHead[0x34];
	BfmePathfindLiveEntry *m_bfmeSlots[512];
	int m_bfmeCursor;
};

// ?bfmeTakeFirstLive@Gen_003D6490@@QAEPAVGen_003F69E0@@XZ
Gen_003F69E0 *Gen_003D6490::bfmeTakeFirstLive(void)
{
	while (m_bfmeCursor < 512)
	{
		if (m_bfmeSlots[m_bfmeCursor] != 0)
		{
			Gen_003F69E0 *payload = m_bfmeSlots[m_bfmeCursor]->m_bfmePayload;
			payload->bfmeDetach();
			return payload;
		}
		++m_bfmeCursor;
	}
	return 0;
}

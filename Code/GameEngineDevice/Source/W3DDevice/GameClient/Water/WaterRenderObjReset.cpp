// cl: /DNDEBUG /MD /EHsc
//
// Clean reconstruction of WaterRenderObjClass::reset at retail 0x007A1390.

class WaterTracksRenderSystem
{
public:
	void reset(void);
};

struct WaterMeshData
{
	float height;
	float velocity;
	unsigned char status;
	unsigned char preferredHeight;
};

class WaterRenderObjClass
{
public:
	void reset(void);

private:
	void updateMapOverrides(void);
	unsigned char m_beforeWaterTracks[0x254];
	WaterTracksRenderSystem *m_waterTrackSystem;
	WaterMeshData *m_meshData;
	unsigned int m_meshDataSize;
	bool m_meshInMotion;
	unsigned char m_beforeGridCells[0x3f];
	int m_gridCellsX;
	int m_gridCellsY;
};

void WaterRenderObjClass::reset(void)
{
	updateMapOverrides();

	if (m_meshData != 0)
	{
		const int mx = m_gridCellsX + 1;
		const int my = m_gridCellsY + 1;
		WaterMeshData *data = m_meshData;

		for (int y = 0; y < my + 2; ++y)
		{
			for (int x = 0; x < mx + 2; ++x)
			{
				data->velocity = 0.0f;
				data->height = 0.0f;
				data->preferredHeight = 0;
				data->status = 0;
				++data;
			}
		}

		m_meshInMotion = false;
	}

	if (m_waterTrackSystem != 0)
		m_waterTrackSystem->reset();
}

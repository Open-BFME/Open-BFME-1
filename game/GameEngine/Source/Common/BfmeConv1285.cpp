#include "System/game_client_random_variable.h"

class BfmeSink1285
{
public:
	virtual void bfmeFill1285(void *out, int value, float x, float y);
};

class BfmeA1285
{
public:
	void *bfmeMake1285(void *out, int value, BfmeSink1285 *sink);
	char m_bfmePad00[0x1c];
	GameClientRandomVariable m_x;
	GameClientRandomVariable m_y;
};

void *BfmeA1285::bfmeMake1285(void *out, int value, BfmeSink1285 *sink)
{
	float x = m_x.getValue();
	float y = m_y.getValue();
	sink->bfmeFill1285(out, value, x, y);
	return out;
}

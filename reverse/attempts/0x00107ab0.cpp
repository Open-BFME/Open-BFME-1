// ?localPixelToRadar@RadarLocalPixelToRadarShim@@QAE_NPBUICoord2D@@PAU2@@Z
// partial score=0.8 date=2026-09-05
// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc

typedef bool Bool;
typedef int Int;
typedef float Real;

#define NULL 0
#define TRUE true
#define FALSE false

struct ICoord2D { Int x; Int y; };

class RvaLPTRWindow
{
public:
	Int winGetSize(Int *width, Int *height);
};

class RadarLocalPixelToRadarShim
{
public:
	Bool localPixelToRadar(const ICoord2D *pixel, ICoord2D *radar);
	void findDrawPositions(Int startX, Int startY, Int width, Int height,
													ICoord2D *ul, ICoord2D *lr);

private:
	char padding00[0x1438];
	RvaLPTRWindow *m_radarWindow;
};

enum { RADAR_CELL_WIDTH = 128, RADAR_CELL_HEIGHT = 128 };

Bool RadarLocalPixelToRadarShim::localPixelToRadar(const ICoord2D *pixel, ICoord2D *radar)
{
	RadarLocalPixelToRadarShim *self = this;

	if (pixel == NULL || radar == NULL)
		return FALSE;

	ICoord2D size;
	self->m_radarWindow->winGetSize(&size.x, &size.y);

	ICoord2D start = { 0, 0 };
	ICoord2D ul, lr;
	findDrawPositions(start.x, start.y, size.x, size.y, &ul, &lr);

	Int scaledWidth = lr.x - ul.x;
	Int scaledHeight = lr.y - ul.y;

	if (scaledWidth < 1)
		return FALSE;
	if (scaledHeight < 1)
		return FALSE;

	if (pixel->x < ul.x || pixel->x > lr.x ||
			pixel->y < ul.y || pixel->y > lr.y)
		return FALSE;

	if (scaledWidth >= scaledHeight)
	{
		radar->x = (pixel->x - ul.x) * RADAR_CELL_WIDTH / scaledWidth;

		radar->y = (Int)(((pixel->y - ul.y) / (Real)(scaledHeight)) * size.y);

		radar->y = (size.y - radar->y) * RADAR_CELL_HEIGHT / size.y;
	}
	else
	{
		radar->x = (Int)(((pixel->x - ul.x) / (Real)(scaledWidth)) * size.x);

		radar->x = radar->x * RADAR_CELL_WIDTH / size.x;

		radar->y = (size.y - pixel->y) * RADAR_CELL_HEIGHT / size.y;
	}

	return TRUE;
}

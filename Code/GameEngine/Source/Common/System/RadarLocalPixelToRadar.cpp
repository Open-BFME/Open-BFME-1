// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc

typedef bool Bool;
typedef int Int;
typedef float Real;

struct ICoord2D
{
	Int x;
	Int y;
};

class GameWindow
{
public:
	Int winGetSize(Int *width, Int *height);
};

class Radar
{
public:
	Bool localPixelToRadar(const ICoord2D *pixel, ICoord2D *radar);
	void findDrawPositions(Int startX, Int startY, Int width, Int height,
		ICoord2D *ul, ICoord2D *lr);

private:
	char padding00[0x1438];
	GameWindow *m_radarWindow;
};

enum
{
	RADAR_CELL_WIDTH = 128,
	RADAR_CELL_HEIGHT = 128
};

Bool Radar::localPixelToRadar(const ICoord2D *pixel, ICoord2D *radar)
{
	if (pixel == 0 || radar == 0)
		return false;

	Int sizeX;
	Int sizeY;
	{
		ICoord2D size;
		m_radarWindow->winGetSize(&size.x, &size.y);
		sizeX = size.x;
		sizeY = size.y;
	}

	ICoord2D ul;
	ICoord2D lr;
	findDrawPositions(0, 0, sizeX, sizeY, &ul, &lr);

	Int scaledWidth = lr.x - ul.x;
	Int scaledHeight = lr.y - ul.y;

	if (scaledWidth < 1)
		return false;
	if (scaledHeight < 1)
		return false;

	if (pixel->x < ul.x || pixel->x > lr.x ||
		pixel->y < ul.y || pixel->y > lr.y)
		return false;

		if (scaledWidth >= scaledHeight)
		{
			radar->x = (pixel->x - ul.x) * RADAR_CELL_WIDTH / scaledWidth;
			Real yNumerator = (Real)(pixel->y - ul.y);
			Real yDenominator = (Real)scaledHeight;
			radar->y = (Int)((yNumerator / yDenominator) * sizeY);
		radar->y = (sizeY - radar->y) * RADAR_CELL_HEIGHT / sizeY;
	}
		else
		{
			Real xNumerator = (Real)(pixel->x - ul.x);
			Real xDenominator = (Real)scaledWidth;
			radar->x = (Int)((xNumerator / xDenominator) * sizeX);
		radar->x = radar->x * RADAR_CELL_WIDTH / sizeX;
		radar->y = (sizeY - pixel->y) * RADAR_CELL_HEIGHT / sizeY;
	}

	return true;
}

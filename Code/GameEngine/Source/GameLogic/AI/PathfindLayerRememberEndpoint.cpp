// Record at most two distinct PathfindLayer endpoint cells. The snap-goal
// caller invokes this twice after finding boundary intersections.

typedef int Int;

struct ICoord2D
{
	Int x;
	Int y;
};

class PathfindLayer
{
public:
	void bfmeRememberEndpoint(const ICoord2D *cell);

private:
	unsigned char opaque[0x18];
	ICoord2D startCell;
	ICoord2D endCell;
};

// ?bfmeRememberEndpoint@PathfindLayer@@QAEXPBUICoord2D@@@Z
void PathfindLayer::bfmeRememberEndpoint(const ICoord2D *cell)
{
	const volatile ICoord2D *coord = cell;
	volatile PathfindLayer *layer = this;
	Int value = coord->x;
	if (value == layer->startCell.x)
	{
		Int y = coord->y;
		if (y == layer->startCell.y)
			return;
	}

	if (value == layer->endCell.x)
	{
		value = coord->y;
		if (value == layer->endCell.y)
			return;
	}

	Int first = startCell.x;
	Int empty = -1;
	if (first == empty)
	{
		startCell.x = coord->x;
		startCell.y = coord->y;
		return;
	}

	if (endCell.x == empty)
	{
		endCell.x = coord->x;
		endCell.y = coord->y;
	}
}

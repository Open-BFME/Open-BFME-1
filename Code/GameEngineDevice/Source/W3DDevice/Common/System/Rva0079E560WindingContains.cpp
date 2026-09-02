// Address-derived reconstruction of the polygon winding test at 0x0079E560.

struct Rva0079E560Point2
{
	float x;
	float y;
};

struct Rva0079E560Point3
{
	float x;
	float y;
	float z;
};

class Rva0079E560Polygon
{
public:
	bool containsPoint(const Rva0079E560Point2 *point);

private:
	unsigned char m_pad[0x54];
	Rva0079E560Point3 *m_points;
	int m_pointCount;
};

bool Rva0079E560Polygon::containsPoint(const Rva0079E560Point2 *point)
{
	int winding = 0;
	if (m_pointCount > 0) {
		int remaining;
		const Rva0079E560Point2 *query = point;
		int followingIndex = 1;
		point = (const Rva0079E560Point2 *)((char *)m_points + 4);
		int index = 0;
		remaining = m_pointCount;
		do {
			int nextIndex = followingIndex < m_pointCount ? followingIndex : 0;

			if (point->x <= query->y) {
				if (m_points[nextIndex].y > query->y
					&& (int)((m_points[nextIndex].x - m_points[index].x)
							* (query->y - m_points[index].y)
						- (m_points[nextIndex].y - m_points[index].y)
							* (query->x - m_points[index].x)) > 0) {
					++winding;
				}
			} else if (m_points[nextIndex].y <= query->y
				&& (int)((m_points[nextIndex].x - m_points[index].x)
						* (query->y - m_points[index].y)
					- (m_points[nextIndex].y - m_points[index].y)
						* (query->x - m_points[index].x)) < 0) {
				--winding;
			}
			point = (const Rva0079E560Point2 *)((char *)point + sizeof(Rva0079E560Point3));
			++followingIndex;
			++index;
		} while (--remaining);
	}

	return winding != 0;
}

// Address-derived reconstruction of the recursive wide-result query at RVA 0x009F4130.
// The caller supplies a result, four-way node storage, bounds, and an optional distance path.
// The owner name remains opaque because no independent vtable or named caller proves it.

extern const float g_bfmeK1253;

struct Rva009F4130Point
{
    float x, y;
};

struct Rva009F39F0Payload;
struct Rva009F39F0Result
{
	Rva009F39F0Payload *m_value;
	void append(int first, int second);
};

class Rva009F4130Item
{
public:
	virtual void slot000(void) = 0;
	virtual const float *position(void) = 0;
	virtual void slot002(void) = 0;
	virtual void *value(void) = 0;
};

struct Rva009F4130Node
{
	void *m_unused00;
	Rva009F4130Item *m_item;
	void *m_unused08;
	void *m_unused0c;
	void *m_unused10;
	Rva009F4130Node *m_next;
};

struct Rva009F4130Range
{
	float m_x0;
	float m_y0;
	float m_unused08;
	float m_x1;
	float m_y1;
    void center(Rva009F4130Point *out) const
    {
        out->x = (m_x0 + m_x1) * g_bfmeK1253;
        out->y = (m_y0 + m_y1) * g_bfmeK1253;
    }
};

struct Rva009F4130NodeList
{
	int m_hasChildren;
	Rva009F4130Node *m_head;
};

class BfmeThingEQ
{
public:
	unsigned char bfmeAskEQ(void *value);
};

typedef float (__cdecl *Rva009F4130Distance)(void *context, void *item, float threshold);

class Rva009F4130Owner
{
public:
    void query(Rva009F39F0Result *result, Rva009F4130NodeList *nodes,
    unsigned int count, int xmin, int ymin, int xmax, int ymax,
    int xorigin, int yorigin, int size, void *distanceContext,
    float threshold, const Rva009F4130Range *range,
    Rva009F4130Distance distance, BfmeThingEQ *filter);
};

// ?query@Rva009F4130Owner@@QAEXPAURva009F39F0Result@@PAURva009F4130NodeList@@IHHHHHHHPAXMPBURva009F4130Range@@P6AM22M@ZPAVBfmeThingEQ@@@Z
void Rva009F4130Owner::query(Rva009F39F0Result *result, Rva009F4130NodeList *nodes,
    unsigned int count, int xmin, int ymin, int xmax, int ymax,
    int xorigin, int yorigin, int size, void *distanceContext,
    float threshold, const Rva009F4130Range *range,
    Rva009F4130Distance distance, BfmeThingEQ *filter)
{
    for (Rva009F4130Node *node = nodes->m_head; node != 0; node = node->m_next)
    {
        union { float distance; int bits; } resultDistance;
        if (distanceContext != 0)
        {
            resultDistance.distance = distance(distanceContext, node->m_item, threshold);
            if (resultDistance.distance > threshold)
                continue;
        }
        else
        {
            const float *position = node->m_item->position();
            if (position[0] < range->m_x0 || position[0] > range->m_x1 ||
                position[1] < range->m_y0 || position[1] > range->m_y1)
                continue;
            Rva009F4130Point center;
            range->center(&center);
            float dy = position[1] - center.y;
            float dx = position[0] - center.x;
            resultDistance.distance = dx * dx + dy * dy;
        }
        void *value = node->m_item->value();
        if (value && (!filter || filter->bfmeAskEQ(value)))
            result->append((int)value, resultDistance.bits);
    }
    if (!nodes->m_hasChildren)
        return;
    size /= 2;
    nodes += 1;
    int ymid = yorigin + size;
    if (ymin < ymid)
    {
        int xmid = xorigin + size;
        if (xmin < xmid)
            query(result, nodes, count >> 2, xmin, ymin, xmax, ymax, xorigin, yorigin, size, distanceContext, threshold, range, distance, filter);
        if (xmax >= xmid)
            query(result, nodes + count, count >> 2, xmin, ymin, xmax, ymax, xmid, yorigin, size, distanceContext, threshold, range, distance, filter);
    }
    if (ymax < ymid)
        return;
    int xmid = xorigin + size;
    if (xmin < xmid)
        query(result, nodes + count * 2, count >> 2, xmin, ymin, xmax, ymax, xorigin, ymid, size, distanceContext, threshold, range, distance, filter);
    if (xmax >= xmid)
        query(result, nodes + count * 3, count >> 2, xmin, ymin, xmax, ymax, xmid, ymid, size, distanceContext, threshold, range, distance, filter);
}

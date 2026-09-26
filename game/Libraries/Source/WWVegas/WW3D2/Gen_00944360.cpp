// cl: /DNDEBUG /MD /EHs-c-

class Gen_009431F0
{
public:
	int map_x(float x);
	int map_y(float y);
	void collect(void *object, const float *bounds, const float *padding);
	void recurse(void *object, void *nodes, int node_count, int min_x, int min_y,
		int max_x, int max_y, int unused_x, int unused_y, int count);

private:
	float origin_x;
	float origin_y;
	unsigned char pad[0x10];
	void *nodes;
	unsigned int node_count;
	float scale;
	int count;
};

void Gen_009431F0::collect(void *object, const float *bounds, const float *padding)
{
	float offset_x = padding ? padding[0] : 0.0f;
	int min_x = map_x(bounds[0] - offset_x);
	offset_x = padding ? padding[0] : 0.0f;
	int max_x = map_x(offset_x + bounds[3]);
	float offset_y = padding ? padding[1] : 0.0f;
	int min_y = map_y(bounds[1] - offset_y);
	offset_y = padding ? padding[1] : 0.0f;
	int max_y = map_y(offset_y + bounds[4]);

	recurse(object, nodes, node_count >> 2, min_x, min_y, max_x, max_y, 0, 0,
		count);
}

#pragma comment(linker, "/alternatename:?recurse@Gen_009431F0@@QAEXPAX0HHHHHHHH@Z=?d_009441d0@@YAXXZ")

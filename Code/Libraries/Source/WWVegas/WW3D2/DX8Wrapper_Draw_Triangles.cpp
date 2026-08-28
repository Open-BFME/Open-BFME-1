// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath/sphere.h
class SphereClass
{
public:
	float Center[3];
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2/sortingrenderer.h
class SortingRendererClass
{
public:
	static void Insert_Triangles(
		const SphereClass &sphere,
		unsigned short start_index,
		unsigned short polygon_count,
		unsigned short min_vertex_index,
		unsigned short vertex_count);
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2/dx8wrapper.h
class DX8Wrapper
{
	static void Draw(
		int primitive_type,
		unsigned short start_index,
		unsigned short polygon_count,
		unsigned short min_vertex_index,
		unsigned short vertex_count,
		int apply_render_state);

public:
	static void Draw_Triangles(
		unsigned buffer_type,
		unsigned short start_index,
		unsigned short polygon_count,
		unsigned short min_vertex_index,
		unsigned short vertex_count);
};

void DX8Wrapper::Draw_Triangles(
	unsigned buffer_type,
	unsigned short start_index,
	unsigned short polygon_count,
	unsigned short min_vertex_index,
	unsigned short vertex_count)
{
	if (buffer_type == 1 || buffer_type == 3) {
		// Retail only materializes the zero center because this path does not consume a radius.
		SphereClass sphere = { { 0.0f, 0.0f, 0.0f } };
		SortingRendererClass::Insert_Triangles(
			sphere, start_index, polygon_count, min_vertex_index, vertex_count);
	} else {
		Draw(4, start_index, polygon_count, min_vertex_index, vertex_count, 1);
	}
}

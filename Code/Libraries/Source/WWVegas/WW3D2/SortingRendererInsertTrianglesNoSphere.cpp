// cl: /DNDEBUG /MD /EHsc
// SortingRendererClass::Insert_Triangles(start, count, minv, vert)
// retail 0x009037D0. Forwards a zeroed 12-byte sphere view plus four stack args.

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath/sphere.h
class SphereClass
{
public:
	float X;
	float Y;
	float Z;
	SphereClass()
	{
		X = 0.0f;
		Y = 0.0f;
		Z = 0.0f;
	}
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2/sortingrenderer.h
class SortingRendererClass
{
public:
	static void Insert_Triangles(
		const SphereClass &bounding_sphere,
		unsigned short start_index,
		unsigned short polygon_count,
		unsigned short min_vertex_index,
		unsigned short vertex_count);
	static void Insert_Triangles(
		unsigned short start_index,
		unsigned short polygon_count,
		unsigned short min_vertex_index,
		unsigned short vertex_count);
};

// ?Insert_Triangles@SortingRendererClass@@SAXGGGG@Z
void SortingRendererClass::Insert_Triangles(
	unsigned short start_index,
	unsigned short polygon_count,
	unsigned short min_vertex_index,
	unsigned short vertex_count)
{
	Insert_Triangles(SphereClass(), start_index, polygon_count, min_vertex_index, vertex_count);
}

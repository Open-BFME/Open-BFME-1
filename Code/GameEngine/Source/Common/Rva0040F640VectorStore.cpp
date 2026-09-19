struct Rva0040F640Vector {
	float x;
	float y;
	float z;
};

class Rva0040F640Body {
private:
	char prefix[0x1c];
	float value_x;
	float value_y;
	float value_z;

public:
	void set(const Rva0040F640Vector &source);
};

// ?dup_0040f640@@YAXXZ
void Rva0040F640Body::set(const Rva0040F640Vector &source)
{
	value_x = source.x;
	value_y = source.y;
	value_z = source.z;
}

typedef void (Rva0040F640Body::*Rva0040F640Set)(const Rva0040F640Vector &);
Rva0040F640Set g_rva0040F640Set = &Rva0040F640Body::set;

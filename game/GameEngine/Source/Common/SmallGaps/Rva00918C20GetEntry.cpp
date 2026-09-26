// ?getEntry@Rva00918C20Owner@@QBEXIPAURva00918C20Vec3@@@Z
struct Rva00918C20Vec3 { float x; float y; float z; };
struct Rva00918C20Owner {
	char m_pad[0xd8];
	Rva00918C20Vec3* m_entries;
	int m_pad2;
	unsigned int m_count;
	void getEntry(unsigned int index, Rva00918C20Vec3* out) const;
};
void Rva00918C20Owner::getEntry(unsigned int index, Rva00918C20Vec3* out) const
{
	if (index < m_count) {
		const Rva00918C20Vec3& e = m_entries[index];
		out->x = e.x;
		out->y = e.y;
		out->z = e.z;
	} else {
		out->x = 0.0f;
		out->y = 0.0f;
		out->z = 0.0f;
	}
}

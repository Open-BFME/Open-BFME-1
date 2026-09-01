// cl: /DNDEBUG /MD /EHsc
// readable body of ?removeTree@W3DTreeBuffer@@QAEXW4DrawableID@@@Z: Code/GameEngineDevice/Source/W3DDevice/GameClient/W3DTreeBuffer.cpp

enum DrawableID
{
	INVALID_DRAWABLE_ID = 0,
	FORCE_DRAWABLEID_TO_LONG_SIZE = 0x7ffffff
};

class W3DTreeBuffer
;

class Vector3
{
public:
	float X;
	float Y;
	float Z;

	Vector3(float x, float y, float z) { X = x; Y = y; Z = z; }
	Vector3 &operator=(const Vector3 &v) { X = v.X; Y = v.Y; Z = v.Z; return *this; }
};

class SphereClass
{
public:
	Vector3 Center;
	float Radius;
};

struct BFME_TREE
{
	Vector3 location;
	char padding0c[0x34];
	int treeType;
	char padding44[4];
	SphereClass bounds;
	DrawableID drawableID;
	char padding5c[0x8c];
};

class W3DTreeBuffer
{
public:
	void removeTree(DrawableID id);

private:
	char padding000000[0x1b0];
	BFME_TREE m_trees[12000];
	int m_numTrees;
	unsigned char m_anythingChanged;
};

void W3DTreeBuffer::removeTree(DrawableID id)
{
	for (int i = 0; i < m_numTrees; ++i) {
		if (m_trees[i].drawableID == id) {
			m_trees[i].location = Vector3(0, 0, 0);
			m_trees[i].treeType = -2;
			m_trees[i].bounds.Center = Vector3(0, 0, 0);
			m_trees[i].bounds.Radius = 1;
			m_anythingChanged = 1;
		}
	}
}

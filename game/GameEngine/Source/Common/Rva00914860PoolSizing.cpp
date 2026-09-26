// Open-BFME5: clean C++ conversion of the three-pool size update.

class Rva00914860PoolA
{
public:
	bool allocate(int count, int extra);
};

class Rva00914860PoolB
{
public:
	bool allocate(int count, int extra);
};

class Rva00914860PoolC
{
public:
	bool allocate(int count, int extra);
};

extern Rva00914860PoolA g_rva00914860PoolA;
extern Rva00914860PoolB g_rva00914860PoolB;
extern Rva00914860PoolC g_rva00914860PoolC;
extern int g_rva00914860Limit;

class Rva00914860Sizer
{
public:
	void updatePoolSizes(int width, int height, int *storedWidth);

private:
	char m_pad00[0x2C];
	int m_sizeMode;
};

void Rva00914860Sizer::updatePoolSizes(int width, int height, int *storedWidth)
{
	int scale = m_sizeMode == 1 ? 4 : 3;
	int scaledHeight = scale * height;
	int scaledWidth = scale * width;
	*storedWidth = scaledWidth;

	if (g_rva00914860Limit < scaledHeight)
	{
		int count = scaledHeight * 2;
		g_rva00914860PoolA.allocate(count, 0);
		g_rva00914860PoolB.allocate(count, 0);
		g_rva00914860PoolC.allocate(count, 0);
	}
}

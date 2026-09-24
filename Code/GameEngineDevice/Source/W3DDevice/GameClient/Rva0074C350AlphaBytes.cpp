// cl: /DNDEBUG /MD /EHsc
// Retail uses a four-stack-word thiscall ABI. The fourth pointer is passed by
// the caller but never read by this body. Keep the owner/method address-derived.

typedef unsigned char Byte;

struct Rva0074C350BlendTile
{
	short blendIndex;
	Byte pad02[2];
	Byte horizontal;
	Byte vertical;
	Byte rightDiagonal;
	Byte leftDiagonal;
	Byte inverted;
	Byte longDiagonal;
	Byte pad0A[2];
	int customBlendEdgeClass;
};

class Rva0074C350Owner
{
public:
	void rva0074C350(int x, int y, Byte alpha[4], void *unused);

private:
	char pad000[8];
	int width;
	char pad00c[0x20 - 0x0c];
	int dataSize;
	char pad024[0x8c - 0x24];
	short *tileIndices;
	int *blendIndices;
	char pad094[0x80a4 - 0x94];
	Rva0074C350BlendTile *blendTiles;
	char pad80a8[0x120e0 - 0x80a8];
	int originX;
	int originY;
};

void Rva0074C350Owner::rva0074C350(int x, int y, Byte alpha[4], void *unused)
{
	int index = (originY + y) * width + originX + x;
	if (index < dataSize && tileIndices)
	{
		int blendIndex = blendIndices[index];
		alpha[0] = 0;
		alpha[1] = 0;
		alpha[2] = 0;
		alpha[3] = 0;
		if (blendIndex)
		{
			if (blendTiles[blendIndex].horizontal)
			{
				if (blendTiles[blendIndex].inverted & 1)
				{
					alpha[0] = alpha[3] = 255;
				}
				else
				{
					alpha[1] = alpha[2] = 255;
				}
			}
			if (blendTiles[blendIndex].vertical)
			{
				if (blendTiles[blendIndex].inverted & 1)
				{
					alpha[0] = alpha[1] = 255;
				}
				else
				{
					alpha[2] = alpha[3] = 255;
				}
			}
			if (blendTiles[blendIndex].rightDiagonal)
			{
				if (blendTiles[blendIndex].inverted & 1)
				{
					alpha[1] = 255;
					if (blendTiles[blendIndex].longDiagonal)
					{
						alpha[0] = 255;
						alpha[2] = 255;
					}
				}
				else
				{
					alpha[2] = 255;
					if (blendTiles[blendIndex].longDiagonal)
					{
						alpha[1] = 255;
						alpha[3] = 255;
					}
				}
			}
			if (blendTiles[blendIndex].leftDiagonal)
			{
				if (blendTiles[blendIndex].inverted & 1)
				{
					alpha[0] = 255;
					if (blendTiles[blendIndex].longDiagonal)
					{
						alpha[1] = 255;
						alpha[3] = 255;
					}
				}
				else
				{
					alpha[3] = 255;
					if (blendTiles[blendIndex].longDiagonal)
					{
						alpha[0] = 255;
						alpha[2] = 255;
					}
				}
			}
			if (blendTiles[blendIndex].customBlendEdgeClass >= 0)
			{
				alpha[0] = alpha[1] = alpha[2] = alpha[3] = 0;
			}
		}
	}
}

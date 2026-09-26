// Retail RVA 0x0000DAAD is a five-byte ILT jump to Bridge::isCellOnEnd at
// 0x001A24B0.
// The symbol pin and four callers prove the method identity.

struct Region2D;

class Bridge
{
public:
	bool isCellOnEnd(const Region2D *cell);
};

class Rva0000DAADBridgeThunk
{
public:
	bool forward(const Region2D *cell);
};

bool Rva0000DAADBridgeThunk::forward(const Region2D *cell)
{
	return ((Bridge *)this)->isCellOnEnd(cell);
}

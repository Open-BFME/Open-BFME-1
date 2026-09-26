// Retail RVA 0x0075F0E0 (145 bytes), thiscall, ret 8.
//
// The GetGameClientRandomValue call passes the literal at 0x01123918,
//   F:\bfme\Code\gameenginedevice\Source\W3DDevice\GameClient\Drawable\W3DScriptedModelDraw.cpp
// with line 1116, so the body lives in that translation unit.  Its one caller
// (0x00765FB0, through ILT 0x0003AAC6) passes the model-state pointer at +0x14
// of the draw object as `this` and stores the result at +0x28.  The owner is
// kept under the address-token class Gen_0075F090 (0x0075F090 reads the same
// +0x2C vector of 0x38-byte elements); the method keeps its own address.
//
// Sums the +0x28 weight of the first min(size, limit) elements, one less for
// element `index`, draws a value below that total and returns the element the
// draw lands in (0 when fewer than two elements are in play).

extern int GetGameClientRandomValue(int low, int high, char *file, int line);

class Elem0075F0E0
{
public:
	int dword_00[10];					// +0x00
	int dword_28;						// +0x28
	int dword_2C[3];					// +0x2C
};

class Vec0075F0E0
{
public:
	int size(void) const
	{
		return (int)(m_finish - m_start);
	}

	Elem0075F0E0 &operator[](int index) const
	{
		return m_start[index];
	}

	Elem0075F0E0 *m_start;					// +0x00
	Elem0075F0E0 *m_finish;					// +0x04
};

class Gen_0075F090
{
public:
	int rva0075F0E0(int index, int limit) const;

private:
	int dword_00[11];					// +0x00
	Vec0075F0E0 m_vector;					// +0x2C
};

// ?rva0075F0E0@Gen_0075F090@@QBEHHH@Z
int Gen_0075F090::rva0075F0E0(int index, int limit) const
{
	int size = m_vector.size();
	if (size > limit)
		size = limit;
	if (size < 2)
		return 0;

	int total = 0;
	int i;
	for (i = 0; i < size; ++i)
	{
		int weight = m_vector[i].dword_28;
		if (i == index)
			--weight;
		total += weight;
	}

	int pick = GetGameClientRandomValue(0, total - 1,
		"F:\\bfme\\Code\\gameenginedevice\\Source\\W3DDevice\\GameClient\\Drawable\\W3DScriptedModelDraw.cpp", 1116);
	for (i = 0; i < size; ++i)
	{
		int weight = m_vector[i].dword_28;
		if (i == index)
			--weight;
		pick -= weight;
		if (pick < 0)
			return i;
	}

	return 0;
}

struct BfmeVec3EQK
{
	float m_bfmeXEQK;
	float m_bfmeYEQK;
	float m_bfmeZEQK;
};

void __cdecl bfmeInnerEQK(int host, BfmeVec3EQK *first, BfmeVec3EQK *second, BfmeVec3EQK value, int extra, int flag);

void __cdecl bfmeCallEQK(int host, BfmeVec3EQK *tail, int unused, int extra)
{
	BfmeVec3EQK *point = tail - 1;
	bfmeInnerEQK(host, point, point, *point, extra, 0);
}

void __cdecl bfmeCallEQL(int host, BfmeVec3EQK *tail, int extra)
{
	BfmeVec3EQK *point = tail - 1;
	bfmeInnerEQK(host, point, point, *point, extra, 0);
}

void __cdecl bfmeInnerEQM(int host, BfmeVec3EQK *first, BfmeVec3EQK *second, BfmeVec3EQK value, int extra, int flag);

void __cdecl bfmeCallEQM(int host, BfmeVec3EQK *tail, int unused, int extra)
{
	BfmeVec3EQK *point = tail - 1;
	bfmeInnerEQM(host, point, point, *point, extra, 0);
}

void __cdecl bfmeCallEQN(int host, BfmeVec3EQK *tail, int extra)
{
	BfmeVec3EQK *point = tail - 1;
	bfmeInnerEQM(host, point, point, *point, extra, 0);
}

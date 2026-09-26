// ?matrixEqual@@YA_NPBM0@Z
bool matrixEqual(const float* p, const float* q)
{
	for (int i = 0; i < 3; ++i)
		for (int j = 0; j < 4; ++j)
			if (p[i * 4 + j] != q[i * 4 + j])
				return false;
	return true;
}

// ?pairsEqual@Rva00913670Owner@@QAE_NPBU1@@Z
// Open-BFME7: float-pair array equality (116 B). The two per-element
// equalities are evaluated as separate bools and combined with a non
// short-circuit AND; promoting the operands to double reproduces the retail
// fld order (other first) while keeping this->m_pairs as the loop pointer.
struct Rva00913670Pair { float x; float y; };
struct Rva00913670Owner {
	int m_0;
	Rva00913670Pair* m_pairs;
	int m_count;
	bool pairsEqual(const Rva00913670Owner* other);
};
bool Rva00913670Owner::pairsEqual(const Rva00913670Owner* other)
{
	if (m_count == other->m_count) {
		for (int i = 0; i < m_count; ++i) {
			bool sameX = (double)other->m_pairs[i].x == (double)m_pairs[i].x;
			bool sameY = (double)other->m_pairs[i].y == (double)m_pairs[i].y;
			if (!(sameX & sameY)) return false;
		}
		return true;
	}
	return false;
}

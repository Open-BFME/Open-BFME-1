// ?anyBlocked@Rva003FD060Owner@@QBE_NXZ
struct Rva003FD060TerrainLogic {
	virtual void s0(); virtual void s1(); virtual void s2(); virtual void s3(); virtual void s4(); virtual void s5(); virtual void s6(); virtual void s7();
	virtual void s8(); virtual void s9(); virtual void s10(); virtual void s11(); virtual void s12(); virtual void s13(); virtual void s14(); virtual void s15();
	virtual void s16(); virtual void s17(); virtual void s18(); virtual void s19(); virtual void s20(); virtual void s21(); virtual void s22(); virtual void s23();
	virtual void s24(); virtual void s25(); virtual void s26(); virtual void s27(); virtual void s28(); virtual void s29(); virtual void s30(); virtual void s31();
	virtual int isValid(int id);
};
extern Rva003FD060TerrainLogic* TheTerrainLogic;
struct Rva003FD060Node { Rva003FD060Node* m_next; char m_pad[0x1c]; int m_id; };
struct Rva003FD060Owner { int m_0; Rva003FD060Node* m_head; bool anyBlocked() const; };
bool Rva003FD060Owner::anyBlocked() const
{
	for (Rva003FD060Node* n = m_head; n; n = n->m_next) {
		if (n->m_id != 0x7fffffff && !TheTerrainLogic->isValid(n->m_id))
			return true;
	}
	return false;
}

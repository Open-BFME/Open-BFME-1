struct BfmeKeyTZ
{
	int m_bfmeOrderTZ;
	float m_bfmeScoreTZ;
};

char __cdecl bfmeLessTZ(const BfmeKeyTZ *first, const BfmeKeyTZ *second)
{
	if (first->m_bfmeOrderTZ < second->m_bfmeOrderTZ)
		return 1;

	if (first->m_bfmeOrderTZ > second->m_bfmeOrderTZ)
		return 0;

	int result = first->m_bfmeScoreTZ < second->m_bfmeScoreTZ;

	return (char)result;
}

// ??0Rva0087EB30EffectParam@@QAE@HHMMPBURva0087EB30Vec3@@@Z
// partial score=0.9 date=2026-09-06
struct Rva0087EB30Vec3 { float x; float y; float z; };
struct Rva0087EB30EffectParam {
	int m_type;
	int m_index;
	float m_valueA;
	float m_value;
	Rva0087EB30Vec3 m_pos;
	int m_extra;
	bool m_flag;
	Rva0087EB30EffectParam(int type, int index, float valueA, float valueB, const Rva0087EB30Vec3* pos);
};
Rva0087EB30EffectParam::Rva0087EB30EffectParam(int type, int index, float valueA, float valueB, const Rva0087EB30Vec3* pos)
{
	m_index = index;
	m_type = type;
	m_valueA = valueA;
	m_value = (type == 2) ? valueB : valueA;
	m_pos.x = pos->x;
	m_pos.y = pos->y;
	m_pos.z = pos->z;
	m_extra = 0;
	m_flag = true;
}

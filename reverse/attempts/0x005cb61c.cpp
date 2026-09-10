// ?findParentTemplate@ParticleSystemManager@@QBEPAVParticleSystemTemplate@@ABVAsciiString@@H@Z
// partial score=0.82 date=2026-09-10
// Complete real-C++ reconstruction retained for later comparison.  The
// identity is supported by the named ScriptEngine caller and the
// ParticleSystemManager map layout; this attempt is not byte verified.

struct BFMEParticleSystemTemplateParentView
{
	char m_prefix[0x68];
	AsciiString m_slaveSystemName;
};

struct BFMEParticleTemplateNode
{
	BFMEParticleTemplateNode *m_next;
	char m_key[sizeof(AsciiString)];
	ParticleSystemTemplate *m_template;
};

struct BFMEParticleTemplateIterator
{
	BFMEParticleTemplateNode *m_cur;
	void *m_table;

	BFMEParticleTemplateNode *skip() const;
	BFMEParticleTemplateIterator &operator++()
	{
		BFMEParticleTemplateNode *next = m_cur->m_next;
		m_cur = next != NULL ? next : skip();
		return *this;
	}
};

struct BFMEParticleTemplateMapView
{
	BFMEParticleTemplateIterator begin() const;
};

struct BFMEParticleSystemManagerMapView
{
	char m_prefix[0x9c];
	BFMEParticleTemplateMapView m_templateMap;
};

ParticleSystemTemplate *ParticleSystemManager::findParentTemplate(
	const AsciiString &name, Int parentNum) const
{
	BFMEParticleSystemManagerMapView *manager =
		reinterpret_cast<BFMEParticleSystemManagerMapView *>(
			const_cast<ParticleSystemManager *>(this));
	BFMEParticleTemplateIterator begin(manager->m_templateMap.begin());
	for (; begin.m_cur != NULL; ++begin) {
		ParticleSystemTemplate *sysTemplate = begin.m_cur->m_template;
		BFMEParticleSystemTemplateParentView *layout =
			reinterpret_cast<BFMEParticleSystemTemplateParentView *>(sysTemplate);
		if (name.compare(layout->m_slaveSystemName) == 0) {
			if (!parentNum--) {
				return sysTemplate;
			}
		}
	}
	return NULL;
}

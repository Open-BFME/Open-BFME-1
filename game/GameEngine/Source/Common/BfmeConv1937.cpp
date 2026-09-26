class BFMERetailAsciiString
{
public:
	BFMERetailAsciiString(const char *text);

	~BFMERetailAsciiString() { releaseBuffer(); }

	void *m_bfmeBufCW;

private:
	void releaseBuffer();
};

class ParticleSystemManager
{
public:
	void bfmeStopCW(const BFMERetailAsciiString &name);
};

extern ParticleSystemManager *TheParticleSystemManager;

class BfmeHostCW
{
public:
	void bfmeSpawnCW(const char *name);
	void bfmeStartCW();
};

void BfmeHostCW::bfmeSpawnCW(const char *name)
{
	bfmeStartCW();

	{
		const BFMERetailAsciiString &text = BFMERetailAsciiString(name);

		TheParticleSystemManager->bfmeStopCW(text);
	}
}

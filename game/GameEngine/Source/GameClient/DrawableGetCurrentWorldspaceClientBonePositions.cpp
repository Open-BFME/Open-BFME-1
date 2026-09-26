// cl: /DNDEBUG /MD /EHsc
// Drawable::getCurrentWorldspaceClientBonePositions, retail RVA 0x004139E0.

class Matrix3D;

class ObjectDrawInterface
{
public:
	virtual void slot00();
	virtual void slot04();
	virtual void slot08();
	virtual void slot0C();
	virtual void slot10();
	virtual bool getCurrentWorldspaceClientBonePositions(
		const char *boneName, Matrix3D &transform) const;
};

class DrawModule
{
public:
	virtual void slot00(); virtual void slot04(); virtual void slot08();
	virtual void slot0C(); virtual void slot10(); virtual void slot14();
	virtual void slot18(); virtual void slot1C(); virtual void slot20();
	virtual void slot24(); virtual void slot28(); virtual void slot2C();
	virtual void slot30(); virtual void slot34(); virtual void slot38();
	virtual void slot3C(); virtual void slot40(); virtual void slot44();
	virtual void slot48(); virtual void slot4C(); virtual void slot50();
	virtual void slot54(); virtual void slot58(); virtual void slot5C();
	virtual void slot60(); virtual void slot64(); virtual void slot68();
	virtual void slot6C(); virtual void slot70(); virtual void slot74();
	virtual void slot78(); virtual void slot7C(); virtual void slot80();
	virtual void slot84(); virtual void slot88(); virtual void slot8C();
	virtual void slot90(); virtual void slot94();
	virtual const ObjectDrawInterface *getObjectDrawInterface() const;
};

class Drawable
{
public:
	bool getCurrentWorldspaceClientBonePositions(
		const char *boneName, Matrix3D &transform) const;

private:
	unsigned char m_pad[0x150];
	const DrawModule **m_drawModules;
};

bool Drawable::getCurrentWorldspaceClientBonePositions(
	const char *boneName, Matrix3D &transform) const
{
	for (const DrawModule **module = m_drawModules; *module; ++module)
	{
		const ObjectDrawInterface *draw = (*module)->getObjectDrawInterface();
		if (draw && draw->getCurrentWorldspaceClientBonePositions(boneName, transform))
			return true;
	}
	return false;
}

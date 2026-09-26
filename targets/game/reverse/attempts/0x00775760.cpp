// ?d_00775760@@YAXXZ
// partial score=0.35 date=2026-09-25
// Partial reconstruction bank for retail RVA 0x00775760.
// ABI remains six-argument here; retail cleanup proves seven stack arguments.
Int W3DModelDraw::getPristineBonePositionsForConditionState(
	const ModelConditionFlags& condition,
	const char* boneNamePrefix,
	Int startIndex,
	Coord3D* positions,
	Matrix3D* transforms,
	Int maxBones) const
{
	const ModelConditionInfo* stateToUse = findBestInfo(condition);
	if (!stateToUse)
		return 0;

	stateToUse->validateStuff(
		stateToUse == m_curState ? m_renderObject : NULL,
		getDrawable()->getScale(),
		getW3DModelDrawModuleData()->m_extraPublicBones);

	const int MAX_BONE_GET = 64;
	static Matrix3D tmpMtx[MAX_BONE_GET];
	if (maxBones > MAX_BONE_GET)
		maxBones = MAX_BONE_GET;
	if (transforms == NULL)
		transforms = tmpMtx;

	Int posCount = 0;
	Int endIndex = (startIndex == 0) ? 0 : 99;
	char buffer[256];
	for (Int i = startIndex; i <= endIndex; ++i)
	{
		if (i == 0)
			strcpy(buffer, boneNamePrefix);
		else
			sprintf(buffer, "%s%02d", boneNamePrefix, i);

		for (char *c = buffer; c && *c; ++c)
			*c = tolower(*c);

		const Matrix3D* mtx = stateToUse->findPristineBone(NAMEKEY(buffer), NULL);
		if (mtx)
			transforms[posCount] = *mtx;
		else
		{
			const Object *obj = getDrawable()->getObject();
			if (obj)
				transforms[posCount] = *obj->getTransformMatrix();
			else
				transforms[posCount].Make_Identity();
			break;
		}

		++posCount;
		if (posCount >= maxBones)
			break;
	}

	if (positions && transforms)
	{
		for (i = 0; i < posCount; ++i)
		{
			Vector3 pos = transforms[i].Get_Translation();
			positions[i].x = pos.X;
			positions[i].y = pos.Y;
			positions[i].z = pos.Z;
		}
	}

	return posCount;
}

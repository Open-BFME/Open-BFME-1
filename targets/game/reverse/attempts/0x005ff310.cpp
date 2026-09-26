// ?update@ParticleSystem@@UAE_NH@Z
// partial score=0.35 date=2026-09-09
// ParticleSystem::update @ 0x005FF310, full clean-C++ GeneralsMD-derived attempt.
Bool ParticleSystem::update( Int localPlayerIndex )
{
	if (TheGlobalData->m_useFX == FALSE)
		return false;
	if (m_delayLeft)
	{
		--m_delayLeft;
		if (m_delayLeft == 0)
			m_startTimestamp = TheGameClient->getFrame();
		return true;
	}
	if (m_windMotion != ParticleSystemInfo::WIND_MOTION_NOT_USED)
		updateWindMotion();
	Bool transformSet = false;
	const Matrix3D *parentXfrm = NULL;
	Bool isShrouded = false;
	if (m_attachedToDrawableID)
	{
		Drawable *attachedTo = TheGameClient->findDrawableByID(m_attachedToDrawableID);
		if (attachedTo)
		{
			if (attachedTo->getFullyObscuredByShroud())
				isShrouded = true;
			parentXfrm = attachedTo->getTransformMatrix();
			m_lastPos = m_pos;
			m_pos = *attachedTo->getPosition();
		}
		else
		{
			m_attachedToDrawableID = INVALID_DRAWABLE_ID;
			destroy();
		}
	}
	else if (m_attachedToObjectID)
	{
		Object *objectAttachedTo = TheGameLogic->findObjectByID(m_attachedToObjectID);
		if (objectAttachedTo)
		{
			if (!isShrouded)
				isShrouded = (objectAttachedTo->getShroudedStatus(localPlayerIndex) >= OBJECTSHROUD_FOGGED);
			const Drawable *draw = objectAttachedTo->getDrawable();
			parentXfrm = draw ? draw->getTransformMatrix() : objectAttachedTo->getTransformMatrix();
			m_lastPos = m_pos;
			m_pos = *objectAttachedTo->getPosition();
		}
		else
		{
			m_attachedToObjectID = INVALID_ID;
			destroy();
		}
	}
	if (parentXfrm)
	{
		if (m_skipParentXfrm)
			m_transform = m_localTransform;
		else if (m_isLocalIdentity == false)
		{
#ifdef ALLOW_TEMPORARIES
			m_transform = (*parentXfrm) * m_localTransform;
#else
			m_transform.mul(*parentXfrm, m_localTransform);
#endif
		}
		else
			m_transform = *parentXfrm;
		m_isIdentity = false;
		transformSet = true;
	}
	if (transformSet == false)
	{
		if (m_isLocalIdentity == false)
		{
			m_transform = m_localTransform;
			m_isIdentity = false;
		}
		else
			m_isIdentity = true;
	}
	if (m_controlParticle)
	{
		const Coord3D *controlPos = m_controlParticle->getPosition();
		m_transform.Set_X_Translation(controlPos->x);
		m_transform.Set_Y_Translation(controlPos->y);
		m_transform.Set_Z_Translation(controlPos->z);
		m_isIdentity = false;
		m_lastPos = m_pos;
		m_pos = *controlPos;
	}
	if (m_isDestroyed == false)
	{
		if (m_isForever || (m_isForever == false && m_systemLifetimeLeft > 0))
		{
			if (!isShrouded && m_isStopped == false && m_masterSystem == NULL)
			{
				if (m_burstDelayLeft == 0)
				{
					ParticlePriorityType priority = getPriority();
					Int count = REAL_TO_INT(m_burstCount.getValue());
					count *= m_countCoeff;
					for (Int i = 0; i < count; i++)
					{
						const ParticleInfo *info = generateParticleInfo(i, count);
						if (!m_isEmitAboveGroundOnly ||
							(info->m_pos.z >= TheTerrainLogic->getGroundHeight(info->m_pos.x, info->m_pos.y)))
						{
							Particle *p = createParticle(info, priority);
							if (p == NULL)
								continue;
							if (m_attachedSystemName.isEmpty() == false)
							{
								const ParticleSystemTemplate *tmp =
									TheParticleSystemManager->findTemplate(m_attachedSystemName);
								if (tmp)
								{
									ParticleSystem *sys = TheParticleSystemManager->createParticleSystem(tmp, TRUE);
									sys->setControlParticle(p);
									p->controlParticleSystem(sys);
								}
							}
							if (m_slaveSystem)
							{
								ParticleInfo mergeInfo =
									ParticleSystem::mergeRelatedParticleSystems(this, m_slaveSystem, false);
								m_slaveSystem->createParticle(&mergeInfo, priority);
							}
						}
					}
					m_burstDelayLeft = (UnsignedInt)m_burstDelay.getValue();
					m_burstDelayLeft *= m_delayCoeff;
				}
				else
					m_burstDelayLeft--;
			}
		}
	}
	Particle *p = m_systemParticlesHead;
	Particle *oldParticle;
	while (p)
	{
		if (m_gravity != 0.0f)
		{
			Coord3D force;
			force.x = 0.0f;
			force.y = 0.0f;
			force.z = m_gravity;
			p->applyForce(&force);
		}
		if (p->update() == false)
		{
			oldParticle = p;
			p = p->m_systemNext;
			oldParticle->deleteInstance();
		}
		else
			p = p->m_systemNext;
	}
	if (m_isDestroyed && !m_systemParticlesHead)
		return false;
	if (m_isForever == false)
	{
		if (m_systemLifetimeLeft)
			m_systemLifetimeLeft--;
		if (getParticleCount())
			return true;
		if (m_systemLifetimeLeft == 0)
			return false;
	}
	return true;
}

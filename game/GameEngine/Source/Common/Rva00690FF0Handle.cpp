// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc

class Gen0002857E
{
public:
	void handle();
	void release();
};

class Rva00690FF0Handle
{
public:
	Rva00690FF0Handle(Gen0002857E *target);

	Gen0002857E *m_target;
};

Rva00690FF0Handle::Rva00690FF0Handle(Gen0002857E *target)
{
	m_target = target;
	if (target)
		target->handle();
}

class Rva006910F0Handle
{
public:
	Rva006910F0Handle(Gen0002857E *target);

	Gen0002857E *m_target;
};

Rva006910F0Handle::Rva006910F0Handle(Gen0002857E *target)
{
	m_target = target;
	if (target)
		target->handle();
}

class Rva00691110Handle
{
public:
	Rva00691110Handle(const Rva00691110Handle &other);

	Gen0002857E *m_target;
};

Rva00691110Handle::Rva00691110Handle(const Rva00691110Handle &other)
{
	Gen0002857E *target = other.m_target;
	m_target = target;
	if (target)
		target->handle();
}

class Rva00691040Handle
{
public:
	Rva00691040Handle &operator=(const Rva00691040Handle &other);

	Gen0002857E *m_target;
};

Rva00691040Handle &Rva00691040Handle::operator=(const Rva00691040Handle &other)
{
	Gen0002857E *target = other.m_target;
	Gen0002857E *old = m_target;
	m_target = target;
	if (target)
		target->handle();
	if (old)
		old->release();
	return *this;
}

class Rva00691140Handle
{
public:
	Rva00691140Handle &operator=(const Rva00691140Handle &other);

	Gen0002857E *m_target;
};

Rva00691140Handle &Rva00691140Handle::operator=(const Rva00691140Handle &other)
{
	Gen0002857E *target = other.m_target;
	Gen0002857E *old = m_target;
	m_target = target;
	if (target)
		target->handle();
	if (old)
		old->release();
	return *this;
}

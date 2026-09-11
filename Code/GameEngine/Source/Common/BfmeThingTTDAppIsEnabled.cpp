// Open-BFME7: Windows XP firewall authorized-application query.

typedef unsigned short *BSTR;
typedef short VARIANT_BOOL;
typedef long HRESULT;

extern "C" __declspec(dllimport) BSTR __stdcall SysAllocString(const unsigned short *value);
extern "C" __declspec(dllimport) unsigned int __stdcall SysStringLen(BSTR value);
extern "C" __declspec(dllimport) void __stdcall SysFreeString(BSTR value);
extern "C" void _ReadWriteBarrier();
#pragma intrinsic(_ReadWriteBarrier)

struct BfmeComObject;

typedef HRESULT (__stdcall *BfmeRelease)(BfmeComObject *self);
typedef HRESULT (__stdcall *BfmeGetAuthorizedApplications)(BfmeComObject *self,
	BfmeComObject **applications);
typedef HRESULT (__stdcall *BfmeAuthorizedApplicationItem)(BfmeComObject *self,
	BSTR imageFileName, BfmeComObject **application);
typedef HRESULT (__stdcall *BfmeGetEnabled)(BfmeComObject *self,
	VARIANT_BOOL *enabled);

struct BfmeComVtable
{
	void *m_00[2];
	BfmeRelease release;                         // IUnknown::Release, +0x08
	void *m_0c[7];
	BfmeAuthorizedApplicationItem item;          // collection::Item, +0x28
	void *m_2c[6];
	BfmeGetEnabled getEnabled;                   // application::get_Enabled, +0x44
	void *m_48[2];
	BfmeGetAuthorizedApplications getApplications; // profile::get_AuthorizedApplications, +0x50
};

struct BfmeComObject
{
	BfmeComVtable *vtable;
};

class BfmeThingTTD
{
public:
	bool applicationIsEnabled();

private:
	const unsigned short *m_name;
	const unsigned short *m_imageFileName;
	bool m_initialized;
	bool m_enabled;
	bool m_added;
	char m_pad0b;
	HRESULT m_comResult;
	BfmeComObject *m_profile;
};

bool BfmeThingTTD::applicationIsEnabled()
{
	BfmeComObject *application = 0;
	BfmeComObject *applications = 0;
	VARIANT_BOOL enabled;
	m_enabled = false;

	HRESULT result = m_profile->vtable->getApplications(m_profile, &applications);
	if (result < 0)
	{
		if (applications != 0)
			applications->vtable->release(applications);
		return false;
	}

	BSTR imageFileName = SysAllocString(m_imageFileName);
	if (SysStringLen(imageFileName) == 0)
	{
		if (applications != 0)
			applications->vtable->release(applications);
		_ReadWriteBarrier();
		return false;
	}

	result = applications->vtable->item(applications, imageFileName, &application);
	if (result >= 0)
	{
		result = application->vtable->getEnabled(application, &enabled);
		if (result < 0 || enabled == 0)
		{
			if (application != 0)
				application->vtable->release(application);
			if (applications != 0)
				applications->vtable->release(applications);
			SysFreeString(imageFileName);
			return false;
		}

		m_enabled = true;
		_ReadWriteBarrier();
	}

	SysFreeString(imageFileName);
	if (application != 0)
		application->vtable->release(application);
	if (applications != 0)
		applications->vtable->release(applications);
	return m_enabled;
}

// This is a part of the Active Template Library.
// Copyright (C) Microsoft Corporation
// All rights reserved.
//
// This source code is only intended as a supplement to the
// Active Template Library Reference and related
// electronic documentation provided with the library.
// See these sources for detailed information regarding the
// Active Template Library product.
#ifndef __ATLSECURITY_H__
#define __ATLSECURITY_H__

#pragma once

#include <sddl.h>
#include <userenv.h>
#include <aclapi.h>
#include <atlcoll.h>
#include <atlstr.h>

#pragma warning(push)
#pragma warning(disable: 4625) // copy constructor could not be generated because a base class copy constructor is inaccessible
#pragma warning(disable: 4626) // assignment operator could not be generated because a base class assignment operator is inaccessible

#ifndef _CPPUNWIND
#pragma warning (disable : 4702)	// unreachable code
#endif

namespace ATL
{
#pragma comment(lib, "userenv.lib")

class CSid
{

public:
	CSid() throw();

	explicit CSid(LPCTSTR pszAccountName, LPCTSTR pszSystem = NULL) throw(...);
	explicit CSid(const SID *pSid, LPCTSTR pszSystem = NULL) throw(...);
	CSid(const SID_IDENTIFIER_AUTHORITY &IdentifierAuthority, BYTE nSubAuthorityCount, ...) throw(...);
	virtual ~CSid() throw() {free(m_pSid);}

	CSid(const CSid &rhs) throw(...);
	CSid &operator=(const CSid &rhs) throw(...);

	CSid(const SID &rhs) throw(...);
	CSid &operator=(const SID &rhs) throw(...);

	typedef CAtlArray<CSid> CSidArray;

	bool LoadAccount(LPCTSTR pszAccountName, LPCTSTR pszSystem = NULL) throw(...);
	bool LoadAccount(const SID *pSid, LPCTSTR pszSystem = NULL) throw(...);

	LPCTSTR AccountName() const throw(...);
	LPCTSTR Domain() const throw(...);
	LPCTSTR Sid() const throw(...);

	const SID *GetPSID() const throw(...) {return m_pSid;}
	operator const SID *() const throw(...) {return GetPSID();}
	SID_NAME_USE SidNameUse() const throw() {return m_sidnameuse;}

	UINT GetLength() const throw()
		{ATLASSERT(IsValid()); return ::GetLengthSid(m_pSid);}

	// SID functions
	bool operator==(const CSid &rhs) const throw()
	{
		if (m_pSid == NULL || rhs.m_pSid == NULL || !IsValid() || !rhs.IsValid())
		{
			return FALSE;
		}
		return 0 != ::EqualSid(m_pSid, rhs.m_pSid);
	}
	bool operator==(const SID &rhs) const throw()
	{
		if (m_pSid == NULL || !IsValid() || !::IsValidSid(const_cast<SID *>(&rhs)))
		{
			return FALSE;
		}
		return 0 != ::EqualSid(m_pSid, const_cast<SID *>(&rhs));
	}

	bool EqualPrefix(const CSid &rhs) const throw()
	{
		if (m_pSid == NULL || rhs.m_pSid == NULL || !IsValid() || !rhs.IsValid())
		{
			return FALSE;
		}
		return 0 != ::EqualPrefixSid(m_pSid, rhs.m_pSid);
	}
	bool EqualPrefix(const SID &rhs) const throw()
	{
		if (m_pSid == NULL || !IsValid() || !::IsValidSid(const_cast<SID *>(&rhs)))
		{
			return FALSE;
		}
		return 0 != ::EqualPrefixSid(m_pSid, const_cast<SID *>(&rhs));
	}

	const SID_IDENTIFIER_AUTHORITY *GetPSID_IDENTIFIER_AUTHORITY() const throw()
		{ATLASSERT(IsValid()); return ::GetSidIdentifierAuthority(m_pSid);}
	DWORD GetSubAuthority(DWORD nSubAuthority) const throw()
		{ATLASSERT(IsValid()); return *::GetSidSubAuthority(m_pSid, nSubAuthority);}
	UCHAR GetSubAuthorityCount() const throw()
		{ATLASSERT(IsValid()); return *::GetSidSubAuthorityCount(m_pSid);}
	bool IsValid() const throw() {return 0 != ::IsValidSid(m_pSid);}

private:
	void Copy(const SID &rhs) throw(...);
	void Clear() throw();
	void GetAccountNameAndDomain() const throw(...);

	SID *m_pSid;

	mutable SID_NAME_USE m_sidnameuse;
	mutable CString m_strAccountName;
	mutable CString m_strDomain;
	mutable CString m_strSid;

	CString m_strSystem;
};

// Well-known sids
namespace Sids
{
__declspec(selectany) extern const SID_IDENTIFIER_AUTHORITY
SecurityNullSidAuthority		= SECURITY_NULL_SID_AUTHORITY,
SecurityWorldSidAuthority		= SECURITY_WORLD_SID_AUTHORITY,
SecurityLocalSidAuthority		= SECURITY_LOCAL_SID_AUTHORITY,
SecurityCreatorSidAuthority		= SECURITY_CREATOR_SID_AUTHORITY,
SecurityNonUniqueAuthority		= SECURITY_NON_UNIQUE_AUTHORITY,
SecurityNTAuthority				= SECURITY_NT_AUTHORITY;

// Universal
inline CSid Null() throw(...)
{
	return CSid(SecurityNullSidAuthority, 1, SECURITY_NULL_RID);
}
inline CSid World() throw(...)
{
	return CSid(SecurityWorldSidAuthority, 1, SECURITY_WORLD_RID);
}
inline CSid Local() throw(...)
{
	return CSid(SecurityLocalSidAuthority, 1, SECURITY_LOCAL_RID);
}
inline CSid CreatorOwner() throw(...)
{
	return CSid(SecurityCreatorSidAuthority, 1, SECURITY_CREATOR_OWNER_RID);
}
inline CSid CreatorGroup() throw(...)
{
	return CSid(SecurityCreatorSidAuthority, 1, SECURITY_CREATOR_GROUP_RID);
}
inline CSid CreatorOwnerServer() throw(...)
{
	return CSid(SecurityCreatorSidAuthority, 1, SECURITY_CREATOR_OWNER_SERVER_RID);
}
inline CSid CreatorGroupServer() throw(...)
{
	return CSid(SecurityCreatorSidAuthority, 1, SECURITY_CREATOR_GROUP_SERVER_RID);
}

// NT Authority
inline CSid Dialup() throw(...)
{
	return CSid(SecurityNTAuthority, 1, SECURITY_DIALUP_RID);
}
inline CSid Network() throw(...)
{
	return CSid(SecurityNTAuthority, 1, SECURITY_NETWORK_RID);
}
inline CSid Batch() throw(...)
{
	return CSid(SecurityNTAuthority, 1, SECURITY_BATCH_RID);
}
inline CSid Interactive() throw(...)
{
	return CSid(SecurityNTAuthority, 1, SECURITY_INTERACTIVE_RID);
}
inline CSid Service() throw(...)
{
	return CSid(SecurityNTAuthority, 1, SECURITY_SERVICE_RID);
}
inline CSid AnonymousLogon() throw(...)
{
	return CSid(SecurityNTAuthority, 1, SECURITY_ANONYMOUS_LOGON_RID);
}
inline CSid Proxy() throw(...)
{
	return CSid(SecurityNTAuthority, 1, SECURITY_PROXY_RID);
}
inline CSid ServerLogon() throw(...)
{
	return CSid(SecurityNTAuthority, 1, SECURITY_SERVER_LOGON_RID);
}
inline CSid Self() throw(...)
{
	return CSid(SecurityNTAuthority, 1, SECURITY_PRINCIPAL_SELF_RID);
}
inline CSid AuthenticatedUser() throw(...)
{
	return CSid(SecurityNTAuthority, 1, SECURITY_AUTHENTICATED_USER_RID);
}
inline CSid RestrictedCode() throw(...)
{
	return CSid(SecurityNTAuthority, 1, SECURITY_RESTRICTED_CODE_RID);
}
inline CSid TerminalServer() throw(...)
{
	return CSid(SecurityNTAuthority, 1, SECURITY_TERMINAL_SERVER_RID);
}
inline CSid System() throw(...)
{
	return CSid(SecurityNTAuthority, 1, SECURITY_LOCAL_SYSTEM_RID);
}

// NT Authority\BUILTIN
inline CSid Admins() throw(...)
{
	return CSid(SecurityNTAuthority, 2, SECURITY_BUILTIN_DOMAIN_RID, DOMAIN_ALIAS_RID_ADMINS);
}
inline CSid Users() throw(...)
{
	return CSid(SecurityNTAuthority, 2, SECURITY_BUILTIN_DOMAIN_RID, DOMAIN_ALIAS_RID_USERS);
}
inline CSid Guests() throw(...)
{
	return CSid(SecurityNTAuthority, 2, SECURITY_BUILTIN_DOMAIN_RID, DOMAIN_ALIAS_RID_GUESTS);
}
inline CSid PowerUsers() throw(...)
{
	return CSid(SecurityNTAuthority, 2, SECURITY_BUILTIN_DOMAIN_RID, DOMAIN_ALIAS_RID_POWER_USERS);
}
inline CSid AccountOps() throw(...)
{
	return CSid(SecurityNTAuthority, 2, SECURITY_BUILTIN_DOMAIN_RID, DOMAIN_ALIAS_RID_ACCOUNT_OPS);
}
inline CSid SystemOps() throw(...)
{
	return CSid(SecurityNTAuthority, 2, SECURITY_BUILTIN_DOMAIN_RID, DOMAIN_ALIAS_RID_SYSTEM_OPS);
}
inline CSid PrintOps() throw(...)
{
	return CSid(SecurityNTAuthority, 2, SECURITY_BUILTIN_DOMAIN_RID, DOMAIN_ALIAS_RID_PRINT_OPS);
}
inline CSid BackupOps() throw(...)
{
	return CSid(SecurityNTAuthority, 2, SECURITY_BUILTIN_DOMAIN_RID, DOMAIN_ALIAS_RID_BACKUP_OPS);
}
inline CSid Replicator() throw(...)
{
	return CSid(SecurityNTAuthority, 2, SECURITY_BUILTIN_DOMAIN_RID, DOMAIN_ALIAS_RID_REPLICATOR);
}
inline CSid RasServers() throw(...)
{
	return CSid(SecurityNTAuthority, 2, SECURITY_BUILTIN_DOMAIN_RID, DOMAIN_ALIAS_RID_RAS_SERVERS);
}
inline CSid PreW2KAccess() throw(...)
{
	return CSid(SecurityNTAuthority, 2, SECURITY_BUILTIN_DOMAIN_RID, DOMAIN_ALIAS_RID_PREW2KCOMPACCESS);
}
} // namespace Sids

inline CSid::CSid() throw()
	: m_pSid(NULL), m_sidnameuse(SidTypeInvalid)
{
}

inline CSid::CSid(LPCTSTR pszAccountName, LPCTSTR pszSystem) throw(...)
	: m_pSid(NULL), m_sidnameuse(SidTypeInvalid)
{
	if(!LoadAccount(pszAccountName, pszSystem))
		AtlThrowLastWin32();
}

inline CSid::CSid(const SID *pSid, LPCTSTR pszSystem) throw(...)
	: m_pSid(NULL), m_sidnameuse(SidTypeInvalid)
{
	if(!LoadAccount(pSid, pszSystem))
		AtlThrowLastWin32();
}

inline CSid::CSid(const SID_IDENTIFIER_AUTHORITY &IdentifierAuthority,
				  BYTE nSubAuthorityCount, ...) throw(...)
				  : m_pSid(NULL), m_sidnameuse(SidTypeInvalid)
{
	SID *pSid;

	ATLASSERT(nSubAuthorityCount);
	if(!nSubAuthorityCount)
		AtlThrow(E_INVALIDARG);

	USES_ATL_SAFE_ALLOCA;
	pSid = static_cast<SID *>(_ATL_SAFE_ALLOCA(::GetSidLengthRequired(nSubAuthorityCount), _ATL_SAFE_ALLOCA_DEF_THRESHOLD));
	if (pSid == NULL)
		AtlThrow(E_OUTOFMEMORY);

	if(!::InitializeSid(pSid,
		const_cast<SID_IDENTIFIER_AUTHORITY *>(&IdentifierAuthority),
		nSubAuthorityCount))
	{
		AtlThrowLastWin32();
	}

	va_list args;
	va_start(args, nSubAuthorityCount);
	for(UINT i = 0; i < nSubAuthorityCount; i++)
		*::GetSidSubAuthority(pSid, i) = va_arg(args, DWORD);
	va_end(args);

	Copy(*pSid);

	m_sidnameuse = SidTypeUnknown;
}

inline CSid::CSid(const CSid &rhs) throw(...)
	: m_sidnameuse(rhs.m_sidnameuse), m_pSid(NULL),
		m_strAccountName(rhs.m_strAccountName), m_strDomain(rhs.m_strDomain),
		m_strSid(rhs.m_strSid)
{
	if(!rhs.IsValid())
		AtlThrow(E_INVALIDARG);

	DWORD dwLengthSid = ::GetLengthSid(rhs.m_pSid);
	m_pSid = static_cast<SID *>(malloc(dwLengthSid));
	if(!m_pSid)
		AtlThrow(E_OUTOFMEMORY);

	if(!::CopySid(dwLengthSid, m_pSid, rhs.m_pSid))
	{
		HRESULT hr = AtlHresultFromLastError();
		free(m_pSid);
		AtlThrow(hr);
	}
}

inline CSid &CSid::operator=(const CSid &rhs) throw(...)
{
	if(this != &rhs)
	{
		if(!rhs.IsValid())
			AtlThrow(E_INVALIDARG);

		m_sidnameuse = rhs.m_sidnameuse;
		m_strAccountName = rhs.m_strAccountName;
		m_strDomain = rhs.m_strDomain;
		m_strSid = rhs.m_strSid;

		free(m_pSid);

		DWORD dwLengthSid = ::GetLengthSid(rhs.m_pSid);
		m_pSid = static_cast<SID *>(malloc(dwLengthSid));
		if(!m_pSid)
			AtlThrow(E_OUTOFMEMORY);

		if(!::CopySid(dwLengthSid, m_pSid, rhs.m_pSid))
		{
			HRESULT hr = AtlHresultFromLastError();
			free(m_pSid);
			m_pSid = NULL;
			AtlThrow(hr);
		}
	}
	return *this;
}

inline CSid::CSid(const SID &rhs) throw(...)
	: m_pSid(NULL), m_sidnameuse(SidTypeInvalid)
{
	Copy(rhs);
}

inline CSid &CSid::operator=(const SID &rhs) throw(...)
{
	if(m_pSid != &rhs)
	{
		Clear();
		Copy(rhs);

		m_sidnameuse = SidTypeUnknown;
	}
	return *this;
}

inline bool CSid::LoadAccount(LPCTSTR pszAccountName, LPCTSTR pszSystem) throw(...)
{
	ATLASSERT(pszAccountName);
	if (!pszAccountName)
		return false;

	static const DWORD dwSidSize = offsetof(SID, SubAuthority) + SID_MAX_SUB_AUTHORITIES * sizeof(DWORD);
	static const DWORD dwDomainSize = 128; // seems reasonable
	CTempBuffer<BYTE, dwSidSize> buffSid;
	CTempBuffer<TCHAR, dwDomainSize> buffDomain;
	// these two allocations just assign the static buffer.
	buffSid.Allocate(dwSidSize);
	buffDomain.Allocate(dwDomainSize);

	SID *pSid = reinterpret_cast<SID *>(static_cast<BYTE*>(buffSid));
	TCHAR *szDomain = static_cast<TCHAR *>(buffDomain);
	DWORD cbSid = dwSidSize, cbDomain = dwDomainSize;


	BOOL bSuccess = ::LookupAccountName(pszSystem, pszAccountName, pSid, &cbSid, szDomain, &cbDomain, &m_sidnameuse);
	if (!bSuccess)
	{
		if (::GetLastError() == ERROR_INSUFFICIENT_BUFFER)
		{
			// We could have gotten the insufficient buffer error because 
			// one or both of pSid and szDomain was too small. Check for that
			// here.
			if (cbSid > dwSidSize)
			{
				// Failed because sid was too small, reallocate it.
				buffSid.Reallocate(cbSid);
				pSid = reinterpret_cast<SID *>(static_cast<BYTE*>(buffSid));
			}

			if (cbDomain > dwDomainSize)
			{
				// Failed because domain was not big enough, reallocate it.
				buffDomain.Reallocate(cbDomain);
				szDomain = static_cast<TCHAR *>(buffDomain);
			}
			bSuccess = ::LookupAccountName(pszSystem, pszAccountName, pSid, &cbSid, szDomain, &cbDomain, &m_sidnameuse);
		}
	}

	if (bSuccess)
	{
		// LookupAccountName doesn't change cbSid on success (although it changes cbDomain)
		cbSid = ::GetLengthSid(pSid);
		free(m_pSid);
		m_pSid = static_cast<SID *>(malloc(cbSid));
		if (!m_pSid)
			AtlThrow(E_OUTOFMEMORY);

		if (::CopySid(cbSid, m_pSid, pSid))
		{
			m_strDomain = szDomain;
			m_strAccountName = pszAccountName;
			m_strSystem = pszSystem;
			return true;
		}
	}

	Clear();
	return false;
}

inline bool CSid::LoadAccount(const SID *pSid, LPCTSTR pszSystem) throw(...)
{
	ATLASSERT(pSid);
	if(pSid)
	{
		_ATLTRY
		{
			m_strSystem = pszSystem;
			Copy(*pSid);
			return true;
		}
		_ATLCATCHALL()
		{
			Clear();
			throw;
		}
	}
	return false;
}

inline LPCTSTR CSid::AccountName() const throw(...)
{
	if(m_strAccountName.IsEmpty())
		GetAccountNameAndDomain();
	return m_strAccountName;
}

inline LPCTSTR CSid::Domain() const throw(...)
{
	if(m_strDomain.IsEmpty())
		GetAccountNameAndDomain();
	return m_strDomain;
}

inline LPCTSTR CSid::Sid() const throw(...)
{
	_ATLTRY
	{
		if(m_strSid.IsEmpty())
		{
#if(_WIN32_WINNT >= 0x0500)
			LPTSTR pszSid;
			if(::ConvertSidToStringSid(m_pSid, &pszSid))
			{
				m_strSid = pszSid;
				::LocalFree(pszSid);
			}
#else
			SID_IDENTIFIER_AUTHORITY *psia = ::GetSidIdentifierAuthority(m_pSid);
			UINT i;

			if(psia->Value[0] || psia->Value[1])
			{
				m_strSid.Format(_T("S-%d-0x%02hx%02hx%02hx%02hx%02hx%02hx"), SID_REVISION,
					(USHORT)psia->Value[0],
					(USHORT)psia->Value[1],
					(USHORT)psia->Value[2],
					(USHORT)psia->Value[3],
					(USHORT)psia->Value[4],
					(USHORT)psia->Value[5]);
			}
			else
			{
				ULONG nAuthority = 0;
				for(i = 2; i < 6; i++)
				{
					nAuthority <<= 8;
					nAuthority |= psia->Value[i];
				}
				m_strSid.Format(_T("S-%d-%lu"), SID_REVISION, nAuthority);
			}

			UINT nSubAuthorityCount = *::GetSidSubAuthorityCount(m_pSid);
			CString strTemp;
			for(i = 0; i < nSubAuthorityCount; i++)
			{
				strTemp.Format(_T("-%lu"), *::GetSidSubAuthority(m_pSid, i));
				m_strSid += strTemp;
			}
#endif
		}
		return m_strSid;
	}
	_ATLCATCHALL()
	{
		m_strSid.Empty();
		throw;
	}
}

inline void CSid::Clear() throw()
{
	m_sidnameuse = SidTypeInvalid;
	m_strAccountName.Empty();
	m_strDomain.Empty();
	m_strSid.Empty();
	m_strSystem.Empty();

	free(m_pSid);
	m_pSid = NULL;
}

inline void CSid::Copy(const SID &rhs) throw(...)
{
	// This function assumes everything is cleaned up/initialized
	// (with the exception of m_strSystem).
	// It does some sanity checking to prevent memory leaks, but
	// you should clean up all members of CSid before calling this
	// function.  (i.e., results are unpredictable on error)

	ATLASSERT(m_sidnameuse == SidTypeInvalid);
	ATLASSERT(m_strAccountName.IsEmpty());
	ATLASSERT(m_strDomain.IsEmpty());
	ATLASSERT(m_strSid.IsEmpty());

	SID *p = const_cast<SID *>(&rhs);
	if(!::IsValidSid(p))
		AtlThrow(E_INVALIDARG);

	free(m_pSid);

	DWORD dwLengthSid = ::GetLengthSid(p);
	m_pSid = static_cast<SID *>(malloc(dwLengthSid));
	if(!m_pSid)
		AtlThrow(E_OUTOFMEMORY);

	if(!::CopySid(dwLengthSid, m_pSid, p))
	{
		HRESULT hr = AtlHresultFromLastError();
		free(m_pSid);
		m_pSid = NULL;
		AtlThrow(hr);
	}
}

inline void CSid::GetAccountNameAndDomain() const throw(...)
{
	static const DWORD dwMax = 32;
	DWORD cbName = dwMax, cbDomain = dwMax;
	TCHAR szName[dwMax], szDomain[dwMax];

	if(::LookupAccountSid(m_strSystem, m_pSid, szName, &cbName, szDomain, &cbDomain, &m_sidnameuse))
	{
		m_strAccountName = szName;
		m_strDomain = szDomain;
	}
	else
	{
		switch(::GetLastError())
		{
		case ERROR_INSUFFICIENT_BUFFER:
		{
			LPTSTR pszName = m_strAccountName.GetBuffer(cbName);
			LPTSTR pszDomain = m_strDomain.GetBuffer(cbDomain);

			if (!::LookupAccountSid(m_strSystem, m_pSid, pszName, &cbName, pszDomain, &cbDomain, &m_sidnameuse))
				AtlThrowLastWin32();

			m_strAccountName.ReleaseBuffer();
			m_strDomain.ReleaseBuffer();
			break;
		}

		case ERROR_NONE_MAPPED:
			m_strAccountName.Empty();
			m_strDomain.Empty();
			m_sidnameuse = SidTypeUnknown;
			break;

		default:
			ATLASSERT(FALSE);
		}
	}
}

//***************************************
// CAcl
//		CAce
//
//		CDacl
//			CAccessAce
//
//		CSacl
//			CAuditAce
//***************************************

// **************************************************************
// ACLs
class CAcl
{
public:
	CAcl() throw() : m_pAcl(NULL), m_bNull(false), m_dwAclRevision(ACL_REVISION){}
	virtual ~CAcl() throw() {free(m_pAcl);}

	CAcl(const CAcl &rhs) throw(...) : m_pAcl(NULL), m_bNull(rhs.m_bNull),
		m_dwAclRevision(rhs.m_dwAclRevision){}
	CAcl &operator=(const CAcl &rhs) throw(...)
	{
		if(this != &rhs)
		{
			free(m_pAcl);
			m_pAcl = NULL;
			m_bNull = rhs.m_bNull;
			m_dwAclRevision = rhs.m_dwAclRevision;
		}
		return *this;
	}

	typedef CAtlArray<ACCESS_MASK> CAccessMaskArray;
	typedef CAtlArray<BYTE> CAceTypeArray;
	typedef CAtlArray<BYTE> CAceFlagArray;

	void GetAclEntries(CSid::CSidArray *pSids, CAccessMaskArray *pAccessMasks = NULL,
		CAceTypeArray *pAceTypes = NULL, CAceFlagArray *pAceFlags = NULL) const throw(...);
	void GetAclEntry(UINT nIndex, CSid* pSid, ACCESS_MASK* pMask = NULL, BYTE* pType = NULL,
		BYTE* pFlags = NULL, GUID* pObjectType = NULL, GUID* pInheritedObjectType = NULL) throw(...);

	bool RemoveAces(const CSid &rSid) throw();

	virtual UINT GetAceCount() const throw() = 0;
	virtual void RemoveAllAces() throw() = 0;

	const ACL *GetPACL() const throw(...);
	operator const ACL *() const throw(...) {return GetPACL();}
	UINT GetLength() const throw(...);

	void SetNull() throw() {RemoveAllAces(); m_bNull = true;}
	void SetEmpty() throw() {RemoveAllAces(); m_bNull = false;}
	bool IsNull() const throw() {return m_bNull;}
	bool IsEmpty() const throw() {return !m_bNull && 0 == GetAceCount();}

private:
	mutable ACL *m_pAcl;
	bool m_bNull;

protected:
	void Dirty() throw() {free(m_pAcl); m_pAcl = NULL;}

	class CAce
	{
	public:
		CAce(const CSid &rSid, ACCESS_MASK accessmask, BYTE aceflags) throw(...)
			: m_dwAccessMask(accessmask), m_sid(rSid), m_aceflags(aceflags), m_pAce(NULL){}
		virtual ~CAce() throw() {free(m_pAce);}

		CAce(const CAce &rhs) throw(...) : m_sid(rhs.m_sid), m_dwAccessMask(rhs.m_dwAccessMask),
			m_aceflags(rhs.m_aceflags), m_pAce(NULL){}
		CAce &operator=(const CAce &rhs) throw(...)
		{
			if(this != &rhs)
			{
				m_sid = rhs.m_sid;
				m_dwAccessMask = rhs.m_dwAccessMask;
				m_aceflags = rhs.m_aceflags;
				free(m_pAce);
				m_pAce = NULL;
			}
			return *this;
		}

		virtual void *GetACE() const throw(...) = 0;
		virtual UINT GetLength() const throw() = 0;
		virtual BYTE AceType() const throw() = 0;
		virtual bool IsObjectAce() const throw() {return false;}
		virtual GUID ObjectType() const throw() { return GUID_NULL; }
		virtual GUID InheritedObjectType() const throw() { return GUID_NULL; }

		ACCESS_MASK AccessMask() const throw()
			{return m_dwAccessMask;}
		BYTE AceFlags() const throw()
			{return m_aceflags;}
		const CSid &Sid() const throw()
			{return m_sid;}

		void AddAccess(ACCESS_MASK accessmask) throw()
			{m_dwAccessMask |= accessmask; free(m_pAce); m_pAce = NULL;}

	protected:
		CSid m_sid;
		ACCESS_MASK m_dwAccessMask;
		BYTE m_aceflags;
		mutable void *m_pAce;
	};

	virtual const CAce *GetAce(UINT nIndex) const throw() = 0;
	virtual void RemoveAce(UINT nIndex) throw() = 0;

	virtual void PrepareAcesForACL() const throw() {}

	DWORD m_dwAclRevision;
};

inline const ACL *CAcl::GetPACL() const throw(...)
{
	if(!m_pAcl && !m_bNull)
	{
		UINT nAclLength = sizeof(ACL);
		const CAce *pAce;
		UINT i;
		const UINT nCount = GetAceCount();

		for(i = 0; i < nCount; i++)
		{
			pAce = GetAce(i);
			ATLASSERT(pAce);
			if(pAce)
				nAclLength += pAce->GetLength();
		}

		m_pAcl = static_cast<ACL *>(malloc(nAclLength));
		if(!m_pAcl)
			AtlThrow(E_OUTOFMEMORY);

		if(!::InitializeAcl(m_pAcl, (DWORD) nAclLength, m_dwAclRevision))
		{
			HRESULT hr = AtlHresultFromLastError();
			free(m_pAcl);
			m_pAcl = NULL;
			AtlThrow(hr);
		}
		else
		{
			PrepareAcesForACL();

			for(i = 0; i < nCount; i++)
			{
				pAce = GetAce(i);
				ATLASSERT(pAce);
				if(!pAce ||
					!::AddAce(m_pAcl, m_dwAclRevision, MAXDWORD, pAce->GetACE(), (DWORD) pAce->GetLength()))
				{
					HRESULT hr = AtlHresultFromLastError();
					free(m_pAcl);
					m_pAcl = NULL;
					AtlThrow(hr);
				}
			}
		}
	}
	return m_pAcl;
}

inline UINT CAcl::GetLength() const throw(...)
{
	ACL *pAcl = const_cast<ACL *>(GetPACL());
	ACL_SIZE_INFORMATION AclSize;

	ATLASSERT(pAcl);

	if(!::GetAclInformation(pAcl, &AclSize, sizeof(AclSize), AclSizeInformation))
		AtlThrowLastWin32();

	return AclSize.AclBytesInUse;
}

inline void CAcl::GetAclEntries(CSid::CSidArray *pSids, CAccessMaskArray *pAccessMasks,
								CAceTypeArray *pAceTypes, CAceFlagArray *pAceFlags) const throw(...)
{
	ATLASSERT(pSids);
	if(pSids)
	{
		pSids->RemoveAll();
		if(pAccessMasks)
			pAccessMasks->RemoveAll();
		if(pAceTypes)
			pAceTypes->RemoveAll();
		if(pAceFlags)
			pAceFlags->RemoveAll();

		const CAce *pAce;
		const UINT nCount = GetAceCount();
		for(UINT i = 0; i < nCount; i++)
		{
			pAce = GetAce(i);

			pSids->Add(pAce->Sid());
			if(pAccessMasks)
				pAccessMasks->Add(pAce->AccessMask());
			if(pAceTypes)
				pAceTypes->Add(pAce->AceType());
			if(pAceFlags)
				pAceFlags->Add(pAce->AceFlags());
		}
	}
}

inline void CAcl::GetAclEntry(
		UINT nIndex,
		CSid* pSid,
		ACCESS_MASK* pMask,
		BYTE* pType,
		BYTE* pFlags,
		GUID* pObjectType,
		GUID* pInheritedObjectType
		) throw(...)
{
	const CAce* pAce = GetAce(nIndex);

	if (pSid)
		*pSid = pAce->Sid();
	if (pMask)
		*pMask = pAce->AccessMask();
	if (pType)
		*pType = pAce->AceType();
	if (pFlags)
		*pFlags = pAce->AceFlags();
	if (pObjectType)
		*pObjectType = pAce->ObjectType();
	if (pInheritedObjectType)
		*pInheritedObjectType = pAce->InheritedObjectType();
}

inline bool CAcl::RemoveAces(const CSid &rSid) throw()
{
	ATLASSERT(rSid.IsValid());

	if(IsNull() || !rSid.IsValid())
		return false;

	bool bRet = false;
	const CAce *pAce;
	UINT nIndex = 0;

	while(nIndex < GetAceCount())
	{
		pAce = GetAce(nIndex);
		if(rSid == pAce->Sid())
		{
			RemoveAce(nIndex);
			bRet = true;
		}
		else
			nIndex++;
	}

	if(bRet)
		Dirty();

	return bRet;
}

// ************************************************
// CDacl
class CDacl : public CAcl
{
public:
	CDacl() throw() {}
	~CDacl() throw() {CDacl::RemoveAllAces();}

	CDacl(const ACL &rhs) throw(...) {Copy(rhs);}
	CDacl &operator=(const ACL &rhs) throw(...);

	bool AddAllowedAce(const CSid &rSid, ACCESS_MASK accessmask, BYTE aceflags = 0) throw(...);
	bool AddDeniedAce(const CSid &rSid, ACCESS_MASK accessmask, BYTE aceflags = 0) throw(...);
#if(_WIN32_WINNT >= 0x0500)
	bool AddAllowedAce(const CSid &rSid, ACCESS_MASK accessmask,  BYTE aceflags,
		const GUID *pObjectType, const GUID *pInheritedObjectType) throw(...);
	bool AddDeniedAce(const CSid &rSid, ACCESS_MASK accessmask, BYTE aceflags,
		const GUID *pObjectType, const GUID *pInheritedObjectType) throw(...);
#endif
	void RemoveAllAces() throw();

	UINT GetAceCount() const throw()
		{return (UINT) m_acl.GetCount();}

private:
	void Copy(const ACL &rhs) throw(...);

	class CAccessAce : public CAcl::CAce
	{
	public:
		CAccessAce(const CSid &rSid, ACCESS_MASK accessmask, BYTE aceflags, bool bAllowAccess) throw(...)
			: CAce(rSid, accessmask, aceflags), m_bAllow(bAllowAccess){}

		void *GetACE() const throw(...);
		UINT GetLength() const throw()
			{return offsetof(ACCESS_ALLOWED_ACE, SidStart) + m_sid.GetLength();}
		BYTE AceType() const throw()
			{return (BYTE)(m_bAllow ? ACCESS_ALLOWED_ACE_TYPE : ACCESS_DENIED_ACE_TYPE);}

		bool Allow() const throw() {return m_bAllow;}
		bool Inherited() const throw() {return 0 != (m_aceflags & INHERITED_ACE);}

		static bool Order(const CAccessAce &lhs, const CAccessAce &rhs) throw()
		{
			// The order is:
			// denied direct aces
			// denied direct object aces
			// allowed direct aces
			// allowed direct object aces
			// denied inherit aces
			// denied inherit object aces
			// allowed inherit aces
			// allowed inherit object aces

			// inherited aces are always "greater" than non-inherited aces
			if(lhs.Inherited() && !rhs.Inherited())
				return true;
			if(!lhs.Inherited() && rhs.Inherited())
				return false;

			// if the aces are *both* either inherited or non-inherited, continue...

			// allowed aces are always "greater" than denied aces (subject to above)
			if(lhs.Allow() && !rhs.Allow())
				return true;
			if(!lhs.Allow() && rhs.Allow())
				return false;

			// if the aces are *both* either allowed or denied, continue...

			// object aces are always "greater" than non-object aces (subject to above)
			if(lhs.IsObjectAce() && !rhs.IsObjectAce())
				return true;
			if(!lhs.IsObjectAce() && rhs.IsObjectAce())
				return false;

			// aces are "equal" (e.g., both are access denied inherited object aces)
			return false;
		}
	protected:
		bool m_bAllow;
	};

#if(_WIN32_WINNT >= 0x0500)
	class CAccessObjectAce : public CAccessAce
	{
	public:
		CAccessObjectAce(const CSid &rSid, ACCESS_MASK accessmask, BYTE aceflags, bool bAllowAccess,
			const GUID *pObjectType, const GUID *pInheritedObjectType) throw(...);
		~CAccessObjectAce() throw();

		CAccessObjectAce(const CAccessObjectAce &rhs) throw(...)
			: CAccessAce(rhs), m_pObjectType(NULL), m_pInheritedObjectType(NULL){*this = rhs;}
		CAccessObjectAce &operator=(const CAccessObjectAce &rhs) throw(...);

		void *GetACE() const throw(...);
		UINT GetLength() const throw();
		BYTE AceType() const throw()
			{return (BYTE)(m_bAllow ? ACCESS_ALLOWED_OBJECT_ACE_TYPE : ACCESS_DENIED_OBJECT_ACE_TYPE);}
		bool IsObjectAce() const throw() {return true;}
		virtual GUID ObjectType() const throw() { return m_pObjectType ? *m_pObjectType : GUID_NULL; }
		virtual GUID InheritedObjectType() const throw() { return m_pInheritedObjectType ? *m_pInheritedObjectType : GUID_NULL; }

	protected:
		GUID *m_pObjectType, *m_pInheritedObjectType;
	};

#endif
	const CAcl::CAce *GetAce(UINT nIndex) const throw()
		{return m_acl[nIndex];}
	void RemoveAce(UINT nIndex) throw();

	void PrepareAcesForACL() const throw();

	mutable CAutoPtrArray<CAccessAce> m_acl;
};

inline CDacl &CDacl::operator=(const ACL &rhs) throw(...)
{
	RemoveAllAces();

	Copy(rhs);
	return *this;
}

inline void CDacl::PrepareAcesForACL() const throw()
{
	// For a dacl, sort the aces
	size_t i, j, h = 1;
	const size_t nCount = m_acl.GetCount();
	CAutoPtr<CAccessAce> spAce;

	while(h * 3 + 1 < nCount)
		h = 3 * h + 1;

	while(h > 0)
	{
		for(i = h - 1; i < nCount; i++)
		{
			spAce = m_acl[i];

			for(j = i; j >= h && CAccessAce::Order(*m_acl[j - h], *spAce); j -= h)
				m_acl[j] = m_acl[j - h];

			m_acl[j] = spAce;
		}

		h /= 3;
	}
}

inline void CDacl::Copy(const ACL &rhs) throw(...)
{
	ACL *pAcl = const_cast<ACL *>(&rhs);
	ACL_SIZE_INFORMATION aclsizeinfo;
	ACE_HEADER *pHeader;
	CSid sid;
	ACCESS_MASK accessmask;
	CAutoPtr<CAccessAce> pAce;

	Dirty();

	if(!::GetAclInformation(pAcl, &aclsizeinfo, sizeof(aclsizeinfo), AclSizeInformation))
		AtlThrowLastWin32();

	for(DWORD i = 0; i < aclsizeinfo.AceCount; i++)
	{
		if(!::GetAce(pAcl, i, reinterpret_cast<void **>(&pHeader)))
			AtlThrowLastWin32();

		accessmask = *reinterpret_cast<ACCESS_MASK *>
			(reinterpret_cast<BYTE *>(pHeader) + sizeof(ACE_HEADER));

		switch(pHeader->AceType)
		{
		case ACCESS_ALLOWED_ACE_TYPE:
		case ACCESS_DENIED_ACE_TYPE:
			sid = *reinterpret_cast<SID *>
				(reinterpret_cast<BYTE *>(pHeader) + sizeof(ACE_HEADER) + sizeof(ACCESS_MASK));

			ATLTRY(pAce.Attach(new CAccessAce(sid, accessmask, pHeader->AceFlags,
				ACCESS_ALLOWED_ACE_TYPE == pHeader->AceType)));
			if (!pAce)
				AtlThrow(E_OUTOFMEMORY);
			m_acl.Add(pAce);
			break;

#if(_WIN32_WINNT >= 0x0500)
		case ACCESS_ALLOWED_OBJECT_ACE_TYPE:
		case ACCESS_DENIED_OBJECT_ACE_TYPE:
		{
			GUID *pObjectType = NULL, *pInheritedObjectType = NULL;
			BYTE *pb = reinterpret_cast<BYTE *>
				(pHeader) + offsetof(ACCESS_ALLOWED_OBJECT_ACE, SidStart);
			DWORD dwFlags = reinterpret_cast<ACCESS_ALLOWED_OBJECT_ACE *>(pHeader)->Flags;

			if(dwFlags & ACE_OBJECT_TYPE_PRESENT)
			{
				pObjectType = reinterpret_cast<GUID *>
					(reinterpret_cast<BYTE *>(pHeader) +
					offsetof(ACCESS_ALLOWED_OBJECT_ACE, ObjectType));
			}
			else
				pb -= sizeof(GUID);

			if(dwFlags & ACE_INHERITED_OBJECT_TYPE_PRESENT)
			{
				pInheritedObjectType = reinterpret_cast<GUID *>
					(reinterpret_cast<BYTE *>(pHeader) +
					(pObjectType ?
					offsetof(ACCESS_ALLOWED_OBJECT_ACE, InheritedObjectType) :
					offsetof(ACCESS_ALLOWED_OBJECT_ACE, ObjectType)));
			}
			else
				pb -= sizeof(GUID);

			sid = *reinterpret_cast<SID *>(pb);

			ATLTRY(pAce.Attach(new CAccessObjectAce(sid, accessmask, pHeader->AceFlags,
				ACCESS_ALLOWED_OBJECT_ACE_TYPE == pHeader->AceType,
				pObjectType, pInheritedObjectType)));
			if (!pAce)
				AtlThrow(E_OUTOFMEMORY);
			m_acl.Add(pAce);
			break;
		}
#endif

		default:
			// Wrong ACE type
			ATLASSERT(false);
		}
	}
}

inline bool CDacl::AddAllowedAce(const CSid &rSid, ACCESS_MASK accessmask, BYTE aceflags) throw(...)
{
	ATLASSERT(rSid.IsValid());
	if(!rSid.IsValid())
		return false;

	if (IsNull())
		SetEmpty();

	CAutoPtr<CAccessAce> pAce;
	ATLTRY(pAce.Attach(new CAccessAce(rSid, accessmask, aceflags, true)));
	if(!pAce)
		AtlThrow(E_OUTOFMEMORY);

	m_acl.Add(pAce);

	Dirty();
	return true;
}

#if(_WIN32_WINNT >= 0x0500)
inline bool CDacl::AddAllowedAce(const CSid &rSid, ACCESS_MASK accessmask, BYTE aceflags,
								 const GUID *pObjectType, const GUID *pInheritedObjectType) throw(...)
{
	if(!pObjectType && !pInheritedObjectType)
		return AddAllowedAce(rSid, accessmask, aceflags);

	ATLASSERT(rSid.IsValid());
	if(!rSid.IsValid())
		return false;

	if (IsNull())
		SetEmpty();

	CAutoPtr<CAccessAce> pAce;
	ATLTRY(pAce.Attach(new CAccessObjectAce(rSid, accessmask, aceflags, true,
		pObjectType, pInheritedObjectType)));
	if(!pAce)
		AtlThrow(E_OUTOFMEMORY);

	m_acl.Add(pAce);

	m_dwAclRevision = ACL_REVISION_DS;
	Dirty();
	return true;
}
#endif

inline bool CDacl::AddDeniedAce(const CSid &rSid, ACCESS_MASK accessmask, BYTE aceflags) throw(...)
{
	ATLASSERT(rSid.IsValid());
	if(!rSid.IsValid())
		return false;

	if (IsNull())
		SetEmpty();

	CAutoPtr<CAccessAce> pAce;
	ATLTRY(pAce.Attach(new CAccessAce(rSid, accessmask, aceflags, false)));
	if(!pAce)
		AtlThrow(E_OUTOFMEMORY);

	m_acl.Add(pAce);

	Dirty();
	return true;
}

#if(_WIN32_WINNT >= 0x0500)
inline bool CDacl::AddDeniedAce(const CSid &rSid, ACCESS_MASK accessmask, BYTE aceflags,
								const GUID *pObjectType, const GUID *pInheritedObjectType) throw(...)
{
	if(!pObjectType && !pInheritedObjectType)
		return AddDeniedAce(rSid, accessmask, aceflags);

	ATLASSERT(rSid.IsValid());
	if(!rSid.IsValid())
		return false;

	if (IsNull())
		SetEmpty();

	CAutoPtr<CAccessAce> pAce;
	ATLTRY(pAce.Attach(new CAccessObjectAce(rSid, accessmask, aceflags, false,
		pObjectType, pInheritedObjectType)));
	if(!pAce)
		AtlThrow(E_OUTOFMEMORY);

	m_acl.Add(pAce);

	m_dwAclRevision = ACL_REVISION_DS;
	Dirty();
	return true;
}
#endif

inline void CDacl::RemoveAllAces() throw()
{
	m_acl.RemoveAll();
	Dirty();
}

inline void CDacl::RemoveAce(UINT nIndex) throw()
{
	m_acl.RemoveAt(nIndex);
}

inline void *CDacl::CAccessAce::GetACE() const throw(...)
{
	C_ASSERT(sizeof(ACCESS_ALLOWED_ACE) == sizeof(ACCESS_DENIED_ACE));
	C_ASSERT(offsetof(ACCESS_ALLOWED_ACE, Header)==offsetof(ACCESS_DENIED_ACE, Header));
	C_ASSERT(offsetof(ACCESS_ALLOWED_ACE, Mask)==offsetof(ACCESS_DENIED_ACE, Mask));
	C_ASSERT(offsetof(ACCESS_ALLOWED_ACE, SidStart)==offsetof(ACCESS_DENIED_ACE, SidStart));

	if(!m_pAce)
	{
		UINT nLength = GetLength();
		ACCESS_ALLOWED_ACE *pAce = static_cast<ACCESS_ALLOWED_ACE *>(malloc(nLength));
		if(!pAce)
			AtlThrow(E_OUTOFMEMORY);

		memset(pAce, 0x00, nLength);

		pAce->Header.AceSize = static_cast<WORD>(nLength);
		pAce->Header.AceFlags = m_aceflags;
		pAce->Header.AceType = AceType();

		pAce->Mask = m_dwAccessMask;
		ATLASSERT(nLength-offsetof(ACCESS_ALLOWED_ACE, SidStart) >= m_sid.GetLength());
		memcpy(&pAce->SidStart, m_sid.GetPSID(), m_sid.GetLength());

		m_pAce = pAce;
	}
	return m_pAce;
}

#if(_WIN32_WINNT >= 0x0500)
inline CDacl::CAccessObjectAce::CAccessObjectAce(const CSid &rSid, ACCESS_MASK accessmask,
												 BYTE aceflags,  bool bAllowAccess,
												 const GUID *pObjectType,
												 const GUID *pInheritedObjectType) throw(...) :
	CAccessAce(rSid, accessmask, aceflags, bAllowAccess),
	m_pObjectType(NULL),
	m_pInheritedObjectType(NULL)
{
	if(pObjectType)
	{
		ATLTRY(m_pObjectType = new GUID(*pObjectType));
		if(!m_pObjectType)
			AtlThrow(E_OUTOFMEMORY);
	}

	if(pInheritedObjectType)
	{
		ATLTRY(m_pInheritedObjectType = new GUID(*pInheritedObjectType));
		if(!m_pInheritedObjectType)
		{
			delete m_pObjectType;
			m_pObjectType = NULL;
			AtlThrow(E_OUTOFMEMORY);
		}
	}
}

inline CDacl::CAccessObjectAce::~CAccessObjectAce() throw()
{
	delete m_pObjectType;
	delete m_pInheritedObjectType;
}

inline CDacl::CAccessObjectAce &CDacl::CAccessObjectAce::operator=(const CAccessObjectAce &rhs) throw(...)
{
	if(this != &rhs)
	{
		CAccessAce::operator=(rhs);

		if(rhs.m_pObjectType)
		{
			if(!m_pObjectType)
			{
				ATLTRY(m_pObjectType = new GUID);
				if(!m_pObjectType)
					AtlThrow(E_OUTOFMEMORY);
			}
			*m_pObjectType = *rhs.m_pObjectType;
		}
		else
		{
			delete m_pObjectType;
			m_pObjectType = NULL;
		}

		if(rhs.m_pInheritedObjectType)
		{
			if(!m_pInheritedObjectType)
			{
				ATLTRY(m_pInheritedObjectType = new GUID);
				if(!m_pInheritedObjectType)
				{
					delete m_pObjectType;
					m_pObjectType = NULL;
					AtlThrow(E_OUTOFMEMORY);
				}
			}
			*m_pInheritedObjectType = *rhs.m_pInheritedObjectType;
		}
		else
		{
			delete m_pInheritedObjectType;
			m_pInheritedObjectType = NULL;
		}
	}
	return *this;
}

inline UINT CDacl::CAccessObjectAce::GetLength() const throw()
{
	UINT nLength = offsetof(ACCESS_ALLOWED_OBJECT_ACE, SidStart);

	if(!m_pObjectType)
		nLength -= sizeof(GUID);
	if(!m_pInheritedObjectType)
		nLength -= sizeof(GUID);

	nLength += m_sid.GetLength();

	return nLength;
}

inline void *CDacl::CAccessObjectAce::GetACE() const throw(...)
{
	C_ASSERT(sizeof(ACCESS_ALLOWED_OBJECT_ACE) == sizeof(ACCESS_DENIED_OBJECT_ACE));
	C_ASSERT(offsetof(ACCESS_ALLOWED_OBJECT_ACE, Header)==offsetof(ACCESS_DENIED_OBJECT_ACE, Header));
	C_ASSERT(offsetof(ACCESS_ALLOWED_OBJECT_ACE, Mask)==offsetof(ACCESS_DENIED_OBJECT_ACE, Mask));
	C_ASSERT(offsetof(ACCESS_ALLOWED_OBJECT_ACE, Flags)==offsetof(ACCESS_DENIED_OBJECT_ACE, Flags));
	C_ASSERT(offsetof(ACCESS_ALLOWED_OBJECT_ACE, ObjectType)==offsetof(ACCESS_DENIED_OBJECT_ACE, ObjectType));
	C_ASSERT(offsetof(ACCESS_ALLOWED_OBJECT_ACE, InheritedObjectType)==offsetof(ACCESS_DENIED_OBJECT_ACE, InheritedObjectType));
	C_ASSERT(offsetof(ACCESS_ALLOWED_OBJECT_ACE, SidStart)==offsetof(ACCESS_DENIED_OBJECT_ACE, SidStart));

	if(!m_pAce)
	{
		UINT nLength = GetLength();

		ACCESS_ALLOWED_OBJECT_ACE *pAce = static_cast<ACCESS_ALLOWED_OBJECT_ACE *>(malloc(nLength));
		if(!pAce)
			AtlThrow(E_OUTOFMEMORY);

		memset(pAce, 0x00, nLength);

		pAce->Header.AceSize = static_cast<WORD>(nLength);
		pAce->Header.AceFlags = m_aceflags;
		pAce->Header.AceType = AceType();

		pAce->Mask = m_dwAccessMask;
		pAce->Flags = 0;

		BYTE *pb = (reinterpret_cast<BYTE *>(pAce)) + offsetof(ACCESS_ALLOWED_OBJECT_ACE, SidStart);
		if(!m_pObjectType)
			pb -= sizeof(GUID);
		else
		{
			pAce->ObjectType = *m_pObjectType;
			pAce->Flags |= ACE_OBJECT_TYPE_PRESENT;
		}

		if(!m_pInheritedObjectType)
			pb -= sizeof(GUID);
		else
		{
			if(m_pObjectType)
				pAce->InheritedObjectType = *m_pInheritedObjectType;
			else
				pAce->ObjectType = *m_pInheritedObjectType;
			pAce->Flags |= ACE_INHERITED_OBJECT_TYPE_PRESENT;
		}
		ATLASSERT(UINT(pb - reinterpret_cast<BYTE *>(pAce)) >= m_sid.GetLength());
		memcpy(pb, m_sid.GetPSID(), m_sid.GetLength());
		m_pAce = pAce;
	}
	return m_pAce;
}
#endif // _WIN32_WINNT

//******************************************
// CSacl
class CSacl : public CAcl
{
public:
	CSacl() throw() {}
	~CSacl() throw() {CSacl::RemoveAllAces();}

	CSacl(const ACL &rhs) throw(...) {Copy(rhs);}
	CSacl &operator=(const ACL &rhs) throw(...);

	bool AddAuditAce(const CSid &rSid, ACCESS_MASK accessmask,
		bool bSuccess, bool bFailure, BYTE aceflags = 0) throw(...);
#if(_WIN32_WINNT >= 0x0500)
	bool AddAuditAce(const CSid &rSid, ACCESS_MASK accessmask,
		bool bSuccess, bool bFailure, BYTE aceflags,
		const GUID *pObjectType, const GUID *pInheritedObjectType) throw(...);
#endif
	void RemoveAllAces() throw();

	UINT GetAceCount() const throw()
		{return (UINT) m_acl.GetCount();}

private:
	void Copy(const ACL &rhs) throw(...);

	class CAuditAce : public CAcl::CAce
	{
	public:
		CAuditAce(const CSid &rSid, ACCESS_MASK accessmask, BYTE aceflags,
			bool bAuditSuccess, bool bAuditFailure) throw(...)
			: CAce(rSid, accessmask, aceflags),
			m_bSuccess(bAuditSuccess), m_bFailure(bAuditFailure){}

		void *GetACE() const throw(...);
		UINT GetLength() const throw()
			{return offsetof(SYSTEM_AUDIT_ACE, SidStart) + m_sid.GetLength();}
		BYTE AceType() const throw()
			{return SYSTEM_AUDIT_ACE_TYPE;}

	protected:
		bool m_bSuccess, m_bFailure;
	};

#if(_WIN32_WINNT >= 0x0500)
	class CAuditObjectAce : public CAuditAce
	{
	public:
		CAuditObjectAce(const CSid &rSid, ACCESS_MASK accessmask, BYTE aceflags,
			bool bAuditSuccess, bool bAuditFailure,
			const GUID *pObjectType, const GUID *pInheritedObjectType) throw(...);
		~CAuditObjectAce() throw();

		CAuditObjectAce(const CAuditObjectAce &rhs) throw(...)
			: CAuditAce(rhs), m_pObjectType(NULL), m_pInheritedObjectType(NULL){*this = rhs;}
		CAuditObjectAce &operator=(const CAuditObjectAce &rhs) throw(...);

		void *GetACE() const throw(...);
		UINT GetLength() const throw();
		BYTE AceType() const throw()
			{return SYSTEM_AUDIT_OBJECT_ACE_TYPE;}
		bool IsObjectAce() const throw() {return true;}
		virtual GUID ObjectType() const throw() { return m_pObjectType ? *m_pObjectType : GUID_NULL; }
		virtual GUID InheritedObjectType() const throw() { return m_pInheritedObjectType ? *m_pInheritedObjectType : GUID_NULL; }

	protected:
		GUID *m_pObjectType, *m_pInheritedObjectType;
	};
#endif
	const CAce *GetAce(UINT nIndex) const throw()
		{return m_acl[nIndex];}
	void RemoveAce(UINT nIndex) throw();

	CAutoPtrArray<CAuditAce> m_acl;
};

inline CSacl &CSacl::operator=(const ACL &rhs) throw(...)
{
	RemoveAllAces();

	Copy(rhs);
	return *this;
}

inline void CSacl::Copy(const ACL &rhs) throw(...)
{
	ACL *pAcl = const_cast<ACL *>(&rhs);
	ACL_SIZE_INFORMATION aclsizeinfo;
	ACE_HEADER *pHeader;
	CSid sid;
	ACCESS_MASK accessmask;
	bool bSuccess, bFailure;
	CAutoPtr<CAuditAce> pAce;

	Dirty();

	if(!::GetAclInformation(pAcl, &aclsizeinfo, sizeof(aclsizeinfo), AclSizeInformation))
		AtlThrowLastWin32();

	for(DWORD i = 0; i < aclsizeinfo.AceCount; i++)
	{
		if(!::GetAce(pAcl, i, reinterpret_cast<void **>(&pHeader)))
			AtlThrowLastWin32();

		accessmask = *reinterpret_cast<ACCESS_MASK *>
			(reinterpret_cast<BYTE *>(pHeader) + sizeof(ACE_HEADER));

		bSuccess = 0 != (pHeader->AceFlags & SUCCESSFUL_ACCESS_ACE_FLAG);
		bFailure = 0 != (pHeader->AceFlags & FAILED_ACCESS_ACE_FLAG);

		switch(pHeader->AceType)
		{
		case SYSTEM_AUDIT_ACE_TYPE:
			sid = *reinterpret_cast<SID *>
				(reinterpret_cast<BYTE *>(pHeader) +	sizeof(ACE_HEADER) + sizeof(ACCESS_MASK));
			ATLTRY(pAce.Attach(new CAuditAce(sid, accessmask, pHeader->AceFlags, bSuccess, bFailure)));
			if (!pAce)
				AtlThrow(E_OUTOFMEMORY);
			m_acl.Add(pAce);
			break;

#if(_WIN32_WINNT >= 0x0500)
		case SYSTEM_AUDIT_OBJECT_ACE_TYPE:
		{
			GUID *pObjectType = NULL, *pInheritedObjectType = NULL;
			BYTE *pb = reinterpret_cast<BYTE *>
				(pHeader) + offsetof(SYSTEM_AUDIT_OBJECT_ACE, SidStart);
			DWORD dwFlags = reinterpret_cast<SYSTEM_AUDIT_OBJECT_ACE *>(pHeader)->Flags;

			if(dwFlags & ACE_OBJECT_TYPE_PRESENT)
			{
				pObjectType = reinterpret_cast<GUID *>
					(reinterpret_cast<BYTE *>(pHeader) +
					offsetof(SYSTEM_AUDIT_OBJECT_ACE, ObjectType));
			}
			else
				pb -= sizeof(GUID);

			if(dwFlags & ACE_INHERITED_OBJECT_TYPE_PRESENT)
			{
				pInheritedObjectType = reinterpret_cast<GUID *>
					(reinterpret_cast<BYTE *>(pHeader) +
					(pObjectType ?
					offsetof(SYSTEM_AUDIT_OBJECT_ACE, InheritedObjectType) :
					offsetof(SYSTEM_AUDIT_OBJECT_ACE, ObjectType)));
			}
			else
				pb -= sizeof(GUID);

			sid = *reinterpret_cast<SID *>(pb);

			ATLTRY(pAce.Attach(new CAuditObjectAce(sid, accessmask, pHeader->AceFlags,
				bSuccess, bFailure, pObjectType, pInheritedObjectType)));
			if(!pAce)
				AtlThrow(E_OUTOFMEMORY);
			m_acl.Add(pAce);
			break;
		}
#endif
		default:
			// Wrong ACE type
			ATLASSERT(false);
		}
	}
}

inline bool CSacl::AddAuditAce(const CSid &rSid, ACCESS_MASK accessmask,
							   bool bSuccess, bool bFailure, BYTE aceflags) throw(...)
{
	ATLASSERT(rSid.IsValid());
	if(!rSid.IsValid())
		return false;

	if (IsNull())
		SetEmpty();

	CAutoPtr<CAuditAce> pAce;
	ATLTRY(pAce.Attach(new CAuditAce(rSid, accessmask, aceflags, bSuccess, bFailure)))
	if(!pAce)
		AtlThrow(E_OUTOFMEMORY);

	m_acl.Add(pAce);

	Dirty();
	return true;
}

#if(_WIN32_WINNT >= 0x0500)
inline bool CSacl::AddAuditAce(const CSid &rSid, ACCESS_MASK accessmask,
							   bool bSuccess, bool bFailure, BYTE aceflags,
							   const GUID *pObjectType, const GUID *pInheritedObjectType) throw(...)
{
	if(!pObjectType && !pInheritedObjectType)
		return AddAuditAce(rSid, accessmask, bSuccess, bFailure, aceflags);

	ATLASSERT(rSid.IsValid());
	if(!rSid.IsValid())
		return false;

	if (IsNull())
		SetEmpty();

	CAutoPtr<CAuditAce> pAce;
	ATLTRY(pAce.Attach(new CAuditObjectAce(rSid, accessmask, aceflags, bSuccess,
		bFailure, pObjectType, pInheritedObjectType)));
	if(!pAce)
		AtlThrow(E_OUTOFMEMORY);

	m_acl.Add(pAce);
	m_dwAclRevision = ACL_REVISION_DS;
	Dirty();
	return true;
}
#endif

inline void CSacl::RemoveAllAces() throw()
{
	m_acl.RemoveAll();
	Dirty();
}

inline void CSacl::RemoveAce(UINT nIndex) throw()
{
	m_acl.RemoveAt(nIndex);
}

inline void *CSacl::CAuditAce::GetACE() const throw(...)
{
	if(!m_pAce)
	{
		UINT nLength = GetLength();
		SYSTEM_AUDIT_ACE *pAce = static_cast<SYSTEM_AUDIT_ACE *>(malloc(nLength));
		if(!pAce)
			AtlThrow(E_OUTOFMEMORY);

		memset(pAce, 0x00, nLength);

		pAce->Header.AceSize = static_cast<WORD>(nLength);
		pAce->Header.AceFlags = m_aceflags;
		pAce->Header.AceType = AceType();;

		pAce->Mask = m_dwAccessMask;
		ATLASSERT(nLength-offsetof(SYSTEM_AUDIT_ACE, SidStart) >= m_sid.GetLength());
		memcpy(&pAce->SidStart, m_sid.GetPSID(), m_sid.GetLength());

		if(m_bSuccess)
			pAce->Header.AceFlags |= SUCCESSFUL_ACCESS_ACE_FLAG;
		else
			pAce->Header.AceFlags &= ~SUCCESSFUL_ACCESS_ACE_FLAG;

		if(m_bFailure)
			pAce->Header.AceFlags |= FAILED_ACCESS_ACE_FLAG;
		else
			pAce->Header.AceFlags &= ~FAILED_ACCESS_ACE_FLAG;

		m_pAce = pAce;
	}
	return m_pAce;
}

#if(_WIN32_WINNT >= 0x0500)
inline CSacl::CAuditObjectAce::CAuditObjectAce(const CSid &rSid, ACCESS_MASK accessmask, BYTE aceflags,
	bool bAuditSuccess, bool bAuditFailure, const GUID *pObjectType, const GUID *pInheritedObjectType) throw(...)
	: CAuditAce(rSid, accessmask, aceflags, bAuditSuccess, bAuditFailure)
{
	if(pObjectType)
	{
		ATLTRY(m_pObjectType = new GUID(*pObjectType));
		if(!m_pObjectType)
			AtlThrow(E_OUTOFMEMORY);
	}

	if(pInheritedObjectType)
	{
		ATLTRY(m_pInheritedObjectType = new GUID(*pInheritedObjectType));
		if(!m_pInheritedObjectType)
		{
			delete m_pObjectType;
			m_pObjectType = NULL;
			AtlThrow(E_OUTOFMEMORY);
		}
	}
}

inline CSacl::CAuditObjectAce::~CAuditObjectAce() throw()
{
	delete m_pObjectType;
	delete m_pInheritedObjectType;
}

inline CSacl::CAuditObjectAce &CSacl::CAuditObjectAce::operator=(const CAuditObjectAce &rhs) throw(...)
{
	if(this != &rhs)
	{
		CAuditAce::operator=(rhs);

		if(rhs.m_pObjectType)
		{
			if(!m_pObjectType)
			{
				ATLTRY(m_pObjectType = new GUID);
				if(!m_pObjectType)
					AtlThrow(E_OUTOFMEMORY);
			}
			*m_pObjectType = *rhs.m_pObjectType;
		}
		else
		{
			delete m_pObjectType;
			m_pObjectType = NULL;
		}

		if(rhs.m_pInheritedObjectType)
		{
			if(!m_pInheritedObjectType)
			{
				ATLTRY(m_pInheritedObjectType = new GUID);
				if(!m_pInheritedObjectType)
				{
					delete m_pObjectType;
					m_pObjectType = NULL;
					AtlThrow(E_OUTOFMEMORY);
				}
			}
			*m_pInheritedObjectType = *rhs.m_pInheritedObjectType;
		}
		else
		{
			delete m_pInheritedObjectType;
			m_pInheritedObjectType = NULL;
		}
	}
	return *this;
}

inline UINT CSacl::CAuditObjectAce::GetLength() const throw()
{
	UINT nLength = offsetof(SYSTEM_AUDIT_OBJECT_ACE, SidStart);

	if(!m_pObjectType)
		nLength -= sizeof(GUID);
	if(!m_pInheritedObjectType)
		nLength -= sizeof(GUID);

	nLength += m_sid.GetLength();

	return nLength;
}

inline void *CSacl::CAuditObjectAce::GetACE() const throw(...)
{
	if(!m_pAce)
	{
		UINT nLength = GetLength();
		SYSTEM_AUDIT_OBJECT_ACE *pAce = static_cast<SYSTEM_AUDIT_OBJECT_ACE *>(malloc(nLength));
		if(!pAce)
			AtlThrow(E_OUTOFMEMORY);

		memset(pAce, 0x00, nLength);

		pAce->Header.AceType = SYSTEM_AUDIT_OBJECT_ACE_TYPE;
		pAce->Header.AceSize = static_cast<WORD>(nLength);
		pAce->Header.AceFlags = m_aceflags;

		pAce->Mask = m_dwAccessMask;
		pAce->Flags = 0;

		if(m_bSuccess)
			pAce->Header.AceFlags |= SUCCESSFUL_ACCESS_ACE_FLAG;
		else
			pAce->Header.AceFlags &= ~SUCCESSFUL_ACCESS_ACE_FLAG;

		if(m_bFailure)
			pAce->Header.AceFlags |= FAILED_ACCESS_ACE_FLAG;
		else
			pAce->Header.AceFlags &= ~FAILED_ACCESS_ACE_FLAG;

		BYTE *pb = ((BYTE *) pAce) + offsetof(SYSTEM_AUDIT_OBJECT_ACE, SidStart);
		if(!m_pObjectType)
			pb -= sizeof(GUID);
		else
		{
			pAce->ObjectType = *m_pObjectType;
			pAce->Flags |= ACE_OBJECT_TYPE_PRESENT;
		}

		if(!m_pInheritedObjectType)
			pb -= sizeof(GUID);
		else
		{
			if(m_pObjectType)
				pAce->InheritedObjectType = *m_pInheritedObjectType;
			else
				pAce->ObjectType = *m_pInheritedObjectType;
			pAce->Flags |= ACE_INHERITED_OBJECT_TYPE_PRESENT;
		}
		ATLASSERT(UINT(pb - reinterpret_cast<BYTE*>(pAce)) >= m_sid.GetLength());
		memcpy(pb, m_sid.GetPSID(), m_sid.GetLength());
		m_pAce = pAce;
	}
	return m_pAce;
}
#endif

//******************************************
// CSecurityDesc

class CSecurityDesc
{
public:
	CSecurityDesc() throw() : m_pSecurityDescriptor(NULL){}
	virtual ~CSecurityDesc() throw() {Clear();}

	CSecurityDesc(const CSecurityDesc &rhs) throw(...);
	CSecurityDesc &operator=(const CSecurityDesc &rhs) throw(...);

	CSecurityDesc(const SECURITY_DESCRIPTOR &rhs) throw(...);
	CSecurityDesc &operator=(const SECURITY_DESCRIPTOR &rhs) throw(...);

#if(_WIN32_WINNT >= 0x0500)
	bool FromString(LPCTSTR pstr) throw(...);
	bool ToString(CString *pstr,
		SECURITY_INFORMATION si =
		OWNER_SECURITY_INFORMATION | GROUP_SECURITY_INFORMATION |
		DACL_SECURITY_INFORMATION | SACL_SECURITY_INFORMATION) const throw(...);
#endif

	void SetOwner(const CSid &sid, bool bDefaulted = false) throw(...);
	void SetGroup(const CSid &sid, bool bDefaulted = false) throw(...);
	void SetDacl(const CDacl &Dacl, bool bDefaulted = false) throw(...);
	void SetDacl(bool bPresent, bool bDefaulted = false) throw(...);
	void SetSacl(const CSacl &Sacl, bool bDefaulted = false) throw(...);
	bool GetOwner(CSid *pSid, bool *pbDefaulted = NULL) const throw(...);
	bool GetGroup(CSid *pSid, bool *pbDefaulted = NULL) const throw(...);
	bool GetDacl(CDacl *pDacl, bool *pbPresent = NULL, bool *pbDefaulted = NULL) const throw(...);
	bool GetSacl(CSacl *pSacl, bool *pbPresent = NULL, bool *pbDefaulted = NULL) const throw(...);

	bool IsDaclDefaulted() const throw();
	bool IsDaclPresent() const throw();
	bool IsGroupDefaulted() const throw();
	bool IsOwnerDefaulted() const throw();
	bool IsSaclDefaulted() const throw();
	bool IsSaclPresent() const throw();
	bool IsSelfRelative() const throw();

	// Only meaningful on Win2k or better
	bool IsDaclAutoInherited() const throw();
	bool IsDaclProtected() const throw();
	bool IsSaclAutoInherited() const throw();
	bool IsSaclProtected() const throw();

	const SECURITY_DESCRIPTOR *GetPSECURITY_DESCRIPTOR() const throw()
		{return m_pSecurityDescriptor;}
	operator const SECURITY_DESCRIPTOR *() const throw() {return GetPSECURITY_DESCRIPTOR();}

	void GetSECURITY_DESCRIPTOR(SECURITY_DESCRIPTOR *pSD, LPDWORD lpdwBufferLength) throw(...);

	UINT GetLength() throw();

	bool GetControl(SECURITY_DESCRIPTOR_CONTROL *psdc) const throw();
#if(_WIN32_WINNT >= 0x0500)
	bool SetControl(SECURITY_DESCRIPTOR_CONTROL ControlBitsOfInterest,
		SECURITY_DESCRIPTOR_CONTROL ControlBitsToSet) throw();
#endif

	void MakeSelfRelative() throw(...);
	void MakeAbsolute() throw(...);

protected:
	virtual void Clear() throw();
	void AllocateAndInitializeSecurityDescriptor() throw(...);
	void Init(const SECURITY_DESCRIPTOR &rhs) throw(...);

	SECURITY_DESCRIPTOR *m_pSecurityDescriptor;
};

class CSecurityAttributes : public SECURITY_ATTRIBUTES
{
public:
	CSecurityAttributes() throw()
		{nLength = 0; lpSecurityDescriptor = NULL; bInheritHandle = FALSE;}
	explicit CSecurityAttributes(const CSecurityDesc &rSecurityDescriptor, bool bInheritHandle = false) throw(...) :
		m_SecurityDescriptor(rSecurityDescriptor)
	{
		Set(m_SecurityDescriptor, bInheritHandle);
	}

	void Set(const CSecurityDesc &rSecurityDescriptor, bool bInheritHandle = false) throw(...)
	{
		m_SecurityDescriptor = rSecurityDescriptor;
		nLength = sizeof(SECURITY_ATTRIBUTES);
		lpSecurityDescriptor = const_cast<SECURITY_DESCRIPTOR *>
			(m_SecurityDescriptor.GetPSECURITY_DESCRIPTOR());
		this->bInheritHandle = bInheritHandle;
	}

protected:
	CSecurityDesc m_SecurityDescriptor;
};

inline CSecurityDesc::CSecurityDesc(const CSecurityDesc &rhs) throw(...)
	: m_pSecurityDescriptor(NULL)
{
	if(rhs.m_pSecurityDescriptor)
		Init(*rhs.m_pSecurityDescriptor);
}

inline CSecurityDesc &CSecurityDesc::operator=(const CSecurityDesc &rhs) throw(...)
{
	if(this != &rhs)
	{
		Clear();
		if(rhs.m_pSecurityDescriptor)
			Init(*rhs.m_pSecurityDescriptor);
	}
	return *this;
}

inline CSecurityDesc::CSecurityDesc(const SECURITY_DESCRIPTOR &rhs) throw(...)
	: m_pSecurityDescriptor(NULL)
{
	Init(rhs);
}

inline CSecurityDesc &CSecurityDesc::operator=(const SECURITY_DESCRIPTOR &rhs) throw(...)
{
	if(m_pSecurityDescriptor != &rhs)
	{
		Clear();
		Init(rhs);
	}
	return *this;
}

inline void CSecurityDesc::Init(const SECURITY_DESCRIPTOR &rhs) throw(...)
{
	SECURITY_DESCRIPTOR *pSD = const_cast<SECURITY_DESCRIPTOR *>(&rhs);
	DWORD dwRev, dwLen = ::GetSecurityDescriptorLength(pSD);

	m_pSecurityDescriptor = static_cast<SECURITY_DESCRIPTOR *>(malloc(dwLen));
	if(!m_pSecurityDescriptor)
		AtlThrow(E_OUTOFMEMORY);

	SECURITY_DESCRIPTOR_CONTROL sdc;
	if(!::GetSecurityDescriptorControl(pSD, &sdc, &dwRev))
	{
		HRESULT hr = AtlHresultFromLastError();
		free(m_pSecurityDescriptor);
		m_pSecurityDescriptor = NULL;
		AtlThrow(hr);
	}

	if(sdc & SE_SELF_RELATIVE)
		memcpy(m_pSecurityDescriptor, pSD, dwLen);
	else
	{
		if(!::MakeSelfRelativeSD(pSD, m_pSecurityDescriptor, &dwLen))
		{
			HRESULT hr = AtlHresultFromLastError();
			free(m_pSecurityDescriptor);
			m_pSecurityDescriptor = NULL;
			AtlThrow(hr);
		}
	}
}

inline void CSecurityDesc::Clear() throw()
{
	if(m_pSecurityDescriptor)
	{
		SECURITY_DESCRIPTOR_CONTROL sdc;
		if(GetControl(&sdc) && !(sdc & SE_SELF_RELATIVE))
		{
			PSID pOwner, pGroup;
			ACL *pDacl, *pSacl;
			BOOL bDefaulted, bPresent;

			::GetSecurityDescriptorOwner(m_pSecurityDescriptor, &pOwner, &bDefaulted);
			free(pOwner);
			::GetSecurityDescriptorGroup(m_pSecurityDescriptor, &pGroup, &bDefaulted);
			free(pGroup);
			::GetSecurityDescriptorDacl(m_pSecurityDescriptor, &bPresent, &pDacl, &bDefaulted);
			if(bPresent)
				free(pDacl);
			::GetSecurityDescriptorSacl(m_pSecurityDescriptor, &bPresent, &pSacl, &bDefaulted);
			if(bPresent)
				free(pSacl);
		}
		free(m_pSecurityDescriptor);
		m_pSecurityDescriptor = NULL;
	}
}

inline void CSecurityDesc::MakeSelfRelative() throw(...)
{
	SECURITY_DESCRIPTOR_CONTROL sdc;
	if(!m_pSecurityDescriptor)
		return;

	if (!GetControl(&sdc))
		AtlThrow(E_FAIL);

	if(sdc & SE_SELF_RELATIVE)
		return;

	SECURITY_DESCRIPTOR *pSD;
	DWORD dwLen = 0;

	::MakeSelfRelativeSD(m_pSecurityDescriptor, NULL, &dwLen);
	if(::GetLastError() != ERROR_INSUFFICIENT_BUFFER)
		AtlThrowLastWin32();

	pSD = static_cast<SECURITY_DESCRIPTOR *>(malloc(dwLen));
	if(!pSD)
		AtlThrow(E_OUTOFMEMORY);

	if(!::MakeSelfRelativeSD(m_pSecurityDescriptor, pSD, &dwLen))
	{
		HRESULT hr = AtlHresultFromLastError();
		free(pSD);
		AtlThrow(hr);
	}

	Clear();
	m_pSecurityDescriptor = pSD;
}

inline void CSecurityDesc::MakeAbsolute() throw(...)
{
	SECURITY_DESCRIPTOR_CONTROL sdc;
	if(!m_pSecurityDescriptor)
		return;

	if (!GetControl(&sdc))
		AtlThrow(E_FAIL);;

	if(!(sdc & SE_SELF_RELATIVE))
		return;

	SECURITY_DESCRIPTOR *pSD;
	SID *pOwner, *pGroup;
	ACL *pDacl, *pSacl;
	DWORD dwSD, dwOwner, dwGroup, dwDacl, dwSacl;

	dwSD = dwOwner = dwGroup = dwDacl = dwSacl = 0;

	::MakeAbsoluteSD(m_pSecurityDescriptor, NULL, &dwSD, NULL, &dwDacl,
		NULL, &dwSacl, NULL, &dwOwner, NULL, &dwGroup);
	if(::GetLastError() != ERROR_INSUFFICIENT_BUFFER)
		AtlThrowLastWin32();

	pSD    = static_cast<SECURITY_DESCRIPTOR *>(malloc(dwSD));
	pOwner = static_cast<SID *>(dwOwner ? malloc(dwOwner) : NULL);
	pGroup = static_cast<SID *>(dwGroup ? malloc(dwGroup) : NULL);
	pDacl  = static_cast<ACL *>(dwDacl ? malloc(dwDacl) : NULL);
	pSacl  = static_cast<ACL *>(dwSacl ? malloc(dwSacl) : NULL);

	if(!::MakeAbsoluteSD(m_pSecurityDescriptor,
		pSD, &dwSD,
		pDacl, &dwDacl,
		pSacl, &dwSacl,
		pOwner, &dwOwner,
		pGroup, &dwGroup))
	{
		HRESULT hr = AtlHresultFromLastError();
		free(pSD);
		free(pOwner);
		free(pGroup);
		free(pDacl);
		free(pSacl);
		AtlThrow(hr);
	}

	Clear();
	m_pSecurityDescriptor = pSD;
}

inline void CSecurityDesc::AllocateAndInitializeSecurityDescriptor() throw(...)
{
	// m_pSecurityDescriptor should be NULL.
	ATLASSERT(!m_pSecurityDescriptor);

	m_pSecurityDescriptor = static_cast<SECURITY_DESCRIPTOR *>(malloc(sizeof(SECURITY_DESCRIPTOR)));
	if(!m_pSecurityDescriptor)
		AtlThrow(E_OUTOFMEMORY);

	if(!::InitializeSecurityDescriptor(m_pSecurityDescriptor, SECURITY_DESCRIPTOR_REVISION))
	{
		HRESULT hr = AtlHresultFromLastError();
		free(m_pSecurityDescriptor);
		m_pSecurityDescriptor = NULL;
		AtlThrow(hr);
	}
}

#if(_WIN32_WINNT >= 0x0500)
inline bool CSecurityDesc::FromString(LPCTSTR pstr) throw(...)
{
	SECURITY_DESCRIPTOR *pSD;
	if(!::ConvertStringSecurityDescriptorToSecurityDescriptor(pstr, SDDL_REVISION_1,
			(PSECURITY_DESCRIPTOR *) &pSD, NULL))
		AtlThrowLastWin32();

	*this = *pSD;
	::LocalFree(pSD);

	return true;
}

inline bool CSecurityDesc::ToString(CString *pstr, SECURITY_INFORMATION si) const throw(...)
{
	ATLASSERT(pstr);
	if(!pstr || !m_pSecurityDescriptor)
		return false;

	LPTSTR pszStringSecurityDescriptor;
	if(!::ConvertSecurityDescriptorToStringSecurityDescriptor(m_pSecurityDescriptor,
			SDDL_REVISION_1,
			si,
			&pszStringSecurityDescriptor,
			NULL))
		AtlThrowLastWin32();

	_ATLTRY
	{
		*pstr = pszStringSecurityDescriptor;
	}
	_ATLCATCHALL()
	{
		::LocalFree(pszStringSecurityDescriptor);
		throw;
	}

	::LocalFree(pszStringSecurityDescriptor);
	return true;
}
#endif

inline void CSecurityDesc::GetSECURITY_DESCRIPTOR(SECURITY_DESCRIPTOR *pSD, LPDWORD lpdwBufferLength) throw(...)
{
	ATLASSERT(lpdwBufferLength && m_pSecurityDescriptor);
	if(!lpdwBufferLength)
		AtlThrow(E_INVALIDARG);
	if (!m_pSecurityDescriptor)
		AtlThrow(E_UNEXPECTED);

	MakeAbsolute();

	if (!::MakeSelfRelativeSD(m_pSecurityDescriptor, pSD, lpdwBufferLength) &&
			(pSD || GetLastError() != ERROR_INSUFFICIENT_BUFFER))
		AtlThrowLastWin32();
}

inline UINT CSecurityDesc::GetLength() throw()
{
	return ::GetSecurityDescriptorLength(m_pSecurityDescriptor);
}

inline void CSecurityDesc::SetOwner(const CSid &sid, bool bDefaulted) throw(...)
{
	if(m_pSecurityDescriptor)
		MakeAbsolute();

	PSID pNewOwner, pOldOwner;
	if(m_pSecurityDescriptor)
	{
		BOOL _bDefaulted;
		if(!::GetSecurityDescriptorOwner(m_pSecurityDescriptor, &pOldOwner, &_bDefaulted))
			AtlThrowLastWin32();
	}
	else
	{
		AllocateAndInitializeSecurityDescriptor();
		pOldOwner = NULL;
	}

	if(!sid.IsValid())
		AtlThrow(E_FAIL);

	UINT nSidLength = sid.GetLength();
	pNewOwner = malloc(nSidLength);
	if(!pNewOwner)
		AtlThrow(E_OUTOFMEMORY);

	if(!::CopySid((DWORD) nSidLength, pNewOwner, const_cast<SID *>(sid.GetPSID())) ||
		!::SetSecurityDescriptorOwner(m_pSecurityDescriptor, pNewOwner, bDefaulted))
	{
		HRESULT hr = AtlHresultFromLastError();
		free(pNewOwner);
		AtlThrow(hr);
	}

	free(pOldOwner);
}

inline void CSecurityDesc::SetGroup(const CSid &sid, bool bDefaulted) throw(...)
{
	if(m_pSecurityDescriptor)
		MakeAbsolute();

	PSID pNewGroup, pOldGroup;
	if(m_pSecurityDescriptor)
	{
		BOOL _bDefaulted;
		if(!::GetSecurityDescriptorGroup(m_pSecurityDescriptor, &pOldGroup, &_bDefaulted))
			AtlThrowLastWin32();
	}
	else
	{
		AllocateAndInitializeSecurityDescriptor();
		pOldGroup = NULL;
	}

	if(!sid.IsValid())
		AtlThrow(E_FAIL);

	UINT nSidLength = sid.GetLength();
	pNewGroup = malloc(nSidLength);
	if(!pNewGroup)
		AtlThrow(E_OUTOFMEMORY);

	if(!::CopySid((DWORD) nSidLength, pNewGroup, const_cast<SID *>(sid.GetPSID())) ||
		!::SetSecurityDescriptorGroup(m_pSecurityDescriptor, pNewGroup, bDefaulted))
	{
		HRESULT hr = AtlHresultFromLastError();
		free(pNewGroup);
		AtlThrow(hr);
	}

	free(pOldGroup);
}

inline void CSecurityDesc::SetDacl(bool bPresent, bool bDefaulted) throw(...)
{
	if(m_pSecurityDescriptor)
		MakeAbsolute();

	PACL pOldDacl = NULL;
	if(m_pSecurityDescriptor)
	{
		BOOL _bDefaulted, _bPresent;
		if(!::GetSecurityDescriptorDacl(m_pSecurityDescriptor, &_bPresent, &pOldDacl, &_bDefaulted))
			AtlThrowLastWin32();
	}
	else
		AllocateAndInitializeSecurityDescriptor();

#ifdef _DEBUG
	if(bPresent)
	{
		// setting a NULL DACL is almost always the wrong thing to do
		ATLTRACE(atlTraceSecurity, 2, _T("Error: Setting Dacl to Null offers no security\n"));
		ATLASSERT(FALSE);
	}
#endif

	if(!::SetSecurityDescriptorDacl(m_pSecurityDescriptor, bPresent, NULL, bDefaulted))
		AtlThrowLastWin32();

	free(pOldDacl);
}

inline void CSecurityDesc::SetDacl(const CDacl &Dacl, bool bDefaulted) throw(...)
{
	if(m_pSecurityDescriptor)
		MakeAbsolute();

	PACL pNewDacl, pOldDacl = NULL;
	if(m_pSecurityDescriptor)
	{
		BOOL _bDefaulted, _bPresent;
		if(!::GetSecurityDescriptorDacl(m_pSecurityDescriptor, &_bPresent, &pOldDacl, &_bDefaulted))
			AtlThrowLastWin32();
	}
	else
		AllocateAndInitializeSecurityDescriptor();

	if(Dacl.IsNull() || Dacl.IsEmpty())
		pNewDacl = NULL;
	else
	{
		UINT nAclLength = Dacl.GetLength();
		ATLASSERT(nAclLength > 0);

		pNewDacl = static_cast<ACL *>(malloc(nAclLength));
		if(!pNewDacl)
			AtlThrow(E_OUTOFMEMORY);

		memcpy(pNewDacl, Dacl.GetPACL(), nAclLength);
	}

#ifdef _DEBUG
	if(Dacl.IsNull())
	{
		// setting a NULL DACL is almost always the wrong thing to do
		ATLTRACE(atlTraceSecurity, 2, _T("Error: Setting Dacl to Null offers no security\n"));
		ATLASSERT(FALSE);
	}
#endif

	if(!::SetSecurityDescriptorDacl(m_pSecurityDescriptor, Dacl.IsNull() || pNewDacl, pNewDacl, bDefaulted))
	{
		HRESULT hr = AtlHresultFromLastError();
		free(pNewDacl);
		AtlThrow(hr);
	}

	free(pOldDacl);
}

inline void CSecurityDesc::SetSacl(const CSacl &Sacl, bool bDefaulted) throw(...)
{
	if(m_pSecurityDescriptor)
		MakeAbsolute();

	PACL pNewSacl, pOldSacl = NULL;
	if(m_pSecurityDescriptor)
	{
		BOOL _bDefaulted, _bPresent;
		if(!::GetSecurityDescriptorSacl(m_pSecurityDescriptor, &_bPresent, &pOldSacl, &_bDefaulted))
			AtlThrowLastWin32();
	}
	else
		AllocateAndInitializeSecurityDescriptor();

	if(Sacl.IsNull() || Sacl.IsEmpty())
		pNewSacl = NULL;
	else
	{
		UINT nAclLength = Sacl.GetLength();
		ATLASSERT(nAclLength > 0);

		pNewSacl = static_cast<ACL *>(malloc(nAclLength));
		if(!pNewSacl)
			AtlThrow(E_OUTOFMEMORY);

		memcpy(pNewSacl, Sacl.GetPACL(), nAclLength);
	}

	if(!::SetSecurityDescriptorSacl(m_pSecurityDescriptor, Sacl.IsNull() || pNewSacl, pNewSacl, bDefaulted))
	{
		HRESULT hr = AtlHresultFromLastError();
		free(pNewSacl);
		AtlThrow(hr);
	}

	free(pOldSacl);
}

inline bool CSecurityDesc::GetOwner(CSid *pSid, bool *pbDefaulted) const throw(...)
{
	ATLASSERT(pSid);
	SID *pOwner;
	BOOL bDefaulted;

	if(!pSid || !m_pSecurityDescriptor ||
		!::GetSecurityDescriptorOwner(m_pSecurityDescriptor, (PSID *) &pOwner, &bDefaulted))
	{
		return false;
	}

	*pSid = *pOwner;

	if(pbDefaulted)
		*pbDefaulted = 0 != bDefaulted;

	return true;
}

inline bool CSecurityDesc::GetGroup(CSid *pSid, bool *pbDefaulted) const throw(...)
{
	ATLASSERT(pSid);
	SID *pGroup;
	BOOL bDefaulted;

	if(!pSid || !m_pSecurityDescriptor ||
		!::GetSecurityDescriptorGroup(m_pSecurityDescriptor, (PSID *) &pGroup, &bDefaulted))
	{
		return false;
	}

	*pSid = *pGroup;

	if(pbDefaulted)
		*pbDefaulted = 0 != bDefaulted;

	return true;
}

inline bool CSecurityDesc::GetDacl(CDacl *pDacl, bool *pbPresent, bool *pbDefaulted) const throw(...)
{
	ACL *pAcl;
	BOOL bPresent, bDefaulted;

	if(!m_pSecurityDescriptor ||
		!::GetSecurityDescriptorDacl(m_pSecurityDescriptor, &bPresent, &pAcl, &bDefaulted))
	{
		return false;
	}

	if(pDacl)
	{
		if(bPresent)
		{
			if(pAcl)
				*pDacl = *pAcl;
			else
				pDacl->SetNull();
		}
		else
			pDacl->SetEmpty();
	}

	if(pbPresent)
		*pbPresent = 0 != bPresent;

	if(pbDefaulted)
		*pbDefaulted = 0 != bDefaulted;

	return true;
}

inline bool CSecurityDesc::GetSacl(CSacl *pSacl, bool *pbPresent, bool *pbDefaulted) const throw(...)
{
	ACL *pAcl;
	BOOL bPresent, bDefaulted;

	if(!m_pSecurityDescriptor ||
		!::GetSecurityDescriptorSacl(m_pSecurityDescriptor, &bPresent, &pAcl, &bDefaulted))
	{
		return false;
	}

	if(pSacl)
	{
		if(bPresent)
		{
			if(pAcl)
				*pSacl = *pAcl;
			else
				pSacl->SetNull();
		}
		else
			pSacl->SetEmpty();
	}

	if(pbPresent)
		*pbPresent = 0 != bPresent;

	if(pbDefaulted)
		*pbDefaulted = 0 != bDefaulted;

	return true;
}

inline bool CSecurityDesc::IsDaclDefaulted() const throw()
{
	SECURITY_DESCRIPTOR_CONTROL sdc;
	if(!GetControl(&sdc))
		return false;

	return (sdc & SE_DACL_PRESENT) &&
		(sdc & SE_DACL_DEFAULTED);
}

inline bool CSecurityDesc::IsDaclPresent() const throw()
{
	SECURITY_DESCRIPTOR_CONTROL sdc;
	if(!GetControl(&sdc))
		return false;

	return 0 != (sdc & SE_DACL_PRESENT);
}

inline bool CSecurityDesc::IsGroupDefaulted() const throw()
{
	SECURITY_DESCRIPTOR_CONTROL sdc;
	if(!GetControl(&sdc))
		return false;

	return 0 != (sdc & SE_GROUP_DEFAULTED);
}

inline bool CSecurityDesc::IsOwnerDefaulted() const throw()
{
	SECURITY_DESCRIPTOR_CONTROL sdc;
	if(!GetControl(&sdc))
		return false;

	return (sdc & SE_OWNER_DEFAULTED);
}

inline bool CSecurityDesc::IsSaclDefaulted() const throw()
{
	SECURITY_DESCRIPTOR_CONTROL sdc;
	if(!GetControl(&sdc))
		return false;

	return (sdc & SE_SACL_PRESENT) &&
		(sdc & SE_SACL_DEFAULTED);
}

inline bool CSecurityDesc::IsSaclPresent() const throw()
{
	SECURITY_DESCRIPTOR_CONTROL sdc;
	if(!GetControl(&sdc))
		return false;

	return 0 != (sdc & SE_SACL_PRESENT);
}

inline bool CSecurityDesc::IsSelfRelative() const throw()
{
	SECURITY_DESCRIPTOR_CONTROL sdc;
	if(!GetControl(&sdc))
		return false;

	return 0 != (sdc & SE_SELF_RELATIVE);
}

inline bool CSecurityDesc::IsDaclAutoInherited() const throw()
{
	SECURITY_DESCRIPTOR_CONTROL sdc;
	if(!GetControl(&sdc))
		return false;

	return 0 != (sdc & SE_DACL_AUTO_INHERITED);
}

inline bool CSecurityDesc::IsDaclProtected() const throw()
{
	SECURITY_DESCRIPTOR_CONTROL sdc;
	if(!GetControl(&sdc))
		return false;

	return 0 != (sdc & SE_DACL_PROTECTED);
}

inline bool CSecurityDesc::IsSaclAutoInherited() const throw()
{
	SECURITY_DESCRIPTOR_CONTROL sdc;
	if(!GetControl(&sdc))
		return false;

	return 0 != (sdc & SE_SACL_AUTO_INHERITED);
}

inline bool CSecurityDesc::IsSaclProtected() const throw()
{
	SECURITY_DESCRIPTOR_CONTROL sdc;
	if(!GetControl(&sdc))
		return false;

	return 0 != (sdc & SE_SACL_PROTECTED);
}

inline bool CSecurityDesc::GetControl(SECURITY_DESCRIPTOR_CONTROL *psdc) const throw()
{
	ATLASSERT(psdc);
	if(!psdc)
		return false;

	DWORD dwRev;
	*psdc = 0;
	if(!m_pSecurityDescriptor ||
		!::GetSecurityDescriptorControl(m_pSecurityDescriptor, psdc, &dwRev))
	{
		return false;
	}
	return true;
}

#if(_WIN32_WINNT >= 0x0500)
inline bool CSecurityDesc::SetControl(SECURITY_DESCRIPTOR_CONTROL ControlBitsOfInterest,
									  SECURITY_DESCRIPTOR_CONTROL ControlBitsToSet) throw()
{
	ATLASSERT(m_pSecurityDescriptor);
	if (!m_pSecurityDescriptor)
		return false;

	return 0 != ::SetSecurityDescriptorControl(m_pSecurityDescriptor,
		ControlBitsOfInterest, ControlBitsToSet);
}
#endif

template<>
class CElementTraits< LUID > :
	public CElementTraitsBase< LUID >
{
public:
	typedef const LUID& INARGTYPE;
	typedef LUID& OUTARGTYPE;

	static ULONG Hash( INARGTYPE luid ) throw()
	{
		return luid.HighPart ^ luid.LowPart;
	}

	static BOOL CompareElements( INARGTYPE element1, INARGTYPE element2 ) throw()
	{
		return element1.HighPart == element2.HighPart && element1.LowPart == element2.LowPart;
	}

	static int CompareElementsOrdered( INARGTYPE element1, INARGTYPE element2 ) throw()
	{
		_LARGE_INTEGER li1, li2;
		li1.LowPart = element1.LowPart;
		li1.HighPart = element1.HighPart;
		li2.LowPart = element2.LowPart;
		li2.HighPart = element2.HighPart;

		if( li1.QuadPart > li2.QuadPart )
			return( 1 );
		else if( li1.QuadPart < li2.QuadPart )
			return( -1 );

		return( 0 );
	}
};

typedef CAtlArray<LUID> CLUIDArray;

//******************************************************
// CTokenPrivileges
class CTokenPrivileges
{
public:
	CTokenPrivileges() throw() : m_bDirty(true), m_pTokenPrivileges(NULL){}
	virtual ~CTokenPrivileges() throw() {free(m_pTokenPrivileges);}

	CTokenPrivileges(const CTokenPrivileges &rhs) throw(...);
	CTokenPrivileges &operator=(const CTokenPrivileges &rhs) throw(...);

	CTokenPrivileges(const TOKEN_PRIVILEGES &rPrivileges) throw(...) :
		m_pTokenPrivileges(NULL) {AddPrivileges(rPrivileges);}
	CTokenPrivileges &operator=(const TOKEN_PRIVILEGES &rPrivileges) throw(...)
		{m_mapTokenPrivileges.RemoveAll(); AddPrivileges(rPrivileges); return *this;}

	void Add(const TOKEN_PRIVILEGES &rPrivileges) throw(...)
		{AddPrivileges(rPrivileges);}
	bool Add(LPCTSTR pszPrivilege, bool bEnable) throw(...);

	typedef CAtlArray<CString> CNames;
	typedef CAtlArray<DWORD> CAttributes;

	bool LookupPrivilege(LPCTSTR pszPrivilege, DWORD *pdwAttributes = NULL) const throw(...);
	void GetNamesAndAttributes(CNames *pNames, CAttributes *pAttributes = NULL) const throw(...);
	void GetDisplayNames(CNames *pDisplayNames) const throw(...);
	void GetLuidsAndAttributes(CLUIDArray *pPrivileges, CAttributes *pAttributes = NULL) const throw(...);

	bool Delete(LPCTSTR pszPrivilege) throw();
	void DeleteAll() throw() {m_mapTokenPrivileges.RemoveAll(); m_bDirty = true;}

	UINT GetCount() const throw() {return (UINT) m_mapTokenPrivileges.GetCount();}

	UINT GetLength() const throw()
		{return offsetof(TOKEN_PRIVILEGES, Privileges) + sizeof(LUID_AND_ATTRIBUTES) * GetCount();}

	const TOKEN_PRIVILEGES *GetPTOKEN_PRIVILEGES() const throw(...);
	operator const TOKEN_PRIVILEGES *() const throw(...) {return GetPTOKEN_PRIVILEGES();}

private:
	typedef CAtlMap<LUID, DWORD> Map;
	Map m_mapTokenPrivileges;
	mutable TOKEN_PRIVILEGES *m_pTokenPrivileges;
	bool m_bDirty;

	void AddPrivileges(const TOKEN_PRIVILEGES &rPrivileges) throw(...);
};

inline CTokenPrivileges::CTokenPrivileges(const CTokenPrivileges &rhs) throw(...)
	: m_pTokenPrivileges(NULL), m_bDirty(true)
{
	const Map::CPair *pPair;
	POSITION pos = rhs.m_mapTokenPrivileges.GetStartPosition();
	while(pos)
	{
		pPair = rhs.m_mapTokenPrivileges.GetNext(pos);
		m_mapTokenPrivileges.SetAt(pPair->m_key, pPair->m_value);
	}
}

inline CTokenPrivileges &CTokenPrivileges::operator=(const CTokenPrivileges &rhs) throw(...)
{
	if(this != &rhs)
	{
		m_mapTokenPrivileges.RemoveAll();

		const Map::CPair *pPair;
		POSITION pos = rhs.m_mapTokenPrivileges.GetStartPosition();
		while(pos)
		{
			pPair = rhs.m_mapTokenPrivileges.GetNext(pos);
			m_mapTokenPrivileges.SetAt(pPair->m_key, pPair->m_value);
		}
		m_bDirty = true;
	}
	return *this;
}

inline bool CTokenPrivileges::Add(LPCTSTR pszPrivilege, bool bEnable) throw(...)
{
	LUID_AND_ATTRIBUTES la;
	if(!::LookupPrivilegeValue(NULL, pszPrivilege, &la.Luid))
		return false;

	la.Attributes = bEnable ? SE_PRIVILEGE_ENABLED : 0;

	m_mapTokenPrivileges.SetAt(la.Luid, la.Attributes);

	m_bDirty = true;
	return true;
}

inline bool CTokenPrivileges::Delete(LPCTSTR pszPrivilege) throw()
{
	LUID Luid;
	if(!::LookupPrivilegeValue(NULL, pszPrivilege, &Luid))
		return false;

	if(!m_mapTokenPrivileges.RemoveKey(Luid))
		return false;

	m_bDirty = true;
	return true;
}

inline const TOKEN_PRIVILEGES *CTokenPrivileges::GetPTOKEN_PRIVILEGES() const throw(...)
{
	if(m_bDirty)
	{
		free(m_pTokenPrivileges);
		m_pTokenPrivileges = NULL;

		if(m_mapTokenPrivileges.GetCount())
		{
			m_pTokenPrivileges = static_cast<TOKEN_PRIVILEGES *>(malloc(GetLength()));
			if(!m_pTokenPrivileges)
				AtlThrow(E_OUTOFMEMORY);

			m_pTokenPrivileges->PrivilegeCount = (DWORD) GetCount();

			UINT i = 0;
			POSITION pos = m_mapTokenPrivileges.GetStartPosition();
			const Map::CPair *pPair;
			while(pos)
			{
				pPair = m_mapTokenPrivileges.GetNext(pos);
				m_pTokenPrivileges->Privileges[i].Luid = pPair->m_key;
				m_pTokenPrivileges->Privileges[i].Attributes = pPair->m_value;

				i++;
			}
		}
	}
	return m_pTokenPrivileges;
}

inline void CTokenPrivileges::AddPrivileges(const TOKEN_PRIVILEGES &rPrivileges) throw(...)
{
	m_bDirty = true;
	for(UINT i = 0; i < rPrivileges.PrivilegeCount; i++)
		m_mapTokenPrivileges.SetAt(
			rPrivileges.Privileges[i].Luid, rPrivileges.Privileges[i].Attributes);
}

inline bool CTokenPrivileges::LookupPrivilege(LPCTSTR pszPrivilege, 
											  DWORD *pdwAttributes) const throw()
{
	DWORD dwAttributes;
	LUID luid;

	if(!::LookupPrivilegeValue(NULL, pszPrivilege, &luid))
		return false;

	if(m_mapTokenPrivileges.Lookup(luid, dwAttributes))
	{
		if(pdwAttributes)
			*pdwAttributes = dwAttributes;
		return true;
	}
	return false;
}

inline void CTokenPrivileges::GetNamesAndAttributes(CNames *pNames,
													CAttributes *pAttributes) const throw(...)
{
	ATLASSERT(pNames);
	if(pNames)
	{
		CAutoVectorPtr<TCHAR> psz;
		DWORD cbName = 0, cbTmp;
		const Map::CPair *pPair;

		pNames->RemoveAll();
		if(pAttributes)
			pAttributes->RemoveAll();

		POSITION pos = m_mapTokenPrivileges.GetStartPosition();
		while(pos)
		{
			pPair = m_mapTokenPrivileges.GetNext(pos);

			cbTmp = cbName;
			if(!::LookupPrivilegeName(NULL, const_cast<LUID *>(&pPair->m_key), psz, &cbTmp))
				if(::GetLastError() == ERROR_INSUFFICIENT_BUFFER)
				{
					psz.Free();
					if(!psz.Allocate(cbTmp + 1))
					{
						pNames->RemoveAll();
						if(pAttributes)
							pAttributes->RemoveAll();
						AtlThrow(E_OUTOFMEMORY);
					}

					cbName = cbTmp;
					if(!::LookupPrivilegeName(NULL, const_cast<LUID *>(&pPair->m_key), psz, &cbTmp))
						break;
				}
				else
					break;

			pNames->Add((LPTSTR) psz);
			if(pAttributes)
				pAttributes->Add(pPair->m_value);
		}

		if(pos)
		{
			pNames->RemoveAll();
			if(pAttributes)
				pAttributes->RemoveAll();
		}
	}
}

inline void CTokenPrivileges::GetDisplayNames(CNames *pDisplayNames) const throw(...)
{
	ATLASSERT(pDisplayNames);
	if(pDisplayNames)
	{
		DWORD dwLang, cbTmp, cbDisplayName = 0;
		CAutoVectorPtr<TCHAR> psz;
		CNames Names;
		UINT i;

		GetNamesAndAttributes(&Names);

		pDisplayNames->RemoveAll();

		for(i = 0; i < Names.GetCount(); i++)
		{
			cbTmp = cbDisplayName;
			if(!::LookupPrivilegeDisplayName(NULL, Names[i], psz, &cbTmp, &dwLang))
			{
				if(::GetLastError() == ERROR_INSUFFICIENT_BUFFER)
				{
					psz.Free();
					if(!psz.Allocate(cbTmp + 1))
					{
						pDisplayNames->RemoveAll();
						AtlThrow(E_OUTOFMEMORY);
					}

					cbDisplayName = cbTmp;
					if(!::LookupPrivilegeDisplayName(NULL, Names[i], psz, &cbTmp, &dwLang))
						break;
				}
				else
					break;
			}
			pDisplayNames->Add((LPTSTR) psz);
		}

		if(i != Names.GetCount())
			pDisplayNames->RemoveAll();
	}
}

inline void CTokenPrivileges::GetLuidsAndAttributes(CLUIDArray *pLuids,
													CAttributes *pAttributes) const throw(...)
{
	ATLASSERT(pLuids);
	if(pLuids)
	{
		const Map::CPair *pPair;

		pLuids->RemoveAll();
		if(pAttributes)
			pAttributes->RemoveAll();

		POSITION pos = m_mapTokenPrivileges.GetStartPosition();
		while(pos)
		{
			pPair = m_mapTokenPrivileges.GetNext(pos);
			pLuids->Add(pPair->m_key);
			if(pAttributes)
				pAttributes->Add(pPair->m_value);
		}
	}
}

//******************************************************
// CTokenGroups
class CTokenGroups
{
public:
	CTokenGroups() throw() : m_pTokenGroups(NULL), m_bDirty(true){}
	virtual ~CTokenGroups() throw() {free(m_pTokenGroups);}

	CTokenGroups(const CTokenGroups &rhs) throw(...);
	CTokenGroups &operator=(const CTokenGroups &rhs) throw(...);

	CTokenGroups(const TOKEN_GROUPS &rhs) throw(...) :
		m_pTokenGroups(NULL) {AddTokenGroups(rhs);}
	CTokenGroups &operator=(const TOKEN_GROUPS &rhs) throw(...)
		{m_mapTokenGroups.RemoveAll(); AddTokenGroups(rhs); return *this;}

	void Add(const TOKEN_GROUPS &rTokenGroups) throw(...)
		{AddTokenGroups(rTokenGroups);}
	void Add(const CSid &rSid, DWORD dwAttributes) throw(...)
		{m_mapTokenGroups.SetAt(rSid, dwAttributes); m_bDirty = true;}

	bool LookupSid(const CSid &rSid, DWORD *pdwAttributes = NULL) const throw();
	void GetSidsAndAttributes(CSid::CSidArray *pSids,
		CAtlArray<DWORD> *pAttributes = NULL) const throw(...);

	bool Delete(const CSid &rSid) throw() {return m_mapTokenGroups.RemoveKey(rSid);}
	void DeleteAll() throw() {m_mapTokenGroups.RemoveAll(); m_bDirty = true;}

	UINT GetCount() const throw() {return (UINT) m_mapTokenGroups.GetCount();}

	UINT GetLength() const throw()
		{return UINT(offsetof(TOKEN_GROUPS, Groups) +
			sizeof(SID_AND_ATTRIBUTES) * m_mapTokenGroups.GetCount());}

	const TOKEN_GROUPS *GetPTOKEN_GROUPS() const throw(...);
	operator const TOKEN_GROUPS *() const throw(...) {return GetPTOKEN_GROUPS();}

private:
	class CTGElementTraits : 
		public CElementTraitsBase< CSid >
	{
	public:
		static UINT Hash(const CSid &sid) throw()
			{return sid.GetSubAuthority(sid.GetSubAuthorityCount() - 1);}

		static bool CompareElements( INARGTYPE element1, INARGTYPE element2 ) throw()
		{
			return( element1 == element2 );
		}
	};

	typedef CAtlMap<CSid, DWORD, CTGElementTraits> Map;
	Map m_mapTokenGroups;
	mutable TOKEN_GROUPS *m_pTokenGroups;
	mutable bool m_bDirty;

	void AddTokenGroups(const TOKEN_GROUPS &rTokenGroups) throw(...);
};

inline CTokenGroups::CTokenGroups(const CTokenGroups &rhs) throw(...)
	: m_pTokenGroups(NULL), m_bDirty(true)
{
	const Map::CPair *pPair;
	POSITION pos = rhs.m_mapTokenGroups.GetStartPosition();
	while(pos)
	{
		pPair = rhs.m_mapTokenGroups.GetNext(pos);
		m_mapTokenGroups.SetAt(pPair->m_key, pPair->m_value);
	}
}

inline CTokenGroups &CTokenGroups::operator=(const CTokenGroups &rhs) throw(...)
{
	if(this != &rhs)
	{
		m_mapTokenGroups.RemoveAll();

		const Map::CPair *pPair;
		POSITION pos = rhs.m_mapTokenGroups.GetStartPosition();
		while(pos)
		{
			pPair = rhs.m_mapTokenGroups.GetNext(pos);
			m_mapTokenGroups.SetAt(pPair->m_key, pPair->m_value);
		}
		m_bDirty = true;
	}
	return *this;
}

inline const TOKEN_GROUPS *CTokenGroups::GetPTOKEN_GROUPS() const throw(...)
{
	if(m_bDirty)
	{
		free(m_pTokenGroups);
		m_pTokenGroups = NULL;

		if(m_mapTokenGroups.GetCount())
		{
			m_pTokenGroups = static_cast<TOKEN_GROUPS *>(malloc(GetLength()));
			if(!m_pTokenGroups)
				AtlThrow(E_OUTOFMEMORY);

			m_pTokenGroups->GroupCount = (DWORD) m_mapTokenGroups.GetCount();

			UINT i = 0;
			POSITION pos = m_mapTokenGroups.GetStartPosition();
			const Map::CPair *pPair;
			while(pos)
			{
				pPair = m_mapTokenGroups.GetNext(pos);
				m_pTokenGroups->Groups[i].Sid = const_cast<SID *>(pPair->m_key.GetPSID());
				m_pTokenGroups->Groups[i].Attributes = pPair->m_value;

				i++;
			}
		}
	}
	return m_pTokenGroups;
}

inline void CTokenGroups::AddTokenGroups(const TOKEN_GROUPS &rTokenGroups) throw(...)
{
	m_bDirty = true;
	for(UINT i = 0; i < rTokenGroups.GroupCount; i++)
		m_mapTokenGroups.SetAt(
			CSid(static_cast<SID *>(rTokenGroups.Groups[i].Sid)),
			rTokenGroups.Groups[i].Attributes);
}

inline bool CTokenGroups::LookupSid(const CSid &rSid, DWORD *pdwAttributes) const throw()
{
	DWORD dwAttributes;
	if(m_mapTokenGroups.Lookup(rSid, dwAttributes))
	{
		if(pdwAttributes)
			*pdwAttributes = dwAttributes;
		return true;
	}
	return false;
}

inline void CTokenGroups::GetSidsAndAttributes(CSid::CSidArray *pSids,
											   CAtlArray<DWORD> *pAttributes) const throw(...)
{
	ATLASSERT(pSids);
	if(pSids)
	{
		const Map::CPair *pPair;

		pSids->RemoveAll();
		if(pAttributes)
			pAttributes->RemoveAll();

		POSITION pos = m_mapTokenGroups.GetStartPosition();
		while(pos)
		{
			pPair = m_mapTokenGroups.GetNext(pos);
			pSids->Add(pPair->m_key);
			if(pAttributes)
				pAttributes->Add(pPair->m_value);
		}
	}
}

// *************************************
// CAccessToken
class CAccessToken
{
public:
	CAccessToken() throw() : m_hToken(NULL), m_hProfile(NULL), m_pRevert(NULL){}

	virtual ~CAccessToken() throw();

	void Attach(HANDLE hToken) throw();
	HANDLE Detach() throw()
		{HANDLE hToken = m_hToken; m_hToken = NULL; Clear(); return hToken;}
	HANDLE GetHandle() const throw() {return m_hToken;}
	HANDLE HKeyCurrentUser() const throw() {return m_hProfile;}

	// Privileges
	bool EnablePrivilege(LPCTSTR pszPrivilege, CTokenPrivileges *pPreviousState = NULL) throw(...);
	bool EnablePrivileges(const CAtlArray<LPCTSTR> &rPrivileges,
		CTokenPrivileges *pPreviousState = NULL) throw(...);
	bool DisablePrivilege(LPCTSTR pszPrivilege, CTokenPrivileges *pPreviousState = NULL) throw(...);
	bool DisablePrivileges(const CAtlArray<LPCTSTR> &rPrivileges, CTokenPrivileges *pPreviousState = NULL) throw(...);
	bool EnableDisablePrivileges(const CTokenPrivileges &rPrivilenges,
		CTokenPrivileges *pPreviousState = NULL) throw(...);
	bool PrivilegeCheck(PPRIVILEGE_SET RequiredPrivileges, bool *pbResult) const throw();

	bool GetLogonSid(CSid *pSid) const throw(...);
	bool GetTokenId(LUID *pluid) const throw(...);
	bool GetLogonSessionId(LUID *pluid) const throw(...);

	bool CheckTokenMembership(const CSid &rSid, bool *pbIsMember) const throw(...);
#if(_WIN32_WINNT >= 0x0500)
	bool IsTokenRestricted() const throw() {return 0 != ::IsTokenRestricted(m_hToken);}
#endif

	// Token Information
protected:
	template<typename RET_T, typename INFO_T>
	void InfoTypeToRetType(RET_T *pRet, const INFO_T &rWork) const throw(...)
		{ATLASSERT(pRet); *pRet = rWork;}
	template<>
	void InfoTypeToRetType(CDacl *pRet, const TOKEN_DEFAULT_DACL &rWork) const throw(...)
		{ATLASSERT(pRet); *pRet = *rWork.DefaultDacl;}
	template<>
	void InfoTypeToRetType(CSid *pRet, const TOKEN_OWNER &rWork) const throw(...)
		{ATLASSERT(pRet); *pRet = *static_cast<SID *>(rWork.Owner);}
	template<>
	void InfoTypeToRetType(CSid *pRet, const TOKEN_PRIMARY_GROUP &rWork) const throw(...)
		{ATLASSERT(pRet); *pRet = *static_cast<SID *>(rWork.PrimaryGroup);}
	template<>
	void InfoTypeToRetType(CSid *pRet, const TOKEN_USER &rWork) const throw(...)
		{ATLASSERT(pRet); *pRet = *static_cast<SID *>(rWork.User.Sid);}

	template<typename RET_T, typename INFO_T>
	bool GetInfoConvert(RET_T *pRet, TOKEN_INFORMATION_CLASS TokenClass, INFO_T *pWork = NULL) const throw(...)
	{
		ATLASSERT(pRet);
		if(!pRet)
			return false;

		DWORD dwLen;
		::GetTokenInformation(m_hToken, TokenClass, NULL, 0, &dwLen);
		if(::GetLastError() != ERROR_INSUFFICIENT_BUFFER)
			return false;
		
		USES_ATL_SAFE_ALLOCA;
		pWork = static_cast<INFO_T *>(_ATL_SAFE_ALLOCA(dwLen, _ATL_SAFE_ALLOCA_DEF_THRESHOLD));
		if (pWork == NULL)
			return false;
		if(!::GetTokenInformation(m_hToken, TokenClass, pWork, dwLen, &dwLen))
			return false;

		InfoTypeToRetType(pRet, *pWork);
		return true;
	}

	template<typename RET_T>
	bool GetInfo(RET_T *pRet, TOKEN_INFORMATION_CLASS TokenClass) const throw(...)
	{
		ATLASSERT(pRet);
		if(!pRet)
			return false;

		DWORD dwLen;
		if(!::GetTokenInformation(m_hToken, TokenClass, pRet, sizeof(RET_T), &dwLen))
			return false;
		return true;
	}

public:
	bool GetDefaultDacl(CDacl *pDacl) const throw(...)
		{return GetInfoConvert<CDacl, TOKEN_DEFAULT_DACL>(pDacl, TokenDefaultDacl);}
	bool GetGroups(CTokenGroups *pGroups) const throw(...)
		{return GetInfoConvert<CTokenGroups, TOKEN_GROUPS>(pGroups, TokenGroups);}
	bool GetImpersonationLevel(SECURITY_IMPERSONATION_LEVEL *pImpersonationLevel) const throw(...)
		{return GetInfo<SECURITY_IMPERSONATION_LEVEL>(pImpersonationLevel, TokenImpersonationLevel);}
	bool GetOwner(CSid *pSid) const throw(...)
		{return GetInfoConvert<CSid, TOKEN_OWNER>(pSid, TokenOwner);}
	bool GetPrimaryGroup(CSid *pSid) const throw(...)
		{return GetInfoConvert<CSid, TOKEN_PRIMARY_GROUP>(pSid, TokenPrimaryGroup);}
	bool GetPrivileges(CTokenPrivileges *pPrivileges) const throw(...)
		{return GetInfoConvert<CTokenPrivileges, TOKEN_PRIVILEGES>(pPrivileges, TokenPrivileges);}
	bool GetTerminalServicesSessionId(DWORD *pdwSessionId) const throw(...)
		{return GetInfo<DWORD>(pdwSessionId, TokenSessionId);}
	bool GetSource(TOKEN_SOURCE *pSource) const throw(...)
		{return GetInfo<TOKEN_SOURCE>(pSource, TokenSource);}
	bool GetStatistics(TOKEN_STATISTICS *pStatistics) const throw(...)
		{return GetInfo<TOKEN_STATISTICS>(pStatistics, TokenStatistics);}
	bool GetType(TOKEN_TYPE *pType) const throw(...)
		{return GetInfo<TOKEN_TYPE>(pType, TokenType);}
	bool GetUser(CSid *pSid) const throw(...)
		{return GetInfoConvert<CSid, TOKEN_USER>(pSid, TokenUser);}

	bool SetOwner(const CSid &rSid) throw(...);
	bool SetPrimaryGroup(const CSid &rSid) throw(...);
	bool SetDefaultDacl(const CDacl &rDacl) throw(...);

	bool CreateImpersonationToken(CAccessToken *pImp,
		SECURITY_IMPERSONATION_LEVEL sil = SecurityImpersonation) const throw(...);
	bool CreatePrimaryToken(CAccessToken *pPri,
		DWORD dwDesiredAccess = MAXIMUM_ALLOWED,
		const CSecurityAttributes *pTokenAttributes = NULL) const throw(...);

#if(_WIN32_WINNT >= 0x0500)
	bool CreateRestrictedToken(CAccessToken *pRestrictedToken,
		const CTokenGroups &SidsToDisable, const CTokenGroups &SidsToRestrict, 
		const CTokenPrivileges &PrivilegesToDelete = CTokenPrivileges()) const throw(...);
#endif

	// Token API type functions
	bool GetProcessToken(DWORD dwDesiredAccess, HANDLE hProcess = NULL) throw();
	bool GetThreadToken(DWORD dwDesiredAccess, HANDLE hThread = NULL, bool bOpenAsSelf = true) throw();
	bool GetEffectiveToken(DWORD dwDesiredAccess) throw();

	bool OpenThreadToken(DWORD dwDesiredAccess,
		bool bImpersonate = false, bool bOpenAsSelf = true,
		SECURITY_IMPERSONATION_LEVEL sil = SecurityImpersonation) throw(...);

#if (_WIN32_WINNT >= 0x0400 ) || defined(_WIN32_DCOM) 
	bool OpenCOMClientToken(DWORD dwDesiredAccess,
		bool bImpersonate = false, bool bOpenAsSelf = true) throw(...);
#endif //(_WIN32_WINNT >= 0x0400 ) || defined(_WIN32_DCOM) 

	bool OpenNamedPipeClientToken(HANDLE hPipe, DWORD dwDesiredAccess,
		bool bImpersonate = false, bool bOpenAsSelf = true) throw(...);
	bool OpenRPCClientToken(RPC_BINDING_HANDLE BindingHandle, DWORD dwDesiredAccess,
		bool bImpersonate = false, bool bOpenAsSelf = true) throw(...);

	bool ImpersonateLoggedOnUser() const throw(...);
	bool Impersonate(HANDLE hThread = NULL) const throw(...);
	bool Revert(HANDLE hThread = NULL) const throw();

	bool LoadUserProfile() throw(...);
	HANDLE GetProfile() const throw() {return m_hProfile;}

	// Must hold Tcb privilege
	bool LogonUser(
		LPCTSTR pszUserName, LPCTSTR pszDomain, LPCTSTR pszPassword,
		DWORD dwLogonType = LOGON32_LOGON_INTERACTIVE,
		DWORD dwLogonProvider = LOGON32_PROVIDER_DEFAULT) throw();

	// Must hold AssignPrimaryToken (unless restricted token) and
	// IncreaseQuota privileges
	bool CreateProcessAsUser(
		LPCTSTR pApplicationName, LPTSTR pCommandLine,
		LPPROCESS_INFORMATION pProcessInformation,
		LPSTARTUPINFO pStartupInfo,
		DWORD dwCreationFlags = NORMAL_PRIORITY_CLASS,
		bool bLoadProfile = false,
		const CSecurityAttributes *pProcessAttributes = NULL,
		const CSecurityAttributes *pThreadAttributes = NULL,
		bool bInherit = false,
		LPCTSTR pCurrentDirectory = NULL) throw();

protected:
	bool EnableDisablePrivileges(const CAtlArray<LPCTSTR> &rPrivileges,
		bool bEnable, CTokenPrivileges *pPreviousState) throw(...);
	bool CheckImpersonation() const throw();

	virtual void Clear() throw();

	HANDLE m_hToken, m_hProfile;

private:
	CAccessToken(const CAccessToken &rhs) throw(...);
	CAccessToken &operator=(const CAccessToken &rhs) throw(...);

	class CRevert
	{
	public:
		virtual bool Revert() throw() = 0;
	};

	class CRevertToSelf : public CRevert
	{
	public:
		bool Revert() throw() {return 0 != ::RevertToSelf();}
	};

#if (_WIN32_WINNT >= 0x0400 ) || defined(_WIN32_DCOM) 
	class CCoRevertToSelf : public CRevert
	{
	public:
		bool Revert() throw() {return SUCCEEDED(::CoRevertToSelf());}
	};
#endif //(_WIN32_WINNT >= 0x0400 ) || defined(_WIN32_DCOM) 

	class CRpcRevertToSelfEx : public CRevert
	{
	public:
		CRpcRevertToSelfEx(RPC_BINDING_HANDLE BindingHandle) throw()
			: m_hBinding(BindingHandle){}
		bool Revert() throw() {return RPC_S_OK == ::RpcRevertToSelfEx(m_hBinding);}

	private:
		RPC_BINDING_HANDLE m_hBinding;
	};
	mutable CRevert *m_pRevert;
};

// *************************************
// CAccessToken implementation
inline CAccessToken::~CAccessToken() throw()
{
	Clear();
}

inline void CAccessToken::Attach(HANDLE hToken) throw()
{
	ATLASSERT(m_hToken == NULL);
	m_hToken = hToken;
}

inline void CAccessToken::Clear() throw()
{
	if(m_hProfile)
	{
		ATLASSERT(m_hToken);
		if(m_hToken)
			::UnloadUserProfile(m_hToken, m_hProfile);
		m_hProfile = NULL;
	}

	if(m_hToken)
	{
		::CloseHandle(m_hToken);
		m_hToken = NULL;
	}
	delete m_pRevert;
	m_pRevert = NULL;
}

inline bool CAccessToken::EnablePrivilege(LPCTSTR pszPrivilege,
										  CTokenPrivileges *pPreviousState) throw(...)
{
	CTokenPrivileges NewState;
	NewState.Add(pszPrivilege, true);
	return EnableDisablePrivileges(NewState, pPreviousState);
}

inline bool CAccessToken::EnablePrivileges(const CAtlArray<LPCTSTR> &rPrivileges,
										   CTokenPrivileges *pPreviousState) throw(...)
{
	return EnableDisablePrivileges(rPrivileges, true, pPreviousState);
}

inline bool CAccessToken::DisablePrivilege(LPCTSTR pszPrivilege,
										   CTokenPrivileges *pPreviousState) throw(...)
{
	CTokenPrivileges NewState;
	NewState.Add(pszPrivilege, false);
	return EnableDisablePrivileges(NewState, pPreviousState);
}

inline bool CAccessToken::DisablePrivileges(const CAtlArray<LPCTSTR> &rPrivileges,
											CTokenPrivileges *pPreviousState) throw(...)
{
	return EnableDisablePrivileges(rPrivileges, false, pPreviousState);
}

inline bool CAccessToken::EnableDisablePrivileges(const CAtlArray<LPCTSTR> &rPrivileges,
												  bool bEnable, CTokenPrivileges *pPreviousState) throw(...)
{
	CTokenPrivileges NewState;
	for(UINT i = 0; i < rPrivileges.GetCount(); i++)
		NewState.Add(rPrivileges[i], bEnable);
	return EnableDisablePrivileges(NewState, pPreviousState);
}

inline bool CAccessToken::EnableDisablePrivileges(const CTokenPrivileges &rNewState,
												  CTokenPrivileges *pPreviousState) throw(...)
{
	if(!rNewState.GetCount())
		return true;

	TOKEN_PRIVILEGES *pNewState = const_cast<TOKEN_PRIVILEGES *>(rNewState.GetPTOKEN_PRIVILEGES());

	if(pPreviousState)
	{
		DWORD dwLength = DWORD(offsetof(TOKEN_PRIVILEGES, Privileges) +
			rNewState.GetCount() * sizeof(LUID_AND_ATTRIBUTES));

		USES_ATL_SAFE_ALLOCA;
		TOKEN_PRIVILEGES *pPrevState = static_cast<TOKEN_PRIVILEGES *>(_ATL_SAFE_ALLOCA(dwLength, _ATL_SAFE_ALLOCA_DEF_THRESHOLD));
		if(!::AdjustTokenPrivileges(m_hToken, FALSE, pNewState, dwLength, pPrevState, &dwLength))
			return false;

		pPreviousState->Add(*pPrevState);
		return true;
	}
	else
		return 0 != ::AdjustTokenPrivileges(m_hToken, FALSE, pNewState, 0, NULL, NULL);
}

inline bool CAccessToken::PrivilegeCheck(PPRIVILEGE_SET RequiredPrivileges, bool *pbResult) const throw()
{
	BOOL bResult;
	if(!::PrivilegeCheck(m_hToken, RequiredPrivileges, &bResult))
		return false;

	*pbResult = 0 != bResult;
	return true;
}

inline bool CAccessToken::GetProcessToken(DWORD dwDesiredAccess, HANDLE hProcess) throw()
{
	if(!hProcess)
		hProcess = ::GetCurrentProcess();

	HANDLE hToken;
	if(!::OpenProcessToken(hProcess, dwDesiredAccess, &hToken))
		return false;

	Clear();
	m_hToken = hToken;
	return true;
}

inline bool CAccessToken::GetThreadToken(DWORD dwDesiredAccess,
										 HANDLE hThread, bool bOpenAsSelf) throw()
{
	if(!hThread)
		hThread = ::GetCurrentThread();

	HANDLE hToken;
	if(!::OpenThreadToken(hThread, dwDesiredAccess, bOpenAsSelf, &hToken))
		return false;

	Clear();
	m_hToken = hToken;

	return true;
}

inline bool CAccessToken::GetEffectiveToken(DWORD dwDesiredAccess) throw()
{
	if(!GetThreadToken(dwDesiredAccess))
		return GetProcessToken(dwDesiredAccess);
	return true;
}

inline bool CAccessToken::CheckImpersonation() const throw()
{
	// You should not be impersonating at this point.  Use GetThreadToken
	// instead of the OpenXXXToken functions or call Revert before
	// calling Impersonate.
	HANDLE hToken;
	if(!::OpenThreadToken(::GetCurrentThread(), 0, false, &hToken) &&
		::GetLastError() != ERROR_NO_TOKEN)
	{
		ATLTRACE(atlTraceSecurity, 2, _T("Caution: replacing thread impersonation token.\n"));
		return true;
	}

	return false;
}

inline bool CAccessToken::OpenThreadToken(DWORD dwDesiredAccess,
										  bool bImpersonate, bool bOpenAsSelf,
										  SECURITY_IMPERSONATION_LEVEL sil) throw(...)
{
	CheckImpersonation();

	if(!::ImpersonateSelf(sil))
		return false;

	HANDLE hToken;
	if(!::OpenThreadToken(::GetCurrentThread(), dwDesiredAccess, bOpenAsSelf, &hToken))
		return false;

	Clear();
	m_hToken = hToken;

	if(!bImpersonate)
		::RevertToSelf();
	else
	{
		ATLTRY(m_pRevert = new CRevertToSelf);
		if(!m_pRevert)
		{
			::RevertToSelf();
			Clear();
			return false;
		}
	}
	return true;
}

#if (_WIN32_WINNT >= 0x0400 ) || defined(_WIN32_DCOM) 
inline bool CAccessToken::OpenCOMClientToken(DWORD dwDesiredAccess,
											 bool bImpersonate, bool bOpenAsSelf) throw(...)
{
	CheckImpersonation();

	if(FAILED(::CoImpersonateClient()))
		return false;

	HANDLE hToken;
	if(!::OpenThreadToken(::GetCurrentThread(), dwDesiredAccess, bOpenAsSelf, &hToken))
		return false;

	Clear();
	m_hToken = hToken;

	if(!bImpersonate)
		::CoRevertToSelf();
	else
	{
		ATLTRY(m_pRevert = new CCoRevertToSelf);
		if(!m_pRevert)
		{
			::CoRevertToSelf();
			Clear();
			return false;
		}
	}
	return true;
}
#endif //(_WIN32_WINNT >= 0x0400 ) || defined(_WIN32_DCOM) 

inline bool CAccessToken::OpenNamedPipeClientToken(HANDLE hPipe, DWORD dwDesiredAccess,
												   bool bImpersonate, bool bOpenAsSelf) throw(...)
{
	CheckImpersonation();

	if(!::ImpersonateNamedPipeClient(hPipe))
		return false;

	HANDLE hToken;
	if(!::OpenThreadToken(::GetCurrentThread(), dwDesiredAccess, bOpenAsSelf, &hToken))
		return false;

	Clear();
	m_hToken = hToken;

	if(!bImpersonate)
		::RevertToSelf();
	else
	{
		ATLTRY(m_pRevert = new CRevertToSelf);
		if(!m_pRevert)
		{
			::RevertToSelf();
			Clear();
			return false;
		}
	}
	return true;
}

inline bool CAccessToken::OpenRPCClientToken(RPC_BINDING_HANDLE BindingHandle,
											 DWORD dwDesiredAccess,
											 bool bImpersonate, bool bOpenAsSelf) throw(...)
{
	CheckImpersonation();

	if(RPC_S_OK != ::RpcImpersonateClient(BindingHandle))
		return false;

	HANDLE hToken;
	if(!::OpenThreadToken(::GetCurrentThread(), dwDesiredAccess, bOpenAsSelf, &hToken))
		return false;

	Clear();
	m_hToken = hToken;

	if(!bImpersonate)
	{
		RPC_STATUS rpcStatus = ::RpcRevertToSelfEx(BindingHandle);
		if( rpcStatus != RPC_S_OK )
		{
			Clear();
			return false;
		}
	}
	else
	{
		ATLTRY(m_pRevert = new CRpcRevertToSelfEx(BindingHandle));
		if(!m_pRevert)
		{
			::RpcRevertToSelfEx(BindingHandle);
			Clear();
			return false;
		}
	}
	return true;
}

inline bool CAccessToken::ImpersonateLoggedOnUser() const throw(...)
{
	CheckImpersonation();

	ATLASSERT(m_hToken);
	if(m_hToken && ::ImpersonateLoggedOnUser(m_hToken))
	{
		ATLASSERT(!m_pRevert);
		delete m_pRevert;
		ATLTRY(m_pRevert = new CRevertToSelf);
		if (!m_pRevert)
		{
			::RevertToSelf();
			return false;
		}
		return true;
	}
	return false;
}

inline bool CAccessToken::Impersonate(HANDLE hThread) const throw(...)
{
	CheckImpersonation();

	ATLASSERT(m_hToken);
	if(m_hToken)
		return 0 != ::SetThreadToken(hThread ? &hThread : NULL, m_hToken);
	return false;
}

inline bool CAccessToken::Revert(HANDLE hThread) const throw()
{
	if (hThread || !m_pRevert)
		return 0 != ::SetThreadToken(hThread ? &hThread : NULL, NULL);

	bool bRet = m_pRevert->Revert();
	delete m_pRevert;
	m_pRevert = NULL;
	return bRet;
}

inline bool CAccessToken::LogonUser(LPCTSTR pszUserName,
									LPCTSTR pszDomain,
									LPCTSTR pszPassword,
									DWORD dwLogonType,
									DWORD dwLogonProvider) throw()
{
	Clear();

	return 0 != ::LogonUser(
		const_cast<LPTSTR>(pszUserName),
		const_cast<LPTSTR>(pszDomain),
		const_cast<LPTSTR>(pszPassword),
		dwLogonType, dwLogonProvider, &m_hToken);
}

inline bool CAccessToken::LoadUserProfile() throw(...)
{
	ATLASSERT(m_hToken && !m_hProfile);
	if(!m_hToken || m_hProfile)
		return false;

	CSid UserSid;
	PROFILEINFO Profile;

	if(!GetUser(&UserSid))
		return false;

	memset(&Profile, 0x00, sizeof(PROFILEINFO));
	Profile.dwSize = sizeof(PROFILEINFO);
	Profile.lpUserName = const_cast<LPTSTR>(UserSid.AccountName());
	if(!::LoadUserProfile(m_hToken, &Profile))
		return false;

	m_hProfile = Profile.hProfile;

	return true;
}

inline bool CAccessToken::SetOwner(const CSid &rSid) throw(...)

{
	TOKEN_OWNER to;
	to.Owner = const_cast<SID *>(rSid.GetPSID());
	return 0 != ::SetTokenInformation(m_hToken, TokenOwner, &to, sizeof(to));
}

inline bool CAccessToken::SetPrimaryGroup(const CSid &rSid) throw(...)
{
	TOKEN_PRIMARY_GROUP tpg;
	tpg.PrimaryGroup = const_cast<SID *>(rSid.GetPSID());
	return 0 != ::SetTokenInformation(m_hToken, TokenPrimaryGroup, &tpg, sizeof(tpg));
}

inline bool CAccessToken::SetDefaultDacl(const CDacl &rDacl) throw(...)
{
	TOKEN_DEFAULT_DACL tdd;
	tdd.DefaultDacl = const_cast<ACL *>(rDacl.GetPACL());
	return 0 != ::SetTokenInformation(m_hToken, TokenDefaultDacl, &tdd, sizeof(tdd));
}

inline bool CAccessToken::CreateImpersonationToken(CAccessToken *pImp,
												   SECURITY_IMPERSONATION_LEVEL sil) const throw(...)
{
	ATLASSERT(pImp);
	if(!pImp)
		return false;

	HANDLE hToken;
	if(!::DuplicateToken(m_hToken, sil, &hToken))
		return false;

	pImp->Clear();
	pImp->m_hToken = hToken;
	return true;
}

inline bool CAccessToken::CreatePrimaryToken(CAccessToken *pPri, DWORD dwDesiredAccess,
											 const CSecurityAttributes *pTokenAttributes) const throw(...)
{
	ATLASSERT(pPri);
	if(!pPri)
		return false;

	HANDLE hToken;
	if(!::DuplicateTokenEx(m_hToken, dwDesiredAccess,
		const_cast<CSecurityAttributes *>(pTokenAttributes),
		SecurityAnonymous, TokenPrimary, &hToken))
	{
		return false;
	}

	pPri->Clear();
	pPri->m_hToken = hToken;
	return true;
}

#if(_WIN32_WINNT >= 0x0500)

inline bool CAccessToken::CreateRestrictedToken(CAccessToken *pRestrictedToken,
												const CTokenGroups &SidsToDisable,
												const CTokenGroups &SidsToRestrict,
												const CTokenPrivileges &PrivilegesToDelete) const throw(...)
{
	ATLASSERT(pRestrictedToken);
	if(!pRestrictedToken)
		return false;

	HANDLE hToken;
	SID_AND_ATTRIBUTES *pSidsToDisable;
	SID_AND_ATTRIBUTES *pSidsToRestrict;
	LUID_AND_ATTRIBUTES *pPrivilegesToDelete;

	UINT nDisableSidCount = SidsToDisable.GetCount();
	if(nDisableSidCount)
	{
		const TOKEN_GROUPS * pTOKEN_GROUPS = SidsToDisable.GetPTOKEN_GROUPS();

		ATLASSERT(pTOKEN_GROUPS != NULL);

		if(pTOKEN_GROUPS != NULL)
		{
			pSidsToDisable = const_cast<SID_AND_ATTRIBUTES *>
				(pTOKEN_GROUPS->Groups);
		}
		else
		{
			return false;
		}
	}
	else
	{
		pSidsToDisable = NULL;
	}

	UINT nRestrictedSidCount = SidsToRestrict.GetCount();
	if(nRestrictedSidCount)
	{
		const TOKEN_GROUPS * pTOKEN_GROUPS = SidsToRestrict.GetPTOKEN_GROUPS();

		ATLASSERT(pTOKEN_GROUPS != NULL);

		if(pTOKEN_GROUPS != NULL)
		{
			pSidsToRestrict = const_cast<SID_AND_ATTRIBUTES *>
				(pTOKEN_GROUPS->Groups);
		}
		else
		{
			return false;
		}

	}
	else
	{
		pSidsToRestrict = NULL;
	}

	UINT nDeletePrivilegesCount = PrivilegesToDelete.GetCount();
	if(nDeletePrivilegesCount)
	{
		const TOKEN_PRIVILEGES * pTOKEN_PRIVILEGES = PrivilegesToDelete.GetPTOKEN_PRIVILEGES();

		ATLASSERT(pTOKEN_PRIVILEGES != NULL);

		if(pTOKEN_PRIVILEGES != NULL)
		{
			pPrivilegesToDelete = const_cast<LUID_AND_ATTRIBUTES *>
				(pTOKEN_PRIVILEGES->Privileges);
		}
		else
		{
			return false;
		}

	}
	else
	{
		pPrivilegesToDelete = NULL;
	}

	if(!::CreateRestrictedToken(m_hToken, 0,
		(DWORD) nDisableSidCount, pSidsToDisable,
		(DWORD) nDeletePrivilegesCount, pPrivilegesToDelete,
		(DWORD) nRestrictedSidCount, pSidsToRestrict, &hToken))
	{
		return false;
	}

	pRestrictedToken->Clear();
	pRestrictedToken->m_hToken = hToken;
	return true;
}

#endif // _WIN32_WINNT >= 0x0500

inline bool CAccessToken::GetLogonSid(CSid *pSid) const throw(...)
{
	ATLASSERT(pSid);
	if(!pSid)
		return false;

	DWORD dwLen;
	::GetTokenInformation(m_hToken, TokenGroups, NULL, 0, &dwLen);
	if(::GetLastError() != ERROR_INSUFFICIENT_BUFFER)
		return false;

	USES_ATL_SAFE_ALLOCA;
	TOKEN_GROUPS *pGroups = static_cast<TOKEN_GROUPS *>(_ATL_SAFE_ALLOCA(dwLen, _ATL_SAFE_ALLOCA_DEF_THRESHOLD));
	if(::GetTokenInformation(m_hToken, TokenGroups, pGroups, dwLen, &dwLen))
		for(UINT i = 0; i < pGroups->GroupCount; i++)
			if(pGroups->Groups[i].Attributes & SE_GROUP_LOGON_ID)
			{
				*pSid = *static_cast<SID *>(pGroups->Groups[i].Sid);
				return true;
			}
	return false;
}

inline bool CAccessToken::GetTokenId(LUID *pluid) const throw(...)
{
	ATLASSERT(pluid);
	if(!pluid)
		return false;

	TOKEN_STATISTICS Statistics;
	if(!GetStatistics(&Statistics))
		return false;

	*pluid = Statistics.TokenId;
	return true;
}

inline bool CAccessToken::GetLogonSessionId(LUID *pluid) const throw(...)
{
	ATLASSERT(pluid);
	if(!pluid)
		return false;

	TOKEN_STATISTICS Statistics;
	if(!GetStatistics(&Statistics))
		return false;

	*pluid = Statistics.AuthenticationId;
	return true;
}

inline bool CAccessToken::CheckTokenMembership(const CSid &rSid, bool *pbIsMember) const throw(...)
{
	// "this" must be an impersonation token and NOT a primary token
	BOOL bIsMember;

	ATLASSERT(pbIsMember);
	if (!pbIsMember)
		return false;

#if(_WIN32_WINNT >= 0x0500)
	if(::CheckTokenMembership(m_hToken, const_cast<SID *>(rSid.GetPSID()), &bIsMember))
#else
	GENERIC_MAPPING gm = {0, 0, 0, 1};
	PRIVILEGE_SET ps;
	DWORD cb = sizeof(PRIVILEGE_SET);
	DWORD ga;
	CSecurityDesc sd;
	CDacl dacl;

	if (!dacl.AddAllowedAce(rSid, 1))
		return false;
	sd.SetOwner(rSid);
	sd.SetGroup(rSid);
	sd.SetDacl(dacl);

	if(::AccessCheck(const_cast<SECURITY_DESCRIPTOR *>(sd.GetPSECURITY_DESCRIPTOR()),
		m_hToken, 1, &gm, &ps, &cb, &ga, &bIsMember))
#endif
	{
		*pbIsMember = 0 != bIsMember;
		return true;
	}
	return false;
}

inline bool CAccessToken::CreateProcessAsUser(
		LPCTSTR pApplicationName, LPTSTR pCommandLine,
		LPPROCESS_INFORMATION pProcessInformation,
		LPSTARTUPINFO pStartupInfo,
		DWORD dwCreationFlags,
		bool bLoadProfile,
		const CSecurityAttributes *pProcessAttributes,
		const CSecurityAttributes *pThreadAttributes,
		bool bInherit,
		LPCTSTR pCurrentDirectory) throw()
{
	ATLASSERT(pProcessInformation != NULL);
	ATLASSERT(pStartupInfo != NULL);

	LPVOID pEnvironmentBlock;
	PROFILEINFO Profile;
	CSid UserSid;
	DWORD dwLastError;

	HANDLE hToken = m_hToken;

	// Straighten out impersonation problems...
	TOKEN_TYPE TokenType;
	if(!GetType(&TokenType))
	{
		return false;
	}

	if (TokenType != TokenPrimary)
	{
		hToken = NULL;
		if (!::DuplicateTokenEx(m_hToken, TOKEN_QUERY|TOKEN_DUPLICATE|TOKEN_ASSIGN_PRIMARY, NULL,
			SecurityImpersonation, TokenPrimary, &hToken))
		{
			return false;
		}
	}

	// Profile
	if(bLoadProfile && !m_hProfile)
	{
		if(!GetUser(&UserSid))
		{
			if(TokenType != TokenPrimary)
				::CloseHandle(hToken);
			return false;
		}
		memset(&Profile, 0x00, sizeof(PROFILEINFO));
		Profile.dwSize = sizeof(PROFILEINFO);
		Profile.lpUserName = const_cast<LPTSTR>(UserSid.AccountName());
		if(::LoadUserProfile(hToken, &Profile))
			m_hProfile = Profile.hProfile;
	}

	// Environment block
	if(!::CreateEnvironmentBlock(&pEnvironmentBlock, hToken, bInherit))
		return false;

	BOOL bRetVal = ::CreateProcessAsUser(
		hToken,
		pApplicationName,
		pCommandLine,
		const_cast<CSecurityAttributes *>(pProcessAttributes),
		const_cast<CSecurityAttributes *>(pThreadAttributes),
		bInherit,
		dwCreationFlags,
		pEnvironmentBlock,
		pCurrentDirectory,
		pStartupInfo,
		pProcessInformation);

	 dwLastError = ::GetLastError();

	if(TokenType != TokenPrimary)
		::CloseHandle(hToken);

	::DestroyEnvironmentBlock(pEnvironmentBlock);

	::SetLastError(dwLastError);
	return bRetVal != 0;
}

//*******************************************
// Private Security
class CPrivateObjectSecurityDesc : public CSecurityDesc
{
public:
	CPrivateObjectSecurityDesc() throw() : m_bPrivate(false), CSecurityDesc(){}
	~CPrivateObjectSecurityDesc() throw() {Clear();}

	bool Create(const CSecurityDesc *pParent, const CSecurityDesc *pCreator,
		bool bIsDirectoryObject, const CAccessToken &Token, PGENERIC_MAPPING GenericMapping) throw();

#if(_WIN32_WINNT >= 0x0500)
	bool Create(const CSecurityDesc *pParent, const CSecurityDesc *pCreator,
		GUID *ObjectType, bool bIsContainerObject, ULONG AutoInheritFlags,
		const CAccessToken &Token, PGENERIC_MAPPING GenericMapping) throw();
#endif

	bool Get(SECURITY_INFORMATION si, CSecurityDesc *pResult) const throw();
	bool Set(SECURITY_INFORMATION si, const CSecurityDesc &Modification,
		PGENERIC_MAPPING GenericMapping, const CAccessToken &Token) throw();

#if(_WIN32_WINNT >= 0x0500)
	bool Set(SECURITY_INFORMATION si, const CSecurityDesc &Modification,
		ULONG AutoInheritFlags, PGENERIC_MAPPING GenericMapping,
		const CAccessToken &Token) throw();

	bool ConvertToAutoInherit(const CSecurityDesc *pParent, GUID *ObjectType,
		bool bIsDirectoryObject, PGENERIC_MAPPING GenericMapping) throw();
#endif

protected:
	void Clear() throw();

private:
	bool m_bPrivate;

	CPrivateObjectSecurityDesc(const CPrivateObjectSecurityDesc &rhs) throw(...);
	CPrivateObjectSecurityDesc &operator=(const CPrivateObjectSecurityDesc &rhs) throw(...);
};

inline void CPrivateObjectSecurityDesc::Clear() throw()
{
	if(m_bPrivate)
	{
		ATLVERIFY(::DestroyPrivateObjectSecurity(reinterpret_cast<PSECURITY_DESCRIPTOR *>(&m_pSecurityDescriptor)));
		m_bPrivate = false;
		m_pSecurityDescriptor = NULL;
	}
	else
		CSecurityDesc::Clear();
}

inline bool CPrivateObjectSecurityDesc::Create(const CSecurityDesc *pParent, const CSecurityDesc *pCreator,
											   bool bIsDirectoryObject, const CAccessToken &Token,
											   PGENERIC_MAPPING GenericMapping) throw()
{
	Clear();

	const SECURITY_DESCRIPTOR *pSDParent = pParent ? pParent->GetPSECURITY_DESCRIPTOR() : NULL;
	const SECURITY_DESCRIPTOR *pSDCreator = pCreator ? pCreator->GetPSECURITY_DESCRIPTOR() : NULL;

	if(!::CreatePrivateObjectSecurity(
		const_cast<SECURITY_DESCRIPTOR *>(pSDParent),
		const_cast<SECURITY_DESCRIPTOR *>(pSDCreator),
		reinterpret_cast<PSECURITY_DESCRIPTOR *>(&m_pSecurityDescriptor),
		bIsDirectoryObject, Token.GetHandle(), GenericMapping))
	{
		return false;
	}

	m_bPrivate = true;
	return true;
}

#if(_WIN32_WINNT >= 0x0500)
inline bool CPrivateObjectSecurityDesc::Create(const CSecurityDesc *pParent, const CSecurityDesc *pCreator,
											   GUID *ObjectType, bool bIsContainerObject, ULONG AutoInheritFlags,
											   const CAccessToken &Token, PGENERIC_MAPPING GenericMapping) throw()
{
	Clear();

	const SECURITY_DESCRIPTOR *pSDParent = pParent ? pParent->GetPSECURITY_DESCRIPTOR() : NULL;
	const SECURITY_DESCRIPTOR *pSDCreator = pCreator ? pCreator->GetPSECURITY_DESCRIPTOR() : NULL;

	if(!::CreatePrivateObjectSecurityEx(
		const_cast<SECURITY_DESCRIPTOR *>(pSDParent),
		const_cast<SECURITY_DESCRIPTOR *>(pSDCreator),
		reinterpret_cast<PSECURITY_DESCRIPTOR *>(&m_pSecurityDescriptor),
		ObjectType, bIsContainerObject, AutoInheritFlags, Token.GetHandle(), GenericMapping))
	{
		return false;
	}

	m_bPrivate = true;
	return true;
}
#endif

inline bool CPrivateObjectSecurityDesc::Get(SECURITY_INFORMATION si, CSecurityDesc *pResult) const throw()
{
	ATLASSERT(pResult);
	if(!pResult)
		return false;

	if(!m_bPrivate)
		return false;

	DWORD dwLength = 0;
	SECURITY_DESCRIPTOR *pSDResult = NULL;

	if(!::GetPrivateObjectSecurity(m_pSecurityDescriptor, si, pSDResult, dwLength, &dwLength) &&
		::GetLastError() != ERROR_INSUFFICIENT_BUFFER)
	{
		return false;
	}

	USES_ATL_SAFE_ALLOCA;
	pSDResult = static_cast<SECURITY_DESCRIPTOR *>(_ATL_SAFE_ALLOCA(dwLength, _ATL_SAFE_ALLOCA_DEF_THRESHOLD));
	if(!::GetPrivateObjectSecurity(m_pSecurityDescriptor, si, pSDResult, dwLength, &dwLength))
		return false;

	*pResult = *pSDResult;

	return true;
}

inline bool CPrivateObjectSecurityDesc::Set(SECURITY_INFORMATION si, const CSecurityDesc &Modification,
											PGENERIC_MAPPING GenericMapping, const CAccessToken &Token) throw()
{
	if(!m_bPrivate)
		return false;

	const SECURITY_DESCRIPTOR *pSDModification = Modification.GetPSECURITY_DESCRIPTOR();

	return 0 != ::SetPrivateObjectSecurity(si,
		const_cast<SECURITY_DESCRIPTOR *>(pSDModification),
		reinterpret_cast<PSECURITY_DESCRIPTOR *>(&m_pSecurityDescriptor),
		GenericMapping, Token.GetHandle());
}

#if(_WIN32_WINNT >= 0x0500)
inline bool CPrivateObjectSecurityDesc::Set(SECURITY_INFORMATION si, const CSecurityDesc &Modification,
											ULONG AutoInheritFlags, PGENERIC_MAPPING GenericMapping,
											const CAccessToken &Token) throw()
{
	if(!m_bPrivate)
		return false;

	const SECURITY_DESCRIPTOR *pSDModification = Modification.GetPSECURITY_DESCRIPTOR();

	return 0 != ::SetPrivateObjectSecurityEx(si,
		const_cast<SECURITY_DESCRIPTOR *>(pSDModification),
		reinterpret_cast<PSECURITY_DESCRIPTOR *>(&m_pSecurityDescriptor),
		AutoInheritFlags, GenericMapping, Token.GetHandle());
}

inline bool CPrivateObjectSecurityDesc::ConvertToAutoInherit(const CSecurityDesc *pParent, GUID *ObjectType,
															 bool bIsDirectoryObject, PGENERIC_MAPPING GenericMapping) throw()
{
	if(!m_bPrivate)
		return false;

	const SECURITY_DESCRIPTOR *pSDParent = pParent ? pParent->GetPSECURITY_DESCRIPTOR() : NULL;
	SECURITY_DESCRIPTOR *pSD;

	if(!::ConvertToAutoInheritPrivateObjectSecurity(
		const_cast<SECURITY_DESCRIPTOR *>(pSDParent),
		m_pSecurityDescriptor,
		reinterpret_cast<PSECURITY_DESCRIPTOR *>(&pSD),
		ObjectType, bIsDirectoryObject, GenericMapping))
	{
		return false;
	}

	Clear();
	m_bPrivate = true;
	m_pSecurityDescriptor = pSD;

	return true;
}
#endif // _WIN32_WINNT >= 0x500

//*******************************************
// Globals
inline bool AtlGetSecurityDescriptor(LPCTSTR pszObjectName,
									 SE_OBJECT_TYPE ObjectType,
									 CSecurityDesc *pSecurityDescriptor,
									 SECURITY_INFORMATION requestedInfo =
										OWNER_SECURITY_INFORMATION |
										GROUP_SECURITY_INFORMATION |
										DACL_SECURITY_INFORMATION |
										SACL_SECURITY_INFORMATION,
									 bool bRequestNeededPrivileges = true
									) throw(...)
{
	ATLASSERT(pSecurityDescriptor);
	if(!pSecurityDescriptor)
		return false;

	SECURITY_DESCRIPTOR *pSD;
	DWORD dwErr;

	CAccessToken at;
	CTokenPrivileges TokenPrivileges;

	if (!(requestedInfo & SACL_SECURITY_INFORMATION))
		bRequestNeededPrivileges = false;

	if (bRequestNeededPrivileges)
	{
		if(!at.OpenThreadToken(TOKEN_IMPERSONATE | TOKEN_ADJUST_PRIVILEGES | TOKEN_QUERY,
					false, false, SecurityImpersonation) ||
				!at.EnablePrivilege(SE_SECURITY_NAME, &TokenPrivileges) ||
				!at.Impersonate())
			return false;
	}

	dwErr = ::GetNamedSecurityInfo(const_cast<LPTSTR>(pszObjectName), ObjectType, requestedInfo,
		NULL, NULL, NULL, NULL, (PSECURITY_DESCRIPTOR *) &pSD);

	if (bRequestNeededPrivileges)
	{
		if( !at.EnableDisablePrivileges(TokenPrivileges) )
			return false;
		if( !at.Revert() )
			return false;
	}

	if(dwErr != ERROR_SUCCESS)
	{
		::SetLastError(dwErr);
		return false;
	}

	*pSecurityDescriptor = *pSD;
	::LocalFree(pSD);
	return true;
}

inline bool AtlGetSecurityDescriptor(HANDLE hObject,
									 SE_OBJECT_TYPE ObjectType,
									 CSecurityDesc *pSecurityDescriptor,
									 SECURITY_INFORMATION requestedInfo =
										OWNER_SECURITY_INFORMATION |
										GROUP_SECURITY_INFORMATION |
										DACL_SECURITY_INFORMATION |
										SACL_SECURITY_INFORMATION,
									 bool bRequestNeededPrivileges = true
									) throw(...)
{
	ATLASSERT(pSecurityDescriptor);
	if(!pSecurityDescriptor)
		return false;

	SECURITY_DESCRIPTOR *pSD;
	DWORD dwErr;

	CAccessToken at;
	CTokenPrivileges TokenPrivileges;

	if (!(requestedInfo & SACL_SECURITY_INFORMATION))
		bRequestNeededPrivileges = false;

	if (bRequestNeededPrivileges)
	{
		if(!at.OpenThreadToken(TOKEN_IMPERSONATE | TOKEN_ADJUST_PRIVILEGES | TOKEN_QUERY,
					false, false, SecurityImpersonation) ||
				!at.EnablePrivilege(SE_SECURITY_NAME, &TokenPrivileges) ||
				!at.Impersonate())
			return false;
	}

	dwErr = ::GetSecurityInfo(hObject, ObjectType, requestedInfo,
		NULL, NULL, NULL, NULL, reinterpret_cast<PSECURITY_DESCRIPTOR *>(&pSD));

	if (bRequestNeededPrivileges)
	{
		if( !at.EnableDisablePrivileges(TokenPrivileges) )
			return false;
		if( !at.Revert() )
			return false;
	}

	if(dwErr != ERROR_SUCCESS)
	{
		::SetLastError(dwErr);
		return false;
	}

	*pSecurityDescriptor = *pSD;
	::LocalFree(pSD);
	return true;
}

inline bool AtlGetOwnerSid(HANDLE hObject, SE_OBJECT_TYPE ObjectType, CSid *pSid) throw(...)
{
	ATLASSERT(hObject && pSid);
	if(!hObject || !pSid)
		return false;

	SID *pOwner;
	PSECURITY_DESCRIPTOR pSD;
	DWORD dwErr = ::GetSecurityInfo(hObject, ObjectType, OWNER_SECURITY_INFORMATION,
		(PSID *) &pOwner, NULL, NULL, NULL, &pSD);

	if(dwErr != ERROR_SUCCESS)
	{
		::SetLastError(dwErr);
		return false;
	}

	*pSid = *pOwner;
	::LocalFree(pSD);
	return true;
}

inline bool AtlSetOwnerSid(HANDLE hObject, SE_OBJECT_TYPE ObjectType, const CSid &rSid) throw(...)
{
	ATLASSERT(hObject && rSid.IsValid());
	if(!hObject || !rSid.IsValid())
		return false;

	DWORD dwErr = ::SetSecurityInfo(hObject, ObjectType, OWNER_SECURITY_INFORMATION,
		const_cast<SID *>(rSid.GetPSID()), NULL, NULL, NULL);

	::SetLastError(dwErr);
	return ERROR_SUCCESS == dwErr;
}

inline bool AtlGetOwnerSid(LPCTSTR pszObjectName, SE_OBJECT_TYPE ObjectType, CSid *pSid) throw(...)
{
	ATLASSERT(pszObjectName && pSid);
	if(!pszObjectName || !pSid)
		return false;

	SID *pOwner;
	PSECURITY_DESCRIPTOR pSD;
	DWORD dwErr = ::GetNamedSecurityInfo(const_cast<LPTSTR>(pszObjectName), ObjectType,
		OWNER_SECURITY_INFORMATION, reinterpret_cast<PSID *>(&pOwner), NULL, NULL, NULL, &pSD);

	if(dwErr != ERROR_SUCCESS)
	{
		::SetLastError(dwErr);
		return false;
	}

	*pSid = *pOwner;
	::LocalFree(pSD);
	return true;
}

inline bool AtlSetOwnerSid(LPCTSTR pszObjectName, SE_OBJECT_TYPE ObjectType, const CSid &rSid) throw(...)
{
	ATLASSERT(pszObjectName && rSid.IsValid());
	if(!pszObjectName || !rSid.IsValid())
		return false;

	DWORD dwErr = ::SetNamedSecurityInfo(const_cast<LPTSTR>(pszObjectName), ObjectType,
		OWNER_SECURITY_INFORMATION, const_cast<SID *>(rSid.GetPSID()), NULL, NULL, NULL);

	::SetLastError(dwErr);
	return ERROR_SUCCESS == dwErr;
}

inline bool AtlGetGroupSid(HANDLE hObject, SE_OBJECT_TYPE ObjectType, CSid *pSid) throw(...)
{
	ATLASSERT(hObject && pSid);
	if(!hObject || !pSid)
		return false;

	SID *pGroup;
	PSECURITY_DESCRIPTOR pSD;
	DWORD dwErr = ::GetSecurityInfo(hObject, ObjectType, GROUP_SECURITY_INFORMATION,
		NULL, reinterpret_cast<PSID *>(&pGroup), NULL, NULL, &pSD);

	if(dwErr != ERROR_SUCCESS)
	{
		::SetLastError(dwErr);
		return false;
	}

	*pSid = *pGroup;
	::LocalFree(pSD);
	return true;
}

inline bool AtlSetGroupSid(HANDLE hObject, SE_OBJECT_TYPE ObjectType, const CSid &rSid) throw(...)
{
	ATLASSERT(hObject && rSid.IsValid());
	if(!hObject || !rSid.IsValid())
		return false;

	DWORD dwErr = ::SetSecurityInfo(hObject, ObjectType, GROUP_SECURITY_INFORMATION,
		NULL, const_cast<SID *>(rSid.GetPSID()), NULL, NULL);

	::SetLastError(dwErr);
	return ERROR_SUCCESS == dwErr;
}

inline bool AtlGetGroupSid(LPCTSTR pszObjectName, SE_OBJECT_TYPE ObjectType, CSid *pSid) throw(...)
{
	ATLASSERT(pszObjectName && pSid);
	if(!pszObjectName || !pSid)
		return false;

	SID *pGroup;
	PSECURITY_DESCRIPTOR pSD;
	DWORD dwErr = ::GetNamedSecurityInfo(const_cast<LPTSTR>(pszObjectName),
		ObjectType, GROUP_SECURITY_INFORMATION, NULL,
		reinterpret_cast<PSID *>(&pGroup), NULL, NULL, &pSD);

	if(dwErr != ERROR_SUCCESS)
	{
		::SetLastError(dwErr);
		return false;
	}

	*pSid = *pGroup;
	::LocalFree(pSD);
	return true;
}

inline bool AtlSetGroupSid(LPCTSTR pszObjectName, SE_OBJECT_TYPE ObjectType, const CSid &rSid) throw(...)
{
	ATLASSERT(pszObjectName && rSid.IsValid());
	if(!pszObjectName || !rSid.IsValid())
		return false;

	DWORD dwErr = ::SetNamedSecurityInfo(const_cast<LPTSTR>(pszObjectName), ObjectType,
		GROUP_SECURITY_INFORMATION, NULL, const_cast<SID *>(rSid.GetPSID()), NULL, NULL);

	::SetLastError(dwErr);
	return ERROR_SUCCESS == dwErr;
}

inline bool AtlGetDacl(HANDLE hObject, SE_OBJECT_TYPE ObjectType, CDacl *pDacl) throw(...)
{
	ATLASSERT(hObject && pDacl);
	if(!hObject || !pDacl)
		return false;

	ACL *pAcl;
	PSECURITY_DESCRIPTOR pSD;

	DWORD dwErr = ::GetSecurityInfo(hObject, ObjectType, DACL_SECURITY_INFORMATION,
		NULL, NULL, &pAcl, NULL, &pSD);

	if(dwErr != ERROR_SUCCESS)
	{
		::SetLastError(dwErr);
		return false;
	}

	if(pAcl)
		*pDacl = *pAcl;
	::LocalFree(pSD);

	return NULL != pAcl;
}

inline bool AtlSetDacl(HANDLE hObject, SE_OBJECT_TYPE ObjectType, const CDacl &rDacl,
					   DWORD dwInheritanceFlowControl = 0) throw(...)
{
	ATLASSERT(hObject);
	if(!hObject)
		return false;

	ATLASSERT(
		dwInheritanceFlowControl == 0 ||
		dwInheritanceFlowControl == PROTECTED_DACL_SECURITY_INFORMATION ||
		dwInheritanceFlowControl == UNPROTECTED_DACL_SECURITY_INFORMATION);

	DWORD dwErr = ::SetSecurityInfo(hObject, ObjectType,
		DACL_SECURITY_INFORMATION | dwInheritanceFlowControl,
		NULL, NULL, const_cast<ACL *>(rDacl.GetPACL()), NULL);

	::SetLastError(dwErr);
	return ERROR_SUCCESS == dwErr;
}

inline bool AtlGetDacl(LPCTSTR pszObjectName, SE_OBJECT_TYPE ObjectType, CDacl *pDacl) throw(...)
{
	ATLASSERT(pszObjectName && pDacl);
	if(!pszObjectName || !pDacl)
		return false;

	ACL *pAcl;
	PSECURITY_DESCRIPTOR pSD;

	DWORD dwErr = ::GetNamedSecurityInfo(const_cast<LPTSTR>(pszObjectName), ObjectType,
		DACL_SECURITY_INFORMATION, NULL, NULL, &pAcl, NULL, &pSD);

	if(dwErr != ERROR_SUCCESS)
	{
		::SetLastError(dwErr);
		return false;
	}

	if(pAcl)
		*pDacl = *pAcl;
	::LocalFree(pSD);

	return NULL != pAcl;
}

inline bool AtlSetDacl(LPCTSTR pszObjectName, SE_OBJECT_TYPE ObjectType, const CDacl &rDacl,
					   DWORD dwInheritanceFlowControl = 0) throw(...)
{
	ATLASSERT(pszObjectName);
	if(!pszObjectName)
		return false;

	ATLASSERT(
		dwInheritanceFlowControl == 0 ||
		dwInheritanceFlowControl == PROTECTED_DACL_SECURITY_INFORMATION ||
		dwInheritanceFlowControl == UNPROTECTED_DACL_SECURITY_INFORMATION);

	DWORD dwErr = ::SetNamedSecurityInfo(const_cast<LPTSTR>(pszObjectName), ObjectType,
		DACL_SECURITY_INFORMATION | dwInheritanceFlowControl,
		NULL, NULL, const_cast<ACL *>(rDacl.GetPACL()), NULL);

	::SetLastError(dwErr);
	return ERROR_SUCCESS == dwErr;
}

inline bool AtlGetSacl(HANDLE hObject,
					   SE_OBJECT_TYPE ObjectType,
					   CSacl *pSacl,
					   bool bRequestNeededPrivileges = true
					   ) throw(...)
{
	ATLASSERT(hObject && pSacl);
	if(!hObject || !pSacl)
		return false;

	ACL *pAcl;
	PSECURITY_DESCRIPTOR pSD;
	CAccessToken at;
	CTokenPrivileges TokenPrivileges;

	if (bRequestNeededPrivileges)
	{
		if(!at.OpenThreadToken(TOKEN_IMPERSONATE | TOKEN_ADJUST_PRIVILEGES | TOKEN_QUERY,
					false, false, SecurityImpersonation) ||
				!at.EnablePrivilege(SE_SECURITY_NAME, &TokenPrivileges) ||
				!at.Impersonate())
			return false;
	}

	DWORD dwErr = ::GetSecurityInfo(hObject, ObjectType, SACL_SECURITY_INFORMATION,
		NULL, NULL, NULL, &pAcl, &pSD);

	if (bRequestNeededPrivileges)
	{
        if( !at.EnableDisablePrivileges(TokenPrivileges) )
			return false;
		if( !at.Revert() )
			return false;
	}

	if(dwErr != ERROR_SUCCESS)
	{
		::SetLastError(dwErr);
		return false;
	}

	if(pAcl)
		*pSacl = *pAcl;
	::LocalFree(pSD);

	return NULL != pAcl;
}

inline bool AtlSetSacl(HANDLE hObject,
					   SE_OBJECT_TYPE ObjectType,
					   const CSacl &rSacl,
					   DWORD dwInheritanceFlowControl = 0,
					   bool bRequestNeededPrivileges = true) throw(...)
{
	ATLASSERT(hObject);
	if (!hObject)
		return false;

	CAccessToken at;
	CTokenPrivileges TokenPrivileges;

	ATLASSERT(
		dwInheritanceFlowControl == 0 ||
		dwInheritanceFlowControl == PROTECTED_SACL_SECURITY_INFORMATION ||
		dwInheritanceFlowControl == UNPROTECTED_SACL_SECURITY_INFORMATION);

	if (bRequestNeededPrivileges)
	{
		if(!at.OpenThreadToken(TOKEN_IMPERSONATE | TOKEN_ADJUST_PRIVILEGES | TOKEN_QUERY,
					false, false, SecurityImpersonation) ||
				!at.EnablePrivilege(SE_SECURITY_NAME, &TokenPrivileges) ||
				!at.Impersonate())
			return false;
	}

	DWORD dwErr = ::SetSecurityInfo(hObject, ObjectType,
		SACL_SECURITY_INFORMATION | dwInheritanceFlowControl,
		NULL, NULL, NULL, const_cast<ACL *>(rSacl.GetPACL()));

	if (bRequestNeededPrivileges)
	{
		if( !at.EnableDisablePrivileges(TokenPrivileges) )
			return false;
		if( !at.Revert() )
			return false;
	}

	::SetLastError(dwErr);
	return ERROR_SUCCESS == dwErr;
}

inline bool AtlGetSacl(LPCTSTR pszObjectName,
					   SE_OBJECT_TYPE ObjectType,
					   CSacl *pSacl,
					   bool bRequestNeededPrivileges = true) throw(...)
{
	ATLASSERT(pszObjectName && pSacl);
	if(!pszObjectName || !pSacl)
		return false;

	ACL *pAcl;
	PSECURITY_DESCRIPTOR pSD;
	CAccessToken at;
	CTokenPrivileges TokenPrivileges;

	if (bRequestNeededPrivileges)
	{
		if(!at.OpenThreadToken(TOKEN_IMPERSONATE | TOKEN_ADJUST_PRIVILEGES | TOKEN_QUERY,
					false, false, SecurityImpersonation) ||
				!at.EnablePrivilege(SE_SECURITY_NAME, &TokenPrivileges) ||
				!at.Impersonate())
			return false;
	}

	DWORD dwErr = ::GetNamedSecurityInfo(const_cast<LPTSTR>(pszObjectName), ObjectType,
		SACL_SECURITY_INFORMATION, NULL, NULL, NULL, &pAcl, &pSD);

	if (bRequestNeededPrivileges)
	{
		at.EnableDisablePrivileges(TokenPrivileges);
		at.Revert();
	}

	::SetLastError(dwErr);
	if(dwErr != ERROR_SUCCESS)
		return false;

	if(pAcl)
		*pSacl = *pAcl;
	::LocalFree(pSD);

	return NULL != pAcl;
}

inline bool AtlSetSacl(LPCTSTR pszObjectName,
					   SE_OBJECT_TYPE ObjectType,
					   const CSacl &rSacl,
					   DWORD dwInheritanceFlowControl = 0,
					   bool bRequestNeededPrivileges = true) throw(...)
{
	ATLASSERT(pszObjectName);
	if (!pszObjectName)
		return false;

	CAccessToken at;
	CTokenPrivileges TokenPrivileges;

	ATLASSERT(
		dwInheritanceFlowControl == 0 ||
		dwInheritanceFlowControl == PROTECTED_SACL_SECURITY_INFORMATION ||
		dwInheritanceFlowControl == UNPROTECTED_SACL_SECURITY_INFORMATION);

	if(bRequestNeededPrivileges)
	{
		if (!at.OpenThreadToken(TOKEN_IMPERSONATE | TOKEN_ADJUST_PRIVILEGES | TOKEN_QUERY,
					false, false, SecurityImpersonation) ||
				!at.EnablePrivilege(SE_SECURITY_NAME, &TokenPrivileges) ||
				!at.Impersonate())
			return false;
	}

	DWORD dwErr = ::SetNamedSecurityInfo(const_cast<LPTSTR>(pszObjectName), ObjectType,
		SACL_SECURITY_INFORMATION | dwInheritanceFlowControl,
		NULL, NULL, NULL, const_cast<ACL *>(rSacl.GetPACL()));

	if (bRequestNeededPrivileges)
	{
		at.EnableDisablePrivileges(TokenPrivileges);
		at.Revert();
	}

	::SetLastError(dwErr);
	return ERROR_SUCCESS == dwErr;
}

} // namespace ATL

#pragma warning(pop)

#endif // __ATLSECURITY_H__

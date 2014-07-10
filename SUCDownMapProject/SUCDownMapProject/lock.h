#pragma once

namespace CCS
{

class CCriticalSection : public CRITICAL_SECTION
{
public:
	explicit CCriticalSection( )
	{
		::InitializeCriticalSection( this );
	}

	~CCriticalSection() throw()
	{
		::DeleteCriticalSection( this );
	}

	// In winxp and newer os, EnterCriticalSection never raise an exception
	void Enter() throw()
	{
		::EnterCriticalSection( this );
	}

	void Leave() throw()
	{
		::LeaveCriticalSection( this );
	}


};

}
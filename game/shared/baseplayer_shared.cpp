#include "stdafx.h"

//-----------------------------------------------------------------------------
// Purpose: Sets the FOV of the client, doing interpolation between old and new if requested
// Input  : FOV - New FOV
//			zoomRate - Amount of time (in seconds) to move between old and new FOV
//-----------------------------------------------------------------------------
bool CBasePlayer::SetFOV( CBaseEntity *pRequester, int FOV, float zoomRate, int iZoomStart /* = 0 */ )
{
	//NOTENOTE: You MUST specify who is requesting the zoom change
	assert( pRequester != NULL );
	if ( pRequester == NULL )
		return false;

	// If we already have an owner, we only allow requests from that owner
	if ( (m_hZoomOwner.Get() != NULL) && (m_hZoomOwner.Get() != pRequester) )
	{
		return false;
	}
	else
	{
		//FIXME: Maybe do this is as an accessor instead
		if ( FOV == 0 )
		{
			m_hZoomOwner = NULL;
		}
		else
		{
			m_hZoomOwner = pRequester;
		}
}

	// Setup our FOV and our scaling time

	if ( iZoomStart > 0 )
	{
		m_iFOVStart = iZoomStart;
	}
	else
	{
		m_iFOVStart = GetFOV();
	}

	m_flFOVTime = gpGlobals->curtime;
	m_iFOV = FOV;

	m_Local.m_flFOVRate = zoomRate;

	return true;
}

int CBasePlayer::GetDefaultFOV( void ) const
{
#if defined( CLIENT_DLL )
	if ( GetObserverMode() == OBS_MODE_IN_EYE )
	{
		C_BasePlayer *pTargetPlayer = dynamic_cast<C_BasePlayer*>(GetObserverTarget());

		if ( pTargetPlayer && !pTargetPlayer->IsObserver() )
		{
			return pTargetPlayer->GetDefaultFOV();
		}
	}
#endif

	int iFOV = (m_iDefaultFOV == 0) ? GameRules()->DefaultFOV() : m_iDefaultFOV;

	return iFOV;
}
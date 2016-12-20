#include "stdafx.h"

//-----------------------------------------------------------------------------
// Purpose: Sets the FOV of the client, doing interpolation between old and new if requested
// Input  : FOV - New FOV
//			zoomRate - Amount of time (in seconds) to move between old and new FOV
//-----------------------------------------------------------------------------
bool CBasePlayer::SetFOV( CBaseEntity *pRequester, int FOV, float zoomRate, int iZoomStart /* = 0 */ )
{
	using fn_t = bool(__thiscall*)( CBasePlayer*, CBaseEntity*, int, float, int );
	return ((fn_t)Addresses::SetFOV)( this, pRequester, FOV, zoomRate, iZoomStart );
}

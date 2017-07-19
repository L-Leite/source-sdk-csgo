#include "stdafx.h"

int CBasePlayer::GetFOV( void )
{
	int nDefaultFOV;

	// The vehicle's FOV wins if we're asking for a default value
	if ( GetVehicle() )
	{
		CacheVehicleView();
		nDefaultFOV = ( m_flVehicleViewFOV == 0 ) ? GetDefaultFOV() : (int) m_flVehicleViewFOV;
	}
	else
	{
		nDefaultFOV = GetDefaultFOV();
	}
	
	int fFOV = ( m_iFOV == 0 ) ? nDefaultFOV : m_iFOV;

	// If it's immediate, just do it
	if ( m_Local.m_flFOVRate == 0.0f )
		return fFOV;

	float deltaTime = (float)( gpGlobals->curtime - m_flFOVTime ) / m_Local.m_flFOVRate;

	if ( deltaTime >= 1.0f )
	{
		//If we're past the zoom time, just take the new value and stop lerping
		m_iFOVStart = fFOV;
	}
	else
	{
		fFOV = SimpleSplineRemapValClamped( deltaTime, 0.0f, 1.0f, m_iFOVStart, fFOV );
	}

	return fFOV;
}

//-----------------------------------------------------------------------------
// Eye angles
//-----------------------------------------------------------------------------
const QAngle &CBasePlayer::EyeAngles()
{
	// NOTE: Viewangles are measured *relative* to the parent's coordinate system
	CBaseEntity *pMoveParent = const_cast<CBasePlayer*>(this)->GetMoveParent();

	if ( !pMoveParent )
	{
		return pl.v_angle;
	}

	// FIXME: Cache off the angles?
	matrix3x4_t eyesToParent, eyesToWorld;
	AngleMatrix( pl.v_angle, eyesToParent );
	ConcatTransforms( pMoveParent->EntityToWorldTransform(), eyesToParent, eyesToWorld );

	static QAngle angEyeWorld;
	MatrixAngles( eyesToWorld, angEyeWorld );
	return angEyeWorld;
}

void CBasePlayer::SetDefaultFOV( int FOV )
{
	m_iDefaultFOV = (FOV == 0) ? GameRules()->DefaultFOV() : FOV;
}


const QAngle &CBasePlayer::LocalEyeAngles()
{
	return pl.v_angle;
}


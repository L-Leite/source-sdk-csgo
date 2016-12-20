//========= Copyright © 1996-2005, Valve Corporation, All rights reserved. ============//
//
// Purpose: 
//
// $NoKeywords: $
//=============================================================================//

#include "stdafx.h"
#include "cs_gamemovement.h"   

IGameMovement *g_pGameMovement = nullptr;

const float DuckSpeedMultiplier = 0.34f;												

bool CGameMovement::IsDead( void ) const
{
	return (player->m_iHealth <= 0) ? true : false;
}

void CCSGameMovement::CustomHandleDuckingSpeedCrop()
{
	if ( !m_bSpeedCropped )
	{
		if ( (mv->m_nButtons & IN_DUCK) /*|| (player->m_Local.m_bDucking)*/ || (player->GetFlags() & FL_DUCKING) )
		{
			mv->m_flForwardMove *= DuckSpeedMultiplier;
			mv->m_flSideMove *= DuckSpeedMultiplier;
			mv->m_flUpMove *= DuckSpeedMultiplier;
			m_bSpeedCropped = true;
		}
	}
}

//-----------------------------------------------------------------------------
// Purpose: Stop ducking
//-----------------------------------------------------------------------------

bool g_bShouldDoubleDuck = false;

void CCSGameMovement::CustomFinishUnDuck()
{
	trace_t trace;
	Vector newOrigin;

	VectorCopy( mv->GetAbsOrigin(), newOrigin );

	if ( player->GetGroundEntity() != NULL )
	{
		newOrigin += VEC_DUCK_HULL_MIN - VEC_HULL_MIN;
		
		if ( g_bShouldDoubleDuck )
		{
			//newOrigin.z += 32.0f;
			g_bShouldDoubleDuck = false;
		}

	}
	else
	{
		// If in air an letting go of croush, make sure we can offset origin to make
		//  up for uncrouching
		Vector hullSizeNormal = VEC_HULL_MAX - VEC_HULL_MIN;
		Vector hullSizeCrouch = VEC_DUCK_HULL_MAX - VEC_DUCK_HULL_MIN;

		Vector viewDelta = -0.5f * (hullSizeNormal - hullSizeCrouch);

		VectorAdd( newOrigin, viewDelta, newOrigin );
	}

	player->m_Local.m_bDucked = false;
	player->RemoveFlag( FL_DUCKING );
	player->m_Local.m_bDucking = false;
	player->SetViewOffset( GetPlayerViewOffset( false ) );
	player->m_Local.m_nDuckTimeMsecs = 0;

	mv->SetAbsOrigin( newOrigin );

	// Recategorize position since ducking can change origin
	CategorizePosition();
}

bool CCSGameMovement::CustomCanUnduck()
{
	trace_t trace;
	Vector newOrigin;

	if ( m_pCSPlayer->m_bDuckOverride )
		return false;

	if ( player->GetMoveType() == MOVETYPE_NOCLIP )
		return true;

	VectorCopy( mv->GetAbsOrigin(), newOrigin );

	if ( player->GetGroundEntity() != NULL )
	{
		newOrigin += VEC_DUCK_HULL_MIN - VEC_HULL_MIN;
	}
	else
	{
		// If in air an letting go of croush, make sure we can offset origin to make
		//  up for uncrouching
		Vector hullSizeNormal = VEC_HULL_MAX - VEC_HULL_MIN;
		Vector hullSizeCrouch = VEC_DUCK_HULL_MAX - VEC_DUCK_HULL_MIN;

		newOrigin += -0.5f * (hullSizeNormal - hullSizeCrouch);
	}

	/*UTIL_TraceHull( mv->GetAbsOrigin(), newOrigin, VEC_HULL_MIN, VEC_HULL_MAX, PlayerSolidMask(), player, COLLISION_GROUP_PLAYER_MOVEMENT, &trace );

	if ( trace.startsolid || (trace.fraction != 1.0f) )
		return false;*/

	return true;
}

//-----------------------------------------------------------------------------
// Purpose: Finish ducking
//-----------------------------------------------------------------------------
void CCSGameMovement::CustomFinishDuck( void )
{
	Vector hullSizeNormal = VEC_HULL_MAX - VEC_HULL_MIN;
	Vector hullSizeCrouch = VEC_DUCK_HULL_MAX - VEC_DUCK_HULL_MIN;

	Vector viewDelta = 0.5f * (hullSizeNormal - hullSizeCrouch);

	player->SetViewOffset( GetPlayerViewOffset( true ) );
	player->AddFlag( FL_DUCKING );
	player->m_Local.m_bDucking = false;

	if ( !player->m_Local.m_bDucked )
	{
		Vector org = mv->GetAbsOrigin();

		if ( player->GetGroundEntity() != NULL )
		{
			org -= VEC_DUCK_HULL_MIN - VEC_HULL_MIN;
		}
		else
		{
			org += viewDelta;
		}
		mv->SetAbsOrigin( org );

		player->m_Local.m_bDucked = true;
	}

	// See if we are stuck?
	FixPlayerCrouchStuck( true );

	// Recategorize position since ducking can change origin
	CategorizePosition();
}

//-----------------------------------------------------------------------------
// Purpose: See if duck button is pressed and do the appropriate things
//-----------------------------------------------------------------------------
void CCSGameMovement::CustomDuck( void )
{
	int buttonsChanged = (mv->m_nOldButtons ^ mv->m_nButtons);	// These buttons have changed this frame
	int buttonsPressed = buttonsChanged & mv->m_nButtons;			// The changed ones still down are "pressed"
	int buttonsReleased = buttonsChanged & mv->m_nOldButtons;		// The changed ones which were previously down are "released"
	
	m_pCSPlayer->m_flDuckSpeed = 8.f;

	// Check to see if we are in the air.
	bool bInAir = player->GetGroundEntity() == NULL && player->GetMoveType() != MOVETYPE_LADDER;

	if ( mv->m_nButtons & IN_DUCK )
	{
		mv->m_nOldButtons |= IN_DUCK;
	}
	else
	{
		mv->m_nOldButtons &= ~IN_DUCK;
	}

	if ( IsDead() )
	{
		// Unduck
		if ( player->GetFlags() & FL_DUCKING )
		{
			CustomFinishUnDuck();
		}
		return;
	}

	CustomHandleDuckingSpeedCrop();	

	if ( player->GetFlags() & FL_ONGROUND )
	{
		static bool bCanDoubleDuck = false;

		if ( player->GetFlags() & FL_DUCKING )
			bCanDoubleDuck = false;
		else if ( mv->m_nButtons & IN_DUCK )
			bCanDoubleDuck = true;
		else if ( player->m_Local.m_bDucking && bCanDoubleDuck )   
			g_bShouldDoubleDuck = true;
	}

	if ( m_pCSPlayer->m_duckUntilOnGround )
	{
		if ( !bInAir )
		{
			m_pCSPlayer->m_duckUntilOnGround = false;
			if ( CustomCanUnduck() )
			{
				CustomFinishUnDuck();
			}
			return;
		}
		else
		{
			if ( mv->m_vecVelocity.z > 0.0f )
				return;

			// Check if we can un-duck.  We want to unduck if we have space for the standing hull, and
			// if it is less than 2 inches off the ground.
			trace_t trace;
			Vector newOrigin;
			Vector groundCheck;

			VectorCopy( mv->GetAbsOrigin(), newOrigin );
			Vector hullSizeNormal = VEC_HULL_MAX - VEC_HULL_MIN;
			Vector hullSizeCrouch = VEC_DUCK_HULL_MAX - VEC_DUCK_HULL_MIN;
			newOrigin -= (hullSizeNormal - hullSizeCrouch);
			groundCheck = newOrigin;
			groundCheck.z -= player->GetStepSize();

			//UTIL_TraceHull( newOrigin, groundCheck, VEC_HULL_MIN, VEC_HULL_MAX, PlayerSolidMask(), player, COLLISION_GROUP_PLAYER_MOVEMENT, &trace );

			//if ( trace.startsolid || trace.fraction == 1.0f )
			//	return; // Can't even stand up, or there's no ground underneath us

			m_pCSPlayer->m_duckUntilOnGround = false;
			if ( CustomCanUnduck() )
			{
				CustomFinishUnDuck();
			}
			return;
		}
	}

	// Holding duck, in process of ducking or fully ducked?
	if ( (mv->m_nButtons & IN_DUCK) || (player->m_Local.m_bDucking) || (player->GetFlags() & FL_DUCKING) )
	{
		if ( mv->m_nButtons & IN_DUCK )
		{
			bool alreadyDucked = !(player->GetFlags() & FL_DUCKING) ? true : false;

			if ( (buttonsPressed & IN_DUCK) && !(player->GetFlags() & FL_DUCKING) )
			{
				// Use 1 second so super long jump will work
				player->m_Local.m_nDuckTimeMsecs = 1000;
				player->m_Local.m_bDucking = true;
			}

			float duckmilliseconds = max( 0.0f, 1000.0f - (float) player->m_Local.m_nDuckTimeMsecs );
			float duckseconds = duckmilliseconds / 1000.0f;

			//time = max( 0.0, ( 1.0 - (float)player->m_Local.m_flDucktime / 1000.0 ) );

			if ( player->m_Local.m_bDucking )
			{
				// Finish ducking immediately if duck time is over or not on ground
				if ( (duckseconds > TIME_TO_DUCK) ||
					(player->GetGroundEntity() == NULL) ||
					alreadyDucked )
				{
					CustomFinishDuck();
				}
				else
				{
					// Calc parametric time
					float duckFraction = SimpleSpline( duckseconds / TIME_TO_DUCK );
					SetDuckedEyeOffset( duckFraction );
				}
			}
		}
		else
		{
			// Try to unduck unless automovement is not allowed
			// NOTE: When not onground, you can always unduck
			if ( player->m_Local.m_bAllowAutoMovement || player->GetGroundEntity() == NULL )
			{
				if ( (buttonsReleased & IN_DUCK) && (player->GetFlags() & FL_DUCKING) )
				{
					// Use 1 second so super long jump will work
					player->m_Local.m_nDuckTimeMsecs = 1000;
					player->m_Local.m_bDucking = true;  // or unducking
				}

				float duckmilliseconds = max( 0.0f, 1000.0f - (float) player->m_Local.m_nDuckTimeMsecs );
				float duckseconds = duckmilliseconds / 1000.0f;

				if ( CustomCanUnduck() )
				{
					if ( player->m_Local.m_bDucking ||
						player->m_Local.m_bDucked ) // or unducking
					{
						// Finish ducking immediately if duck time is over or not on ground
						if ( (duckseconds > TIME_TO_UNDUCK) ||
							(player->GetGroundEntity() == NULL) )
						{
							CustomFinishUnDuck();
						}
						else
						{
							// Calc parametric time
							float duckFraction = SimpleSpline( 1.0f - (duckseconds / TIME_TO_UNDUCK) );
							SetDuckedEyeOffset( duckFraction );
						}
					}
				}
				else
				{
					// Still under something where we can't unduck, so make sure we reset this timer so
					//  that we'll unduck once we exit the tunnel, etc.
					player->m_Local.m_flLastDuckTime = 1000;
				}
			}
		}
	}
}
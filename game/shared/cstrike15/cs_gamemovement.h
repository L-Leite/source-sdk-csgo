//========= Copyright © 1996-2005, Valve Corporation, All rights reserved. ============//
//
// Purpose: 
//
// $Workfile:     $
// $Date:         $
// $NoKeywords: $
//=============================================================================//
#if !defined( CSGAMEMOVEMENT_H )
#define CSGAMEMOVEMENT_H
#ifdef _WIN32
#pragma once
#endif

#include "gamemovement.h"
#include "cs_gamerules.h"
#include "in_buttons.h"
#include "movevars_shared.h"

#ifdef CLIENT_DLL
	#include "c_cs_player.h"
#else
	#include "cs_player.h"			   
	#include "KeyValues.h"
#endif

#define STAMINA_MAX				100.0
#define STAMINA_COST_JUMP		25.0
#define STAMINA_COST_FALL		20.0
#define STAMINA_RECOVER_RATE	19.0
#define CS_WALK_SPEED			100.0f

extern bool g_bMovementOptimizations;

class CCSGameMovement : public CGameMovement
{
public:
	DECLARE_CLASS( CCSGameMovement, CGameMovement );

	CCSGameMovement();

	virtual void ProcessMovement( CBasePlayer *pPlayer, CMoveData *pMove );
	virtual bool CanAccelerate();
	virtual bool CheckJumpButton( void );
	virtual void ReduceTimers( void );
	virtual void WalkMove( void );
	virtual void AirMove( void );
	virtual bool LadderMove( void );
	virtual void DecayPunchAngle( void );
	virtual void CheckParameters( void );

	// Ducking
	virtual void Duck( void );
	virtual void FinishUnDuck( void );
	virtual void FinishDuck( void );
	virtual bool CanUnduck();
	virtual void HandleDuckingSpeedCrop();
	
	void CustomDuck();
	void CustomFinishUnDuck();
	void CustomFinishDuck();
	bool CustomCanUnduck();
	void CustomHandleDuckingSpeedCrop();
	 
	 

	virtual bool OnLadder( trace_t &trace );
	virtual float LadderDistance( void ) const
	{
		if ( player->GetMoveType() == MOVETYPE_LADDER )
			return 10.0f;
		return 2.0f;
	}

	virtual unsigned int LadderMask( void ) const
	{
		return MASK_PLAYERSOLID & ( ~CONTENTS_PLAYERCLIP );
	}

	virtual float ClimbSpeed( void ) const;
	virtual float LadderLateralMultiplier( void ) const;

public:
	virtual void PlayerMove();

	void CheckForLadders( bool wasOnGround );
	virtual unsigned int PlayerSolidMask( bool brushOnly = false );	///< returns the solid mask for the given player, so bots can have a more-restrictive set

public:
	CCSPlayer *m_pCSPlayer;
};

#endif // CSGAMEMOVEMENT_H
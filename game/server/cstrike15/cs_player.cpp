#include "stdafx.h"

CCSPlayerStateInfo* g_pPlayerStateInfos = nullptr;

bool CCSPlayer::IsVIP() const
{
	return m_isVIP;
}

bool CCSPlayer::IsInBuyZone()
{
	return m_bInBuyZone && !IsVIP();
}

void CCSPlayer::AddAccount( int amount, bool bTrackChange )
{
	m_iAccount += amount;

	if ( m_iAccount < 0 )
		m_iAccount = 0;
	/*else if ( m_iAccount > 16000 )
		m_iAccount = 16000;*/
}

void CCSPlayer::HintMessage( const char* pMessage, bool bDisplayIfDead, bool bOverrideClientSettings /*= false*/ )
{
	using fn_t = bool(__thiscall*)( CHintMessageQueue*, const char*, CHintMessageQueue* );

	if ( bDisplayIfDead || IsAlive() )
		((fn_t)Addresses::HintMessage)( m_pHintMessageQueue, pMessage, m_pHintMessageQueue);
}

bool CCSPlayer::CanPlayerBuy( bool display )
{
	CCSGameRules* mp = CSGameRules(); // On top to fill	some cvars

	// is the player in a buy zone?
	if ( !IsInBuyZone() )
	{
		if ( !mp_buy_anywhere->GetBool() )
		{
			if ( display )
				HintMessage( "#SFUI_BuyMenu_NotInBuyZone", false, true );

			return false;
		}	 		
	}

	// is the player alive?
	if ( m_lifeState != LIFE_ALIVE )
	{
		return false;
	}	   							  	

	int buyTime = (int) (mp_buytime->GetFloat() * 60);

	if ( mp->IsBuyTimeElapsed() )
	{
		if ( display )
			HintMessage( "#SFUI_BuyMenu_YoureOutOfTime", false, true );

		return false;
	}

	if ( m_bIsVIP )
	{
		if ( display )
			HintMessage( "#VIP_cant_buy", false, true );

		return false;
	}
			
	if ( mp->m_bCTCantBuy && (GetTeamNumber() == TEAM_CT) )
	{
		if ( display == true )
			HintMessage( "#CT_cant_buy", false, true );

		return false;
	}

	if ( mp->m_bTCantBuy && (GetTeamNumber() == TEAM_TERRORIST) )
	{
		if ( display == true )
			HintMessage( "#Terrorist_cant_buy", false, true );

		return false;
	}

	return true;
}

bool CCSPlayer::HandleCommand_JoinClass( int iClass )
{
	if ( iClass == CS_CLASS_NONE )
	{
		// User choosed random class
		switch ( GetTeamNumber() )
		{
			case TEAM_TERRORIST:	iClass = RandomInt( FIRST_T_CLASS, LAST_T_CLASS );
				break;

			case TEAM_CT:			iClass = RandomInt( FIRST_CT_CLASS, LAST_CT_CLASS );
				break;

			default:				iClass = CS_CLASS_NONE;
				break;
		}
	}

	// clamp to valid classes
	switch ( GetTeamNumber() )
	{
		case TEAM_TERRORIST:
			iClass = clamp( iClass, FIRST_T_CLASS, LAST_T_CLASS );
			break;
		case TEAM_CT:
			iClass = clamp( iClass, FIRST_CT_CLASS, LAST_CT_CLASS );
			break;
		default:
			iClass = CS_CLASS_NONE;
	}

	// Reset the player's state
	if ( State_Get() == STATE_ACTIVE )
	{
		CSGameRules()->CheckWinConditions();
	}		

	if ( !IsBot() && State_Get() == STATE_ACTIVE ) // Bots are responsible about only switching classes when they join.
	{
		// Kill player if switching classes while alive.
		// This mimics goldsrc CS 1.6, and prevents a player from hiding, and switching classes to
		// make the opposing team think there are more enemies than there really are.
		CommitSuicide();
	}

	if ( m_iClass != iClass )
	{
		m_iClass = iClass;
		SetModelFromClass();		
	}

	if ( State_Get() == STATE_PICKINGCLASS )
	{
		GetIntoGame();
	}
			
	return true;
}

void CCSPlayer::GetIntoGame()
{
	using fn_t = void(__thiscall*)( CCSPlayer* );
	((fn_t)Addresses::GetIntoGame)(this);
}

bool CCSPlayer::HasC4() const
{
	return (Weapon_OwnsThisType( "weapon_c4" ) != NULL);
}

bool CCSPlayer::HasShield() const
{
#ifdef CS_SHIELD_ENABLED
	return m_bHasShield;
#else
	return false;
#endif
}


bool CCSPlayer::IsShieldDrawn() const
{
#ifdef CS_SHIELD_ENABLED
	return m_bShieldDrawn;
#else
	return false;
#endif
}

void CCSPlayer::PhysObjectSleep()
{
	IPhysicsObject *pObj = VPhysicsGetObject();
	if ( pObj )
		pObj->Sleep();
}

void CCSPlayer::ResetMaxSpeed()
{
	float speed;

	CWeaponCSBase *pWeapon = GetActiveCSWeapon();
	if ( IsObserver() )
	{
		// Player gets speed bonus in observer mode
		speed = 900;
	}
	else if ( CSGameRules()->IsFreezePeriod() )
	{
		// Player should not move during the freeze period
		speed = 1;
	}
	else if ( m_bIsVIP == true )  // VIP is slow due to the armour he's wearing
	{
		speed = 227;
	}
	else if ( pWeapon )
	{
		if ( HasShield() && IsShieldDrawn() )
		{
			speed = 160;
		}
		else
			speed = pWeapon->GetMaxSpeed(); // Get player speed from selected weapon
	}
	else
	{
		// No active item, set the player's speed to default
		speed = 240;
	}						 

	SetMaxSpeed( speed );
}

CWeaponCSBase* CCSPlayer::GetActiveCSWeapon() const
{
	// dont use dynamic_cast to not call our constructor
	return static_cast< CWeaponCSBase* >(GetActiveWeapon());
}

void CCSPlayer::State_Transition( CSPlayerState newState )
{
	using fn_t = void( __thiscall* )( CCSPlayer*, CSPlayerState );
	ConsoleDebugW( L"Changing to %i state\n", newState );

	if ( newState == STATE_PICKINGCLASS )
	{
		State_Leave();
		State_Enter( newState );
		return;
	}

	((fn_t)Addresses::StateTransition)( this, newState );
}

void CCSPlayer::State_Enter( CSPlayerState newState )
{	 
	static CCSPlayerStateInfo playerState_PickingClass = { STATE_PICKINGCLASS, "STATE_PICKINGCLASS", &CCSPlayer::State_Enter_PICKINGCLASS, nullptr, nullptr };
	m_iPlayerState = newState;
	m_pCurStateInfo = &playerState_PickingClass;

	//if ( cs_ShowStateTransitions.GetInt() == -1 || cs_ShowStateTransitions.GetInt() == entindex() )
	{
		if ( m_pCurStateInfo )
			ConsoleDebugA( "ShowStateTransitions: entering '%s'\n", m_pCurStateInfo->m_pStateName );
		else
			ConsoleDebugA( "ShowStateTransitions: entering #%d\n", newState );
	}

	// Initialize the new state.
	if ( m_pCurStateInfo && m_pCurStateInfo->pfnEnterState )
		(this->*m_pCurStateInfo->pfnEnterState)();
}										   

void CCSPlayer::State_Leave()
{
	if ( m_pCurStateInfo && m_pCurStateInfo->pfnLeaveState )
	{
		(this->*m_pCurStateInfo->pfnLeaveState)();
	}
}

void CCSPlayer::State_Enter_PICKINGCLASS()
{
	ConsoleDebugW( L"Entered STATE_PICKINGCLASS!\n" );

	if ( CommandLine()->FindParm( "-makereslists" ) ) // don't show the menu when making reslists
	{
		g_pEngineServer->ClientCommand( edict(), "joinclass 0\n" );
		return;
	}

	// go to spec mode, if dying keep deathcam
	if ( GetObserverMode() == OBS_MODE_DEATHCAM )
	{
		StartObserverMode( OBS_MODE_DEATHCAM );
	}
	else
	{
		StartObserverMode( OBS_MODE_FIXED );
	}

	m_iClass = CS_CLASS_NONE;

	// Set the player's speed
	ResetMaxSpeed();
	PhysObjectSleep();

	// show the class menu:
	if ( GetTeamNumber() == TEAM_TERRORIST && TerroristPlayerModels.Count() > 1 )
	{
#ifdef VGUI_TEST
		ShowViewPortPanel( PANEL_CLASS_TER );
#else
		g_pEngineServer->ClientCommand( edict(), "classmenu" );
#endif
	}
	else if ( GetTeamNumber() == TEAM_CT && CTPlayerModels.Count() > 1 )
	{
#ifdef VGUI_TEST
		ShowViewPortPanel( PANEL_CLASS_CT );
#else
		g_pEngineServer->ClientCommand( edict(), "classmenu" );
#endif
	}
	else
	{
		HandleCommand_JoinClass( 0 );
	}
}

void CCSPlayer::SetModelFromClass( void )
{
	if ( GetTeamNumber() == TEAM_TERRORIST )
	{
		int index = m_iClass - FIRST_T_CLASS;
		if ( index < 0 || index >= TerroristPlayerModels.Count() )
		{
			index = RandomInt( 0, TerroristPlayerModels.Count() - 1 );
			m_iClass = index + FIRST_T_CLASS; // clean up players who selected a higher class than we support yet
		}
		ConsoleDebugW( L"Setting %S to player %S\n", TerroristPlayerModels[ index ], GetPlayerName() );
		SetModel( TerroristPlayerModels[ index ] );
	}
	else if ( GetTeamNumber() == TEAM_CT )
	{
		int index = m_iClass - FIRST_CT_CLASS;
		if ( index < 0 || index >= CTPlayerModels.Count() )
		{
			index = RandomInt( 0, CTPlayerModels.Count() - 1 );
			m_iClass = index + FIRST_CT_CLASS; // clean up players who selected a higher class than we support yet
		}
		ConsoleDebugW( L"Setting %S to player %S\n", CTPlayerModels[ index ], GetPlayerName() );
		SetModel( CTPlayerModels[ index ] );
	}
	else
	{
		ConsoleDebugW( L"Setting default %S to player %S\n", CTPlayerModels[ 0 ], GetPlayerName() );
		SetModel( CTPlayerModels[ 0 ] );
	}

	strcpy_s( m_szArmsModel, "models/weapons/t_arms_phoenix.mdl" );
}

bool CCSPlayer::ShouldRunRateLimitedCommand( const CCommand &args )
{
	using fn_t = bool(__thiscall*)( CCSPlayer*, const CCommand& );
	return ((fn_t)Addresses::ShouldRunRateLimitedCommand)( this, args );
}
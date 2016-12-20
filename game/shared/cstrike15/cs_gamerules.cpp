#include "stdafx.h"

#ifdef CLIENT_DLL
#else
#include "cs_player.h"
#include "cs_gamerules.h"
#endif

// Let's initialize this here for now	
CGlobalVars* gpGlobals = nullptr;

ConVar* mp_c4timer = nullptr;
ConVar* mp_buytime = nullptr;
ConVar* mp_buy_anywhere = nullptr;
ConVar* mp_freezetime = nullptr;
ConVar* mp_playerid = nullptr;

#ifndef CLIENT_DLL
ConVar* mp_autoteambalance = nullptr;
#endif // !CLIENT_DLL

CCSGameRules* CSGameRules()
{
	static bool bInit = false;

	if ( !bInit )
	{
		mp_buytime = cvar->FindVar( "mp_buytime" );
		ConsoleDebugW( L"mp_buytime: %p\n", mp_buytime );

		mp_buy_anywhere = cvar->FindVar( "mp_buy_anywhere" );
		ConsoleDebugW( L"mp_buy_anywhere: %p\n", mp_buy_anywhere );

		bInit = true;
	}

	return (CCSGameRules*) *g_pGameRules;
}

float CCSGameRules::GetRoundElapsedTime()
{
	return gpGlobals->curtime - m_fRoundStartTime;
}

bool CCSGameRules::IsFreezePeriod()
{
	return m_bFreezePeriod;
}


bool CCSGameRules::IsVIPMap() const
{
	//MIKETODO: VIP mode
	return false;
}


bool CCSGameRules::IsBombDefuseMap() const
{
	return m_bMapHasBombTarget;
}

bool CCSGameRules::IsHostageRescueMap() const
{
	return m_bMapHasRescueZone;
}

bool CCSGameRules::IsLogoMap() const
{
	return m_bLogoMap;
}

float CCSGameRules::GetBuyTimeLength() const
{
	return (mp_buytime->GetFloat() * 60);
}

bool CCSGameRules::IsBuyTimeElapsed()
{
	return (GetRoundElapsedTime() > GetBuyTimeLength());
}

bool CCSGameRules::CheckWinConditions()
{
	using fn_t = bool(__thiscall*)( CCSGameRules* );
	return ((fn_t)Addresses::CheckWinConditions)( this );
}

// To implement it myself I would need the entity list to work and it would need more stuff to be reversed and used, fuck it
bool CCSGameRules::IsThereABomber()
{
	using fn_t = bool( __thiscall* )(CCSGameRules*);
	return ((fn_t) Addresses::IsThereABomber)(this);
}

// Same thing here
bool CCSGameRules::IsThereABomb()
{
	using fn_t = bool(__thiscall*)( CCSGameRules* );
	return ((fn_t)Addresses::IsThereABomb)( this );
}

void CCSGameRules::GiveC4()
{
	using fn_t = void( __thiscall* )(CCSGameRules*);
	((fn_t) Addresses::GiveC4)(this);
}
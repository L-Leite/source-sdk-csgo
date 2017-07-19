#include "stdafx.h"

#ifdef CLIENT_DLL
#else
#include "cs_player.h"
#include "cs_gamerules.h"
#endif

CViewVectors* GetCSViewVectors()
{
	return (CViewVectors*)Addresses::CSViewVectors;
}

CCSGameRules* CSGameRules()
{			   
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
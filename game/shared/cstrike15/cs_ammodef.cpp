//========= Copyright © 1996-2005, Valve Corporation, All rights reserved. ============//
//
// Purpose:
//
//=============================================================================//

#include "stdafx.h"
#include "cs_ammodef.h"

CCSAmmoDef* GetCSAmmoDef()
{
	CCSAmmoDef* res = (CCSAmmoDef*) GetAmmoDef();

	static bool bChangedMoneyValues = false;

	if ( !bChangedMoneyValues )
	{
		bChangedMoneyValues = true;

		ConsoleDebugW( L"\n--------------------------------------------------\nBULLET INDEXES\n" );
		ConsoleDebugW( L"Index( BULLET_PLAYER_50AE ): %i\n", res->Index( BULLET_PLAYER_50AE ) );
		ConsoleDebugW( L"Index( BULLET_PLAYER_762MM ): %i\n", res->Index( BULLET_PLAYER_762MM ) );
		ConsoleDebugW( L"Index( BULLET_PLAYER_556MM ): %i\n", res->Index( BULLET_PLAYER_556MM ) );
		ConsoleDebugW( L"Index( BULLET_PLAYER_556MM_SMALL ): %i\n", res->Index( BULLET_PLAYER_556MM_SMALL ) );
		ConsoleDebugW( L"Index( BULLET_PLAYER_556MM_BOX ): %i\n", res->Index( BULLET_PLAYER_556MM_BOX ) );
		ConsoleDebugW( L"Index( BULLET_PLAYER_338MAG ): %i\n", res->Index( BULLET_PLAYER_338MAG ) );
		ConsoleDebugW( L"Index( BULLET_PLAYER_9MM ): %i\n", res->Index( BULLET_PLAYER_9MM ) );
		ConsoleDebugW( L"Index( BULLET_PLAYER_BUCKSHOT ): %i\n", res->Index( BULLET_PLAYER_BUCKSHOT ) );
		ConsoleDebugW( L"Index( BULLET_PLAYER_45ACP ): %i\n", res->Index( BULLET_PLAYER_45ACP ) );
		ConsoleDebugW( L"Index( BULLET_PLAYER_357SIG ): %i\n", res->Index( BULLET_PLAYER_357SIG ) );
		ConsoleDebugW( L"Index( BULLET_PLAYER_357SIG_SMALL ): %i\n", res->Index( BULLET_PLAYER_357SIG_SMALL ) );
		ConsoleDebugW( L"Index( BULLET_PLAYER_357SIG_MIN ): %i\n", res->Index( BULLET_PLAYER_357SIG_MIN ) );

		ConsoleDebugW( L"Index( BULLET_PLAYER_57MM ): %i\n", res->Index( BULLET_PLAYER_57MM ) );
		ConsoleDebugW( L"Index( AMMO_TYPE_HEGRENADE ): %i\n", res->Index( AMMO_TYPE_HEGRENADE ) );
		ConsoleDebugW( L"Index( AMMO_TYPE_FLASHBANG ): %i\n", res->Index( AMMO_TYPE_FLASHBANG ) );
		ConsoleDebugW( L"Index( AMMO_TYPE_SMOKEGRENADE ): %i\n", res->Index( AMMO_TYPE_SMOKEGRENADE ) );
		ConsoleDebugW( L"Index( AMMO_TYPE_MOLOTOV ): %i\n", res->Index( AMMO_TYPE_MOLOTOV ) );
		ConsoleDebugW( L"Index( AMMO_TYPE_DECOY ): %i\n", res->Index( AMMO_TYPE_DECOY ) );
		ConsoleDebugW( L"Index( AMMO_TYPE_TASERCHARGE ): %i\n", res->Index( AMMO_TYPE_TASERCHARGE ) );
		ConsoleDebugW( L"Index( BULLET_PLAYER_357SIG_P250 ): %i\n", res->Index( BULLET_PLAYER_357SIG_P250 ) );
		ConsoleDebugW( L"Index( AMMO_TYPE_HEALTHSHOT ): %i\n", res->Index( AMMO_TYPE_HEALTHSHOT ) );
		ConsoleDebugW( L"Index( AMMO_TYPE_TAGRENADE ): %i\n", res->Index( AMMO_TYPE_TAGRENADE ) );
		ConsoleDebugW( L"\n--------------------------------------------------\n\n" );

		res->m_csAmmo[ res->Index( BULLET_PLAYER_9MM ) ].cost = 20;
		res->m_csAmmo[ res->Index( BULLET_PLAYER_9MM ) ].buySize = 30;
		res->m_csAmmo[ res->Index( BULLET_PLAYER_45ACP ) ].cost = 25;
		res->m_csAmmo[ res->Index( BULLET_PLAYER_45ACP ) ].buySize = 12;
		res->m_csAmmo[ res->Index( BULLET_PLAYER_357SIG_SMALL ) ].cost = 25; // This is hkp2000 i think
		res->m_csAmmo[ res->Index( BULLET_PLAYER_357SIG_SMALL ) ].buySize = 12;
		res->m_csAmmo[ res->Index( BULLET_PLAYER_357SIG_P250 ) ].cost = 50;
		res->m_csAmmo[ res->Index( BULLET_PLAYER_357SIG_P250 ) ].buySize = 13;
		res->m_csAmmo[ res->Index( BULLET_PLAYER_50AE ) ].cost = 40;
		res->m_csAmmo[ res->Index( BULLET_PLAYER_50AE ) ].buySize = 7;
		res->m_csAmmo[ res->Index( BULLET_PLAYER_BUCKSHOT ) ].cost = 65;
		res->m_csAmmo[ res->Index( BULLET_PLAYER_BUCKSHOT ) ].buySize = 8;
		res->m_csAmmo[ res->Index( BULLET_PLAYER_57MM ) ].cost = 50;
		res->m_csAmmo[ res->Index( BULLET_PLAYER_57MM ) ].buySize = 50;
		res->m_csAmmo[ res->Index( BULLET_PLAYER_556MM ) ].cost = 60;
		res->m_csAmmo[ res->Index( BULLET_PLAYER_556MM ) ].buySize = 30;
		res->m_csAmmo[ res->Index( BULLET_PLAYER_556MM_SMALL ) ].cost = 60;
		res->m_csAmmo[ res->Index( BULLET_PLAYER_556MM_SMALL ) ].buySize = 30;
		res->m_csAmmo[ res->Index( BULLET_PLAYER_762MM ) ].cost = 80;
		res->m_csAmmo[ res->Index( BULLET_PLAYER_762MM ) ].buySize = 30;
		res->m_csAmmo[ res->Index( BULLET_PLAYER_338MAG ) ].cost = 125;
		res->m_csAmmo[ res->Index( BULLET_PLAYER_338MAG ) ].buySize = 10;
	}

	return res;
}

CAmmoDef* GetAmmoDef()
{
	return *(CAmmoDef**) Addresses::AmmoDef;
}


//-----------------------------------------------------------------------------
void CCSAmmoDef::AddAmmoCost( int index, int cost, int buySize )
{
	if ( index < 1 || index >= m_nAmmoIndex )
		return;

	m_csAmmo[index].buySize = buySize;
	m_csAmmo[index].cost = cost;
}

void CCSAmmoDef::AddAmmoCost( char const* name, int cost, int buySize )
{
	int index = Index( name );
	if ( index < 1 || index >= m_nAmmoIndex )
		return;

	m_csAmmo[ index ].buySize = buySize;
	m_csAmmo[ index ].cost = cost;
}

//-----------------------------------------------------------------------------
int CCSAmmoDef::GetBuySize( int index ) const
{
	if ( index < 1 || index >= m_nAmmoIndex )
		return 0;

	return m_csAmmo[index].buySize;
}


//-----------------------------------------------------------------------------
int CCSAmmoDef::GetCost( int index ) const
{
	if ( index < 1 || index >= m_nAmmoIndex )
		return 0;

	return m_csAmmo[index].cost;
}


//-----------------------------------------------------------------------------
CCSAmmoDef::CCSAmmoDef(void)
{
	memset( m_csAmmo, 0, sizeof( m_csAmmo ) );
}


//-----------------------------------------------------------------------------
CCSAmmoDef::~CCSAmmoDef( void )
{
}

//-----------------------------------------------------------------------------

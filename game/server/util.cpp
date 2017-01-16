#include "stdafx.h"

// returns a CBaseEntity pointer to a player by index.  Only returns if the player is spawned and connected
// otherwise returns NULL
// Index is 1 based
CBasePlayer	*UTIL_PlayerByIndex( int playerIndex )
{
	CBasePlayer *pPlayer = NULL;

	if ( playerIndex > 0 && playerIndex <= gpGlobals->maxClients )
	{
		edict_t *pPlayerEdict = INDEXENT( playerIndex );
		if ( pPlayerEdict && !pPlayerEdict->IsFree() )
		{
			pPlayer = (CBasePlayer*)GetContainingEntity( pPlayerEdict );
		}
	}
	
	return pPlayer;
}

//------------------------------------------------------------------------------
// Purpose : Creates both an decal and any associated impact effects (such
//			 as flecks) for the given iDamageType and the trace's end position
// Input   :
// Output  :
//------------------------------------------------------------------------------
void UTIL_ImpactTrace( trace_t *pTrace, int iDamageType, char *pCustomImpactName )
{
	CBaseEntity *pEntity = pTrace->m_pEnt;

	// Is the entity valid, is the surface sky?
	if ( !pEntity || !UTIL_IsValidEntity( pEntity ) || (pTrace->surface.flags & SURF_SKY) )
		return;

	if ( pTrace->fraction == 1.0 )
		return;

	pEntity->ImpactTrace( pTrace, iDamageType, pCustomImpactName );
}

bool UTIL_IsValidEntity( CBaseEntity *pEnt )
{
	edict_t *pEdict = pEnt->edict();
	if ( !pEdict || pEdict->IsFree() )
		return false;
	return true;
}

//
// Get the local player on a listen server - this is for multiplayer use only
// 
CBasePlayer *UTIL_GetListenServerHost( void )
{
	// no "local player" if this is a dedicated server or a single player game
	if ( engine->IsDedicatedServer() )
	{
		Assert( !"UTIL_GetListenServerHost" );
		Warning( "UTIL_GetListenServerHost() called from a dedicated server or single-player game.\n" );
		return NULL;
	}

	return UTIL_PlayerByIndex( 1 );
}
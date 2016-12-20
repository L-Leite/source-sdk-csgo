#include "stdafx.h"

#include "model_types.h"

//-----------------------------------------------------------------------------
//
// Shared client/server trace filter code
//
//-----------------------------------------------------------------------------
/*bool PassServerEntityFilter( const IHandleEntity *pTouch, const IHandleEntity *pPass )
{
	if ( !pPass )
		return true;

	if ( pTouch == pPass )
		return false;

	const CBaseEntity *pEntTouch = EntityFromEntityHandle( pTouch );
	const CBaseEntity *pEntPass = EntityFromEntityHandle( pPass );
	if ( !pEntTouch || !pEntPass )
		return true;

	// don't clip against own missiles
	if ( pEntTouch->GetOwnerEntity() == pEntPass )
		return false;

	// don't clip against owner
	if ( pEntPass->GetOwnerEntity() == pEntTouch )
		return false;


	return true;
}

//-----------------------------------------------------------------------------
// Simple trace filter
//-----------------------------------------------------------------------------
CTraceFilterSimple::CTraceFilterSimple( const IHandleEntity *passedict, int collisionGroup,
										ShouldHitFunc_t pExtraShouldHitFunc )
{
	m_pPassEnt = passedict;
	m_collisionGroup = collisionGroup;
	m_pExtraShouldHitCheckFunction = pExtraShouldHitFunc;
}

//-----------------------------------------------------------------------------
// A standard filter to be applied to just about everything.
//-----------------------------------------------------------------------------
bool StandardFilterRules( IHandleEntity *pHandleEntity, int fContentsMask )
{
	CBaseEntity *pCollide = EntityFromEntityHandle( pHandleEntity );

	// Static prop case...
	if ( !pCollide )
		return true;

	SolidType_t solid = pCollide->GetSolid();
	const model_t *pModel = pCollide->GetModel();

	if ( (modelinfo->GetModelType( pModel ) != mod_brush) || (solid != SOLID_BSP && solid != SOLID_VPHYSICS) )
	{
		if ( (fContentsMask & CONTENTS_MONSTER) == 0 )
			return false;
	}

	// This code is used to cull out tests against see-thru entities
	if ( !(fContentsMask & CONTENTS_WINDOW) )
	{
#ifdef CLIENT_DLL
		if ( g_pClientLeafSystem->GetTranslucencyType( pCollide->RenderHandle() ) == RENDERABLE_IS_TRANSLUCENT )
			return false;
#else
		bool bIsTranslucent = modelinfo->IsTranslucent( pModel );
		bool bIsTwoPass = modelinfo->IsTranslucentTwoPass( pModel );
		if ( bIsTranslucent && !bIsTwoPass )
			return false;
#endif
	}

	// FIXME: this is to skip BSP models that are entities that can be 
	// potentially moved/deleted, similar to a monster but doors don't seem to 
	// be flagged as monsters
	// FIXME: the FL_WORLDBRUSH looked promising, but it needs to be set on 
	// everything that's actually a worldbrush and it currently isn't
	if ( !(fContentsMask & CONTENTS_MOVEABLE) && (pCollide->GetMoveType() == MOVETYPE_PUSH) )// !(touch->flags & FL_WORLDBRUSH) )
		return false;

	return true;
}


//-----------------------------------------------------------------------------
// The trace filter!
//-----------------------------------------------------------------------------
bool CTraceFilterSimple::ShouldHitEntity( IHandleEntity *pHandleEntity, int contentsMask )
{
	if ( !StandardFilterRules( pHandleEntity, contentsMask ) )
		return false;

	if ( m_pPassEnt )
	{
		if ( !PassServerEntityFilter( pHandleEntity, m_pPassEnt ) )
		{
			return false;
		}
	}

	// Don't test if the game code tells us we should ignore this collision...
	CBaseEntity *pEntity = EntityFromEntityHandle( pHandleEntity );
	if ( !pEntity )
		return false;
	if ( !pEntity->ShouldCollide( m_collisionGroup, contentsMask ) )
		return false;
	if ( pEntity && !GameRules()->ShouldCollide( m_collisionGroup, pEntity->GetCollisionGroup() ) )
		return false;
	if ( m_pExtraShouldHitCheckFunction &&
		 (! ( m_pExtraShouldHitCheckFunction( pHandleEntity, contentsMask ) ) ) )
		return false;
	return true;
}*/
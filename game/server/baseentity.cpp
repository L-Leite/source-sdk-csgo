#include "stdafx.h"

int* CBaseEntity::m_nDebugPlayer = nullptr;
bool CBaseEntity::s_bAbsQueriesValid = true;

// This EmitSound seems to not crash
void CBaseEntity::EmitSound( const char* soundname, CBaseEntity* entityAgainForSomeReason )
{
	using fn_t = void( __thiscall* )(CBaseEntity*, const char*, CBaseEntity*);
	((fn_t) Addresses::EmitSound)(this, soundname, entityAgainForSomeReason);
}

//-----------------------------------------------------------------------------
// Hits triggers with raycasts
//-----------------------------------------------------------------------------
class CTriggerTraceEnum : public IEntityEnumerator
{
public:
	CTriggerTraceEnum( Ray_t *pRay, const CTakeDamageInfo &info, const Vector& dir, int contentsMask ) :
		m_info( info ), m_VecDir( dir ), m_ContentsMask( contentsMask ), m_pRay( pRay )
	{
	}

	virtual bool EnumEntity( IHandleEntity *pHandleEntity )
	{
		trace_t tr;

		CBaseEntity *pEnt = gEntList->GetBaseEntity( pHandleEntity->GetRefEHandle() );

		// Done to avoid hitting an entity that's both solid & a trigger.
		if ( pEnt->IsSolid() )
			return true;

		enginetrace->ClipRayToEntity( *m_pRay, m_ContentsMask, pHandleEntity, &tr );
		if ( tr.fraction < 1.0f )
		{
			pEnt->DispatchTraceAttack( m_info, m_VecDir, &tr );
			ApplyMultiDamage();
		}

		return true;
	}

private:
	Vector m_VecDir;
	int m_ContentsMask;
	Ray_t *m_pRay;
	CTakeDamageInfo m_info;
};

void CBaseEntity::TraceAttackToTriggers( const CTakeDamageInfo &info, const Vector& start, const Vector& end, const Vector& dir )
{
	Ray_t ray;
	ray.Init( start, end );

	CTriggerTraceEnum triggerTraceEnum( &ray, info, dir, MASK_SHOT );
	enginetrace->EnumerateEntities( ray, true, &triggerTraceEnum );
}

int CBaseEntity::GetTeamNumber( void ) const
{
	return m_iTeamNum;
}

int CBaseEntity::PrecacheModel( const char* name )
{
	using fn_t = int(__thiscall*)( const char* );
	ConsoleDebugW( L"Precaching %S...\n", name );
	return ((fn_t) Addresses::PrecacheModel)( name );
}

CBaseEntity *CBaseEntity::GetGroundEntity( void )
{
	return m_hGroundEntity;
}

model_t *CBaseEntity::GetModel( void )
{
	return (model_t *) modelinfo->GetModel( GetModelIndex() );
}

//-----------------------------------------------------------------------------
// Purpose: Calculates the absolute position of an edict in the world
//			assumes the parent's absolute origin has already been calculated
//-----------------------------------------------------------------------------
void CBaseEntity::CalcAbsolutePosition( void )
{		  
	using fn_t = void(__thiscall*)(CBaseEntity*);
	((fn_t)Addresses::CalcAbsolutePosition)( this );
}
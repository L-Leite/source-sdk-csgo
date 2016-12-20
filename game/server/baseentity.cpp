#include "stdafx.h"

// This EmitSound seems to not crash
void CBaseEntity::EmitSound( const char* soundname, CBaseEntity* entityAgainForSomeReason )
{
	using fn_t = void( __thiscall* )(CBaseEntity*, const char*, CBaseEntity*);
	((fn_t) Addresses::EmitSound)(this, soundname, entityAgainForSomeReason);
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
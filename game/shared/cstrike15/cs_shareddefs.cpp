//========= Copyright © 1996-2005, Valve Corporation, All rights reserved. ============//
//
// Purpose: 
//
//=============================================================================//

#include "stdafx.h"
#include "cs_shareddefs.h"


CCSClassInfo g_ClassInfos[] =
{
	{ "None" },

	{ "Phoenix Connection" },
	{ "L337 KREW" },
	{ "Arctic Avengers" },
	{ "Guerilla Warfare" },

	{ "Seal Team 6" },
	{ "GSG-9" },
	{ "SAS" },
	{ "GIGN" }
};

const CCSClassInfo* GetCSClassInfo( int i )
{
	Assert( i >= 0 && i < ARRAYSIZE( g_ClassInfos ) );
	return &g_ClassInfos[i];
}


// Construct some arrays of player model strings, so we can statically initialize CUtlVectors for general usage
const char *CTPlayerModelStrings[] =
{
	"models/player/custom_player/legacy/ctm_st6_variant_urban.mdl",
	"models/player/custom_player/legacy/ctm_st6_variant_gsg9.mdl",
	"models/player/custom_player/legacy/ctm_st6_variant_sas.mdl",
	"models/player/ctm_gign.mdl",
};

const char *TerroristPlayerModelStrings[] =
{
	"models/player/custom_player/legacy/tm_phoenix_variant_classic.mdl",
	"models/player/tm_leet_varianta.mdl",
	"models/player/custom_player/legacy/tm_phoenix_variant_arctic.mdl",
	"models/player/custom_player/legacy/tm_phoenix_variant_guerilla.mdl",
};
CUtlVectorInitialized< const char * > CTPlayerModels( CTPlayerModelStrings, ARRAYSIZE( CTPlayerModelStrings ) );
CUtlVectorInitialized< const char * > TerroristPlayerModels( TerroristPlayerModelStrings, ARRAYSIZE( TerroristPlayerModelStrings ) );

PlayerModelInfo g_PlayerModelInfo;

PlayerModelInfo::PlayerModelInfo()
{
	memset( this, 0, sizeof( PlayerModelInfo ) );
	m_iCTPlayerModels = m_iTerroristPlayerModels = m_iPlayerModels = 0;
	Pad[ 0 ] = Pad[ 1 ] = -1;
}

void PlayerModelInfo::Precache()
{
	ConsoleDebugW( L"PlayerModelInfo::Cache called!\n" );

	memset( this, 0, sizeof( PlayerModelInfo ) ); // gotta reset every map

	AddModel( "tm_phoenix" );
	AddModel( "tm_leet_varianta" );
	AddModel( "tm_balkan_varianta" );
	AddModel( "tm_separatist" );
	AddModel( "tm_anarchist" );
	m_iTerroristPlayerModels = 5;

	AddModel( "ctm_st6" );
	AddModel( "ctm_gsg9" );
	AddModel( "ctm_sas" );
	AddModel( "ctm_gign" );
	AddModel( "ctm_idf" );
	m_iCTPlayerModels = 5;			 

	// Prob wont need to set CT arms
	strcpy_s( m_szCTArmsModel, "models/weapons/t_arms_phoenix.mdl" );
	strcpy_s( m_szTerroristArmsModel, "models/weapons/t_arms_phoenix.mdl" );
}

void PlayerModelInfo::AddModel( char* szModel )
{
	using fn_t = void(__thiscall*)( PlayerModelInfo*, char* );
	((fn_t) Addresses::AddModel)( this, szModel );
}
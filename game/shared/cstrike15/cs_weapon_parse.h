//========= Copyright © 1996-2005, Valve Corporation, All rights reserved. ============//
//
// Purpose: 
//
//=============================================================================//

#ifndef CS_WEAPON_PARSE_H
#define CS_WEAPON_PARSE_H
#ifdef _WIN32
#pragma once
#endif


#include "weapon_parse.h"
#include "networkvar.h"


//--------------------------------------------------------------------------------------------------------
enum CSWeaponType
{

	WEAPONTYPE_KNIFE=0,	
	WEAPONTYPE_PISTOL,
	WEAPONTYPE_SUBMACHINEGUN,
	WEAPONTYPE_RIFLE,
	WEAPONTYPE_SHOTGUN,
	WEAPONTYPE_SNIPER_RIFLE,
	WEAPONTYPE_MACHINEGUN,
	WEAPONTYPE_C4,
	WEAPONTYPE_GRENADE,
	WEAPONTYPE_UNKNOWN

};


//--------------------------------------------------------------------------------------------------------
enum CSWeaponID
{
	WEAPON_NONE = 0,

	WEAPON_P228,
	WEAPON_GLOCK,
	WEAPON_SCOUT,
	WEAPON_HEGRENADE,
	WEAPON_XM1014,
	WEAPON_C4,
	WEAPON_MAC10,
	WEAPON_AUG,
	WEAPON_SMOKEGRENADE,
	WEAPON_ELITE,
	WEAPON_FIVESEVEN,
	WEAPON_UMP45,
	WEAPON_SG550,

	WEAPON_GALIL,
	WEAPON_FAMAS,
	WEAPON_USP,
	WEAPON_AWP,
	WEAPON_MP5NAVY,
	WEAPON_M249,
	WEAPON_M3,
	WEAPON_M4A1,
	WEAPON_TMP,
	WEAPON_G3SG1,
	WEAPON_FLASHBANG,
	WEAPON_DEAGLE,
	WEAPON_SG552,
	WEAPON_AK47,
	WEAPON_KNIFE,
	WEAPON_P90,

	WEAPON_SHIELDGUN,	// BOTPORT: Is this still needed?

	WEAPON_KEVLAR,
	WEAPON_ASSAULTSUIT,
	WEAPON_NVG,

	// BaseCombatCharacter defines its own WEAPON_MAX, gotta fix it
	//WEAPON_MAX,		// number of weapons weapon index
};


#define MAX_EQUIPMENT (WEAPON_MAX - WEAPON_KEVLAR)

void PrepareEquipmentInfo( void );

//--------------------------------------------------------------------------------------------------------
const char * WeaponClassAsString( CSWeaponType weaponType );


//--------------------------------------------------------------------------------------------------------
CSWeaponType WeaponClassFromString( const char * weaponType );

//--------------------------------------------------------------------------------------------------------
enum CSWeaponID;


//--------------------------------------------------------------------------------------------------------
const char * WeaponClassAsString( CSWeaponType weaponType );


//--------------------------------------------------------------------------------------------------------
CSWeaponType WeaponClassFromString( const char * weaponType );


//--------------------------------------------------------------------------------------------------------
CSWeaponType WeaponClassFromWeaponID( CSWeaponID weaponID );


//--------------------------------------------------------------------------------------------------------
CSWeaponType WeaponClassFromWeaponID( CSWeaponID weaponID );


//--------------------------------------------------------------------------------------------------------
class CCSWeaponInfo : public FileWeaponInfo_t
{
public:
	DECLARE_CLASS_GAMEROOT( CCSWeaponInfo, FileWeaponInfo_t );
	
	CCSWeaponInfo();
	~CCSWeaponInfo();
	
	virtual void Parse( ::KeyValues *pKeyValuesData, const char *szWeaponName );

	virtual void RefreshDynamicParameters();

	virtual int GetPrimaryClipSize( const CEconItemView* pEconItemView, int bUseAlternative, int unused = 0 );
	virtual int GetSecondaryClipSize( const CEconItemView* pEconItemView, int bUseAlternative, int unused = 0 );
	virtual int GetDefaultPrimaryClipSize( const CEconItemView* pEconItemView, int bUseAlternative, int unused = 0 );
	virtual int GetDefaultSecondaryClipSize( const CEconItemView* pEconItemView, int bUseAlternative, int unused = 0 );
	virtual int GetPrimaryReserveAmmo( const CEconItemView* pEconItemView, int bUseAlternative, int unused = 0 );
	virtual int GetSecondaryReserveAmmo( const CEconItemView* pEconItemView, int bUseAlternative, int unused = 0 );

	int		GetWeaponPrice( void );
	void	SetWeaponPrice( int iPrice ) { m_iWeaponPrice = iPrice; }

public:
	int Pad00;

	int m_iTeam;				// Which team can have this weapon. TEAM_UNASSIGNED if both can have it.

	CSWeaponType m_WeaponType;
	bool m_bFullAuto;

	float m_flHeatPerShot;

	int m_iWeaponPrice;

	float m_flWeaponArmorRatio;

	float m_flMaxSpeed;			// How fast the player can run while this is his primary weapon.
	float m_flMaxSpeedAlt;

	int	  m_iCrosshairMinDistance;
	int	  m_iCrosshairDeltaDistance;

	// Parameters for FX_FireBullets:
	int		m_fPenetration;
	int		m_iDamage;
	float	m_flRange;
	float	m_flRangeModifier;
	int		m_iBullets;
	float	m_flCycleTime;
	float	m_flCycleTimeAlt;

	char m_szHeatEffect[ MAX_WEAPON_STRING ];

	float m_flSmokeColor[ 3 ]; // idk if there's a specific structure for these things

	char m_szMuzzleFlashEffect_1stPerson[ MAX_WEAPON_STRING ];
	char m_szMuzzleFlashEffect_3rdPerson[ MAX_WEAPON_STRING ];
	char m_szEjectBrassEffect[ MAX_WEAPON_STRING ]; 
	char m_szTracerEffect[ MAX_WEAPON_STRING ];  
	int m_iTracerFrequency;

	// Variables that control how fast the weapon's accuracy changes as it is fired.
	float m_fSpread; //0x09D0 
	float m_fSpreadAlt; //0x09D4 
	float m_fInaccuracyCrouch; //0x09D8 
	float m_fInaccuracyCrouchAlt; //0x09DC 
	float m_fInaccuracyStand; //0x09E0 
	float m_fInaccuracyStandAlt; //0x09E4 
	float m_fInaccuracyJump; //0x09E8 
	float m_fInaccuracyJumpAlt; //0x09EC 
	float m_fInaccuracyLand; //0x09F0 
	float m_fInaccuracyLandAlt; //0x09F4 
	float m_fInaccuracyLadder; //0x09F8 
	float m_fInaccuracyLadderAlt; //0x09FC 
	float m_fInaccuracyFire; //0x0A00 
	float m_fInaccuracyFireAlt; //0x0A04 
	float m_fInaccuracyMove; //0x0A08 
	float m_fInaccuracyMoveAlt; //0x0A0C 
	float m_fRecoveryTimeStand; //0x0A10 
	float m_fRecoveryTimeCrouch; //0x0A14 
	float m_fRecoveryTimeStandFinal; //0x0A18 
	float m_fRecoveryTimeCrouchFinal; //0x0A1C 
	float m_fInaccuracyReload; //0x0A20 
	float m_fInaccuracyAltSwitch; //0x0A24 

	float m_fRecoilAngle; //0x0A28 
	float m_fRecoilAngleAlt; //0x0A2C 
	float m_fRecoilAngleVariance; //0x0A30 
	float m_fRecoilAngleVarianceAlt; //0x0A34 
	float m_fRecoilMagnitude; //0x0A38 
	float m_fRecoilMagnitudeAlt; //0x0A3C 
	float m_fRecoilMagnitudeVariance; //0x0A40 
	float m_fRecoilMagnitudeVarianceAlt; //0x0A44 
	int m_iRecoilSeed; //0x0A48 

	float m_fFlinchVelocityModifierLarge; //0x0A4C 
	float m_fFlinchVelocityModifierSmall; //0x0A50 

										  // Delay until the next idle animation after shooting.
	float	m_flTimeToIdleAfterFire;
	float	m_flIdleInterval;

	uint8_t Pad01[ 0x400 ];

	int m_iZoomLevels;

	int Pad02;

	int m_iZoomFov1;
	int m_iZoomFov2;				
	float m_fZoomTime0;
	float m_fZoomTime1;
	float m_fZoomTime2;		 
	bool m_bHideViewModelZoomed;  
	char m_szZoomINSound[ MAX_WEAPON_STRING ];
	char m_ZoomOUTSound[ MAX_WEAPON_STRING ];

	float m_flBotAudibleRange;	// How far away a bot can hear this weapon.
	
	bool  m_bCanUseWithShield;
	
	char m_WrongTeamMsg[32];	// Reference to a string describing the error if someone tries to buy
								// this weapon but they're on the wrong team to have it.
								// Zero-length if no specific message for this weapon.

	char m_szAnimExtension[16];
	char m_szShieldViewModel[64];

	char m_szAddonModel[MAX_WEAPON_STRING];		// If this is set, it is used as the addon model. Otherwise, szWorldModel is used.
	char m_szAddonLocation[MAX_WEAPON_STRING];	
	char m_szSilencerModel[MAX_WEAPON_STRING];	// Alternate model with silencer attached

	float m_fAddonScale;
	
	float m_fThrowVelocity;

	int m_iKillAward;	  
};


#endif // CS_WEAPON_PARSE_H

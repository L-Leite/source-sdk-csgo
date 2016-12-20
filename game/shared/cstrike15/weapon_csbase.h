//========= Copyright © 1996-2005, Valve Corporation, All rights reserved. ============//
//
// Purpose: 
//
//=============================================================================//

#ifndef WEAPON_CSBASE_H
#define WEAPON_CSBASE_H
#ifdef _WIN32
#pragma once
#endif


#include "cs_playeranimstate.h"
#include "cs_weapon_parse.h"


#if defined( CLIENT_DLL )
	#define CWeaponCSBase C_WeaponCSBase
#endif

extern int  ClassnameToWeaponID( const char *classname );
extern int	AliasToWeaponID( const char *alias );
extern const char *WeaponIDToAlias( int id );
extern const char *GetTranslatedWeaponAlias( const char *alias);
extern bool	IsPrimaryWeapon( int id );
extern bool IsSecondaryWeapon( int id );
extern int GetShellForAmmoType( const char *ammoname );

#define SHIELD_VIEW_MODEL "models/weapons/v_shield.mdl"
#define SHIELD_WORLD_MODEL "models/weapons/w_shield.mdl"

class CCSPlayer;

// These are the names of the ammo types that go in the CAmmoDefs and that the 
// weapon script files reference.
#define BULLET_PLAYER_50AE		"BULLET_PLAYER_50AE"
#define BULLET_PLAYER_762MM		"BULLET_PLAYER_762MM"
#define BULLET_PLAYER_556MM		"BULLET_PLAYER_556MM"
#define BULLET_PLAYER_556MM_SMALL "BULLET_PLAYER_556MM_SMALL"
#define BULLET_PLAYER_556MM_BOX	"BULLET_PLAYER_556MM_BOX"
#define BULLET_PLAYER_338MAG	"BULLET_PLAYER_338MAG"
#define BULLET_PLAYER_9MM		"BULLET_PLAYER_9MM"
#define BULLET_PLAYER_BUCKSHOT	"BULLET_PLAYER_BUCKSHOT"
#define BULLET_PLAYER_45ACP		"BULLET_PLAYER_45ACP"
#define BULLET_PLAYER_357SIG	"BULLET_PLAYER_357SIG"
#define BULLET_PLAYER_357SIG_SMALL "BULLET_PLAYER_357SIG_SMALL"
#define BULLET_PLAYER_357SIG_MIN "BULLET_PLAYER_357SIG_MIN"
#define BULLET_PLAYER_57MM		"BULLET_PLAYER_57MM"
#define AMMO_TYPE_HEGRENADE		"AMMO_TYPE_HEGRENADE"
#define AMMO_TYPE_FLASHBANG		"AMMO_TYPE_FLASHBANG"
#define AMMO_TYPE_SMOKEGRENADE	"AMMO_TYPE_SMOKEGRENADE"
#define AMMO_TYPE_MOLOTOV		"AMMO_TYPE_MOLOTOV"
#define AMMO_TYPE_DECOY			"AMMO_TYPE_DECOY"
#define AMMO_TYPE_TASERCHARGE	"AMMO_TYPE_TASERCHARGE"
#define BULLET_PLAYER_357SIG_P250 "BULLET_PLAYER_357SIG_P250"
#define AMMO_TYPE_HEALTHSHOT	"AMMO_TYPE_HEALTHSHOT"
#define AMMO_TYPE_TAGRENADE		"AMMO_TYPE_TAGRENADE"

#define CROSSHAIR_CONTRACT_PIXELS_PER_SECOND	7.0f

// Given an ammo type (like from a weapon's GetPrimaryAmmoType()), this compares it
// against the ammo name you specify.
// MIKETODO: this should use indexing instead of searching and strcmp()'ing all the time.
bool IsAmmoType( int iAmmoType, const char *pAmmoName );

typedef enum
{
	Primary_Mode = 0,
	Secondary_Mode,
} CSWeaponMode;

#if defined( CLIENT_DLL )

	//--------------------------------------------------------------------------------------------------------------
	/**
	*  Returns the client's ID_* value for the currently owned weapon, or ID_NONE if no weapon is owned
	*/
	CSWeaponID GetClientWeaponID( bool primary );

#endif

	//--------------------------------------------------------------------------------------------------------------
	CCSWeaponInfo * GetWeaponInfo( CSWeaponID weaponID );


class CWeaponCSBase : public CBaseCombatWeapon
{
public:
	DECLARE_CLASS( CWeaponCSBase, CBaseCombatWeapon );
	DECLARE_NETWORKCLASS(); 
	DECLARE_PREDICTABLE();

	CWeaponCSBase();

	#ifdef GAME_DLL
		DECLARE_DATADESC();

		virtual const char* GetTracerType();

		virtual void CheckRespawn();
		virtual CBaseEntity* Respawn();
		
		virtual const Vector& GetBulletSpread();
		virtual float	GetDefaultAnimSpeed();

		virtual void	BulletWasFired( const Vector &vecStart, const Vector &vecEnd );
		virtual bool	ShouldRemoveOnRoundRestart();
		virtual void	OnRoundRestart();
		virtual bool	DefaultReload( int iClipSize1, int iClipSize2, int iActivity );

		void SendReloadEvents();

		void Materialize();
		void AttemptToMaterialize();
		virtual void Use( CBaseEntity *pActivator, CBaseEntity *pCaller, USE_TYPE useType, float value );

		virtual bool IsRemoveable();
		virtual void RemoveUnownedWeaponThink();
		
	#endif

	// Make sure to check if these belong to shared virtuals if we ever need to reverse this on the client dll
	virtual int		GetShotgunReloadState();

	// CCSWeaponInfo shit
	virtual int		GetWeaponPrice() const;
	virtual bool	IsFullAuto() const;
	virtual int		GetDamage() const;
	virtual int		GetKillAward() const;
	virtual float	GetCycleTime() const;
	virtual float	GetArmorRatio() const;
	virtual bool	HasTraditionalScope() const;
	virtual float	GetInaccuracyStand( bool bUseAlternative /*maybe?*/ ) const;
	virtual float	GetInaccuracyCrouch( bool bUseAlternative /*?*/ ) const;
	virtual bool	CannotShootUnderwater();
	virtual float	GetRecoilMagnitude( bool bUseAlternative /*?*/ ) const;
	virtual float	GetRecoilMagnitudeVariance( bool bUseAlternative /*?*/ ) const;
	virtual float	GetRecoilAngle( bool bUseAlternative ) const;
	virtual float	GetRecoilAngleVariance( bool bUseAlternative ) const;
	virtual float	GetMaxSpeed() const;	// What's the player's max speed while holding this weapon.
	virtual int		GetZoomLevels() const;
	virtual bool	CanBeUsedWithShield() const;
	virtual const char* GetZoomInSound() const;
	virtual const char* GetZoomOutSound() const;
	virtual float	GetBotAudibleRange() const;
	virtual const char* GetWrongTeamMsg() const;
	virtual const char* GetAnimExtension() const;
	virtual const char* GetShieldViewModel() const;
	virtual const char* GetSilencerModel() const;
	virtual const char* GetAddonScale() const;
	virtual float	GetThrowVelocity() const;
	virtual int		GetZoomFOV( bool bUseAlternative ) const;
	virtual float	GetZoomTime( bool bUseAlternative ) const;
	virtual CSWeaponType GetWeaponType() const;
	virtual const char* GetDefinitionName() const;
	virtual int		GetRecoilSeed();
	virtual const CCSWeaponInfo* GetCSWpnData() const; // Get CS-specific weapon data. I'd rather use a pointer in order to not use any constructor
	virtual int		GetCSZoomLevel() const;
	virtual CSWeaponID GetCSWeaponID() const;
	virtual bool	IsSilenced( void ) const { return false; }	// return true if this weapon has a silencer equipped
	virtual bool	HasSilencer() const;			  			   	

	virtual bool	Holster( CBaseCombatWeapon *pSwitchingTo );
	// All predicted weapons need to implement and return true
	virtual bool	IsPredicted() const;

	// Pistols reset m_iShotsFired to 0 when the attack button is released.
	bool			IsPistol() const;

	CCSPlayer* GetPlayerOwner() const;			

	// return true if this weapon is an instance of the given weapon type (ie: "IsA" WEAPON_GLOCK)
	bool IsA( CSWeaponID id ) const						{ return GetWeaponID() == id; }

	// return true if this weapon is a kinf of the given weapon type (ie: "IsKindOf" WEAPONTYPE_RIFLE )
	bool IsKindOf( CSWeaponType type ) const			{ return GetCSWpnData()->m_WeaponType == type; }

	virtual void SetWeaponModelIndex( const char *pName );
	virtual void OnPickedUp( CBaseCombatCharacter *pNewOwner );

	virtual void	OnJump( float a1 );
	virtual void	OnLand( float a1 );

	virtual bool	HasZoom();

public:
	#if defined( CLIENT_DLL )

		virtual void	ProcessMuzzleFlashEvent();
		virtual bool	OnFireEvent( C_BaseViewModel *pViewModel, const Vector& origin, const QAngle& angles, int event, const char *options );
		virtual bool	ShouldPredict();
		virtual void	DrawCrosshair();
		virtual void	OnDataChanged( DataUpdateType_t type );

		virtual int		GetMuzzleAttachment( void );
		virtual bool	HideViewModelWhenZoomed( void ) { return true; }

		float			m_flCrosshairDistance;
		int				m_iAmmoLastCheck;
		int				m_iAlpha;
		int				m_iScopeTextureID;
		int				m_iCrosshairTextureID; // for white additive texture

		virtual int GetMuzzleFlashStyle( void );

	#else

		virtual bool	Reload();
		virtual void	Spawn();
		virtual bool	KeyValue( const char *szKeyName, const char *szValue );

		virtual bool PhysicsSplash( const Vector &centerPoint, const Vector &normal, float rawSpeed, float scaledSpeed );

	#endif

	bool IsUseable();
	virtual bool	CanDeploy( void );
	virtual void	UpdateShieldState( void );
	virtual bool	SendWeaponAnim( int iActivity );
	virtual void	SendViewModelAnim( int nSequence );
	virtual void	SecondaryAttack( void );
	virtual void	Precache( void );
	virtual bool	CanBeSelected( void );
	virtual Activity GetDeployActivity( void );
	virtual bool	DefaultDeploy( char *szViewModel, char *szWeaponModel, int iActivity, char *szAnimExt );
	virtual void 	DefaultTouch( CBaseEntity *pOther );	// default weapon touch
	virtual bool	DefaultPistolReload();
	
	virtual const char* GetPlayerAnimationExtension();		
	virtual const char* GetAddonModel();

	virtual void	WeaponReset();
	virtual bool	WeaponHasBurst();
	virtual bool	IsInBurstMode();
	virtual bool	WeaponHasPrefireAnim();
	virtual bool	WeaponHasBulletAltfire();
	virtual float	GetInaccuracy();
	virtual float	GetSpread();
	virtual void	UpdateAccuracyPenalty();
	virtual bool	IsReloadVisuallyComplete();

	virtual bool	Deploy();
	virtual void	Drop( const Vector &vecVelocity );
	bool PlayEmptySound();
	virtual void	ItemPostFrame();
	virtual void	ItemBusyFrame();

	virtual const char		*GetViewModel( int viewmodelindex = 0 ) const;

	virtual const char*		GetShootSound( int iIndex ) const;

	virtual void			Operator_HandleAnimEvent( animevent_t *pEvent, CBaseCombatCharacter *pOperator );

	CSWeaponMode m_weaponMode;
	float	m_fAccuracyPenalty;

	uint8_t CSBasePad00[ 0xC ];

	float	m_flRecoilIndex;

	bool m_bBurstMode;

	float m_flPostponeFireReadyTime;

	bool m_bReloadVisuallyComplete;
	bool m_bSilencerOn;
	float m_flDoneSwitchingSilencer;

	int CSBasePad01;

	int m_iOriginalTeamNumber;

	bool	m_bDelayFire;			// This variable is used to delay the time between subsequent button pressing.
	
	int CSBasePad02;
	
	void SetExtraAmmoCount( int count ) { m_iExtraPrimaryAmmo = count; }
	int GetExtraAmmoCount( void ) { return m_iExtraPrimaryAmmo; }

private:

	float	m_flDecreaseShotsFired;

	CWeaponCSBase( const CWeaponCSBase & );

	int		m_iExtraPrimaryAmmo;

	float	m_nextPrevOwnerTouchTime;
	
	typedef CHandle< CCSPlayer > CCSPlayerHandle;
	CCSPlayerHandle m_hPrevOwner;

	int m_iDefaultExtraAmmo;

	uint8_t CSPlayerPad03[ 0x1C ];

	float m_fLastShotTime;

	uint8_t CSPlayerPad04[ 0xC ];

	int m_iIronSightMode;

	int CSPlayerPad05;
};


#endif // WEAPON_CSBASE_H

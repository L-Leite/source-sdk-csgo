//========= Copyright © 1996-2005, Valve Corporation, All rights reserved. ============//
//
// Purpose: 
//
//=============================================================================//

#ifndef C_CS_PLAYER_H
#define C_CS_PLAYER_H
#ifdef _WIN32
#pragma once
#endif

#include "ihasattributes.h"
#include "cs_playeranimstate.h"
#include "c_baseplayer.h"
#include "cs_shareddefs.h"
#include "baseparticleentity.h"
#include "beamdraw.h"
#include "GameEventListener.h"

enum CSWeaponID;

class C_PhysicsProp;
class C_BaseWeaponWorldModel;
class C_CHostage;
class C_HostageCarriableProp;


class CAddonModel
{
public:
	CHandle<C_BaseAnimating> m_hEnt;	// The model for the addon.
	int m_iAddon;						// One of the ADDON_ bits telling which model this is.
	int m_iAttachmentPoint;				// Which attachment point on the player model this guy is on.
};


class C_CSPlayer : public C_BasePlayer, public CGameEventListener, public ICSPlayerAnimStateHelpers, public IHasAttributes
{
public:
	DECLARE_CLASS( C_CSPlayer, C_BasePlayer );
	DECLARE_CLIENTCLASS();
	DECLARE_PREDICTABLE();
	DECLARE_INTERPOLATION();

	C_CSPlayer();
	virtual ~C_CSPlayer();

	virtual void Spawn( void );

	virtual bool Simulate();

	bool HasDefuser() const;

	void GiveDefuser();
	void RemoveDefuser();

	bool HasNightVision() const;

	static C_CSPlayer* GetLocalCSPlayer();
	CSPlayerState State_Get() const;

	virtual float GetMinFOV() const;

	// Get how much $$$ this guy has.
	int GetAccount() const;

	// Returns one of the CS_CLASS_ enums.
	int PlayerClass() const;

	bool IsInBuyZone();
	bool CanShowTeamMenu() const;	// Returns true if we're allowed to show the team menu right now.

									// Get the amount of armor the player has.
	int ArmorValue() const;
	bool HasHelmet() const;

	virtual const QAngle& EyeAngles();
	virtual const QAngle& GetRenderAngles();
	virtual void CalcObserverView( Vector& eyeOrigin, QAngle& eyeAngles, float& fov );

	virtual void			GetRenderBounds( Vector& theMins, Vector& theMaxs );
	virtual void			GetShadowRenderBounds( Vector &mins, Vector &maxs, ShadowType_t shadowType );
	virtual bool			GetShadowCastDirection( Vector *pDirection, ShadowType_t shadowType ) const;

	virtual void VPhysicsUpdate( IPhysicsObject *pPhysics );

	// Get the ID target entity index. The ID target is the player that is behind our crosshairs, used to
	// display the player's name.
	int GetIDTarget() const;

	virtual void OnSetDormant( bool bDormant );
	virtual void NotifyShouldTransmit( ShouldTransmitState_t state );
	virtual void ClientThink();

	virtual void OnDataChanged( DataUpdateType_t type );
	virtual void PostDataUpdate( DataUpdateType_t updateType );
	virtual bool Interpolate( float currentTime );
	virtual void UpdateStepSound( surfacedata_t *psurface, const Vector &vecOrigin, const Vector &vecVelocity );
	virtual surfacedata_t * GetFootstepSurface( const Vector &origin, const char *surfaceName );
	virtual void ValidateModelIndex( void );

	virtual int	GetMaxHealth() const;

	bool		Weapon_CanSwitchTo( C_BaseCombatWeapon *pWeapon );

	virtual void UpdateClientSideAnimation();
	virtual void ProcessMuzzleFlashEvent();

	virtual const Vector& GetRenderOrigin( void );

	bool CreateMove( float flInputSampleTime, CUserCmd *pCmd );

	CUtlVector< C_BaseParticleEntity* > m_SmokeGrenades;

	virtual bool ShouldDraw( void );
	virtual void BuildTransformations( CStudioHdr *pStudioHdr, Vector *pos, Quaternion q[], const matrix3x4_t& cameraTransform, int boneMask, CBoneBitList &boneComputed );

	virtual C_BaseAnimating * BecomeRagdollOnClient();
	virtual IRagdoll* GetRepresentativeRagdoll() const;

	void ImpactTrace( trace_t *pTrace, int iDamageType, char *pCustomImpactName );

	// Have this player play the sounds from his view model's reload animation.
	void PlayReloadEffect();

	virtual void FireEvent( const Vector& origin, const QAngle& angles, int event, const char *options );

	bool		 HasC4( void );

	virtual bool CreateLightEffects( void ) {}	//no dimlight effects

												// Sometimes the server wants to update the client's cycle to get the two to run in sync (for proper hit detection)
	virtual void SetServerIntendedCycle( float intended );
	virtual float GetServerIntendedCycle( void );

	virtual bool ShouldReceiveProjectedTextures( int flags )
	{
		return (this != C_BasePlayer::GetLocalPlayer());
	}

	// Called by shared code.
public:
	virtual void UpdateOnRemove( void );

	virtual unsigned int PhysicsSolidMaskForEntity( void ) const;

	virtual bool ShouldRegenerateOriginFromCellBits() const;

	virtual void SetModelPointer( const model_t *pModel );

	virtual bool ShouldInterpolate();

	virtual void AccumulateLayers( IBoneSetup &boneSetup, Vector pos[], Quaternion q[], float currentTime );

	virtual void* GetLayerSequenceCycleRate( C_AnimationLayer* animationLayer, int );

	virtual float GetPlayerMaxSpeed();

	virtual void CalcView( Vector &eyeOrigin, QAngle &eyeAngles, float &zNear, float &zFar, float &fov );

	virtual int GetObserverMode() const;
	virtual CBaseEntity* GetObserverTarget() const;
	virtual void SetObserverTarget( EHANDLE hObserverTarget );

	virtual void TeamChange( int iNewTeam );

	virtual void ThirdPersonSwitch( bool bThirdperson );

	virtual int GetLastKillerIndex();

	virtual float GetFOV( void ) const;

	virtual const QAngle& GetAimPunchAngle();

	virtual const char* GetVOIPParticleEffectName();
	virtual CNewParticleEffect* GetVOIPParticleEffect();

	virtual float GetDeathCamInterpolationTime();
	virtual void CalcDeathCamView( Vector& eyeOrigin, QAngle& eyeAngles, float& fov );
	virtual void CalcFreezeCamView( Vector& eyeOrigin, QAngle& eyeAngles, float& fov );

	virtual int GetObserverInterpState() const;
	virtual bool IsInObserverInterpolation() const;
	virtual bool IsHoldingTaunt() const;
	virtual bool IsHoldingLookAtWeapon() const;

	// CGameEventListener override.
	virtual void FireGameEvent( IGameEvent *event );

	// ICSPlayerAnimState overrides.
	virtual CWeaponCSBase* CSAnim_GetActiveWeapon();
	virtual bool CSAnim_CanMove();

	// IHasAttributes overrides.
	virtual CAttributeManager*	GetAttributeManager();
	virtual CAttributeContainer*	GetAttributeContainer();
	virtual CBaseEntity*	GetAttributeOwner();
	virtual CAttributeList*	GetAttributeList();
	virtual void	ReapplyProvision() = 0;

	void DoAnimationEvent( PlayerAnimEvent_t event, int nData = 0 );


	// Implemented in shared code.
public:

	void GetBulletTypeParameters(
		int iBulletType,
		float &fPenetrationPower,
		float &flPenetrationDistance );

	void FireBullet(
		Vector vecSrc,
		const QAngle &shootAngles,
		float vecSpread,
		float flDistance,
		int iPenetration,
		int iBulletType,
		int iDamage,
		float flRangeModifier,
		CBaseEntity *pevAttacker,
		bool bDoEffects,
		float x,
		float y );

	void KickBack(
		float up_base,
		float lateral_base,
		float up_modifier,
		float lateral_modifier,
		float up_max,
		float lateral_max,
		int direction_change );

	// Returns true if the player is allowed to move.
	bool CanMove() const;

	bool HasC4() const;	// Is this player carrying a C4 bomb?
	bool IsVIP() const;	// Is this player the VIP?

	virtual void SetAnimation( PLAYER_ANIM playerAnim );

public:
	// C_CSPlayer vtable functions

	virtual void PlayClientJumpSound();
	virtual bool IsTaunting() const;
	virtual bool IsThirdPersonTaunt() const;
	virtual bool IsLookingAtWeapon() const;
	virtual bool GetTauntYaw() const;
	virtual const char* GetRadioHeadParticleEffectName() const;
	virtual void UpdateRadioHeadIcon( bool bUpdate );
	virtual bool ShouldShowRadioHeadIcon() const;
	virtual CNewParticleEffect* GetRadioHeadParticleEffect();
	virtual float GetParticleHeadLabelOffset();
	virtual bool HasSpeechVOIPParticleIconActive();

public:

	void UpdateIDTarget( void );
	void RemoveAddonModels( void );
	void UpdateMinModels( void );

	void SetActivity( Activity eActivity );
	Activity GetActivity( void ) const;

	IPlayerAnimState *GetPlayerAnimState() { return m_PlayerAnimState; }

public:	
	class CCSSoundEvent
	{
	public:
		string_t m_SoundName;
		float m_flEventTime;	// Play the event when gpGlobals->curtime goes past this.
	};

	bool IsInHostageRescueZone( void );

	CWeaponCSBase* GetActiveCSWeapon() const { return reinterpret_cast<CWeaponCSBase*>(GetActiveWeapon()); }
	CWeaponCSBase* GetCSWeapon( CSWeaponID id ) const;

	virtual ShadowType_t		ShadowCastType();

#ifdef CS_SHIELD_ENABLED
	bool HasShield( void ) { return m_bHasShield; }
	bool IsShieldDrawn( void ) { return m_bShieldDrawn; }
	void SetShieldDrawnState( bool bState ) { m_bShieldDrawn = bState; }
#else
	bool HasShield( void ) { return false; }
	bool IsShieldDrawn( void ) { return false; }
	void SetShieldDrawnState( bool bState ) {}
#endif

	void SurpressLadderChecks( const Vector& pos, const Vector& normal );
	bool CanGrabLadder( const Vector& pos, const Vector& normal );

	// Having the RecvProxy in the player allows us to keep the var private
	static void RecvProxy_CycleLatch( const CRecvProxyData *pData, void *pStruct, void *pOut );

	void UpdateRadar();
	void UpdateSoundEvents();

	void CreateAddonModel( int i );
	void UpdateAddonModels();

	void PushawayThink();

	void ReleaseFlashlight( void );

public:	   
	uint8_t					CSPlayerPad00[ 0x20 ]; //0x3804

	C_BaseWeaponWorldModel*	m_pBaseWeaponWorldModel; //0x3848 

	uint8_t					CSPlayerPad01[ 0x24 ]; //0x384C

	ITexture*				m_pTexture; //0x3870 

	uint8_t					CSPlayerPad02[ 0xC ]; //0x3874

	IPlayerAnimState*		m_PlayerAnimState; //0x3880 

	uint8_t					CSPlayerPad03[ 0x8 ]; //0x3884

	bool					m_bIsScoped; //0x388C 
	bool					m_bIsWalking; //0x388D 
	bool					m_bResumeZoom; //0x388E 

	CSPlayerState			m_iPlayerState; //0x3890 

	bool					m_bIsDefusing; //0x3894 
	bool					m_bIsGrabbingHostage; //0x3895 
	bool					m_bIsRescuing; //0x3896 

	float m_fImmuneToGunGameDamageTime; //0x3898 

	uint8_t					CSPlayerPad04[ 0x4 ]; //0x389C

	bool					m_bGunGameImmunity; //0x38A0 
	bool					m_bHasMovedSinceSpawn; //0x38A1 
	bool					m_bMadeFinalGunGameProgressiveKill; //0x38A2 

	int						m_iGunGameProgressiveWeaponIndex; //0x38A4 
	int						m_iNumGunGameTRKillPoints; //0x38A8 
	int						m_iNumGunGameKillsWithCurrentWeapon; //0x38AC 
	int						m_iNumRoundKills; //0x38B0 
	int						m_iNumRoundKillsHeadshots; //0x38B4 

	float					m_fMolotovUseTime; //0x38B8 
	float					m_fMolotovDamageTime; //0x38BC 

	bool					m_bInBombZone; //0x38C0 
	bool					m_bInBuyZone; //0x38C1 
	bool					m_bInNoDefuseArea; //0x38C2 

	int						m_iThrowGrenadeCounter; //0x38C4 

	bool					m_bWaitForNoAttack; //0x38C8 
	bool					m_bIsRespawningForDMBonus; //0x38C9 

	float					m_flGuardianTooFarDistFrac; //0x38CC 
	float					m_flDetectedByEnemySensorTime; //0x38D0 

	uint8_t					CSPlayerPad05[ 0x4 ]; //0x38D4

	bool					m_bKilledByTaser; //0x38D8 

	int						m_iMoveState; // 2 means moving (?)

	bool					m_isCurrentGunGameLeader; //0x38E1 
	bool					m_isCurrentGunGameTeamLeader; //0x38E2 

	char					m_szArmsModel[ 256 ]; //0x38E3 


	float					m_flLowerBodyYawTarget; //0x39E4 

	bool					m_bStrafing; //0x39E8 

	uint8_t					CSPlayerPad06[ 0x68AB ]; // There's more bullshit in here, did Valve forget about dynamic vectors?

	int						m_iAddonBits; //0xA294 
	int						m_iPrimaryAddon; //0xA298 
	int						m_iSecondaryAddon; //0xA29C 

	float					m_iProgressBarDuration; //0xA2A0 
	float					m_flProgressBarStartTime; //0xA2A4 

	uint8_t					CSPlayerPadA2A8[ 0x8 ]; //0xA2A8
	int						m_iShotsFired; //0xA2B0 
	uint8_t					CSPlayerPadA2B4[ 0x5 ]; //0xA2B4

	bool					m_bNightVisionOn; //0xA2B9 
	bool					m_bHasNightVision; //0xA2BA 

	uint8_t					CSPlayerPad08[ 0x4 ]; //0xA2BB

	float					m_flGroundAccelLinearFracLastTime; //0xA2C0 

	int						m_iStartAccount; //0xA2C4 

	int						m_totalHitsOnServer; //0xA2C8 

	uint8_t					CSPlayerPad09[ 0x4 ]; //0xA2CC

	CHandle< CRagdoll >		m_hRagdoll; //0xA2D0 
	CHandle< C_CHostage	>	m_hCarriedHostage; //0xA2D4 
	CHandle< C_HostageCarriableProp > m_hCarriedHostageProp; //0xA2D8 

	uint8_t					CSPlayerPad10[ 0x18 ]; //0xA2DC

	float m_flFlashMaxAlpha; //0xA2F4 
	float m_flFlashDuration; //0xA2F8 

	uint8_t					CSPlayerPad11[ 0x40 ]; //0xA2FC

	int						m_iMatchStats_Kills[ 30 ]; //0xA33C 
	int						m_iMatchStats_Damage[ 30 ]; //0xA3B4 
	int						m_iMatchStats_EquipmentValue[ 30  ]; //0xA42C 
	int						m_iMatchStats_MoneySaved[ 30 ]; //0xA4A4 
	int						m_iMatchStats_KillReward[ 30 ]; //0xA51C 
	int						m_iMatchStats_LiveTime[ 30 ]; //0xA594 
	int						m_iMatchStats_Deaths[ 30 ]; //0xA60C 
	int						m_iMatchStats_Assists[ 30 ]; //0xA684 
	int						m_iMatchStats_HeadShotKills[ 30 ]; //0xA6FC 
	int						m_iMatchStats_Objective[ 30 ]; //0xA774 
	int						m_iMatchStats_CashEarned[ 30 ]; //0xA7EC 
	int						m_iMatchStats_UtilityDamage[ 30 ];
	int						m_iMatchStats_EnemiesFlashed[ 30 ];

	uint8_t					CSPlayerPad12[ 0x5C ]; //0xA864

	uint16_t				m_unCurrentEquipmentValue; //0xA8C8 
	uint16_t				m_unRoundStartEquipmentValue; //0xA8CA 
	uint16_t				m_unFreezetimeEndEquipmentValue; //0xA8CC 

	int						m_rank[ 6 ]; //0xA8D0 

	uint16_t				m_unMusicID; //0xA8E8 

	int						m_iAccount; //0xA8EC 

	bool					m_bHasHelmet; //0xA8F0 
	bool					m_bHasHeavyArmor; //0xA8F1 

	int						m_iClass; //0xA8F4 

	int						m_iArmor; //0xA8F8 

	QAngle					m_angEyeAngles; //0xA8FC 

	bool					m_bHasDefuser; //0xA908 
	bool					m_bInHostageRescueZone; //0xA909 

	uint8_t					CSPlayerPad13[ 0x10 ]; //0xA90A

	bool					m_bHud_MiniScoreHidden; //0xA91A 
	bool					m_bHud_RadarHidden; //0xA91B 

	int						m_nLastKillerIndex; //0xA91C 
	int						m_nLastConcurrentKilled; //0xA920 
	int						m_nDeathCamMusic; //0xA924 

	CInterpolatedVar< QAngle > m_iv_angEyeAngles; //0xA928 

	uint8_t					CSPlayerPad14[ 0xD0 ]; //0xA954

	float					m_cycleLatch; //0xAA24 

	uint8_t					CSPlayerPad15[ 0x190 ]; //0xAA28

	bool					m_bIsLookingAtWeapon; //0xABB8 
	bool					m_bIsHoldingLookAtWeapon; //0xABB9 

	uint8_t					CSPlayerPad16[ 0x97 ]; //0xABBA

	bool					m_bIsAssassinationTarget; //0xAC51 
	bool					m_bIsControllingBot; //0xAC52 
	bool					m_bCanControlObservedBot; //0xAC53 
	int						m_iControlledBotEntIndex; //0xAC54 

	uint8_t					CSPlayerPad17[ 0x4 ]; //0xAC58

	bool					m_bHasControlledBotThisRound; //0xAC5C

	uint8_t					CSPlayerPad18[ 0x22B ]; //0xAC5D

private:
	C_CSPlayer( const C_CSPlayer & );
};

inline CSPlayerState C_CSPlayer::State_Get() const
{
	return m_iPlayerState;
}

#endif // C_CS_PLAYER_H
//========= Copyright © 1996-2005, Valve Corporation, All rights reserved. ============//
//
// Purpose: 
//
//=============================================================================//

#ifndef WEAPON_CSBASE_GUN_H
#define WEAPON_CSBASE_GUN_H
#ifdef _WIN32
#pragma once
#endif


#include "weapon_csbase.h"


// This is the base class for pistols and rifles.
#if defined( CLIENT_DLL )

	#define CWeaponCSBaseGun C_WeaponCSBaseGun

#else
#endif


class CWeaponCSBaseGun : public CWeaponCSBase
{
public:
	
	DECLARE_CLASS( CWeaponCSBaseGun, CWeaponCSBase );
	DECLARE_NETWORKCLASS(); 
	DECLARE_PREDICTABLE();
	
	CWeaponCSBaseGun();

	virtual void PrimaryAttack();
	virtual void SecondaryAttack();
	virtual void Spawn();
	virtual void Drop( const Vector &vecVelocity );
	virtual bool SendWeaponAnim( int iActivity );
	virtual void Precache();
	virtual bool Deploy();
	virtual bool Holster( CBaseCombatWeapon *pSwitchingTo );
	virtual bool Reload();
	virtual void WeaponIdle();	
	virtual const char* GetWorldModel() const;

	virtual bool IsFullAuto() const;	  

	virtual const CCSWeaponInfo* GetCSWpnData() const; // Get CS-specific weapon data.
	virtual int		GetCSZoomLevel() const;
	inline void SetCSZoomLevel( int zoomLevel ) { m_zoomLevel = zoomLevel; }

	virtual bool	HasZoom();			   
	virtual bool	DefaultPistolReload();		
	virtual bool	IsInBurstMode();
	virtual bool	WeaponHasBulletAltfire();

	// Derived classes call this to fire a bullet.
	bool CSBaseGunFire( float flSpread, float flCycleTime, bool bPrimaryMode );

	// Usually plays the shot sound. Guns with silencers can play different sounds.
	virtual void DoFireEffects();

	virtual bool IsInBurstMode() const;	// Using 'const' so it matches the vftable
	virtual bool DoesUnzoomAfterShot();

	virtual void ItemPostFrame();
	virtual void ItemBusyFrame();

	virtual bool IsZoomed();

protected: 
	int m_zoomLevel;
	int m_iBurstShotsRemaining;
	float m_fNextBurstShotTime;

	uint8_t CSBaseGunPad00[ 0xC ];

private:

	CWeaponCSBaseGun( const CWeaponCSBaseGun & );
};


#endif // WEAPON_CSBASE_GUN_H

//========= Copyright Valve Corporation, All rights reserved. ============//
//
// Purpose: 
//
//===========================================================================//

#ifndef ECON_ENTITY_H
#define ECON_ENTITY_H

#ifdef _WIN32
#pragma once
#endif

#if defined( CLIENT_DLL )
#define CEconEntity C_EconEntity
#endif

#include "ihasattributes.h"
#include "econ_item_view.h"
#include "attribute_manager.h"
#include "UtlSortVector.h"

struct wearableanimplayback_t
{
	int iStub;
};

class CEconEntity : public CBaseFlex, public IHasAttributes
{
	DECLARE_CLASS( CEconEntity, CBaseAnimating );
	DECLARE_NETWORKCLASS();
	DECLARE_DATADESC();

#ifdef CLIENT_DLL
	DECLARE_PREDICTABLE();
#endif

public:
	CEconEntity();
	~CEconEntity();

#ifdef CLIENT_DLL
	virtual void OnPreDataChanged( DataUpdateType_t );
	virtual void OnDataChanged( DataUpdateType_t );
	virtual void FireEvent( const Vector& origin, const QAngle& angles, int event, const char *options );
	virtual bool OnFireEvent( C_BaseViewModel *pViewModel, const Vector& origin, const QAngle& angles, int event, const char *options );
#endif

	virtual int ShouldTransmit( const CCheckTransmitInfo *pInfo );

	virtual int OnNewModel();	 

	virtual void GiveTo( CBaseEntity *pEntity );

	virtual CBaseEntity* CalculateVisibleClassFor( CBaseCombatCharacter* pCombatCharacter );

	virtual CAttributeManager *GetAttributeManager( void ) { return &m_AttributeManager; }
	virtual CAttributeContainer *GetAttributeContainer( void ) { return &m_AttributeManager; }
	virtual CBaseEntity *GetAttributeOwner( void ) { return NULL; }
	virtual CAttributeList*	GetAttributeList() { return nullptr; }
	virtual void SetOriginalOwnerXuid( uint low, uint high );
	virtual uint64 GetOriginalOwnerXuid();
	virtual int GetFallbackPaintKit();
	virtual int GetFallbackSeed();
	virtual float GetFallbackWear();
	virtual int GetFallbackStatTrak();
	virtual void UpdateBodygroups( CBaseCombatCharacter* pCharacter, int iValue );
	virtual int TranslateViewmodelHandActivity( int iActivity ) { return iActivity; }

	virtual void UpdateOnRemove( void );

private:					 
	CNetworkVarEmbedded( CAttributeContainer, m_AttributeManager );	  

	uint m_OriginalOwnerXuidLow;
	uint m_OriginalOwnerXuidHigh;
	int m_nFallbackPaintKit;
	int m_nFallbackSeed;
	float m_flFallbackWear;
	int m_nFallbackStatTrak;

	uint8_t Pad04[ 0x8 ];
};

#endif
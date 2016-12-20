//=============================================================================
//
// Purpose: Applies attributes.
//
//=============================================================================

#ifndef ATTRIBUTE_MANAGER_H
#define ATTRIBUTE_MANAGER_H

#ifdef _WIN32
#pragma once
#endif

#include "gamestringpool.h"

// Client specific.
#ifdef CLIENT_DLL
EXTERN_RECV_TABLE( DT_AttributeManager );
EXTERN_RECV_TABLE( DT_AttributeContainer );
// Server specific.
#else
EXTERN_SEND_TABLE( DT_AttributeManager );
EXTERN_SEND_TABLE( DT_AttributeContainer );
#endif

class CAttributeManager
{
public:
	DECLARE_EMBEDDED_NETWORKVAR();
	DECLARE_CLASS_NOBASE( CAttributeManager );

	CAttributeManager();

#ifdef CLIENT_DLL
	virtual void		OnPreDataChanged( DataUpdateType_t updateType );
	virtual void		OnDataChanged( DataUpdateType_t updatetype );
#endif
	void				AddProvider( CBaseEntity *pEntity );
	void				RemoveProvider( CBaseEntity *pEntity );
	void				ProviteTo( CBaseEntity *pEntity );
	void				StopProvidingTo( CBaseEntity *pEntity );
	virtual void		InitializeAttributes( CBaseEntity *pEntity );
	virtual float		ApplyAttributeFloat( float flValue, const CBaseEntity *pEntity, string_t strAttributeClass );
	virtual string_t	ApplyAttributeString( string_t strValue, const CBaseEntity *pEntity, string_t strAttributeClass );

protected:
	uint8_t EconPad00[ 0x14 ];

	CNetworkVar( int, m_iReapplyProvisionParity );
	CNetworkHandle( CBaseEntity, m_hOuter );
	int EconPad01;

	int m_ProviderType;	 

	uint8_t EconPad02[ 0x18 ];
};

class CAttributeContainer : public CAttributeManager
{
public:
	DECLARE_EMBEDDED_NETWORKVAR();
	DECLARE_CLASS( CAttributeContainer, CAttributeManager );
#ifdef CLIENT_DLL
	DECLARE_PREDICTABLE();
#endif

	CAttributeContainer();

	float		ApplyAttributeFloat( float flValue, const CBaseEntity *pEntity, string_t strAttributeClass );
	string_t	ApplyAttributeString( string_t strValue, const CBaseEntity *pEntity, string_t strAttributeClass );

	CEconItemView* GetItem() { return &m_Item; }

private:
	CEconItemView m_Item;
};

#endif // ATTRIBUTE_MANAGER_H
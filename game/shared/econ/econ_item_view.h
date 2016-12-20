#ifndef TF_ECON_ITEM_VIEW_H
#define TF_ECON_ITEM_VIEW_H

#ifdef _WIN32
#pragma once
#endif

class CEconItemHandle
{
public:
	// CEconItem *m_pItem; TODO: not implemented yet, get a GC going

	uint64 m_SteamID; // The owner of the item?
	int m_ItemID;
};


#ifdef CLIENT_DLL
EXTERN_RECV_TABLE( DT_ScriptCreatedItem )
#else
EXTERN_SEND_TABLE( DT_ScriptCreatedItem )
#endif

class CEconItemView
{
public:
	DECLARE_CLASS_NOBASE( CEconItemView );
	DECLARE_EMBEDDED_NETWORKVAR();
	CEconItemView();
	CEconItemView( int iItemID );

	void Init( int iItemID );

	const char* GetWorldDisplayModel( int iClass = 0 ) const;
	const char* GetPlayerDisplayModel( int iClass = 0 ) const;
	const char* GetEntityName( void );
	bool IsCosmetic( void );
	int GetAnimationSlot( void );
	Activity GetActivityOverride( int iTeamNumber, Activity actOriginalActivity );
	const char* GetActivityOverride( int iTeamNumber, const char *name );
	const char* GetSoundOverride( int iIndex, int iTeamNum = TEAM_UNASSIGNED ) const;
	bool HasCapability( const char* name );
	bool HasTag( const char* name );

	void SetItemDefIndex( int iItemID );
	int GetItemDefIndex( void ) const;

private:
	uint8_t Pad00[ 0x48 ];

	CNetworkVar( int, m_iItemDefinitionIndex );

	CNetworkVar( int, m_iEntityQuality ); // maybe an enum?
	CNetworkVar( int, m_iEntityLevel );

	uint8_t Pad01[ 0x8 ];

	CNetworkVar( int, m_iItemIDHigh );
	CNetworkVar( int, m_iItemIDLow );
	CNetworkVar( uint64, m_iAccountID );

	int Pad02;

	bool m_bInitialized;

	uint8_t Pad03[ 0x17F ];
};

#endif // TF_ECON_ITEM_VIEW_H
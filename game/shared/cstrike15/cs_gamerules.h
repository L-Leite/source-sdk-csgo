//========= Copyright © 1996-2005, Valve Corporation, All rights reserved. ============//
//
// Purpose: The TF Game rules object
//
// $Workfile:     $
// $Date:         $
// $NoKeywords: $
//=============================================================================//

#ifndef CS_GAMERULES_H
#define CS_GAMERULES_H

#ifdef _WIN32
#pragma once
#endif


#include "teamplay_gamerules.h"
#include "convar.h"
#include "cs_shareddefs.h"
#include "gamevars_shared.h"

#ifdef CLIENT_DLL
	#include "c_cs_player.h"
#else
	#include "cs_player.h"
#endif

// used for EndRoundMessage() logged messages
#define Target_Bombed							1
#define VIP_Escaped								2
#define VIP_Assassinated						3
#define Terrorists_Escaped						4
#define CTs_PreventEscape						5
#define Escaping_Terrorists_Neutralized			6
#define Bomb_Defused							7
#define CTs_Win									8
#define Terrorists_Win							9
#define Round_Draw								10
#define All_Hostages_Rescued					11
#define Target_Saved							12
#define Hostages_Not_Rescued					13
#define Terrorists_Not_Escaped					14
#define VIP_Not_Escaped							15
#define Game_Commencing							16

#define	WINNER_NONE		0
#define WINNER_DRAW		1
#define WINNER_TER		TEAM_TERRORIST
#define WINNER_CT		TEAM_CT	

extern ConVar* mp_startmoney;
extern ConVar* mp_tkpunish;
extern ConVar* mp_c4timer;
extern ConVar* mp_buytime;
extern ConVar* mp_buy_anywhere;
extern ConVar* mp_freezetime;
extern ConVar* mp_playerid;

#ifndef CLIENT_DLL
	extern ConVar* mp_autoteambalance;
#endif // !CLIENT_DLL


#ifdef CLIENT_DLL
	#define CCSGameRules C_CSGameRules
	#define CCSGameRulesProxy C_CSGameRulesProxy
#endif


class CCSGameRulesProxy : public CGameRulesProxy
{
public:
	DECLARE_CLASS( CCSGameRulesProxy, CGameRulesProxy );
	DECLARE_NETWORKCLASS();
};


class CCSGameRules : public CTeamplayRules
{
public:
	DECLARE_CLASS( CCSGameRules, CTeamplayRules );

	// Stuff that is shared between client and server.
	bool IsFreezePeriod();


	virtual bool ShouldCollide( int collisionGroup0, int collisionGroup1 );

	float GetMapRemainingTime();	// time till end of map, -1 if timelimit is disabled
	float GetMapElapsedTime();	// How much time has elapsed since the map started.
	float GetRoundRemainingTime();	// time till end of round
	float GetRoundStartTime();		// When this round started.
	float GetRoundElapsedTime();	// How much time has elapsed since the round started.
	float GetBuyTimeLength() const;
	int GetRoundLength() const { return m_iRoundTime; }
	int   SelectDefaultTeam( bool ignoreBots = false );
	int   GetHumanTeam();			// TEAM_UNASSIGNED if no restrictions

	bool IsVIPMap() const;
	bool IsBombDefuseMap() const;
	bool IsHostageRescueMap() const;
	bool IsIntermission() const;
	bool IsLogoMap() const;
	bool IsSpawnPointValid( CBaseEntity *pSpot, CBasePlayer *pPlayer );

	bool IsBuyTimeElapsed();

	// Get the view vectors for this mod.
	virtual const CViewVectors* GetViewVectors() const;

	virtual void RegisterScriptFunctions( void ) { };

	virtual void ClientCommandKeyValues( edict_t *pEntity, KeyValues *pKeyValues ) {}

	virtual bool IsConnectedUserInfoChangeAllowed( CBasePlayer* player );

	void UploadGameStats( void );
	int  GetStartMoney( void );

public:

	float GetExplosionDamageAdjustment(Vector & vecSrc, Vector & vecEnd, CBaseEntity *pEntityToIgnore); // returns multiplier between 0.0 and 1.0 that is the percentage of any damage done from vecSrc to vecEnd that actually makes it.
	float GetAmountOfEntityVisible(Vector & src, CBaseEntity *player); // returns a value from 0 to 1 that is the percentage of player visible from src.

	uint8 Pad00[ 0x8 ];

	CNetworkVar( bool, m_bFreezePeriod );	 // TRUE at beginning of round, set to FALSE when the period expires
	CNetworkVar( float, m_fWarmupPeriodEnd );
	CNetworkVar( float, m_fWarmupPeriodStart );
	CNetworkVar( bool, m_bTerroristTimeOutActive );
	CNetworkVar( bool, m_bCTTimeOutActive );
	CNetworkVar( float, m_flTerroristTimeOutRemaining );
	CNetworkVar( float, m_flCTTimeOutRemaining );
	CNetworkVar( int, m_nTerroristTimeOuts );
	CNetworkVar( int, m_nCTTimeOuts );
	CNetworkVar( bool, m_bMatchWaitingForResume );
	CNetworkVar( int, m_iRoundTime );		 // (From mp_roundtime) - How many seconds long this round is.
	CNetworkVar( float, m_fMatchStartTime );
	CNetworkVar( float, m_fRoundStartTime ); // time round has started	
	float m_flRestartRoundTime;	// the global time when the round is supposed to end, if this is not 0
	CNetworkVar( bool, m_bGameRestart );
	CNetworkVar( float, m_flGameStartTime );
	CNetworkVar( int, m_timeUntilNextPhaseStarts ); // Might be float
	CNetworkVar( int, m_gamePhase ); 
	CNetworkVar( int, m_totalRoundsPlayed );
	CNetworkVar( int, m_nOvertimePlaying );	   
	CNetworkVar( int, m_iHostagesRemaining );
	CNetworkVar( bool, m_bAnyHostageReached );
	CNetworkVar( bool, m_bMapHasBombTarget );
	CNetworkVar( bool, m_bMapHasRescueZone );
	bool m_bMapHasBuyZone;
	CNetworkVar( bool, m_bIsQueuedMatchmaking );
	CNetworkVar( bool, m_bIsValveDS );
	CNetworkVar( bool, m_bLogoMap );		 // If there's an info_player_logo entity, then it's a logo map.
	CNetworkVar( int, m_iNumGunGameProgressiveWeaponsCT );
	CNetworkVar( int, m_iNumGunGameProgressiveWeaponsT );
	CNetworkVar( int, m_iSpectatorSlotCount );
	CNetworkArray( int, m_GGProgressiveWeaponOrderCT, 60 );
	CNetworkArray( int, m_GGProgressiveWeaponOrderT, 60 );
	CNetworkArray( int, m_GGProgressiveWeaponKillUpgradeOrderCT, 60 );
	CNetworkArray( int, m_GGProgressiveWeaponKillUpgradeOrderT, 60 );
	CNetworkVar( int, m_MatchDevice );
	CNetworkVar( bool, m_bHasMatchStarted );

	CNetworkVar( float, m_flDMBonusStartTime );
	CNetworkVar( float, m_flDMBonusTimeLength );
	CNetworkVar( uint16,m_unDMBonusWeaponLoadoutSlot );
	CNetworkVar( bool, m_bDMBonusActive );
	CNetworkVar( int, m_nNextMapInMapgroup );
	
	CNetworkString( m_szTournamentEventName, 260 );
	CNetworkString( m_szTournamentEventStage, 260 );
	CNetworkString( m_szMatchStatTxt, 260 );
	CNetworkString( m_szTournamentPredictionsTxt, 260 );

	CNetworkVar( int, m_nTournamentPredictionsPct );
	CNetworkVar( float, m_flCMMItemDropRevealStartTime );
	CNetworkVar( float, m_flCMMItemDropRevealEndTime );

	uint8 Pad01[ 0x1 ];

	CNetworkVar( bool, m_bIsQuestEligible );
	CNetworkVar( int, m_nGuardianModeWaveNumber );
	CNetworkVar( int, m_nGuardianModeSpecialKillsRemaining );
	CNetworkVar( int, m_nGuardianModeSpecialWeaponNeeded );

	uint8 Pad02[ 0x8 ];

	CNetworkVar( int, m_numGlobalGiftsGiven );
	CNetworkVar( int, m_numGlobalGifters );
	CNetworkVar( int, m_numGlobalGiftsPeriodSeconds );
	CNetworkArray( int, m_arrFeaturedGiftersAccounts, 4 ); 
	CNetworkArray( int, m_arrFeaturedGiftersGifts, 4 );
	CNetworkArray( int, m_arrTournamentActiveCasterAccounts, 4 );

	CNetworkVar( int, m_nHalloweenMaskListSeed );

	bool m_bBombDropped;
	bool m_bBombPlanted;
	int m_iRoundWinStatus;		// 1 == CT's won last round, 2 == Terrorists did, 3 == Draw, no winner
	CNetworkVar( int, m_eRoundWinReason );
	bool m_bTCantBuy;
	bool m_bCTCantBuy;

	CNetworkVar( float, m_flGuardianBuyUntilTime );
	CNetworkArray( int, m_iMatchStats_RoundResults, 30 ); 
	CNetworkArray( int, m_iMatchStats_PlayersAlive_CT, 30 );
	CNetworkArray( int, m_iMatchStats_PlayersAlive_T, 30 );

	uint8 Pad03[ 0x100 ];

	CNetworkVar( int, m_iActiveAssassinationTargetMissionID );

	int Pad04;

	CNetworkArray( int, m_nEndMatchMapGroupVoteOptions, 10 );

	uint8 Pad05[ 0x1C ];
	
public:											
	int GetNumHostagesRemaining( void ) { return m_iHostagesRemaining; }

	virtual CBaseCombatWeapon *GetNextBestWeapon( CBaseCombatCharacter *pPlayer, CBaseCombatWeapon *pCurrentWeapon );

	virtual const unsigned char *GetEncryptionKey( void ) { return (unsigned char *)"d7NSuLq2"; } // both the client and server need this key

#ifdef CLIENT_DLL

	DECLARE_CLIENTCLASS_NOBASE(); // This makes datatables able to access our private vars.
	CCSGameRules();

#else

	DECLARE_SERVERCLASS_NOBASE(); // This makes datatables able to access our private vars.
	
	CCSGameRules();
	virtual ~CCSGameRules();

	void DumpTimers( void ) const;	// debugging to help track down a stuck server (rare?)

	CBaseEntity *GetPlayerSpawnSpot( CBasePlayer *pPlayer );

	static void EndRound();

	virtual void PlayerKilled( CBasePlayer *pVictim, const CTakeDamageInfo &info );
	virtual void Think();

	virtual void RefreshSkillData( bool forceUpdate );

	// Called at the end of GameFrame (i.e. after all game logic has run this frame)
	virtual void EndGameFrame( void );		 

	virtual bool ClientCommand( CBaseEntity *pEdict, const CCommand &args );
	virtual void PlayerSpawn( CBasePlayer *pPlayer );
			void ShowSpawnPoints();

	virtual bool PlayTextureSounds( void ) { return true; }
	// Let the game rules specify if fall death should fade screen to black
	virtual bool  FlPlayerFallDeathDoesScreenFade( CBasePlayer *pl ) { return FALSE; }
	virtual bool FPlayerCanTakeDamage( CBasePlayer *pPlayer, CBaseEntity *pAttacker );

	virtual void  RadiusDamage( const CTakeDamageInfo &info, const Vector &vecSrcIn, float flRadius, int iClassIgnore, CBaseEntity *pEntityIgnore );
	void RadiusDamage( const CTakeDamageInfo &info, const Vector &vecSrcIn, float flRadius, int iClassIgnore, bool bIgnoreWorld );
	
	// Death notices
	virtual void		DeathNotice( CBasePlayer *pVictim, const CTakeDamageInfo &info );

	virtual void			InitDefaultAIRelationships( void );

	virtual int PlayerRelationship( CBaseEntity *pPlayer, CBaseEntity *pTarget );
	virtual bool PlayerCanHearChat( CBasePlayer *pListener, CBasePlayer *pSpeaker );

	virtual const char *GetGameDescription( void ) { return "Counter-Strike: Source"; }  // this is the game name that gets seen in the server browser
	virtual const char *AIClassText(int classType);

	virtual bool IsTeamChangeSilent( CBasePlayer* pPlayer, int, bool, bool );

	virtual bool FShouldSwitchWeapon( CBasePlayer *pPlayer, CBaseCombatWeapon *pWeapon );

	// Called after the map has finished loading.
	virtual void LevelInitPostEntity();

	virtual float FlPlayerFallDamage( CBasePlayer *pPlayer );

	virtual void ClientDisconnected( edict_t *pClient );


	virtual bool ForceSplitScreenPlayersOnToSameTeam();

	virtual int GetMaxHumanPlayers() const;

	virtual bool CanHLTVSpectateBots( int a1, int a2 );

	// Recreate all the map entities from the map data (preserving their indices),
	// then remove everything else except the players.
	// Also get rid of all world decals.
	void CleanUpMap();

	void CheckFreezePeriodExpired();
	void CheckRoundTimeExpired();

	// check if the scenario has been won/lost
	// return true if the scenario is over, false if the scenario is still in progress
	bool CheckWinConditions( void );	

	void TerminateRound( float tmDelay, int reason );
	void RestartRound( void );
	void BalanceTeams( void );
	void MoveHumansToHumanTeam( void );
	bool TeamFull( int team_id );
	bool TeamStacked( int newTeam_id, int curTeam_id  );
	bool FPlayerCanRespawn( CBasePlayer *pPlayer );
	void UpdateTeamScores();
	void CheckMapConditions();
	void MarkLivingPlayersOnTeamAsNotReceivingMoneyNextRound(int team);

	// Check various conditions to end the map.
	bool CheckGameOver();
	bool CheckMaxRounds();
	bool CheckWinLimit();
	bool CheckFragLimit();

	void CheckLevelInitialized();
	void CheckRestartRound();
	

	// Checks if it still needs players to start a round, or if it has enough players to start rounds.
	// Starts a round and returns true if there are enough players.
	bool NeededPlayersCheck( bool &bNeededPlayers );

	// Setup counts for m_iNumTerrorist, m_iNumCT, m_iNumSpawnableTerrorist, m_iNumSpawnableCT, etc.
	void InitializePlayerCounts(
		int &NumAliveTerrorist,
		int &NumAliveCT,
		int &NumDeadTerrorist,
		int &NumDeadCT
		);

	// Check to see if the round is over for the various game types. Terminates the round
	// and returns true if the round should end.
	bool PrisonRoundEndCheck();
	bool BombRoundEndCheck( bool bNeededPlayers );
	bool HostageRescueRoundEndCheck( bool bNeededPlayers );

	// Check to see if the teams exterminated each other. Ends the round and returns true if so.
	bool TeamExterminationCheck(
		int NumAliveTerrorist,
		int NumAliveCT,
		int NumDeadTerrorist,
		int NumDeadCT,
		bool bNeededPlayers
		);

	void ReadMultiplayCvars();
	void SwapAllPlayers();

	void BroadcastSound( const char *sound, int team = -1 );


	// VIP FUNCTIONS
	bool VIPRoundEndCheck( bool bNeededPlayers );
	void PickNextVIP();


	// BOMB MAP FUNCTIONS
	void GiveC4();
	bool IsThereABomber();
	bool IsThereABomb();

	// HOSTAGE MAP FUNCTIONS
	void HostageTouched();

	
	// Sets up g_pPlayerResource.
	virtual void CreateStandardEntities();
	virtual const char *GetChatPrefix( bool bTeamOnly, CBasePlayer *pPlayer );
	virtual const char *GetChatLocation( bool bTeamOnly, CBasePlayer *pPlayer );
	virtual const char *GetChatFormat( bool bTeamOnly, CBasePlayer *pPlayer );
	virtual void ClientSettingsChanged( CBasePlayer *pPlayer );
	
	virtual bool CanClientCustomizeOwnIdentity();
	virtual int IPointsForKill( CBasePlayer* pAttacker, CBasePlayer *pKilled );

	virtual bool IgnorePlayerKillCommand();

	bool IsCareer( void ) const		{ return false; }		// returns true if this is a CZ "career" game

	virtual bool FAllowNPCs( void );

	virtual void HandleScrambleTeams();

protected:
	virtual void GoToIntermission( void );

public:

	bool IsFriendlyFireOn();

	virtual float GetRoundRestartTime();	   
	virtual bool IsGameRestarting();						  
	virtual int GetNextRespawnWave( int, CBasePlayer* pPlayer );	
	virtual void SpawningLatePlayer( CCSPlayer* pPlayer );		
	virtual void CheckAndAwardAssists( CCSPlayer*, CCSPlayer* ); 
	virtual bool HasPassedMinRespawnTime( CBasePlayer* pPlayer );
	virtual void GoToIntermission( bool );

	virtual void	SetAllowWeaponSwitch( bool allow );
	virtual bool	GetAllowWeaponSwitch( void );

	// VARIABLES FOR ALL TYPES OF MAPS
	bool m_bLevelInitialized;	
	int m_iTotalRoundsPlayed;
	int m_iUnBalancedRounds;	// keeps track of the # of consecutive rounds that have gone by where one team outnumbers the other team by more than 2
	
	uint8 Pad06[ 0x8 ];

	// GAME TIMES
	int m_iFreezeTime;		// (From mp_freezetime) - How many seconds long the intro round (when players are frozen) is.

	int m_iNumTerrorist;		// The number of terrorists on the team (this is generated at the end of a round)
	int m_iNumCT;				// The number of CTs on the team (this is generated at the end of a round)
	int m_iNumSpawnableTerrorist;
	int m_iNumSpawnableCT;

	uint8 Pad07[ 0x14 ];

	bool m_bFirstConnected;
	bool m_bCompleteReset;		// Set to TRUE to have the scores reset next time round restarts

	uint8 Pad08[ 0x6B ];

	bool m_bIgnoreWinConditions;

	uint8 Pad09[ 0x6A ];

	float m_tmNextPeriodicThink;

	uint8 Pad10[ 0xC ];

	// HOSTAGE RESCUE VARIABLES
	int		m_iHostagesRescued;
	int		m_iHostagesTouched;
	float	m_flNextHostageAnnouncement;

	uint8 Pad11[ 0x44 ];

	// PRISON ESCAPE VARIABLES
	int		m_iHaveEscaped;
	bool	m_bMapHasEscapeZone;
	int		m_iNumEscapers;
	int		m_iNumEscapeRounds;		// keeps track of the # of consecutive rounds of escape played.. Teams will be swapped after 8 rounds

	// BOMB MAP VARIABLES
	bool	m_bTargetBombed;	// whether or not the bomb has been bombed
	bool	m_bBombDefused;	// whether or not the bomb has been defused
	bool	m_bMapHasBombZone;

	uint8 Pad12[ 0x9 ];

	int m_iAccountCT;
	uint8 Pad13[ 0x2 ];
	short m_iNumCTWins;

	int m_iAccountTerrorist;	
	uint8 Pad14[ 0x2 ];
	short m_iNumTerroristWins;

	uint8 Pad15[ 0x11C ];

public:			  


#endif
};

//-----------------------------------------------------------------------------
// Gets us at the team fortress game rules
//-----------------------------------------------------------------------------

CCSGameRules* CSGameRules();

#define IGNORE_SPECTATORS true
int UTIL_HumansInGame( bool ignoreSpectators = false );



//-----------------------------------------------------------------------------
// Purpose: Useful utility functions
//-----------------------------------------------------------------------------
#ifdef CLIENT_DLL

#else
	
	class CTFTeam;
	CTFTeam *GetOpposingTeam( CTeam *pTeam );
	bool EntityPlacementTest( CBaseEntity *pMainEnt, const Vector &vOrigin, Vector &outPos, bool bDropToGround );

#endif

#endif // TF_GAMERULES_H

//========= Copyright © 1996-2005, Valve Corporation, All rights reserved. ============//
//
// Purpose: Headers and defines for Autobuy and Rebuy 
//
//=============================================================================//

/**
 * Weapon classes as used by the AutoBuy
 * Has to be different that the previous ones because these are bitmasked values as a weapon can be from
 * more than one class.  This also includes all the classes of equipment that a player can buy.
 */

#define MAX_BUYABLE_GRENADES 4 // Probably, didn't try to bypass the limit

enum AutoBuyClassType
{
	AUTOBUYCLASS_PRIMARY = 1,
	AUTOBUYCLASS_SECONDARY = 2,
	AUTOBUYCLASS_AMMO = 4,
	AUTOBUYCLASS_ARMOR = 8,
	AUTOBUYCLASS_DEFUSER = 16,
	AUTOBUYCLASS_PISTOL = 32,
	AUTOBUYCLASS_SMG = 64,
	AUTOBUYCLASS_RIFLE = 128,
	AUTOBUYCLASS_SNIPERRIFLE = 256,
	AUTOBUYCLASS_SHOTGUN = 512,
	AUTOBUYCLASS_MACHINEGUN = 1024,
	AUTOBUYCLASS_GRENADE = 2048,
	AUTOBUYCLASS_NIGHTVISION = 4096,
	AUTOBUYCLASS_SHIELD = 8192,
};

struct AutoBuyInfoStruct
{
	AutoBuyClassType m_class;
	char *m_command;
	char *m_classname;
};

struct RebuyStruct
{
	int m_primary; // These use a different ID from weapon IDs, gotta reverse them
	int m_secondary;
	int m_tertiary;	// Zeus goes here
	int m_Grenades[ MAX_BUYABLE_GRENADES ];

	uint8_t Pad[ 0x10 ];

	int m_armor;					// 0, 1, or 2 (0 = none, 1 = vest, 2 = vest + helmet)

	bool m_defuser;					// do we want a defuser
	bool m_nightVision;				// do we want night vision
	bool m_bBought;
};

extern AutoBuyInfoStruct g_autoBuyInfo[];

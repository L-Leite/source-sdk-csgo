#include "stdafx.h"

void CBaseCombatWeapon::GiveAmmo( int a1, int iCount, bool bSuppressSound, int a2 )
{
	using fn_t = void( __thiscall* )(CBaseCombatWeapon*, int, int, bool, int);
	((fn_t) Addresses::GiveAmmo)(this, a1, iCount, bSuppressSound, a2);
}
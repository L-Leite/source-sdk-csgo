#include "stdafx.h"

//-----------------------------------------------------------------------------
// Purpose: 
// Output : CBaseCombatWeapon
//-----------------------------------------------------------------------------
CBaseCombatWeapon *CBaseCombatCharacter::GetActiveWeapon() const
{
	return m_hActiveWeapon;
}
#include "stdafx.h"

bool IsAmmoType( int iAmmoType, const char *pAmmoName )
{
	return GetAmmoDef()->Index( pAmmoName ) == iAmmoType;
}

CCSPlayer* CWeaponCSBase::GetPlayerOwner() const
{
	return static_cast< CCSPlayer* >(GetOwner());
}
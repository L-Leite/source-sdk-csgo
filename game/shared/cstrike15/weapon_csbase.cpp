#include "stdafx.h"

CCSPlayer* CWeaponCSBase::GetPlayerOwner() const
{
	return static_cast< CCSPlayer* >(GetOwner());
}
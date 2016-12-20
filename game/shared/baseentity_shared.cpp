#include "stdafx.h"

#define CHANGE_FLAGS(flags,newFlags) (flags = (newFlags))

void CBaseEntity::AddFlag( int flags )
{
	CHANGE_FLAGS( m_fFlags, m_fFlags | flags );
}

void CBaseEntity::RemoveFlag( int flagsToRemove )
{
	CHANGE_FLAGS( m_fFlags, m_fFlags & ~flagsToRemove );
}

void CBaseEntity::ClearFlags( void )
{
	CHANGE_FLAGS( m_fFlags, 0 );
}

void CBaseEntity::ToggleFlag( int flagToToggle )
{
	CHANGE_FLAGS( m_fFlags, m_fFlags ^ flagToToggle );
}
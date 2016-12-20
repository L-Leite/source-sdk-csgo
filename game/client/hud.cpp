#include "stdafx.h"
#include "hudelement.h"

CUtlVector< CHudElement * > &CHud::GetHudList()
{
	return m_HudList;
}

const CUtlVector< CHudElement * > &CHud::GetHudList() const
{
	return m_HudList;
}

CUtlVector< vgui::Panel * > &CHud::GetHudPanelList()
{
	return m_HudPanelList;
}

const CUtlVector< vgui::Panel * > &CHud::GetHudPanelList() const
{
	return m_HudPanelList;
}

CHudElement *CHud::FindElement( const char *pName )
{
	for ( int i = 0; i < GetHudList().Count(); i++ )
	{
		if ( stricmp( GetHudList()[ i ]->GetName(), pName ) == 0 )
			return GetHudList()[i];
	}

	DevWarning(1, "[%d] Could not find Hud Element: %s\n", m_nSplitScreenSlot, pName );
	Assert(0);
	return NULL;
}
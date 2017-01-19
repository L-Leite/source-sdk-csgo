//========= Copyright � 1996-2005, Valve Corporation, All rights reserved. ============//
//
// Purpose:		Namespace for functions dealing with Debug Overlays
//
// $Workfile:     $
// $Date:         $
// $NoKeywords: $
//=============================================================================//

#include "stdafx.h"
#include "ndebugoverlay.h"

//-----------------------------------------------------------------------------
// Purpose: Add an overlay line with padding on the start and end
//-----------------------------------------------------------------------------
void DebugDrawLine( const Vector& vecAbsStart, const Vector& vecAbsEnd, int r, int g, int b, bool test, float duration )
{
	NDebugOverlay::Line( vecAbsStart + Vector( 0,0,0.1), vecAbsEnd + Vector( 0,0,0.1), r,g,b, test, duration );
}

#include "stdafx.h"

//-----------------------------------------------------------------------------
// Purpose: 
// Input  :
//-----------------------------------------------------------------------------
void CBaseAnimating::LockStudioHdr()
{
	using fn_t = void(__thiscall*)(CBaseAnimating*);
	((fn_t)Addresses::LockStudioHdr)( this );
}

//=========================================================
//=========================================================
void CBaseAnimating::GetBonePosition( int iBone, Vector &origin, QAngle &angles )
{
	CStudioHdr *pStudioHdr = GetModelPtr();
	if ( !pStudioHdr )
	{
		Assert( !"CBaseAnimating::GetBonePosition: model missing" );
		return;
	}

	if ( iBone < 0 || iBone >= pStudioHdr->numbones() )
	{
		Assert( !"CBaseAnimating::GetBonePosition: invalid bone index" );
		return;
	}

	matrix3x4_t bonetoworld;
	GetBoneTransform( iBone, bonetoworld );

	MatrixAngles( bonetoworld, angles, origin );
}

float CBaseAnimating::GetModelScale() const
{
	return m_flModelScale;
}

static Vector	hullcolor[ 8 ] =
{
	Vector( 1.0, 1.0, 1.0 ),
	Vector( 1.0, 0.5, 0.5 ),
	Vector( 0.5, 1.0, 0.5 ),
	Vector( 1.0, 1.0, 0.5 ),
	Vector( 0.5, 0.5, 1.0 ),
	Vector( 1.0, 0.5, 1.0 ),
	Vector( 0.5, 1.0, 1.0 ),
	Vector( 1.0, 1.0, 1.0 )
};


//-----------------------------------------------------------------------------
// Purpose: Send the current hitboxes for this model to the client ( to compare with
//  r_drawentities 3 client side boxes ).
// WARNING:  This uses a ton of bandwidth, only use on a listen server
//-----------------------------------------------------------------------------
void CBaseAnimating::DrawServerHitboxes( float duration /*= 0.0f*/, bool monocolor /*= false*/  )
{
	MDLCACHE_CRITICAL_SECTION();

	CStudioHdr *pStudioHdr = GetModelPtr();
	if ( !pStudioHdr )
		return;

	mstudiohitboxset_t *set =pStudioHdr->pHitboxSet( m_nHitboxSet );
	if ( !set )
		return;

	Vector position;
	QAngle angles;

	int r = 0;
	int g = 0;
	int b = 255;

	for ( int i = 0; i < set->numhitboxes; i++ )
	{
		mstudiobbox_t *pbox = set->pHitbox( i );

		GetBonePosition( pbox->bone, position, angles );

		if ( !monocolor )
		{
			int j = (pbox->group % 8);
			
			r = ( int ) ( 255.0f * hullcolor[j][0] );
			g = ( int ) ( 255.0f * hullcolor[j][1] );
			b = ( int ) ( 255.0f * hullcolor[j][2] );
		}

		NDebugOverlay::BoxAngles( position, pbox->bbmin*GetModelScale(), pbox->bbmax*GetModelScale(), angles, r, g, b, 0 ,duration );
	}
}

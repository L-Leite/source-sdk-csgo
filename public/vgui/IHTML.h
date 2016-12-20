//========= Copyright © 1996-2005, Valve Corporation, All rights reserved. ============//
//
// Purpose: 
//
// $NoKeywords: $
//=============================================================================//

#ifndef IHTML_H
#define IHTML_H

#ifdef _WIN32
#pragma once
#endif

#include <vgui/VGUI.h>
#include <vgui/MouseCode.h>
#include <vgui/KeyCode.h>
#include <vgui/Cursor.h>
#include <vgui/IImage.h>

namespace vgui
{

//-----------------------------------------------------------------------------
// Purpose: basic interface for a HTML window
//-----------------------------------------------------------------------------
class IHTML
{
public:
	// open a new page
	virtual void OpenURL(const char *)=0;

	// stops the existing page from loading
	virtual bool StopLoading()=0;

	// refreshes the current page
	virtual bool Refresh()=0;

	// display the control
	virtual bool Show(bool shown)=0;

	// return the currently opened page
	virtual char *GetOpenedPage()=0;

	// called when the browser needs to be resized
	virtual void OnSize(int x,int y, int w,int h)=0;

	// returns the width and height (in pixels) of the HTML page
	virtual void GetHTMLSize(int &wide,int &tall)=0;

	// clear the text in an existing control
	virtual void Clear()=0;

	// add text to the browser control (as a HTML formated string)
	virtual void AddText(const char *text)=0;


	enum MOUSE_STATE { UP,DOWN,MOVE };

	virtual void OnMouse(MouseCode code,MOUSE_STATE s,int x,int y)=0;
	virtual void OnChar(wchar_t unichar)=0;
	virtual void OnKeyDown(KeyCode code)=0;

	virtual vgui::IImage *GetBitmap()=0;

	virtual void SetVisible( bool state ) = 0;
};

	//-----------------------------------------------------------------------------
	// Purpose: basic callback interface for a HTML window
	//-----------------------------------------------------------------------------
	class IHTMLEvents
	{
	public:
		// unused functions we keep around so the vtable layout is binary compatible
		virtual bool Obsolete_OnStartURL(const char *url, const char *target, bool first)=0;
		virtual void Obsolete_OnFinishURL(const char *url)=0;
		virtual void Obsolete_OnProgressURL(long current, long maximum)=0;
		virtual void Obsolete_OnSetStatusText(const char *text) =0;
		virtual void Obsolete_OnUpdate() =0;
		virtual void Obsolete_OnLink()=0;
		virtual void Obsolete_OffLink()=0;
	
		// call backs for events
		// when the top level browser is changing the page they are looking at (not sub iframes or the like loading)
		virtual void OnURLChanged( const char *url, const char *pchPostData, bool bIsRedirect ) = 0;
		// the control has finished loading a request, could be a sub request in the page
		virtual void OnFinishRequest( const char *url, const char *pageTitle ) = 0;

		// the lower html control wants to load a url, do we allow it?
		virtual bool OnStartRequestInternal( const char *url, const char *target, const char *pchPostData, bool bIsRedirect ) = 0;

		// show a popup menu for this html control
		virtual void ShowPopup( int x, int y, int wide, int tall ) = 0;
		// hide any popup menu you are showing
		virtual void HidePopup() = 0;
		// show an external html window at this position and side
		virtual bool OnPopupHTMLWindow( const char *pchURL, int x, int y, int wide, int tall ) = 0;
		// the browser is telling us the title it would like us to show
		virtual void SetHTMLTitle( const char *pchTitle ) = 0;
		// the browser is loading a sub url for a page, usually an image or css
		virtual void OnLoadingResource( const char *pchURL ) = 0;
		// the browser is telling us the user is hovering a url or the like 
		virtual void OnSetStatusText(const char *text) =0;
		// the browser wants the cursor changed please
		virtual void OnSetCursor( vgui::CursorCode cursor ) = 0;
		// the browser wants to ask the user to select a local file and tell it about it
		virtual void OnFileLoadDialog( const char *pchTitle, const char *pchInitialFile ) = 0;
		// show and hide tooltip text
		virtual void OnShowToolTip( const char *pchText ) = 0;
		virtual void OnUpdateToolTip( const char *pchText ) = 0;
		virtual void OnHideToolTip() = 0;


		// IE only code
		virtual bool BOnCreateNewWindow( void **ppDispatch ) = 0;
		virtual void OnLink()=0;
		virtual void OffLink()=0;
		virtual void OnCloseWindow() = 0;
		virtual void OnUpdate() =0;
		virtual void OnProgressRequest(long current, long maximum)=0;

		// new Chrome calls
		virtual bool OnOpenNewTab( const char *pchURL, bool bForeground ) = 0;
	};

}

#endif // IHTML_H

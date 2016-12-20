#ifndef INVENTORYUPDATELISTENER_H
#define INVENTORYUPDATELISTENER_H

#ifdef _WIN32
#pragma once
#endif

namespace GCSDK
{
	
abstract_class ISharedObjectListener
{
public:
	virtual void InventoryUpdateListener00( int a2, int a3, int a4, int a5, int a6, int a7 ) = 0;
	virtual void InventoryUpdateListener01( int a2, int a3, int a4, int a5, int a6, int a7 ) = 0;
	virtual void InventoryUpdateListener02( int a2, int a3, int a4, int a5, int a6, int a7 ) = 0;
	virtual void InventoryUpdateListener03( int a2, int a3, int a4, int a5, int a6 ) = 0;
	virtual void InventoryUpdateListener04( int a2, int a3, int a4, int a5, int a6 ) = 0;
	virtual void InventoryUpdateListener05( int a2 ) = 0;
};

}

abstract_class IInventoryUpdateListener : public GCSDK::ISharedObjectListener
{
public:
};

#endif // INVENTORYUPDATELISTENER_H

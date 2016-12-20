#ifndef ECONITEMINTERFACE_H
#define ECONITEMINTERFACE_H
#ifdef _WIN32
#pragma once
#endif

enum EStickerAttributeType;
class IEconItemDefinition;
class IEconItemAttributeIterator;

abstract_class IEconItemInterface
{ 
public:
	virtual int				GetCustomPaintKitIndex() = 0;
	virtual int				GetCustomPaintKitSeed() = 0;
	virtual double			GetCustomPaintKitWear( float ) = 0;
	virtual float			GetStickerAttributeBySlotIndexFloat( int, EStickerAttributeType, float ) = 0;
	virtual int				GetStickerAttributeBySlotIndexInt( int, EStickerAttributeType, unsigned int )= 0;
	virtual bool			IsTradable() = 0;
	virtual bool			IsMarketable() = 0;
	virtual bool			IsCommodity() = 0;
	virtual bool			IsUsableInCrafting() = 0;
	virtual bool			IsHiddenFromDropList() = 0;
	virtual int				GetExpirationDate() = 0;
	virtual IEconItemDefinition* GetItemDefinition() = 0;
	virtual int				GetAccountID() = 0;
	virtual int				GetItemID() = 0;
	virtual int				GetQuality() = 0;
	virtual int				GetRarity() = 0;
	virtual int				GetFlags() = 0;
	virtual int				GetOrigin() = 0;
	virtual int				GetQuantity() = 0;
	virtual int				GetItemLevel() = 0;
	virtual bool			GetInUse() = 0;
	virtual const char*		GetCustomName() = 0;
	virtual const char*		GetCustomDesc() = 0;
	virtual int				GetItemSetIndex() = 0;
	virtual void*			IterateAttributes( IEconItemAttributeIterator* pIterator ) = 0;
};

#endif // ECONITEMINTERFACE_H
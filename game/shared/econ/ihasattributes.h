#ifndef IHASATTRIBUTES_H
#define IHASATTRIBUTES_H
#ifdef _WIN32
#pragma once
#endif

class CAttributeManager;
class CAttributeContainer;
class CAttributeList;

//-----------------------------------------------------------------------------
// Purpose: Allows to determine if entity has attribute related members
//-----------------------------------------------------------------------------
abstract_class IHasAttributes
{ 
public:
	virtual CAttributeManager*	GetAttributeManager() = 0;
	virtual CAttributeContainer*	GetAttributeContainer() = 0;
	virtual CBaseEntity*	GetAttributeOwner() = 0;
	virtual CAttributeList*	GetAttributeList() = 0;
	virtual void	ReapplyProvision() = 0;
};

#endif // IHASATTRIBUTES_H
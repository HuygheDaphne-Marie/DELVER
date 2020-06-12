#include "pch.h"
#include "MenuComponent.h"
#include "Menu.h"

MenuComponent::MenuComponent()
	: m_pMenu{ nullptr }
{
}
MenuComponent::~MenuComponent()
{
}

const Menu* MenuComponent::GetMenu() const
{
	return m_pMenu;
}
void MenuComponent::SetMenu(Menu* menu)
{
	if (m_pMenu != nullptr && m_pMenu != menu)
	{
		m_pMenu->RemoveComponent(this);
	}
	m_pMenu = menu;
}
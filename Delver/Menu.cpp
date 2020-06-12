#include "pch.h"
#include "Menu.h"
#include "MenuComponent.h"

Menu::Menu()
	: m_MenuState{}
	, m_StateComponents{}
{
}
Menu::~Menu()
{
	for (std::unordered_map<State, std::vector<MenuComponent*>>::iterator itr{ m_StateComponents.begin() }; itr != m_StateComponents.end(); itr++)
	{
		for (MenuComponent* component : itr->second)
		{
			delete component;
		}
		itr->second.clear();
	}
	m_StateComponents.clear();
}

void Menu::Update(float elapsedSec)
{
	std::vector<MenuComponent*>* currentComponents{ GetComponentsForCurrentMenuState() };
	if (currentComponents == nullptr)
	{
		return;
	}

	for (MenuComponent* component : *currentComponents)
	{
		component->Update(elapsedSec);
	}
}
void Menu::Draw() const
{
	const std::vector<MenuComponent*>* currentComponents{ GetComponentsForCurrentMenuState() };
	if (currentComponents == nullptr)
	{
		return;
	}

	for (MenuComponent* component : *currentComponents)
	{
		component->Draw();
	}
}

void Menu::OnClick(const Point2f& clickPos)
{
	std::vector<MenuComponent*>* currentComponents{ GetComponentsForCurrentMenuState() };
	if (currentComponents == nullptr)
	{
		return;
	}

	for (MenuComponent* component : *currentComponents)
	{
		component->OnClick(clickPos);
	}
}
void Menu::OnPress(const SDL_KeyboardEvent& e)
{
	std::vector<MenuComponent*>* currentComponents{ GetComponentsForCurrentMenuState() };
	if (currentComponents == nullptr)
	{
		return;
	}

	for (MenuComponent* component : *currentComponents)
	{
		component->OnPress(e);
	}
}

void Menu::AddComponent(State menuState, MenuComponent* component)
{
	std::unordered_map<State, std::vector<MenuComponent*>>::const_iterator itr{ m_StateComponents.find(menuState) };
	if (itr != m_StateComponents.end())
	{
		std::vector<MenuComponent*>* components{ GetComponentsForMenuState(menuState) };
		components->push_back(component);
	}
	else
	{
		std::vector<MenuComponent*> newComponentsList{ component };
		m_StateComponents.insert({ menuState, newComponentsList });
	}
	component->SetMenu(this);
}
void Menu::RemoveComponent(MenuComponent* component) // Doesn't delete the component, that's up to you!
{
	for (std::unordered_map<State, std::vector<MenuComponent*>>::iterator itr{ m_StateComponents.begin() }; itr != m_StateComponents.end(); itr++)
	{
		RemoveComponent(itr->first, component);
	}
}
void Menu::RemoveComponent(State menuState, MenuComponent* component) // Doesn't delete the component, that's up to you!
{
	std::unordered_map<State, std::vector<MenuComponent*>>::const_iterator itr{ m_StateComponents.find(menuState) };
	if (itr != m_StateComponents.end())
	{
		std::vector<MenuComponent*>* components{ GetComponentsForMenuState(menuState) };
		for (int i{0}; i < components->size(); i++)
		{
			if (components->at(i) == component)
			{
				components->at(i) = nullptr;
				components->at(i) = components->at(components->size() - 1);
				i--;
				components->pop_back();
			}
		}
	}
}

std::vector<MenuComponent*>* Menu::GetComponentsForCurrentMenuState()
{
	return GetComponentsForMenuState(m_MenuState);
}
std::vector<MenuComponent*>* Menu::GetComponentsForMenuState(State menuState)
{
	std::unordered_map<State, std::vector<MenuComponent*>>::iterator itr{ m_StateComponents.find(menuState) };
	if (itr != m_StateComponents.end())
	{
		return &(itr->second);
	}
	else
	{
		return nullptr;
	}
}

const std::vector<MenuComponent*>* Menu::GetComponentsForCurrentMenuState() const
{
	return GetComponentsForMenuState(m_MenuState);
}
const std::vector<MenuComponent*>* Menu::GetComponentsForMenuState(State menuState) const
{
	std::unordered_map<State, std::vector<MenuComponent*>>::const_iterator itr{ m_StateComponents.find(menuState) };
	if (itr != m_StateComponents.end())
	{
		return &(itr->second);
	}
	else
	{
		return nullptr;
	}
}
#pragma once
#include <unordered_map>
#include <vector>

class MenuComponent;

class Menu
{
public:
	enum class State
	{
		playing,
		paused
	};

	Menu();
	Menu(const Menu& other) = delete;
	Menu& operator=(const Menu& other) = delete;
	Menu(Menu&& other) = delete;
	Menu& operator=(Menu&& other) = delete;
	~Menu();

	void Update(float elapsedSec);
	void Draw() const;

	void OnClick(const Point2f& clickPos);
	void OnPress(const SDL_KeyboardEvent& e);

	void AddComponent(State menuState, MenuComponent* component);
	void RemoveComponent(State menuState, MenuComponent* component);

	const std::vector<MenuComponent*>* GetComponentsForCurrentMenuState() const;
	const std::vector<MenuComponent*>* GetComponentsForMenuState(State menuState) const;

	State m_MenuState;

private:
	std::unordered_map<State, std::vector<MenuComponent*>> m_StateComponents;

	std::vector<MenuComponent*>* GetComponentsForCurrentMenuState();
	std::vector<MenuComponent*>* GetComponentsForMenuState(State menuState);
};


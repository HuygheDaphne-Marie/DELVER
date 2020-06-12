#pragma once

class Menu;

class MenuComponent
{
public:
	MenuComponent();
	MenuComponent(const MenuComponent& other) = delete;
	MenuComponent& operator=(const MenuComponent& other) = delete;
	MenuComponent(MenuComponent&& other) = delete;
	MenuComponent& operator=(MenuComponent&& other) = delete;
	virtual ~MenuComponent();

	virtual void Update(float elapsedsec) = 0;
	virtual void Draw() const = 0;

	virtual void OnClick(const Point2f& clickPos) = 0;
	virtual void OnPress(const SDL_KeyboardEvent& e) = 0;

	const Menu* GetMenu() const;
	void SetMenu(Menu* menu);

private:
	Menu* m_pMenu;
};


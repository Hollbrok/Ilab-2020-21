#pragma once

#include "Libraries.h"

using namespace std;
using namespace sf;


class text {
private:

	string shribe;


	Font font;

public:

	Text txt;

	text(string shribeName)
	{
		font.loadFromFile("CyrilicOld.TTF");

		txt.setFont(font);
		txt.setCharacterSize(20);

		//начальный цвет
		txt.setFillColor(Color(0, 0, 0));

		txt.setString(shribeName);

		shribe = shribeName;
	}

	//текст будет следить за спрайтом
	virtual void sleditForSprite(Sprite& s, float x, float y) 
	{
		txt.setPosition(s.getPosition().x + x, s.getPosition().y + y);
	}

	//дать число тексту
	void getChislo(float n) {

		ostringstream chislo;

		chislo << n;

		txt.setString(shribe + chislo.str());
	}


	//ф-я для текста
	void setString(string name)
	{
		txt.setString(name);
	}

	virtual void setPosition(float x, float y) 
	{
		txt.setPosition(x, y);
	}

	void setFillTextColor(float R, float G1, float B) 
	{
		txt.setFillColor(Color(R, G1, B));
	}

	//поменять размер шрифта
	void setCharacterSize(float a) 
	{
		txt.setCharacterSize(a);
	}

	//нарисовать в окне
	virtual void draw(RenderWindow& window) 
	{
		window.draw(txt);
	};
};

//кнопка
class Button :public text {
private:

	float w, h; //ширина и высота кнопки
	bool press;   // 

	sf::Color color;//= Vector3i(0, 0, 0);

	sf::Color st_color;


public:

	RectangleShape button;//сам крвадрат

	Button(float W, float H, string shribeName) :text(shribeName) 
	{

		w = W * 1.5;
		h = H * 1.5;

		press = false;

		button.setSize(Vector2f(w, h));

		txt.setPosition(button.getPosition());

	}

	void changeTxt(const char* text)
	{
		txt.setString(text);
	}

	void SetTxtPos(int x = 0, int y = 0)
	{
		if ((x == 0) && (y == 0))
			txt.setPosition(button.getPosition() + Vector2f(w/2, h/2));
		else
			txt.setPosition(x, y);
	}

	//кнопка следит за спрайтом
	void sleditForSprite(Sprite& s, float x, float y) override 
	{
		button.setPosition(s.getPosition().x + x, s.getPosition().y + y);
		txt.setPosition(s.getPosition().x + x, s.getPosition().y + y);
	}

	//рисуеи и кнопк(квадрат) и текст
	void draw(RenderWindow& window) override {

		txt.setPosition(button.getPosition());
		// ЗДЕСЬ МОЖНО ВЫРАВНИВАТЬ

		window.draw(button);
		window.draw(txt);
	}

	//нажатие
	bool pressed(Event& event, Vector2f  pos) 
	{

		if (button.getGlobalBounds().contains(pos.x, pos.y) && event.type == Event::MouseButtonPressed && !press) {
			if (event.key.code == Mouse::Left) {
				press = true;
				return true;
			}
		};

		if (!(press)) return false;

		if (press) {

			if (!(event.type == Event::MouseButtonPressed)) {

				press = false;

			}

			return false;
		}
	};

	//наведена мышка
	bool navediaMouse(Event& event, Vector2f  pos) {


		if (button.getGlobalBounds().contains(pos.x, pos.y)) return true;

		else return false;



	}

	//поменять размеры квадрата кнопки 
	void setButtonSize(float W, float H) {

		w = W;
		h = H;

		button.setSize(Vector2f(W, H));

	}

	//Поменять на центр 
	void setOringCenter() {
		button.setOrigin(w / 2, h / 2);
	}

	//поменять позицию
	void setPosition(float x, float y)  override {

		button.setPosition(x, y);

	}

	//поменять цвет квадрата
	void setFillRacktengelColor(float R, float G, float B) {

		button.setFillColor(Color(R, G, B));
		color = Color(R, G, B);
		st_color = color;
	}

	void setFillRacktengelColor(sf::Color new_color) 
	{
		button.setFillColor(new_color);
		color = new_color;
		st_color = color;
	}

	void changeFillRacktengelColor(sf::Color new_color)
	{
		button.setFillColor(new_color);
		color = new_color;
	}

	void changeFillRacktengelColor(float R, float G, float B) {

		button.setFillColor(Color(R, G, B));
		color = Color(R, G, B);
	}

	sf::Color GetColor()
	{
		return st_color;
	}
};







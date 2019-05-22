#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <SOIL.h>

//#include <cstdlib>
#include <map>
#include <iostream>
#include <string>
#include <vector>
#include <ctime>

#include "fonts.h"

using std::map;
using std::string;
using std::vector;
using std::cout;
using std::cerr;
using std::endl;

//---------------------------------------------------------------------------------------------
//global variables and types

#define MAIN_MENU_TITLE "Sunrise"

const float BUTTON_COLOR_RGB[4] = {0.f/255, 0.f/255, 0.f/255, 63.f/255};

enum class ButtonType {
	START,
	LOAD,
	OPTIONS,
	EXIT
};

enum class LabelType {
	TITLE,
	FULLSCREEN
};

enum class Orientation {
	VERTICAL,
	HORIZONTAL
};

enum class VerticalAlign {
	TOP,
	MIDDLE,
	BOTTOM
};

enum class HorizontalAlign {
	LEFT,
	MIDDLE,
	RIGHT
};

/*class ButtonProperties { //TODO �� ����� ��������
//public:
	//string title;
private:
	string _title;
	FontName fontName;

public:
	void(*callback)();

	ButtonProperties(string, void(*)());

	string getTitle() const;
};*/

class UserInterface;

class UIItem;

class ActiveUIItem;

class UIItemsContainer;

//MenuItemContainer* menuItemContainer;

//---------------------------------------------------------------------------------------------
//class Drawer declaration

static class UIItemDrawer {
	friend class UserInterface;
	friend class UIItemsContainer;

private:
	static void drawUIItem(UIItem*);

	static void setPosition(UIItem* UIItem, int, int);

	static void updateContainerProperties(UIItemsContainer*);
};

//---------------------------------------------------------------------------------------------
//class UserInterface declaration

class UserInterface {
private:
	int _displayWidth = 0;
	int _displayHeight = 0;
	ActiveUIItem*** _controlField = nullptr;
	int _windowWidth = 0;
	int _windowHeight = 0;

	Orientation _orientation = Orientation::VERTICAL;
	HorizontalAlign _horizontalAlign = HorizontalAlign::MIDDLE;
	VerticalAlign _verticalAlign = VerticalAlign::MIDDLE;

	UIItemsContainer* _UIItemsContainer = nullptr;
	//int _windowWidth = 0;
	//int _windowHeight = 0;

	UserInterface();
	~UserInterface();
	UserInterface(const UserInterface&) = delete;
	UserInterface& operator=(const UserInterface&) = delete;

	void updateContainerProperties();
public:
	static UserInterface& Instance();	

	//��������� ������� ������� � ��������. ������� ���������� ������ � ������ ������� ����������
	void setDisplaySize(int, int);

	//��������� �������� ������� ���� ����������
	void setWindowSize(int, int);

	//��������� �������� ������� ���� ����������
	//arguments:
	//#1 - width of window
	//#2 - height of window
	void getWindowSize(int*, int*) const;

	//��������� �������� ���� �������� ���������� �� ������ ����������
	//arguments:
	//#1 - xPos of active UI item left side
	//#2 - width of active UI item
	//#3 - yPos of active UI item top side
	//#4 - height of active UI item
	//#5 - active UI item pointer
	void setActiveUIItemControlField(int, int, int, int, ActiveUIItem*);

	void triggerActiveUIItemOnClickCallbackAtPoint(int, int);

	//���������� � ��������� ���������� �����. ��������� - ������� ������ ���� �� ����������� ������ ���������� ������� �������� ��������� ����������. �� ����� ����� ��������� ��������� ����������� ����� ��������
	void clearControlField();

	//debug
	//void __drawControlField();

	void setUIItemsContainer(UIItemsContainer*);

	//void updateContainerProperties(); //�����

	void drawUserInterface() const;
};

//---------------------------------------------------------------------------------------------
//class UserInterfaceItem declaration

class UIItem {
	friend class UIItemDrawer;

private: //�� �����������
	virtual void drawUIItem() const = 0;
protected:
	int _xPos = 0, _yPos = 0;
	int _width = 0, _height = 0;
	int _paddingSize = 0;
	int _marginSize = 0; //�������� ������ �� ��� ���������� ����������

	//virtual void drawUIItem() const = 0;
	virtual void setPosition(int, int);
public:
	virtual ~UIItem() = default;

	//��������� �������� �������� ����������
	//arguments:
	//#1 - width
	//#2 - height
	//#3 - marginSize
	//virtual void getUIItemSizes(int*, int*, int*) const = 0;

	//virtual void setPosition(int, int) = 0;

	void getUIItemSizes(int*, int*, int*) const;

	//virtual void drawUIItem() const = 0; // �����
};

//---------------------------------------------------------------------------------------------
//class ActiveUserInterfaceItem declaration

class ActiveUIItem : public UIItem {
protected:
	//��������������:
	//int _xPos = 0, _yPos = 0;
	//int _width = 0, _height = 0;
	//int _paddingSize = 0;
	//int _marginSize = 0;

	void(*_onClickCallback)();
public:
	virtual void onClick() const = 0;
};

//---------------------------------------------------------------------------------------------
//class MenuItemContainer declaration

//class UIItemsContainer : private UIItem { //������ ��������������� ��������� � UIItem
class UIItemsContainer : public UIItem {
	friend class UIItemDrawer;

private:
	//��������������:
	//int _xPos = 0, _yPos = 0;
	//int _width = 0, _height = 0;
	//int _paddingSize = 0;
	//int _marginSize = 0;

	Orientation _orientation;
	VerticalAlign _verticalAlign;
	HorizontalAlign _horizontalAlign;
	//bool _scrollable = false;

	//UIItemsContainer* _parentContainer = nullptr;
	vector<UIItem*> _UIItems;

	void drawUIItem() const;
	void updateContainerProperties();

	virtual void setPosition(int, int) override;
public:
	//UIItemsContainer(UIItemsContainer*, Orientation, VerticalAlign, HorizontalAlign) noexcept;
	UIItemsContainer(Orientation, VerticalAlign, HorizontalAlign) noexcept;
	//UIItemsContainer(UIItemsContainer &UIItemsContainer);
	~UIItemsContainer();

	//void getUIItemSizes(int*, int*, int*) const; //�����������

	//void setPosition(int, int); //�����������

	//void drawUIItem() const; //�����
	//void drawUIElement();
	//void onClick() const;

	//UIItemsContainer* _parentContainer = nullptr;

	void addUIItem(UIItem* const menuItem);

	//void updateContainerProperties(); //������
};

//---------------------------------------------------------------------------------------------
//fuctions declaration

void createMainMenu();
//UIItemsContainer* createMainMenu();

//---------------------------------------------------------------------------------------------
//callbacks declaration

void callback_windowSize(GLFWwindow*, int, int);
void callback_key(GLFWwindow*, int, int, int, int);
void callback_mouseButton(GLFWwindow*, int, int, int);

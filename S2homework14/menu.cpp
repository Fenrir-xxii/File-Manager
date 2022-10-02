#include "menu.h"

size_t Menu::getFrameHeight() const
{
	return (((options.size()+1)/2) + 5);
}

Menu::Menu(const std::vector<std::string>& options)
{
	this->options = options;
}

void Menu::drawFrame(bool active)
{

	size_t height = getFrameHeight();

	for (size_t y = 0; y < height; y++)
	{
		for (size_t x = 0; x < WINDOW_WIDTH; x++)
		{
			if (x == 0 || x == WINDOW_WIDTH - 1 || y == 0 || y == height - 1) {
				SetCursorPosition(x, y);
				active ? SetColor(ConsoleColor::WHITE, ConsoleColor::BLUE) : SetColor(ConsoleColor::WHITE, ConsoleColor::GRAY);
				std::cout << ' ';
			}
		}
	}

	for (int i = 0; i < WINDOW_WIDTH; i++)
	{
		SetCursorPosition(i, 2);
		active ? SetColor(ConsoleColor::WHITE, ConsoleColor::BLUE) : SetColor(ConsoleColor::WHITE, ConsoleColor::GRAY);
		std::cout << ' ';
	}

	SetColor(WHITE, BLACK);
}

void Menu::drawFrame(int x, int y, size_t height, bool active)
{

	for (size_t coordY = y; coordY < height; coordY++)
	{
		for (size_t coordX = x; coordX < WINDOW_WIDTH + x; coordX++)
		{
			if (coordX == x || coordX == WINDOW_WIDTH + x - 1 || coordY == y || coordY == height - 1) {
				SetCursorPosition(coordX, coordY);
				active ? SetColor(ConsoleColor::WHITE, ConsoleColor::BLUE) : SetColor(ConsoleColor::WHITE, ConsoleColor::GRAY);
				std::cout << ' ';
			}
		}
	}

	for (int i = x; i < WINDOW_WIDTH + x; i++)
	{
		SetCursorPosition(i, 2);
		active ? SetColor(ConsoleColor::WHITE, ConsoleColor::BLUE) : SetColor(ConsoleColor::WHITE, ConsoleColor::GRAY);
		std::cout << ' ';
	}

	SetColor(WHITE, BLACK);
	drawInstructions();
}

void Menu::drawFrameSimple()
{
	size_t height = getFrameHeight()-1;

	for (size_t y = 0; y < height; y++)
	{
		for (size_t x = 0; x < 15; x++)
		{
			if (x == 0 || x == 14 || y == 0 || y == height - 1) {
				SetCursorPosition(x, y);
				SetColor(ConsoleColor::WHITE, ConsoleColor::BLUE);
				std::cout << ' ';
			}
		}
	}
	SetColor(WHITE, BLACK);
}

void Menu::drawOptions() {
	int startX = 3;
	int startY = 3;

	for (size_t i = 0; i < (options.size()+1)/2; i++)
	{
		SetCursorPosition(startX, startY + i);
		if (activeOption == i) {
			//active ? SetColor(RED, WHITE) : SetColor(RED, GRAY);
			SetColor(RED, WHITE);
		}
		else {
			SetColor(WHITE, BLACK);
		}
		auto item = options[i];
		if (item.size() > (WINDOW_WIDTH - 13))
		{
			item = item.substr(0, (WINDOW_WIDTH - 13)) + "...";
		}
		//item.append(std::string((WINDOW_WIDTH - SIZE_AREA) - item.size(), ' '));
		std::cout << item;
	}

	int shift = (options.size() - 1) / 2;
	SetColor(WHITE, BLACK);
	for (size_t j = (options.size() + 1) / 2; j < options.size(); j++)
	{
		SetCursorPosition(startX + WINDOW_WIDTH - SIZE_AREA, startY + j - shift);
		std::cout << options[j];
	}

}

void Menu::drawOptions(int x) {
	int startX = x+3;
	int startY = 3;

	for (size_t i = 0; i < (options.size() + 1) / 2; i++)
	{
		SetCursorPosition(startX, startY + i);
		if (activeOption == i) {
			SetColor(RED, WHITE);
		}
		else {
			SetColor(WHITE, BLACK);
		}
		auto item = options[i];
		if (item.size() > (WINDOW_WIDTH - 13))
		{
			item = item.substr(0, (WINDOW_WIDTH - 13)) + "...";
		}
		std::cout << item;
	}

	int shift = (options.size() - 1) / 2;
	SetColor(WHITE, BLACK);
	for (size_t j = (options.size() + 1) / 2; j < options.size(); j++)
	{
		SetCursorPosition(startX + WINDOW_WIDTH - SIZE_AREA, startY + j - shift);
		std::cout << options[j];
	}


}

void Menu::drawOptionsSimple() 
{
	int startX = 2;
	int startY = 1;

	for (size_t i = 0; i < options.size(); i++)
	{
		SetCursorPosition(startX, startY + i);
		if (activeOption == i) {
			SetColor(RED, WHITE);
		}
		else {
			SetColor(WHITE, BLACK);
		}
		auto item = options[i];
		if (item.size() > (WINDOW_WIDTH - 13))
		{
			item = item.substr(0, (WINDOW_WIDTH - 13)) + "...";
		}
		std::cout << item;
	}
	SetColor(ConsoleColor::WHITE, ConsoleColor::BLACK);
}

void Menu::drawCurrentPath(std::string currentPath, int x, int y)
{
	SetCursorPosition(x, y);
	std::string cut;
	if (currentPath.size() < (WINDOW_WIDTH-5))
	{
		std::cout << currentPath;
	}
	else
	{
		cut = "..." + currentPath.substr(currentPath.size() - (WINDOW_WIDTH-5));
		std::cout << cut;
	}
}

void Menu::drawSearchResults(std::vector <std::string> results)
{
	system("cls");
	SetCursorPosition(0, 0);

	for (size_t coordY = 0; coordY < (results.size() / 2) + 3; coordY++)
	{
		for (size_t coordX = 0; coordX < WINDOW_WIDTH; coordX++)
		{
			if (coordX == 0 || coordX == WINDOW_WIDTH-1 || coordY == 0 || coordY == (results.size() / 2) + 2) {
				SetCursorPosition(coordX, coordY);
				SetColor(ConsoleColor::WHITE, ConsoleColor::RED_FADE);
				std::cout << ' ';
			}
		}
	}
	SetCursorPosition(1, 0);
	std::cout << "SEARCH RESULTS:" << std::endl;

	SetCursorPosition(0, 0);

	for (size_t coordY = 0; coordY < (results.size()/2) + 3; coordY++)
	{
		for (size_t coordX = WINDOW_WIDTH; coordX < WINDOW_WIDTH * 2; coordX++)
		{
			if (coordX == WINDOW_WIDTH || coordX == (WINDOW_WIDTH*2)-1 || coordY == 0 || coordY == (results.size() / 2) + 2) {
				SetCursorPosition(coordX, coordY);
				SetColor(ConsoleColor::WHITE, ConsoleColor::RED_FADE);
				std::cout << ' ';
			}
		}
	}
	SetCursorPosition(WINDOW_WIDTH+1, 0);
	std::cout << "PATH:" << std::endl;

	SetColor(ConsoleColor::WHITE, ConsoleColor::BLACK);

	if (!results.size())
	{
		SetCursorPosition(2, 1);
		std::cout << "No result found";
	}

	for (int i = 0; i < results.size()/2; i++)
	{
		SetCursorPosition(2, 1+i);
		if (results[i].size() > (WINDOW_WIDTH - 8))
		{
			results[i] = results[i].substr(0, (WINDOW_WIDTH - 8)) + "...";
		}
		std::cout << results[i] << std::endl;
	}

	for (int j = results.size() / 2; j < results.size(); j++)
	{
		SetCursorPosition(WINDOW_WIDTH+1, 1 + j- results.size() / 2);
		if (results[j].size() > (WINDOW_WIDTH - 8))
		{
			results[j] = "..." + results[j].substr(results[j].size() - (WINDOW_WIDTH - 8));
		}
		std::cout << results[j] << std::endl;
	}

	SetCursorPosition(2, 4 + (results.size() / 2));
	std::cout << "Press any key to exit";

}

void Menu::drawMessageFrame(std::string message)
{
	system("cls");
	SetCursorPosition(0, 0);

	for (size_t coordY = 0; coordY < 10; coordY++)
	{
		for (size_t coordX = 0; coordX < WINDOW_WIDTH; coordX++)
		{
			if (coordX == 0 || coordX == WINDOW_WIDTH - 1 || coordY == 0 || coordY == 10-1) {
				SetCursorPosition(coordX, coordY);
				SetColor(ConsoleColor::WHITE, ConsoleColor::GREEN_FADE);
				std::cout << ' ';
			}
		}
	}
	SetCursorPosition(1, 1);
	std::cout << message << std::endl;
	SetColor(ConsoleColor::WHITE, ConsoleColor::BLACK);
	SetCursorPosition(1, 2);
	if (message == "Enter seeking extention")
	{
		std::cout << "*.";
	}
}

void Menu::drawInstructions()
{

	int startX = (2 * WINDOW_WIDTH) + 2;
	int startY = 1;

	std::vector < std::string > item;
	item.push_back("TAB");
	item.push_back("switch window");
	item.push_back("SPACE");
	item.push_back("create new dir");
	item.push_back("1");
	item.push_back("copy");
	item.push_back("2");
	item.push_back("remove dir/file");
	item.push_back("3");
	item.push_back("move");
	item.push_back("4");
	item.push_back("rename");
	item.push_back("5");
	item.push_back("search by mask");
	item.push_back("6");
	item.push_back("change volume");
	item.push_back("ESC");
	item.push_back("exit");

	
	for (size_t i = 0; i < item.size(); i++)
	{
		SetCursorPosition(startX, startY + i);
		if (i % 2)
		{
			SetColor(WHITE, BLACK);
			startY++;
		}
		else
		{
			SetColor(WHITE, RED_FADE);
		}
		std::cout << item[i];
	}

}

void Menu::down() {
	activeOption++;
	if (activeOption >= ((options.size()+1)/2)) {
		activeOption = 0;
	}
}

void Menu::subDown() {
	activeOption++;
	if (activeOption >= options.size()) {
		activeOption = 0;
	}
}

void Menu::up() {
	activeOption--;
	if (activeOption < 0) {
		activeOption = ((options.size()+1)/2) - 1;
	}
}

void Menu::subUp() 
{
	activeOption--;
	if (activeOption < 0) {
		activeOption = options.size() - 1;
	}
}

int Menu::getSelectedOption() const {
	return activeOption;
}

size_t Menu::getWidth()
{
	return WINDOW_WIDTH;
}

size_t Menu::getHeight()
{
	return getFrameHeight();
}

void Menu::setActive(bool active)
{
	this->active = active;
}

bool Menu::getActive()
{
	return this->active;
}

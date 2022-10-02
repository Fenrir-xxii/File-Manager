#pragma once

#include <iostream>
#include <vector>
#include <string>
#include "console.h"
#include "FileManager.h"

#define WINDOW_WIDTH 60
#define SIZE_AREA 10

class Menu {
private:
	int activeOption = 0;
	std::vector<std::string> options;
	size_t getFrameHeight() const;
	bool active = true;
	//FileManager fileManager;

public:
	Menu(const std::vector<std::string>& options);

	void drawFrame(bool active = true);

	void drawFrame(int x, int y, size_t height, bool active = false);

	void drawFrameSimple();

	void drawOptions();

	void drawOptions(int x);

	void drawOptionsSimple();

	void drawCurrentPath(std::string currentPath, int x = 1, int y = 1);

	void drawSearchResults(std::vector <std::string> results);

	void drawMessageFrame(std::string message);

	void drawInstructions();

	void subDown();

	void down();

	void subUp();

	void up();

	int getSelectedOption() const;

	size_t getWidth();

	size_t getHeight();

	void setActive(bool active);

	bool getActive();

};


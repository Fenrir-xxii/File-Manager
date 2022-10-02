#include <iostream>
#include "FileManager.h"
#include "menu.h"



int main()
{	
	FileManager fmLEFT;
	FileManager fmRIGHT;
	
	std::vector < std::string> content = fmLEFT.getContent(fs::current_path().string());

	Menu leftMENU(content);
	Menu rightMENU(content);

	size_t width = WINDOW_WIDTH;
	size_t height = leftMENU.getHeight();

	rightMENU.setActive(false);

	int key;
	bool leftActive = true;

	Menu subMenu(content);
	std::vector<std::string> temp;
	std::string name;
	fs::path source;
	fs::path destination;
	int line;
	int line2;

	while (true)
	{
		leftMENU.drawFrame(leftActive);
		rightMENU.drawFrame(width, 0, height, !leftActive);
		leftMENU.drawCurrentPath(fmLEFT.getCurrentPath().string());
		rightMENU.drawCurrentPath(fmRIGHT.getCurrentPath().string(), 61, 1);
		rightMENU.drawOptions(width);
		leftMENU.drawOptions();
		key = getKey();

		switch (key)
		{
		case UP_ARROW:
			leftActive ? leftMENU.up() : rightMENU.up();
			break;
		case DOWN_ARROW:
			leftActive ? leftMENU.down() : rightMENU.down();
			break;
		case TAB:
			// switch menu
			leftActive = !leftActive;
			break;
		case ENTER:
			if (leftActive)
			{
				if (leftMENU.getSelectedOption() == 0)  // previous folder
				{
					destination = fmLEFT.previousDirectory();
				}
				else
				{
					destination = fmLEFT.enterDirectory(leftMENU.getSelectedOption());
				}
				leftMENU = fmLEFT.getContent(destination);
			}
			else
			{
				if (rightMENU.getSelectedOption() == 0)  // previous folder
				{
					destination = fmRIGHT.previousDirectory();
				}
				else
				{
					destination = fmRIGHT.enterDirectory(rightMENU.getSelectedOption());
				}
				rightMENU = fmRIGHT.getContent(destination);
			}
			break;
		case SPACE:
			// create directory
			leftMENU.drawMessageFrame("Enter name of directory");
			std::getline(std::cin, name);
			if (leftActive)
			{
				fmLEFT.createDirectory(name);
				leftMENU = fmLEFT.getContent(fmLEFT.getCurrentPath());
			}
			else
			{
				fmRIGHT.createDirectory(name);
				rightMENU = fmRIGHT.getContent(fmRIGHT.getCurrentPath());
			}
			break;
		case COPY_1:
			//copy
			if (leftActive)
			{
				if (leftMENU.getSelectedOption() == 0)  // previous folder
				{
					break;
				}
				line = leftMENU.getSelectedOption();
				source = fmLEFT.getCurrentPath();
				destination = fmRIGHT.getCurrentPath();
				fmLEFT.copy(source, destination, line, true);
				rightMENU = fmRIGHT.getContent(fmRIGHT.getCurrentPath());
			}
			else
			{
				if (rightMENU.getSelectedOption() == 0)  // previous folder
				{
					break;
				}
				line = rightMENU.getSelectedOption();
				source = fmRIGHT.getCurrentPath();
				destination = fmLEFT.getCurrentPath();
				fmRIGHT.copy(source, destination, line, true);
				leftMENU = fmLEFT.getContent(fmLEFT.getCurrentPath());
			}
			break;
		case DELETE_2:
			// delete file / dir
			if (leftActive)
			{
				if (leftMENU.getSelectedOption() == 0)  // previous folder
				{
					break;
				}
				line = leftMENU.getSelectedOption();
				source = fmLEFT.getCurrentPath();
				fmLEFT.remove(source, line);
				leftMENU = fmLEFT.getContent(fmLEFT.getCurrentPath());
			}
			else
			{
				if (rightMENU.getSelectedOption() == 0)  // previous folder
				{
					break;
				}
				line = rightMENU.getSelectedOption();
				source = fmRIGHT.getCurrentPath();
				fmRIGHT.remove(source, line);
				rightMENU = fmRIGHT.getContent(fmRIGHT.getCurrentPath());
			}
			break;
		case MOVE_3:
			// move file / dir
			if (leftActive)
			{
				if (leftMENU.getSelectedOption() == 0)  // previous folder
				{
					break;
				}
				line = leftMENU.getSelectedOption();
				source = fmLEFT.getCurrentPath();
				destination = fmRIGHT.getCurrentPath();
				fmLEFT.move(source, destination, line);
				leftMENU = fmLEFT.getContent(fmLEFT.getCurrentPath());
				rightMENU = fmRIGHT.getContent(fmRIGHT.getCurrentPath());
			}
			else
			{
				if (rightMENU.getSelectedOption() == 0)  // previous folder
				{
					break;
				}
				line = rightMENU.getSelectedOption();
				source = fmRIGHT.getCurrentPath();
				destination = fmLEFT.getCurrentPath();
				fmRIGHT.move(source, destination, line);
				rightMENU = fmRIGHT.getContent(fmRIGHT.getCurrentPath());
				leftMENU = fmLEFT.getContent(fmLEFT.getCurrentPath());
			}
			break;
		case RENAME_4:
			// rename file / dir
			if (leftActive)
			{
				if (leftMENU.getSelectedOption() == 0)  // previous folder
				{
					break;
				}
				line = leftMENU.getSelectedOption();
				source = fmLEFT.getCurrentPath();
				leftMENU.drawMessageFrame("Enter new name");
				std::getline(std::cin, name);
				fmLEFT.rename(source, line, name);
				leftMENU = fmLEFT.getContent(fmLEFT.getCurrentPath());
			}
			else
			{
				if (rightMENU.getSelectedOption() == 0)  // previous folder
				{
					break;
				}
				line = rightMENU.getSelectedOption();
				source = fmRIGHT.getCurrentPath();
				rightMENU.drawMessageFrame("Enter new name");
				std::getline(std::cin, name);
				fmRIGHT.rename(source, line, name);
				rightMENU = fmRIGHT.getContent(fmRIGHT.getCurrentPath());
			}
			break;
		case SEARCH_5:
			// search by mask
			leftMENU.drawMessageFrame("Enter seeking extention");
			std::cin >> name;
			temp = fmLEFT.search(name);
			leftMENU.drawSearchResults(temp);
			do
			{
				key = getKey();
			} while (key < 0);
			system("cls");
			break;
		case CHANGE_VOL_6:
			// change volume
			system("cls");
			temp = fmLEFT.getVolumes();
			subMenu = temp;
			do
			{
				subMenu.drawOptionsSimple();
				subMenu.drawFrameSimple();
				key = getKey();
				switch (key)
				{
				case UP_ARROW:
					subMenu.subUp();
					break;
				case DOWN_ARROW:
					subMenu.subDown();
					break;
				case ENTER:
					line2 = subMenu.getSelectedOption();
					destination = temp[line];
					if (leftActive)
					{
						leftMENU = fmLEFT.getContent(destination);
						fmLEFT.setCurrentPath(destination);
					}
					else
					{
						rightMENU = fmRIGHT.getContent(destination);
						fmRIGHT.setCurrentPath(destination);
					}
					break;
				case ESC:
					break;
				}
			} while (key != ESC and key!=ENTER);
			system("cls");
			break;
		case ESC:
			system("cls");
			return 0;
			break;
		default:
			break;
		}
		Sleep(100);
	}
}


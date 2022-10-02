#pragma once
#include <filesystem>
#include <iostream>
#include <string>
#include <vector>
#include "menu.h"
#include <fstream>

namespace fs = std::filesystem;

class FileManager
{
protected:
	fs::path currentPath = fs::current_path();
public:
	void createDirectory(std::string& dirName);
	void copy(fs::path& sourcePath, fs::path& destinationPath, int line, bool recursive = false);
	void move(fs::path& from, fs::path& to, int line);
	void remove(fs::path& path, int line);
	void rename(fs::path& from, int line, std::string newName);
	std::vector <std::string> getContent(fs::path path);
	std::vector <std::string> getFileSizes(fs::path path);
	fs::path getCurrentPath();
	fs::path enterDirectory(int line);
	fs::path previousDirectory();
	std::vector<std::string> search(std::string seek);
	void readFile(fs::path& path);
	std::vector<std::string> getVolumes();
	//fs::path changeVolume(char vol);
	void setCurrentPath(fs::path path);
};

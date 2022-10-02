#include "FileManager.h"

void FileManager::createDirectory(std::string& dirName)
{
    fs::path path = this->currentPath;
    path /= dirName;
    fs::create_directory(path);
}

void FileManager::copy(fs::path& sourcePath, fs::path& destinationPath, int line, bool recursive)
{
    std::string name;
    int i = 0;

    try
    {
        if (fs::exists(sourcePath) and fs::exists(destinationPath))
        {

            for (auto const& dirEntry : fs::directory_iterator{ sourcePath })
            {
                if (dirEntry.is_directory())
                {
                    if (i == line - 1)
                    {
                        if (recursive)
                        {
                            name = dirEntry.path().filename().string();
                            destinationPath /= name;
                            fs::create_directory(destinationPath);
                            fs::copy(dirEntry, destinationPath, fs::copy_options::overwrite_existing | fs::copy_options::recursive);
                        }
                        else
                        {
                            fs::copy(sourcePath, destinationPath, fs::copy_options::overwrite_existing);
                        }
                    }
                    i++;
                }

            }
            for (auto const& dirEntry : fs::directory_iterator{ sourcePath })
            {
                if (dirEntry.is_regular_file())
                {
                    if (i == line - 1)
                    {
                        name = dirEntry.path().filename().string();
                        sourcePath /= name;
                        if (recursive)
                        {
                            fs::copy(sourcePath, destinationPath, fs::copy_options::overwrite_existing | fs::copy_options::recursive);
                        }
                        else
                        {
                            fs::copy(sourcePath, destinationPath, fs::copy_options::overwrite_existing);
                        }
                    }
                    i++;
                }
            }
        }
    }
    catch (std::exception& e)
    {
        std::cout << e.what();
    }
}

void FileManager::move(fs::path& from, fs::path& to, int line)
{
    std::string name;
    int i = 0;

    for (auto const& dirEntry : fs::directory_iterator{ from })
    {
        if (dirEntry.is_directory())
        {
            if (i == line - 1)
            {
                name = dirEntry.path().filename().string();
                to /= name;
                from /= name;
                i++;
                break;
            }
            i++;
        }
    }

    for (auto const& dirEntry : fs::directory_iterator{ from })
    {
        if (dirEntry.is_regular_file())
        {
            if (i == line - 1)
            {
                name = dirEntry.path().filename().string();
                to /= name;
                from /= name;
                i++;
                break;
            }
            i++;
        }
    }

    try
    {
        if (fs::exists(from) and !(fs::exists(to)))
        {
            fs::rename(from, to);
        }
    }
    catch (std::exception& e)
    {
        std::cout << e.what();
    }
}

void FileManager::remove(fs::path& path, int line)
{
    std::string name;
    int i = 0;

    try
    {
        if (fs::exists(path))
        {

            for (auto const& dirEntry : fs::directory_iterator{ path })
            {
                if (dirEntry.is_directory())
                {
                    if (i == line - 1)
                    {
                        name = dirEntry.path().filename().string();
                        path /= name;
                        fs::remove_all(path);
                    }
                    i++;
                }
            }
            for (auto const& dirEntry : fs::directory_iterator{ path })
            {
                if (dirEntry.is_regular_file())
                {
                    if (i == line - 1)
                    {
                        name = dirEntry.path().filename().string();
                        path /= name;
                        fs::remove(path);
                    }
                    i++;
                }
            }
        }
        // else if destinationPath doesn't exist ask user to create one
    }
    catch (std::exception& e)
    {
        std::cout << e.what();
    }
}

void FileManager::rename(fs::path& from, int line, std::string newName)
{
    std::string name;
    int i = 0;

    fs::path newPath = this->currentPath;
    newPath /= newName;

    for (auto const& dirEntry : fs::directory_iterator{ from })
    {
        if (dirEntry.is_directory())
        {
            if (i == line - 1)
            {
                name = dirEntry.path().filename().string(); 
                from /= name;
                i++;
                break;
            }
            i++;
        }
    }

    for (auto const& dirEntry : fs::directory_iterator{ from })
    {
        if (dirEntry.is_regular_file())
        {
            if (i == line - 1)
            {
                name = dirEntry.path().filename().string();
                from /= name;
                i++;
                break;
            }
            i++;
        }
    }


    try
    {
        if (fs::exists(from) and !(fs::exists(newPath)))
        {
            fs::rename(from, newPath);
        }
    }
    catch (std::exception& e)
    {
        std::cout << e.what();
    }

}

std::vector <std::string> FileManager::getContent(fs::path path)
{
    system("cls");
    std::vector<std::string> names;
    std::string name;

    names.push_back("...(^)");

    for (auto const& dirEntry : fs::directory_iterator{ path })  // pushes all directories first
    {
        if (dirEntry.is_directory())
        {
            name = dirEntry.path().filename().string();
            name = "> " + name;
            names.push_back(name);
        }
    }

    for (auto const& dirEntry : fs::directory_iterator{ path }) // pushes all files after folders
    {
        if (dirEntry.is_regular_file())
        {
            name = dirEntry.path().filename().string();
            name = "* " + name;
            names.push_back(name);
        }
    }
    std::vector<std::string> sizes = getFileSizes(path);  // get sizes of files and push it to names vector

    for (int i = 0; i < sizes.size(); i++)
    {
        names.push_back(sizes[i]);
    }
    system("cls");
    return names;
}

std::vector <std::string> FileManager::getFileSizes(fs::path path)
{
    std::vector<std::string> sizes;
    std::string size;
    int temp;
    std::string filePath = "";

    for (auto const& dirEntry : fs::directory_iterator{ path })
    {
        if (dirEntry.is_directory())
        {
            size = "<DIR>";
            sizes.push_back(size);
        }
    }

    for (auto const& dirEntry : fs::directory_iterator{ path })
    {
        if (dirEntry.is_regular_file())
        {
            filePath = dirEntry.path().string();
			try {
				temp = fs::file_size(filePath);
			}
			catch (...)
			{
				temp = 0;
			};
            size = std::to_string(temp);
            sizes.push_back(size);
        }
    }

    return sizes;
}

fs::path FileManager::getCurrentPath()
{
    return this->currentPath;
}

fs::path FileManager::enterDirectory(int line)
{
    fs::path newPath = currentPath;

    int i = 0;
    int key = 0;
    std::string name;

    for (auto const& dirEntry : fs::directory_iterator{ newPath })
    {
        if (dirEntry.is_directory())
        {
            name = dirEntry.path().filename().string();
            if (i == line - 1)
            {
                newPath /= name;
                currentPath = newPath;
                return newPath;
            }
            i++;
        }
    }

    for (auto const& dirEntry : fs::directory_iterator{ newPath })  // if file -> open it
    {
        if (dirEntry.is_regular_file())
        {
            name = dirEntry.path().filename().string();
            if (i == line - 1)
            {
                newPath /= name;
                readFile(newPath);
                do {
                    key = getKey();
                } while (key < 0);
                return currentPath;
            }
            i++;
        }
    }

    return currentPath;
}


fs::path FileManager::previousDirectory()
{
    fs::path newPath = currentPath;

    if (newPath.has_parent_path())
    {
        currentPath = currentPath.parent_path();
    }

    return currentPath;
}

std::vector<std::string> FileManager::search(std::string seek)
{
    std::vector<std::string> result;
    std::vector<std::string> path;
    fs::path currentPath = this->currentPath;
    std::string name;
    std::string pathOfFoundFile;

    seek = "." + seek;

    for (auto const& dirEntry : fs::recursive_directory_iterator{ currentPath })
    {
        if (dirEntry.is_regular_file())
        {
            name = dirEntry.path().filename().string();
            currentPath = fs::current_path();
            currentPath /= name;
            if (currentPath.extension() == seek)
            {
                result.push_back(name);
                pathOfFoundFile = dirEntry.path().string();
                fs::path temp(pathOfFoundFile);
                pathOfFoundFile = temp.parent_path().string();
                path.push_back(pathOfFoundFile);
            }

        }
    }

    for (int i = 0; i < path.size(); i++)
    {
        result.push_back(path[i]);
    }

    return result;
}

void FileManager::readFile(fs::path& path)
{
    system("cls");
    SetColor(BLACK, YELLOW_FADE);
    std::cout << "�ontents of file: " << path << std::endl << std::endl;
    SetColor(WHITE, BLACK);

    std::string text;
    std::ifstream file(path);

    if (file.is_open())
    {
        while (getline(file, text))
        {
            std::cout << text << std::endl;
        }
        file.close();
    }
    else
    {
        std::cout << "Unable to open file" << std::endl;
    }
    SetColor(BLACK, YELLOW_FADE);
    std::cout << "\n\n\n\nPress any key to exit";
    SetColor(WHITE, BLACK);
}

std::vector<std::string> FileManager::getVolumes()
{
    std::string pathStr = ":\\";
    fs::path p = pathStr;
    std::vector < std::string> volumes;
    char letter = 'A';
    for (int i = 65; i < 91; i++)
    {
        try
        {
            pathStr = letter + pathStr;
            p = pathStr;
            if (fs::exists(p))
            {
                volumes.push_back(pathStr);
                //std::cout << letter << " Exists\n";
            }
            letter++;
            pathStr = ":\\";
        }
        catch (...)
        {
            //std::cout << letter << " Do not exist\n";
        }
    }

    return volumes;
}

//fs::path FileManager::changeVolume(char vol)
//{
//	// show existing volumes
//	// convert from lowercase to upper
//	// check is such volume exists
//
//
//	fs::path newPath = this->currentPath;
//	std::string p = ":\\";
//
//
//	p = vol + p;
//	newPath = p;
//
//	return newPath;
//}

void FileManager::setCurrentPath(fs::path path)
{
    this->currentPath = path;
}
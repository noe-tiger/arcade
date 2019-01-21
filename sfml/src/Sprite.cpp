//
// EPITECH PROJECT, 2018
// arcade
// File description:
// sfml interface
//

#include "Sprite.hpp"
#include "Core.hpp"
#include "Sfml.hpp"


#include <iostream>
namespace arcade {
Sprite::Sprite(const std::string &pathname)
{
	if (!pathname.empty())
		setImage(pathname);
}

bool Sprite::setImage(const std::string &pathname)
{
	_texture.loadFromFile(pathname);
	this->setTexture(_texture);
	return true;
}

static bool fileDir(std::vector<std::string> &container,
		    const std::string &folderName)
{
	DIR *directory;
	struct dirent *dirent;

	directory = opendir(folderName.c_str());
	if (!directory)
		return false;
	while ((dirent = readdir(directory)))
		if (dirent->d_type == DT_REG)
			container.push_back(
				std::string(folderName + dirent->d_name));
	closedir(directory);
	sort(container.begin(), container.end());
	return true;
}


bool loadSprites(std::vector<Sprite> &sprites, const std::string &folder)
{
	std::vector<std::string> files;

	if (!fileDir(files, folder))
		return false;
	sprites.resize(files.size());
	for (size_t i = 0; i < files.size(); ++i)
		sprites[i].setImage(files[i]);
	return true;
}
} // namespace arcade

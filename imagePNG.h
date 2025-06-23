#ifndef IMAGEPNG_H
#define IMAGEPNG_H

#include <string>
#include <vector>

class ImagePNG {
public:
	ImagePNG(std::string_view name, std::vector<unsigned char>& imgData, int height, int width, int channels);
	~ImagePNG();

	const std::string& getName();
	std::vector<unsigned char> getImageData();
	void setImageData(std::vector<unsigned char> imgData);
	int& getHeight();
	int& getWidth();
	int& getChannels();
	size_t& getSize();

private:
	const std::string name;
	std::vector<unsigned char> imgData;
	int height{};
	int width{};
	int channels{};
	size_t size{};
};

#endif

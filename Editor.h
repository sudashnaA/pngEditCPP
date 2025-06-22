#ifndef EDITOR_H
#define EDITOR_H

#include "imagePNG.h"
#include <memory>
#include <vector>

class Editor {

public:
	Editor();
	~Editor();

	void readImage(std::string imageName);
	void openImage(std::string imageName);
	void writeEdits();
	const std::unique_ptr<ImagePNG>& getLatestImage();
	void resetImageEditsHistory();
	void clearImageEditsHistory();
	void addToImageEditsHistory(std::unique_ptr<ImagePNG> image);

private:
	std::vector<std::unique_ptr<ImagePNG>> ImageEditsHistory;
};

#endif 


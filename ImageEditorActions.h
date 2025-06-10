#ifndef IMAGEEDITORACTIONS_H
#define IMAGEEDITORACTIONS_H

void increaseBrightness(unsigned char*& imgData, int width, int height, int channels);
void applyColorTint(unsigned char*& imgData, int width, int height, int channels);
void resetEdits(unsigned char*& imgData, unsigned char*& imgDataCopy, size_t size);
void saveImage(unsigned char*& imgData, int width, int height, int channels);
bool exitProgram();

#endif

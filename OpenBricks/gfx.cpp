#include "gfx.h"

void blurDrawBufferHorizontally(int radius, OSL_IMAGE* blurBuffer)
{
  unsigned int sumR, sumG, sumB;
  unsigned int n = 2 * radius + 1;
  unsigned long *destPxl, *readPxl;
  oslLockImage(blurBuffer);
  for (int j = 0; j < blurBuffer->sizeY; ++j) {
    //Blurring line j
    sumR = 0;
    sumG = 0;
    sumB = 0;
    //Calc first sum
    for (int i = 0; i < radius; ++i) {
      readPxl = (unsigned long*)oslGetImagePixelAddr(osl_curBuf, i, j);
      sumR += (0x0000ff & (*readPxl));
      sumG += (0x00ff00 & (*readPxl)) >> 8;
      sumB += (0xff0000 & (*readPxl)) >> 16;
    }
    //Start blurring
    //First, just add pixels
    for (int i = 0; i < (radius + 1); ++i) {
      readPxl = (unsigned long*)oslGetImagePixelAddr(osl_curBuf, i + radius, j);
      sumR += (0x0000ff & (*readPxl));
      sumG += (0x00ff00 & (*readPxl)) >> 8;
      sumB += (0xff0000 & (*readPxl)) >> 16;
      destPxl = (unsigned long*)oslGetImagePixelAddr(blurBuffer, i, j);
      *destPxl = RGB(sumR/(i+radius+1), sumG/(i+radius+1), sumB/(i+radius+1));
    }
    //Then add and substract at the same time
    for (int i = (radius + 1); i < (blurBuffer->sizeX - radius); ++i) {
      readPxl = (unsigned long*)oslGetImagePixelAddr(osl_curBuf, i + radius, j);
      sumR += (0x0000ff & (*readPxl));
      sumG += (0x00ff00 & (*readPxl)) >> 8;
      sumB += (0xff0000 & (*readPxl)) >> 16;
      readPxl = (unsigned long*)oslGetImagePixelAddr(osl_curBuf, i - radius - 1, j);
      sumR -= (0x0000ff & (*readPxl));
      sumG -= (0x00ff00 & (*readPxl)) >> 8;
      sumB -= (0xff0000 & (*readPxl)) >> 16;
      destPxl = (unsigned long*)oslGetImagePixelAddr(blurBuffer, i, j);
      *destPxl = RGB(sumR/n, sumG/n, sumB/n);
    }
    //Finally only substract
    for (int i = (blurBuffer->sizeX - radius); i < blurBuffer->sizeX; ++i) {
      readPxl = (unsigned long*)oslGetImagePixelAddr(osl_curBuf, i - radius - 1, j);
      sumR -= (0x0000ff & (*readPxl));
      sumG -= (0x00ff00 & (*readPxl)) >> 8;
      sumB -= (0xff0000 & (*readPxl)) >> 16;
      destPxl = (unsigned long*)oslGetImagePixelAddr(blurBuffer, i, j);
      *destPxl = RGB(sumR/(blurBuffer->sizeX-i+radius), sumG/(blurBuffer->sizeX-i+radius), sumB/(blurBuffer->sizeX-i+radius));
    }
  }
  oslUnlockImage(blurBuffer);
  oslDrawImage(blurBuffer);
}

void blurDrawBufferVertically(int radius, OSL_IMAGE* blurBuffer)
{
  unsigned int sumR, sumG, sumB;
  unsigned int n = 2 * radius + 1;
  unsigned long *destPxl, *readPxl;
  oslLockImage(blurBuffer);
  for (int i = 0; i < blurBuffer->sizeX; ++i) {
    //Blurring column i
    sumR = 0;
    sumG = 0;
    sumB = 0;
    //Calc first sum
    for (int j = 0; j < radius; ++j) {
      readPxl = (unsigned long*)oslGetImagePixelAddr(osl_curBuf, i, j);
      sumR += (0x0000ff & (*readPxl));
      sumG += (0x00ff00 & (*readPxl)) >> 8;
      sumB += (0xff0000 & (*readPxl)) >> 16;
    }
    //Start blurring
    //First, just add pixels
    for (int j = 0; j < (radius + 1); ++j) {
      readPxl = (unsigned long*)oslGetImagePixelAddr(osl_curBuf, i, j + radius);
      sumR += (0x0000ff & (*readPxl));
      sumG += (0x00ff00 & (*readPxl)) >> 8;
      sumB += (0xff0000 & (*readPxl)) >> 16;
      destPxl = (unsigned long*)oslGetImagePixelAddr(blurBuffer, i, j);
      *destPxl = RGB(sumR/(j+radius+1), sumG/(j+radius+1), sumB/(j+radius+1));
    }
    //Then add and substract at the same time
    for (int j = (radius + 1); j < (blurBuffer->sizeY - radius); ++j) {
      readPxl = (unsigned long*)oslGetImagePixelAddr(osl_curBuf, i, j + radius);
      sumR += (0x0000ff & (*readPxl));
      sumG += (0x00ff00 & (*readPxl)) >> 8;
      sumB += (0xff0000 & (*readPxl)) >> 16;
      readPxl = (unsigned long*)oslGetImagePixelAddr(osl_curBuf, i, j - radius - 1);
      sumR -= (0x0000ff & (*readPxl));
      sumG -= (0x00ff00 & (*readPxl)) >> 8;
      sumB -= (0xff0000 & (*readPxl)) >> 16;
      destPxl = (unsigned long*)oslGetImagePixelAddr(blurBuffer, i, j);
      *destPxl = RGB(sumR/n, sumG/n, sumB/n);
    }
    //Finally only substract
    for (int j = (blurBuffer->sizeY - radius); j < blurBuffer->sizeY; ++j) {
      readPxl = (unsigned long*)oslGetImagePixelAddr(osl_curBuf, i, j - radius - 1);
      sumR -= (0x0000ff & (*readPxl));
      sumG -= (0x00ff00 & (*readPxl)) >> 8;
      sumB -= (0xff0000 & (*readPxl)) >> 16;
      destPxl = (unsigned long*)oslGetImagePixelAddr(blurBuffer, i, j);
      *destPxl = RGB(sumR/(blurBuffer->sizeY-j+radius), sumG/(blurBuffer->sizeY-j+radius), sumB/(blurBuffer->sizeY-j+radius));
    }
  }
  oslUnlockImage(blurBuffer);
  oslDrawImage(blurBuffer);
}

void blurDrawBuffer(int radius, OSL_IMAGE* blurBuffer)
{
  blurDrawBufferHorizontally(radius, blurBuffer);
  blurDrawBufferVertically(radius, blurBuffer);
}

void drawImageFrameXY(OSL_IMAGE *img, int frame, int x, int y)
{
  oslSetImageFrame(img, frame);
  oslDrawImageXY(img, x ,y);
}

// Screenshot.cpp : 
//

#include "stdafx.h"
#include "Screenshot.h"

void Screenshot::Shot() {
	// Taking screenshot and converting http://en.sfml-dev.org/forums/index.php?PHPSESSID=mh8852hrt7604lvb9nhk0c9ng5&topic=14323.15

	// (1) get the device context of the screen
	// Definition: The CreateDC function creates a device context (DC) 
	//  ..for a device using the specified name.
	HDC hScreenDC = CreateDCA("DISPLAY", NULL, NULL, NULL);

	// (2) and a device context to put it in
	// Definition: The CreateCompatibleDC function creates a memory 
	//  ..device context (DC) compatible with the specified device.
	HDC hMemoryDC = CreateCompatibleDC(hScreenDC);

	// (3) Gets the users screen size in x and y dimensions
	// Definition: The GetDeviceCaps function retrieves device-specific 
	//  ..information for the specified device.
	int x = GetDeviceCaps(hScreenDC, HORZRES);
	int y = GetDeviceCaps(hScreenDC, VERTRES);

	// (4) maybe worth checking these are positive values
	// Definition: The CreateCompatibleBitmap function creates a bitmap 
	//  ..compatible with the device that is associated with the specified 
	//  ..device context.
	HBITMAP hBitmap = CreateCompatibleBitmap(hScreenDC, x, y);

	// (5) get a new bitmap
	// Definition: The SelectObject function selects an object into the 
	//  ..specified device context (DC). The new object replaces the previous 
	//  ..object of the same type.
	HBITMAP hOldBitmap = (HBITMAP)SelectObject(hMemoryDC, hBitmap);

	// Definition: The BitBlt function performs a bit-block transfer of the 
	//  ..color data corresponding to a rectangle of pixels from the specified 
	//  ..source device context into a destination device context.
	BitBlt(hMemoryDC, 0, 0, x, y, hScreenDC, 0, 0, SRCCOPY);

	BITMAP bm;
	::GetObject(hBitmap, sizeof(bm), &bm);

	BITMAPINFO bmpInfo;
	bmpInfo.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
	bmpInfo.bmiHeader.biWidth = bm.bmWidth;
	bmpInfo.bmiHeader.biHeight = -bm.bmHeight;
	bmpInfo.bmiHeader.biPlanes = 1;
	bmpInfo.bmiHeader.biBitCount = 32;
	bmpInfo.bmiHeader.biCompression = BI_RGB;
	bmpInfo.bmiHeader.biSizeImage = 0;
	bmpInfo.bmiHeader.biClrImportant = 0;

	COLORREF* pixel = new COLORREF[bm.bmWidth * bm.bmHeight];
	GetDIBits(hMemoryDC, hBitmap, 0, bm.bmHeight, pixel, &bmpInfo, DIB_RGB_COLORS);

	originalImage->create(bm.bmWidth, bm.bmHeight, sf::Color::Black);
	int j = 0;
	for (int y = 0; y < bm.bmHeight; ++y)
	{
		for (int x = 0; x < bm.bmWidth; ++x)
		{
			COLORREF thisColor = pixel[j++];
			originalImage->setPixel(x, y, sf::Color(GetBValue(thisColor), GetGValue(thisColor), GetRValue(thisColor)));
		}
	}
}

const time_point<system_clock>  Screenshot::TimestampSet() {
	return system_clock::now();
}

const time_point<system_clock> Screenshot::TimestampGet(){
	return timestamp;
}

shared_ptr<sf::Image> Screenshot::ImageGet() {
	return originalImage;
}

string Screenshot::LabelGet() {
	return label;
}

void Screenshot::LabelSet(string text) {
	this->label = text;
}

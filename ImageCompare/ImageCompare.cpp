// ImageCompare.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <windows.h>
#include <gdiplus.h>
using namespace Gdiplus;
#pragma comment(lib, "gdiplus.lib")
//seriously? It can't find the freaking .lib?

int wmain(int argc,      // Number of strings in array argv
	wchar_t  *argv[],   // Array of command-line argument strings
	wchar_t *envp[])  // Array of environment variable strings
{	

	if (4 != argc) { // 2 input files, 1 output file and the argv[0] executable file.
		printf("Usage %ws, image1, image2, output\nThe images will be XORed and returned in the output file", argv[0]);
		return 1;
		}
	Status  stat;
	GdiplusStartupInput gdiplusStartupInput;
	ULONG_PTR gdiplusToken;
	GdiplusStartup(&gdiplusToken, &gdiplusStartupInput, NULL);
	
	Bitmap* image1 = new Bitmap(argv[1]); //stmt31_96.png
	printf("Source image %ws is %u x %u\n", argv[1], image1->GetWidth(), image1->GetHeight());
	HBITMAP hImage1 = 0;
	image1->GetHBITMAP(Color::White, &hImage1);
	HDC src = CreateCompatibleDC(0);
	SelectObject(src, hImage1);

	Bitmap* image2 = new Bitmap(argv[2]);
	printf("Destination image %ws is %u x %u\n", argv[2], image2->GetWidth(), image2->GetHeight());
	HBITMAP hImage2 = 0;
	image2->GetHBITMAP(Color::White, &hImage2);
	HDC dst = CreateCompatibleDC(0);
	//HDC dst = CreateDC(L"DISPLAY", NULL, NULL, NULL); //NO! Makes it show up on the display.
	SelectObject(dst, hImage2);

	if ((image1->GetWidth() != image2->GetWidth())
		|| (image1->GetHeight() != image2->GetHeight())
		|| (0 == image1->GetHeight() )
		|| (0 == image1->GetWidth() )
		) {
		printf("ERROR: Size mismatch. All images must be the same size\n");
		}
	else {
		BOOL ok;
		ok = BitBlt(dst, 0, 0, image2->GetWidth(), image2->GetHeight(), src, 0, 0, SRCINVERT ); //SCRERASE also interesting
		printf("Comparison complete, writing %ws\n",argv[3]);

		Bitmap* image3 = new Bitmap(hImage2, NULL); 

		//always returns white
		//Bitmap* image3 = new Bitmap(image2->GetWidth(),image2->GetHeight(),image2->GetPixelFormat());	image3->FromHBITMAP(hImage2, NULL); 
		//GetObject(dst, sizeof(image3), image3);

		//CLSID   encoderClsid;
		//GetEncoderClsid(L"image/png", &encoderClsid); //scans a list of all encoders to match the text name? Stupid.
		//const CLSID encoderClsid = CreateGUID("{557cf406-1a04-11d3-9a73-0000f81ef32e}"); //requires a template and atlbase.h
		//just get me the encoder for PNG?
		const CLSID encoderClsid = { 0x557cf406, 0x1a04, 0x11d3,{ 0x9a,0x73,0x00,0x00,0xf8,0x1e,0xf3,0x2e } };
		stat = image3->Save(argv[3], &encoderClsid, NULL);
		delete image3;
		}
	DeleteDC(src);
	DeleteDC(dst);
	DeleteObject(hImage1);
	DeleteObject(hImage2);
	delete image1;
	delete image2;
	GdiplusShutdown(gdiplusToken);
	return 0;
}


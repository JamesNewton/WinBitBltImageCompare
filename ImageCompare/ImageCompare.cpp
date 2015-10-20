// ImageCompare.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <windows.h>
//#include <atlbase.h>
//#include <wingdi.h>
#include <atlimage.h>
//for CImage
//#include <afxwin.h>
//for CBitmap
#include <gdiplus.h>
//#include "GdiPlusImageCodec.h"
using namespace Gdiplus;
#pragma comment(lib, "gdiplus.lib")
//seriously? It can't find the freaking .lib?

//template<class S>
//CLSID CreateGUID(const S& hexString)
//{
//	CLSID clsid;
//	CLSIDFromString(CComBSTR(hexString), &clsid);
//
//	return clsid;
//}

wchar_t *convertCharArrayToLPCWSTR(const char* charArray)
{
	wchar_t* wString = new wchar_t[4096];
	MultiByteToWideChar(CP_ACP, 0, charArray, -1, wString, 4096);
	return wString;
}

int main(int argc,      // Number of strings in array argv
	char *argv[],   // Array of command-line argument strings
	char *envp[])  // Array of environment variable strings
{	
	Status  stat;
	GdiplusStartupInput gdiplusStartupInput;
	ULONG_PTR gdiplusToken;
	GdiplusStartup(&gdiplusToken, &gdiplusStartupInput, NULL);


	Bitmap* image1 = new Bitmap(L"E:\\Driver\\flantest\\coll91_96.png"); //stmt31_96.png
	printf("Source image: %u x %u\n", image1->GetWidth(), image1->GetHeight());
	HBITMAP hImage1 = 0;
	image1->GetHBITMAP(Color::White, &hImage1);
	HDC src = CreateCompatibleDC(0);
	SelectObject(src, hImage1);

	Bitmap* image2 = new Bitmap(L"E:\\Driver\\flantest\\inv23_96.png");
	printf("Destination image: %u x %u\n", image2->GetWidth(), image2->GetHeight());
	HBITMAP hImage2 = 0;
	image2->GetHBITMAP(Color::White, &hImage2);
	HDC dst = CreateCompatibleDC(0);
	//HDC dst = CreateDC(L"DISPLAY", NULL, NULL, NULL); //NO! Makes it show up on the display.
	SelectObject(dst, hImage2);

	if ((image1->GetWidth() != image2->GetWidth()) || (image1->GetHeight() != image2->GetHeight())) {
		printf("ERROR: Size mismatch\n");
		}
	else {
		BOOL ok;
		ok = BitBlt(dst, 0, 0, image2->GetWidth(), image2->GetHeight(), src, 0, 0, SRCINVERT ); //SCRERASE also interesting

		Bitmap* image3 = new Bitmap(hImage2, NULL); //always returns inverted invoice.
		//Bitmap* image3 = new Bitmap(image2->GetWidth(),image2->GetHeight(),image2->GetPixelFormat());	image3->FromHBITMAP(hImage2, NULL); //always returns white
		//GetObject(dst, sizeof(image3), image3);

		//CLSID   encoderClsid;
		//GetEncoderClsid(L"image/png", &encoderClsid); //scans a list of all encoders to match the text name? Stupid.
		//const CLSID encoderClsid = CreateGUID("{557cf406-1a04-11d3-9a73-0000f81ef32e}"); //requires a template and atlbase.h
		//just get me the encoder for PNG?
		const CLSID encoderClsid = { 0x557cf406, 0x1a04, 0x11d3,{ 0x9a,0x73,0x00,0x00,0xf8,0x1e,0xf3,0x2e } };
		stat = image3->Save(L"test.png", &encoderClsid, NULL);
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

	//char * test = "E:\\Driver\\flantest\\coll91_96.png";
	//Image img1(L"E:\\Driver\\flantest\\coll91_96.png", false);
	//HBITMAP hImage1 = 0;
	//BITMAP bImage1;
	//img1.GetHBITMAP(Color::White, &hImage1);
	//GetObject(hImage1, sizeof(BITMAP), &bImage1);
	//HANDLE img1, img2; img1 = LoadImage(0, convertCharArrayToLPCWSTR(test), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
	//std::cout << "Width:" << bImage1.bmWidth << std::endl;
	
    return 0;
}


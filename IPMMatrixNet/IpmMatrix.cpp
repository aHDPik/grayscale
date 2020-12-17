#include "IpmMatrix.h"

#include <matrix_ipm.h>

using namespace System::Windows::Media::Imaging;
using namespace System::Windows::Media;
using namespace System::Collections::Generic;
using namespace System::Windows;

namespace MatrixIpm {

	WriteableBitmap^ IpmMatrix::Ipm(BitmapImage^ img, Matr m)
	{
		FormatConvertedBitmap^ bgr24 = gcnew FormatConvertedBitmap();

		// BitmapSource objects like FormatConvertedBitmap can only have their properties
		// changed within a BeginInit/EndInit block.
		bgr24->BeginInit();

		// Use the BitmapSource object defined above as the source for this new
		// BitmapSource (chain the BitmapSource objects together).
		bgr24->Source = img;

		// Set the new format to Gray32Float (grayscale).
		bgr24->DestinationFormat = PixelFormats::Bgr24;
		bgr24->EndInit();

		array<unsigned char>^ pixels = gcnew array<unsigned char>(img->PixelWidth * img->PixelHeight * 3);
		bgr24->CopyPixels(pixels, img->PixelWidth * 3, 0);
		pin_ptr<unsigned char> pixelsPin = &pixels[0];
		unsigned char* pixelsNative = pixelsPin;

		array<unsigned char>^ pixelsOut = gcnew array<unsigned char>(img->PixelWidth * img->PixelHeight * 3);
		pin_ptr<unsigned char> pixelsOutPin = &pixelsOut[0];
		unsigned char* pixelsOutNative = pixelsOutPin;

		matrixipm::Matr mNative;

		mNative.a = m.a;
		mNative.b = m.b;
		mNative.c = m.c;
		mNative.d = m.d;
		mNative.e = m.e;
		mNative.f = m.f;
		mNative.g = m.g;
		mNative.h = m.h;
		mNative.i = m.i;

		matrixipm::ipm(pixelsNative, pixelsOutNative, img->PixelWidth, img->PixelHeight, mNative);




		WriteableBitmap^ res = gcnew WriteableBitmap(img->PixelWidth, img->PixelHeight, 92, 92, PixelFormats::Bgr24, nullptr);
		res->WritePixels(System::Windows::Int32Rect(0, 0, img->PixelWidth, img->PixelHeight), pixelsOut, img->PixelWidth * 3, 0);

		return res;

	}

	WriteableBitmap^ IpmMatrix::Ipm4Points(BitmapImage^ img, List<Point>^ originalPoints, List<Point>^ modifiedPoints)
	{
		std::vector<matrixipm::ImagePoint> originalNativePoints, modifiedNativePoints;
		FormatConvertedBitmap^ bgr24 = gcnew FormatConvertedBitmap();

		// BitmapSource objects like FormatConvertedBitmap can only have their properties
		// changed within a BeginInit/EndInit block.
		bgr24->BeginInit();

		// Use the BitmapSource object defined above as the source for this new
		// BitmapSource (chain the BitmapSource objects together).
		bgr24->Source = img;

		// Set the new format to Gray32Float (grayscale).
		bgr24->DestinationFormat = PixelFormats::Bgr24;
		bgr24->EndInit();

		array<unsigned char>^ pixels = gcnew array<unsigned char>(img->PixelWidth * img->PixelHeight * 3);
		bgr24->CopyPixels(pixels, img->PixelWidth * 3, 0);
		pin_ptr<unsigned char> pixelsPin = &pixels[0];
		unsigned char* pixelsNative = pixelsPin;

		array<unsigned char>^ pixelsOut = gcnew array<unsigned char>(img->PixelWidth * img->PixelHeight * 3);
		pin_ptr<unsigned char> pixelsOutPin = &pixelsOut[0];
		unsigned char* pixelsOutNative = pixelsOutPin;

		for each (Point p in originalPoints)
			originalNativePoints.push_back({ p.X,p.Y });

		for each (Point p in modifiedPoints)
			modifiedNativePoints.push_back({ p.X,p.Y });

		matrixipm::ipm4Points(originalNativePoints, modifiedNativePoints, pixelsNative, pixelsOutNative, img->PixelWidth, img->PixelHeight);

		WriteableBitmap^ res = gcnew WriteableBitmap(img->PixelWidth, img->PixelHeight, 92, 92, PixelFormats::Bgr24, nullptr);
		res->WritePixels(System::Windows::Int32Rect(0, 0, img->PixelWidth, img->PixelHeight), pixelsOut, img->PixelWidth * 3, 0);

		return res;
	}

}

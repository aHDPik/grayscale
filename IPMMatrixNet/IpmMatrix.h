#pragma once
namespace MatrixIpm {

	public value struct Matr {
	public:
		double a;
		double b;
		double c;
		double d;
		double e;
		double f;
		double g;
		double h;
		double i;
	};

	public ref class IpmMatrix
	{
	public:
		static System::Windows::Media::Imaging::WriteableBitmap^ Ipm(System::Windows::Media::Imaging::BitmapImage^ img, Matr m);
		static System::Windows::Media::Imaging::WriteableBitmap^ Ipm4Points(System::Windows::Media::Imaging::BitmapImage^ img,
			System::Collections::Generic::List<System::Windows::Point>^ originalPoints, System::Collections::Generic::List<System::Windows::Point>^ modifiedPoints);
	};

}


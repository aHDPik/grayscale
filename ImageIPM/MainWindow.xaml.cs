using Microsoft.Win32;
using System;
using System.Collections.Generic;
using System.Globalization;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Data;
using System.Windows.Documents;
using System.Windows.Input;
using System.Windows.Media;
using System.Windows.Media.Imaging;
using System.Windows.Navigation;
using System.Windows.Shapes;

namespace ImageIPM
{
    /// <summary>
    /// Логика взаимодействия для MainWindow.xaml
    /// </summary>
    public partial class MainWindow : Window
    {
        private BitmapImage bitmap;
        private bool leftSelect = false;
        private bool rightSelect = false;
        private List<Point> realImgPoints = new List<Point>();
        private List<Point> realModifiedImgPoints = new List<Point>();

        public MainWindow()
        {
            InitializeComponent();
        }

        private void openMenu_Click(object sender, RoutedEventArgs e)
        {
            OpenFileDialog ofd = new OpenFileDialog();
            if (ofd.ShowDialog().Value)
            {
                bitmap = new BitmapImage(new Uri(ofd.FileName));
                MatrixIpm.Matr m = new MatrixIpm.Matr();
                m.a = double.Parse(aTb.Text, CultureInfo.InvariantCulture);
                m.b = double.Parse(bTb.Text, CultureInfo.InvariantCulture);
                m.c = double.Parse(cTb.Text, CultureInfo.InvariantCulture);
                m.d = double.Parse(dTb.Text, CultureInfo.InvariantCulture);
                m.e = double.Parse(eTb.Text, CultureInfo.InvariantCulture);
                m.f = double.Parse(fTb.Text, CultureInfo.InvariantCulture);
                m.g = double.Parse(gTb.Text, CultureInfo.InvariantCulture);
                m.h = double.Parse(hTb.Text, CultureInfo.InvariantCulture);
                m.i = double.Parse(iTb.Text, CultureInfo.InvariantCulture);
                WriteableBitmap res = MatrixIpm.IpmMatrix.Ipm(bitmap, m);
                img.Source = bitmap;
                modifiedImg.Source = res;
            }
        }

        private void open4PointsMenu_Click(object sender, RoutedEventArgs e)
        {
            OpenFileDialog ofd = new OpenFileDialog();
            if (ofd.ShowDialog().Value)
            {
                bitmap = new BitmapImage(new Uri(ofd.FileName));
                img.Source = bitmap;
                WriteableBitmap res = new WriteableBitmap(bitmap.PixelWidth, bitmap.PixelHeight, 92, 92, PixelFormats.Bgr24, null);
                modifiedImg.Source = res;
                MessageBox.Show("Выберите 4 точки на изначальной картинке");
                leftSelect = true;
            }
        }

        private void DrawAllPoints()
        {
            DrawPoints(imgCanvas, realImgPoints, img);
            DrawPoints(modifiedImgCanvas, realModifiedImgPoints, modifiedImg);
        }

        private void DrawPoints(Canvas canvas, List<Point> realPoints, Image drawImg)
        {
            canvas.Children.Clear();
            foreach (Point realP in realPoints)
            {
                Point imagePoint = new Point(realP.X / bitmap.PixelWidth * drawImg.ActualWidth, realP.Y / bitmap.PixelHeight * drawImg.ActualHeight);
                double shiftX = (canvas.ActualWidth - img.ActualWidth) / 2;
                double shiftY = (canvas.ActualHeight - img.ActualHeight) / 2;
                Point canvasPoint = new Point(imagePoint.X + shiftX, imagePoint.Y + shiftY);
                DrawCircle(canvas, canvasPoint);
            }
        }

        private void DrawCircle(Canvas canvas, Point center)
        {
            Ellipse ellipse = new Ellipse();
            ellipse.Width = 10;
            ellipse.Height = 10;
            ellipse.Fill = Brushes.Red;
            Canvas.SetLeft(ellipse, center.X - ellipse.Width / 2);
            Canvas.SetTop(ellipse, center.Y - ellipse.Height / 2);
            canvas.Children.Add(ellipse);
        }

        private void img_MouseLeftButtonUp(object sender, MouseButtonEventArgs e)
        {
            if (leftSelect)
            {
                Point p = Mouse.GetPosition(img);
                Point realP = new Point(p.X / img.ActualWidth * bitmap.PixelWidth, p.Y / img.ActualHeight * bitmap.PixelHeight);
                realImgPoints.Add(realP);
                DrawAllPoints();
                if (realImgPoints.Count == 4)
                {
                    leftSelect = false;
                    MessageBox.Show("Выберите 4 точки на результирующей картинке");
                    rightSelect = true;
                }
            }
        }

        private void modifiedImg_MouseLeftButtonUp(object sender, MouseButtonEventArgs e)
        {
            if (rightSelect)
            {
                Point p = Mouse.GetPosition(modifiedImg);
                Point realP = new Point(p.X / modifiedImg.ActualWidth * bitmap.PixelWidth, p.Y / modifiedImg.ActualHeight * bitmap.PixelHeight);
                realModifiedImgPoints.Add(realP);
                DrawAllPoints();
                if (realModifiedImgPoints.Count == 4)
                {
                    rightSelect = false;
                    WriteableBitmap res = MatrixIpm.IpmMatrix.Ipm4Points(bitmap, realImgPoints, realModifiedImgPoints);
                    modifiedImg.Source = res;
                }
            }
        }

        private void Window_SizeChanged(object sender, SizeChangedEventArgs e)
        {
            DrawAllPoints();
        }
    }
}

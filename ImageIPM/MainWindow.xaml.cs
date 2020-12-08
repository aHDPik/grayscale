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
    }
}

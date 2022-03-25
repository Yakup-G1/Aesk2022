using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using System.Windows.Media;
using LiveCharts;
using LiveCharts.Defaults;
using LiveCharts.Wpf;
using Brushes = System.Windows.Media.Brushes;

namespace Telemetry
{
    public partial class frmGraphic : Form
    {

        public static LineSeries Roll;
        public static LineSeries Pitch;
        public static LineSeries Yaw;
        public static LineSeries Altitude;

        public static Axis AxisX;
        public static Axis AxisY;


        public static ChartValues<float> RollValues;
        public static ChartValues<float> PitchValues;
        public static ChartValues<float> YawValues;
        public static ChartValues<float> AltitudeValues;

        #region .. Double Buffered function ..

        public static void SetDoubleBuffered(System.Windows.Forms.Control c)
        {
            if (System.Windows.Forms.SystemInformation.TerminalServerSession)
                return;
            System.Reflection.PropertyInfo aProp = typeof(System.Windows.Forms.Control).GetProperty("DoubleBuffered", System.Reflection.BindingFlags.NonPublic | System.Reflection.BindingFlags.Instance);
            aProp.SetValue(c, true, null);
        }
        #endregion

        #region .. code for Flucuring ..
        protected override CreateParams CreateParams
        {
            get
            {
                CreateParams cp = base.CreateParams;
                cp.ExStyle |= 0x02000000;
                return cp;
            }
        }

        #endregion

        public frmGraphic()
        {
            InitializeComponent();

            SetDoubleBuffered(cartesianChart1);

            Roll = new LineSeries();
            Pitch = new LineSeries();
            Yaw = new LineSeries();
            Altitude = new LineSeries();

            AxisX = new Axis();
            AxisY = new Axis();

            RollValues = new ChartValues<float>();
            PitchValues = new ChartValues<float>();
            YawValues = new ChartValues<float>();
            AltitudeValues = new ChartValues<float>();

            Roll.Title = "Roll";
            Roll.Values = RollValues;
            Roll.StrokeThickness = 3;
            Roll.StrokeDashArray = new System.Windows.Media.DoubleCollection(5);
            Roll.Stroke = new SolidColorBrush(System.Windows.Media.Color.FromRgb(255, 255, 255));
            Roll.Fill = null;
            Roll.LineSmoothness = 0.7;
            Roll.PointGeometrySize = 7;

            Pitch.Title = "Pitch";
            Pitch.Values = PitchValues;
            Pitch.StrokeThickness = 3;
            Pitch.StrokeDashArray = new System.Windows.Media.DoubleCollection(5);
            Pitch.Stroke = new SolidColorBrush(System.Windows.Media.Color.FromRgb(23, 34, 213));
            Pitch.Fill = null;
            Pitch.LineSmoothness = 0.7;
            Pitch.PointGeometrySize = 7;

            Yaw.Title = "Yaw";
            Yaw.Values = YawValues;
            Yaw.StrokeThickness = 3;
            Yaw.StrokeDashArray = new System.Windows.Media.DoubleCollection(5);
            Yaw.Stroke = new SolidColorBrush(System.Windows.Media.Color.FromRgb(13, 241, 43));
            Yaw.Fill = null;
            Yaw.LineSmoothness = 0.7;
            Yaw.PointGeometrySize = 7;

            Altitude.Title = "Altitude";
            Altitude.Values = AltitudeValues;
            Altitude.StrokeThickness = 3;
            Altitude.StrokeDashArray = new System.Windows.Media.DoubleCollection(5);
            Altitude.Stroke = new SolidColorBrush(System.Windows.Media.Color.FromRgb(242, 23, 45));
            Altitude.Fill = null;
            Altitude.LineSmoothness = 0.7;
            Altitude.PointGeometrySize = 7;

            AxisX.IsMerged = false;
            AxisX.Separator = (new Separator
            {
                StrokeThickness = 1,
                StrokeDashArray = new DoubleCollection(2),
                Stroke = new SolidColorBrush(System.Windows.Media.Color.FromRgb(222, 222, 222))
            });

            AxisY.IsMerged = false;
            AxisY.Separator = (new Separator
            {
                StrokeThickness = 1,
                StrokeDashArray = new DoubleCollection(2),
                Stroke = new SolidColorBrush(System.Windows.Media.Color.FromRgb(222, 222, 222))
            });


            cartesianChart1.Series.Add(Roll);
            cartesianChart1.Series.Add(Pitch);
            cartesianChart1.Series.Add(Yaw);
            cartesianChart1.Series.Add(Altitude);

            cartesianChart1.Background = new SolidColorBrush(System.Windows.Media.Color.FromRgb(46, 51, 73));

        }

        private void frmGraphic_Load(object sender, EventArgs e)
        {

        }

        public static void PlotGraphics()
        {

            RollValues.Add(RecieveData.roll);
            PitchValues.Add(RecieveData.pitch);
            YawValues.Add(RecieveData.yaw);
            AltitudeValues.Add(RecieveData.altitude);

            if (RollValues.Count > 30)
                RollValues.RemoveAt(0);

            if (PitchValues.Count > 30)
                PitchValues.RemoveAt(0);

            if (YawValues.Count > 30)
                YawValues.RemoveAt(0);

            if (AltitudeValues.Count > 30)
                AltitudeValues.RemoveAt(0);
        }
    }
}

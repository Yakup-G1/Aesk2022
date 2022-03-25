using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using System.Threading;
using ZedGraph;


namespace Telemetry
{
    public partial class frmGraphics : Form
    {

        public static int SystemStart;

        public static bool scrolling = true;

        public static GraphPane RollPane = new GraphPane();
        LineItem RollLine;
        LineItem RollErrorLine;
        public static RollingPointPairList listPointsRoll = new RollingPointPairList(6000);
        public static RollingPointPairList listPointsRollError = new RollingPointPairList(6000);


        public static GraphPane PitchPane = new GraphPane();
        LineItem PitchLine;
        LineItem PitchErrorLine;
        public static RollingPointPairList listPointsPitch = new RollingPointPairList(6000);
        public static RollingPointPairList listPointsPitchError = new RollingPointPairList(6000);


        public static GraphPane YawPane = new GraphPane();
        LineItem YawLine;
        LineItem YawErrorLine;
        public static RollingPointPairList listPointsYaw = new RollingPointPairList(6000);
        public static RollingPointPairList listPointsYawError = new RollingPointPairList(6000);


        public static GraphPane AltitudePane = new GraphPane();
        LineItem AltitudeLine;
        LineItem AltitudeErrorLine;
        public static RollingPointPairList listPointsAltitude = new RollingPointPairList(6000);
        public static RollingPointPairList listPointsAltitudeError= new RollingPointPairList(6000);

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

        public frmGraphics()
        {
            InitializeComponent();

            UITools.Graphics.zedGraphControl1 = zedGraphControl1;
            UITools.Graphics.zedGraphControl2 = zedGraphControl2;
            UITools.Graphics.zedGraphControl3 = zedGraphControl3;
            UITools.Graphics.zedGraphControl4 = zedGraphControl4;

            SetDoubleBuffered(zedGraphControl1);
            SetDoubleBuffered(zedGraphControl2);
            SetDoubleBuffered(zedGraphControl3);
            SetDoubleBuffered(zedGraphControl4);
            SetDoubleBuffered(tableLayoutPanel1);
            SetDoubleBuffered(tableLayoutPanel2);
            SetDoubleBuffered(tableLayoutPanel3);

            GraphsInit();

        }

        private void frmGraphics_Load(object sender, EventArgs e)
        {

        }
        private void GraphsInit()
        {

            zedGraphControl1.Size = new Size(600, 283);
            zedGraphControl2.Size = new Size(600, 283);
            zedGraphControl3.Size = new Size(600, 283);
            zedGraphControl4.Size = new Size(600, 283);

            SystemStart = Environment.TickCount;  // bilgisayarını açtığın andan bu yana geçen zaman

            //                  *** Roll ***                //

            RollPane = zedGraphControl1.GraphPane;
            RollPane.Title.Text = "Roll Graphic";
            RollPane.XAxis.Title.Text = "Seconds";
            RollPane.YAxis.Title.Text = "Degree";
            RollPane.XAxis.Scale.Min = 0;
            RollPane.XAxis.Scale.Max = 10;
            RollPane.YAxis.Scale.Min = -20;
            RollPane.YAxis.Scale.Max = 20;

            RollLine = RollPane.AddCurve("Roll_Angle", listPointsRoll, Color.Blue, SymbolType.None);
            RollErrorLine = RollPane.AddCurve("Roll Error", listPointsRollError, Color.Red, SymbolType.None);
            RollLine.Line.Width = 3;
            RollErrorLine.Line.Width = 3;

            RollPane.Chart.Fill.Color = System.Drawing.Color.FromArgb(46, 51, 73);
            RollPane.Fill.Color = System.Drawing.Color.FromArgb(46, 51, 73);
            RollPane.Chart.Border.Color = Color.White;
            RollPane.Border.IsVisible = false;
            RollPane.Title.FontSpec.Family = "Eras Bold ITC";
            RollPane.Title.FontSpec.Size = 23;
            RollPane.Title.FontSpec.IsBold = false;
            RollPane.Title.FontSpec.FontColor = Color.White;
            RollPane.XAxis.Title.FontSpec.Family = "Eras Bold ITC";
            RollPane.YAxis.Title.FontSpec.Family = "Eras Bold ITC";
            RollPane.XAxis.Title.FontSpec.FontColor = Color.White;
            RollPane.YAxis.Title.FontSpec.FontColor = Color.White;
            RollPane.XAxis.Scale.FontSpec.FontColor = Color.White;
            RollPane.YAxis.Scale.FontSpec.FontColor = Color.White;
            RollPane.XAxis.MajorGrid.IsVisible = true;

            //                  ***Pitch * **                //

            PitchPane = zedGraphControl2.GraphPane;
            PitchPane.Title.Text = "Pitch Graphic";
            PitchPane.XAxis.Title.Text = "Seconds";
            PitchPane.YAxis.Title.Text = "Degree";
            PitchPane.XAxis.Scale.Min = 0;
            PitchPane.XAxis.Scale.Max = 10;
            PitchPane.YAxis.Scale.Min = -20;
            PitchPane.YAxis.Scale.Max = 20;

            PitchLine = PitchPane.AddCurve("Pitch Angle", listPointsPitch, Color.Blue, SymbolType.None);
            PitchErrorLine = PitchPane.AddCurve("Pitch Error", listPointsPitchError, Color.Red, SymbolType.None);
            PitchLine.Line.Width = 3;
            PitchErrorLine.Line.Width = 3;

            PitchPane.Chart.Fill.Color = System.Drawing.Color.FromArgb(46, 51, 73);
            PitchPane.Fill.Color = System.Drawing.Color.FromArgb(46, 51, 73);
            PitchPane.Chart.Border.Color = Color.White;
            PitchPane.Border.IsVisible = false;
            PitchPane.Title.FontSpec.Family = "Eras Bold ITC";
            PitchPane.Title.FontSpec.Size = 23;
            PitchPane.Title.FontSpec.IsBold = false;
            PitchPane.Title.FontSpec.FontColor = Color.White;
            PitchPane.XAxis.Title.FontSpec.Family = "Eras Bold ITC";
            PitchPane.YAxis.Title.FontSpec.Family = "Eras Bold ITC";
            PitchPane.XAxis.Title.FontSpec.FontColor = Color.White;
            PitchPane.YAxis.Title.FontSpec.FontColor = Color.White;
            PitchPane.XAxis.Scale.FontSpec.FontColor = Color.White;
            PitchPane.YAxis.Scale.FontSpec.FontColor = Color.White;
            PitchPane.XAxis.MajorGrid.IsVisible = true;

            //                  *** Yaw ***                //

            YawPane = zedGraphControl3.GraphPane;
            YawPane.Title.Text = "Yaw Graphic";
            YawPane.XAxis.Title.Text = "Seconds";
            YawPane.YAxis.Title.Text = "Degree";
            YawPane.XAxis.Scale.Min = 0;
            YawPane.XAxis.Scale.Max = 10;
            YawPane.YAxis.Scale.Min = -20;
            YawPane.YAxis.Scale.Max = 20;

            YawLine = YawPane.AddCurve("Yaw_Angle", listPointsYaw, Color.Blue, SymbolType.None);
            YawErrorLine = YawPane.AddCurve("Yaw Error", listPointsYawError, Color.Red, SymbolType.None);
            YawLine.Line.Width = 3;
            YawErrorLine.Line.Width = 3;

            YawPane.Chart.Fill.Color = System.Drawing.Color.FromArgb(46, 51, 73);
            YawPane.Fill.Color = System.Drawing.Color.FromArgb(46, 51, 73);
            YawPane.Chart.Border.Color = Color.White;
            YawPane.Border.IsVisible = false;
            YawPane.Title.FontSpec.Family = "Eras Bold ITC";
            YawPane.Title.FontSpec.Size = 23;
            YawPane.Title.FontSpec.IsBold = false;
            YawPane.Title.FontSpec.FontColor = Color.White;
            YawPane.XAxis.Title.FontSpec.Family = "Eras Bold ITC";
            YawPane.YAxis.Title.FontSpec.Family = "Eras Bold ITC";
            YawPane.XAxis.Title.FontSpec.FontColor = Color.White;
            YawPane.YAxis.Title.FontSpec.FontColor = Color.White;
            YawPane.XAxis.Scale.FontSpec.FontColor = Color.White;
            YawPane.YAxis.Scale.FontSpec.FontColor = Color.White;
            YawPane.XAxis.MajorGrid.IsVisible = true;

            //                  *** Altitude ***                //

            AltitudePane = zedGraphControl4.GraphPane;
            AltitudePane.Title.Text = "Altitude Graphic";
            AltitudePane.XAxis.Title.Text = "Seconds";
            AltitudePane.YAxis.Title.Text = "Altitude (M)";
            AltitudePane.XAxis.Scale.Min = 0;
            AltitudePane.XAxis.Scale.Max = 10;
            AltitudePane.YAxis.Scale.Min = -10;
            AltitudePane.YAxis.Scale.Max = 10;

            AltitudeLine = AltitudePane.AddCurve("Altitude", listPointsAltitude, Color.Blue, SymbolType.None);
            AltitudeErrorLine = AltitudePane.AddCurve("Altitude Error", listPointsAltitudeError, Color.Red, SymbolType.None);
            AltitudeLine.Line.Width = 3;
            AltitudeErrorLine.Line.Width = 3;

            AltitudePane.Chart.Fill.Color = System.Drawing.Color.FromArgb(46, 51, 73);
            AltitudePane.Fill.Color = System.Drawing.Color.FromArgb(46, 51, 73);
            AltitudePane.Chart.Border.Color = Color.White;
            AltitudePane.Border.IsVisible = false;
            AltitudePane.Title.FontSpec.Family = "Eras Bold ITC";
            AltitudePane.Title.FontSpec.Size = 23;
            AltitudePane.Title.FontSpec.IsBold = false;
            AltitudePane.Title.FontSpec.FontColor = Color.White;
            AltitudePane.XAxis.Title.FontSpec.Family = "Eras Bold ITC";
            AltitudePane.YAxis.Title.FontSpec.Family = "Eras Bold ITC";
            AltitudePane.XAxis.Title.FontSpec.FontColor = Color.White;
            AltitudePane.YAxis.Title.FontSpec.FontColor = Color.White;
            AltitudePane.XAxis.Scale.FontSpec.FontColor = Color.White;
            AltitudePane.YAxis.Scale.FontSpec.FontColor = Color.White;
            AltitudePane.XAxis.MajorGrid.IsVisible = true;
        }
        
        public static void Draw_Grapichs(ZedGraphControl zedGraphControl1, ZedGraphControl zedGraphControl2, ZedGraphControl zedGraphControl3,ZedGraphControl zedGraphControl4)
        {
            try
            {
                if (scrolling)
                {
                    double time = (Environment.TickCount - SystemStart) / 1000.0;

                    Scale xScale1 = zedGraphControl1.GraphPane.XAxis.Scale;
                    Scale xScale2 = zedGraphControl2.GraphPane.XAxis.Scale;
                    Scale xScale3 = zedGraphControl3.GraphPane.XAxis.Scale;
                    Scale xScale4 = zedGraphControl4.GraphPane.XAxis.Scale;

                    if (time > xScale1.Max - xScale1.MajorStep)
                    {
                        xScale1.Max = time + xScale1.MajorStep;
                        xScale1.Min = xScale1.Max - 10;
                    }
                    if (time > xScale2.Max - xScale2.MajorStep)
                    {
                        xScale2.Max = time + xScale2.MajorStep;
                        xScale2.Min = xScale2.Max - 10;
                    }
                    if (time > xScale3.Max - xScale3.MajorStep)
                    {
                        xScale3.Max = time + xScale3.MajorStep;
                        xScale3.Min = xScale3.Max - 10;
                    }
                    if (time > xScale4.Max - xScale4.MajorStep)
                    {
                        xScale4.Max = time + xScale4.MajorStep;
                        xScale4.Min = xScale4.Max - 10;
                    }

                    listPointsRoll.Add(new PointPair(time, Convert.ToDouble(RecieveData.roll)));
                    listPointsRollError.Add(new PointPair(time, Convert.ToDouble(RecieveData.rollError)));

                    listPointsPitch.Add(new PointPair(time, Convert.ToDouble(RecieveData.pitch)));
                    listPointsPitchError.Add(new PointPair(time, Convert.ToDouble(RecieveData.pitchError)));

                    listPointsYaw.Add(new PointPair(time, Convert.ToDouble(RecieveData.yaw)));
                    listPointsYawError.Add(new PointPair(time, Convert.ToDouble(RecieveData.yawError)));

                    listPointsAltitude.Add(new PointPair(time, Convert.ToDouble(RecieveData.altitude)));
                    listPointsAltitudeError.Add(new PointPair(time, Convert.ToDouble(RecieveData.altitudeError)));

                    RollPane.XAxis.Scale.Max = time;
                    zedGraphControl1.Refresh();
                    RollPane.AxisChange();

                    PitchPane.XAxis.Scale.Max = time;
                    zedGraphControl2.Refresh();
                    PitchPane.AxisChange();

                    YawPane.XAxis.Scale.Max = time;
                    zedGraphControl3.Refresh();
                    YawPane.AxisChange();

                    AltitudePane.XAxis.Scale.Max = time;
                    zedGraphControl4.Refresh();
                    AltitudePane.AxisChange();
                }
                else
                {
                    ; ;
                }
            }
            catch (Exception)
            {
                ; ;
            }
        }

        private void btnScroll_Click_1(object sender, EventArgs e)
        {
            if (scrolling)
            {
                scrolling = false;
                btnScroll.Image = Image.FromFile(@"D:\Fork\aesk-iha-2022\Uav_Telemetry_System\Telemetry\png\play.png");
            }
            else
            {
                btnScroll.Image = Image.FromFile(@"D:\Fork\aesk-iha-2022\Uav_Telemetry_System\Telemetry\png\stop.png");
                scrolling = true;
            }
        }

        private void frmGraphics_Leave(object sender, EventArgs e)
        {
            //scrolling = false;
        }

        private void frmGraphics_Enter(object sender, EventArgs e)
        {
            zedGraphControl2.Visible = true;
            zedGraphControl3.Visible = true;
            zedGraphControl1.Visible = true;
            zedGraphControl4.Visible = true;

            zedGraphControl1.Size = new Size(600, 283);
            zedGraphControl2.Size = new Size(600, 283);
            zedGraphControl3.Size = new Size(600, 283);
            zedGraphControl4.Size = new Size(600, 283);

            //scrolling = true;
        }

        private void btnZoomRollGraph_Click(object sender, EventArgs e)
        {
            zedGraphControl2.Visible = false;
            zedGraphControl3.Visible = false;
            zedGraphControl4.Visible = false;

            zedGraphControl1.Visible = true;
            zedGraphControl1.Size = new Size(1100, 500);
        }

        private void btnZoomYawGraph_Click(object sender, EventArgs e)
        {
            zedGraphControl2.Visible = false;
            zedGraphControl1.Visible = false;
            zedGraphControl4.Visible = false;

            zedGraphControl3.Visible = true;
            zedGraphControl3.Size = new Size(1100, 500);
        }

        private void btnZoomAltitudeGraph_Click(object sender, EventArgs e)
        {
            zedGraphControl2.Visible = false;
            zedGraphControl3.Visible = false;
            zedGraphControl1.Visible = false;

            zedGraphControl4.Visible = true;
            zedGraphControl4.Size = new Size(1100, 500);
        }

        private void btnZoomPitchGraph_Click(object sender, EventArgs e)
        {
            zedGraphControl3.Visible = false;
            zedGraphControl1.Visible = false;
            zedGraphControl4.Visible = false;

            zedGraphControl2.Visible = true;
            zedGraphControl2.Size = new Size(1100, 500);
        }

        private void ZoomOut_Click(object sender, EventArgs e)
        {
            zedGraphControl2.Visible = true;
            zedGraphControl3.Visible = true;
            zedGraphControl1.Visible = true;
            zedGraphControl4.Visible = true;

            zedGraphControl1.Size = new Size(600, 283);
            zedGraphControl2.Size = new Size(600, 283);
            zedGraphControl3.Size = new Size(600, 283);
            zedGraphControl4.Size = new Size(600, 283);

            RollPane.YAxis.Scale.Min = -20;
            RollPane.YAxis.Scale.Max = 20;
            PitchPane.YAxis.Scale.Min = -20;
            PitchPane.YAxis.Scale.Max = 20;
            YawPane.YAxis.Scale.Min = -20;
            YawPane.YAxis.Scale.Max = 20;
            AltitudePane.YAxis.Scale.Min = -10;
            AltitudePane.YAxis.Scale.Max = 10;
        }
    }
}

using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using GMap.NET;
using GMap.NET.MapProviders;
using GMap.NET.WindowsForms;
using System.Threading;
using GMap.NET.WindowsForms.Markers;
using System.IO;
using System.IO.Ports;

namespace Telemetry
{
    public partial class frmHome : Form
    {

        public static List<PointLatLng> _inComingLatLng;
        public static List<PointLatLng> _inComingLatLng_son;
        public static List<double> _inComingLatLngBuffer;

        public static GMapRoute routeLayer;
        public static GMapOverlay routeOverlay;
        public static  List<PointLatLng> waypointsBuffer;

        //public static GMapOverlay routersOverlay_Upp;
        //public static GMapOverlay markers_upp = new GMapOverlay("markers");
        //public static GMapRoute line_layer_Upp;

        public static UInt16 index = 0;

        public static bool homeActivatedFlag;
        public static bool GPS_Counter_Tick;

        public frmHome()
        {
            InitializeComponent();

            SetDoubleBuffered(ActualPositionMap);

            _inComingLatLng = new List<PointLatLng>();
            _inComingLatLngBuffer = new List<double>();
            _inComingLatLng_son = new List<PointLatLng>();
            waypointsBuffer = new List<PointLatLng>();

            UITools.Home.pictureBox1 = pictureBox1;
            UITools.Home.ActualPositionMap = ActualPositionMap;

            ActualPositionMap.Controls.Add(pictureBox1);
            pictureBox1.Location = new Point(733, 253);
            pictureBox1.BackColor = Color.Transparent;

            SetDoubleBuffered(pictureBox1);

        }

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

        private void frmHome_Load(object sender, EventArgs e)
        {
            ActualPositionMap.DragButton = MouseButtons.Right;
            ActualPositionMap.MapProvider = GMapProviders.BingSatelliteMap;
            double lat = 41.025879;
            double lng = 28.889451;
            ActualPositionMap.Position = new PointLatLng(lat, lng);
            ActualPositionMap.MinZoom = 5;
            ActualPositionMap.MaxZoom = 100;
            ActualPositionMap.Zoom = 10;

            ActualPositionMap.ShowCenter = false;

            homeActivatedFlag = true;
        }
        
        public static void gpsUpdateLocation()
        {
            if (RecieveData.latitude > 33 && RecieveData.latitude < 48 && GPS_Counter_Tick)
            {
                GPS_Counter_Tick = false;

                UITools.Home.ActualPositionMap.Position = new GMap.NET.PointLatLng(RecieveData.latitude, RecieveData.longitude);
                waypointsBuffer.Add(new PointLatLng(RecieveData.latitude, RecieveData.longitude));

                //routeLayer = new GMapRoute(waypointsBuffer, "Route Layer");
                //routeLayer.Stroke = new Pen(Brushes.AliceBlue, 3);
                //routeOverlay = new GMapOverlay("Route Overlay");
                //routeOverlay.Routes.Add(routeLayer);
                //UITools.Home.ActualPositionMap.Overlays.Add(routeOverlay);
                //UITools.Home.ActualPositionMap.UpdateRouteLocalPosition(routeLayer);
            }
        }

        private void frmHome_Enter(object sender, EventArgs e)
        {
            homeActivatedFlag = true;
        }

        private void frmHome_Leave(object sender, EventArgs e)
        {
            homeActivatedFlag = false;
        }

        private void GPS_Timer_Tick(object sender, EventArgs e)
        {
            GPS_Counter_Tick = true;
        }
    }
}

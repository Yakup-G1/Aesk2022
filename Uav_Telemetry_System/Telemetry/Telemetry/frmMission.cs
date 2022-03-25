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
using GMap.NET.WindowsForms.Markers;

namespace Telemetry
{
    public partial class frmMission : Form
    {

        GMapRoute routeLayer;     
        GMapOverlay routeOverlay;

        GMapOverlay markers = new GMapOverlay("markers");

        private List<PointLatLng> waypointsBuffer;      // Buffer noktalarının lat-long'ları bu listede tutulur.
        private List<PointLatLng> mainRoutePoints;      // Mouse'dan tıklanılan noktaların lat-long'ları bu listede tutulur.
        private List<double> mainLatPoints;             // Mouse'dan tıklanılan noktaların latitude'ları bu listede tutulur.
        private List<double> mainLngPoints;             // Mouse'dan tıklanılan noktaların longitude'ları bu listede tutulur.

        private List<double> latList;                   // Drone'a gönderilecek olan Latitude Buffer'ı
        private List<double> lngList;                   // Drone'a gönderilecek olan Longitude Buffer'ı


        double gpsCoefficient = 0.00001;    // latitude-longitude cinsinden, hemen hemen 1 metreye denk geliyor. Gerek olursa input olarak alınabilir.
        public static int index = 0;
        int indexForBrush = 0;
        int refIndex;

        int distance = 0;
        int totalDistance = 0;              // Toplam rota uzunluğunu metre cinsinden tutacağımız değişken.

        public static byte[] GPS_Buffer = new byte[256];

        public static ushort crc16_dataTx;
        public static ushort crc16_dataRx;
        public static bool GPS_Com_Flag = false;

        void BrushRoute(byte mode)
        {
            int i;

            refIndex = indexForBrush;

            if (mode == 'G')
            {

                if (indexForBrush != 0)         // Rota oluşturmak için en az 2 nokta gerekli olduğundan dolayı
                {

                    double latDifference = mainLatPoints[mainLatPoints.Count - 1] - latList[latList.Count - 1]; // son seçilen 2 nokta arasındaki latitude hatası
                    double lngDifference = mainLngPoints[mainLngPoints.Count - 1] - lngList[lngList.Count - 1]; // son seçilen 2 nokta arasındaki longitude hatası

                    Int32 latDifferenceInMeters = Convert.ToInt32(latDifference * 100000);  // Sadece uzaklığı hesaplama için kullanılacak
                    Int32 lngDifferenceInMeters = Convert.ToInt32(lngDifference * 100000);  // Sadece uzaklığı hesaplama için kullanılacak

                    distance = (int)(Math.Sqrt((Math.Pow(latDifferenceInMeters, 2) + Math.Pow(lngDifferenceInMeters, 2)))); // Stoke's teoremine Diverjans teoremini uygulayınca distance verisi çıkıyor
                    totalDistance += distance;
                    lblDistance.Text = Convert.ToString(totalDistance) + " Meters";

                    latList.Add(mainLatPoints[mainLatPoints.Count - 1]);
                    lngList.Add(mainLngPoints[mainLngPoints.Count - 1]);
                    indexForBrush++;
                }
                else     // İlk nokta ise sadece tıklanılan nokta buffer'a alınıyor
                {
                    latList.Add(mainLatPoints[mainLatPoints.Count - 1]);
                    lngList.Add(mainLngPoints[mainLngPoints.Count - 1]);
                    indexForBrush++;
                }

            }
            else if(mode == 'C')
            {

                if (Convert.ToInt16(txtRadius.Text) < 0 || Convert.ToInt16(txtRadius.Text) > 20)    // Yarıçapı makul seviyede tutmak için
                {
                    txtRadius.Text = "6";
                    MessageBox.Show("RADIUS CANNOT BE 0 OR BIGGER THAN 20 METERS");
                }

                if (indexForBrush != 0)     // Seçilen ilk nokta ise patlamamak için
                {
                    int k;

                    double latDifference = (mainLatPoints[mainLatPoints.Count - 1] - gpsCoefficient * Convert.ToInt16(txtRadius.Text)) - mainLatPoints[mainLatPoints.Count - 2];  // error hesaplanıyor
                    double lngDifference = mainLngPoints[mainLngPoints.Count - 1] - mainLngPoints[mainLngPoints.Count - 2];

                    Int32 latDifferenceInMeters = Convert.ToInt32(latDifference * 100000);  // Sadece uzaklığı hesaplama için
                    Int32 lngDifferenceInMeters = Convert.ToInt32(lngDifference * 100000);  // Sadece uzaklığı hesaplama için
                    distance = (int)(Math.Sqrt((Math.Pow(latDifferenceInMeters, 2) + Math.Pow(lngDifferenceInMeters, 2))));  // schrödingerin denklemleri uygulanıyor
                    totalDistance += distance;
                    lblDistance.Text = Convert.ToString(totalDistance) + " Meters";

                    for (k = 0; k < distance; k++)
                    {
                        latList.Add(mainLatPoints[mainLatPoints.Count - 2] + (k + 1) * (latDifference / distance));
                        lngList.Add(mainLngPoints[mainLngPoints.Count - 2] + (k + 1) * (lngDifference / distance));
                        indexForBrush++;
                    }

                }


                latList.Add(mainLatPoints[mainLatPoints.Count - 1] - gpsCoefficient * Convert.ToInt16(txtRadius.Text));
                lngList.Add(mainLngPoints[mainLngPoints.Count - 1]);

                indexForBrush++;

                // Alt taraftaki seri, for döngüleri ile sekizgen biçiminde buffer oluşturuluyor
                for (i = 0; i < Convert.ToInt16(txtRadius.Text) / 2; i++)
                {
                    latList.Add(latList[indexForBrush - 1]);
                    lngList.Add(lngList[indexForBrush - 1] - gpsCoefficient);
                    indexForBrush++;
                }
                for (i = 0; i < Convert.ToInt16(txtRadius.Text) / 2; i++)
                {
                    latList.Add(latList[indexForBrush - 1] + gpsCoefficient);
                    lngList.Add(lngList[indexForBrush - 1] - gpsCoefficient);
                    indexForBrush++;
                }
                for (i = 0; i < Convert.ToInt16(txtRadius.Text); i++)
                {
                    latList.Add(latList[indexForBrush - 1] + gpsCoefficient);
                    lngList.Add(lngList[indexForBrush - 1]);
                    indexForBrush++;
                }
                for (i = 0; i < Convert.ToInt16(txtRadius.Text) / 2; i++)
                {
                    latList.Add(latList[indexForBrush - 1] + gpsCoefficient);
                    lngList.Add(lngList[indexForBrush - 1] + gpsCoefficient);
                    indexForBrush++;
                }
                for (i = 0; i < Convert.ToInt16(txtRadius.Text); i++)
                {
                    latList.Add(latList[indexForBrush - 1]);
                    lngList.Add(lngList[indexForBrush - 1] + gpsCoefficient);
                    indexForBrush++;
                }
                for (i = 0; i < Convert.ToInt16(txtRadius.Text) / 2; i++)
                {
                    latList.Add(latList[indexForBrush - 1] - gpsCoefficient);
                    lngList.Add(lngList[indexForBrush - 1] + gpsCoefficient);
                    indexForBrush++;
                }
                for (i = 0; i < Convert.ToInt16(txtRadius.Text); i++)
                {
                    latList.Add(latList[indexForBrush - 1] - gpsCoefficient);
                    lngList.Add(lngList[indexForBrush - 1]);
                    indexForBrush++;
                }
                for (i = 0; i < Convert.ToInt16(txtRadius.Text) / 2; i++)
                {
                    latList.Add(latList[indexForBrush - 1] - gpsCoefficient);
                    lngList.Add(lngList[indexForBrush - 1] - gpsCoefficient);
                    indexForBrush++;
                }
                for (i = 0; i < Convert.ToInt16(txtRadius.Text) / 2; i++)
                {
                    latList.Add(latList[indexForBrush - 1]);
                    lngList.Add(lngList[indexForBrush - 1] - gpsCoefficient);
                    indexForBrush++;
                }

            }

            for (int j = refIndex; j < indexForBrush; j++)      //Waypoints list'ine atanıyor.
            {
                waypointsBuffer.Add(new PointLatLng(latList[j], lngList[j]));
            }

            listBox1.Items.Add(mainRoutePoints.Count-1 + ". Point :");
            listBox1.Items.Add(mainLatPoints[mainRoutePoints.Count - 1]);
            listBox1.Items.Add(mainLngPoints[mainRoutePoints.Count - 1]);
            

            routeLayer = new GMapRoute(waypointsBuffer, "Route Layer");         // Rota çizdiriliyor.
            routeLayer.Stroke = new Pen(Brushes.Aqua, 3);
            routeOverlay = new GMapOverlay("Route Overlay");
            routeOverlay.Routes.Add(routeLayer);
            MissionMap.Overlays.Add(routeOverlay);
            MissionMap.UpdateRouteLocalPosition(routeLayer);
        }


        public frmMission()
        {
            InitializeComponent();

            waypointsBuffer = new List<PointLatLng>();
            mainRoutePoints = new List<PointLatLng>();
            mainLatPoints = new List<double>();         
            mainLngPoints = new List<double>();
            latList = new List<double>();
            lngList = new List<double>();

            SetDoubleBuffered(MissionMap);
            SetDoubleBuffered(btnCircle);
            SetDoubleBuffered(btnStabilize);
            SetDoubleBuffered(btnGoAhead);
            SetDoubleBuffered(btnGetRoute);
            SetDoubleBuffered(tableLayoutPanel1);
            SetDoubleBuffered(tableLayoutPanel2);
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

        private void frmMission_Load(object sender, EventArgs e)
        {
            MissionMap.DragButton = MouseButtons.Right;                 // Sürüklemek için sağ tık kullanılsın diyoruz
            MissionMap.MapProvider = GMapProviders.BingSatelliteMap;
            double lat = 41.025879;
            double lng = 28.889451;
            MissionMap.Position = new PointLatLng(lat, lng);            // Başlangıç koordinatlarını belirliyoruz
            MissionMap.MinZoom = 5;
            MissionMap.MaxZoom = 100;
            MissionMap.Zoom = 17;

            MissionMap.Zoom += 0.0001;                                  // Böyle yapınca harita güncelleniyor
            MissionMap.Zoom -= 0.0001;                                  // geri düzeltiyoruz

            MissionMap.ShowCenter = false;

            GPS_Buffer[0] = (byte)'G';                                  //ASCI 71

            index = 2;

        }

        private void MissionMap_MouseClick(object sender, MouseEventArgs e)
        {
            if (e.Button == MouseButtons.Left )                     // Sol tık ile nokta koyacağız
            {
                var point = MissionMap.FromLocalToLatLng(e.X, e.Y);

                double lat = point.Lat;                 
                double lng = point.Lng;

                mainRoutePoints.Add(new PointLatLng(lat, lng));     // Tıklanılan noktaların enlem boylam verisi bu listede

                mainLatPoints.Add(Convert.ToDouble(lat));
                mainLngPoints.Add(Convert.ToDouble(lng));

                if (btnGoAhead.Checked == true)
                {
                    AddMarker(point, GMarkerGoogleType.blue);

                    GPS_Buffer[index++] = (byte)'G';                                        // Header = G
                    GPS_Buffer[index++] = (byte)'A';                                        // Header = A

                }
                else if (btnCircle.Checked == true)
                {
                    AddMarker(point, GMarkerGoogleType.yellow);

                    GPS_Buffer[index++] = (byte)'C';                                        // Header = C
                    GPS_Buffer[index++] = Convert.ToByte(Convert.ToInt16(txtRadius.Text));  // Radius

                }

                BrushRoute(GPS_Buffer[index-2]);

                byte[] latBufferBytes = new byte[4];
                byte[] lngBufferBytes = new byte[4];

                latBufferBytes = BitConverter.GetBytes((Int32)(mainLatPoints[mainLatPoints.Count-1] * 1000000));
                lngBufferBytes = BitConverter.GetBytes((Int32)(mainLngPoints[mainLngPoints.Count - 1] * 1000000));

                latBufferBytes.CopyTo(GPS_Buffer, index);
                lngBufferBytes.CopyTo(GPS_Buffer, index += 4);

                index += 4;

                MissionMap.Zoom += 0.0001;
                MissionMap.Zoom -= 0.0001;

            }
        }

        private void AddMarker(PointLatLng pointToAdd, GMarkerGoogleType markerType)
        {
            GMapOverlay markers = new GMapOverlay("markers");
            GMarkerGoogle marker = new GMarkerGoogle(pointToAdd, markerType);
            markers.Markers.Add(marker);
            MissionMap.Overlays.Add(markers);
        }

        private void txtRadius_KeyPress(object sender, KeyPressEventArgs e)     // yarıçap yerine harf vs girilmesini önlemek için
        {
            if (!char.IsControl(e.KeyChar) && !char.IsDigit(e.KeyChar) && e.KeyChar != ',')
            {
                e.Handled = true;
            }
        }

        private void btnClear_Click(object sender, EventArgs e)
        {
            waypointsBuffer.Clear();
            mainRoutePoints.Clear();
            mainLatPoints.Clear();
            mainLngPoints.Clear();
            latList.Clear();
            lngList.Clear();
            for (int k = 2; k < 256; k++)
            {
                GPS_Buffer[k] = 0;
            }
            index = 2;
            indexForBrush = 0;
            totalDistance = 0;
            lblDistance.Text = Convert.ToString(totalDistance) + " Meters";
            listBox1.Items.Clear();

            if (routeOverlay != null)
            {
                routeOverlay.Routes.Clear();
                markers.Markers.Clear();
                MissionMap.Overlays.Clear();
            }

            MissionMap.Refresh();
        }

        private void btnUndo_Click(object sender, EventArgs e)      
        {
            //waypointsBuffer.RemoveAt(waypointsBuffer.Count - 1);

            //mainRoutePoints.RemoveAt(mainRoutePoints.Count - 1);
            //mainLatPoints.RemoveAt(mainLatPoints.Count - 1);
            //mainLngPoints.RemoveAt(mainLngPoints.Count - 1);
            //index--;
            //totalDistance -= distance;
            //lblDistance.Text = Convert.ToString(totalDistance) + " Meters";

            MessageBox.Show("biz çizdiğimiz rotadan şaşmayız");

            //for (int i = index; i >= refIndex; i--)
            //{
            //    latList.RemoveAt(i);
            //    lngList.RemoveAt(i);
            //}

            //if (routeOverlay != null)
            //{
            //    routeOverlay.Routes.Clear();
            //    markers.Markers.Clear();
            //    MissionMap.Overlays.Clear();
            //}

            //for (int i = 0; i < latList.Count; i++)
            //{
            //    AddMarker(mainRoutePoints[i], GMarkerGoogleType.blue);
            //}

            //routeLayer = new GMapRoute(waypointsBuffer, "Route Layer");     // Rota çizdiriyoruz
            //routeLayer.Stroke = new Pen(Brushes.Aqua, 3);
            //routeOverlay = new GMapOverlay("Route Overlay");
            //routeOverlay.Routes.Add(routeLayer);
            //MissionMap.Overlays.Add(routeOverlay);
            //MissionMap.UpdateRouteLocalPosition(routeLayer);

            //MissionMap.Refresh();
            //listBox1.Items.Clear();
            //for (int i = 0; i < latList.Count; i++)
            //{
            //    listBox1.Items.Add(i + ". Point :");
            //    listBox1.Items.Add(latList[i]);
            //    listBox1.Items.Add(lngList[i]);
            //}
        }

        private void btnGetRoute_Click(object sender, EventArgs e)
        {
            GPS_Com_Flag = true;

            byte[] byteCounterBytes = new byte[4];
            byteCounterBytes = BitConverter.GetBytes(index);
            UInt16 utility = byteCounterBytes[0];

            GPS_Buffer[1] = (byte)utility;

            crc16_dataTx = Form1.aeskCRCCalculate(GPS_Buffer, (uint)index);

            try
            {
                Form1.serialPort1.Write(GPS_Buffer, 0, index);
                System.Threading.Thread.Sleep(50);

                if(crc16_dataRx == crc16_dataTx && GPS_Com_Flag == false)
                {
                    MessageBox.Show("Succesfully Transmitted");
                }
                else
                {
                    MessageBox.Show("Transmission Failed");
                }
            }
            catch (Exception ex)
            {
                MessageBox.Show(ex.Message, "hata");
            }
        }
    }
}

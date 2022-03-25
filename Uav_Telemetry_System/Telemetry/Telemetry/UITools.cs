using System;
using System.Collections.Generic;
using System.Diagnostics;
using System.Drawing;
using System.IO;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using GMap.NET.WindowsForms;
using ZedGraph;


namespace Telemetry
{
    public static class UITools
    {
        public static Dictionary<string, Form> forms = new Dictionary<string, Form>();
        public static Form MainCopyForm;    //form tipinde Ana formumuzun kopyasını oluşturuyoruz.

        public static class SetPID
        {
            public static Button btnRxRollPitchKp;
            public static Button btnRxRollPitchKi;
            public static Button btnRxRollPitchKd;

            public static Button btnRxYawKp;
            public static Button btnRxYawKi;
            public static Button btnRxYawKd;

            public static Button btnRxAltitudeKp;
            public static Button btnRxAltitudeKi;
            public static Button btnRxAltitudeKd;

            public static Button btnRxGpsKp;
            public static Button btnRxGpsKi;
            public static Button btnRxGpsKd;

            public static Button btnRxExt1Kp;
            public static Button btnRxExt1Ki;
            public static Button btnRxExt1Kd;

            public static Button btnRxExt2Kp;
            public static Button btnRxExt2Ki;
            public static Button btnRxExt2Kd;

            public static TextBox txtRollPitchKp;
            public static TextBox txtRollPitchKi;
            public static TextBox txtRollPitchKd;

            public static TextBox txtYawKp;
            public static TextBox txtYawKi;
            public static TextBox txtYawKd;

            public static TextBox txtAltitudeKp;
            public static TextBox txtAltitudeKi;
            public static TextBox txtAltitudeKd;

            public static TextBox txtGpsKp;
            public static TextBox txtGpsKi;
            public static TextBox txtGpsKd;

            public static TextBox txtExt1Kp;
            public static TextBox txtExt1Ki;
            public static TextBox txtExt1Kd;

            public static TextBox txtExt2Kp;
            public static TextBox txtExt2Ki;
            public static TextBox txtExt2Kd;

        }   

        public static class Main
        {
            public static Button btnAltitude;
            public static Button btnYaw;
            public static Button btnRoll;
            public static Button btnPitch;

            public static Button btnTM1;
            public static Button btnTM2;
            public static Button btnTM3;
            public static Button btnTM4;
        }

        public static class Graphics
        {
            public static ZedGraphControl zedGraphControl1;
            public static ZedGraphControl zedGraphControl2;
            public static ZedGraphControl zedGraphControl3;
            public static ZedGraphControl zedGraphControl4;
        }

        public static class Home
        {
            public static GMapControl ActualPositionMap;
            public static PictureBox pictureBox1;
        }

        public static class RCControl
        {
            public static Button btnAdc1;
            public static Button btnAdc2;
            public static Button btnAdc3;
            public static Button btnAdc4;
            public static Button btnAdc5;
            public static Button btnAdc6;
            public static Button btnAdc7;
            public static Button btnAdc8;
            public static Button btnAdc9;
            public static Button btnAdc10;

            public static Button btnVelN;
            public static Button btnVelE;
            public static Button btnVelD;
            public static Button btnhAcc;
            public static Button btnSatellite;
            public static Button btnGspeed;
            public static Button btnLatitude;
            public static Button btnLongitude;

        }
    }
}

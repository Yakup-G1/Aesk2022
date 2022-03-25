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

namespace Telemetry
{
    public partial class frmRCControl : Form
    {

        public static Thread threadRCControl;
        public frmRCControl()
        {
            InitializeComponent();

            UITools.RCControl.btnAdc1 =  btnAdc1;
            UITools.RCControl.btnAdc2 =  btnAdc2;
            UITools.RCControl.btnAdc3 =  btnAdc3;
            UITools.RCControl.btnAdc4 =  btnAdc4;
            UITools.RCControl.btnAdc5 =  btnAdc5;
            UITools.RCControl.btnAdc6 =  btnAdc6;
            UITools.RCControl.btnAdc7 =  btnAdc7;
            UITools.RCControl.btnAdc8 =  btnAdc8;
            UITools.RCControl.btnAdc9 =  btnAdc9;
            UITools.RCControl.btnAdc10 = btnAdc10;

            UITools.RCControl.btnLatitude = btnLatitude;
            UITools.RCControl.btnLongitude = btnLongitude;
            UITools.RCControl.btnhAcc = btnhAcc;
            UITools.RCControl.btnGspeed = btnGspeed;
            UITools.RCControl.btnVelD = btnVelD;
            UITools.RCControl.btnVelE = btnVelE;
            UITools.RCControl.btnVelN = btnVelN;
            UITools.RCControl.btnSatellite = btnSatellite;

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
        private void frmRCControl_Load(object sender, EventArgs e)
        {

        }
    }

}

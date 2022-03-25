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
    public partial class frmSetPID : Form
    {

        public frmSetPID()
        {
            InitializeComponent();

            UITools.SetPID.btnRxAltitudeKp = btnRxAltitudeKp;
            UITools.SetPID.btnRxAltitudeKi = btnRxAltitudeKi;
            UITools.SetPID.btnRxAltitudeKd = btnRxAltitudeKd;

            UITools.SetPID.btnRxRollPitchKp = btnRxRollPitchKp;
            UITools.SetPID.btnRxRollPitchKi = btnRxRollPitchKi;
            UITools.SetPID.btnRxRollPitchKd = btnRxRollPitchKd;

            UITools.SetPID.btnRxYawKp = btnRxYawKp;
            UITools.SetPID.btnRxYawKi = btnRxYawKi;
            UITools.SetPID.btnRxYawKd = btnRxYawKd;

            UITools.SetPID.btnRxGpsKp = btnRxGpsKp;
            UITools.SetPID.btnRxGpsKi = btnRxGpsKi;
            UITools.SetPID.btnRxGpsKd = btnRxGpsKd;

            UITools.SetPID.btnRxExt1Kp = btnRxExt1Kp;
            UITools.SetPID.btnRxExt1Ki = btnRxExt1Ki;
            UITools.SetPID.btnRxExt1Kd = btnRxExt1Kd;

            UITools.SetPID.btnRxExt2Kp = btnRxExt2Kp;
            UITools.SetPID.btnRxExt2Ki = btnRxExt2Ki;
            UITools.SetPID.btnRxExt2Kd = btnRxExt2Kd;


            UITools.SetPID.txtRollPitchKp = txtRollPitchKp;
            UITools.SetPID.txtRollPitchKi = txtRollPitchKi;
            UITools.SetPID.txtRollPitchKd = txtRollPitchKd;

            UITools.SetPID.txtYawKp = txtYawKp;
            UITools.SetPID.txtYawKi = txtYawKi;
            UITools.SetPID.txtYawKd = txtYawKd;

            UITools.SetPID.txtAltitudeKp = txtAltitudeKp;
            UITools.SetPID.txtAltitudeKi = txtAltitudeKi;
            UITools.SetPID.txtAltitudeKd = txtAltitudeKd;

            UITools.SetPID.txtGpsKp = txtGPSKp;
            UITools.SetPID.txtGpsKi = txtGPSKi;
            UITools.SetPID.txtGpsKd = txtGPSKd;

            UITools.SetPID.txtExt1Kp = txtExt1Kp;
            UITools.SetPID.txtExt1Ki = txtExt1Ki;
            UITools.SetPID.txtExt1Kd = txtExt1Kd;

            UITools.SetPID.txtExt2Kp = txtExt2Kp;
            UITools.SetPID.txtExt2Ki = txtExt2Ki;
            UITools.SetPID.txtExt2Kd = txtExt2Kd;

            #region DoubleBuffers
            SetDoubleBuffered(tableLayoutPanel1);
            SetDoubleBuffered(tableLayoutPanel2);
            SetDoubleBuffered(tableLayoutPanel3);
            SetDoubleBuffered(tableLayoutPanel4);
            SetDoubleBuffered(tableLayoutPanel5);
            SetDoubleBuffered(tableLayoutPanel6);
            SetDoubleBuffered(tableLayoutPanel7);
            SetDoubleBuffered(tableLayoutPanel8);
            SetDoubleBuffered(tableLayoutPanel9);
            SetDoubleBuffered(tableLayoutPanel10);
            SetDoubleBuffered(tableLayoutPanel11);
            SetDoubleBuffered(tableLayoutPanel12);
            SetDoubleBuffered(tableLayoutPanel13);
            SetDoubleBuffered(tableLayoutPanel14);
            SetDoubleBuffered(tableLayoutPanel15);
            SetDoubleBuffered(tableLayoutPanel16);
            SetDoubleBuffered(tableLayoutPanel17);
            SetDoubleBuffered(tableLayoutPanel18);
            SetDoubleBuffered(tableLayoutPanel19);
            SetDoubleBuffered(tableLayoutPanel20);
            SetDoubleBuffered(tableLayoutPanel21);
            SetDoubleBuffered(tableLayoutPanel22);
            SetDoubleBuffered(tableLayoutPanel23);
            SetDoubleBuffered(tableLayoutPanel24);
            SetDoubleBuffered(tableLayoutPanel25);
            SetDoubleBuffered(tableLayoutPanel26);
            SetDoubleBuffered(tableLayoutPanel28);
            SetDoubleBuffered(pictureBox1);
            SetDoubleBuffered(btnRxAltitudeKp);
            SetDoubleBuffered(btnRxAltitudeKi);
            SetDoubleBuffered(btnRxAltitudeKd);
            SetDoubleBuffered(btnRxExt1Kp);
            SetDoubleBuffered(btnRxExt1Ki);
            SetDoubleBuffered(btnRxExt1Kd);
            SetDoubleBuffered(btnRxExt2Kp);
            SetDoubleBuffered(btnRxExt2Ki);
            SetDoubleBuffered(btnRxExt2Kd);
            SetDoubleBuffered(btnRxGpsKp);
            SetDoubleBuffered(btnRxGpsKi);
            SetDoubleBuffered(btnRxGpsKd);
            SetDoubleBuffered(btnRxRollPitchKp);
            SetDoubleBuffered(btnRxRollPitchKi);
            SetDoubleBuffered(btnRxRollPitchKd);
            SetDoubleBuffered(btnRxYawKp);
            SetDoubleBuffered(btnRxYawKi);
            SetDoubleBuffered(btnRxYawKd);
            #endregion
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

        #region..KeyPress Protections..
        private void txtRollPitchKp_KeyPress(object sender, KeyPressEventArgs e)
        {
            if (!char.IsControl(e.KeyChar) && !char.IsDigit(e.KeyChar) && e.KeyChar != ',')
            {
                e.Handled = true;
            }
        }

        private void txtRollPitchKi_KeyPress(object sender, KeyPressEventArgs e)
        {
            if (!char.IsControl(e.KeyChar) && !char.IsDigit(e.KeyChar) && e.KeyChar != ',')
            {
                e.Handled = true;
            }
        }

        private void txtRollPitchKd_KeyPress(object sender, KeyPressEventArgs e)
        {
            if (!char.IsControl(e.KeyChar) && !char.IsDigit(e.KeyChar) && e.KeyChar != ',')
            {
                e.Handled = true;
            }
        }

        private void txtYawKp_KeyPress(object sender, KeyPressEventArgs e)
        {
            if (!char.IsControl(e.KeyChar) && !char.IsDigit(e.KeyChar) && e.KeyChar != ',')
            {
                e.Handled = true;
            }
        }

        private void txtYawKi_KeyPress(object sender, KeyPressEventArgs e)
        {
            if (!char.IsControl(e.KeyChar) && !char.IsDigit(e.KeyChar) && e.KeyChar != ',')
            {
                e.Handled = true;
            }
        }

        private void txtYawKd_KeyPress(object sender, KeyPressEventArgs e)
        {
            if (!char.IsControl(e.KeyChar) && !char.IsDigit(e.KeyChar) && e.KeyChar != ',')
            {
                e.Handled = true;
            }
        }

        private void txtAltitudeKp_KeyPress(object sender, KeyPressEventArgs e)
        {
            if (!char.IsControl(e.KeyChar) && !char.IsDigit(e.KeyChar) && e.KeyChar != ',')
            {
                e.Handled = true;
            }
        }

        private void txtAltitudeKi_KeyPress(object sender, KeyPressEventArgs e)
        {
            if (!char.IsControl(e.KeyChar) && !char.IsDigit(e.KeyChar) && e.KeyChar != ',')
            {
                e.Handled = true;
            }
        }

        private void txtAltitudeKd_KeyPress(object sender, KeyPressEventArgs e)
        {
            if (!char.IsControl(e.KeyChar) && !char.IsDigit(e.KeyChar) && e.KeyChar != ',')
            {
                e.Handled = true;
            }
        }

        private void txtGPSKp_KeyPress(object sender, KeyPressEventArgs e)
        {
            if (!char.IsControl(e.KeyChar) && !char.IsDigit(e.KeyChar) && e.KeyChar != ',')
            {
                e.Handled = true;
            }
        }

        private void txtGPSKi_KeyPress(object sender, KeyPressEventArgs e)
        {
            if (!char.IsControl(e.KeyChar) && !char.IsDigit(e.KeyChar) && e.KeyChar != ',')
            {
                e.Handled = true;
            }
        }

        private void txtGPSKd_KeyPress(object sender, KeyPressEventArgs e)
        {
            if (!char.IsControl(e.KeyChar) && !char.IsDigit(e.KeyChar) && e.KeyChar != ',')
            {
                e.Handled = true;
            }
        }

        private void textBox15_KeyPress(object sender, KeyPressEventArgs e)
        {
            if (!char.IsControl(e.KeyChar) && !char.IsDigit(e.KeyChar) && e.KeyChar != ',')
            {
                e.Handled = true;
            }
        }

        private void textBox14_KeyPress(object sender, KeyPressEventArgs e)
        {
            if (!char.IsControl(e.KeyChar) && !char.IsDigit(e.KeyChar) && e.KeyChar != ',')
            {
                e.Handled = true;
            }
        }

        private void textBox13_KeyPress(object sender, KeyPressEventArgs e)
        {
            if (!char.IsControl(e.KeyChar) && !char.IsDigit(e.KeyChar) && e.KeyChar != ',')
            {
                e.Handled = true;
            }
        }

        private void textBox18_KeyPress(object sender, KeyPressEventArgs e)
        {
            if (!char.IsControl(e.KeyChar) && !char.IsDigit(e.KeyChar) && e.KeyChar != ',')
            {
                e.Handled = true;
            }
        }

        private void textBox17_KeyPress(object sender, KeyPressEventArgs e)
        {
            if (!char.IsControl(e.KeyChar) && !char.IsDigit(e.KeyChar) && e.KeyChar != ',')
            {
                e.Handled = true;
            }
        }

        private void textBox16_KeyPress(object sender, KeyPressEventArgs e)
        {
            if (!char.IsControl(e.KeyChar) && !char.IsDigit(e.KeyChar) && e.KeyChar != ',')
            {
                e.Handled = true;
            }
        }



        #endregion


        public static byte[] PID_Transmit_Buffer = new byte[256];

        public static int byteCounter = 56;

        private void frmSetPID_Load(object sender, EventArgs e)
        {

            PID_Transmit_Buffer[0] = (byte)'P'; //  ASCII 80

        }
        private void btnSetDefaultValues_Click(object sender, EventArgs e)
        {
            txtRollPitchKp.Text = "0,09"; txtYawKp.Text = "0,2"; txtAltitudeKp.Text = "1,3";
            txtRollPitchKi.Text = "0,043"; txtYawKi.Text = "0"; txtAltitudeKi.Text = "0";
            txtRollPitchKd.Text = "0,013"; txtYawKd.Text = "25"; txtAltitudeKd.Text = "0,1";
            txtGPSKp.Text = "0"; txtGPSKi.Text = "0"; txtGPSKd.Text = "0";
            txtExt1Kp.Text = "0"; txtExt1Ki.Text = "0"; txtExt1Kd.Text = "0";
            txtExt2Kp.Text = "0"; txtExt2Ki.Text = "0"; txtExt2Kd.Text = "0";
        }
        private void btnClearBuffer_Click(object sender, EventArgs e)
        {
            int i;
            for (i = 2; i < 256; i++)
            {
                PID_Transmit_Buffer[i] = 0;
            }

            txtRollPitchKp.Text = "0"; txtRollPitchKi.Text = "0"; txtRollPitchKd.Text = "0";
            txtYawKp.Text = "0"; txtYawKi.Text = "0"; txtYawKd.Text = "0";
            txtAltitudeKp.Text = "0"; txtAltitudeKd.Text = "0"; txtAltitudeKi.Text = "0";
            txtGPSKp.Text = "0"; txtGPSKi.Text = "0"; txtGPSKd.Text = "0";
            txtExt1Kp.Text = "0"; txtExt1Ki.Text = "0"; txtExt1Kd.Text = "0";
            txtExt2Kp.Text = "0"; txtExt2Ki.Text = "0"; txtExt2Kd.Text = "0";
        }

        private void btnSendPID_Click(object sender, EventArgs e)
        {

            float RollPitch_Kp, RollPitch_Ki, RollPitch_Kd;
            float Yaw_Kp, Yaw_Ki, Yaw_Kd;
            float Altitude_Kp, Altitude_Ki, Altitude_Kd;
            float GPS_Kp, GPS_Ki, GPS_Kd;
            float ext1_Kp, ext1_Ki, ext1_Kd;
            float ext2_Kp, ext2_Ki, ext2_Kd;

            RollPitch_Kp = float.Parse(txtRollPitchKp.Text);
            RollPitch_Ki = float.Parse(txtRollPitchKi.Text);
            RollPitch_Kd = float.Parse(txtRollPitchKd.Text);
            Yaw_Kp       = float.Parse(txtYawKp.Text);
            Yaw_Ki       = float.Parse(txtYawKi.Text);
            Yaw_Kd       = float.Parse(txtYawKd.Text);
            Altitude_Kp  = float.Parse(txtAltitudeKp.Text);
            Altitude_Ki  = float.Parse(txtAltitudeKi.Text);
            Altitude_Kd  = float.Parse(txtAltitudeKd.Text);
            GPS_Kp       = float.Parse(txtGPSKp.Text);
            GPS_Ki       = float.Parse(txtGPSKi.Text);
            GPS_Kd       = float.Parse(txtGPSKd.Text);
            ext1_Kp      = float.Parse(txtExt1Kp.Text);
            ext1_Ki      = float.Parse(txtExt1Ki.Text);
            ext1_Kd      = float.Parse(txtExt1Kd.Text);
            ext2_Kp      = float.Parse(txtExt2Kp.Text);
            ext2_Ki      = float.Parse(txtExt2Ki.Text);
            ext2_Kd      = float.Parse(txtExt2Kd.Text);

            byte[] RollPitch_Kp_Bytes = new byte[4];
            byte[] RollPitch_Ki_Bytes = new byte[4];
            byte[] RollPitch_Kd_Bytes = new byte[4];
            byte[] Yaw_Kp_Bytes       = new byte[4];
            byte[] Yaw_Ki_Bytes       = new byte[4];
            byte[] Yaw_Kd_Bytes       = new byte[4];
            byte[] Altitude_Kp_Bytes  = new byte[4];
            byte[] Altitude_Ki_Bytes  = new byte[4];
            byte[] Altitude_Kd_Bytes  = new byte[4];
            byte[] GPS_Kp_Bytes       = new byte[4];
            byte[] GPS_Ki_Bytes       = new byte[4];
            byte[] GPS_Kd_Bytes       = new byte[4];
            byte[] ext1_Kp_Bytes      = new byte[4];
            byte[] ext1_Ki_Bytes      = new byte[4];
            byte[] ext1_Kd_Bytes      = new byte[4];
            byte[] ext2_Kp_Bytes      = new byte[4];
            byte[] ext2_Ki_Bytes      = new byte[4];
            byte[] ext2_Kd_Bytes      = new byte[4];

            RollPitch_Kp_Bytes  = BitConverter.GetBytes((UInt32)(RollPitch_Kp * 100000));
            RollPitch_Ki_Bytes  = BitConverter.GetBytes((UInt32)(RollPitch_Ki * 100000));
            RollPitch_Kd_Bytes  = BitConverter.GetBytes((UInt32)(RollPitch_Kd * 100000));
            Yaw_Kp_Bytes        = BitConverter.GetBytes((UInt32)(Yaw_Kp * 100000));
            Yaw_Ki_Bytes        = BitConverter.GetBytes((UInt32)(Yaw_Ki * 100000));
            Yaw_Kd_Bytes        = BitConverter.GetBytes((UInt32)(Yaw_Kd * 100000));
            Altitude_Kp_Bytes   = BitConverter.GetBytes((UInt32)(Altitude_Kp * 100000));
            Altitude_Ki_Bytes   = BitConverter.GetBytes((UInt32)(Altitude_Ki * 100000));
            Altitude_Kd_Bytes   = BitConverter.GetBytes((UInt32)(Altitude_Kd * 100000));
            GPS_Kp_Bytes        = BitConverter.GetBytes((UInt32)(GPS_Kp * 100000));
            GPS_Ki_Bytes        = BitConverter.GetBytes((UInt32)(GPS_Ki * 100000));
            GPS_Kd_Bytes        = BitConverter.GetBytes((UInt32)(GPS_Kd * 100000));
            ext1_Kp_Bytes       = BitConverter.GetBytes((UInt32)(ext1_Kp * 100000));
            ext1_Ki_Bytes       = BitConverter.GetBytes((UInt32)(ext1_Ki * 100000));
            ext1_Kd_Bytes       = BitConverter.GetBytes((UInt32)(ext1_Kd * 100000));
            ext2_Kp_Bytes       = BitConverter.GetBytes((UInt32)(ext2_Kp * 100000));
            ext2_Ki_Bytes       = BitConverter.GetBytes((UInt32)(ext2_Ki * 100000));
            ext2_Kd_Bytes       = BitConverter.GetBytes((UInt32)(ext2_Kd * 100000));

            RollPitch_Kp_Bytes.CopyTo(PID_Transmit_Buffer, 2);
            RollPitch_Ki_Bytes.CopyTo(PID_Transmit_Buffer, 5);
            RollPitch_Kd_Bytes.CopyTo(PID_Transmit_Buffer, 8);
            Yaw_Kp_Bytes.CopyTo(PID_Transmit_Buffer, 11);
            Yaw_Ki_Bytes.CopyTo(PID_Transmit_Buffer, 14);
            Yaw_Kd_Bytes.CopyTo(PID_Transmit_Buffer, 17);
            Altitude_Kp_Bytes.CopyTo(PID_Transmit_Buffer, 20);
            Altitude_Ki_Bytes.CopyTo(PID_Transmit_Buffer, 23);
            Altitude_Kd_Bytes.CopyTo(PID_Transmit_Buffer, 26);
            GPS_Kp_Bytes.CopyTo(PID_Transmit_Buffer, 29);
            GPS_Ki_Bytes.CopyTo(PID_Transmit_Buffer, 32);
            GPS_Kd_Bytes.CopyTo(PID_Transmit_Buffer, 35);
            ext1_Kp_Bytes.CopyTo(PID_Transmit_Buffer, 38);
            ext1_Ki_Bytes.CopyTo(PID_Transmit_Buffer, 41);
            ext1_Kd_Bytes.CopyTo(PID_Transmit_Buffer, 44);
            ext2_Kp_Bytes.CopyTo(PID_Transmit_Buffer, 47);
            ext2_Ki_Bytes.CopyTo(PID_Transmit_Buffer, 50);
            ext2_Kd_Bytes.CopyTo(PID_Transmit_Buffer, 53);

            byte[] byteCounterBytes = new byte[4];
            byteCounterBytes = BitConverter.GetBytes(byteCounter);
            UInt16 utility = byteCounterBytes[0];

            PID_Transmit_Buffer[1] = (byte)utility;

            try
            {
                Form1.serialPort1.Write(PID_Transmit_Buffer, 0, byteCounter);
            }
            catch (Exception ex)
            {
                MessageBox.Show(ex.Message, "hata");
            }
        }

    }
}

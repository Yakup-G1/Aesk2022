using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading;
using System.Threading.Tasks;
using System.Windows.Forms;
using System.Runtime.InteropServices;
using System.IO.Ports;
using System.Diagnostics;

namespace Telemetry
{
    public partial class Form1 : Form
    {

        RecieveData recieveData = new RecieveData();

        public static SerialPort serialPort1 = new SerialPort();

        public static int bytesToReadCount;

        Thread threadDelegate;

        //Log logs = new Log(@"C:\\dene\\");

        //Stopwatch timer = new Stopwatch();

        #region sevenleri ayırma
        [DllImport("Gdi32.dll", EntryPoint = "CreateRoundRectRgn")]

        private static extern IntPtr CreateRoundRectRgn
        (
            int nLeftRect,
            int nTopRect,
            int nRightRect,
            int nBottomRect,
            int nWidthEllipse,
            int nHeightEllipse
        );
        #endregion

        public Form1()
        {
            InitializeComponent();

            UITools.forms.Add("Mission", new frmMission());
            UITools.forms.Add("Graphics", new frmGraphics());
            UITools.forms.Add("Home", new frmHome());
            UITools.forms.Add("RCControl", new frmRCControl());
            UITools.forms.Add("SetPID", new frmSetPID());
            UITools.forms.Add("UAVReset", new frmSettings());

            UITools.Main.btnAltitude = btnAltitude;
            UITools.Main.btnYaw = btnYaw;
            UITools.Main.btnRoll = btnRoll;
            UITools.Main.btnPitch= btnPitch;
            UITools.Main.btnTM1 = btnTM1;
            UITools.Main.btnTM2 = btnTM2;
            UITools.Main.btnTM3 = btnTM3;
            UITools.Main.btnTM4 = btnTM4;

            #region   .. Double Buffers ..
            SetDoubleBuffered(tableLayoutPanel1);
            SetDoubleBuffered(tableLayoutPanel2);
            SetDoubleBuffered(tableLayoutPanel3);
            SetDoubleBuffered(tableLayoutPanel4);
            SetDoubleBuffered(tableLayoutPanel5);
            SetDoubleBuffered(tableLayoutPanel6);
            SetDoubleBuffered(pnlControl);
            SetDoubleBuffered(pnlFormLoader);
            SetDoubleBuffered(pnlNav);
            SetDoubleBuffered(panel2);
            SetDoubleBuffered(button2);
            SetDoubleBuffered(btnPitch);
            SetDoubleBuffered(button4);
            SetDoubleBuffered(btnTM2);
            SetDoubleBuffered(btnTM4);
            SetDoubleBuffered(button10);
            SetDoubleBuffered(button12);
            SetDoubleBuffered(btnTM3);
            SetDoubleBuffered(btnYaw);
            SetDoubleBuffered(btnTM1);
            SetDoubleBuffered(btnAltitude);
            SetDoubleBuffered(btnRoll);
            SetDoubleBuffered(pictureBox1);
            SetDoubleBuffered(artifical_Horizon1);
            SetDoubleBuffered(headingIndicator1);
            SetDoubleBuffered(altimeter1);
            #endregion  

            serialPort1.BaudRate = 9600;
            Control.CheckForIllegalCrossThreadCalls = false; // Thread çakışmalarının önlenmesi için

            //Menünün kontrol panelinde seçtiğin butonların seçiili olduğunu anlamak için görsel tasarım
            pnlNav.Height = btnHome.Height;
            pnlNav.Top = btnHome.Top;
            pnlNav.Left = btnHome.Left;
            btnHome.BackColor = Color.FromArgb(46, 51, 73);

            //Uygulama ilk açıldığında home ekranı gelsin diye initialize'de bir kere çağırılıyor
            FormManagement.openChildForm(UITools.forms["Home"], pnlFormLoader);

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

        string[] ports = SerialPort.GetPortNames();

        private void Form1_Load(object sender, EventArgs e)
        {

            foreach (string port in ports)
            {
                comboBox1.Items.Add(port);
            }
            try
            {
                comboBox1.SelectedIndex = 0;
            }
            catch (Exception)
            {
                ; ;
            }

            serialPort1.DataReceived += new SerialDataReceivedEventHandler(serialPort1_DataReceived);
        }

        #region..Serial Port Processes..

        private void serialPort1_DataReceived(object sender, SerialDataReceivedEventArgs e)
            {
            if (serialPort1.IsOpen == true)
            {
                try
                {
                    bytesToReadCount = serialPort1.BytesToRead;
                    byte[] ReceiveBuffer = new byte[bytesToReadCount+2];    // +2'nin sebebi buffer converter'a eklediğim convert toint24 fonksiyonu

                    serialPort1.Read(ReceiveBuffer, 0, bytesToReadCount);

                    if ( bytesToReadCount > 0 )
                    {
                        recieveData.DataPackRead(ReceiveBuffer);
                    }

                }
                catch (Exception)
                {
                    ; ;
                }
            }
        }

        public static void PIDSendReceiveControl()
        {
            double error = 0.002;
            if (Math.Abs(Convert.ToDouble(UITools.SetPID.txtRollPitchKp.Text) - Convert.ToDouble(UITools.SetPID.btnRxRollPitchKp.Text)) < error)
                UITools.SetPID.btnRxRollPitchKp.BackColor = Color.Green;
            else
                UITools.SetPID.btnRxRollPitchKp.BackColor = Color.Red;
            if (Math.Abs(Convert.ToDouble(UITools.SetPID.txtRollPitchKi.Text) - Convert.ToDouble(UITools.SetPID.btnRxRollPitchKi.Text)) < error)
                UITools.SetPID.btnRxRollPitchKi.BackColor = Color.Green;
            else
                UITools.SetPID.btnRxRollPitchKi.BackColor = Color.Red;
            if (Math.Abs(Convert.ToDouble(UITools.SetPID.txtRollPitchKd.Text) - Convert.ToDouble(UITools.SetPID.btnRxRollPitchKd.Text)) < error)
                UITools.SetPID.btnRxRollPitchKd.BackColor = Color.Green;
            else
                UITools.SetPID.btnRxRollPitchKd.BackColor = Color.Red;
            if (Math.Abs(Convert.ToDouble(UITools.SetPID.txtYawKp.Text) - Convert.ToDouble(UITools.SetPID.btnRxYawKp.Text)) < error)
                UITools.SetPID.btnRxYawKp.BackColor = Color.Green;
            else
                UITools.SetPID.btnRxYawKp.BackColor = Color.Red;
            if (Math.Abs(Convert.ToDouble(UITools.SetPID.txtYawKi.Text) - Convert.ToDouble(UITools.SetPID.btnRxYawKi.Text)) < error)
                UITools.SetPID.btnRxYawKi.BackColor = Color.Green;
            else
                UITools.SetPID.btnRxYawKi.BackColor = Color.Red;
            if (Math.Abs(Convert.ToDouble(UITools.SetPID.txtYawKd.Text) - Convert.ToDouble(UITools.SetPID.btnRxYawKd.Text)) < error)
                UITools.SetPID.btnRxYawKd.BackColor = Color.Green;
            else
                UITools.SetPID.btnRxYawKd.BackColor = Color.Red;
            if (Math.Abs(Convert.ToDouble(UITools.SetPID.txtAltitudeKp.Text) - Convert.ToDouble(UITools.SetPID.btnRxAltitudeKp.Text)) < error)
                UITools.SetPID.btnRxAltitudeKp.BackColor = Color.Green;
            else
                UITools.SetPID.btnRxAltitudeKp.BackColor = Color.Red;
            if (Math.Abs(Convert.ToDouble(UITools.SetPID.txtAltitudeKi.Text) - Convert.ToDouble(UITools.SetPID.btnRxAltitudeKi.Text)) < error)
                UITools.SetPID.btnRxAltitudeKi.BackColor = Color.Green;
            else
                UITools.SetPID.btnRxAltitudeKi.BackColor = Color.Red;
            if (Math.Abs(Convert.ToDouble(UITools.SetPID.txtAltitudeKd.Text) - Convert.ToDouble(UITools.SetPID.btnRxAltitudeKd.Text)) < error)
                UITools.SetPID.btnRxAltitudeKd.BackColor = Color.Green;
            else
                UITools.SetPID.btnRxAltitudeKd.BackColor = Color.Red;
            if (Math.Abs(Convert.ToDouble(UITools.SetPID.txtGpsKp.Text) - Convert.ToDouble(UITools.SetPID.btnRxGpsKp.Text)) < error)
                UITools.SetPID.btnRxGpsKp.BackColor = Color.Green;
            else
                UITools.SetPID.btnRxGpsKp.BackColor = Color.Red;
            if (Math.Abs(Convert.ToDouble(UITools.SetPID.txtGpsKi.Text) - Convert.ToDouble(UITools.SetPID.btnRxGpsKi.Text)) < error)
                UITools.SetPID.btnRxGpsKi.BackColor = Color.Green;
            else
                UITools.SetPID.btnRxGpsKi.BackColor = Color.Red;
            if (Math.Abs(Convert.ToDouble(UITools.SetPID.txtGpsKd.Text) - Convert.ToDouble(UITools.SetPID.btnRxGpsKd.Text)) < error)
                UITools.SetPID.btnRxGpsKd.BackColor = Color.Green;
            else
                UITools.SetPID.btnRxGpsKd.BackColor = Color.Red;
            if (Math.Abs(Convert.ToDouble(UITools.SetPID.txtExt1Kp.Text) - Convert.ToDouble(UITools.SetPID.btnRxExt1Kp.Text)) < error)
                UITools.SetPID.btnRxExt1Kp.BackColor = Color.Green;
            else
                UITools.SetPID.btnRxExt1Kp.BackColor = Color.Red;
            if (Math.Abs(Convert.ToDouble(UITools.SetPID.txtExt1Ki.Text) - Convert.ToDouble(UITools.SetPID.btnRxExt1Ki.Text)) < error)
                UITools.SetPID.btnRxExt1Ki.BackColor = Color.Green;
            else
                UITools.SetPID.btnRxExt1Ki.BackColor = Color.Red;
            if (Math.Abs(Convert.ToDouble(UITools.SetPID.txtExt1Kd.Text) - Convert.ToDouble(UITools.SetPID.btnRxExt1Kd.Text)) < error)
                UITools.SetPID.btnRxExt1Kd.BackColor = Color.Green;
            else
                UITools.SetPID.btnRxExt1Kd.BackColor = Color.Red;
            if (Math.Abs(Convert.ToDouble(UITools.SetPID.txtExt2Kp.Text) - Convert.ToDouble(UITools.SetPID.btnRxExt2Kp.Text)) < error)
                UITools.SetPID.btnRxExt2Kp.BackColor = Color.Green;
            else
                UITools.SetPID.btnRxExt2Kp.BackColor = Color.Red;
            if (Math.Abs(Convert.ToDouble(UITools.SetPID.txtExt2Ki.Text) - Convert.ToDouble(UITools.SetPID.btnRxExt2Ki.Text)) < error)
                UITools.SetPID.btnRxExt2Ki.BackColor = Color.Green;
            else
                UITools.SetPID.btnRxExt2Ki.BackColor = Color.Red;
            if (Math.Abs(Convert.ToDouble(UITools.SetPID.txtExt2Kd.Text) - Convert.ToDouble(UITools.SetPID.btnRxExt2Kd.Text)) < error)
                UITools.SetPID.btnRxExt2Kd.BackColor = Color.Green;
            else
                UITools.SetPID.btnRxExt2Kd.BackColor = Color.Red;
        }
        private void displayDataEvent()
        {
            if(serialPort1.IsOpen == true)
            {
                try
                {

                    UITools.Main.btnAltitude.Text = RecieveData.altitude.ToString();
                    UITools.Main.btnYaw.Text = RecieveData.yaw.ToString();
                    UITools.Main.btnRoll.Text = RecieveData.roll.ToString();
                    UITools.Main.btnPitch.Text = RecieveData.pitch.ToString();
                    UITools.Main.btnTM1.Text = RecieveData.motor1.ToString();
                    UITools.Main.btnTM2.Text = RecieveData.motor2.ToString();
                    UITools.Main.btnTM3.Text = RecieveData.motor3.ToString();
                    UITools.Main.btnTM4.Text = RecieveData.motor4.ToString();
                    btnBattery.Text = (RecieveData.batteryVoltage/100).ToString();
                    btnLidar.Text = RecieveData.LidarOutput.ToString();

                    UITools.RCControl.btnLatitude.Text = RecieveData.latitude.ToString(); ;
                    UITools.RCControl.btnLongitude.Text = RecieveData.longitude.ToString(); ;
                    UITools.RCControl.btnhAcc.Text = RecieveData.hAcc.ToString(); ;
                    UITools.RCControl.btnVelN.Text = RecieveData.velD.ToString(); ;
                    UITools.RCControl.btnVelE.Text = RecieveData.velE.ToString(); ;
                    UITools.RCControl.btnVelD.Text = RecieveData.velN.ToString(); ;
                    UITools.RCControl.btnGspeed.Text = RecieveData.gSpeed.ToString();
                    UITools.RCControl.btnSatellite.Text = RecieveData.SatelliteNumber.ToString();

                    //UITools.RCControl.adc1.Text = RecieveData.adc1.ToString();
                    //UITools.RCControl.adc2.Text = RecieveData.adc2.ToString();
                    //UITools.RCControl.adc3.Text = RecieveData.adc3.ToString();
                    //UITools.RCControl.adc4.Text = RecieveData.adc4.ToString();
                    //UITools.RCControl.adc5.Text = RecieveData.adc5.ToString();
                    //UITools.RCControl.adc6.Text = RecieveData.adc6.ToString();
                    //UITools.RCControl.adc7.Text = RecieveData.adc7.ToString();
                    //UITools.RCControl.adc8.Text = RecieveData.adc8.ToString();
                    //UITools.RCControl.adc9.Text = RecieveData.adc9.ToString();
                    //UITools.RCControl.adc10.Text = RecieveData.adc10.ToString();

                    float heading = RecieveData.yaw;
                    if (heading < 0)
                        heading = heading + 360;
                    headingIndicator1.Heading = (UInt16)heading;

                    artifical_Horizon1.RollAngle = Convert.ToDouble(RecieveData.roll);
                    artifical_Horizon1.PitchAngle = Convert.ToDouble(RecieveData.pitch);
                    artifical_Horizon1.Refresh();

                    altimeter1.Altitude = (UInt16)RecieveData.altitude;
                    altimeter1.Refresh();

                    if (frmHome.homeActivatedFlag == true)
                    {
                        frmHome.gpsUpdateLocation();
                    }

                    frmGraphics.Draw_Grapichs
                    (
                        UITools.Graphics.zedGraphControl1,
                        UITools.Graphics.zedGraphControl2,
                        UITools.Graphics.zedGraphControl3,
                        UITools.Graphics.zedGraphControl4
                    );

                    Form1.PIDSendReceiveControl();

                    //TimeSpan timeTaken = timer.Elapsed;

                    //string timeStr = timeTaken.ToString();
                    //string parts = timeStr.Split('.')[0];

                    //logs.WriteLine(parts);

                }
                catch (Exception)
                {

                }
            }
        }

        
        private void delegateFunction()
        {
            try
            {
                while (true)
                {
                    this.Invoke((MethodInvoker)delegate { displayDataEvent(); });

                    Thread.Sleep(50);
                }
            }
            catch (Exception)
            {
                ; ;
            }

        }

        public static ushort aeskCRCCalculate(byte[] frame, uint framesize)
        {
            ushort crc16_data = 0;
            byte data = 0;
            for (byte mlen = 0; mlen < framesize; mlen++)
            {
                data = Convert.ToByte(((byte)frame[mlen] ^ Convert.ToByte(((crc16_data) & (0xFF)))));
                Console.WriteLine(data);
                data = (byte)((byte)data ^ (byte)(data << 4));
                crc16_data = (ushort)((((ushort)data << 8) | ((crc16_data & 0xFF00) >> 8)) ^ (byte)(data >> 4) ^ ((ushort)data << 3));
            }
            return (crc16_data);
        }


        private void Form1_FormClosed(object sender, FormClosedEventArgs e)
        {
            if (serialPort1.IsOpen)
            {
                serialPort1.Close();
            }
            serialPort1.DataReceived -= new SerialDataReceivedEventHandler(serialPort1_DataReceived);
        }

        private void Form1_FormClosing(object sender, FormClosingEventArgs e)
        {
            if (serialPort1.IsOpen)
            {
                serialPort1.Close();
            }
            serialPort1.DataReceived -= new SerialDataReceivedEventHandler(serialPort1_DataReceived);

        }
        #endregion

        #region..Anasayfa Butonlarının Eventleri..
        private void btnHome_Click(object sender, EventArgs e)
        {
            pnlNav.Height = btnHome.Height;
            pnlNav.Top = btnHome.Top;
            pnlNav.Left = btnHome.Left;
            btnHome.BackColor = Color.FromArgb(46, 51, 73);

            FormManagement.openChildForm(UITools.forms["Home"], pnlFormLoader);
        }

        private void btnMission_Click(object sender, EventArgs e)
        {
            pnlNav.Height = btnMission.Height;
            pnlNav.Top = btnMission.Top;
            pnlNav.Left = btnMission.Left;
            btnMission.BackColor = Color.FromArgb(46, 51, 73);
            btnHome.BackColor = Color.FromArgb(24, 29, 53);

            FormManagement.openChildForm(UITools.forms["Mission"], pnlFormLoader);
        }

        private void btnRCControl_Click(object sender, EventArgs e)
        {
            pnlNav.Height = btnRCControl.Height;
            pnlNav.Top = btnRCControl.Top;
            pnlNav.Left = btnRCControl.Left;
            btnRCControl.BackColor = Color.FromArgb(46, 51, 73);
            btnHome.BackColor = Color.FromArgb(24, 29, 53);

            FormManagement.openChildForm(UITools.forms["RCControl"], pnlFormLoader);
        }

        private void btnGraphics_Click(object sender, EventArgs e)
        {
            pnlNav.Height = btnGraphics.Height;
            pnlNav.Top = btnGraphics.Top;
            pnlNav.Left = btnGraphics.Left;
            btnGraphics.BackColor = Color.FromArgb(46, 51, 73);
            btnHome.BackColor = Color.FromArgb(24, 29, 53);

            FormManagement.openChildForm(UITools.forms["Graphics"], pnlFormLoader);
        }

        private void btnSetPID_Click(object sender, EventArgs e)
        {

            pnlNav.Height = btnSetPID.Height;
            pnlNav.Top = btnSetPID.Top;
            pnlNav.Left = btnSetPID.Left;
            btnSetPID.BackColor = Color.FromArgb(46, 51, 73);
            btnHome.BackColor = Color.FromArgb(24, 29, 53);

            FormManagement.openChildForm(UITools.forms["SetPID"], pnlFormLoader);
       
            //this.pnlFormLoader.Controls.Clear();
            //frmSetPID frmHome_Vrb = new frmSetPID() { Dock = DockStyle.Fill, TopLevel = false, TopMost = true };
            //frmHome_Vrb.FormBorderStyle = FormBorderStyle.None;
            //this.pnlFormLoader.Controls.Add(frmHome_Vrb);
            //frmHome_Vrb.Show();

            // başta her buton eventine bu şekilde 5 satır kod yazarak formu çağırıyodum. ibret olsun diye silmedim.
        }
        #endregion

        #region ..UI Panel Design..
        private void btnHome_Leave(object sender, EventArgs e)
        {
            btnHome.BackColor = Color.FromArgb(24, 30, 54);
        }

        private void btnMission_Leave(object sender, EventArgs e)
        {
            btnMission.BackColor = Color.FromArgb(24, 30, 54);
        }

        private void btnSettings_Leave(object sender, EventArgs e)
        {
            btnReset.BackColor = Color.FromArgb(24, 30, 54);
        }

        private void btnRCControl_Leave(object sender, EventArgs e)
        {
            btnRCControl.BackColor = Color.FromArgb(24, 30, 54);
        }

        private void btnGraphics_Leave(object sender, EventArgs e)
        {
            btnGraphics.BackColor = Color.FromArgb(24, 30, 54);
        }

        private void btnSetPID_Leave(object sender, EventArgs e)
        {
            btnSetPID.BackColor = Color.FromArgb(24, 30, 54);
        }

        #endregion

        private void btnConnect_Click(object sender, EventArgs e)
        {

            threadDelegate = new Thread(delegateFunction);
            threadDelegate.Start();

            try
            {
                serialPort1.PortName = comboBox1.Text;

                serialPort1.BaudRate = 9600;
                serialPort1.DataBits = 8;             
                serialPort1.StopBits = StopBits.One;
                serialPort1.Parity = Parity.None;

                serialPort1.ReadTimeout = 100;                      //Başlangıçta sistemi açarken sisteme küçük bir zaman tanıyoruz.

                serialPort1.Open();
                serialPort1.DiscardInBuffer();
                serialPort1.DiscardOutBuffer();

                if(serialPort1.IsOpen)
                { 
                    btnDisconnect.BackColor = Color.DimGray;
                    btnConnect.BackColor = Color.LightGreen;

                    UITools.Home.pictureBox1.Visible = true;
                }
            }
            catch (Exception ex)
            {
                MessageBox.Show(ex.Message,"Hata");
            }
            
        }

        private void btnDisconnect_Click(object sender, EventArgs e)
        {
            if (serialPort1.IsOpen)
            {
                serialPort1.Close();

                threadDelegate.Abort();
            }
            if(serialPort1.IsOpen == false)
            {
                btnConnect.BackColor = Color.DimGray;
                btnDisconnect.BackColor = Color.Red;
            }

        }

        private void btnRefresh_Click(object sender, EventArgs e)
        {
            comboBox1.Items.Clear();
            comboBox1.ResetText();
     
            string[] ports = SerialPort.GetPortNames();

            foreach (string port in ports)
            {
                comboBox1.Items.Add(port);
            }
            try
            {
                comboBox1.SelectedIndex = 0;
            }
            catch (Exception)
            {
                ; ;
            }
        }

        private void btnReset_Click(object sender, EventArgs e)
        {
            //pnlNav.Height = btnReset.Height;
            //pnlNav.Top = btnReset.Top;
            //pnlNav.Left = btnReset.Left;
            //btnReset.BackColor = Color.FromArgb(46, 51, 73);
            //btnHome.BackColor = Color.FromArgb(24, 29, 53);

            //FormManagement.openChildForm(UITools.forms["UAVReset"], pnlFormLoader);

            const string message = "Are you sure that you would like to RESET UAV !?";
            const string caption = "Form Closing";
            var result = MessageBox.Show(message, caption, MessageBoxButtons.YesNo,MessageBoxIcon.Question);

            if (result == DialogResult.Yes)
            {
                if(serialPort1.IsOpen)
                {
                    byte[] ResetMessage = new byte[3];
                    ResetMessage[0] = (byte)'U';
                    ResetMessage[1] = (byte)(Int16)3;
                    serialPort1.Write(ResetMessage, 0, 3);
                }
            }
        }
    }
}

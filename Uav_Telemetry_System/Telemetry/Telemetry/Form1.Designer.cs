
namespace Telemetry
{
    partial class Form1
    {
        /// <summary>
        /// Required designer variable.
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        /// Clean up any resources being used.
        /// </summary>
        /// <param name="disposing">true if managed resources should be disposed; otherwise, false.</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Windows Form Designer generated code

        /// <summary>
        /// Required method for Designer support - do not modify
        /// the contents of this method with the code editor.
        /// </summary>
        private void InitializeComponent()
        {
            System.ComponentModel.ComponentResourceManager resources = new System.ComponentModel.ComponentResourceManager(typeof(Form1));
            this.pnlControl = new System.Windows.Forms.Panel();
            this.btnReset = new System.Windows.Forms.Button();
            this.pnlNav = new System.Windows.Forms.Panel();
            this.btnSetPID = new System.Windows.Forms.Button();
            this.btnGraphics = new System.Windows.Forms.Button();
            this.btnRCControl = new System.Windows.Forms.Button();
            this.btnMission = new System.Windows.Forms.Button();
            this.btnHome = new System.Windows.Forms.Button();
            this.panel2 = new System.Windows.Forms.Panel();
            this.pictureBox1 = new System.Windows.Forms.PictureBox();
            this.pnlFormLoader = new System.Windows.Forms.Panel();
            this.tableLayoutPanel5 = new System.Windows.Forms.TableLayoutPanel();
            this.tableLayoutPanel4 = new System.Windows.Forms.TableLayoutPanel();
            this.comboBox1 = new System.Windows.Forms.ComboBox();
            this.tableLayoutPanel3 = new System.Windows.Forms.TableLayoutPanel();
            this.btnConnect = new System.Windows.Forms.Button();
            this.btnDisconnect = new System.Windows.Forms.Button();
            this.lblTitle = new System.Windows.Forms.Label();
            this.btnRefresh = new System.Windows.Forms.Button();
            this.tableLayoutPanel2 = new System.Windows.Forms.TableLayoutPanel();
            this.button1 = new System.Windows.Forms.Button();
            this.btnTM4 = new System.Windows.Forms.Button();
            this.btnTM3 = new System.Windows.Forms.Button();
            this.button3 = new System.Windows.Forms.Button();
            this.btnLidar = new System.Windows.Forms.Button();
            this.btnBattery = new System.Windows.Forms.Button();
            this.btnTM1 = new System.Windows.Forms.Button();
            this.btnTM2 = new System.Windows.Forms.Button();
            this.headingIndicator1 = new CS_WinForms_Ctrl_Heading_Indicator.HeadingIndicator();
            this.artifical_Horizon1 = new CS_WinForms_Ctrl_Artificial_Horizon.Artifical_Horizon();
            this.tableLayoutPanel1 = new System.Windows.Forms.TableLayoutPanel();
            this.button12 = new System.Windows.Forms.Button();
            this.button2 = new System.Windows.Forms.Button();
            this.button4 = new System.Windows.Forms.Button();
            this.btnAltitude = new System.Windows.Forms.Button();
            this.btnRoll = new System.Windows.Forms.Button();
            this.btnPitch = new System.Windows.Forms.Button();
            this.button10 = new System.Windows.Forms.Button();
            this.btnYaw = new System.Windows.Forms.Button();
            this.altimeter1 = new CS_WinForms_Ctrl_Altimeter.Altimeter();
            this.tableLayoutPanel6 = new System.Windows.Forms.TableLayoutPanel();
            this.pnlControl.SuspendLayout();
            this.panel2.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.pictureBox1)).BeginInit();
            this.tableLayoutPanel5.SuspendLayout();
            this.tableLayoutPanel4.SuspendLayout();
            this.tableLayoutPanel3.SuspendLayout();
            this.tableLayoutPanel2.SuspendLayout();
            this.tableLayoutPanel1.SuspendLayout();
            this.tableLayoutPanel6.SuspendLayout();
            this.SuspendLayout();
            // 
            // pnlControl
            // 
            this.pnlControl.BackColor = System.Drawing.Color.FromArgb(((int)(((byte)(24)))), ((int)(((byte)(29)))), ((int)(((byte)(53)))));
            this.pnlControl.Controls.Add(this.btnReset);
            this.pnlControl.Controls.Add(this.pnlNav);
            this.pnlControl.Controls.Add(this.btnSetPID);
            this.pnlControl.Controls.Add(this.btnGraphics);
            this.pnlControl.Controls.Add(this.btnRCControl);
            this.pnlControl.Controls.Add(this.btnMission);
            this.pnlControl.Controls.Add(this.btnHome);
            this.pnlControl.Controls.Add(this.panel2);
            this.pnlControl.Dock = System.Windows.Forms.DockStyle.Left;
            this.pnlControl.Location = new System.Drawing.Point(0, 0);
            this.pnlControl.Margin = new System.Windows.Forms.Padding(3, 2, 3, 2);
            this.pnlControl.Name = "pnlControl";
            this.pnlControl.Size = new System.Drawing.Size(200, 803);
            this.pnlControl.TabIndex = 0;
            // 
            // btnReset
            // 
            this.btnReset.Dock = System.Windows.Forms.DockStyle.Bottom;
            this.btnReset.FlatAppearance.BorderSize = 0;
            this.btnReset.FlatStyle = System.Windows.Forms.FlatStyle.Flat;
            this.btnReset.Font = new System.Drawing.Font("Nirmala UI", 10.8F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.btnReset.ForeColor = System.Drawing.Color.FromArgb(((int)(((byte)(0)))), ((int)(((byte)(126)))), ((int)(((byte)(249)))));
            this.btnReset.Image = global::Telemetry.Properties.Resources._008_settings_1;
            this.btnReset.Location = new System.Drawing.Point(0, 753);
            this.btnReset.Margin = new System.Windows.Forms.Padding(3, 2, 3, 2);
            this.btnReset.Name = "btnReset";
            this.btnReset.Size = new System.Drawing.Size(200, 50);
            this.btnReset.TabIndex = 5;
            this.btnReset.Text = "UAV RESET";
            this.btnReset.TextImageRelation = System.Windows.Forms.TextImageRelation.TextBeforeImage;
            this.btnReset.UseVisualStyleBackColor = true;
            this.btnReset.Click += new System.EventHandler(this.btnReset_Click);
            // 
            // pnlNav
            // 
            this.pnlNav.BackColor = System.Drawing.Color.FromArgb(((int)(((byte)(0)))), ((int)(((byte)(126)))), ((int)(((byte)(249)))));
            this.pnlNav.Location = new System.Drawing.Point(0, 226);
            this.pnlNav.Margin = new System.Windows.Forms.Padding(3, 2, 3, 2);
            this.pnlNav.Name = "pnlNav";
            this.pnlNav.Size = new System.Drawing.Size(5, 223);
            this.pnlNav.TabIndex = 1;
            // 
            // btnSetPID
            // 
            this.btnSetPID.Dock = System.Windows.Forms.DockStyle.Top;
            this.btnSetPID.FlatAppearance.BorderSize = 0;
            this.btnSetPID.FlatStyle = System.Windows.Forms.FlatStyle.Flat;
            this.btnSetPID.Font = new System.Drawing.Font("Nirmala UI", 10.8F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.btnSetPID.ForeColor = System.Drawing.Color.FromArgb(((int)(((byte)(0)))), ((int)(((byte)(126)))), ((int)(((byte)(249)))));
            this.btnSetPID.Image = global::Telemetry.Properties.Resources.setting;
            this.btnSetPID.Location = new System.Drawing.Point(0, 399);
            this.btnSetPID.Margin = new System.Windows.Forms.Padding(3, 2, 3, 2);
            this.btnSetPID.Name = "btnSetPID";
            this.btnSetPID.Size = new System.Drawing.Size(200, 50);
            this.btnSetPID.TabIndex = 4;
            this.btnSetPID.Text = "SET PID       ";
            this.btnSetPID.TextImageRelation = System.Windows.Forms.TextImageRelation.TextBeforeImage;
            this.btnSetPID.UseVisualStyleBackColor = true;
            this.btnSetPID.Click += new System.EventHandler(this.btnSetPID_Click);
            this.btnSetPID.Leave += new System.EventHandler(this.btnSetPID_Leave);
            // 
            // btnGraphics
            // 
            this.btnGraphics.Dock = System.Windows.Forms.DockStyle.Top;
            this.btnGraphics.FlatAppearance.BorderSize = 0;
            this.btnGraphics.FlatStyle = System.Windows.Forms.FlatStyle.Flat;
            this.btnGraphics.Font = new System.Drawing.Font("Nirmala UI", 10.8F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.btnGraphics.ForeColor = System.Drawing.Color.FromArgb(((int)(((byte)(0)))), ((int)(((byte)(126)))), ((int)(((byte)(249)))));
            this.btnGraphics.Image = global::Telemetry.Properties.Resources.growth__1_;
            this.btnGraphics.Location = new System.Drawing.Point(0, 349);
            this.btnGraphics.Margin = new System.Windows.Forms.Padding(3, 2, 3, 2);
            this.btnGraphics.Name = "btnGraphics";
            this.btnGraphics.Size = new System.Drawing.Size(200, 50);
            this.btnGraphics.TabIndex = 3;
            this.btnGraphics.Text = "GRAPHICS  ";
            this.btnGraphics.TextImageRelation = System.Windows.Forms.TextImageRelation.TextBeforeImage;
            this.btnGraphics.UseVisualStyleBackColor = true;
            this.btnGraphics.Click += new System.EventHandler(this.btnGraphics_Click);
            this.btnGraphics.Leave += new System.EventHandler(this.btnGraphics_Leave);
            // 
            // btnRCControl
            // 
            this.btnRCControl.Dock = System.Windows.Forms.DockStyle.Top;
            this.btnRCControl.FlatAppearance.BorderSize = 0;
            this.btnRCControl.FlatStyle = System.Windows.Forms.FlatStyle.Flat;
            this.btnRCControl.Font = new System.Drawing.Font("Nirmala UI", 10.8F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.btnRCControl.ForeColor = System.Drawing.Color.FromArgb(((int)(((byte)(0)))), ((int)(((byte)(126)))), ((int)(((byte)(249)))));
            this.btnRCControl.Image = global::Telemetry.Properties.Resources.icons8_joystick_32;
            this.btnRCControl.Location = new System.Drawing.Point(0, 299);
            this.btnRCControl.Margin = new System.Windows.Forms.Padding(3, 2, 3, 2);
            this.btnRCControl.Name = "btnRCControl";
            this.btnRCControl.Size = new System.Drawing.Size(200, 50);
            this.btnRCControl.TabIndex = 2;
            this.btnRCControl.Text = "RC CTRL     ";
            this.btnRCControl.TextImageRelation = System.Windows.Forms.TextImageRelation.TextBeforeImage;
            this.btnRCControl.UseVisualStyleBackColor = true;
            this.btnRCControl.Click += new System.EventHandler(this.btnRCControl_Click);
            this.btnRCControl.Leave += new System.EventHandler(this.btnRCControl_Leave);
            // 
            // btnMission
            // 
            this.btnMission.Dock = System.Windows.Forms.DockStyle.Top;
            this.btnMission.FlatAppearance.BorderSize = 0;
            this.btnMission.FlatStyle = System.Windows.Forms.FlatStyle.Flat;
            this.btnMission.Font = new System.Drawing.Font("Nirmala UI", 10.8F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.btnMission.ForeColor = System.Drawing.Color.FromArgb(((int)(((byte)(0)))), ((int)(((byte)(126)))), ((int)(((byte)(249)))));
            this.btnMission.Image = global::Telemetry.Properties.Resources.icons8_location_32;
            this.btnMission.Location = new System.Drawing.Point(0, 249);
            this.btnMission.Margin = new System.Windows.Forms.Padding(3, 2, 3, 2);
            this.btnMission.Name = "btnMission";
            this.btnMission.Size = new System.Drawing.Size(200, 50);
            this.btnMission.TabIndex = 1;
            this.btnMission.Text = "MISSION    ";
            this.btnMission.TextImageRelation = System.Windows.Forms.TextImageRelation.TextBeforeImage;
            this.btnMission.UseVisualStyleBackColor = true;
            this.btnMission.Click += new System.EventHandler(this.btnMission_Click);
            this.btnMission.Leave += new System.EventHandler(this.btnMission_Leave);
            // 
            // btnHome
            // 
            this.btnHome.Dock = System.Windows.Forms.DockStyle.Top;
            this.btnHome.FlatAppearance.BorderSize = 0;
            this.btnHome.FlatStyle = System.Windows.Forms.FlatStyle.Flat;
            this.btnHome.Font = new System.Drawing.Font("Nirmala UI", 10.8F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.btnHome.ForeColor = System.Drawing.Color.FromArgb(((int)(((byte)(0)))), ((int)(((byte)(126)))), ((int)(((byte)(249)))));
            this.btnHome.Image = global::Telemetry.Properties.Resources._001_home;
            this.btnHome.Location = new System.Drawing.Point(0, 199);
            this.btnHome.Margin = new System.Windows.Forms.Padding(3, 2, 3, 2);
            this.btnHome.Name = "btnHome";
            this.btnHome.Size = new System.Drawing.Size(200, 50);
            this.btnHome.TabIndex = 1;
            this.btnHome.Text = "HOME         ";
            this.btnHome.TextImageRelation = System.Windows.Forms.TextImageRelation.TextBeforeImage;
            this.btnHome.UseVisualStyleBackColor = true;
            this.btnHome.Click += new System.EventHandler(this.btnHome_Click);
            this.btnHome.Leave += new System.EventHandler(this.btnHome_Leave);
            // 
            // panel2
            // 
            this.panel2.Controls.Add(this.pictureBox1);
            this.panel2.Dock = System.Windows.Forms.DockStyle.Top;
            this.panel2.Location = new System.Drawing.Point(0, 0);
            this.panel2.Margin = new System.Windows.Forms.Padding(3, 2, 3, 2);
            this.panel2.Name = "panel2";
            this.panel2.Size = new System.Drawing.Size(200, 199);
            this.panel2.TabIndex = 1;
            // 
            // pictureBox1
            // 
            this.pictureBox1.Image = global::Telemetry.Properties.Resources.A__MAVİ_1;
            this.pictureBox1.Location = new System.Drawing.Point(25, 25);
            this.pictureBox1.Margin = new System.Windows.Forms.Padding(3, 2, 3, 2);
            this.pictureBox1.Name = "pictureBox1";
            this.pictureBox1.Size = new System.Drawing.Size(149, 150);
            this.pictureBox1.SizeMode = System.Windows.Forms.PictureBoxSizeMode.Zoom;
            this.pictureBox1.TabIndex = 0;
            this.pictureBox1.TabStop = false;
            // 
            // pnlFormLoader
            // 
            this.pnlFormLoader.Dock = System.Windows.Forms.DockStyle.Fill;
            this.pnlFormLoader.Location = new System.Drawing.Point(3, 209);
            this.pnlFormLoader.Margin = new System.Windows.Forms.Padding(3, 2, 3, 2);
            this.pnlFormLoader.Name = "pnlFormLoader";
            this.pnlFormLoader.Size = new System.Drawing.Size(1346, 592);
            this.pnlFormLoader.TabIndex = 2;
            // 
            // tableLayoutPanel5
            // 
            this.tableLayoutPanel5.ColumnCount = 7;
            this.tableLayoutPanel5.ColumnStyles.Add(new System.Windows.Forms.ColumnStyle(System.Windows.Forms.SizeType.Absolute, 200F));
            this.tableLayoutPanel5.ColumnStyles.Add(new System.Windows.Forms.ColumnStyle(System.Windows.Forms.SizeType.Absolute, 300F));
            this.tableLayoutPanel5.ColumnStyles.Add(new System.Windows.Forms.ColumnStyle(System.Windows.Forms.SizeType.Absolute, 200F));
            this.tableLayoutPanel5.ColumnStyles.Add(new System.Windows.Forms.ColumnStyle(System.Windows.Forms.SizeType.Absolute, 300F));
            this.tableLayoutPanel5.ColumnStyles.Add(new System.Windows.Forms.ColumnStyle(System.Windows.Forms.SizeType.Absolute, 200F));
            this.tableLayoutPanel5.ColumnStyles.Add(new System.Windows.Forms.ColumnStyle(System.Windows.Forms.SizeType.Absolute, 130F));
            this.tableLayoutPanel5.ColumnStyles.Add(new System.Windows.Forms.ColumnStyle(System.Windows.Forms.SizeType.Absolute, 20F));
            this.tableLayoutPanel5.Controls.Add(this.tableLayoutPanel4, 5, 0);
            this.tableLayoutPanel5.Controls.Add(this.tableLayoutPanel2, 3, 0);
            this.tableLayoutPanel5.Controls.Add(this.headingIndicator1, 4, 0);
            this.tableLayoutPanel5.Controls.Add(this.artifical_Horizon1, 0, 0);
            this.tableLayoutPanel5.Controls.Add(this.tableLayoutPanel1, 1, 0);
            this.tableLayoutPanel5.Controls.Add(this.altimeter1, 2, 0);
            this.tableLayoutPanel5.Dock = System.Windows.Forms.DockStyle.Fill;
            this.tableLayoutPanel5.Location = new System.Drawing.Point(3, 3);
            this.tableLayoutPanel5.Name = "tableLayoutPanel5";
            this.tableLayoutPanel5.RowCount = 1;
            this.tableLayoutPanel5.RowStyles.Add(new System.Windows.Forms.RowStyle(System.Windows.Forms.SizeType.Percent, 100F));
            this.tableLayoutPanel5.Size = new System.Drawing.Size(1346, 201);
            this.tableLayoutPanel5.TabIndex = 20;
            // 
            // tableLayoutPanel4
            // 
            this.tableLayoutPanel4.CellBorderStyle = System.Windows.Forms.TableLayoutPanelCellBorderStyle.OutsetDouble;
            this.tableLayoutPanel4.ColumnCount = 1;
            this.tableLayoutPanel4.ColumnStyles.Add(new System.Windows.Forms.ColumnStyle(System.Windows.Forms.SizeType.Percent, 100F));
            this.tableLayoutPanel4.Controls.Add(this.comboBox1, 0, 0);
            this.tableLayoutPanel4.Controls.Add(this.tableLayoutPanel3, 0, 2);
            this.tableLayoutPanel4.Controls.Add(this.lblTitle, 0, 3);
            this.tableLayoutPanel4.Controls.Add(this.btnRefresh, 0, 1);
            this.tableLayoutPanel4.Dock = System.Windows.Forms.DockStyle.Fill;
            this.tableLayoutPanel4.Location = new System.Drawing.Point(1203, 3);
            this.tableLayoutPanel4.Name = "tableLayoutPanel4";
            this.tableLayoutPanel4.RowCount = 4;
            this.tableLayoutPanel4.RowStyles.Add(new System.Windows.Forms.RowStyle(System.Windows.Forms.SizeType.Percent, 27F));
            this.tableLayoutPanel4.RowStyles.Add(new System.Windows.Forms.RowStyle(System.Windows.Forms.SizeType.Percent, 27F));
            this.tableLayoutPanel4.RowStyles.Add(new System.Windows.Forms.RowStyle(System.Windows.Forms.SizeType.Percent, 27F));
            this.tableLayoutPanel4.RowStyles.Add(new System.Windows.Forms.RowStyle(System.Windows.Forms.SizeType.Percent, 19F));
            this.tableLayoutPanel4.Size = new System.Drawing.Size(124, 195);
            this.tableLayoutPanel4.TabIndex = 21;
            // 
            // comboBox1
            // 
            this.comboBox1.BackColor = System.Drawing.Color.White;
            this.comboBox1.Cursor = System.Windows.Forms.Cursors.Hand;
            this.comboBox1.Dock = System.Windows.Forms.DockStyle.Fill;
            this.comboBox1.FlatStyle = System.Windows.Forms.FlatStyle.Popup;
            this.comboBox1.Font = new System.Drawing.Font("Microsoft Sans Serif", 8.8F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(162)));
            this.comboBox1.ForeColor = System.Drawing.Color.FromArgb(((int)(((byte)(0)))), ((int)(((byte)(126)))), ((int)(((byte)(249)))));
            this.comboBox1.FormattingEnabled = true;
            this.comboBox1.Location = new System.Drawing.Point(6, 5);
            this.comboBox1.Margin = new System.Windows.Forms.Padding(3, 2, 3, 2);
            this.comboBox1.Name = "comboBox1";
            this.comboBox1.Size = new System.Drawing.Size(112, 26);
            this.comboBox1.TabIndex = 11;
            // 
            // tableLayoutPanel3
            // 
            this.tableLayoutPanel3.ColumnCount = 2;
            this.tableLayoutPanel3.ColumnStyles.Add(new System.Windows.Forms.ColumnStyle(System.Windows.Forms.SizeType.Percent, 50F));
            this.tableLayoutPanel3.ColumnStyles.Add(new System.Windows.Forms.ColumnStyle(System.Windows.Forms.SizeType.Percent, 50F));
            this.tableLayoutPanel3.Controls.Add(this.btnConnect, 0, 0);
            this.tableLayoutPanel3.Controls.Add(this.btnDisconnect, 1, 0);
            this.tableLayoutPanel3.Dock = System.Windows.Forms.DockStyle.Fill;
            this.tableLayoutPanel3.Location = new System.Drawing.Point(6, 108);
            this.tableLayoutPanel3.Name = "tableLayoutPanel3";
            this.tableLayoutPanel3.RowCount = 1;
            this.tableLayoutPanel3.RowStyles.Add(new System.Windows.Forms.RowStyle(System.Windows.Forms.SizeType.Percent, 100F));
            this.tableLayoutPanel3.Size = new System.Drawing.Size(112, 42);
            this.tableLayoutPanel3.TabIndex = 22;
            // 
            // btnConnect
            // 
            this.btnConnect.BackColor = System.Drawing.SystemColors.GrayText;
            this.btnConnect.Dock = System.Windows.Forms.DockStyle.Fill;
            this.btnConnect.Location = new System.Drawing.Point(3, 2);
            this.btnConnect.Margin = new System.Windows.Forms.Padding(3, 2, 3, 2);
            this.btnConnect.Name = "btnConnect";
            this.btnConnect.Size = new System.Drawing.Size(50, 38);
            this.btnConnect.TabIndex = 14;
            this.btnConnect.UseVisualStyleBackColor = false;
            this.btnConnect.Click += new System.EventHandler(this.btnConnect_Click);
            // 
            // btnDisconnect
            // 
            this.btnDisconnect.BackColor = System.Drawing.Color.Red;
            this.btnDisconnect.Dock = System.Windows.Forms.DockStyle.Fill;
            this.btnDisconnect.Location = new System.Drawing.Point(59, 2);
            this.btnDisconnect.Margin = new System.Windows.Forms.Padding(3, 2, 3, 2);
            this.btnDisconnect.Name = "btnDisconnect";
            this.btnDisconnect.Size = new System.Drawing.Size(50, 38);
            this.btnDisconnect.TabIndex = 15;
            this.btnDisconnect.UseVisualStyleBackColor = false;
            this.btnDisconnect.Click += new System.EventHandler(this.btnDisconnect_Click);
            // 
            // lblTitle
            // 
            this.lblTitle.AutoSize = true;
            this.lblTitle.Dock = System.Windows.Forms.DockStyle.Fill;
            this.lblTitle.Font = new System.Drawing.Font("Nirmala UI", 11F, System.Drawing.FontStyle.Bold);
            this.lblTitle.ForeColor = System.Drawing.Color.White;
            this.lblTitle.Location = new System.Drawing.Point(6, 156);
            this.lblTitle.Name = "lblTitle";
            this.lblTitle.Size = new System.Drawing.Size(112, 36);
            this.lblTitle.TabIndex = 3;
            this.lblTitle.Text = "   ON        OFF  ";
            // 
            // btnRefresh
            // 
            this.btnRefresh.BackColor = System.Drawing.Color.FromArgb(((int)(((byte)(46)))), ((int)(((byte)(51)))), ((int)(((byte)(73)))));
            this.btnRefresh.Dock = System.Windows.Forms.DockStyle.Fill;
            this.btnRefresh.FlatStyle = System.Windows.Forms.FlatStyle.Flat;
            this.btnRefresh.Font = new System.Drawing.Font("Times New Roman", 10.8F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(162)));
            this.btnRefresh.ForeColor = System.Drawing.Color.White;
            this.btnRefresh.Location = new System.Drawing.Point(6, 56);
            this.btnRefresh.Margin = new System.Windows.Forms.Padding(3, 2, 3, 2);
            this.btnRefresh.Name = "btnRefresh";
            this.btnRefresh.Size = new System.Drawing.Size(112, 44);
            this.btnRefresh.TabIndex = 18;
            this.btnRefresh.Text = "Refresh";
            this.btnRefresh.UseVisualStyleBackColor = false;
            this.btnRefresh.Click += new System.EventHandler(this.btnRefresh_Click);
            // 
            // tableLayoutPanel2
            // 
            this.tableLayoutPanel2.CellBorderStyle = System.Windows.Forms.TableLayoutPanelCellBorderStyle.Inset;
            this.tableLayoutPanel2.ColumnCount = 2;
            this.tableLayoutPanel2.ColumnStyles.Add(new System.Windows.Forms.ColumnStyle(System.Windows.Forms.SizeType.Percent, 50F));
            this.tableLayoutPanel2.ColumnStyles.Add(new System.Windows.Forms.ColumnStyle(System.Windows.Forms.SizeType.Percent, 50F));
            this.tableLayoutPanel2.Controls.Add(this.button1, 0, 0);
            this.tableLayoutPanel2.Controls.Add(this.btnTM4, 1, 3);
            this.tableLayoutPanel2.Controls.Add(this.btnTM3, 1, 2);
            this.tableLayoutPanel2.Controls.Add(this.button3, 0, 1);
            this.tableLayoutPanel2.Controls.Add(this.btnLidar, 1, 0);
            this.tableLayoutPanel2.Controls.Add(this.btnBattery, 1, 1);
            this.tableLayoutPanel2.Controls.Add(this.btnTM1, 0, 2);
            this.tableLayoutPanel2.Controls.Add(this.btnTM2, 0, 3);
            this.tableLayoutPanel2.Dock = System.Windows.Forms.DockStyle.Fill;
            this.tableLayoutPanel2.Location = new System.Drawing.Point(703, 3);
            this.tableLayoutPanel2.Name = "tableLayoutPanel2";
            this.tableLayoutPanel2.RowCount = 4;
            this.tableLayoutPanel2.RowStyles.Add(new System.Windows.Forms.RowStyle(System.Windows.Forms.SizeType.Percent, 25F));
            this.tableLayoutPanel2.RowStyles.Add(new System.Windows.Forms.RowStyle(System.Windows.Forms.SizeType.Percent, 25F));
            this.tableLayoutPanel2.RowStyles.Add(new System.Windows.Forms.RowStyle(System.Windows.Forms.SizeType.Percent, 25F));
            this.tableLayoutPanel2.RowStyles.Add(new System.Windows.Forms.RowStyle(System.Windows.Forms.SizeType.Percent, 25F));
            this.tableLayoutPanel2.RowStyles.Add(new System.Windows.Forms.RowStyle(System.Windows.Forms.SizeType.Absolute, 20F));
            this.tableLayoutPanel2.Size = new System.Drawing.Size(294, 195);
            this.tableLayoutPanel2.TabIndex = 1;
            // 
            // button1
            // 
            this.button1.BackColor = System.Drawing.Color.FromArgb(((int)(((byte)(46)))), ((int)(((byte)(51)))), ((int)(((byte)(73)))));
            this.button1.Dock = System.Windows.Forms.DockStyle.Fill;
            this.button1.FlatStyle = System.Windows.Forms.FlatStyle.Flat;
            this.button1.Font = new System.Drawing.Font("Times New Roman", 11.2F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(162)));
            this.button1.ForeColor = System.Drawing.Color.FromArgb(((int)(((byte)(0)))), ((int)(((byte)(126)))), ((int)(((byte)(249)))));
            this.button1.Location = new System.Drawing.Point(5, 4);
            this.button1.Margin = new System.Windows.Forms.Padding(3, 2, 3, 2);
            this.button1.Name = "button1";
            this.button1.Size = new System.Drawing.Size(138, 42);
            this.button1.TabIndex = 1;
            this.button1.Text = "LIDAR";
            this.button1.UseVisualStyleBackColor = false;
            // 
            // btnTM4
            // 
            this.btnTM4.BackColor = System.Drawing.Color.FromArgb(((int)(((byte)(46)))), ((int)(((byte)(51)))), ((int)(((byte)(73)))));
            this.btnTM4.Dock = System.Windows.Forms.DockStyle.Fill;
            this.btnTM4.FlatStyle = System.Windows.Forms.FlatStyle.Flat;
            this.btnTM4.Font = new System.Drawing.Font("Times New Roman", 11.2F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(162)));
            this.btnTM4.ForeColor = System.Drawing.Color.FromArgb(((int)(((byte)(249)))), ((int)(((byte)(226)))), ((int)(((byte)(249)))));
            this.btnTM4.Location = new System.Drawing.Point(151, 148);
            this.btnTM4.Margin = new System.Windows.Forms.Padding(3, 2, 3, 2);
            this.btnTM4.Name = "btnTM4";
            this.btnTM4.Size = new System.Drawing.Size(138, 43);
            this.btnTM4.TabIndex = 0;
            this.btnTM4.Text = "-";
            this.btnTM4.UseVisualStyleBackColor = false;
            // 
            // btnTM3
            // 
            this.btnTM3.BackColor = System.Drawing.Color.FromArgb(((int)(((byte)(46)))), ((int)(((byte)(51)))), ((int)(((byte)(73)))));
            this.btnTM3.Dock = System.Windows.Forms.DockStyle.Fill;
            this.btnTM3.FlatStyle = System.Windows.Forms.FlatStyle.Flat;
            this.btnTM3.Font = new System.Drawing.Font("Times New Roman", 11.2F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(162)));
            this.btnTM3.ForeColor = System.Drawing.Color.FromArgb(((int)(((byte)(249)))), ((int)(((byte)(226)))), ((int)(((byte)(249)))));
            this.btnTM3.Location = new System.Drawing.Point(151, 100);
            this.btnTM3.Margin = new System.Windows.Forms.Padding(3, 2, 3, 2);
            this.btnTM3.Name = "btnTM3";
            this.btnTM3.Size = new System.Drawing.Size(138, 42);
            this.btnTM3.TabIndex = 11;
            this.btnTM3.Text = "-";
            this.btnTM3.UseVisualStyleBackColor = false;
            // 
            // button3
            // 
            this.button3.BackColor = System.Drawing.Color.FromArgb(((int)(((byte)(46)))), ((int)(((byte)(51)))), ((int)(((byte)(73)))));
            this.button3.Dock = System.Windows.Forms.DockStyle.Fill;
            this.button3.FlatStyle = System.Windows.Forms.FlatStyle.Flat;
            this.button3.Font = new System.Drawing.Font("Times New Roman", 11.2F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(162)));
            this.button3.ForeColor = System.Drawing.Color.FromArgb(((int)(((byte)(0)))), ((int)(((byte)(126)))), ((int)(((byte)(249)))));
            this.button3.Location = new System.Drawing.Point(5, 52);
            this.button3.Margin = new System.Windows.Forms.Padding(3, 2, 3, 2);
            this.button3.Name = "button3";
            this.button3.Size = new System.Drawing.Size(138, 42);
            this.button3.TabIndex = 2;
            this.button3.Text = "BATTERY";
            this.button3.UseVisualStyleBackColor = false;
            // 
            // btnLidar
            // 
            this.btnLidar.BackColor = System.Drawing.Color.FromArgb(((int)(((byte)(46)))), ((int)(((byte)(51)))), ((int)(((byte)(73)))));
            this.btnLidar.Dock = System.Windows.Forms.DockStyle.Fill;
            this.btnLidar.FlatStyle = System.Windows.Forms.FlatStyle.Flat;
            this.btnLidar.Font = new System.Drawing.Font("Times New Roman", 11.2F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(162)));
            this.btnLidar.ForeColor = System.Drawing.Color.FromArgb(((int)(((byte)(249)))), ((int)(((byte)(226)))), ((int)(((byte)(249)))));
            this.btnLidar.Location = new System.Drawing.Point(151, 4);
            this.btnLidar.Margin = new System.Windows.Forms.Padding(3, 2, 3, 2);
            this.btnLidar.Name = "btnLidar";
            this.btnLidar.Size = new System.Drawing.Size(138, 42);
            this.btnLidar.TabIndex = 4;
            this.btnLidar.Text = "-";
            this.btnLidar.UseVisualStyleBackColor = false;
            // 
            // btnBattery
            // 
            this.btnBattery.BackColor = System.Drawing.Color.FromArgb(((int)(((byte)(46)))), ((int)(((byte)(51)))), ((int)(((byte)(73)))));
            this.btnBattery.Dock = System.Windows.Forms.DockStyle.Fill;
            this.btnBattery.FlatStyle = System.Windows.Forms.FlatStyle.Flat;
            this.btnBattery.Font = new System.Drawing.Font("Times New Roman", 11.2F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(162)));
            this.btnBattery.ForeColor = System.Drawing.Color.FromArgb(((int)(((byte)(249)))), ((int)(((byte)(226)))), ((int)(((byte)(249)))));
            this.btnBattery.Location = new System.Drawing.Point(151, 52);
            this.btnBattery.Margin = new System.Windows.Forms.Padding(3, 2, 3, 2);
            this.btnBattery.Name = "btnBattery";
            this.btnBattery.Size = new System.Drawing.Size(138, 42);
            this.btnBattery.TabIndex = 3;
            this.btnBattery.Text = "-";
            this.btnBattery.UseVisualStyleBackColor = false;
            // 
            // btnTM1
            // 
            this.btnTM1.BackColor = System.Drawing.Color.FromArgb(((int)(((byte)(46)))), ((int)(((byte)(51)))), ((int)(((byte)(73)))));
            this.btnTM1.Dock = System.Windows.Forms.DockStyle.Fill;
            this.btnTM1.FlatStyle = System.Windows.Forms.FlatStyle.Flat;
            this.btnTM1.Font = new System.Drawing.Font("Times New Roman", 11.2F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(162)));
            this.btnTM1.ForeColor = System.Drawing.Color.FromArgb(((int)(((byte)(249)))), ((int)(((byte)(226)))), ((int)(((byte)(249)))));
            this.btnTM1.Location = new System.Drawing.Point(5, 100);
            this.btnTM1.Margin = new System.Windows.Forms.Padding(3, 2, 3, 2);
            this.btnTM1.Name = "btnTM1";
            this.btnTM1.Size = new System.Drawing.Size(138, 42);
            this.btnTM1.TabIndex = 12;
            this.btnTM1.Text = "-";
            this.btnTM1.UseVisualStyleBackColor = false;
            // 
            // btnTM2
            // 
            this.btnTM2.BackColor = System.Drawing.Color.FromArgb(((int)(((byte)(46)))), ((int)(((byte)(51)))), ((int)(((byte)(73)))));
            this.btnTM2.Dock = System.Windows.Forms.DockStyle.Fill;
            this.btnTM2.FlatStyle = System.Windows.Forms.FlatStyle.Flat;
            this.btnTM2.Font = new System.Drawing.Font("Times New Roman", 11.2F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(162)));
            this.btnTM2.ForeColor = System.Drawing.Color.FromArgb(((int)(((byte)(249)))), ((int)(((byte)(226)))), ((int)(((byte)(249)))));
            this.btnTM2.Location = new System.Drawing.Point(5, 148);
            this.btnTM2.Margin = new System.Windows.Forms.Padding(3, 2, 3, 2);
            this.btnTM2.Name = "btnTM2";
            this.btnTM2.Size = new System.Drawing.Size(138, 43);
            this.btnTM2.TabIndex = 0;
            this.btnTM2.Text = "-";
            this.btnTM2.UseVisualStyleBackColor = false;
            // 
            // headingIndicator1
            // 
            this.headingIndicator1.Dock = System.Windows.Forms.DockStyle.Fill;
            this.headingIndicator1.Heading = 0;
            this.headingIndicator1.Location = new System.Drawing.Point(1005, 5);
            this.headingIndicator1.Margin = new System.Windows.Forms.Padding(5);
            this.headingIndicator1.Name = "headingIndicator1";
            this.headingIndicator1.Size = new System.Drawing.Size(190, 191);
            this.headingIndicator1.TabIndex = 6;
            // 
            // artifical_Horizon1
            // 
            this.artifical_Horizon1.Dock = System.Windows.Forms.DockStyle.Fill;
            this.artifical_Horizon1.Location = new System.Drawing.Point(5, 5);
            this.artifical_Horizon1.Margin = new System.Windows.Forms.Padding(5);
            this.artifical_Horizon1.Name = "artifical_Horizon1";
            this.artifical_Horizon1.PitchAngle = 0D;
            this.artifical_Horizon1.RollAngle = 0D;
            this.artifical_Horizon1.Size = new System.Drawing.Size(190, 191);
            this.artifical_Horizon1.TabIndex = 7;
            // 
            // tableLayoutPanel1
            // 
            this.tableLayoutPanel1.CellBorderStyle = System.Windows.Forms.TableLayoutPanelCellBorderStyle.Inset;
            this.tableLayoutPanel1.ColumnCount = 2;
            this.tableLayoutPanel1.ColumnStyles.Add(new System.Windows.Forms.ColumnStyle(System.Windows.Forms.SizeType.Percent, 50F));
            this.tableLayoutPanel1.ColumnStyles.Add(new System.Windows.Forms.ColumnStyle(System.Windows.Forms.SizeType.Percent, 50F));
            this.tableLayoutPanel1.Controls.Add(this.button12, 0, 3);
            this.tableLayoutPanel1.Controls.Add(this.button2, 0, 0);
            this.tableLayoutPanel1.Controls.Add(this.button4, 0, 1);
            this.tableLayoutPanel1.Controls.Add(this.btnAltitude, 1, 3);
            this.tableLayoutPanel1.Controls.Add(this.btnRoll, 1, 0);
            this.tableLayoutPanel1.Controls.Add(this.btnPitch, 1, 1);
            this.tableLayoutPanel1.Controls.Add(this.button10, 0, 2);
            this.tableLayoutPanel1.Controls.Add(this.btnYaw, 1, 2);
            this.tableLayoutPanel1.Dock = System.Windows.Forms.DockStyle.Fill;
            this.tableLayoutPanel1.Location = new System.Drawing.Point(203, 3);
            this.tableLayoutPanel1.Name = "tableLayoutPanel1";
            this.tableLayoutPanel1.RowCount = 4;
            this.tableLayoutPanel1.RowStyles.Add(new System.Windows.Forms.RowStyle(System.Windows.Forms.SizeType.Percent, 25F));
            this.tableLayoutPanel1.RowStyles.Add(new System.Windows.Forms.RowStyle(System.Windows.Forms.SizeType.Percent, 25F));
            this.tableLayoutPanel1.RowStyles.Add(new System.Windows.Forms.RowStyle(System.Windows.Forms.SizeType.Percent, 25F));
            this.tableLayoutPanel1.RowStyles.Add(new System.Windows.Forms.RowStyle(System.Windows.Forms.SizeType.Percent, 25F));
            this.tableLayoutPanel1.RowStyles.Add(new System.Windows.Forms.RowStyle(System.Windows.Forms.SizeType.Absolute, 20F));
            this.tableLayoutPanel1.Size = new System.Drawing.Size(294, 195);
            this.tableLayoutPanel1.TabIndex = 27;
            // 
            // button12
            // 
            this.button12.BackColor = System.Drawing.Color.FromArgb(((int)(((byte)(46)))), ((int)(((byte)(51)))), ((int)(((byte)(73)))));
            this.button12.Dock = System.Windows.Forms.DockStyle.Fill;
            this.button12.FlatStyle = System.Windows.Forms.FlatStyle.Flat;
            this.button12.Font = new System.Drawing.Font("Times New Roman", 11.2F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(162)));
            this.button12.ForeColor = System.Drawing.Color.FromArgb(((int)(((byte)(0)))), ((int)(((byte)(126)))), ((int)(((byte)(249)))));
            this.button12.Location = new System.Drawing.Point(5, 148);
            this.button12.Margin = new System.Windows.Forms.Padding(3, 2, 3, 2);
            this.button12.Name = "button12";
            this.button12.Size = new System.Drawing.Size(138, 43);
            this.button12.TabIndex = 4;
            this.button12.Text = "ALTITUDE";
            this.button12.UseVisualStyleBackColor = false;
            // 
            // button2
            // 
            this.button2.BackColor = System.Drawing.Color.FromArgb(((int)(((byte)(46)))), ((int)(((byte)(51)))), ((int)(((byte)(73)))));
            this.button2.Dock = System.Windows.Forms.DockStyle.Fill;
            this.button2.FlatStyle = System.Windows.Forms.FlatStyle.Flat;
            this.button2.Font = new System.Drawing.Font("Times New Roman", 11.2F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(162)));
            this.button2.ForeColor = System.Drawing.Color.FromArgb(((int)(((byte)(0)))), ((int)(((byte)(126)))), ((int)(((byte)(249)))));
            this.button2.Location = new System.Drawing.Point(5, 4);
            this.button2.Margin = new System.Windows.Forms.Padding(3, 2, 3, 2);
            this.button2.Name = "button2";
            this.button2.Size = new System.Drawing.Size(138, 42);
            this.button2.TabIndex = 0;
            this.button2.Text = "ROLL";
            this.button2.UseVisualStyleBackColor = false;
            // 
            // button4
            // 
            this.button4.BackColor = System.Drawing.Color.FromArgb(((int)(((byte)(46)))), ((int)(((byte)(51)))), ((int)(((byte)(73)))));
            this.button4.Dock = System.Windows.Forms.DockStyle.Fill;
            this.button4.FlatStyle = System.Windows.Forms.FlatStyle.Flat;
            this.button4.Font = new System.Drawing.Font("Times New Roman", 11.2F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(162)));
            this.button4.ForeColor = System.Drawing.Color.FromArgb(((int)(((byte)(0)))), ((int)(((byte)(126)))), ((int)(((byte)(249)))));
            this.button4.Location = new System.Drawing.Point(5, 52);
            this.button4.Margin = new System.Windows.Forms.Padding(3, 2, 3, 2);
            this.button4.Name = "button4";
            this.button4.Size = new System.Drawing.Size(138, 42);
            this.button4.TabIndex = 0;
            this.button4.Text = "PITCH";
            this.button4.UseVisualStyleBackColor = false;
            // 
            // btnAltitude
            // 
            this.btnAltitude.BackColor = System.Drawing.Color.FromArgb(((int)(((byte)(46)))), ((int)(((byte)(51)))), ((int)(((byte)(73)))));
            this.btnAltitude.Dock = System.Windows.Forms.DockStyle.Fill;
            this.btnAltitude.FlatStyle = System.Windows.Forms.FlatStyle.Flat;
            this.btnAltitude.Font = new System.Drawing.Font("Times New Roman", 11.2F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(162)));
            this.btnAltitude.ForeColor = System.Drawing.Color.FromArgb(((int)(((byte)(249)))), ((int)(((byte)(226)))), ((int)(((byte)(249)))));
            this.btnAltitude.Location = new System.Drawing.Point(151, 148);
            this.btnAltitude.Margin = new System.Windows.Forms.Padding(3, 2, 3, 2);
            this.btnAltitude.Name = "btnAltitude";
            this.btnAltitude.Size = new System.Drawing.Size(138, 43);
            this.btnAltitude.TabIndex = 8;
            this.btnAltitude.Text = "-";
            this.btnAltitude.UseVisualStyleBackColor = false;
            // 
            // btnRoll
            // 
            this.btnRoll.BackColor = System.Drawing.Color.FromArgb(((int)(((byte)(46)))), ((int)(((byte)(51)))), ((int)(((byte)(73)))));
            this.btnRoll.Dock = System.Windows.Forms.DockStyle.Fill;
            this.btnRoll.FlatStyle = System.Windows.Forms.FlatStyle.Flat;
            this.btnRoll.Font = new System.Drawing.Font("Times New Roman", 11.2F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(162)));
            this.btnRoll.ForeColor = System.Drawing.Color.FromArgb(((int)(((byte)(249)))), ((int)(((byte)(226)))), ((int)(((byte)(249)))));
            this.btnRoll.Location = new System.Drawing.Point(151, 4);
            this.btnRoll.Margin = new System.Windows.Forms.Padding(3, 2, 3, 2);
            this.btnRoll.Name = "btnRoll";
            this.btnRoll.Size = new System.Drawing.Size(138, 42);
            this.btnRoll.TabIndex = 0;
            this.btnRoll.Text = "-";
            this.btnRoll.UseVisualStyleBackColor = false;
            // 
            // btnPitch
            // 
            this.btnPitch.BackColor = System.Drawing.Color.FromArgb(((int)(((byte)(46)))), ((int)(((byte)(51)))), ((int)(((byte)(73)))));
            this.btnPitch.Dock = System.Windows.Forms.DockStyle.Fill;
            this.btnPitch.FlatStyle = System.Windows.Forms.FlatStyle.Flat;
            this.btnPitch.Font = new System.Drawing.Font("Times New Roman", 11.2F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(162)));
            this.btnPitch.ForeColor = System.Drawing.Color.FromArgb(((int)(((byte)(249)))), ((int)(((byte)(226)))), ((int)(((byte)(249)))));
            this.btnPitch.Location = new System.Drawing.Point(151, 52);
            this.btnPitch.Margin = new System.Windows.Forms.Padding(3, 2, 3, 2);
            this.btnPitch.Name = "btnPitch";
            this.btnPitch.Size = new System.Drawing.Size(138, 42);
            this.btnPitch.TabIndex = 0;
            this.btnPitch.Text = "-";
            this.btnPitch.UseVisualStyleBackColor = false;
            // 
            // button10
            // 
            this.button10.BackColor = System.Drawing.Color.FromArgb(((int)(((byte)(46)))), ((int)(((byte)(51)))), ((int)(((byte)(73)))));
            this.button10.Dock = System.Windows.Forms.DockStyle.Fill;
            this.button10.FlatStyle = System.Windows.Forms.FlatStyle.Flat;
            this.button10.Font = new System.Drawing.Font("Times New Roman", 11.2F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(162)));
            this.button10.ForeColor = System.Drawing.Color.FromArgb(((int)(((byte)(0)))), ((int)(((byte)(126)))), ((int)(((byte)(249)))));
            this.button10.Location = new System.Drawing.Point(5, 100);
            this.button10.Margin = new System.Windows.Forms.Padding(3, 2, 3, 2);
            this.button10.Name = "button10";
            this.button10.Size = new System.Drawing.Size(138, 42);
            this.button10.TabIndex = 10;
            this.button10.Text = "YAW";
            this.button10.UseVisualStyleBackColor = false;
            // 
            // btnYaw
            // 
            this.btnYaw.BackColor = System.Drawing.Color.FromArgb(((int)(((byte)(46)))), ((int)(((byte)(51)))), ((int)(((byte)(73)))));
            this.btnYaw.Dock = System.Windows.Forms.DockStyle.Fill;
            this.btnYaw.FlatStyle = System.Windows.Forms.FlatStyle.Flat;
            this.btnYaw.Font = new System.Drawing.Font("Times New Roman", 11.2F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(162)));
            this.btnYaw.ForeColor = System.Drawing.Color.FromArgb(((int)(((byte)(249)))), ((int)(((byte)(226)))), ((int)(((byte)(249)))));
            this.btnYaw.Location = new System.Drawing.Point(151, 100);
            this.btnYaw.Margin = new System.Windows.Forms.Padding(3, 2, 3, 2);
            this.btnYaw.Name = "btnYaw";
            this.btnYaw.Size = new System.Drawing.Size(138, 42);
            this.btnYaw.TabIndex = 6;
            this.btnYaw.Text = "-";
            this.btnYaw.UseVisualStyleBackColor = false;
            // 
            // altimeter1
            // 
            this.altimeter1.Altitude = 0;
            this.altimeter1.Dock = System.Windows.Forms.DockStyle.Fill;
            this.altimeter1.Location = new System.Drawing.Point(504, 4);
            this.altimeter1.Margin = new System.Windows.Forms.Padding(4, 4, 4, 4);
            this.altimeter1.Name = "altimeter1";
            this.altimeter1.Size = new System.Drawing.Size(192, 193);
            this.altimeter1.TabIndex = 28;
            // 
            // tableLayoutPanel6
            // 
            this.tableLayoutPanel6.ColumnCount = 1;
            this.tableLayoutPanel6.ColumnStyles.Add(new System.Windows.Forms.ColumnStyle(System.Windows.Forms.SizeType.Percent, 50F));
            this.tableLayoutPanel6.Controls.Add(this.tableLayoutPanel5, 0, 0);
            this.tableLayoutPanel6.Controls.Add(this.pnlFormLoader, 0, 1);
            this.tableLayoutPanel6.Dock = System.Windows.Forms.DockStyle.Fill;
            this.tableLayoutPanel6.Location = new System.Drawing.Point(200, 0);
            this.tableLayoutPanel6.Name = "tableLayoutPanel6";
            this.tableLayoutPanel6.RowCount = 2;
            this.tableLayoutPanel6.RowStyles.Add(new System.Windows.Forms.RowStyle(System.Windows.Forms.SizeType.Percent, 25.90286F));
            this.tableLayoutPanel6.RowStyles.Add(new System.Windows.Forms.RowStyle(System.Windows.Forms.SizeType.Percent, 74.09714F));
            this.tableLayoutPanel6.Size = new System.Drawing.Size(1352, 803);
            this.tableLayoutPanel6.TabIndex = 20;
            // 
            // Form1
            // 
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.None;
            this.BackColor = System.Drawing.Color.FromArgb(((int)(((byte)(46)))), ((int)(((byte)(51)))), ((int)(((byte)(73)))));
            this.ClientSize = new System.Drawing.Size(1552, 803);
            this.Controls.Add(this.tableLayoutPanel6);
            this.Controls.Add(this.pnlControl);
            this.DoubleBuffered = true;
            this.Icon = ((System.Drawing.Icon)(resources.GetObject("$this.Icon")));
            this.Margin = new System.Windows.Forms.Padding(3, 2, 3, 2);
            this.Name = "Form1";
            this.Text = "TELEMETRY UAV";
            this.FormClosing += new System.Windows.Forms.FormClosingEventHandler(this.Form1_FormClosing);
            this.FormClosed += new System.Windows.Forms.FormClosedEventHandler(this.Form1_FormClosed);
            this.Load += new System.EventHandler(this.Form1_Load);
            this.pnlControl.ResumeLayout(false);
            this.panel2.ResumeLayout(false);
            ((System.ComponentModel.ISupportInitialize)(this.pictureBox1)).EndInit();
            this.tableLayoutPanel5.ResumeLayout(false);
            this.tableLayoutPanel4.ResumeLayout(false);
            this.tableLayoutPanel4.PerformLayout();
            this.tableLayoutPanel3.ResumeLayout(false);
            this.tableLayoutPanel2.ResumeLayout(false);
            this.tableLayoutPanel1.ResumeLayout(false);
            this.tableLayoutPanel6.ResumeLayout(false);
            this.ResumeLayout(false);

        }

        #endregion

        private System.Windows.Forms.Panel pnlControl;
        private System.Windows.Forms.Button btnHome;
        private System.Windows.Forms.Panel panel2;
        private System.Windows.Forms.PictureBox pictureBox1;
        private System.Windows.Forms.Button btnMission;
        private System.Windows.Forms.Panel pnlNav;
        private System.Windows.Forms.Panel pnlFormLoader;
        private System.Windows.Forms.Button btnRCControl;
        private System.Windows.Forms.Button btnSetPID;
        private System.Windows.Forms.Button btnGraphics;
        private System.Windows.Forms.TableLayoutPanel tableLayoutPanel5;
        private System.Windows.Forms.TableLayoutPanel tableLayoutPanel4;
        private System.Windows.Forms.ComboBox comboBox1;
        private System.Windows.Forms.TableLayoutPanel tableLayoutPanel3;
        private System.Windows.Forms.Button btnConnect;
        private System.Windows.Forms.Button btnDisconnect;
        private System.Windows.Forms.Label lblTitle;
        private System.Windows.Forms.Button btnRefresh;
        private System.Windows.Forms.TableLayoutPanel tableLayoutPanel2;
        private System.Windows.Forms.Button button2;
        private System.Windows.Forms.Button btnTM4;
        private System.Windows.Forms.Button btnRoll;
        private System.Windows.Forms.Button btnTM2;
        private System.Windows.Forms.Button button4;
        private System.Windows.Forms.Button btnPitch;
        private CS_WinForms_Ctrl_Heading_Indicator.HeadingIndicator headingIndicator1;
        private CS_WinForms_Ctrl_Artificial_Horizon.Artifical_Horizon artifical_Horizon1;
        private System.Windows.Forms.TableLayoutPanel tableLayoutPanel1;
        private System.Windows.Forms.Button button12;
        private System.Windows.Forms.Button btnTM3;
        private System.Windows.Forms.Button btnAltitude;
        private System.Windows.Forms.Button button10;
        private System.Windows.Forms.Button btnTM1;
        private System.Windows.Forms.TableLayoutPanel tableLayoutPanel6;
        private System.Windows.Forms.Button btnYaw;
        private CS_WinForms_Ctrl_Altimeter.Altimeter altimeter1;
        private System.Windows.Forms.Button btnReset;
        private System.Windows.Forms.Button button1;
        private System.Windows.Forms.Button button3;
        private System.Windows.Forms.Button btnLidar;
        private System.Windows.Forms.Button btnBattery;
    }
}


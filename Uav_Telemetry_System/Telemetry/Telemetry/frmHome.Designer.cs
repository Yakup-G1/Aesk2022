
namespace Telemetry
{
    partial class frmHome
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
            this.components = new System.ComponentModel.Container();
            this.splitter1 = new System.Windows.Forms.Splitter();
            this.ActualPositionMap = new GMap.NET.WindowsForms.GMapControl();
            this.pictureBox1 = new System.Windows.Forms.PictureBox();
            this.GPS_Timer = new System.Windows.Forms.Timer(this.components);
            ((System.ComponentModel.ISupportInitialize)(this.pictureBox1)).BeginInit();
            this.SuspendLayout();
            // 
            // splitter1
            // 
            this.splitter1.Location = new System.Drawing.Point(0, 0);
            this.splitter1.Name = "splitter1";
            this.splitter1.Size = new System.Drawing.Size(1780, 673);
            this.splitter1.TabIndex = 0;
            this.splitter1.TabStop = false;
            // 
            // ActualPositionMap
            // 
            this.ActualPositionMap.Anchor = ((System.Windows.Forms.AnchorStyles)((((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Bottom) 
            | System.Windows.Forms.AnchorStyles.Left) 
            | System.Windows.Forms.AnchorStyles.Right)));
            this.ActualPositionMap.Bearing = 0F;
            this.ActualPositionMap.CanDragMap = true;
            this.ActualPositionMap.EmptyTileColor = System.Drawing.Color.Navy;
            this.ActualPositionMap.GrayScaleMode = false;
            this.ActualPositionMap.HelperLineOption = GMap.NET.WindowsForms.HelperLineOptions.DontShow;
            this.ActualPositionMap.LevelsKeepInMemmory = 5;
            this.ActualPositionMap.Location = new System.Drawing.Point(0, 0);
            this.ActualPositionMap.MarkersEnabled = true;
            this.ActualPositionMap.MaxZoom = 2;
            this.ActualPositionMap.MinZoom = 2;
            this.ActualPositionMap.MouseWheelZoomEnabled = true;
            this.ActualPositionMap.MouseWheelZoomType = GMap.NET.MouseWheelZoomType.MousePositionAndCenter;
            this.ActualPositionMap.Name = "ActualPositionMap";
            this.ActualPositionMap.NegativeMode = false;
            this.ActualPositionMap.PolygonsEnabled = true;
            this.ActualPositionMap.RetryLoadTile = 0;
            this.ActualPositionMap.RoutesEnabled = true;
            this.ActualPositionMap.ScaleMode = GMap.NET.WindowsForms.ScaleModes.Integer;
            this.ActualPositionMap.SelectedAreaFillColor = System.Drawing.Color.FromArgb(((int)(((byte)(33)))), ((int)(((byte)(65)))), ((int)(((byte)(105)))), ((int)(((byte)(225)))));
            this.ActualPositionMap.ShowTileGridLines = false;
            this.ActualPositionMap.Size = new System.Drawing.Size(1780, 673);
            this.ActualPositionMap.TabIndex = 1;
            this.ActualPositionMap.Zoom = 0D;
            // 
            // pictureBox1
            // 
            this.pictureBox1.BackColor = System.Drawing.Color.Transparent;
            this.pictureBox1.Image = global::Telemetry.Properties.Resources.GPS_Drone_Icon;
            this.pictureBox1.Location = new System.Drawing.Point(836, 304);
            this.pictureBox1.Name = "pictureBox1";
            this.pictureBox1.Size = new System.Drawing.Size(64, 64);
            this.pictureBox1.SizeMode = System.Windows.Forms.PictureBoxSizeMode.AutoSize;
            this.pictureBox1.TabIndex = 2;
            this.pictureBox1.TabStop = false;
            this.pictureBox1.Visible = false;
            // 
            // GPS_Timer
            // 
            this.GPS_Timer.Enabled = true;
            this.GPS_Timer.Tick += new System.EventHandler(this.GPS_Timer_Tick);
            // 
            // frmHome
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(8F, 16F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.BackColor = System.Drawing.Color.FromArgb(((int)(((byte)(46)))), ((int)(((byte)(51)))), ((int)(((byte)(73)))));
            this.ClientSize = new System.Drawing.Size(1782, 673);
            this.Controls.Add(this.pictureBox1);
            this.Controls.Add(this.ActualPositionMap);
            this.Controls.Add(this.splitter1);
            this.Name = "frmHome";
            this.Text = "frmHome";
            this.Load += new System.EventHandler(this.frmHome_Load);
            this.Enter += new System.EventHandler(this.frmHome_Enter);
            this.Leave += new System.EventHandler(this.frmHome_Leave);
            ((System.ComponentModel.ISupportInitialize)(this.pictureBox1)).EndInit();
            this.ResumeLayout(false);
            this.PerformLayout();

        }


        #endregion

        private System.Windows.Forms.Splitter splitter1;
        private GMap.NET.WindowsForms.GMapControl ActualPositionMap;
        private System.Windows.Forms.PictureBox pictureBox1;
        private System.Windows.Forms.Timer GPS_Timer;
    }
}

namespace Telemetry
{
    partial class frmMission
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
            this.panel1 = new System.Windows.Forms.Panel();
            this.tableLayoutPanel1 = new System.Windows.Forms.TableLayoutPanel();
            this.button1 = new System.Windows.Forms.Button();
            this.txtRadius = new System.Windows.Forms.TextBox();
            this.tableLayoutPanel2 = new System.Windows.Forms.TableLayoutPanel();
            this.btnClear = new System.Windows.Forms.Button();
            this.btnUndo = new System.Windows.Forms.Button();
            this.lblDistance = new System.Windows.Forms.Label();
            this.listBox1 = new System.Windows.Forms.ListBox();
            this.btnGetRoute = new System.Windows.Forms.Button();
            this.splitter1 = new System.Windows.Forms.Splitter();
            this.MissionMap = new GMap.NET.WindowsForms.GMapControl();
            this.btnInfinite = new System.Windows.Forms.RadioButton();
            this.btnStabilize = new System.Windows.Forms.RadioButton();
            this.btnCircle = new System.Windows.Forms.RadioButton();
            this.btnGoAhead = new System.Windows.Forms.RadioButton();
            this.panel1.SuspendLayout();
            this.tableLayoutPanel1.SuspendLayout();
            this.tableLayoutPanel2.SuspendLayout();
            this.SuspendLayout();
            // 
            // panel1
            // 
            this.panel1.BackColor = System.Drawing.Color.FromArgb(((int)(((byte)(24)))), ((int)(((byte)(29)))), ((int)(((byte)(53)))));
            this.panel1.Controls.Add(this.btnInfinite);
            this.panel1.Controls.Add(this.tableLayoutPanel1);
            this.panel1.Controls.Add(this.tableLayoutPanel2);
            this.panel1.Controls.Add(this.lblDistance);
            this.panel1.Controls.Add(this.listBox1);
            this.panel1.Controls.Add(this.btnGetRoute);
            this.panel1.Controls.Add(this.btnStabilize);
            this.panel1.Controls.Add(this.btnCircle);
            this.panel1.Controls.Add(this.btnGoAhead);
            this.panel1.Dock = System.Windows.Forms.DockStyle.Right;
            this.panel1.Location = new System.Drawing.Point(1291, 0);
            this.panel1.Name = "panel1";
            this.panel1.Size = new System.Drawing.Size(241, 673);
            this.panel1.TabIndex = 1;
            // 
            // tableLayoutPanel1
            // 
            this.tableLayoutPanel1.ColumnCount = 2;
            this.tableLayoutPanel1.ColumnStyles.Add(new System.Windows.Forms.ColumnStyle(System.Windows.Forms.SizeType.Percent, 33F));
            this.tableLayoutPanel1.ColumnStyles.Add(new System.Windows.Forms.ColumnStyle(System.Windows.Forms.SizeType.Percent, 33F));
            this.tableLayoutPanel1.Controls.Add(this.button1, 0, 0);
            this.tableLayoutPanel1.Controls.Add(this.txtRadius, 1, 0);
            this.tableLayoutPanel1.Location = new System.Drawing.Point(0, 284);
            this.tableLayoutPanel1.Name = "tableLayoutPanel1";
            this.tableLayoutPanel1.RowCount = 1;
            this.tableLayoutPanel1.RowStyles.Add(new System.Windows.Forms.RowStyle(System.Windows.Forms.SizeType.Percent, 100F));
            this.tableLayoutPanel1.RowStyles.Add(new System.Windows.Forms.RowStyle(System.Windows.Forms.SizeType.Absolute, 38F));
            this.tableLayoutPanel1.Size = new System.Drawing.Size(241, 38);
            this.tableLayoutPanel1.TabIndex = 14;
            // 
            // button1
            // 
            this.button1.Dock = System.Windows.Forms.DockStyle.Top;
            this.button1.FlatAppearance.BorderSize = 2;
            this.button1.FlatStyle = System.Windows.Forms.FlatStyle.Flat;
            this.button1.Font = new System.Drawing.Font("Nirmala UI", 7.8F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.button1.ForeColor = System.Drawing.Color.FromArgb(((int)(((byte)(0)))), ((int)(((byte)(196)))), ((int)(((byte)(249)))));
            this.button1.Location = new System.Drawing.Point(3, 3);
            this.button1.Name = "button1";
            this.button1.Size = new System.Drawing.Size(114, 32);
            this.button1.TabIndex = 10;
            this.button1.Text = "Radius :";
            this.button1.TextImageRelation = System.Windows.Forms.TextImageRelation.TextBeforeImage;
            this.button1.UseVisualStyleBackColor = true;
            // 
            // txtRadius
            // 
            this.txtRadius.BackColor = System.Drawing.Color.FromArgb(((int)(((byte)(24)))), ((int)(((byte)(29)))), ((int)(((byte)(53)))));
            this.txtRadius.Dock = System.Windows.Forms.DockStyle.Fill;
            this.txtRadius.Font = new System.Drawing.Font("Microsoft Sans Serif", 12F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(162)));
            this.txtRadius.ForeColor = System.Drawing.Color.FromArgb(((int)(((byte)(0)))), ((int)(((byte)(196)))), ((int)(((byte)(249)))));
            this.txtRadius.Location = new System.Drawing.Point(123, 3);
            this.txtRadius.Name = "txtRadius";
            this.txtRadius.Size = new System.Drawing.Size(115, 30);
            this.txtRadius.TabIndex = 11;
            this.txtRadius.Text = "6";
            this.txtRadius.TextAlign = System.Windows.Forms.HorizontalAlignment.Center;
            this.txtRadius.KeyPress += new System.Windows.Forms.KeyPressEventHandler(this.txtRadius_KeyPress);
            // 
            // tableLayoutPanel2
            // 
            this.tableLayoutPanel2.ColumnCount = 2;
            this.tableLayoutPanel2.ColumnStyles.Add(new System.Windows.Forms.ColumnStyle(System.Windows.Forms.SizeType.Percent, 33F));
            this.tableLayoutPanel2.ColumnStyles.Add(new System.Windows.Forms.ColumnStyle(System.Windows.Forms.SizeType.Percent, 33F));
            this.tableLayoutPanel2.Controls.Add(this.btnClear, 0, 0);
            this.tableLayoutPanel2.Controls.Add(this.btnUndo, 0, 0);
            this.tableLayoutPanel2.Location = new System.Drawing.Point(0, 246);
            this.tableLayoutPanel2.Name = "tableLayoutPanel2";
            this.tableLayoutPanel2.RowCount = 1;
            this.tableLayoutPanel2.RowStyles.Add(new System.Windows.Forms.RowStyle(System.Windows.Forms.SizeType.Percent, 100F));
            this.tableLayoutPanel2.Size = new System.Drawing.Size(241, 38);
            this.tableLayoutPanel2.TabIndex = 13;
            // 
            // btnClear
            // 
            this.btnClear.Dock = System.Windows.Forms.DockStyle.Top;
            this.btnClear.FlatAppearance.BorderSize = 2;
            this.btnClear.FlatStyle = System.Windows.Forms.FlatStyle.Flat;
            this.btnClear.Font = new System.Drawing.Font("Nirmala UI", 7.8F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.btnClear.ForeColor = System.Drawing.Color.Gray;
            this.btnClear.Location = new System.Drawing.Point(123, 3);
            this.btnClear.Name = "btnClear";
            this.btnClear.Size = new System.Drawing.Size(115, 32);
            this.btnClear.TabIndex = 11;
            this.btnClear.Text = "CLEAR";
            this.btnClear.TextImageRelation = System.Windows.Forms.TextImageRelation.TextBeforeImage;
            this.btnClear.UseVisualStyleBackColor = true;
            this.btnClear.Click += new System.EventHandler(this.btnClear_Click);
            // 
            // btnUndo
            // 
            this.btnUndo.Dock = System.Windows.Forms.DockStyle.Top;
            this.btnUndo.FlatAppearance.BorderSize = 2;
            this.btnUndo.FlatStyle = System.Windows.Forms.FlatStyle.Flat;
            this.btnUndo.Font = new System.Drawing.Font("Nirmala UI", 7.8F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.btnUndo.ForeColor = System.Drawing.Color.Gray;
            this.btnUndo.Location = new System.Drawing.Point(3, 3);
            this.btnUndo.Name = "btnUndo";
            this.btnUndo.Size = new System.Drawing.Size(114, 32);
            this.btnUndo.TabIndex = 10;
            this.btnUndo.Text = "UNDO";
            this.btnUndo.TextImageRelation = System.Windows.Forms.TextImageRelation.TextBeforeImage;
            this.btnUndo.UseVisualStyleBackColor = true;
            this.btnUndo.Click += new System.EventHandler(this.btnUndo_Click);
            // 
            // lblDistance
            // 
            this.lblDistance.AutoSize = true;
            this.lblDistance.Font = new System.Drawing.Font("MV Boli", 10.2F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.lblDistance.ForeColor = System.Drawing.SystemColors.ActiveCaption;
            this.lblDistance.Location = new System.Drawing.Point(64, 405);
            this.lblDistance.Name = "lblDistance";
            this.lblDistance.Size = new System.Drawing.Size(93, 22);
            this.lblDistance.TabIndex = 10;
            this.lblDistance.Text = "0 Meters";
            // 
            // listBox1
            // 
            this.listBox1.BackColor = System.Drawing.Color.FromArgb(((int)(((byte)(24)))), ((int)(((byte)(29)))), ((int)(((byte)(53)))));
            this.listBox1.ForeColor = System.Drawing.Color.White;
            this.listBox1.FormattingEnabled = true;
            this.listBox1.HorizontalScrollbar = true;
            this.listBox1.ItemHeight = 16;
            this.listBox1.Location = new System.Drawing.Point(3, 430);
            this.listBox1.Name = "listBox1";
            this.listBox1.Size = new System.Drawing.Size(231, 228);
            this.listBox1.TabIndex = 4;
            // 
            // btnGetRoute
            // 
            this.btnGetRoute.FlatAppearance.BorderSize = 2;
            this.btnGetRoute.FlatStyle = System.Windows.Forms.FlatStyle.Flat;
            this.btnGetRoute.Font = new System.Drawing.Font("Nirmala UI", 10.8F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.btnGetRoute.ForeColor = System.Drawing.Color.FromArgb(((int)(((byte)(0)))), ((int)(((byte)(126)))), ((int)(((byte)(249)))));
            this.btnGetRoute.Location = new System.Drawing.Point(0, 198);
            this.btnGetRoute.Name = "btnGetRoute";
            this.btnGetRoute.Size = new System.Drawing.Size(241, 44);
            this.btnGetRoute.TabIndex = 9;
            this.btnGetRoute.Text = "GET ROUTE";
            this.btnGetRoute.TextImageRelation = System.Windows.Forms.TextImageRelation.TextBeforeImage;
            this.btnGetRoute.UseVisualStyleBackColor = true;
            this.btnGetRoute.Click += new System.EventHandler(this.btnGetRoute_Click);
            // 
            // splitter1
            // 
            this.splitter1.Location = new System.Drawing.Point(0, 0);
            this.splitter1.Name = "splitter1";
            this.splitter1.Size = new System.Drawing.Size(1288, 673);
            this.splitter1.TabIndex = 2;
            this.splitter1.TabStop = false;
            // 
            // MissionMap
            // 
            this.MissionMap.Anchor = ((System.Windows.Forms.AnchorStyles)((((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Bottom) 
            | System.Windows.Forms.AnchorStyles.Left) 
            | System.Windows.Forms.AnchorStyles.Right)));
            this.MissionMap.Bearing = 0F;
            this.MissionMap.CanDragMap = true;
            this.MissionMap.EmptyTileColor = System.Drawing.Color.Navy;
            this.MissionMap.GrayScaleMode = false;
            this.MissionMap.HelperLineOption = GMap.NET.WindowsForms.HelperLineOptions.DontShow;
            this.MissionMap.LevelsKeepInMemmory = 5;
            this.MissionMap.Location = new System.Drawing.Point(0, 0);
            this.MissionMap.MarkersEnabled = true;
            this.MissionMap.MaxZoom = 2;
            this.MissionMap.MinZoom = 2;
            this.MissionMap.MouseWheelZoomEnabled = true;
            this.MissionMap.MouseWheelZoomType = GMap.NET.MouseWheelZoomType.MousePositionAndCenter;
            this.MissionMap.Name = "MissionMap";
            this.MissionMap.NegativeMode = false;
            this.MissionMap.PolygonsEnabled = true;
            this.MissionMap.RetryLoadTile = 0;
            this.MissionMap.RoutesEnabled = true;
            this.MissionMap.ScaleMode = GMap.NET.WindowsForms.ScaleModes.Integer;
            this.MissionMap.SelectedAreaFillColor = System.Drawing.Color.FromArgb(((int)(((byte)(33)))), ((int)(((byte)(65)))), ((int)(((byte)(105)))), ((int)(((byte)(225)))));
            this.MissionMap.ShowTileGridLines = false;
            this.MissionMap.Size = new System.Drawing.Size(1285, 673);
            this.MissionMap.TabIndex = 3;
            this.MissionMap.Zoom = 0D;
            this.MissionMap.MouseClick += new System.Windows.Forms.MouseEventHandler(this.MissionMap_MouseClick);
            // 
            // btnInfinite
            // 
            this.btnInfinite.Dock = System.Windows.Forms.DockStyle.Top;
            this.btnInfinite.Font = new System.Drawing.Font("Nirmala UI", 10.8F, System.Drawing.FontStyle.Bold);
            this.btnInfinite.ForeColor = System.Drawing.Color.FromArgb(((int)(((byte)(13)))), ((int)(((byte)(217)))), ((int)(((byte)(57)))));
            this.btnInfinite.Image = global::Telemetry.Properties.Resources.infinite__1_;
            this.btnInfinite.Location = new System.Drawing.Point(0, 144);
            this.btnInfinite.Name = "btnInfinite";
            this.btnInfinite.Size = new System.Drawing.Size(241, 48);
            this.btnInfinite.TabIndex = 15;
            this.btnInfinite.Text = "Infinite   ";
            this.btnInfinite.TextAlign = System.Drawing.ContentAlignment.MiddleCenter;
            this.btnInfinite.TextImageRelation = System.Windows.Forms.TextImageRelation.TextBeforeImage;
            this.btnInfinite.UseVisualStyleBackColor = true;
            // 
            // btnStabilize
            // 
            this.btnStabilize.Dock = System.Windows.Forms.DockStyle.Top;
            this.btnStabilize.Font = new System.Drawing.Font("Nirmala UI", 10.8F, System.Drawing.FontStyle.Bold);
            this.btnStabilize.ForeColor = System.Drawing.Color.FromArgb(((int)(((byte)(252)))), ((int)(((byte)(99)))), ((int)(((byte)(85)))));
            this.btnStabilize.Image = global::Telemetry.Properties.Resources.time;
            this.btnStabilize.Location = new System.Drawing.Point(0, 96);
            this.btnStabilize.Name = "btnStabilize";
            this.btnStabilize.Size = new System.Drawing.Size(241, 48);
            this.btnStabilize.TabIndex = 8;
            this.btnStabilize.Text = "Stabilize  ";
            this.btnStabilize.TextAlign = System.Drawing.ContentAlignment.MiddleCenter;
            this.btnStabilize.TextImageRelation = System.Windows.Forms.TextImageRelation.TextBeforeImage;
            this.btnStabilize.UseVisualStyleBackColor = true;
            this.btnStabilize.Visible = false;
            // 
            // btnCircle
            // 
            this.btnCircle.Dock = System.Windows.Forms.DockStyle.Top;
            this.btnCircle.Font = new System.Drawing.Font("Nirmala UI", 10.8F, System.Drawing.FontStyle.Bold);
            this.btnCircle.ForeColor = System.Drawing.Color.FromArgb(((int)(((byte)(252)))), ((int)(((byte)(243)))), ((int)(((byte)(87)))));
            this.btnCircle.Image = global::Telemetry.Properties.Resources.loading;
            this.btnCircle.Location = new System.Drawing.Point(0, 48);
            this.btnCircle.Name = "btnCircle";
            this.btnCircle.Size = new System.Drawing.Size(241, 48);
            this.btnCircle.TabIndex = 7;
            this.btnCircle.Text = "Circle       ";
            this.btnCircle.TextAlign = System.Drawing.ContentAlignment.MiddleCenter;
            this.btnCircle.TextImageRelation = System.Windows.Forms.TextImageRelation.TextBeforeImage;
            this.btnCircle.UseVisualStyleBackColor = true;
            // 
            // btnGoAhead
            // 
            this.btnGoAhead.Checked = true;
            this.btnGoAhead.Dock = System.Windows.Forms.DockStyle.Top;
            this.btnGoAhead.Font = new System.Drawing.Font("Nirmala UI", 10.8F, System.Drawing.FontStyle.Bold);
            this.btnGoAhead.ForeColor = System.Drawing.Color.FromArgb(((int)(((byte)(87)))), ((int)(((byte)(129)))), ((int)(((byte)(252)))));
            this.btnGoAhead.Image = global::Telemetry.Properties.Resources.ahead_only;
            this.btnGoAhead.Location = new System.Drawing.Point(0, 0);
            this.btnGoAhead.Name = "btnGoAhead";
            this.btnGoAhead.Size = new System.Drawing.Size(241, 48);
            this.btnGoAhead.TabIndex = 6;
            this.btnGoAhead.TabStop = true;
            this.btnGoAhead.Text = "Go Ahead";
            this.btnGoAhead.TextAlign = System.Drawing.ContentAlignment.MiddleCenter;
            this.btnGoAhead.TextImageRelation = System.Windows.Forms.TextImageRelation.TextBeforeImage;
            this.btnGoAhead.UseVisualStyleBackColor = true;
            // 
            // frmMission
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(8F, 16F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.BackColor = System.Drawing.Color.FromArgb(((int)(((byte)(46)))), ((int)(((byte)(51)))), ((int)(((byte)(73)))));
            this.ClientSize = new System.Drawing.Size(1532, 673);
            this.Controls.Add(this.MissionMap);
            this.Controls.Add(this.splitter1);
            this.Controls.Add(this.panel1);
            this.Name = "frmMission";
            this.Text = "frmMission";
            this.Load += new System.EventHandler(this.frmMission_Load);
            this.panel1.ResumeLayout(false);
            this.panel1.PerformLayout();
            this.tableLayoutPanel1.ResumeLayout(false);
            this.tableLayoutPanel1.PerformLayout();
            this.tableLayoutPanel2.ResumeLayout(false);
            this.ResumeLayout(false);

        }

        #endregion

        private System.Windows.Forms.Panel panel1;
        private System.Windows.Forms.Splitter splitter1;
        private GMap.NET.WindowsForms.GMapControl MissionMap;
        private System.Windows.Forms.RadioButton btnGoAhead;
        private System.Windows.Forms.Button btnGetRoute;
        private System.Windows.Forms.RadioButton btnStabilize;
        private System.Windows.Forms.RadioButton btnCircle;
        private System.Windows.Forms.ListBox listBox1;
        private System.Windows.Forms.Label lblDistance;
        private System.Windows.Forms.TableLayoutPanel tableLayoutPanel1;
        private System.Windows.Forms.Button button1;
        private System.Windows.Forms.TextBox txtRadius;
        private System.Windows.Forms.TableLayoutPanel tableLayoutPanel2;
        private System.Windows.Forms.Button btnClear;
        private System.Windows.Forms.Button btnUndo;
        private System.Windows.Forms.RadioButton btnInfinite;
    }
}
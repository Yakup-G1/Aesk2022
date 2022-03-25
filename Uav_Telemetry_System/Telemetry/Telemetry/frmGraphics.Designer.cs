
namespace Telemetry
{
    partial class frmGraphics
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
            this.tableLayoutPanel1 = new System.Windows.Forms.TableLayoutPanel();
            this.zedGraphControl1 = new ZedGraph.ZedGraphControl();
            this.zedGraphControl2 = new ZedGraph.ZedGraphControl();
            this.zedGraphControl3 = new ZedGraph.ZedGraphControl();
            this.zedGraphControl4 = new ZedGraph.ZedGraphControl();
            this.tableLayoutPanel3 = new System.Windows.Forms.TableLayoutPanel();
            this.tableLayoutPanel2 = new System.Windows.Forms.TableLayoutPanel();
            this.btnZoomRollGraph = new System.Windows.Forms.Button();
            this.btnZoomPitchGraph = new System.Windows.Forms.Button();
            this.btnScroll = new System.Windows.Forms.Button();
            this.btnZoomYawGraph = new System.Windows.Forms.Button();
            this.ZoomOut = new System.Windows.Forms.Button();
            this.btnZoomAltitudeGraph = new System.Windows.Forms.Button();
            this.tableLayoutPanel1.SuspendLayout();
            this.tableLayoutPanel3.SuspendLayout();
            this.tableLayoutPanel2.SuspendLayout();
            this.SuspendLayout();
            // 
            // tableLayoutPanel1
            // 
            this.tableLayoutPanel1.ColumnCount = 2;
            this.tableLayoutPanel1.ColumnStyles.Add(new System.Windows.Forms.ColumnStyle());
            this.tableLayoutPanel1.ColumnStyles.Add(new System.Windows.Forms.ColumnStyle());
            this.tableLayoutPanel1.Controls.Add(this.zedGraphControl1, 0, 0);
            this.tableLayoutPanel1.Controls.Add(this.zedGraphControl2, 1, 0);
            this.tableLayoutPanel1.Controls.Add(this.zedGraphControl3, 1, 1);
            this.tableLayoutPanel1.Controls.Add(this.zedGraphControl4, 0, 1);
            this.tableLayoutPanel1.Dock = System.Windows.Forms.DockStyle.Fill;
            this.tableLayoutPanel1.Location = new System.Drawing.Point(3, 3);
            this.tableLayoutPanel1.Name = "tableLayoutPanel1";
            this.tableLayoutPanel1.RowCount = 2;
            this.tableLayoutPanel1.RowStyles.Add(new System.Windows.Forms.RowStyle());
            this.tableLayoutPanel1.RowStyles.Add(new System.Windows.Forms.RowStyle());
            this.tableLayoutPanel1.Size = new System.Drawing.Size(1350, 567);
            this.tableLayoutPanel1.TabIndex = 5;
            // 
            // zedGraphControl1
            // 
            this.zedGraphControl1.Dock = System.Windows.Forms.DockStyle.Fill;
            this.zedGraphControl1.Location = new System.Drawing.Point(4, 4);
            this.zedGraphControl1.Margin = new System.Windows.Forms.Padding(4, 4, 4, 4);
            this.zedGraphControl1.Name = "zedGraphControl1";
            this.zedGraphControl1.ScrollGrace = 0D;
            this.zedGraphControl1.ScrollMaxX = 0D;
            this.zedGraphControl1.ScrollMaxY = 0D;
            this.zedGraphControl1.ScrollMaxY2 = 0D;
            this.zedGraphControl1.ScrollMinX = 0D;
            this.zedGraphControl1.ScrollMinY = 0D;
            this.zedGraphControl1.ScrollMinY2 = 0D;
            this.zedGraphControl1.Size = new System.Drawing.Size(667, 275);
            this.zedGraphControl1.TabIndex = 0;
            this.zedGraphControl1.UseExtendedPrintDialog = true;
            // 
            // zedGraphControl2
            // 
            this.zedGraphControl2.Dock = System.Windows.Forms.DockStyle.Fill;
            this.zedGraphControl2.Location = new System.Drawing.Point(679, 4);
            this.zedGraphControl2.Margin = new System.Windows.Forms.Padding(4, 4, 4, 4);
            this.zedGraphControl2.Name = "zedGraphControl2";
            this.zedGraphControl2.ScrollGrace = 0D;
            this.zedGraphControl2.ScrollMaxX = 0D;
            this.zedGraphControl2.ScrollMaxY = 0D;
            this.zedGraphControl2.ScrollMaxY2 = 0D;
            this.zedGraphControl2.ScrollMinX = 0D;
            this.zedGraphControl2.ScrollMinY = 0D;
            this.zedGraphControl2.ScrollMinY2 = 0D;
            this.zedGraphControl2.Size = new System.Drawing.Size(667, 275);
            this.zedGraphControl2.TabIndex = 1;
            this.zedGraphControl2.UseExtendedPrintDialog = true;
            // 
            // zedGraphControl3
            // 
            this.zedGraphControl3.Dock = System.Windows.Forms.DockStyle.Fill;
            this.zedGraphControl3.Location = new System.Drawing.Point(679, 287);
            this.zedGraphControl3.Margin = new System.Windows.Forms.Padding(4, 4, 4, 4);
            this.zedGraphControl3.Name = "zedGraphControl3";
            this.zedGraphControl3.ScrollGrace = 0D;
            this.zedGraphControl3.ScrollMaxX = 0D;
            this.zedGraphControl3.ScrollMaxY = 0D;
            this.zedGraphControl3.ScrollMaxY2 = 0D;
            this.zedGraphControl3.ScrollMinX = 0D;
            this.zedGraphControl3.ScrollMinY = 0D;
            this.zedGraphControl3.ScrollMinY2 = 0D;
            this.zedGraphControl3.Size = new System.Drawing.Size(667, 276);
            this.zedGraphControl3.TabIndex = 3;
            this.zedGraphControl3.UseExtendedPrintDialog = true;
            // 
            // zedGraphControl4
            // 
            this.zedGraphControl4.Dock = System.Windows.Forms.DockStyle.Fill;
            this.zedGraphControl4.Location = new System.Drawing.Point(4, 287);
            this.zedGraphControl4.Margin = new System.Windows.Forms.Padding(4, 4, 4, 4);
            this.zedGraphControl4.Name = "zedGraphControl4";
            this.zedGraphControl4.ScrollGrace = 0D;
            this.zedGraphControl4.ScrollMaxX = 0D;
            this.zedGraphControl4.ScrollMaxY = 0D;
            this.zedGraphControl4.ScrollMaxY2 = 0D;
            this.zedGraphControl4.ScrollMinX = 0D;
            this.zedGraphControl4.ScrollMinY = 0D;
            this.zedGraphControl4.ScrollMinY2 = 0D;
            this.zedGraphControl4.Size = new System.Drawing.Size(667, 276);
            this.zedGraphControl4.TabIndex = 2;
            this.zedGraphControl4.UseExtendedPrintDialog = true;
            // 
            // tableLayoutPanel3
            // 
            this.tableLayoutPanel3.ColumnCount = 2;
            this.tableLayoutPanel3.ColumnStyles.Add(new System.Windows.Forms.ColumnStyle(System.Windows.Forms.SizeType.Percent, 91.49798F));
            this.tableLayoutPanel3.ColumnStyles.Add(new System.Windows.Forms.ColumnStyle(System.Windows.Forms.SizeType.Percent, 8.502025F));
            this.tableLayoutPanel3.Controls.Add(this.tableLayoutPanel1, 0, 0);
            this.tableLayoutPanel3.Controls.Add(this.tableLayoutPanel2, 1, 0);
            this.tableLayoutPanel3.Dock = System.Windows.Forms.DockStyle.Fill;
            this.tableLayoutPanel3.Location = new System.Drawing.Point(0, 0);
            this.tableLayoutPanel3.Name = "tableLayoutPanel3";
            this.tableLayoutPanel3.RowCount = 1;
            this.tableLayoutPanel3.RowStyles.Add(new System.Windows.Forms.RowStyle(System.Windows.Forms.SizeType.Percent, 50F));
            this.tableLayoutPanel3.Size = new System.Drawing.Size(1482, 573);
            this.tableLayoutPanel3.TabIndex = 7;
            // 
            // tableLayoutPanel2
            // 
            this.tableLayoutPanel2.ColumnCount = 1;
            this.tableLayoutPanel2.ColumnStyles.Add(new System.Windows.Forms.ColumnStyle(System.Windows.Forms.SizeType.Percent, 100F));
            this.tableLayoutPanel2.Controls.Add(this.btnZoomRollGraph, 0, 0);
            this.tableLayoutPanel2.Controls.Add(this.btnZoomPitchGraph, 0, 5);
            this.tableLayoutPanel2.Controls.Add(this.btnScroll, 0, 2);
            this.tableLayoutPanel2.Controls.Add(this.btnZoomYawGraph, 0, 1);
            this.tableLayoutPanel2.Controls.Add(this.ZoomOut, 0, 3);
            this.tableLayoutPanel2.Controls.Add(this.btnZoomAltitudeGraph, 0, 4);
            this.tableLayoutPanel2.Dock = System.Windows.Forms.DockStyle.Fill;
            this.tableLayoutPanel2.Location = new System.Drawing.Point(1359, 3);
            this.tableLayoutPanel2.Name = "tableLayoutPanel2";
            this.tableLayoutPanel2.RowCount = 6;
            this.tableLayoutPanel2.RowStyles.Add(new System.Windows.Forms.RowStyle(System.Windows.Forms.SizeType.Percent, 16.66667F));
            this.tableLayoutPanel2.RowStyles.Add(new System.Windows.Forms.RowStyle(System.Windows.Forms.SizeType.Percent, 16.66667F));
            this.tableLayoutPanel2.RowStyles.Add(new System.Windows.Forms.RowStyle(System.Windows.Forms.SizeType.Percent, 16.66667F));
            this.tableLayoutPanel2.RowStyles.Add(new System.Windows.Forms.RowStyle(System.Windows.Forms.SizeType.Percent, 16.66667F));
            this.tableLayoutPanel2.RowStyles.Add(new System.Windows.Forms.RowStyle(System.Windows.Forms.SizeType.Percent, 16.66667F));
            this.tableLayoutPanel2.RowStyles.Add(new System.Windows.Forms.RowStyle(System.Windows.Forms.SizeType.Percent, 16.66667F));
            this.tableLayoutPanel2.RowStyles.Add(new System.Windows.Forms.RowStyle(System.Windows.Forms.SizeType.Absolute, 20F));
            this.tableLayoutPanel2.Size = new System.Drawing.Size(120, 567);
            this.tableLayoutPanel2.TabIndex = 6;
            // 
            // btnZoomRollGraph
            // 
            this.btnZoomRollGraph.Dock = System.Windows.Forms.DockStyle.Fill;
            this.btnZoomRollGraph.FlatAppearance.BorderSize = 0;
            this.btnZoomRollGraph.FlatStyle = System.Windows.Forms.FlatStyle.Flat;
            this.btnZoomRollGraph.Font = new System.Drawing.Font("Impact", 13F);
            this.btnZoomRollGraph.ForeColor = System.Drawing.Color.FromArgb(((int)(((byte)(27)))), ((int)(((byte)(180)))), ((int)(((byte)(193)))));
            this.btnZoomRollGraph.Image = global::Telemetry.Properties.Resources.zoom_in__3_;
            this.btnZoomRollGraph.Location = new System.Drawing.Point(3, 3);
            this.btnZoomRollGraph.Name = "btnZoomRollGraph";
            this.btnZoomRollGraph.Size = new System.Drawing.Size(114, 88);
            this.btnZoomRollGraph.TabIndex = 5;
            this.btnZoomRollGraph.Text = "Roll";
            this.btnZoomRollGraph.TextAlign = System.Drawing.ContentAlignment.BottomLeft;
            this.btnZoomRollGraph.UseVisualStyleBackColor = true;
            this.btnZoomRollGraph.Click += new System.EventHandler(this.btnZoomRollGraph_Click);
            // 
            // btnZoomPitchGraph
            // 
            this.btnZoomPitchGraph.Dock = System.Windows.Forms.DockStyle.Fill;
            this.btnZoomPitchGraph.FlatAppearance.BorderSize = 0;
            this.btnZoomPitchGraph.FlatStyle = System.Windows.Forms.FlatStyle.Flat;
            this.btnZoomPitchGraph.Font = new System.Drawing.Font("Impact", 13F);
            this.btnZoomPitchGraph.ForeColor = System.Drawing.Color.FromArgb(((int)(((byte)(27)))), ((int)(((byte)(180)))), ((int)(((byte)(193)))));
            this.btnZoomPitchGraph.Image = global::Telemetry.Properties.Resources.zoom_in__3_;
            this.btnZoomPitchGraph.Location = new System.Drawing.Point(3, 473);
            this.btnZoomPitchGraph.Name = "btnZoomPitchGraph";
            this.btnZoomPitchGraph.Size = new System.Drawing.Size(114, 91);
            this.btnZoomPitchGraph.TabIndex = 10;
            this.btnZoomPitchGraph.Text = "Pitch";
            this.btnZoomPitchGraph.TextAlign = System.Drawing.ContentAlignment.BottomLeft;
            this.btnZoomPitchGraph.UseVisualStyleBackColor = true;
            this.btnZoomPitchGraph.Click += new System.EventHandler(this.btnZoomPitchGraph_Click);
            // 
            // btnScroll
            // 
            this.btnScroll.Dock = System.Windows.Forms.DockStyle.Fill;
            this.btnScroll.FlatAppearance.BorderSize = 0;
            this.btnScroll.FlatStyle = System.Windows.Forms.FlatStyle.Flat;
            this.btnScroll.Font = new System.Drawing.Font("Algerian", 13F);
            this.btnScroll.ForeColor = System.Drawing.Color.FromArgb(((int)(((byte)(0)))), ((int)(((byte)(126)))), ((int)(((byte)(249)))));
            this.btnScroll.Image = global::Telemetry.Properties.Resources.stop;
            this.btnScroll.Location = new System.Drawing.Point(3, 191);
            this.btnScroll.Name = "btnScroll";
            this.btnScroll.Size = new System.Drawing.Size(114, 88);
            this.btnScroll.TabIndex = 4;
            this.btnScroll.UseVisualStyleBackColor = true;
            this.btnScroll.Click += new System.EventHandler(this.btnScroll_Click_1);
            // 
            // btnZoomYawGraph
            // 
            this.btnZoomYawGraph.Dock = System.Windows.Forms.DockStyle.Fill;
            this.btnZoomYawGraph.FlatAppearance.BorderSize = 0;
            this.btnZoomYawGraph.FlatStyle = System.Windows.Forms.FlatStyle.Flat;
            this.btnZoomYawGraph.Font = new System.Drawing.Font("Impact", 13F);
            this.btnZoomYawGraph.ForeColor = System.Drawing.Color.FromArgb(((int)(((byte)(27)))), ((int)(((byte)(180)))), ((int)(((byte)(193)))));
            this.btnZoomYawGraph.Image = global::Telemetry.Properties.Resources.zoom_in__3_;
            this.btnZoomYawGraph.Location = new System.Drawing.Point(3, 97);
            this.btnZoomYawGraph.Name = "btnZoomYawGraph";
            this.btnZoomYawGraph.Size = new System.Drawing.Size(114, 88);
            this.btnZoomYawGraph.TabIndex = 11;
            this.btnZoomYawGraph.Text = "Yaw";
            this.btnZoomYawGraph.TextAlign = System.Drawing.ContentAlignment.BottomLeft;
            this.btnZoomYawGraph.UseVisualStyleBackColor = true;
            this.btnZoomYawGraph.Click += new System.EventHandler(this.btnZoomYawGraph_Click);
            // 
            // ZoomOut
            // 
            this.ZoomOut.Dock = System.Windows.Forms.DockStyle.Fill;
            this.ZoomOut.FlatAppearance.BorderSize = 0;
            this.ZoomOut.FlatStyle = System.Windows.Forms.FlatStyle.Flat;
            this.ZoomOut.Font = new System.Drawing.Font("Algerian", 13F);
            this.ZoomOut.ForeColor = System.Drawing.Color.FromArgb(((int)(((byte)(0)))), ((int)(((byte)(126)))), ((int)(((byte)(249)))));
            this.ZoomOut.Image = global::Telemetry.Properties.Resources.zoom_out;
            this.ZoomOut.Location = new System.Drawing.Point(3, 285);
            this.ZoomOut.Name = "ZoomOut";
            this.ZoomOut.Size = new System.Drawing.Size(114, 88);
            this.ZoomOut.TabIndex = 12;
            this.ZoomOut.UseVisualStyleBackColor = true;
            this.ZoomOut.Click += new System.EventHandler(this.ZoomOut_Click);
            // 
            // btnZoomAltitudeGraph
            // 
            this.btnZoomAltitudeGraph.Dock = System.Windows.Forms.DockStyle.Fill;
            this.btnZoomAltitudeGraph.FlatAppearance.BorderSize = 0;
            this.btnZoomAltitudeGraph.FlatStyle = System.Windows.Forms.FlatStyle.Flat;
            this.btnZoomAltitudeGraph.Font = new System.Drawing.Font("Impact", 11.3F);
            this.btnZoomAltitudeGraph.ForeColor = System.Drawing.Color.FromArgb(((int)(((byte)(27)))), ((int)(((byte)(180)))), ((int)(((byte)(193)))));
            this.btnZoomAltitudeGraph.Image = global::Telemetry.Properties.Resources.zoom_in__3_;
            this.btnZoomAltitudeGraph.Location = new System.Drawing.Point(3, 379);
            this.btnZoomAltitudeGraph.Name = "btnZoomAltitudeGraph";
            this.btnZoomAltitudeGraph.Size = new System.Drawing.Size(114, 88);
            this.btnZoomAltitudeGraph.TabIndex = 13;
            this.btnZoomAltitudeGraph.Text = "Altitude";
            this.btnZoomAltitudeGraph.TextAlign = System.Drawing.ContentAlignment.BottomLeft;
            this.btnZoomAltitudeGraph.UseVisualStyleBackColor = true;
            this.btnZoomAltitudeGraph.Click += new System.EventHandler(this.btnZoomAltitudeGraph_Click);
            // 
            // frmGraphics
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(8F, 16F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.AutoScroll = true;
            this.BackColor = System.Drawing.Color.FromArgb(((int)(((byte)(46)))), ((int)(((byte)(51)))), ((int)(((byte)(73)))));
            this.ClientSize = new System.Drawing.Size(1482, 573);
            this.Controls.Add(this.tableLayoutPanel3);
            this.DoubleBuffered = true;
            this.Name = "frmGraphics";
            this.Text = "frmGraphics";
            this.Load += new System.EventHandler(this.frmGraphics_Load);
            this.Enter += new System.EventHandler(this.frmGraphics_Enter);
            this.Leave += new System.EventHandler(this.frmGraphics_Leave);
            this.tableLayoutPanel1.ResumeLayout(false);
            this.tableLayoutPanel3.ResumeLayout(false);
            this.tableLayoutPanel2.ResumeLayout(false);
            this.ResumeLayout(false);

        }

        #endregion

        private System.Windows.Forms.TableLayoutPanel tableLayoutPanel1;
        private ZedGraph.ZedGraphControl zedGraphControl1;
        private ZedGraph.ZedGraphControl zedGraphControl2;
        private ZedGraph.ZedGraphControl zedGraphControl3;
        private ZedGraph.ZedGraphControl zedGraphControl4;
        private System.Windows.Forms.TableLayoutPanel tableLayoutPanel3;
        private System.Windows.Forms.TableLayoutPanel tableLayoutPanel2;
        private System.Windows.Forms.Button btnZoomRollGraph;
        private System.Windows.Forms.Button btnZoomPitchGraph;
        private System.Windows.Forms.Button btnScroll;
        private System.Windows.Forms.Button btnZoomYawGraph;
        private System.Windows.Forms.Button ZoomOut;
        private System.Windows.Forms.Button btnZoomAltitudeGraph;
    }
}
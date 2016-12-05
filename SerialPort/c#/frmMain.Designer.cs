namespace SerialPort
{
    partial class frmMain
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
            this.groupBox1 = new System.Windows.Forms.GroupBox();
            this.txtSend = new System.Windows.Forms.TextBox();
            this.btnWriteAsync = new System.Windows.Forms.Button();
            this.btnWriteSync = new System.Windows.Forms.Button();
            this.groupBox2 = new System.Windows.Forms.GroupBox();
            this.txtRecv = new System.Windows.Forms.TextBox();
            this.timer1 = new System.Windows.Forms.Timer(this.components);
            this.groupBox4 = new System.Windows.Forms.GroupBox();
            this.btnClose = new System.Windows.Forms.Button();
            this.label5 = new System.Windows.Forms.Label();
            this.cboStop = new System.Windows.Forms.ComboBox();
            this.label4 = new System.Windows.Forms.Label();
            this.cboData = new System.Windows.Forms.ComboBox();
            this.label3 = new System.Windows.Forms.Label();
            this.cboParity = new System.Windows.Forms.ComboBox();
            this.label2 = new System.Windows.Forms.Label();
            this.cboBaud = new System.Windows.Forms.ComboBox();
            this.label1 = new System.Windows.Forms.Label();
            this.cboCOM = new System.Windows.Forms.ComboBox();
            this.btnOpen = new System.Windows.Forms.Button();
            this.groupBox3 = new System.Windows.Forms.GroupBox();
            this.chkXON = new System.Windows.Forms.CheckBox();
            this.chkRTS = new System.Windows.Forms.CheckBox();
            this.groupBox1.SuspendLayout();
            this.groupBox2.SuspendLayout();
            this.groupBox4.SuspendLayout();
            this.groupBox3.SuspendLayout();
            this.SuspendLayout();
            // 
            // groupBox1
            // 
            this.groupBox1.Controls.Add(this.txtSend);
            this.groupBox1.Controls.Add(this.btnWriteAsync);
            this.groupBox1.Controls.Add(this.btnWriteSync);
            this.groupBox1.Location = new System.Drawing.Point(257, 5);
            this.groupBox1.Name = "groupBox1";
            this.groupBox1.Size = new System.Drawing.Size(282, 165);
            this.groupBox1.TabIndex = 19;
            this.groupBox1.TabStop = false;
            this.groupBox1.Text = "发送";
            // 
            // txtSend
            // 
            this.txtSend.Location = new System.Drawing.Point(9, 18);
            this.txtSend.Multiline = true;
            this.txtSend.Name = "txtSend";
            this.txtSend.ScrollBars = System.Windows.Forms.ScrollBars.Vertical;
            this.txtSend.Size = new System.Drawing.Size(265, 101);
            this.txtSend.TabIndex = 16;
            // 
            // btnWriteAsync
            // 
            this.btnWriteAsync.Location = new System.Drawing.Point(90, 125);
            this.btnWriteAsync.Name = "btnWriteAsync";
            this.btnWriteAsync.Size = new System.Drawing.Size(73, 29);
            this.btnWriteAsync.TabIndex = 18;
            this.btnWriteAsync.Text = "异步发送";
            this.btnWriteAsync.UseVisualStyleBackColor = true;
            this.btnWriteAsync.Click += new System.EventHandler(this.btnWriteAsync_Click);
            // 
            // btnWriteSync
            // 
            this.btnWriteSync.Location = new System.Drawing.Point(9, 125);
            this.btnWriteSync.Name = "btnWriteSync";
            this.btnWriteSync.Size = new System.Drawing.Size(73, 29);
            this.btnWriteSync.TabIndex = 17;
            this.btnWriteSync.Text = "同步发送";
            this.btnWriteSync.UseVisualStyleBackColor = true;
            this.btnWriteSync.Click += new System.EventHandler(this.btnWriteSync_Click);
            // 
            // groupBox2
            // 
            this.groupBox2.Controls.Add(this.txtRecv);
            this.groupBox2.Location = new System.Drawing.Point(9, 174);
            this.groupBox2.Name = "groupBox2";
            this.groupBox2.Size = new System.Drawing.Size(530, 168);
            this.groupBox2.TabIndex = 21;
            this.groupBox2.TabStop = false;
            this.groupBox2.Text = "接收";
            // 
            // txtRecv
            // 
            this.txtRecv.Location = new System.Drawing.Point(10, 16);
            this.txtRecv.Multiline = true;
            this.txtRecv.Name = "txtRecv";
            this.txtRecv.ReadOnly = true;
            this.txtRecv.ScrollBars = System.Windows.Forms.ScrollBars.Vertical;
            this.txtRecv.Size = new System.Drawing.Size(510, 141);
            this.txtRecv.TabIndex = 20;
            // 
            // timer1
            // 
            this.timer1.Enabled = true;
            this.timer1.Interval = 200;
            this.timer1.Tick += new System.EventHandler(this.timer1_Tick);
            // 
            // groupBox4
            // 
            this.groupBox4.Controls.Add(this.btnClose);
            this.groupBox4.Controls.Add(this.label5);
            this.groupBox4.Controls.Add(this.cboStop);
            this.groupBox4.Controls.Add(this.label4);
            this.groupBox4.Controls.Add(this.cboData);
            this.groupBox4.Controls.Add(this.label3);
            this.groupBox4.Controls.Add(this.cboParity);
            this.groupBox4.Controls.Add(this.label2);
            this.groupBox4.Controls.Add(this.cboBaud);
            this.groupBox4.Controls.Add(this.label1);
            this.groupBox4.Controls.Add(this.cboCOM);
            this.groupBox4.Controls.Add(this.btnOpen);
            this.groupBox4.Controls.Add(this.groupBox3);
            this.groupBox4.Location = new System.Drawing.Point(9, 5);
            this.groupBox4.Name = "groupBox4";
            this.groupBox4.Size = new System.Drawing.Size(239, 165);
            this.groupBox4.TabIndex = 15;
            this.groupBox4.TabStop = false;
            this.groupBox4.Text = "串口";
            // 
            // btnClose
            // 
            this.btnClose.Location = new System.Drawing.Point(154, 123);
            this.btnClose.Name = "btnClose";
            this.btnClose.Size = new System.Drawing.Size(58, 30);
            this.btnClose.TabIndex = 14;
            this.btnClose.Text = "关闭";
            this.btnClose.UseVisualStyleBackColor = true;
            this.btnClose.Click += new System.EventHandler(this.btnClose_Click);
            // 
            // label5
            // 
            this.label5.AutoSize = true;
            this.label5.Location = new System.Drawing.Point(10, 138);
            this.label5.Name = "label5";
            this.label5.Size = new System.Drawing.Size(41, 12);
            this.label5.TabIndex = 8;
            this.label5.Text = "停止位";
            // 
            // cboStop
            // 
            this.cboStop.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList;
            this.cboStop.FormattingEnabled = true;
            this.cboStop.Items.AddRange(new object[] {
            "1",
            "1.5",
            "2"});
            this.cboStop.Location = new System.Drawing.Point(56, 134);
            this.cboStop.Name = "cboStop";
            this.cboStop.Size = new System.Drawing.Size(74, 20);
            this.cboStop.TabIndex = 9;
            // 
            // label4
            // 
            this.label4.AutoSize = true;
            this.label4.Location = new System.Drawing.Point(10, 109);
            this.label4.Name = "label4";
            this.label4.Size = new System.Drawing.Size(41, 12);
            this.label4.TabIndex = 6;
            this.label4.Text = "数据位";
            // 
            // cboData
            // 
            this.cboData.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList;
            this.cboData.FormattingEnabled = true;
            this.cboData.Items.AddRange(new object[] {
            "4",
            "5",
            "6",
            "7",
            "8"});
            this.cboData.Location = new System.Drawing.Point(56, 105);
            this.cboData.Name = "cboData";
            this.cboData.Size = new System.Drawing.Size(74, 20);
            this.cboData.TabIndex = 7;
            // 
            // label3
            // 
            this.label3.AutoSize = true;
            this.label3.Location = new System.Drawing.Point(10, 80);
            this.label3.Name = "label3";
            this.label3.Size = new System.Drawing.Size(41, 12);
            this.label3.TabIndex = 4;
            this.label3.Text = "校验法";
            // 
            // cboParity
            // 
            this.cboParity.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList;
            this.cboParity.FormattingEnabled = true;
            this.cboParity.Items.AddRange(new object[] {
            "N(无)",
            "O(奇)",
            "E(偶)",
            "M(置1)",
            "S(置0)"});
            this.cboParity.Location = new System.Drawing.Point(56, 76);
            this.cboParity.Name = "cboParity";
            this.cboParity.Size = new System.Drawing.Size(74, 20);
            this.cboParity.TabIndex = 5;
            // 
            // label2
            // 
            this.label2.AutoSize = true;
            this.label2.Location = new System.Drawing.Point(10, 51);
            this.label2.Name = "label2";
            this.label2.Size = new System.Drawing.Size(41, 12);
            this.label2.TabIndex = 2;
            this.label2.Text = "波特率";
            // 
            // cboBaud
            // 
            this.cboBaud.FormattingEnabled = true;
            this.cboBaud.Items.AddRange(new object[] {
            "110",
            "300",
            "600",
            "1200",
            "2400",
            "4800",
            "9600",
            "14400",
            "19200",
            "38400",
            "56000",
            "57600",
            "115200",
            "128000",
            "256000"});
            this.cboBaud.Location = new System.Drawing.Point(56, 47);
            this.cboBaud.Name = "cboBaud";
            this.cboBaud.Size = new System.Drawing.Size(74, 20);
            this.cboBaud.TabIndex = 3;
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Location = new System.Drawing.Point(10, 22);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(23, 12);
            this.label1.TabIndex = 0;
            this.label1.Text = "COM";
            // 
            // cboCOM
            // 
            this.cboCOM.FormattingEnabled = true;
            this.cboCOM.Location = new System.Drawing.Point(56, 18);
            this.cboCOM.Name = "cboCOM";
            this.cboCOM.Size = new System.Drawing.Size(74, 20);
            this.cboCOM.TabIndex = 1;
            // 
            // btnOpen
            // 
            this.btnOpen.Location = new System.Drawing.Point(154, 82);
            this.btnOpen.Name = "btnOpen";
            this.btnOpen.Size = new System.Drawing.Size(58, 30);
            this.btnOpen.TabIndex = 13;
            this.btnOpen.Text = "打开";
            this.btnOpen.UseVisualStyleBackColor = true;
            this.btnOpen.Click += new System.EventHandler(this.btnOpen_Click);
            // 
            // groupBox3
            // 
            this.groupBox3.Controls.Add(this.chkXON);
            this.groupBox3.Controls.Add(this.chkRTS);
            this.groupBox3.Location = new System.Drawing.Point(138, 13);
            this.groupBox3.Name = "groupBox3";
            this.groupBox3.Size = new System.Drawing.Size(90, 60);
            this.groupBox3.TabIndex = 12;
            this.groupBox3.TabStop = false;
            this.groupBox3.Text = "流控制";
            // 
            // chkXON
            // 
            this.chkXON.AutoSize = true;
            this.chkXON.Location = new System.Drawing.Point(10, 38);
            this.chkXON.Name = "chkXON";
            this.chkXON.Size = new System.Drawing.Size(72, 16);
            this.chkXON.TabIndex = 11;
            this.chkXON.Text = "XON/XOFF";
            this.chkXON.UseVisualStyleBackColor = true;
            // 
            // chkRTS
            // 
            this.chkRTS.AutoSize = true;
            this.chkRTS.Location = new System.Drawing.Point(10, 18);
            this.chkRTS.Name = "chkRTS";
            this.chkRTS.Size = new System.Drawing.Size(66, 16);
            this.chkRTS.TabIndex = 10;
            this.chkRTS.Text = "RTS/CTS";
            this.chkRTS.UseVisualStyleBackColor = true;
            // 
            // frmMain
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 12F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(546, 350);
            this.Controls.Add(this.groupBox4);
            this.Controls.Add(this.groupBox2);
            this.Controls.Add(this.groupBox1);
            this.Name = "frmMain";
            this.Text = "串行通讯";
            this.Load += new System.EventHandler(this.frmMain_Load);
            this.FormClosed += new System.Windows.Forms.FormClosedEventHandler(this.frmMain_FormClosed);
            this.groupBox1.ResumeLayout(false);
            this.groupBox1.PerformLayout();
            this.groupBox2.ResumeLayout(false);
            this.groupBox2.PerformLayout();
            this.groupBox4.ResumeLayout(false);
            this.groupBox4.PerformLayout();
            this.groupBox3.ResumeLayout(false);
            this.groupBox3.PerformLayout();
            this.ResumeLayout(false);

        }

        #endregion

        private System.Windows.Forms.GroupBox groupBox1;
        private System.Windows.Forms.TextBox txtSend;
        private System.Windows.Forms.Button btnWriteAsync;
        private System.Windows.Forms.Button btnWriteSync;
        private System.Windows.Forms.GroupBox groupBox2;
        private System.Windows.Forms.TextBox txtRecv;
        private System.Windows.Forms.Timer timer1;
        private System.Windows.Forms.GroupBox groupBox4;
        private System.Windows.Forms.Button btnClose;
        private System.Windows.Forms.Label label5;
        private System.Windows.Forms.ComboBox cboStop;
        private System.Windows.Forms.Label label4;
        private System.Windows.Forms.ComboBox cboData;
        private System.Windows.Forms.Label label3;
        private System.Windows.Forms.ComboBox cboParity;
        private System.Windows.Forms.Label label2;
        private System.Windows.Forms.ComboBox cboBaud;
        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.ComboBox cboCOM;
        private System.Windows.Forms.Button btnOpen;
        private System.Windows.Forms.GroupBox groupBox3;
        private System.Windows.Forms.CheckBox chkXON;
        private System.Windows.Forms.CheckBox chkRTS;
    }
}


namespace EDC20HOST
{
    partial class Tracker
    {
        /// <summary>
        /// 必需的设计器变量。
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        /// 清理所有正在使用的资源。
        /// </summary>
        /// <param name="disposing">如果应释放托管资源，为 true；否则为 false。</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
                capture.Dispose();
                cc.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Windows 窗体设计器生成的代码

        /// <summary>
        /// 设计器支持所需的方法 - 不要修改
        /// 使用代码编辑器修改此方法的内容。
        /// </summary>
        private void InitializeComponent()
        {
            this.components = new System.ComponentModel.Container();
            this.tbInfo = new System.Windows.Forms.TextBox();
            this.pbCamera = new System.Windows.Forms.PictureBox();
            this.tbPoint1 = new System.Windows.Forms.TextBox();
            this.tbPoint2 = new System.Windows.Forms.TextBox();
            this.tbPoint3 = new System.Windows.Forms.TextBox();
            this.tbPoint4 = new System.Windows.Forms.TextBox();
            this.btnReset = new System.Windows.Forms.Button();
            this.lblHue1L = new System.Windows.Forms.Label();
            this.nudHue1L = new System.Windows.Forms.NumericUpDown();
            this.nudHue1H = new System.Windows.Forms.NumericUpDown();
            this.lblHueH = new System.Windows.Forms.Label();
            this.nudHue2L = new System.Windows.Forms.NumericUpDown();
            this.lblHue2L = new System.Windows.Forms.Label();
            this.nudHue2H = new System.Windows.Forms.NumericUpDown();
            this.lblHue2H = new System.Windows.Forms.Label();
            this.nudSat1L = new System.Windows.Forms.NumericUpDown();
            this.lblSat1L = new System.Windows.Forms.Label();
            this.nudSat2L = new System.Windows.Forms.NumericUpDown();
            this.lblSat2L = new System.Windows.Forms.Label();
            this.nudValueL = new System.Windows.Forms.NumericUpDown();
            this.lblValueL = new System.Windows.Forms.Label();
            this.nudAreaL = new System.Windows.Forms.NumericUpDown();
            this.lblAreaL = new System.Windows.Forms.Label();
            this.timer100ms = new System.Windows.Forms.Timer(this.components);
            this.label1 = new System.Windows.Forms.Label();
            this.buttonStart = new System.Windows.Forms.Button();
            this.buttonPause = new System.Windows.Forms.Button();
            this.label2 = new System.Windows.Forms.Label();
            this.label3 = new System.Windows.Forms.Label();
            this.label4 = new System.Windows.Forms.Label();
            this.label5 = new System.Windows.Forms.Label();
            this.label6 = new System.Windows.Forms.Label();
            this.label7 = new System.Windows.Forms.Label();
            this.label8 = new System.Windows.Forms.Label();
            this.label9 = new System.Windows.Forms.Label();
            this.label10 = new System.Windows.Forms.Label();
            this.label11 = new System.Windows.Forms.Label();
            this.label12 = new System.Windows.Forms.Label();
            this.labelALocation = new System.Windows.Forms.Label();
            this.labelBLocation = new System.Windows.Forms.Label();
            this.label1L = new System.Windows.Forms.Label();
            this.label2L = new System.Windows.Forms.Label();
            this.label3L = new System.Windows.Forms.Label();
            this.label17 = new System.Windows.Forms.Label();
            this.label4L = new System.Windows.Forms.Label();
            this.label5L = new System.Windows.Forms.Label();
            this.labelValidP = new System.Windows.Forms.Label();
            this.labelRound = new System.Windows.Forms.Label();
            this.labelState = new System.Windows.Forms.Label();
            this.labelAScore = new System.Windows.Forms.Label();
            this.labelBScore = new System.Windows.Forms.Label();
            this.button_restart = new System.Windows.Forms.Button();
            this.numericUpDownScoreA = new System.Windows.Forms.NumericUpDown();
            this.numericUpDownScoreB = new System.Windows.Forms.NumericUpDown();
            this.labelAGetScore = new System.Windows.Forms.Label();
            this.labelBGetScore = new System.Windows.Forms.Label();
            this.buttonChangeScore = new System.Windows.Forms.Button();
            this.numericUpDownTime = new System.Windows.Forms.NumericUpDown();
            this.button1 = new System.Windows.Forms.Button();
            this.button_minus10 = new System.Windows.Forms.Button();
            this.button_minus20 = new System.Windows.Forms.Button();
            this.button_minus80 = new System.Windows.Forms.Button();
            this.button_plus50 = new System.Windows.Forms.Button();
            this.button_plus100 = new System.Windows.Forms.Button();
            this.button_plus150 = new System.Windows.Forms.Button();
            this.button_reset = new System.Windows.Forms.Button();
            this.groupBox_car = new System.Windows.Forms.GroupBox();
            this.radioButton_CarB = new System.Windows.Forms.RadioButton();
            this.radioButton_CarA = new System.Windows.Forms.RadioButton();
            this.button_video = new System.Windows.Forms.Button();
            this.checkBox_DebugMode = new System.Windows.Forms.CheckBox();
            this.setAcarBtn = new System.Windows.Forms.Button();
            this.CarYTB = new System.Windows.Forms.TextBox();
            this.CarXTB = new System.Windows.Forms.TextBox();
            this.label27 = new System.Windows.Forms.Label();
            this.label26 = new System.Windows.Forms.Label();
            this.setBcarposBtn = new System.Windows.Forms.Button();
            this.label16 = new System.Windows.Forms.Label();
            this.label18 = new System.Windows.Forms.Label();
            this.nextPassengerEndXTB = new System.Windows.Forms.TextBox();
            this.nextPassengerEndYTB = new System.Windows.Forms.TextBox();
            this.label15 = new System.Windows.Forms.Label();
            this.label14 = new System.Windows.Forms.Label();
            this.label13 = new System.Windows.Forms.Label();
            this.updatePassengerBtn = new System.Windows.Forms.Button();
            this.nextPassengerTB = new System.Windows.Forms.TextBox();
            this.nextPassengerStartXTB = new System.Windows.Forms.TextBox();
            this.nextPassengerStartYTB = new System.Windows.Forms.TextBox();
            this.round1Btn = new System.Windows.Forms.Button();
            this.deltayawLb = new System.Windows.Forms.Label();
            this.yawLb = new System.Windows.Forms.Label();
            this.nowLb = new System.Windows.Forms.Label();
            this.goLb = new System.Windows.Forms.Label();
            this.lb2 = new System.Windows.Forms.Label();
            this.label24 = new System.Windows.Forms.Label();
            this.bluetoothLb = new System.Windows.Forms.Label();
            this.clearreceiveBtn = new System.Windows.Forms.Button();
            this.receiveTB = new System.Windows.Forms.TextBox();
            this.portCB = new System.Windows.Forms.ComboBox();
            this.label20 = new System.Windows.Forms.Label();
            this.bluetoothBtn = new System.Windows.Forms.Button();
            this.serialPort1 = new System.IO.Ports.SerialPort(this.components);
            this.distanceLb = new System.Windows.Forms.Label();
            this.myIDTB = new System.Windows.Forms.TextBox();
            this.label29 = new System.Windows.Forms.Label();
            this.setmyidBtn = new System.Windows.Forms.Button();
            ((System.ComponentModel.ISupportInitialize)(this.pbCamera)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.nudHue1L)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.nudHue1H)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.nudHue2L)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.nudHue2H)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.nudSat1L)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.nudSat2L)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.nudValueL)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.nudAreaL)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.numericUpDownScoreA)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.numericUpDownScoreB)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.numericUpDownTime)).BeginInit();
            this.SuspendLayout();
            // 
            // tbInfo
            // 
            this.tbInfo.Font = new System.Drawing.Font("微软雅黑", 9F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.tbInfo.Location = new System.Drawing.Point(20, 20);
            this.tbInfo.Name = "tbInfo";
            this.tbInfo.ReadOnly = true;
            this.tbInfo.Size = new System.Drawing.Size(150, 27);
            this.tbInfo.TabIndex = 1;
            // 
            // pbCamera
            // 
            this.pbCamera.Location = new System.Drawing.Point(200, 20);
            this.pbCamera.Name = "pbCamera";
            this.pbCamera.Size = new System.Drawing.Size(640, 480);
            this.pbCamera.SizeMode = System.Windows.Forms.PictureBoxSizeMode.AutoSize;
            this.pbCamera.TabIndex = 2;
            this.pbCamera.TabStop = false;
            this.pbCamera.MouseClick += new System.Windows.Forms.MouseEventHandler(this.pbCamera_MouseClick);
            // 
            // tbPoint1
            // 
            this.tbPoint1.Font = new System.Drawing.Font("微软雅黑", 9F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.tbPoint1.Location = new System.Drawing.Point(20, 70);
            this.tbPoint1.Name = "tbPoint1";
            this.tbPoint1.ReadOnly = true;
            this.tbPoint1.Size = new System.Drawing.Size(150, 27);
            this.tbPoint1.TabIndex = 3;
            // 
            // tbPoint2
            // 
            this.tbPoint2.Font = new System.Drawing.Font("微软雅黑", 9F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.tbPoint2.Location = new System.Drawing.Point(20, 120);
            this.tbPoint2.Name = "tbPoint2";
            this.tbPoint2.ReadOnly = true;
            this.tbPoint2.Size = new System.Drawing.Size(150, 27);
            this.tbPoint2.TabIndex = 4;
            // 
            // tbPoint3
            // 
            this.tbPoint3.Font = new System.Drawing.Font("微软雅黑", 9F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.tbPoint3.Location = new System.Drawing.Point(20, 170);
            this.tbPoint3.Name = "tbPoint3";
            this.tbPoint3.ReadOnly = true;
            this.tbPoint3.Size = new System.Drawing.Size(150, 27);
            this.tbPoint3.TabIndex = 5;
            // 
            // tbPoint4
            // 
            this.tbPoint4.Font = new System.Drawing.Font("微软雅黑", 9F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.tbPoint4.Location = new System.Drawing.Point(20, 220);
            this.tbPoint4.Name = "tbPoint4";
            this.tbPoint4.ReadOnly = true;
            this.tbPoint4.Size = new System.Drawing.Size(150, 27);
            this.tbPoint4.TabIndex = 6;
            // 
            // btnReset
            // 
            this.btnReset.Font = new System.Drawing.Font("微软雅黑", 9F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.btnReset.Location = new System.Drawing.Point(20, 270);
            this.btnReset.Name = "btnReset";
            this.btnReset.Size = new System.Drawing.Size(150, 30);
            this.btnReset.TabIndex = 7;
            this.btnReset.Text = "重设边界点";
            this.btnReset.UseVisualStyleBackColor = true;
            this.btnReset.Click += new System.EventHandler(this.btnReset_Click);
            // 
            // lblHue1L
            // 
            this.lblHue1L.AutoSize = true;
            this.lblHue1L.Font = new System.Drawing.Font("微软雅黑", 9F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.lblHue1L.Location = new System.Drawing.Point(20, 320);
            this.lblHue1L.Name = "lblHue1L";
            this.lblHue1L.Size = new System.Drawing.Size(60, 20);
            this.lblHue1L.TabIndex = 8;
            this.lblHue1L.Text = "Hue1L:";
            // 
            // nudHue1L
            // 
            this.nudHue1L.Font = new System.Drawing.Font("微软雅黑", 9F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.nudHue1L.Location = new System.Drawing.Point(85, 320);
            this.nudHue1L.Maximum = new decimal(new int[] {
            180,
            0,
            0,
            0});
            this.nudHue1L.Name = "nudHue1L";
            this.nudHue1L.Size = new System.Drawing.Size(75, 27);
            this.nudHue1L.TabIndex = 10;
            this.nudHue1L.ValueChanged += new System.EventHandler(this.nudHue1L_ValueChanged);
            // 
            // nudHue1H
            // 
            this.nudHue1H.Font = new System.Drawing.Font("微软雅黑", 9F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.nudHue1H.Location = new System.Drawing.Point(85, 370);
            this.nudHue1H.Maximum = new decimal(new int[] {
            180,
            0,
            0,
            0});
            this.nudHue1H.Name = "nudHue1H";
            this.nudHue1H.Size = new System.Drawing.Size(75, 27);
            this.nudHue1H.TabIndex = 12;
            this.nudHue1H.ValueChanged += new System.EventHandler(this.nudHue1H_ValueChanged);
            // 
            // lblHueH
            // 
            this.lblHueH.AutoSize = true;
            this.lblHueH.Font = new System.Drawing.Font("微软雅黑", 9F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.lblHueH.Location = new System.Drawing.Point(20, 370);
            this.lblHueH.Name = "lblHueH";
            this.lblHueH.Size = new System.Drawing.Size(64, 20);
            this.lblHueH.TabIndex = 11;
            this.lblHueH.Text = "Hue1H:";
            // 
            // nudHue2L
            // 
            this.nudHue2L.Font = new System.Drawing.Font("微软雅黑", 9F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.nudHue2L.Location = new System.Drawing.Point(85, 420);
            this.nudHue2L.Maximum = new decimal(new int[] {
            180,
            0,
            0,
            0});
            this.nudHue2L.Name = "nudHue2L";
            this.nudHue2L.Size = new System.Drawing.Size(75, 27);
            this.nudHue2L.TabIndex = 14;
            this.nudHue2L.ValueChanged += new System.EventHandler(this.nudHue2L_ValueChanged);
            // 
            // lblHue2L
            // 
            this.lblHue2L.AutoSize = true;
            this.lblHue2L.Font = new System.Drawing.Font("微软雅黑", 9F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.lblHue2L.Location = new System.Drawing.Point(20, 420);
            this.lblHue2L.Name = "lblHue2L";
            this.lblHue2L.Size = new System.Drawing.Size(60, 20);
            this.lblHue2L.TabIndex = 13;
            this.lblHue2L.Text = "Hue2L:";
            // 
            // nudHue2H
            // 
            this.nudHue2H.Font = new System.Drawing.Font("微软雅黑", 9F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.nudHue2H.Location = new System.Drawing.Point(85, 470);
            this.nudHue2H.Maximum = new decimal(new int[] {
            180,
            0,
            0,
            0});
            this.nudHue2H.Name = "nudHue2H";
            this.nudHue2H.Size = new System.Drawing.Size(75, 27);
            this.nudHue2H.TabIndex = 16;
            this.nudHue2H.ValueChanged += new System.EventHandler(this.nudHue2H_ValueChanged);
            // 
            // lblHue2H
            // 
            this.lblHue2H.AutoSize = true;
            this.lblHue2H.Font = new System.Drawing.Font("微软雅黑", 9F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.lblHue2H.Location = new System.Drawing.Point(20, 470);
            this.lblHue2H.Name = "lblHue2H";
            this.lblHue2H.Size = new System.Drawing.Size(64, 20);
            this.lblHue2H.TabIndex = 15;
            this.lblHue2H.Text = "Hue2H:";
            // 
            // nudSat1L
            // 
            this.nudSat1L.Font = new System.Drawing.Font("微软雅黑", 9F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.nudSat1L.Location = new System.Drawing.Point(85, 520);
            this.nudSat1L.Maximum = new decimal(new int[] {
            255,
            0,
            0,
            0});
            this.nudSat1L.Name = "nudSat1L";
            this.nudSat1L.Size = new System.Drawing.Size(75, 27);
            this.nudSat1L.TabIndex = 18;
            this.nudSat1L.ValueChanged += new System.EventHandler(this.nudSat1L_ValueChanged);
            // 
            // lblSat1L
            // 
            this.lblSat1L.AutoSize = true;
            this.lblSat1L.Font = new System.Drawing.Font("微软雅黑", 9F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.lblSat1L.Location = new System.Drawing.Point(20, 520);
            this.lblSat1L.Name = "lblSat1L";
            this.lblSat1L.Size = new System.Drawing.Size(53, 20);
            this.lblSat1L.TabIndex = 17;
            this.lblSat1L.Text = "Sat1L:";
            // 
            // nudSat2L
            // 
            this.nudSat2L.Font = new System.Drawing.Font("微软雅黑", 9F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.nudSat2L.Location = new System.Drawing.Point(85, 570);
            this.nudSat2L.Maximum = new decimal(new int[] {
            255,
            0,
            0,
            0});
            this.nudSat2L.Name = "nudSat2L";
            this.nudSat2L.Size = new System.Drawing.Size(75, 27);
            this.nudSat2L.TabIndex = 20;
            this.nudSat2L.ValueChanged += new System.EventHandler(this.nudSat2L_ValueChanged);
            // 
            // lblSat2L
            // 
            this.lblSat2L.AutoSize = true;
            this.lblSat2L.Font = new System.Drawing.Font("微软雅黑", 9F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.lblSat2L.Location = new System.Drawing.Point(20, 570);
            this.lblSat2L.Name = "lblSat2L";
            this.lblSat2L.Size = new System.Drawing.Size(53, 20);
            this.lblSat2L.TabIndex = 19;
            this.lblSat2L.Text = "Sat2L:";
            // 
            // nudValueL
            // 
            this.nudValueL.Font = new System.Drawing.Font("微软雅黑", 9F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.nudValueL.Location = new System.Drawing.Point(85, 620);
            this.nudValueL.Maximum = new decimal(new int[] {
            255,
            0,
            0,
            0});
            this.nudValueL.Name = "nudValueL";
            this.nudValueL.Size = new System.Drawing.Size(75, 27);
            this.nudValueL.TabIndex = 22;
            this.nudValueL.ValueChanged += new System.EventHandler(this.nudValueL_ValueChanged);
            // 
            // lblValueL
            // 
            this.lblValueL.AutoSize = true;
            this.lblValueL.Font = new System.Drawing.Font("微软雅黑", 9F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.lblValueL.Location = new System.Drawing.Point(20, 620);
            this.lblValueL.Name = "lblValueL";
            this.lblValueL.Size = new System.Drawing.Size(61, 20);
            this.lblValueL.TabIndex = 21;
            this.lblValueL.Text = "ValueL:";
            // 
            // nudAreaL
            // 
            this.nudAreaL.Font = new System.Drawing.Font("微软雅黑", 9F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.nudAreaL.Location = new System.Drawing.Point(85, 670);
            this.nudAreaL.Maximum = new decimal(new int[] {
            1000,
            0,
            0,
            0});
            this.nudAreaL.Name = "nudAreaL";
            this.nudAreaL.Size = new System.Drawing.Size(75, 27);
            this.nudAreaL.TabIndex = 24;
            this.nudAreaL.ValueChanged += new System.EventHandler(this.nudAreaL_ValueChanged);
            // 
            // lblAreaL
            // 
            this.lblAreaL.AutoSize = true;
            this.lblAreaL.Font = new System.Drawing.Font("微软雅黑", 9F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.lblAreaL.Location = new System.Drawing.Point(20, 670);
            this.lblAreaL.Name = "lblAreaL";
            this.lblAreaL.Size = new System.Drawing.Size(55, 20);
            this.lblAreaL.TabIndex = 23;
            this.lblAreaL.Text = "AreaL:";
            // 
            // timer100ms
            // 
            this.timer100ms.Tick += new System.EventHandler(this.timer100ms_Tick);
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Font = new System.Drawing.Font("微软雅黑", 9F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.label1.Location = new System.Drawing.Point(1363, 345);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(92, 20);
            this.label1.TabIndex = 25;
            this.label1.Text = "CurrRound:";
            // 
            // buttonStart
            // 
            this.buttonStart.Font = new System.Drawing.Font("微软雅黑", 9F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.buttonStart.Location = new System.Drawing.Point(664, 802);
            this.buttonStart.Name = "buttonStart";
            this.buttonStart.Size = new System.Drawing.Size(80, 35);
            this.buttonStart.TabIndex = 27;
            this.buttonStart.Text = "开始";
            this.buttonStart.UseVisualStyleBackColor = true;
            this.buttonStart.Click += new System.EventHandler(this.buttonStart_Click);
            // 
            // buttonPause
            // 
            this.buttonPause.Font = new System.Drawing.Font("微软雅黑", 9F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.buttonPause.Location = new System.Drawing.Point(664, 760);
            this.buttonPause.Name = "buttonPause";
            this.buttonPause.Size = new System.Drawing.Size(80, 35);
            this.buttonPause.TabIndex = 28;
            this.buttonPause.Text = "暂停";
            this.buttonPause.UseVisualStyleBackColor = true;
            this.buttonPause.Click += new System.EventHandler(this.buttonPause_Click);
            // 
            // label2
            // 
            this.label2.AutoSize = true;
            this.label2.Font = new System.Drawing.Font("微软雅黑", 9F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.label2.Location = new System.Drawing.Point(1363, 25);
            this.label2.Name = "label2";
            this.label2.Size = new System.Drawing.Size(80, 20);
            this.label2.TabIndex = 30;
            this.label2.Text = "A车坐标：";
            // 
            // label3
            // 
            this.label3.AutoSize = true;
            this.label3.Font = new System.Drawing.Font("微软雅黑", 9F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.label3.Location = new System.Drawing.Point(1363, 65);
            this.label3.Name = "label3";
            this.label3.Size = new System.Drawing.Size(78, 20);
            this.label3.TabIndex = 31;
            this.label3.Text = "B车坐标：";
            // 
            // label4
            // 
            this.label4.AutoSize = true;
            this.label4.Font = new System.Drawing.Font("微软雅黑", 9F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.label4.Location = new System.Drawing.Point(1363, 105);
            this.label4.Name = "label4";
            this.label4.Size = new System.Drawing.Size(93, 20);
            this.label4.TabIndex = 32;
            this.label4.Text = "乘客1坐标：";
            // 
            // label5
            // 
            this.label5.AutoSize = true;
            this.label5.Font = new System.Drawing.Font("微软雅黑", 9F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.label5.Location = new System.Drawing.Point(1363, 145);
            this.label5.Name = "label5";
            this.label5.Size = new System.Drawing.Size(93, 20);
            this.label5.TabIndex = 33;
            this.label5.Text = "乘客2坐标：";
            // 
            // label6
            // 
            this.label6.AutoSize = true;
            this.label6.Font = new System.Drawing.Font("微软雅黑", 9F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.label6.Location = new System.Drawing.Point(1363, 185);
            this.label6.Name = "label6";
            this.label6.Size = new System.Drawing.Size(93, 20);
            this.label6.TabIndex = 34;
            this.label6.Text = "乘客3坐标：";
            // 
            // label7
            // 
            this.label7.AutoSize = true;
            this.label7.Font = new System.Drawing.Font("微软雅黑", 9F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.label7.Location = new System.Drawing.Point(1363, 225);
            this.label7.Name = "label7";
            this.label7.Size = new System.Drawing.Size(93, 20);
            this.label7.TabIndex = 35;
            this.label7.Text = "乘客4坐标：";
            // 
            // label8
            // 
            this.label8.AutoSize = true;
            this.label8.Font = new System.Drawing.Font("微软雅黑", 9F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.label8.Location = new System.Drawing.Point(1363, 265);
            this.label8.Name = "label8";
            this.label8.Size = new System.Drawing.Size(93, 20);
            this.label8.TabIndex = 36;
            this.label8.Text = "乘客5坐标：";
            // 
            // label9
            // 
            this.label9.AutoSize = true;
            this.label9.Font = new System.Drawing.Font("微软雅黑", 9F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.label9.Location = new System.Drawing.Point(1363, 305);
            this.label9.Name = "label9";
            this.label9.Size = new System.Drawing.Size(99, 20);
            this.label9.TabIndex = 37;
            this.label9.Text = "有效乘客数：";
            // 
            // label10
            // 
            this.label10.AutoSize = true;
            this.label10.Font = new System.Drawing.Font("微软雅黑", 9F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.label10.Location = new System.Drawing.Point(1363, 385);
            this.label10.Name = "label10";
            this.label10.Size = new System.Drawing.Size(84, 20);
            this.label10.TabIndex = 38;
            this.label10.Text = "比赛状态：";
            // 
            // label11
            // 
            this.label11.AutoSize = true;
            this.label11.Font = new System.Drawing.Font("微软雅黑", 9F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.label11.Location = new System.Drawing.Point(1363, 425);
            this.label11.Name = "label11";
            this.label11.Size = new System.Drawing.Size(116, 20);
            this.label11.TabIndex = 39;
            this.label11.Text = "A车得分/犯规：";
            // 
            // label12
            // 
            this.label12.AutoSize = true;
            this.label12.Font = new System.Drawing.Font("微软雅黑", 9F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.label12.Location = new System.Drawing.Point(1363, 465);
            this.label12.Name = "label12";
            this.label12.Size = new System.Drawing.Size(114, 20);
            this.label12.TabIndex = 40;
            this.label12.Text = "B车得分/犯规：";
            // 
            // labelALocation
            // 
            this.labelALocation.AutoSize = true;
            this.labelALocation.Font = new System.Drawing.Font("微软雅黑", 9F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.labelALocation.Location = new System.Drawing.Point(1483, 25);
            this.labelALocation.Name = "labelALocation";
            this.labelALocation.Size = new System.Drawing.Size(18, 20);
            this.labelALocation.TabIndex = 26;
            this.labelALocation.Text = "0";
            // 
            // labelBLocation
            // 
            this.labelBLocation.AutoSize = true;
            this.labelBLocation.Font = new System.Drawing.Font("微软雅黑", 9F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.labelBLocation.Location = new System.Drawing.Point(1483, 65);
            this.labelBLocation.Name = "labelBLocation";
            this.labelBLocation.Size = new System.Drawing.Size(18, 20);
            this.labelBLocation.TabIndex = 41;
            this.labelBLocation.Text = "0";
            // 
            // label1L
            // 
            this.label1L.AutoSize = true;
            this.label1L.Font = new System.Drawing.Font("微软雅黑", 9F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.label1L.Location = new System.Drawing.Point(1483, 105);
            this.label1L.Name = "label1L";
            this.label1L.Size = new System.Drawing.Size(18, 20);
            this.label1L.TabIndex = 42;
            this.label1L.Text = "0";
            // 
            // label2L
            // 
            this.label2L.AutoSize = true;
            this.label2L.Font = new System.Drawing.Font("微软雅黑", 9F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.label2L.Location = new System.Drawing.Point(1483, 145);
            this.label2L.Name = "label2L";
            this.label2L.Size = new System.Drawing.Size(18, 20);
            this.label2L.TabIndex = 43;
            this.label2L.Text = "0";
            // 
            // label3L
            // 
            this.label3L.AutoSize = true;
            this.label3L.Font = new System.Drawing.Font("微软雅黑", 9F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.label3L.Location = new System.Drawing.Point(1483, 185);
            this.label3L.Name = "label3L";
            this.label3L.Size = new System.Drawing.Size(18, 20);
            this.label3L.TabIndex = 44;
            this.label3L.Text = "0";
            // 
            // label17
            // 
            this.label17.AutoSize = true;
            this.label17.Font = new System.Drawing.Font("微软雅黑", 9F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.label17.Location = new System.Drawing.Point(1483, 225);
            this.label17.Name = "label17";
            this.label17.Size = new System.Drawing.Size(18, 20);
            this.label17.TabIndex = 45;
            this.label17.Text = "0";
            // 
            // label4L
            // 
            this.label4L.AutoSize = true;
            this.label4L.Font = new System.Drawing.Font("微软雅黑", 9F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.label4L.Location = new System.Drawing.Point(1483, 225);
            this.label4L.Name = "label4L";
            this.label4L.Size = new System.Drawing.Size(18, 20);
            this.label4L.TabIndex = 46;
            this.label4L.Text = "0";
            // 
            // label5L
            // 
            this.label5L.AutoSize = true;
            this.label5L.Font = new System.Drawing.Font("微软雅黑", 9F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.label5L.Location = new System.Drawing.Point(1483, 265);
            this.label5L.Name = "label5L";
            this.label5L.Size = new System.Drawing.Size(18, 20);
            this.label5L.TabIndex = 47;
            this.label5L.Text = "0";
            // 
            // labelValidP
            // 
            this.labelValidP.AutoSize = true;
            this.labelValidP.Font = new System.Drawing.Font("微软雅黑", 9F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.labelValidP.Location = new System.Drawing.Point(1483, 305);
            this.labelValidP.Name = "labelValidP";
            this.labelValidP.Size = new System.Drawing.Size(18, 20);
            this.labelValidP.TabIndex = 48;
            this.labelValidP.Text = "0";
            // 
            // labelRound
            // 
            this.labelRound.AutoSize = true;
            this.labelRound.Font = new System.Drawing.Font("微软雅黑", 9F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.labelRound.Location = new System.Drawing.Point(1483, 345);
            this.labelRound.Name = "labelRound";
            this.labelRound.Size = new System.Drawing.Size(18, 20);
            this.labelRound.TabIndex = 49;
            this.labelRound.Text = "0";
            // 
            // labelState
            // 
            this.labelState.AutoSize = true;
            this.labelState.Font = new System.Drawing.Font("微软雅黑", 9F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.labelState.Location = new System.Drawing.Point(1483, 385);
            this.labelState.Name = "labelState";
            this.labelState.Size = new System.Drawing.Size(18, 20);
            this.labelState.TabIndex = 50;
            this.labelState.Text = "0";
            // 
            // labelAScore
            // 
            this.labelAScore.AutoSize = true;
            this.labelAScore.Font = new System.Drawing.Font("微软雅黑", 9F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.labelAScore.Location = new System.Drawing.Point(1483, 425);
            this.labelAScore.Name = "labelAScore";
            this.labelAScore.Size = new System.Drawing.Size(18, 20);
            this.labelAScore.TabIndex = 51;
            this.labelAScore.Text = "0";
            // 
            // labelBScore
            // 
            this.labelBScore.AutoSize = true;
            this.labelBScore.Font = new System.Drawing.Font("微软雅黑", 9F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.labelBScore.Location = new System.Drawing.Point(1483, 465);
            this.labelBScore.Name = "labelBScore";
            this.labelBScore.Size = new System.Drawing.Size(18, 20);
            this.labelBScore.TabIndex = 52;
            this.labelBScore.Text = "0";
            // 
            // button_restart
            // 
            this.button_restart.Font = new System.Drawing.Font("微软雅黑", 9F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.button_restart.Location = new System.Drawing.Point(664, 885);
            this.button_restart.Name = "button_restart";
            this.button_restart.Size = new System.Drawing.Size(80, 35);
            this.button_restart.TabIndex = 56;
            this.button_restart.Text = "新游戏";
            this.button_restart.UseVisualStyleBackColor = true;
            this.button_restart.Click += new System.EventHandler(this.button_restart_Click);
            // 
            // numericUpDownScoreA
            // 
            this.numericUpDownScoreA.Font = new System.Drawing.Font("微软雅黑", 9F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.numericUpDownScoreA.Increment = new decimal(new int[] {
            10,
            0,
            0,
            0});
            this.numericUpDownScoreA.Location = new System.Drawing.Point(275, 944);
            this.numericUpDownScoreA.Maximum = new decimal(new int[] {
            10000,
            0,
            0,
            0});
            this.numericUpDownScoreA.Name = "numericUpDownScoreA";
            this.numericUpDownScoreA.Size = new System.Drawing.Size(75, 27);
            this.numericUpDownScoreA.TabIndex = 57;
            // 
            // numericUpDownScoreB
            // 
            this.numericUpDownScoreB.Font = new System.Drawing.Font("微软雅黑", 9F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.numericUpDownScoreB.Increment = new decimal(new int[] {
            10,
            0,
            0,
            0});
            this.numericUpDownScoreB.Location = new System.Drawing.Point(461, 944);
            this.numericUpDownScoreB.Maximum = new decimal(new int[] {
            10000,
            0,
            0,
            0});
            this.numericUpDownScoreB.Name = "numericUpDownScoreB";
            this.numericUpDownScoreB.Size = new System.Drawing.Size(75, 27);
            this.numericUpDownScoreB.TabIndex = 58;
            // 
            // labelAGetScore
            // 
            this.labelAGetScore.AutoSize = true;
            this.labelAGetScore.Font = new System.Drawing.Font("微软雅黑", 9F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.labelAGetScore.Location = new System.Drawing.Point(198, 946);
            this.labelAGetScore.Name = "labelAGetScore";
            this.labelAGetScore.Size = new System.Drawing.Size(54, 20);
            this.labelAGetScore.TabIndex = 59;
            this.labelAGetScore.Text = "A加分:";
            // 
            // labelBGetScore
            // 
            this.labelBGetScore.AutoSize = true;
            this.labelBGetScore.Font = new System.Drawing.Font("微软雅黑", 9F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.labelBGetScore.Location = new System.Drawing.Point(388, 946);
            this.labelBGetScore.Name = "labelBGetScore";
            this.labelBGetScore.Size = new System.Drawing.Size(52, 20);
            this.labelBGetScore.TabIndex = 60;
            this.labelBGetScore.Text = "B加分:";
            // 
            // buttonChangeScore
            // 
            this.buttonChangeScore.Font = new System.Drawing.Font("微软雅黑", 9F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.buttonChangeScore.Location = new System.Drawing.Point(562, 939);
            this.buttonChangeScore.Name = "buttonChangeScore";
            this.buttonChangeScore.Size = new System.Drawing.Size(80, 35);
            this.buttonChangeScore.TabIndex = 61;
            this.buttonChangeScore.Text = "确定";
            this.buttonChangeScore.UseVisualStyleBackColor = true;
            this.buttonChangeScore.Click += new System.EventHandler(this.buttonChangeScore_Click);
            // 
            // numericUpDownTime
            // 
            this.numericUpDownTime.Font = new System.Drawing.Font("微软雅黑", 9F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.numericUpDownTime.Increment = new decimal(new int[] {
            10,
            0,
            0,
            0});
            this.numericUpDownTime.Location = new System.Drawing.Point(9, 911);
            this.numericUpDownTime.Maximum = new decimal(new int[] {
            10000,
            0,
            0,
            0});
            this.numericUpDownTime.Minimum = new decimal(new int[] {
            50,
            0,
            0,
            0});
            this.numericUpDownTime.Name = "numericUpDownTime";
            this.numericUpDownTime.Size = new System.Drawing.Size(75, 27);
            this.numericUpDownTime.TabIndex = 62;
            this.numericUpDownTime.Value = new decimal(new int[] {
            95,
            0,
            0,
            0});
            // 
            // button1
            // 
            this.button1.Font = new System.Drawing.Font("微软雅黑", 9F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.button1.Location = new System.Drawing.Point(90, 906);
            this.button1.Name = "button1";
            this.button1.Size = new System.Drawing.Size(80, 35);
            this.button1.TabIndex = 63;
            this.button1.Text = "确定";
            this.button1.UseVisualStyleBackColor = true;
            this.button1.Click += new System.EventHandler(this.button1_Click);
            // 
            // button_minus10
            // 
            this.button_minus10.Font = new System.Drawing.Font("微软雅黑", 9F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.button_minus10.Location = new System.Drawing.Point(4, 779);
            this.button_minus10.Name = "button_minus10";
            this.button_minus10.Size = new System.Drawing.Size(80, 35);
            this.button_minus10.TabIndex = 64;
            this.button_minus10.Text = "-10";
            this.button_minus10.UseVisualStyleBackColor = true;
            this.button_minus10.Click += new System.EventHandler(this.button_minus10_Click);
            // 
            // button_minus20
            // 
            this.button_minus20.Font = new System.Drawing.Font("微软雅黑", 9F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.button_minus20.Location = new System.Drawing.Point(4, 819);
            this.button_minus20.Name = "button_minus20";
            this.button_minus20.Size = new System.Drawing.Size(80, 35);
            this.button_minus20.TabIndex = 65;
            this.button_minus20.Text = "-20";
            this.button_minus20.UseVisualStyleBackColor = true;
            this.button_minus20.Click += new System.EventHandler(this.button_minus20_Click);
            // 
            // button_minus80
            // 
            this.button_minus80.Font = new System.Drawing.Font("微软雅黑", 9F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.button_minus80.Location = new System.Drawing.Point(4, 860);
            this.button_minus80.Name = "button_minus80";
            this.button_minus80.Size = new System.Drawing.Size(80, 35);
            this.button_minus80.TabIndex = 66;
            this.button_minus80.Text = "-80";
            this.button_minus80.UseVisualStyleBackColor = true;
            this.button_minus80.Click += new System.EventHandler(this.button_minus80_Click);
            // 
            // button_plus50
            // 
            this.button_plus50.Font = new System.Drawing.Font("微软雅黑", 9F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.button_plus50.Location = new System.Drawing.Point(90, 778);
            this.button_plus50.Name = "button_plus50";
            this.button_plus50.Size = new System.Drawing.Size(80, 35);
            this.button_plus50.TabIndex = 67;
            this.button_plus50.Text = "+50";
            this.button_plus50.UseVisualStyleBackColor = true;
            this.button_plus50.Click += new System.EventHandler(this.button_plus50_Click);
            // 
            // button_plus100
            // 
            this.button_plus100.Font = new System.Drawing.Font("微软雅黑", 9F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.button_plus100.Location = new System.Drawing.Point(90, 819);
            this.button_plus100.Name = "button_plus100";
            this.button_plus100.Size = new System.Drawing.Size(80, 35);
            this.button_plus100.TabIndex = 68;
            this.button_plus100.Text = "+100";
            this.button_plus100.UseVisualStyleBackColor = true;
            this.button_plus100.Click += new System.EventHandler(this.button_plus100_Click);
            // 
            // button_plus150
            // 
            this.button_plus150.Font = new System.Drawing.Font("微软雅黑", 9F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.button_plus150.Location = new System.Drawing.Point(90, 860);
            this.button_plus150.Name = "button_plus150";
            this.button_plus150.Size = new System.Drawing.Size(80, 35);
            this.button_plus150.TabIndex = 69;
            this.button_plus150.Text = "+150";
            this.button_plus150.UseVisualStyleBackColor = true;
            this.button_plus150.Click += new System.EventHandler(this.button_plus150_Click);
            // 
            // button_reset
            // 
            this.button_reset.Font = new System.Drawing.Font("微软雅黑", 9F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.button_reset.Location = new System.Drawing.Point(664, 844);
            this.button_reset.Name = "button_reset";
            this.button_reset.Size = new System.Drawing.Size(80, 35);
            this.button_reset.TabIndex = 72;
            this.button_reset.Text = "复位";
            this.button_reset.UseVisualStyleBackColor = true;
            this.button_reset.Click += new System.EventHandler(this.button_reset_Click);
            // 
            // groupBox_car
            // 
            this.groupBox_car.BackColor = System.Drawing.SystemColors.ButtonFace;
            this.groupBox_car.Location = new System.Drawing.Point(194, 731);
            this.groupBox_car.Name = "groupBox_car";
            this.groupBox_car.Size = new System.Drawing.Size(200, 52);
            this.groupBox_car.TabIndex = 73;
            this.groupBox_car.TabStop = false;
            // 
            // radioButton_CarB
            // 
            this.radioButton_CarB.AutoSize = true;
            this.radioButton_CarB.Font = new System.Drawing.Font("微软雅黑", 9F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.radioButton_CarB.Location = new System.Drawing.Point(275, 898);
            this.radioButton_CarB.Name = "radioButton_CarB";
            this.radioButton_CarB.Size = new System.Drawing.Size(54, 24);
            this.radioButton_CarB.TabIndex = 1;
            this.radioButton_CarB.TabStop = true;
            this.radioButton_CarB.Text = "B车";
            this.radioButton_CarB.UseVisualStyleBackColor = true;
            // 
            // radioButton_CarA
            // 
            this.radioButton_CarA.AutoSize = true;
            this.radioButton_CarA.Font = new System.Drawing.Font("微软雅黑", 9F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.radioButton_CarA.Location = new System.Drawing.Point(204, 898);
            this.radioButton_CarA.Name = "radioButton_CarA";
            this.radioButton_CarA.Size = new System.Drawing.Size(56, 24);
            this.radioButton_CarA.TabIndex = 0;
            this.radioButton_CarA.TabStop = true;
            this.radioButton_CarA.Text = "A车";
            this.radioButton_CarA.UseVisualStyleBackColor = true;
            // 
            // button_video
            // 
            this.button_video.Font = new System.Drawing.Font("微软雅黑", 9F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.button_video.Location = new System.Drawing.Point(653, 719);
            this.button_video.Name = "button_video";
            this.button_video.Size = new System.Drawing.Size(100, 35);
            this.button_video.TabIndex = 74;
            this.button_video.Text = "开始录像";
            this.button_video.UseVisualStyleBackColor = true;
            this.button_video.Click += new System.EventHandler(this.button_video_Click);
            // 
            // checkBox_DebugMode
            // 
            this.checkBox_DebugMode.AutoSize = true;
            this.checkBox_DebugMode.Font = new System.Drawing.Font("微软雅黑", 9F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.checkBox_DebugMode.Location = new System.Drawing.Point(551, 808);
            this.checkBox_DebugMode.Name = "checkBox_DebugMode";
            this.checkBox_DebugMode.Size = new System.Drawing.Size(91, 24);
            this.checkBox_DebugMode.TabIndex = 73;
            this.checkBox_DebugMode.Text = "调试模式";
            this.checkBox_DebugMode.UseVisualStyleBackColor = true;
            this.checkBox_DebugMode.CheckedChanged += new System.EventHandler(this.checkBox_DebugMode_CheckedChanged);
            // 
            // setAcarBtn
            // 
            this.setAcarBtn.Font = new System.Drawing.Font("宋体", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.setAcarBtn.Location = new System.Drawing.Point(435, 775);
            this.setAcarBtn.Name = "setAcarBtn";
            this.setAcarBtn.Size = new System.Drawing.Size(97, 57);
            this.setAcarBtn.TabIndex = 138;
            this.setAcarBtn.Text = "设置A车";
            this.setAcarBtn.UseVisualStyleBackColor = true;
            this.setAcarBtn.Click += new System.EventHandler(this.setmycarBtn_Click);
            // 
            // CarYTB
            // 
            this.CarYTB.Location = new System.Drawing.Point(313, 834);
            this.CarYTB.Name = "CarYTB";
            this.CarYTB.Size = new System.Drawing.Size(100, 25);
            this.CarYTB.TabIndex = 135;
            // 
            // CarXTB
            // 
            this.CarXTB.Location = new System.Drawing.Point(313, 780);
            this.CarXTB.Name = "CarXTB";
            this.CarXTB.Size = new System.Drawing.Size(100, 25);
            this.CarXTB.TabIndex = 134;
            // 
            // label27
            // 
            this.label27.AutoSize = true;
            this.label27.Font = new System.Drawing.Font("宋体", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.label27.Location = new System.Drawing.Point(216, 839);
            this.label27.Name = "label27";
            this.label27.Size = new System.Drawing.Size(79, 20);
            this.label27.TabIndex = 133;
            this.label27.Text = "车Y坐标";
            // 
            // label26
            // 
            this.label26.AutoSize = true;
            this.label26.Font = new System.Drawing.Font("宋体", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.label26.Location = new System.Drawing.Point(216, 785);
            this.label26.Name = "label26";
            this.label26.Size = new System.Drawing.Size(79, 20);
            this.label26.TabIndex = 132;
            this.label26.Text = "车X坐标";
            // 
            // setBcarposBtn
            // 
            this.setBcarposBtn.Font = new System.Drawing.Font("宋体", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.setBcarposBtn.Location = new System.Drawing.Point(435, 845);
            this.setBcarposBtn.Name = "setBcarposBtn";
            this.setBcarposBtn.Size = new System.Drawing.Size(97, 54);
            this.setBcarposBtn.TabIndex = 131;
            this.setBcarposBtn.Text = "设置B车";
            this.setBcarposBtn.UseVisualStyleBackColor = true;
            this.setBcarposBtn.Click += new System.EventHandler(this.setBcarposBtn_Click);
            // 
            // label16
            // 
            this.label16.AutoSize = true;
            this.label16.Location = new System.Drawing.Point(518, 679);
            this.label16.Name = "label16";
            this.label16.Size = new System.Drawing.Size(150, 15);
            this.label16.TabIndex = 130;
            this.label16.Text = "下一个乘客终点Y坐标";
            // 
            // label18
            // 
            this.label18.AutoSize = true;
            this.label18.Location = new System.Drawing.Point(518, 632);
            this.label18.Name = "label18";
            this.label18.Size = new System.Drawing.Size(150, 15);
            this.label18.TabIndex = 129;
            this.label18.Text = "下一个乘客终点X坐标";
            // 
            // nextPassengerEndXTB
            // 
            this.nextPassengerEndXTB.Location = new System.Drawing.Point(698, 622);
            this.nextPassengerEndXTB.Name = "nextPassengerEndXTB";
            this.nextPassengerEndXTB.Size = new System.Drawing.Size(74, 25);
            this.nextPassengerEndXTB.TabIndex = 128;
            // 
            // nextPassengerEndYTB
            // 
            this.nextPassengerEndYTB.Location = new System.Drawing.Point(698, 669);
            this.nextPassengerEndYTB.Name = "nextPassengerEndYTB";
            this.nextPassengerEndYTB.Size = new System.Drawing.Size(74, 25);
            this.nextPassengerEndYTB.TabIndex = 127;
            // 
            // label15
            // 
            this.label15.AutoSize = true;
            this.label15.Location = new System.Drawing.Point(219, 632);
            this.label15.Name = "label15";
            this.label15.Size = new System.Drawing.Size(82, 15);
            this.label15.TabIndex = 126;
            this.label15.Text = "第几个乘客";
            // 
            // label14
            // 
            this.label14.AutoSize = true;
            this.label14.Location = new System.Drawing.Point(215, 737);
            this.label14.Name = "label14";
            this.label14.Size = new System.Drawing.Size(150, 15);
            this.label14.TabIndex = 125;
            this.label14.Text = "下一个乘客起点Y坐标";
            // 
            // label13
            // 
            this.label13.AutoSize = true;
            this.label13.Location = new System.Drawing.Point(215, 685);
            this.label13.Name = "label13";
            this.label13.Size = new System.Drawing.Size(150, 15);
            this.label13.TabIndex = 124;
            this.label13.Text = "下一个乘客起点X坐标";
            // 
            // updatePassengerBtn
            // 
            this.updatePassengerBtn.Font = new System.Drawing.Font("宋体", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.updatePassengerBtn.Location = new System.Drawing.Point(521, 715);
            this.updatePassengerBtn.Name = "updatePassengerBtn";
            this.updatePassengerBtn.Size = new System.Drawing.Size(97, 35);
            this.updatePassengerBtn.TabIndex = 123;
            this.updatePassengerBtn.Text = "加乘客";
            this.updatePassengerBtn.UseVisualStyleBackColor = true;
            this.updatePassengerBtn.Click += new System.EventHandler(this.updatePassengerBtn_Click);
            // 
            // nextPassengerTB
            // 
            this.nextPassengerTB.Location = new System.Drawing.Point(399, 622);
            this.nextPassengerTB.Name = "nextPassengerTB";
            this.nextPassengerTB.Size = new System.Drawing.Size(74, 25);
            this.nextPassengerTB.TabIndex = 122;
            // 
            // nextPassengerStartXTB
            // 
            this.nextPassengerStartXTB.Location = new System.Drawing.Point(399, 675);
            this.nextPassengerStartXTB.Name = "nextPassengerStartXTB";
            this.nextPassengerStartXTB.Size = new System.Drawing.Size(74, 25);
            this.nextPassengerStartXTB.TabIndex = 121;
            // 
            // nextPassengerStartYTB
            // 
            this.nextPassengerStartYTB.Location = new System.Drawing.Point(399, 725);
            this.nextPassengerStartYTB.Name = "nextPassengerStartYTB";
            this.nextPassengerStartYTB.Size = new System.Drawing.Size(74, 25);
            this.nextPassengerStartYTB.TabIndex = 120;
            // 
            // round1Btn
            // 
            this.round1Btn.Location = new System.Drawing.Point(1367, 521);
            this.round1Btn.Name = "round1Btn";
            this.round1Btn.Size = new System.Drawing.Size(134, 71);
            this.round1Btn.TabIndex = 151;
            this.round1Btn.Text = "Round to 1";
            this.round1Btn.UseVisualStyleBackColor = true;
            this.round1Btn.Click += new System.EventHandler(this.round1Btn_Click);
            // 
            // deltayawLb
            // 
            this.deltayawLb.AutoSize = true;
            this.deltayawLb.Font = new System.Drawing.Font("宋体", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.deltayawLb.Location = new System.Drawing.Point(1043, 832);
            this.deltayawLb.Name = "deltayawLb";
            this.deltayawLb.Size = new System.Drawing.Size(109, 20);
            this.deltayawLb.TabIndex = 150;
            this.deltayawLb.Text = "deltayawLb";
            // 
            // yawLb
            // 
            this.yawLb.AutoSize = true;
            this.yawLb.Font = new System.Drawing.Font("宋体", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.yawLb.Location = new System.Drawing.Point(1040, 795);
            this.yawLb.Name = "yawLb";
            this.yawLb.Size = new System.Drawing.Size(59, 20);
            this.yawLb.TabIndex = 149;
            this.yawLb.Text = "yawLb";
            // 
            // nowLb
            // 
            this.nowLb.AutoSize = true;
            this.nowLb.Font = new System.Drawing.Font("宋体", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.nowLb.Location = new System.Drawing.Point(1043, 756);
            this.nowLb.Name = "nowLb";
            this.nowLb.Size = new System.Drawing.Size(59, 20);
            this.nowLb.TabIndex = 148;
            this.nowLb.Text = "nowLb";
            // 
            // goLb
            // 
            this.goLb.AutoSize = true;
            this.goLb.Font = new System.Drawing.Font("宋体", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.goLb.Location = new System.Drawing.Point(1040, 717);
            this.goLb.Name = "goLb";
            this.goLb.Size = new System.Drawing.Size(49, 20);
            this.goLb.TabIndex = 147;
            this.goLb.Text = "goLb";
            // 
            // lb2
            // 
            this.lb2.AutoSize = true;
            this.lb2.Font = new System.Drawing.Font("宋体", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.lb2.Location = new System.Drawing.Point(1043, 888);
            this.lb2.Name = "lb2";
            this.lb2.Size = new System.Drawing.Size(299, 20);
            this.lb2.TabIndex = 146;
            this.lb2.Text = "Distance to next destination:";
            // 
            // label24
            // 
            this.label24.AutoSize = true;
            this.label24.Font = new System.Drawing.Font("宋体", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.label24.Location = new System.Drawing.Point(1040, 951);
            this.label24.Name = "label24";
            this.label24.Size = new System.Drawing.Size(129, 20);
            this.label24.TabIndex = 145;
            this.label24.Text = "蓝牙接收信息";
            // 
            // bluetoothLb
            // 
            this.bluetoothLb.AutoSize = true;
            this.bluetoothLb.Font = new System.Drawing.Font("宋体", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.bluetoothLb.Location = new System.Drawing.Point(1194, 941);
            this.bluetoothLb.MinimumSize = new System.Drawing.Size(200, 40);
            this.bluetoothLb.Name = "bluetoothLb";
            this.bluetoothLb.Size = new System.Drawing.Size(289, 40);
            this.bluetoothLb.TabIndex = 144;
            this.bluetoothLb.Text = "Tx:    Bytes    Rx:    Bytes";
            this.bluetoothLb.TextAlign = System.Drawing.ContentAlignment.MiddleCenter;
            // 
            // clearreceiveBtn
            // 
            this.clearreceiveBtn.Font = new System.Drawing.Font("宋体", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.clearreceiveBtn.Location = new System.Drawing.Point(1038, 20);
            this.clearreceiveBtn.Name = "clearreceiveBtn";
            this.clearreceiveBtn.Size = new System.Drawing.Size(86, 35);
            this.clearreceiveBtn.TabIndex = 143;
            this.clearreceiveBtn.Text = "清空";
            this.clearreceiveBtn.UseVisualStyleBackColor = true;
            this.clearreceiveBtn.Click += new System.EventHandler(this.clearreceiveBtn_Click);
            // 
            // receiveTB
            // 
            this.receiveTB.Location = new System.Drawing.Point(1038, 70);
            this.receiveTB.Multiline = true;
            this.receiveTB.Name = "receiveTB";
            this.receiveTB.ScrollBars = System.Windows.Forms.ScrollBars.Vertical;
            this.receiveTB.Size = new System.Drawing.Size(289, 620);
            this.receiveTB.TabIndex = 142;
            // 
            // portCB
            // 
            this.portCB.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList;
            this.portCB.FormattingEnabled = true;
            this.portCB.Location = new System.Drawing.Point(1206, 25);
            this.portCB.Name = "portCB";
            this.portCB.Size = new System.Drawing.Size(121, 23);
            this.portCB.TabIndex = 141;
            // 
            // label20
            // 
            this.label20.AutoSize = true;
            this.label20.Location = new System.Drawing.Point(1148, 28);
            this.label20.Name = "label20";
            this.label20.Size = new System.Drawing.Size(37, 15);
            this.label20.TabIndex = 140;
            this.label20.Text = "串口";
            // 
            // bluetoothBtn
            // 
            this.bluetoothBtn.Font = new System.Drawing.Font("宋体", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.bluetoothBtn.Location = new System.Drawing.Point(1248, 753);
            this.bluetoothBtn.Name = "bluetoothBtn";
            this.bluetoothBtn.Size = new System.Drawing.Size(94, 51);
            this.bluetoothBtn.TabIndex = 139;
            this.bluetoothBtn.Text = "蓝牙连接";
            this.bluetoothBtn.UseVisualStyleBackColor = true;
            this.bluetoothBtn.Click += new System.EventHandler(this.bluetoothBtn_Click);
            // 
            // serialPort1
            // 
            this.serialPort1.DataReceived += new System.IO.Ports.SerialDataReceivedEventHandler(this.SerialPort1_DataReceived);
            // 
            // distanceLb
            // 
            this.distanceLb.AutoSize = true;
            this.distanceLb.Font = new System.Drawing.Font("宋体", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.distanceLb.Location = new System.Drawing.Point(1369, 888);
            this.distanceLb.Name = "distanceLb";
            this.distanceLb.Size = new System.Drawing.Size(19, 20);
            this.distanceLb.TabIndex = 152;
            this.distanceLb.Text = "0";
            // 
            // myIDTB
            // 
            this.myIDTB.Font = new System.Drawing.Font("宋体", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.myIDTB.Location = new System.Drawing.Point(790, 947);
            this.myIDTB.Name = "myIDTB";
            this.myIDTB.Size = new System.Drawing.Size(100, 30);
            this.myIDTB.TabIndex = 154;
            this.myIDTB.Text = "A";
            // 
            // label29
            // 
            this.label29.AutoSize = true;
            this.label29.Font = new System.Drawing.Font("宋体", 22.2F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.label29.Location = new System.Drawing.Point(783, 895);
            this.label29.Name = "label29";
            this.label29.Size = new System.Drawing.Size(169, 38);
            this.label29.TabIndex = 153;
            this.label29.Text = "本车代号";
            // 
            // setmyidBtn
            // 
            this.setmyidBtn.Font = new System.Drawing.Font("微软雅黑", 9F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.setmyidBtn.Location = new System.Drawing.Point(909, 944);
            this.setmyidBtn.Name = "setmyidBtn";
            this.setmyidBtn.Size = new System.Drawing.Size(80, 35);
            this.setmyidBtn.TabIndex = 155;
            this.setmyidBtn.Text = "确定";
            this.setmyidBtn.UseVisualStyleBackColor = true;
            this.setmyidBtn.Click += new System.EventHandler(this.setmyidBtn_Click);
            // 
            // Tracker
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(8F, 15F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.AutoSize = true;
            this.AutoSizeMode = System.Windows.Forms.AutoSizeMode.GrowAndShrink;
            this.ClientSize = new System.Drawing.Size(1568, 1018);
            this.Controls.Add(this.setmyidBtn);
            this.Controls.Add(this.myIDTB);
            this.Controls.Add(this.label29);
            this.Controls.Add(this.distanceLb);
            this.Controls.Add(this.round1Btn);
            this.Controls.Add(this.deltayawLb);
            this.Controls.Add(this.yawLb);
            this.Controls.Add(this.nowLb);
            this.Controls.Add(this.goLb);
            this.Controls.Add(this.lb2);
            this.Controls.Add(this.label24);
            this.Controls.Add(this.bluetoothLb);
            this.Controls.Add(this.clearreceiveBtn);
            this.Controls.Add(this.receiveTB);
            this.Controls.Add(this.portCB);
            this.Controls.Add(this.label20);
            this.Controls.Add(this.bluetoothBtn);
            this.Controls.Add(this.setAcarBtn);
            this.Controls.Add(this.CarYTB);
            this.Controls.Add(this.CarXTB);
            this.Controls.Add(this.label27);
            this.Controls.Add(this.label26);
            this.Controls.Add(this.setBcarposBtn);
            this.Controls.Add(this.label16);
            this.Controls.Add(this.label18);
            this.Controls.Add(this.nextPassengerEndXTB);
            this.Controls.Add(this.nextPassengerEndYTB);
            this.Controls.Add(this.label15);
            this.Controls.Add(this.label14);
            this.Controls.Add(this.label13);
            this.Controls.Add(this.updatePassengerBtn);
            this.Controls.Add(this.nextPassengerTB);
            this.Controls.Add(this.nextPassengerStartXTB);
            this.Controls.Add(this.nextPassengerStartYTB);
            this.Controls.Add(this.radioButton_CarB);
            this.Controls.Add(this.radioButton_CarA);
            this.Controls.Add(this.button_video);
            this.Controls.Add(this.groupBox_car);
            this.Controls.Add(this.checkBox_DebugMode);
            this.Controls.Add(this.button_reset);
            this.Controls.Add(this.button_plus150);
            this.Controls.Add(this.button_plus100);
            this.Controls.Add(this.button_plus50);
            this.Controls.Add(this.button_minus80);
            this.Controls.Add(this.button_minus20);
            this.Controls.Add(this.button_minus10);
            this.Controls.Add(this.button1);
            this.Controls.Add(this.numericUpDownTime);
            this.Controls.Add(this.buttonChangeScore);
            this.Controls.Add(this.labelBGetScore);
            this.Controls.Add(this.labelAGetScore);
            this.Controls.Add(this.numericUpDownScoreB);
            this.Controls.Add(this.numericUpDownScoreA);
            this.Controls.Add(this.button_restart);
            this.Controls.Add(this.labelBScore);
            this.Controls.Add(this.labelAScore);
            this.Controls.Add(this.labelState);
            this.Controls.Add(this.labelRound);
            this.Controls.Add(this.labelValidP);
            this.Controls.Add(this.label5L);
            this.Controls.Add(this.label4L);
            this.Controls.Add(this.label17);
            this.Controls.Add(this.label3L);
            this.Controls.Add(this.label2L);
            this.Controls.Add(this.label1L);
            this.Controls.Add(this.labelBLocation);
            this.Controls.Add(this.label12);
            this.Controls.Add(this.label11);
            this.Controls.Add(this.label10);
            this.Controls.Add(this.label9);
            this.Controls.Add(this.label8);
            this.Controls.Add(this.label7);
            this.Controls.Add(this.label6);
            this.Controls.Add(this.label5);
            this.Controls.Add(this.label4);
            this.Controls.Add(this.label3);
            this.Controls.Add(this.label2);
            this.Controls.Add(this.buttonPause);
            this.Controls.Add(this.buttonStart);
            this.Controls.Add(this.labelALocation);
            this.Controls.Add(this.label1);
            this.Controls.Add(this.nudAreaL);
            this.Controls.Add(this.lblAreaL);
            this.Controls.Add(this.nudValueL);
            this.Controls.Add(this.lblValueL);
            this.Controls.Add(this.nudSat2L);
            this.Controls.Add(this.lblSat2L);
            this.Controls.Add(this.nudSat1L);
            this.Controls.Add(this.lblSat1L);
            this.Controls.Add(this.nudHue2H);
            this.Controls.Add(this.lblHue2H);
            this.Controls.Add(this.nudHue2L);
            this.Controls.Add(this.lblHue2L);
            this.Controls.Add(this.nudHue1H);
            this.Controls.Add(this.lblHueH);
            this.Controls.Add(this.nudHue1L);
            this.Controls.Add(this.lblHue1L);
            this.Controls.Add(this.btnReset);
            this.Controls.Add(this.tbPoint4);
            this.Controls.Add(this.tbPoint3);
            this.Controls.Add(this.tbPoint2);
            this.Controls.Add(this.tbPoint1);
            this.Controls.Add(this.pbCamera);
            this.Controls.Add(this.tbInfo);
            this.Name = "Tracker";
            this.Text = "EDC20HOST";
            this.FormClosed += new System.Windows.Forms.FormClosedEventHandler(this.Tracker_FormClosed);
            this.Load += new System.EventHandler(this.Tracker_Load);
            ((System.ComponentModel.ISupportInitialize)(this.pbCamera)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.nudHue1L)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.nudHue1H)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.nudHue2L)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.nudHue2H)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.nudSat1L)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.nudSat2L)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.nudValueL)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.nudAreaL)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.numericUpDownScoreA)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.numericUpDownScoreB)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.numericUpDownTime)).EndInit();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion
        private System.Windows.Forms.TextBox tbInfo;
        private System.Windows.Forms.PictureBox pbCamera;
        private System.Windows.Forms.TextBox tbPoint1;
        private System.Windows.Forms.TextBox tbPoint2;
        private System.Windows.Forms.TextBox tbPoint3;
        private System.Windows.Forms.TextBox tbPoint4;
        private System.Windows.Forms.Button btnReset;
        private System.Windows.Forms.Label lblHue1L;
        private System.Windows.Forms.NumericUpDown nudHue1L;
        private System.Windows.Forms.NumericUpDown nudHue1H;
        private System.Windows.Forms.Label lblHueH;
        private System.Windows.Forms.NumericUpDown nudHue2L;
        private System.Windows.Forms.Label lblHue2L;
        private System.Windows.Forms.NumericUpDown nudHue2H;
        private System.Windows.Forms.Label lblHue2H;
        private System.Windows.Forms.NumericUpDown nudSat1L;
        private System.Windows.Forms.Label lblSat1L;
        private System.Windows.Forms.NumericUpDown nudSat2L;
        private System.Windows.Forms.Label lblSat2L;
        private System.Windows.Forms.NumericUpDown nudValueL;
        private System.Windows.Forms.Label lblValueL;
        private System.Windows.Forms.NumericUpDown nudAreaL;
        private System.Windows.Forms.Label lblAreaL;
        private System.Windows.Forms.Timer timer100ms;
        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.Button buttonStart;
        private System.Windows.Forms.Button buttonPause;
        private System.Windows.Forms.Label label2;
        private System.Windows.Forms.Label label3;
        private System.Windows.Forms.Label label4;
        private System.Windows.Forms.Label label5;
        private System.Windows.Forms.Label label6;
        private System.Windows.Forms.Label label7;
        private System.Windows.Forms.Label label8;
        private System.Windows.Forms.Label label9;
        private System.Windows.Forms.Label label10;
        private System.Windows.Forms.Label label11;
        private System.Windows.Forms.Label label12;
        private System.Windows.Forms.Label labelALocation;
        private System.Windows.Forms.Label labelBLocation;
        private System.Windows.Forms.Label label1L;
        private System.Windows.Forms.Label label2L;
        private System.Windows.Forms.Label label3L;
        private System.Windows.Forms.Label label17;
        private System.Windows.Forms.Label label4L;
        private System.Windows.Forms.Label label5L;
        private System.Windows.Forms.Label labelValidP;
        private System.Windows.Forms.Label labelRound;
        private System.Windows.Forms.Label labelState;
        private System.Windows.Forms.Label labelAScore;
        private System.Windows.Forms.Label labelBScore;
        private System.Windows.Forms.Button button_restart;
        private System.Windows.Forms.NumericUpDown numericUpDownScoreA;
        private System.Windows.Forms.NumericUpDown numericUpDownScoreB;
        private System.Windows.Forms.Label labelAGetScore;
        private System.Windows.Forms.Label labelBGetScore;
        private System.Windows.Forms.Button buttonChangeScore;
        private System.Windows.Forms.NumericUpDown numericUpDownTime;
        private System.Windows.Forms.Button button1;
        private System.Windows.Forms.Button button_minus10;
        private System.Windows.Forms.Button button_minus20;
        private System.Windows.Forms.Button button_minus80;
        private System.Windows.Forms.Button button_plus50;
        private System.Windows.Forms.Button button_plus100;
        private System.Windows.Forms.Button button_plus150;
        private System.Windows.Forms.Button button_reset;
        private System.Windows.Forms.GroupBox groupBox_car;
        private System.Windows.Forms.Button button_video;
        private System.Windows.Forms.CheckBox checkBox_DebugMode;
        private System.Windows.Forms.RadioButton radioButton_CarB;
        private System.Windows.Forms.RadioButton radioButton_CarA;
        private System.Windows.Forms.Button setAcarBtn;
        private System.Windows.Forms.TextBox CarYTB;
        private System.Windows.Forms.TextBox CarXTB;
        private System.Windows.Forms.Label label27;
        private System.Windows.Forms.Label label26;
        private System.Windows.Forms.Button setBcarposBtn;
        private System.Windows.Forms.Label label16;
        private System.Windows.Forms.Label label18;
        private System.Windows.Forms.TextBox nextPassengerEndXTB;
        private System.Windows.Forms.TextBox nextPassengerEndYTB;
        private System.Windows.Forms.Label label15;
        private System.Windows.Forms.Label label14;
        private System.Windows.Forms.Label label13;
        private System.Windows.Forms.Button updatePassengerBtn;
        private System.Windows.Forms.TextBox nextPassengerTB;
        private System.Windows.Forms.TextBox nextPassengerStartXTB;
        private System.Windows.Forms.TextBox nextPassengerStartYTB;
        private System.Windows.Forms.Button round1Btn;
        private System.Windows.Forms.Label deltayawLb;
        private System.Windows.Forms.Label yawLb;
        private System.Windows.Forms.Label nowLb;
        private System.Windows.Forms.Label goLb;
        private System.Windows.Forms.Label lb2;
        private System.Windows.Forms.Label label24;
        private System.Windows.Forms.Label bluetoothLb;
        private System.Windows.Forms.Button clearreceiveBtn;
        private System.Windows.Forms.TextBox receiveTB;
        private System.Windows.Forms.ComboBox portCB;
        private System.Windows.Forms.Label label20;
        private System.Windows.Forms.Button bluetoothBtn;
        private System.IO.Ports.SerialPort serialPort1;
        private System.Windows.Forms.Label distanceLb;
        private System.Windows.Forms.TextBox myIDTB;
        private System.Windows.Forms.Label label29;
        private System.Windows.Forms.Button setmyidBtn;
    }
}


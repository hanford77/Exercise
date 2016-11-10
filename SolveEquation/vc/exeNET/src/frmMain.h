#pragma once

#include <math.h>
#include <vcclr.h>

public ref class frmMain : public System::Windows::Forms::Form
{
public:
	frmMain(void)
	{
		InitializeComponent();
	}
protected:
   ~frmMain()
	{
		if(components)
		{
			delete components;
		}
	}
private: System::Windows::Forms::GroupBox^  groupBox1;
private: System::Windows::Forms::TextBox^  txtI4;

private: System::Windows::Forms::Label^  label2;
private: System::Windows::Forms::TextBox^  txtR4;

private: System::Windows::Forms::Label^  label1;
private: System::Windows::Forms::Label^  label13;
private: System::Windows::Forms::TextBox^  txtI0;

private: System::Windows::Forms::Label^  label14;
private: System::Windows::Forms::TextBox^  txtR0;

private: System::Windows::Forms::Label^  label15;
private: System::Windows::Forms::Label^  label10;
private: System::Windows::Forms::TextBox^  txtI1;

private: System::Windows::Forms::Label^  label11;
private: System::Windows::Forms::TextBox^  txtR1;

private: System::Windows::Forms::Label^  label12;
private: System::Windows::Forms::Label^  label7;
private: System::Windows::Forms::TextBox^  txtI2;

private: System::Windows::Forms::Label^  label8;
private: System::Windows::Forms::TextBox^  txtR2;

private: System::Windows::Forms::Label^  label9;
private: System::Windows::Forms::Label^  label4;
private: System::Windows::Forms::TextBox^  txtI3;

private: System::Windows::Forms::Label^  label5;
private: System::Windows::Forms::TextBox^  txtR3;

private: System::Windows::Forms::Label^  label6;
private: System::Windows::Forms::Label^  label3;
private: System::Windows::Forms::GroupBox^  groupBox2;

private: System::Windows::Forms::Label^  label19;
private: System::Windows::Forms::TextBox^  txtID;

private: System::Windows::Forms::Label^  label20;
private: System::Windows::Forms::TextBox^  txtRD;

private: System::Windows::Forms::Label^  lblD;

private: System::Windows::Forms::Label^  label22;
private: System::Windows::Forms::TextBox^  txtIC;

private: System::Windows::Forms::Label^  label23;
private: System::Windows::Forms::TextBox^  txtRC;

private: System::Windows::Forms::Label^  lblC;

private: System::Windows::Forms::Label^  label25;
private: System::Windows::Forms::TextBox^  txtIB;

private: System::Windows::Forms::Label^  label26;
private: System::Windows::Forms::TextBox^  txtRB;

private: System::Windows::Forms::Label^  lblB;

private: System::Windows::Forms::Label^  label28;
private: System::Windows::Forms::TextBox^  txtIA;

private: System::Windows::Forms::Label^  label29;
private: System::Windows::Forms::TextBox^  txtRA;

private: System::Windows::Forms::Label^  lblA;

protected: 

protected: 
private:
	System::ComponentModel::Container ^components;

#pragma region Windows Form Designer generated code
	void InitializeComponent(void)
	{
        this->groupBox1 = (gcnew System::Windows::Forms::GroupBox());
        this->label13 = (gcnew System::Windows::Forms::Label());
        this->txtI0 = (gcnew System::Windows::Forms::TextBox());
        this->label14 = (gcnew System::Windows::Forms::Label());
        this->txtR0 = (gcnew System::Windows::Forms::TextBox());
        this->label15 = (gcnew System::Windows::Forms::Label());
        this->label10 = (gcnew System::Windows::Forms::Label());
        this->txtI1 = (gcnew System::Windows::Forms::TextBox());
        this->label11 = (gcnew System::Windows::Forms::Label());
        this->txtR1 = (gcnew System::Windows::Forms::TextBox());
        this->label12 = (gcnew System::Windows::Forms::Label());
        this->label7 = (gcnew System::Windows::Forms::Label());
        this->txtI2 = (gcnew System::Windows::Forms::TextBox());
        this->label8 = (gcnew System::Windows::Forms::Label());
        this->txtR2 = (gcnew System::Windows::Forms::TextBox());
        this->label9 = (gcnew System::Windows::Forms::Label());
        this->label4 = (gcnew System::Windows::Forms::Label());
        this->txtI3 = (gcnew System::Windows::Forms::TextBox());
        this->label5 = (gcnew System::Windows::Forms::Label());
        this->txtR3 = (gcnew System::Windows::Forms::TextBox());
        this->label6 = (gcnew System::Windows::Forms::Label());
        this->label3 = (gcnew System::Windows::Forms::Label());
        this->txtI4 = (gcnew System::Windows::Forms::TextBox());
        this->label2 = (gcnew System::Windows::Forms::Label());
        this->txtR4 = (gcnew System::Windows::Forms::TextBox());
        this->label1 = (gcnew System::Windows::Forms::Label());
        this->groupBox2 = (gcnew System::Windows::Forms::GroupBox());
        this->label19 = (gcnew System::Windows::Forms::Label());
        this->txtID = (gcnew System::Windows::Forms::TextBox());
        this->label20 = (gcnew System::Windows::Forms::Label());
        this->txtRD = (gcnew System::Windows::Forms::TextBox());
        this->lblD = (gcnew System::Windows::Forms::Label());
        this->label22 = (gcnew System::Windows::Forms::Label());
        this->txtIC = (gcnew System::Windows::Forms::TextBox());
        this->label23 = (gcnew System::Windows::Forms::Label());
        this->txtRC = (gcnew System::Windows::Forms::TextBox());
        this->lblC = (gcnew System::Windows::Forms::Label());
        this->label25 = (gcnew System::Windows::Forms::Label());
        this->txtIB = (gcnew System::Windows::Forms::TextBox());
        this->label26 = (gcnew System::Windows::Forms::Label());
        this->txtRB = (gcnew System::Windows::Forms::TextBox());
        this->lblB = (gcnew System::Windows::Forms::Label());
        this->label28 = (gcnew System::Windows::Forms::Label());
        this->txtIA = (gcnew System::Windows::Forms::TextBox());
        this->label29 = (gcnew System::Windows::Forms::Label());
        this->txtRA = (gcnew System::Windows::Forms::TextBox());
        this->lblA = (gcnew System::Windows::Forms::Label());
        this->groupBox1->SuspendLayout();
        this->groupBox2->SuspendLayout();
        this->SuspendLayout();
        // 
        // groupBox1
        // 
        this->groupBox1->Controls->Add(this->label13);
        this->groupBox1->Controls->Add(this->txtI0);
        this->groupBox1->Controls->Add(this->label14);
        this->groupBox1->Controls->Add(this->txtR0);
        this->groupBox1->Controls->Add(this->label15);
        this->groupBox1->Controls->Add(this->label10);
        this->groupBox1->Controls->Add(this->txtI1);
        this->groupBox1->Controls->Add(this->label11);
        this->groupBox1->Controls->Add(this->txtR1);
        this->groupBox1->Controls->Add(this->label12);
        this->groupBox1->Controls->Add(this->label7);
        this->groupBox1->Controls->Add(this->txtI2);
        this->groupBox1->Controls->Add(this->label8);
        this->groupBox1->Controls->Add(this->txtR2);
        this->groupBox1->Controls->Add(this->label9);
        this->groupBox1->Controls->Add(this->label4);
        this->groupBox1->Controls->Add(this->txtI3);
        this->groupBox1->Controls->Add(this->label5);
        this->groupBox1->Controls->Add(this->txtR3);
        this->groupBox1->Controls->Add(this->label6);
        this->groupBox1->Controls->Add(this->label3);
        this->groupBox1->Controls->Add(this->txtI4);
        this->groupBox1->Controls->Add(this->label2);
        this->groupBox1->Controls->Add(this->txtR4);
        this->groupBox1->Controls->Add(this->label1);
        this->groupBox1->Location = System::Drawing::Point(7, 5);
        this->groupBox1->Name = L"groupBox1";
        this->groupBox1->Size = System::Drawing::Size(531, 167);
        this->groupBox1->TabIndex = 0;
        this->groupBox1->TabStop = false;
        this->groupBox1->Text = L"方程系数";
        // 
        // label13
        // 
        this->label13->AutoSize = true;
        this->label13->Location = System::Drawing::Point(508, 137);
        this->label13->Name = L"label13";
        this->label13->Size = System::Drawing::Size(11, 12);
        this->label13->TabIndex = 24;
        this->label13->Text = L"i";
        // 
        // txtI0
        // 
        this->txtI0->Location = System::Drawing::Point(296, 133);
        this->txtI0->Name = L"txtI0";
        this->txtI0->Size = System::Drawing::Size(199, 21);
        this->txtI0->TabIndex = 23;
        this->txtI0->TextChanged += gcnew System::EventHandler(this, &frmMain::OnTextChanged);
        // 
        // label14
        // 
        this->label14->AutoSize = true;
        this->label14->Location = System::Drawing::Point(272, 137);
        this->label14->Name = L"label14";
        this->label14->Size = System::Drawing::Size(11, 12);
        this->label14->TabIndex = 22;
        this->label14->Text = L"+";
        // 
        // txtR0
        // 
        this->txtR0->Location = System::Drawing::Point(60, 133);
        this->txtR0->Name = L"txtR0";
        this->txtR0->Size = System::Drawing::Size(199, 21);
        this->txtR0->TabIndex = 21;
        this->txtR0->TextChanged += gcnew System::EventHandler(this, &frmMain::OnTextChanged);
        // 
        // label15
        // 
        this->label15->AutoSize = true;
        this->label15->Location = System::Drawing::Point(6, 137);
        this->label15->Name = L"label15";
        this->label15->Size = System::Drawing::Size(41, 12);
        this->label15->TabIndex = 20;
        this->label15->Text = L"0 次项";
        // 
        // label10
        // 
        this->label10->AutoSize = true;
        this->label10->Location = System::Drawing::Point(508, 108);
        this->label10->Name = L"label10";
        this->label10->Size = System::Drawing::Size(11, 12);
        this->label10->TabIndex = 19;
        this->label10->Text = L"i";
        // 
        // txtI1
        // 
        this->txtI1->Location = System::Drawing::Point(296, 104);
        this->txtI1->Name = L"txtI1";
        this->txtI1->Size = System::Drawing::Size(199, 21);
        this->txtI1->TabIndex = 18;
        this->txtI1->TextChanged += gcnew System::EventHandler(this, &frmMain::OnTextChanged);
        // 
        // label11
        // 
        this->label11->AutoSize = true;
        this->label11->Location = System::Drawing::Point(272, 108);
        this->label11->Name = L"label11";
        this->label11->Size = System::Drawing::Size(11, 12);
        this->label11->TabIndex = 17;
        this->label11->Text = L"+";
        // 
        // txtR1
        // 
        this->txtR1->Location = System::Drawing::Point(60, 104);
        this->txtR1->Name = L"txtR1";
        this->txtR1->Size = System::Drawing::Size(199, 21);
        this->txtR1->TabIndex = 16;
        this->txtR1->TextChanged += gcnew System::EventHandler(this, &frmMain::OnTextChanged);
        // 
        // label12
        // 
        this->label12->AutoSize = true;
        this->label12->Location = System::Drawing::Point(6, 108);
        this->label12->Name = L"label12";
        this->label12->Size = System::Drawing::Size(41, 12);
        this->label12->TabIndex = 15;
        this->label12->Text = L"1 次项";
        // 
        // label7
        // 
        this->label7->AutoSize = true;
        this->label7->Location = System::Drawing::Point(508, 79);
        this->label7->Name = L"label7";
        this->label7->Size = System::Drawing::Size(11, 12);
        this->label7->TabIndex = 14;
        this->label7->Text = L"i";
        // 
        // txtI2
        // 
        this->txtI2->Location = System::Drawing::Point(296, 75);
        this->txtI2->Name = L"txtI2";
        this->txtI2->Size = System::Drawing::Size(199, 21);
        this->txtI2->TabIndex = 13;
        this->txtI2->TextChanged += gcnew System::EventHandler(this, &frmMain::OnTextChanged);
        // 
        // label8
        // 
        this->label8->AutoSize = true;
        this->label8->Location = System::Drawing::Point(272, 79);
        this->label8->Name = L"label8";
        this->label8->Size = System::Drawing::Size(11, 12);
        this->label8->TabIndex = 12;
        this->label8->Text = L"+";
        // 
        // txtR2
        // 
        this->txtR2->Location = System::Drawing::Point(60, 75);
        this->txtR2->Name = L"txtR2";
        this->txtR2->Size = System::Drawing::Size(199, 21);
        this->txtR2->TabIndex = 11;
        this->txtR2->TextChanged += gcnew System::EventHandler(this, &frmMain::OnTextChanged);
        // 
        // label9
        // 
        this->label9->AutoSize = true;
        this->label9->Location = System::Drawing::Point(6, 79);
        this->label9->Name = L"label9";
        this->label9->Size = System::Drawing::Size(41, 12);
        this->label9->TabIndex = 10;
        this->label9->Text = L"2 次项";
        // 
        // label4
        // 
        this->label4->AutoSize = true;
        this->label4->Location = System::Drawing::Point(508, 50);
        this->label4->Name = L"label4";
        this->label4->Size = System::Drawing::Size(11, 12);
        this->label4->TabIndex = 9;
        this->label4->Text = L"i";
        // 
        // txtI3
        // 
        this->txtI3->Location = System::Drawing::Point(296, 46);
        this->txtI3->Name = L"txtI3";
        this->txtI3->Size = System::Drawing::Size(199, 21);
        this->txtI3->TabIndex = 8;
        this->txtI3->TextChanged += gcnew System::EventHandler(this, &frmMain::OnTextChanged);
        // 
        // label5
        // 
        this->label5->AutoSize = true;
        this->label5->Location = System::Drawing::Point(272, 50);
        this->label5->Name = L"label5";
        this->label5->Size = System::Drawing::Size(11, 12);
        this->label5->TabIndex = 7;
        this->label5->Text = L"+";
        // 
        // txtR3
        // 
        this->txtR3->Location = System::Drawing::Point(60, 46);
        this->txtR3->Name = L"txtR3";
        this->txtR3->Size = System::Drawing::Size(199, 21);
        this->txtR3->TabIndex = 6;
        this->txtR3->TextChanged += gcnew System::EventHandler(this, &frmMain::OnTextChanged);
        // 
        // label6
        // 
        this->label6->AutoSize = true;
        this->label6->Location = System::Drawing::Point(6, 50);
        this->label6->Name = L"label6";
        this->label6->Size = System::Drawing::Size(41, 12);
        this->label6->TabIndex = 5;
        this->label6->Text = L"3 次项";
        // 
        // label3
        // 
        this->label3->AutoSize = true;
        this->label3->Location = System::Drawing::Point(508, 21);
        this->label3->Name = L"label3";
        this->label3->Size = System::Drawing::Size(11, 12);
        this->label3->TabIndex = 4;
        this->label3->Text = L"i";
        // 
        // txtI4
        // 
        this->txtI4->Location = System::Drawing::Point(296, 17);
        this->txtI4->Name = L"txtI4";
        this->txtI4->Size = System::Drawing::Size(199, 21);
        this->txtI4->TabIndex = 3;
        this->txtI4->TextChanged += gcnew System::EventHandler(this, &frmMain::OnTextChanged);
        // 
        // label2
        // 
        this->label2->AutoSize = true;
        this->label2->Location = System::Drawing::Point(272, 21);
        this->label2->Name = L"label2";
        this->label2->Size = System::Drawing::Size(11, 12);
        this->label2->TabIndex = 2;
        this->label2->Text = L"+";
        // 
        // txtR4
        // 
        this->txtR4->Location = System::Drawing::Point(60, 17);
        this->txtR4->Name = L"txtR4";
        this->txtR4->Size = System::Drawing::Size(199, 21);
        this->txtR4->TabIndex = 1;
        this->txtR4->TextChanged += gcnew System::EventHandler(this, &frmMain::OnTextChanged);
        // 
        // label1
        // 
        this->label1->AutoSize = true;
        this->label1->Location = System::Drawing::Point(6, 21);
        this->label1->Name = L"label1";
        this->label1->Size = System::Drawing::Size(41, 12);
        this->label1->TabIndex = 0;
        this->label1->Text = L"4 次项";
        // 
        // groupBox2
        // 
        this->groupBox2->Controls->Add(this->label19);
        this->groupBox2->Controls->Add(this->txtID);
        this->groupBox2->Controls->Add(this->label20);
        this->groupBox2->Controls->Add(this->txtRD);
        this->groupBox2->Controls->Add(this->lblD);
        this->groupBox2->Controls->Add(this->label22);
        this->groupBox2->Controls->Add(this->txtIC);
        this->groupBox2->Controls->Add(this->label23);
        this->groupBox2->Controls->Add(this->txtRC);
        this->groupBox2->Controls->Add(this->lblC);
        this->groupBox2->Controls->Add(this->label25);
        this->groupBox2->Controls->Add(this->txtIB);
        this->groupBox2->Controls->Add(this->label26);
        this->groupBox2->Controls->Add(this->txtRB);
        this->groupBox2->Controls->Add(this->lblB);
        this->groupBox2->Controls->Add(this->label28);
        this->groupBox2->Controls->Add(this->txtIA);
        this->groupBox2->Controls->Add(this->label29);
        this->groupBox2->Controls->Add(this->txtRA);
        this->groupBox2->Controls->Add(this->lblA);
        this->groupBox2->Location = System::Drawing::Point(8, 176);
        this->groupBox2->Name = L"groupBox2";
        this->groupBox2->Size = System::Drawing::Size(531, 136);
        this->groupBox2->TabIndex = 1;
        this->groupBox2->TabStop = false;
        this->groupBox2->Text = L"方程的解";
        // 
        // label19
        // 
        this->label19->AutoSize = true;
        this->label19->Location = System::Drawing::Point(508, 108);
        this->label19->Name = L"label19";
        this->label19->Size = System::Drawing::Size(11, 12);
        this->label19->TabIndex = 19;
        this->label19->Text = L"i";
        // 
        // txtID
        // 
        this->txtID->Location = System::Drawing::Point(296, 104);
        this->txtID->Name = L"txtID";
        this->txtID->ReadOnly = true;
        this->txtID->Size = System::Drawing::Size(199, 21);
        this->txtID->TabIndex = 18;
        // 
        // label20
        // 
        this->label20->AutoSize = true;
        this->label20->Location = System::Drawing::Point(272, 108);
        this->label20->Name = L"label20";
        this->label20->Size = System::Drawing::Size(11, 12);
        this->label20->TabIndex = 17;
        this->label20->Text = L"+";
        // 
        // txtRD
        // 
        this->txtRD->Location = System::Drawing::Point(60, 104);
        this->txtRD->Name = L"txtRD";
        this->txtRD->ReadOnly = true;
        this->txtRD->Size = System::Drawing::Size(199, 21);
        this->txtRD->TabIndex = 16;
        // 
        // lblD
        // 
        this->lblD->AutoSize = true;
        this->lblD->Location = System::Drawing::Point(6, 108);
        this->lblD->Name = L"lblD";
        this->lblD->Size = System::Drawing::Size(17, 12);
        this->lblD->TabIndex = 15;
        this->lblD->Text = L"x4";
        // 
        // label22
        // 
        this->label22->AutoSize = true;
        this->label22->Location = System::Drawing::Point(508, 79);
        this->label22->Name = L"label22";
        this->label22->Size = System::Drawing::Size(11, 12);
        this->label22->TabIndex = 14;
        this->label22->Text = L"i";
        // 
        // txtIC
        // 
        this->txtIC->Location = System::Drawing::Point(296, 75);
        this->txtIC->Name = L"txtIC";
        this->txtIC->ReadOnly = true;
        this->txtIC->Size = System::Drawing::Size(199, 21);
        this->txtIC->TabIndex = 13;
        // 
        // label23
        // 
        this->label23->AutoSize = true;
        this->label23->Location = System::Drawing::Point(272, 79);
        this->label23->Name = L"label23";
        this->label23->Size = System::Drawing::Size(11, 12);
        this->label23->TabIndex = 12;
        this->label23->Text = L"+";
        // 
        // txtRC
        // 
        this->txtRC->Location = System::Drawing::Point(60, 75);
        this->txtRC->Name = L"txtRC";
        this->txtRC->ReadOnly = true;
        this->txtRC->Size = System::Drawing::Size(199, 21);
        this->txtRC->TabIndex = 11;
        // 
        // lblC
        // 
        this->lblC->AutoSize = true;
        this->lblC->Location = System::Drawing::Point(6, 79);
        this->lblC->Name = L"lblC";
        this->lblC->Size = System::Drawing::Size(17, 12);
        this->lblC->TabIndex = 10;
        this->lblC->Text = L"x3";
        // 
        // label25
        // 
        this->label25->AutoSize = true;
        this->label25->Location = System::Drawing::Point(508, 50);
        this->label25->Name = L"label25";
        this->label25->Size = System::Drawing::Size(11, 12);
        this->label25->TabIndex = 9;
        this->label25->Text = L"i";
        // 
        // txtIB
        // 
        this->txtIB->Location = System::Drawing::Point(296, 46);
        this->txtIB->Name = L"txtIB";
        this->txtIB->ReadOnly = true;
        this->txtIB->Size = System::Drawing::Size(199, 21);
        this->txtIB->TabIndex = 8;
        // 
        // label26
        // 
        this->label26->AutoSize = true;
        this->label26->Location = System::Drawing::Point(272, 50);
        this->label26->Name = L"label26";
        this->label26->Size = System::Drawing::Size(11, 12);
        this->label26->TabIndex = 7;
        this->label26->Text = L"+";
        // 
        // txtRB
        // 
        this->txtRB->Location = System::Drawing::Point(60, 46);
        this->txtRB->Name = L"txtRB";
        this->txtRB->ReadOnly = true;
        this->txtRB->Size = System::Drawing::Size(199, 21);
        this->txtRB->TabIndex = 6;
        // 
        // lblB
        // 
        this->lblB->AutoSize = true;
        this->lblB->Location = System::Drawing::Point(6, 50);
        this->lblB->Name = L"lblB";
        this->lblB->Size = System::Drawing::Size(17, 12);
        this->lblB->TabIndex = 5;
        this->lblB->Text = L"x2";
        // 
        // label28
        // 
        this->label28->AutoSize = true;
        this->label28->Location = System::Drawing::Point(508, 21);
        this->label28->Name = L"label28";
        this->label28->Size = System::Drawing::Size(11, 12);
        this->label28->TabIndex = 4;
        this->label28->Text = L"i";
        // 
        // txtIA
        // 
        this->txtIA->Location = System::Drawing::Point(296, 17);
        this->txtIA->Name = L"txtIA";
        this->txtIA->ReadOnly = true;
        this->txtIA->Size = System::Drawing::Size(199, 21);
        this->txtIA->TabIndex = 3;
        // 
        // label29
        // 
        this->label29->AutoSize = true;
        this->label29->Location = System::Drawing::Point(272, 21);
        this->label29->Name = L"label29";
        this->label29->Size = System::Drawing::Size(11, 12);
        this->label29->TabIndex = 2;
        this->label29->Text = L"+";
        // 
        // txtRA
        // 
        this->txtRA->Location = System::Drawing::Point(60, 17);
        this->txtRA->Name = L"txtRA";
        this->txtRA->ReadOnly = true;
        this->txtRA->Size = System::Drawing::Size(199, 21);
        this->txtRA->TabIndex = 1;
        // 
        // lblA
        // 
        this->lblA->AutoSize = true;
        this->lblA->Location = System::Drawing::Point(6, 21);
        this->lblA->Name = L"lblA";
        this->lblA->Size = System::Drawing::Size(17, 12);
        this->lblA->TabIndex = 0;
        this->lblA->Text = L"x1";
        // 
        // frmMain
        // 
        this->ClientSize = System::Drawing::Size(546, 320);
        this->Controls->Add(this->groupBox2);
        this->Controls->Add(this->groupBox1);
        this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::FixedSingle;
        this->MaximizeBox = false;
        this->MinimizeBox = false;
        this->Name = L"frmMain";
        this->Text = L"求解一元四次方程";
        this->groupBox1->ResumeLayout(false);
        this->groupBox1->PerformLayout();
        this->groupBox2->ResumeLayout(false);
        this->groupBox2->PerformLayout();
        this->ResumeLayout(false);

    }
#pragma endregion
private: System::Void OnTextChanged(System::Object^  sender, System::EventArgs^  e)
    {
        double z[10];
        {//读取方程系数
            pin_ptr<const wchar_t> wch;
            z[0] = wcstod(wch = PtrToStringChars(txtR0->Text),NULL);
            z[1] = wcstod(wch = PtrToStringChars(txtI0->Text),NULL);
            z[2] = wcstod(wch = PtrToStringChars(txtR1->Text),NULL);
            z[3] = wcstod(wch = PtrToStringChars(txtI1->Text),NULL);
            z[4] = wcstod(wch = PtrToStringChars(txtR2->Text),NULL);
            z[5] = wcstod(wch = PtrToStringChars(txtI2->Text),NULL);
            z[6] = wcstod(wch = PtrToStringChars(txtR3->Text),NULL);
            z[7] = wcstod(wch = PtrToStringChars(txtI3->Text),NULL);
            z[8] = wcstod(wch = PtrToStringChars(txtR4->Text),NULL);
            z[9] = wcstod(wch = PtrToStringChars(txtI4->Text),NULL);
        }
        double  x[12];
        int     n   =   SolveEquation(z,x);
        const double d = 1e-10;
        if (n >= 1)
        {
            txtRA->Text = x[0].ToString();
            txtIA->Text = x[1].ToString();
            lblA->Text = x[2].ToString("0.e+000");
            lblA->ForeColor = fabs(x[2]) > d ? System::Drawing::Color::Red : System::Drawing::Color::Blue;
        }
        else
        {
            lblA->Text = ""; txtRA->Text = ""; txtIA->Text = "";
        }
        if (n >= 2)
        {
            txtRB->Text = x[3].ToString();
            txtIB->Text = x[4].ToString();
            lblB->Text = x[5].ToString("0.e+000");
            lblB->ForeColor = fabs(x[5]) > d ? System::Drawing::Color::Red : System::Drawing::Color::Blue;
        }
        else
        {
            lblB->Text = ""; txtRB->Text = ""; txtIB->Text = "";
        }
        if (n >= 3)
        {
            txtRC->Text = x[6].ToString();
            txtIC->Text = x[7].ToString();
            lblC->Text = x[8].ToString("0.e+000");
            lblC->ForeColor = fabs(x[8]) > d ? System::Drawing::Color::Red : System::Drawing::Color::Blue;
        }
        else
        {
            lblC->Text = ""; txtRC->Text = ""; txtIC->Text = "";
        }
        if (n >= 4)
        {
            txtRD->Text = x[9].ToString();
            txtID->Text = x[10].ToString();
            lblD->Text = x[11].ToString("0.e+000");
            lblD->ForeColor = fabs(x[11]) > d ? System::Drawing::Color::Red : System::Drawing::Color::Blue;
        }
        else
        {
            lblD->Text = ""; txtRD->Text = ""; txtID->Text = "";
        }
    }
};

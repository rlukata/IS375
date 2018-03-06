#pragma once

namespace ramiLukata_Assignment6 {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// Summary for helloWorld
	/// </summary>
	public ref class helloWorld : public System::Windows::Forms::Form
	{
	public:
		helloWorld(void)
		{
			InitializeComponent();
			//
			//TODO: Add the constructor code here
			//
		}

	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~helloWorld()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::Button^  sayHelloButton;
	private: System::Windows::Forms::Label^  showHelloLabel;
	protected:

	private:
		/// <summary>
		/// Required designer variable.
		/// </summary>
		System::ComponentModel::Container ^components;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
		void InitializeComponent(void)
		{
			this->sayHelloButton = (gcnew System::Windows::Forms::Button());
			this->showHelloLabel = (gcnew System::Windows::Forms::Label());
			this->SuspendLayout();
			// 
			// sayHelloButton
			// 
			this->sayHelloButton->Location = System::Drawing::Point(13, 13);
			this->sayHelloButton->Name = L"sayHelloButton";
			this->sayHelloButton->Size = System::Drawing::Size(236, 58);
			this->sayHelloButton->TabIndex = 0;
			this->sayHelloButton->Text = L"Press me!";
			this->sayHelloButton->UseVisualStyleBackColor = true;
			this->sayHelloButton->Click += gcnew System::EventHandler(this, &helloWorld::sayHelloButton_Click);
			// 
			// showHelloLabel
			// 
			this->showHelloLabel->AutoSize = true;
			this->showHelloLabel->Location = System::Drawing::Point(12, 93);
			this->showHelloLabel->Name = L"showHelloLabel";
			this->showHelloLabel->Size = System::Drawing::Size(0, 13);
			this->showHelloLabel->TabIndex = 1;
			this->showHelloLabel->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			// 
			// helloWorld
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(261, 120);
			this->Controls->Add(this->showHelloLabel);
			this->Controls->Add(this->sayHelloButton);
			this->Name = L"helloWorld";
			this->Text = L"helloWorld";
			this->Load += gcnew System::EventHandler(this, &helloWorld::helloWorld_Load);
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
	private: System::Void helloWorld_Load(System::Object^  sender, System::EventArgs^  e) {
	}
	private: System::Void sayHelloButton_Click(System::Object^  sender, System::EventArgs^  e) {
				 showHelloLabel->Text = "Hello World! (through Windows forms)";
	}
	};
}

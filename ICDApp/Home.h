#pragma once
#include <string>

namespace ICDApp {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// Summary for Home
	/// </summary>
	public ref class Home : public System::Windows::Forms::Form
	{
	public:
		Home(void)
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
		~Home()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::Button^ button_openConnection;
	protected:
	private: System::Windows::Forms::Button^ button_closeConnection;

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
			this->button_openConnection = (gcnew System::Windows::Forms::Button());
			this->button_closeConnection = (gcnew System::Windows::Forms::Button());
			this->SuspendLayout();
			// 
			// button_openConnection
			// 
			this->button_openConnection->Location = System::Drawing::Point(490, 133);
			this->button_openConnection->Name = L"button_openConnection";
			this->button_openConnection->Size = System::Drawing::Size(164, 44);
			this->button_openConnection->TabIndex = 0;
			this->button_openConnection->Text = L"Open Connection";
			this->button_openConnection->UseVisualStyleBackColor = true;
			// 
			// button_closeConnection
			// 
			this->button_closeConnection->Location = System::Drawing::Point(490, 183);
			this->button_closeConnection->Name = L"button_closeConnection";
			this->button_closeConnection->Size = System::Drawing::Size(164, 44);
			this->button_closeConnection->TabIndex = 1;
			this->button_closeConnection->Text = L"Close Connection";
			this->button_closeConnection->UseVisualStyleBackColor = true;
			// 
			// Home
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(8, 16);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(817, 510);
			this->Controls->Add(this->button_closeConnection);
			this->Controls->Add(this->button_openConnection);
			this->Name = L"Home";
			this->Text = L"Home";
			this->ResumeLayout(false);

		}
#pragma endregion
	};
}

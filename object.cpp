//---------------------------------------------------------------------------

#include <vcl.h>
#include <inifiles.hpp>
#include <process.h>
#include <string.h>
#include <iostream.h>
#include <conio.h>
#include <stdio.h>
#pragma hdrstop

#include "object.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "AdvTabSet"
#pragma resource "*.dfm"
TObject_form *Object_form;

//���������� �������� �����
AnsiString lngopt;
//
AnsiString plug;
//---------------------------------------------------------------------------
__fastcall TObject_form::TObject_form(TComponent* Owner)
	: TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TObject_form::FormClose(TObject *Sender, TCloseAction &Action)
{  	//��� �������� ����� ��������� �������� ����� �������� � ����
Object_form->ListBox1->Items->SaveToFile(ExtractFilePath(Application->ExeName)+"\\plugin\\module.sw");
Object_form->ListBox2->Items->SaveToFile(ExtractFilePath(Application->ExeName)+"\\plugin\\object.sw");
//������ ����������� ��� ��������
TRect r1,r2;
r1 = Rect(Left+Width/2,Top+Height/2,Left+Width/2,Top+Height/2);
r2 = BoundsRect;
DrawAnimatedRects(Handle,IDANI_CAPTION,&r2,&r1);
}
//---------------------------------------------------------------------------

void __fastcall TObject_form::FormCreate(TObject *Sender)
{
Object_form->ListBox1->Items->LoadFromFile(ExtractFilePath(Application->ExeName)+"\\plugin\\module.sw");
Object_form->ListBox2->Items->LoadFromFile(ExtractFilePath(Application->ExeName)+"\\plugin\\object.sw");
//������ ������������� ��� ��������
TRect r1,r2;
r1 = Rect(Left+Width/2,Top+Height/2,Left+Width/2,Top+Height/2);
r2 = BoundsRect;
DrawAnimatedRects(Handle,IDANI_CAPTION,&r1,&r2);
Ini = new TIniFile(ExtractFilePath(Application->ExeName)+"\\Data\\config.ini");
lngopt=Ini->ReadString("lngflag","active","");
 //�������� ������� �����
if(lngopt=="gb")
{
 Inilng = new TIniFile(ExtractFilePath(Application->ExeName)+"\\Data\\eng.lng");
}
if(lngopt=="ua")
{
 Inilng = new TIniFile(ExtractFilePath(Application->ExeName)+"\\Data\\ua.lng");
 }
if(lngopt=="ru")
{
 Inilng = new TIniFile(ExtractFilePath(Application->ExeName)+"\\Data\\rus.lng");
}
Object_form->Caption=Inilng->ReadString("module","obj1","");
Object_form->AdvTabSet1->AdvTabs->Items[0]->Caption=Inilng->ReadString("module","obj2","");
Object_form->AdvTabSet1->AdvTabs->Items[1]->Caption=Inilng->ReadString("module","obj3","");

}
//---------------------------------------------------------------------------
void __fastcall TObject_form::N2Click(TObject *Sender)
{//������� ��������� ������ �� ������
ListBox1->Clear();
ShowMessage("������ ������!");
}
//---------------------------------------------------------------------------


void __fastcall TObject_form::ListBox2DblClick(TObject *Sender)
{ //�������� ������ ���������

    for(int i = 0; i < ListBox2->Items->Count; i++)

    if(ListBox2->Selected[i])
	plug = ExtractFilePath(Application->ExeName)+"\\plugin\\"+ListBox2->Items->Strings[i];
	//system(plug.c_str());
	WinExec(plug.c_str(), SW_HIDE);

//ShowMessage("��������� ������ �� ������!\n�������� �� �� ����������, ���������� ��������� ����� � ���������!");

}
//---------------------------------------------------------------------------

void __fastcall TObject_form::N1Click(TObject *Sender)
{
  //�������� ����� ������ � ������
  if(!OpenDialog1->Execute())return;
Object_form->ListBox1->Items->Add(ExtractFileName(OpenDialog1->FileName));
}
//---------------------------------------------------------------------------


void __fastcall TObject_form::AdvTabSet1Change(TObject *Sender, int NewTab, bool &AllowChange)

{      //������������� ����� ���������
switch (AdvTabSet1->TabIndex)
{
case 1: ListBox2->Visible=true;
{ListBox1->Visible=false;}
		 break;
case 0: ListBox1->Visible=true;
{ListBox2->Visible=false;}
		 break;
		 }
}
//---------------------------------------------------------------------------

void __fastcall TObject_form::N3Click(TObject *Sender)
{   //��������� ������
  if(!OpenDialog2->Execute())return;
Object_form->ListBox2->Items->Add(ExtractFileName(OpenDialog2->FileName));
}
//---------------------------------------------------------------------------

void __fastcall TObject_form::N4Click(TObject *Sender)
{ //������� ��������� ������
for(int i = 0; i < ListBox2->Items->Count; i++)
if(ListBox2->Selected[i])
{ Object_form->ListBox2->Items->Delete(StrToInt(ListBox2->Items->Strings[i]));
}

}
//---------------------------------------------------------------------------



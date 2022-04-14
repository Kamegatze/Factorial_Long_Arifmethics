// MyNewDialog.cpp : implementation file
//

#include "pch.h"
#include "BaseApp.h"
#include "afxdialogex.h"
#include "MyNewDialog.h"
#include <Cstring>


// MyNewDialog dialog

IMPLEMENT_DYNAMIC(MyNewDialog, CDialogEx)

MyNewDialog::MyNewDialog(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG1, pParent)
{

}

MyNewDialog::~MyNewDialog()
{
}

void MyNewDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(MyNewDialog, CDialogEx)
	ON_BN_CLICKED(IDOK, &MyNewDialog::OnBnClickedOk)
END_MESSAGE_MAP()


// MyNewDialog message handlers


void MyNewDialog::OnBnClickedOk()
{
	// TODO: Add your control notification handler code here
	GetDlgItemText(IDC_EDIT1, stroka);
	CDialogEx::OnOK();
}

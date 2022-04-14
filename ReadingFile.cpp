// ReadingFile.cpp : implementation file
//

#include "pch.h"
#include "BaseApp.h"
#include "afxdialogex.h"
#include "ReadingFile.h"


// ReadingFile dialog

IMPLEMENT_DYNAMIC(ReadingFile, CDialogEx)

ReadingFile::ReadingFile(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_BASEAPP_DIALOG, pParent)
{

}

ReadingFile::~ReadingFile()
{
}

void ReadingFile::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(ReadingFile, CDialogEx)
END_MESSAGE_MAP()


// ReadingFile message handlers

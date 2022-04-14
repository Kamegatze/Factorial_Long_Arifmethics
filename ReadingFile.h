#pragma once
#include "afxdialogex.h"


// ReadingFile dialog

class ReadingFile : public CDialogEx
{
	DECLARE_DYNAMIC(ReadingFile)

public:
	ReadingFile(CWnd* pParent = nullptr);   // standard constructor
	virtual ~ReadingFile();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG1 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
};

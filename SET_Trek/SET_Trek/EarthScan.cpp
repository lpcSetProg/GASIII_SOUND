// EarthScan.cpp : implementation file
//

#include "stdafx.h"
#include "EarthScan.h"
#include "afxdialogex.h"


// EarthScan dialog

IMPLEMENT_DYNAMIC(EarthScan, CDialogEx)

EarthScan::EarthScan(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_PROPPAGE_MEDIUM, pParent)
{

}

EarthScan::~EarthScan()
{
}

void EarthScan::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(EarthScan, CDialogEx)
END_MESSAGE_MAP()


// EarthScan message handlers

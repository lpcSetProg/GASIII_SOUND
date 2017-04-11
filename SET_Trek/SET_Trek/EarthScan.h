#pragma once
#include "GameController.h"
#include "Graphics.h"
#include "SectorMap1.h"
#include "Ship.h"
#include "Planet.h"
#include "Grid.h"

// EarthScan dialog

class EarthScan : public CDialogEx
{
	DECLARE_DYNAMIC(EarthScan)

public:
	EarthScan(CWnd* pParent = NULL);   // standard constructor
	virtual ~EarthScan();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_PROPPAGE_MEDIUM };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
};

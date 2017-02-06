// OrderGridFilter.cpp : implementation file
//

#include "stdafx.h"
#include "TradingSDI.h"
#include "OrderGridFilter.h"
#include "afxdialogex.h"
#include "OrderGrid.h"
#include "OutputWnd.h"

IMPLEMENT_DYNAMIC(OrderGridFilter, CDialogEx)

OrderGridFilter::OrderGridFilter(CWnd* pParent /*=NULL*/)
	: CDialogEx(OrderGridFilter::IDD, pParent)
{

}

OrderGridFilter::~OrderGridFilter()
{
}

void OrderGridFilter::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);	
}


BEGIN_MESSAGE_MAP(OrderGridFilter, CDialogEx)
END_MESSAGE_MAP()




 




BOOLEAN  OrderGridFilter::CheckvalueInArray(CString arr[],CString strval) 
{
	try
	{
	int arrcount=arr->GetLength();
    for (int forcount=0;forcount<arrcount;forcount++)
	{
		if (arr[forcount]==strval)
		{
			return true;
		}
	}
    return false  ;
	}
	catch(_com_error & ce)
			{
				AfxMessageBox(ce.Description()+L"CheckvalueInArray");			
			} 
}

void OrderGridFilter::addItemToCombobox()
{
	try
	{
	int rows=1;
	//rows=COutputWnd::m_wndOutputOrder.GetNumberRows();
	CString strstatus=L"";
	CString strclient=L"";
	CString strorder=L"";
	CString strdate=L"";
	CString strsymbol=L"";
	CString strordertype=L"";
	CString strqty=L"";
	CString strrate=L"";
	CString strcomment=L"";

	CString arr[500]={};
	CString arr1[500]={};
	CString arr2[500]={};
	CString arr3[500]={};
	CString arr4[500]={};
	CString arr5[500]={};
	CString arr6[500]={};
	CString arr7[500]={};
	CString arr8[500]={};
	for (int forcount=0;forcount<rows;forcount++)
	{
			/*strstatus=COutputWnd::m_wndOutputOrder.QuickGetText(0,forcount);
			strstatus=strstatus.Trim();
			strclient=COutputWnd::m_wndOutputOrder.QuickGetText(1,forcount);
			strclient=strclient.Trim();
			strorder=COutputWnd::m_wndOutputOrder.QuickGetText(2,forcount);
			strorder=strorder.Trim();
			strdate=COutputWnd::m_wndOutputOrder.QuickGetText(3,forcount);
			strdate=strdate.Trim();
			strsymbol=COutputWnd::m_wndOutputOrder.QuickGetText(4,forcount);
			strsymbol=strsymbol.Trim();
			strordertype=COutputWnd::m_wndOutputOrder.QuickGetText(5,forcount);
			strordertype=strordertype.Trim();
			strqty=COutputWnd::m_wndOutputOrder.QuickGetText(6,forcount);
			strqty=strqty.Trim();
			strrate=COutputWnd::m_wndOutputOrder.QuickGetText(7,forcount);
			strrate=strrate.Trim();
			strcomment=COutputWnd::m_wndOutputOrder.QuickGetText(8,forcount);*/
			strcomment=strcomment.Trim();
			if (strstatus!=L"")
			{
				if (CheckvalueInArray(arr,strstatus)==false )
				{
					cmb_status->AddString(strstatus);										
					arr[forcount]=strstatus;
				}
			}

			if (strclient!=L"")
			{
				if (CheckvalueInArray(arr1,strclient)==false )
				{					
					cmb_client->AddString(strclient);					
					arr1[forcount]=strclient;
				}
			}
			if (strorder!=L"")
			{
				if (CheckvalueInArray(arr2,strorder)==false )
				{										
					cmb_order->AddString(strorder);					
					arr2[forcount]=strorder;
				}
			}
			if (strdate!=L"")
			{
				if (CheckvalueInArray(arr3,strdate)==false )
				{										
					
					cmb_date->AddString(strdate);					
					arr3[forcount]=strdate;
				}
			}
			if (strsymbol!=L"")
			{
				if (CheckvalueInArray(arr4,strsymbol)==false )
				{																				
					cmb_symbol->AddString(strsymbol);					
					arr4[forcount]=strsymbol;
				}
			}
			if (strordertype!=L"")
			{
				if (CheckvalueInArray(arr5,strordertype)==false )
				{																									
					cmb_ordertype->AddString(strordertype);					
					arr5[forcount]=strordertype;
				}
			}

			if (strqty !=L"")
			{
				if (CheckvalueInArray(arr6,strqty)==false )
				{																														
					cmb_qty->AddString(strqty);			
					arr6[forcount]=strqty;
				}
			}

			if (strrate !=L"")
			{
				if (CheckvalueInArray(arr7,strrate)==false )
				{																																			
					cmb_rate->AddString(strrate);				
					arr7[forcount]=strrate;
				}
			}
			if (strcomment !=L"")
			{
				if (CheckvalueInArray(arr8,strcomment)==false )
				{																																			
					
					cmb_comment->AddString(strcomment);
					arr8[forcount]=strcomment;
				}
			}
			
	}
	}
	catch(_com_error & ce)
			{
				AfxMessageBox(ce.Description()+L"addItemToCombobox");			
			} 
}

BOOL OrderGridFilter::OnInitDialog()
{
	try
	{
	cmb_status=(CComboBox*)GetDlgItem(FL_CMB_STATUS);
	cmb_client=(CComboBox*)GetDlgItem(FL_CMB_LOGIN);
	cmb_order=(CComboBox*)GetDlgItem(FL_CMB_ORDER);
	cmb_date=(CComboBox*)GetDlgItem(FL_CMB_DATE);
	cmb_symbol=(CComboBox*)GetDlgItem(FL_CMB_SYMBOL);
	cmb_ordertype=(CComboBox*)GetDlgItem(FL_CMB_ORDERTYPE);
	cmb_qty=(CComboBox*)GetDlgItem(FL_CMB_QTY);
	cmb_rate=(CComboBox*)GetDlgItem(FL_CMB_RATE);
	cmb_comment=(CComboBox*)GetDlgItem(FL_CMB_COMMENT);
	OrderGridFilter::addItemToCombobox();
	return true;
	}
	catch(_com_error & ce)
			{
				AfxMessageBox(ce.Description()+L"OnInitDialog()");			
				return false;
			} 
}

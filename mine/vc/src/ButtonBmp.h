//ButtonBmp.h
#pragma once

class CButtonBmp : public CButton
{
public:
    CButtonBmp();
public:
// Overrides
    // ClassWizard generated virtual function overrides
    //{{AFX_VIRTUAL(CBMPButton)
    public:
    virtual void DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct);
    //}}AFX_VIRTUAL
// Implementation
public:
    void SetBtnBitmap(int i);
    virtual ~CButtonBmp();
    // Generated message map functions
protected:
    //{{AFX_MSG(CBMPButton)
    //}}AFX_MSG
    DECLARE_MESSAGE_MAP()
private:
    HBITMAP m_hBmp;
    HDC     m_hMem;
    int     m_idxBmp;
};

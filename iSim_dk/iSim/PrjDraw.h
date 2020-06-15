#pragma once
class CPrjDraw
{
public:
  CPrjDraw(void);
  ~CPrjDraw(void);
   
public:
  unsigned int* m_pData;
  
protected:
  CRect m_rectPrev;
  int m_nTypePrev;

public:
  void Init(void);
  int GetMem(int nDataNum);
  void DrawProjHorz(CDC* pDC, CRect rectRoi, int iwid, int ihgt);
  void DrawProjVert(CDC* pDC, CRect rectRoi, int iwid, int ihgt);
  BOOL IsChanged(CRect rectRoi, int nPrjType);
};


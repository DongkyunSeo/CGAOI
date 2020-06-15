
class CTracker{
protected:
	CWnd *m_pWnd;//부모 윈도우 핸들러
	BOOL m_bDown;//마우스 버튼 플러그
	CRect m_rectOld;//이전 영역 좌표 저장 변수
	int m_nHandleNum; //마우스가 추적박스에서 8개방향과 이동 위치의 어느점에 있는가
	int m_nMode; // 모드 0은 기존 영역 핸들을 조절함. 모드 1 은 영역을 새로 선택함.
	CRect m_rectHandle[12]; //8개 방향의 좌표와 4개방향의 이동좌표 저장 변수
	CPoint m_OldPoint; //이전 마우스 포인터 변수
  CRect m_rectTrack; //이동되는 영역 좌표 임시 저장
	int m_nLineDot; //8개 영역 박스 점이 선보다 얼마나 두꺼운가를 저장하는 변수
	int m_nLineThick; 	//추적박스 라인의 두께
	int m_bHandleSet; //m_rectHandle영역이 설정되어 있으면 TRUE그렇지 않으면 FALSE
  BOOL m_bShow;

  void MakeHandle(); // m_rectHandle의 영역을 만들어주는 함수
	void SetMouseCursor();
  void Redraw(void);

public:
	CPoint m_ScrollPos; //View 의 Scroll 위치
	CRect m_rect; 	// 추적박스의 좌표

	CTracker();
	CTracker(CWnd *pWnd,int dot=1 ,int thick=1);
  void SetCWnd(CWnd* pWnd);
	void SetRect(CRect rect);
	void Draw(CDC* pDC);

	int PtInHandle(CPoint point);
  void Reset(void);

	void OnMouseMove(UINT nFlags, CPoint point);
	void OnLButtonDown(UINT nFlags, CPoint point);
	void OnLButtonUp(UINT nFlags, CPoint point);


  CRect GetRect(void);
  void Hide(void);
  void Show(void);
  CRect GetCurRect(void);
};

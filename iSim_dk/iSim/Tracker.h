
class CTracker{
protected:
	CWnd *m_pWnd;//�θ� ������ �ڵ鷯
	BOOL m_bDown;//���콺 ��ư �÷���
	CRect m_rectOld;//���� ���� ��ǥ ���� ����
	int m_nHandleNum; //���콺�� �����ڽ����� 8������� �̵� ��ġ�� ������� �ִ°�
	int m_nMode; // ��� 0�� ���� ���� �ڵ��� ������. ��� 1 �� ������ ���� ������.
	CRect m_rectHandle[12]; //8�� ������ ��ǥ�� 4�������� �̵���ǥ ���� ����
	CPoint m_OldPoint; //���� ���콺 ������ ����
  CRect m_rectTrack; //�̵��Ǵ� ���� ��ǥ �ӽ� ����
	int m_nLineDot; //8�� ���� �ڽ� ���� ������ �󸶳� �β���� �����ϴ� ����
	int m_nLineThick; 	//�����ڽ� ������ �β�
	int m_bHandleSet; //m_rectHandle������ �����Ǿ� ������ TRUE�׷��� ������ FALSE
  BOOL m_bShow;

  void MakeHandle(); // m_rectHandle�� ������ ������ִ� �Լ�
	void SetMouseCursor();
  void Redraw(void);

public:
	CPoint m_ScrollPos; //View �� Scroll ��ġ
	CRect m_rect; 	// �����ڽ��� ��ǥ

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

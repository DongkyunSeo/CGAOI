#pragma once
class CStopWatch
{
public:
  CStopWatch(void);
  ~CStopWatch(void);
  int Start(void);
  int Stop(void);
  int ResultMsgBox(void);
  CString GetStrElapsed();
  double GetElapsed();

protected:
  CString m_strMsg;
  CString m_strTot;

  INT64 m_Freq;
  INT64 m_BeginTime;
  INT64 m_EndTime;
  double m_Elapsed;
  

};


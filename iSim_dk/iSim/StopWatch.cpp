#include "StdAfx.h"
#include "StopWatch.h"


CStopWatch::CStopWatch(void)
{
  QueryPerformanceFrequency((LARGE_INTEGER *) &m_Freq );
}


CStopWatch::~CStopWatch(void)
{

}



int CStopWatch::Start(void)
{
  QueryPerformanceCounter((LARGE_INTEGER *) &m_BeginTime ); 

  return 0;
}


int CStopWatch::Stop(void)
{
  QueryPerformanceCounter((LARGE_INTEGER *) &m_EndTime );
  
  INT64 elapsed = m_EndTime - m_BeginTime; 

  m_Elapsed = (double)elapsed / (double)(m_Freq) * 1000.;

  m_strTot.Format(_T("%.3lf ms"),m_Elapsed);
  m_strMsg.Format(_T("Elapsed time : %.3lf msec "),m_Elapsed);

  return 0;
}



int CStopWatch::ResultMsgBox(void)
{
  AfxMessageBox(m_strMsg);
  return 0;
}


CString CStopWatch::GetStrElapsed()
{
  return m_strTot;
}

double CStopWatch::GetElapsed()
{
  return m_Elapsed;
}

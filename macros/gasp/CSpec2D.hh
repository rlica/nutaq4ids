#ifndef CSpec2D_h
#define CSpec2D_h 1

//#include "G4Types.hh"

using namespace std;

//////////////////////////////////////////////////////////////////////
/// This class handles packed matrices in uncompressed GASP format
//////////////////////////////////////////////////////////////////////
class CSpec2D
{
  public:
    CSpec2D(int nch1 = 256, int nch2 = 256, int nsp = 1);
   ~CSpec2D();

  private:
    int  nSpec;     //> Number of spectra		     
    int  nChan1;    //> Number of channels (axis 1)	     
    int  nChan2;    //> Number of channels (axis 2)	     
    int *pData;     //> Buffer where the spectra are stored  
     
  ///////////////////////////////////////////////////////////////
  /// Methods to operate on the whole memory buffer
  //////////////////////////////////////////////////////////////
  public:
    void         reNew(int nch1 = 256, int nch2 = 256, int nsp = 1);
    void         erase();
    void         list ();
     
  public:
    void  write(const char *);  //> Write out the matrices
     
  //////////////////////////////////////////////////////////////////
  /// Methods to manipulate the channel content
  //////////////////////////////////////////////////////////////////
  public:
    inline void  set  (const int val, const int ch1, const int ch2, const int sp = 0);
    inline void  Set  (const int val,	    int ch1,	   int ch2, const int sp = 0);
    inline int   get  ( 	      const int ch1, const int ch2, const int sp = 0);
    inline void  incr ( 	      const int ch1, const int ch2, const int sp = 0);
    inline void  Incr ( 		    int ch1,	   int ch2, const int sp = 0);

  public:
    inline int   GetNumberOfSpectra ();
    inline int   GetNumberOfChannels1();
    inline int   GetNumberOfChannels2();
};

inline void CSpec2D::set(const int val, const int ch1, const int ch2, const int sp)
{
  if(sp < 0 || sp >= nSpec) return;
  if(ch1 <  0 || ch1 >= nChan1) return;
  if(ch2 <  0 || ch2 >= nChan2) return;
  *(pData + sp*nChan1*nChan2 + ch1*nChan1 + ch2) = val;
}

inline void CSpec2D::Set(const int val, int ch1, int ch2, const int sp)
{
  if(sp < 0 || sp >= nSpec) return;
  if(ch1 <  0) ch1 = 0;
  if(ch1 >= nChan1) ch1 = nChan1-1;
  if(ch2 <  0) ch2 = 0;
  if(ch2 >= nChan2) ch2 = nChan2-1;
  *(pData + sp*nChan1*nChan2 + ch1*nChan1 + ch2) = val;
}

inline int CSpec2D::get(int ch1, int ch2, const int sp)
{
  if(sp < 0 || sp >= nSpec) return 0;
  if(ch1 <  0 || ch1 >= nChan1) return 0;
  if(ch2 <  0 || ch2 >= nChan2) return 0;
  return   *(pData + sp*nChan1*nChan2 + ch1*nChan1 + ch2);
}

inline void CSpec2D::incr(const int ch1, const int ch2, const int sp)
{
  if(sp < 0 || sp >= nSpec) return;
  if(ch1 <  0 || ch1 >= nChan1) return;
  if(ch2 <  0 || ch2 >= nChan2) return;
  pData[sp*nChan1*nChan2 + ch1*nChan1 + ch2]++;
}

inline void CSpec2D::Incr(int ch1, int ch2, const int sp)
{
  if(sp < 0 || sp >= nSpec) return;
  if(ch1 <  0) ch1 = 0;
  if(ch1 >= nChan1) ch1 = nChan1-1;
  if(ch2 <  0) ch2 = 0;
  if(ch2 >= nChan2) ch2 = nChan2-1;
  pData[sp*nChan1*nChan2 + ch1*nChan1 + ch2]++;
}

inline int CSpec2D::GetNumberOfSpectra()
{
  return nSpec;
}

inline int CSpec2D::GetNumberOfChannels1()
{
  return nChan1;
}

inline int CSpec2D::GetNumberOfChannels2()
{
  return nChan2;
}

#endif

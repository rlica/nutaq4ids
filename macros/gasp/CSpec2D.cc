#include "CSpec2D.hh"

#include <iostream>
#include <fstream>
#include <iomanip>
#include <cstring>


CSpec2D::CSpec2D(int nch1, int nch2, int nsp)
{
  if(nch1 < 1) nch1 = 1;
  if(nch2 < 1) nch2 = 1;
  if(nsp < 1) nsp = 1;
  nChan1 = nch1;
  nChan2 = nch2;
  nSpec  = nsp;
  pData = new int[nChan1*nChan2*nSpec];
  erase();
}

CSpec2D::~CSpec2D()
{
  if(pData) delete [] pData;
}

void CSpec2D::reNew(int nch1, int nch2, int nsp)
{
  if(pData)  delete [] pData;
  CSpec2D(nch1, nch2, nsp);
}

void CSpec2D::erase()
{
  int nn = nChan1*nChan2*nSpec;
  for(int ii = 0; ii < nn; pData[ii++] = 0){;}
}

void CSpec2D::list()
{
  cout << "CSpec2D::list() not implemented" << endl;
}

void CSpec2D::write(const char * specname)
{
  fstream fout;
  fout.open(specname, ios::out | ios::binary);
  if(!fout.is_open()) return;

  int nn = nChan1*nChan2*nSpec;
  fout.write((const char *)pData, sizeof(int)*nn);
  fout.close();
  cout << "Spectrum " << specname << "(" << nChan1 << "*" << nChan2 << "*" << nSpec << ")" << endl;
}

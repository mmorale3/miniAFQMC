////////////////////////////////////////////////////////////////////////////////
// This file is distributed under the University of Illinois/NCSA Open Source
// License.  See LICENSE file in top directory for details.
//
// Copyright (c) 2016 Jeongnim Kim and QMCPACK developers.
//
// File developed by:
// Ken Esler, kpesler@gmail.com,
//    University of Illinois at Urbana-Champaign
// Jeongnim Kim, jeongnim.kim@gmail.com,
//    University of Illinois at Urbana-Champaign
// Jeremy McMinnis, jmcminis@gmail.com,
//    University of Illinois at Urbana-Champaign
//
// File created by:
// Jeongnim Kim, jeongnim.kim@gmail.com,
//    University of Illinois at Urbana-Champaign
////////////////////////////////////////////////////////////////////////////////

#ifndef QMCPLUSPLUS_TRAITS_H
#define QMCPLUSPLUS_TRAITS_H

#include <config.h>
#include <string>
#include <vector>
#include <map>
#include <complex>
#include <Utilities/OhmmsInfo.h>
#include <Message/Communicate.h>

#include <Kokkos_Core.hpp>

#define byRows   999
#define byCols   111

// careful here that RealType is consistent with this!!!
#define MKL_INT         int
#define MKL_Complex8    std::complex<float> 
#define MKL_Complex16   std::complex<double> 

// define empty DEBUG_MEMORY
#define DEBUG_MEMORY(msg)
// uncomment this out to trace the call tree of destructors
//#define DEBUG_MEMORY(msg) std::cerr << "<<<< " << msg << std::endl;

#if defined(DEBUG_PSIBUFFER_ON)
#define DEBUG_PSIBUFFER(who, msg)                              \
  std::cerr << "PSIBUFFER " << who << " " << msg << std::endl; \
  std::cerr.flush();
#else
#define DEBUG_PSIBUFFER(who, msg)
#endif

#include<boost/multi_array.hpp>

#include "Matrix/SparseMatrix.hpp"
#include "Matrix/SparseMatrix_ref.hpp"

#include <KokkosSparse.hpp>

namespace qmcplusplus
{

  //using boost::multi_array_types::index_gen;
  using boost::extents;
  using boost::indices;
  typedef boost::multi_array_types::index_range range_t;

  typedef OHMMS_INDEXTYPE                 IndexType;
  typedef OHMMS_INDEXTYPE                 OrbitalType;
  typedef OHMMS_PRECISION_FULL            RealType;
  typedef OHMMS_PRECISION                 SPRealType;

#if defined(QMC_COMPLEX)
  typedef std::complex<RealType>  ValueType;
  typedef std::complex<SPRealType>       SPValueType;
#else
  typedef RealType                       ValueType;
  typedef SPRealType                     SPValueType;
#endif
  typedef std::complex<RealType>         ComplexType;
  typedef std::complex<SPRealType>       SPComplexType;


/*
  typedef SMDenseVector<IndexType>     IndexSMVector;
  typedef SMDenseVector<RealType>      RealSMVector;
  typedef SMDenseVector<ValueType>     ValueSMVector;
  typedef SMDenseVector<SPValueType>   SPValueSMVector;
  typedef SMDenseVector<ComplexType>   ComplexSMVector;
  typedef SMDenseVector<SPComplexType>   SPComplexSMVector;
*/

  size_t inline idx4c(size_t i, size_t j, size_t k, size_t l, size_t ni, size_t nj, size_t nk, size_t nl)
                     {return ((i*nj + j)*nk + k)*nl + l;}
  size_t inline idx3c(size_t i, size_t j, size_t k, size_t ni, size_t nj, size_t nk)
                     {return (i*nj + j)*nk + k;}
  size_t inline idx2c(size_t i, size_t j, size_t ni, size_t nj) {return i*nj + j;}

  size_t inline idx4f(size_t i, size_t j, size_t k, size_t l, size_t ni, size_t nj, size_t nk, size_t nl)
                     {return i + (j + (k + l*nk)*nj)*ni;}
  size_t inline idx3f(size_t i, size_t j, size_t k, size_t ni, size_t nj, size_t nk)
                     {return i + (j + k*nj)*ni;}
  size_t inline idx2f( size_t i, size_t j, size_t ni, size_t nj) {return i + j*ni;}

  size_t inline idx2(size_t i, size_t j, size_t ni, size_t nj) {return idx2f(i, j, ni, nj);}
  size_t inline idx3(size_t i, size_t j, size_t k, size_t ni, size_t nj, size_t nk)
                    {return idx3f(i, j, k, ni, nj, nk);}
  size_t inline idx4(size_t i, size_t j, size_t k, size_t l, size_t ni, size_t nj, size_t nk, size_t nl)
                    {return idx4f(i, j, k, l, ni, nj, nk, nl);}

  // [nwalk][2][NMO][NAEA]
  typedef boost::multi_array<ValueType,4> WalkerContainer;
  typedef Kokkos::View<ValueType****, Kokkos::LayoutLeft> WalkerContainerKokkos;
  typedef Kokkos::View<ComplexType****, Kokkos::LayoutLeft> ComplexArray4D;

  typedef boost::multi_array<IndexType,1> IndexVector;
  typedef boost::multi_array<RealType,1> RealVector;
  typedef boost::multi_array<SPRealType,1> SPRealVector;
  typedef boost::multi_array<ValueType,1> ValueVector;
  typedef boost::multi_array<SPValueType,1> SPValueVector;
  typedef boost::multi_array<ComplexType,1> ComplexVector;
  typedef Kokkos::View<ComplexType*> ComplexVectorKokkos;
  typedef boost::multi_array<SPComplexType,1> SPComplexVector;

  typedef boost::multi_array<IndexType,2> IndexMatrix;  
  typedef boost::multi_array<RealType,2> RealMatrix;  
  typedef boost::multi_array<SPRealType,2> SPRealMatrix;  
  typedef boost::multi_array<ValueType,2> ValueMatrix;  
  typedef boost::multi_array<SPValueType,2> SPValueMatrix;  
  typedef boost::multi_array<ComplexType,2> ComplexMatrix;  
  typedef Kokkos::View<ComplexType**, Kokkos::LayoutLeft> ComplexMatrixKokkos;  
  typedef boost::multi_array<SPComplexType,2> SPComplexMatrix;  
  typedef Kokkos::View<SPComplexType**, Kokkos::LayoutLeft> SPComplexMatrixKokkos;  

  typedef SparseMatrix<IndexType>     IndexSpMat;
  typedef SparseMatrix<RealType>      RealSpMat;
  typedef SparseMatrix<ValueType>     ValueSpMat;
  typedef SparseMatrix<SPValueType>   SPValueSpMat;
  typedef SparseMatrix<ComplexType>   ComplexSpMat;

  typedef KokkosSparse::CrsMatrix<ComplexType, size_t, Kokkos::Threads> ComplexSpMatKokkos;

/*
  typedef SMSparseMatrix<IndexType>     IndexSMSpMat;
  typedef SMSparseMatrix<RealType>      RealSMSpMat;
  typedef SMSparseMatrix<ValueType>     ValueSMSpMat;
  typedef SMSparseMatrix<SPValueType>   SPValueSMSpMat;
  typedef SMSparseMatrix<ComplexType>   ComplexSMSpMat;
  typedef SMSparseMatrix<SPComplexType>   SPComplexSMSpMat;
*/

inline std::ostream &app_log() { return OhmmsInfo::Log->getStream(); }

inline std::ostream &app_error()
{
  OhmmsInfo::Log->getStream() << "ERROR ";
  return OhmmsInfo::Error->getStream();
}

inline std::ostream &app_warning()
{
  OhmmsInfo::Log->getStream() << "WARNING ";
  return OhmmsInfo::Warn->getStream();
}

inline std::ostream &app_debug() { return OhmmsInfo::Debug->getStream(); }
}

namespace std{

inline  void swap(std::tuple<int &, int &, qmcplusplus::RealType &> const& a, std::tuple<int &, int &, qmcplusplus::RealType &> const& b) {
    using std::swap;
    swap(std::get<0>(a), std::get<0>(b));
    swap(std::get<1>(a), std::get<1>(b));
    swap(std::get<2>(a), std::get<2>(b));
  }

inline  void swap(std::tuple<int &, int &, std::complex<qmcplusplus::RealType> &> const & a, std::tuple<int &, int &, std::complex<qmcplusplus::RealType> &> const& b) {
    using std::swap;
    swap(std::get<0>(a), std::get<0>(b));
    swap(std::get<1>(a), std::get<1>(b));
    swap(std::get<2>(a), std::get<2>(b));
  }

}

#endif

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <algorithm>
#include "ReadBinaryDosage.h"
#include <Rcpp.h>

enum class Header4pos {
  header = 0,
    version = 4,
    numSub = 8,
    numSNPs = 12,
    numGroups = 16,
    subOptions = 20,
    snpOptions = 24,
    startSub = 28,
    startSNP = 32,
    startDosage = 36,
    startGroups = 40
};
///////////////////////////////////////////////////////////////////////////////
//
//                            CReadBinaryDosage
//
///////////////////////////////////////////////////////////////////////////////

CReadBinaryDosageX::CReadBinaryDosageX(const std::string &filename) {
  m_filename = filename;
  memset(m_version, 0, sizeof(m_version));
  m_mainVersion = 0;
  m_subVersion = 0;
  m_numSubjects = 0;
  m_numSNPs = 0;
  m_numGroups = 0;
  m_startSubjects = 0;
  m_startSNPs = 0;
  m_startDosages = 0;
  m_subjectOptions = 0;
  m_snpOptions = 0;
  m_usesFamilyID = false;
}

CReadBinaryDosageX::~CReadBinaryDosageX() {
  m_infile.close();
}

int CReadBinaryDosageX::ReadVersion(const char *version) {
  m_infile.read((char *)m_version, 4);
  if (!m_infile.good())
    return 1;
  if (std::memcmp(m_version, version, 4))
    return 1;
  return 0;
}

int CReadBinaryDosageX::ReadHeader() {
  const char bdHeader[4] = { 'b', 'o', 's', 'e' };
  char header[4];
  if (!m_infile.is_open())
    return 1;

  m_infile.read(header, 4);
  if (!m_infile.good())
    return 1;
  if (std::memcmp(bdHeader, header, 4))
    return 1;
  return 0;
}

int CReadBinaryDosageX::ReadGroups() {
  m_numGroups = 1;
  m_groupSize.resize(1);
  m_groupSize[0] = m_numSubjects;
  return 0;
}

void CReadBinaryDosageX::WriteData(std::ostream &outfile) {
  outfile << "---------------------------------------------------------" << std::endl;
  outfile << "Filename\t\t:\t" << m_filename << std::endl;
  outfile << "Version\t\t\t:\t" << m_mainVersion << '.' << m_subVersion << std::endl;
  outfile << "Number of subjects\t:\t" << m_numSubjects << std::endl;
  outfile << "Subject options\t\t:\t" << std::hex << m_subjectOptions << std::dec << std::endl;
  outfile << "Start subjects\t\t:\t" << m_startSubjects << std::endl;
  outfile << "First subject\t\t:\t";
  if (m_FID.size() > 0)
    outfile << m_FID[0] << '\t';
  if (m_IID.size() > 0)
    outfile << m_IID[0];
  outfile << std::endl;
  outfile << "Last subject\t\t:\t";
  if (m_FID.size() > 0)
    outfile << m_FID[m_FID.size() - 1] << '\t';
  if (m_IID.size() > 0)
    outfile << m_IID[m_IID.size() - 1];
  outfile << std::endl;
  outfile << "Number of groups\t:\t" << m_numGroups << std::endl;
  outfile << "Group sizes\t\t:";
  for (int i = 0; i < m_numGroups; ++i)
    outfile << '\t' << m_groupSize[i];
  outfile << std::endl;
  outfile << "---------------------------------------------------------" << std::endl;
}
///////////////////////////////////////////////////////////////////////////////
//
//                            CReadMultifileBinaryDosage
//
///////////////////////////////////////////////////////////////////////////////

CReadMultifileBinaryDosage::CReadMultifileBinaryDosage(const std::string &filename) : CReadBinaryDosageX(filename) {
  std::string inputFilename;

  inputFilename = m_filename + std::string(".fam");
  m_famFile.open(inputFilename.c_str());
  inputFilename = m_filename + std::string(".map");
  m_mapFile.open(inputFilename.c_str());
  inputFilename = m_filename + std::string(".bdose");
  m_infile.open(inputFilename.c_str(), std::ios_base::in | std::ios_base::binary);
}

CReadMultifileBinaryDosage::~CReadMultifileBinaryDosage() {
  m_famFile.close();
  m_mapFile.close();
}

int CReadMultifileBinaryDosage::ReadSubjects() {
  std::string junk, fam, sub;
  std::istringstream iss;
  bool familyID;
  int numCol;


  if (!m_famFile.is_open())
    return 1;

  std::getline(m_famFile, junk);
  if (m_famFile.fail())
    return 1;
  numCol = 0;
  iss.str(junk);
  iss >> fam;
  while (!iss.fail()) {
    ++numCol;
    iss >> fam;
  }
  switch(numCol) {
  case 1:
  case 5:
    familyID = false;
    break;
  case 2:
  case 6:
    familyID = true;
    break;
  default:
    return 1;
  }
  do {
    iss.clear();
    iss.str(junk);
    if (familyID) {
      iss >> fam;
      m_FID.push_back(fam);
    }
    iss >> sub;
    m_IID.push_back(sub);
    getline(m_famFile, junk);
  } while (!m_famFile.fail());
  m_numSubjects = m_IID.size();
  return 0;
}

int CReadMultifileBinaryDosage::ReadSNP() {
  std::string junk, chromosome, snpID, refAllele, altAllele;
  int bp;
  std::istringstream iss;


  if (!m_mapFile.is_open())
    return 1;

  std::getline(m_mapFile, junk);
  if (m_famFile.fail())
    return 1;
  iss.str(junk);
  iss >> chromosome >> snpID >> bp >> bp >> refAllele >> altAllele;
  if (iss.fail())
    return 1;
  do {
    iss.clear();
    iss.str(junk);
    iss >> chromosome >> snpID >> bp >> bp >> refAllele >> altAllele;
    m_chromosome.push_back(chromosome);
    m_SNPID.push_back(snpID);
    m_bp.push_back(bp);
    m_refAllele.push_back(refAllele);
    m_altAllele.push_back(altAllele);
    getline(m_famFile, junk);
  } while (!m_famFile.fail());
  m_numSNPs = m_SNPID.size();
  return 0;
}

///////////////////////////////////////////////////////////////////////////////
//
//                            CReadBinaryDosage11
//
///////////////////////////////////////////////////////////////////////////////

CReadBinaryDosage11::CReadBinaryDosage11(const std::string &filename) : CReadMultifileBinaryDosage(filename) {
  m_mainVersion = 1;
  m_subVersion = 1;
}

int CReadBinaryDosage11::ReadHeader() {
  const char version[4] = { 0x00, 0x01, 0x00, 0x01};

  if (CReadBinaryDosageX::ReadHeader())
    return 1;
  return ReadVersion(version);
}

///////////////////////////////////////////////////////////////////////////////
//
//                            CReadBinaryDosage12
//
///////////////////////////////////////////////////////////////////////////////

CReadBinaryDosage12::CReadBinaryDosage12(const std::string &filename) : CReadMultifileBinaryDosage(filename) {
  m_mainVersion = 1;
  m_subVersion = 2;
}

int CReadBinaryDosage12::ReadHeader() {
  const char version[4] = { 0x00, 0x01, 0x00, 0x02};

  if (CReadBinaryDosageX::ReadHeader())
    return 1;
  return ReadVersion(version);
}

///////////////////////////////////////////////////////////////////////////////
//
//                            CReadBinaryDosage21
//
///////////////////////////////////////////////////////////////////////////////

CReadBinaryDosage21::CReadBinaryDosage21(const std::string &filename) : CReadMultifileBinaryDosage(filename) {
  m_mainVersion = 2;
  m_subVersion = 1;
}

int CReadBinaryDosage21::ReadHeader() {
  const char version[4] = { 0x00, 0x02, 0x00, 0x01};

  if (CReadBinaryDosageX::ReadHeader())
    return 1;
  return ReadVersion(version);
}

///////////////////////////////////////////////////////////////////////////////
//
//                            CReadBinaryDosage22
//
///////////////////////////////////////////////////////////////////////////////

CReadBinaryDosage22::CReadBinaryDosage22(const std::string &filename) : CReadMultifileBinaryDosage(filename) {
  m_mainVersion = 2;
  m_subVersion = 2;
}

int CReadBinaryDosage22::ReadHeader() {
  const char version[4] = { 0x00, 0x02, 0x00, 0x02};

  if (CReadBinaryDosageX::ReadHeader())
    return 1;
  return ReadVersion(version);
}

///////////////////////////////////////////////////////////////////////////////
//
//                            CReadBinaryDosage31
//
///////////////////////////////////////////////////////////////////////////////

CReadBinaryDosage31::CReadBinaryDosage31(const std::string &filename) : CReadMultifileBinaryDosage(filename) {
  m_mainVersion = 3;
  m_subVersion = 1;
}

int CReadBinaryDosage31::ReadHeader() {
  const char version[4] = { 0x00, 0x03, 0x00, 0x01};

  if (CReadBinaryDosageX::ReadHeader())
    return 1;
  return ReadVersion(version);
}

int CReadBinaryDosage31::ReadSubjects() {
  m_infile.read((char *)&m_numSubjects, sizeof(int));
  if (!m_infile.good())
    return 1;
  m_IID.reserve(m_numSubjects);
  m_FID.reserve(m_numSubjects);
  return CReadMultifileBinaryDosage::ReadSubjects();
}

///////////////////////////////////////////////////////////////////////////////
//
//                            CReadBinaryDosage32
//
///////////////////////////////////////////////////////////////////////////////

CReadBinaryDosage32::CReadBinaryDosage32(const std::string &filename) : CReadMultifileBinaryDosage(filename) {
  m_mainVersion = 3;
  m_subVersion = 2;
}

int CReadBinaryDosage32::ReadHeader() {
  const char version[4] = { 0x00, 0x03, 0x00, 0x02};

  if (CReadBinaryDosageX::ReadHeader())
    return 1;
  return ReadVersion(version);
}

int CReadBinaryDosage32::ReadSubjects() {
  m_infile.read((char *)&m_numSubjects, sizeof(int));
  if (!m_infile.good())
    return 1;
  m_IID.reserve(m_numSubjects);
  m_FID.reserve(m_numSubjects);
  return CReadMultifileBinaryDosage::ReadSubjects();
}

///////////////////////////////////////////////////////////////////////////////
//
//                            CReadBinaryDosage4x
//
///////////////////////////////////////////////////////////////////////////////

CReadBinaryDosage4x::CReadBinaryDosage4x(const std::string &filename) : CReadBinaryDosageX(filename) {
  std::string infilename;

  infilename = m_filename + std::string(".bdose");
  m_infile.open(infilename.c_str(), std::ios_base::in | std::ios_base::binary);
}

int CReadBinaryDosage4x::ReadString(std::vector<std::string> &stringToRead, const int sizeToRead) {
  std::vector<std::string>::iterator stringIt;
  std::string x;
  char *charString = NULL;
  std::istringstream iss;

  charString = new char[sizeToRead];
  m_infile.read(charString, sizeToRead);
  x = charString;
  iss.str(x);
  for (stringIt = stringToRead.begin(); stringIt != stringToRead.end(); ++stringIt) {
    iss >> x;
    *stringIt = x;
  }
  if (iss.fail())
    return 1;

  if (charString)
    delete [] charString;
  return 0;
}

int CReadBinaryDosage4x::ReadHeader() {
  m_infile.seekg((int)Header4pos::numSub);
  m_infile.read((char *)&m_numSubjects, sizeof(int));
  m_infile.read((char *)&m_numSNPs, sizeof(int));
  m_infile.read((char *)&m_numGroups, sizeof(int));
  m_infile.read((char *)&m_subjectOptions, sizeof(int));
  m_infile.read((char *)&m_snpOptions, sizeof(int));
  m_infile.read((char *)&m_startSubjects, sizeof(int));
  m_infile.read((char *)&m_startSNPs, sizeof(int));
  m_infile.read((char *)&m_startDosages, sizeof(int));
  if (m_infile.fail())
    return 1;
  return 0;
}

int CReadBinaryDosage4x::ReadGroups() {
  m_groupSize.resize(m_numGroups);
  m_infile.seekg((int)Header4pos::startGroups);
  m_infile.read((char *)m_groupSize.data(), m_numGroups * sizeof(int));
  if (!m_infile.good())
    return 1;

  return 0;
}

int CReadBinaryDosage4x::ReadSubjects() {
  int iidSize, fidSize;

  m_infile.seekg(m_startSubjects);
  m_infile.read((char *)&iidSize, sizeof(int));
  m_infile.read((char *)&fidSize, sizeof(int));

  m_IID.resize(m_numSubjects);
  if (ReadString(m_IID, iidSize))
    return 1;

  if (fidSize > 0) {
    m_FID.resize(m_numSubjects);
    if (ReadString(m_FID, fidSize))
      return 1;
  } else {
    m_FID.resize(0);
  }

  return 0;
}

int CReadBinaryDosage4x::ReadSNP() {
  return 0;
}

///////////////////////////////////////////////////////////////////////////////
//
//                            CReadBinaryDosage41
//
///////////////////////////////////////////////////////////////////////////////

CReadBinaryDosage41::CReadBinaryDosage41(const std::string &filename) : CReadBinaryDosage4x(filename) {
  m_mainVersion = 4;
  m_subVersion = 1;
}

int CReadBinaryDosage41::ReadHeader() {
  const char version[4] = { 0x00, 0x04, 0x00, 0x01};

  if (CReadBinaryDosageX::ReadHeader())
    return 1;
  if (ReadVersion(version))
    return 1;
  return CReadBinaryDosage4x::ReadHeader();
}

///////////////////////////////////////////////////////////////////////////////
//
//                            CReadBinaryDosage42
//
///////////////////////////////////////////////////////////////////////////////

CReadBinaryDosage42::CReadBinaryDosage42(const std::string &filename) : CReadBinaryDosage4x(filename) {
  m_mainVersion = 4;
  m_subVersion = 2;
}

int CReadBinaryDosage42::ReadHeader() {
  const char version[4] = { 0x00, 0x04, 0x00, 0x02};

  if (CReadBinaryDosageX::ReadHeader())
    return 1;
  if (ReadVersion(version))
    return 1;
  return CReadBinaryDosage4x::ReadHeader();
}

///////////////////////////////////////////////////////////////////////////////
//                            Test code
///////////////////////////////////////////////////////////////////////////////

int TestReadBD(CReadBinaryDosageX *bdf) {
  bdf->ReadHeader();
  bdf->ReadSubjects();
  bdf->ReadSNP();
  bdf->ReadGroups();
  bdf->WriteData(Rcpp::Rcout);
  return 0;
}
//' Function to test writing of binary dosage files
//'
//' Function to test writing of binary dosage files
//' @return
//' 0 success
//' 1 failure
//' @export
// [[Rcpp::export]]
int TestReadBinaryDosage() {
  CReadBinaryDosage11 f11("Test/Test.Format11");
  CReadBinaryDosage12 f12("Test/Test.Format12");
  CReadBinaryDosage21 f21("Test/Test.Format21");
  CReadBinaryDosage22 f22("Test/Test.Format22");
  CReadBinaryDosage31 f31("Test/Test.Format31");
  CReadBinaryDosage32 f32("Test/Test.Format32");
  CReadBinaryDosage41 f41("Test/Test.Format41");
  CReadBinaryDosage42 f42("Test/Test.Format42");

  TestReadBD(&f11);
  TestReadBD(&f12);
  TestReadBD(&f21);
  TestReadBD(&f22);
  TestReadBD(&f31);
  TestReadBD(&f32);
  TestReadBD(&f41);
  TestReadBD(&f42);

  return 0;
}

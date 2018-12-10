#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <cstring>
#include <vector>
#include <limits>
#include <algorithm>
#include "MiniReader.h"

const int ReadBufferSize = 100000000;

CMiniReader::CMiniReader(const std::string &_filename) {
  m_good = true;
  m_filename = _filename;
  m_numSamples = 0;
  m_numSNPs = 0;

  m_chunked = false;
  m_currentChunk = -1;

  m_currentPos = 0;
  m_startDosageData = 0;
  m_geneticDataReader = NULL;
  m_currentSNP = 0;
}

CMiniReader::~CMiniReader() {
  if (m_geneticDataReader)
    delete m_geneticDataReader;
  m_infile.close();
}

bool CMiniReader::GetChunkSNP() {
//  std::cout << m_currentSNP << '\t' << m_snpChunk[m_currentSNP] << '\t' << m_currentChunk << std::endl;
  if (m_snpChunk[m_currentSNP] != m_currentChunk) {
    ReadChunk(m_snpChunk[m_currentSNP]);
  }

  m_iss.clear();
  m_iss.seekg(m_stringPos[m_currentSNP]);
  if (m_geneticDataReader->ReadData(m_iss, m_dosage, m_p0, m_p1, m_p2))
    m_good = false;

  return m_good;
}

bool CMiniReader::GetFirst() {
  if (!m_good)
    return false;
  m_currentSNP = 0;
  if (m_chunked)
    return GetChunkSNP();
  m_infile.seekg(m_startDosageData);
  if (m_geneticDataReader->ReadData(m_infile, m_dosage, m_p0, m_p1, m_p2))
    m_good = false;
  return m_good;
}

bool CMiniReader::GetNext() {
  if (!m_good)
    return false;
  ++m_currentSNP;
  if (m_currentSNP == NumSNPs()) {
    --m_currentSNP;
    return false;
  }
  if (m_chunked)
    return GetChunkSNP();
  if (m_geneticDataReader->ReadData(m_infile, m_dosage, m_p0, m_p1, m_p2))
    m_good = false;
  return m_good;
}

bool CMiniReader::GetSNP(int n) {
  if (!m_good)
    return false;
  if (n == 0 || n > NumSNPs())
    return false;
  --n;
  if (n == m_currentSNP)
    return true;
  if (m_chunked) {
    m_currentSNP = n - 1;
    return GetChunkSNP();
  }
  if (n == 0)
    return GetFirst();
  if (n < m_currentSNP) {
    m_infile.seekg(m_startDosageData);
    m_geneticDataReader->SkipSNP(m_infile);
    m_currentSNP = 0;
  }
  while (m_currentSNP < n - 1) {
    m_geneticDataReader->SkipSNP(m_infile);
    ++m_currentSNP;
  }
  return GetNext();
}

bool CMiniReader::GetSNP(int n, std::streampos snpLoc) {
  m_infile.seekg(snpLoc);
  m_currentSNP = n - 1;
  if (m_chunked)
    return GetChunkSNP();
  if (m_geneticDataReader->ReadData(m_infile, m_dosage, m_p0, m_p1, m_p2))
    m_good = false;
  return m_good;
}

int CMiniReader::CloseFile() {
  if (!m_good)
    return 1;

  if (m_infile.is_open()) {
    m_currentPos = m_infile.tellg();
    m_infile.close();
  }

  return 0;
}

int CMiniReader::ReadChunk(int n) {
  std::streampos startPos, endPos;
  int readLength;
  char *x;

  x = &m_readBuffer[0];

  m_currentChunk = -1;
  if ((unsigned int)n + 2 > m_startSNP.size() || n < 0)
    return 1;

  startPos = m_filePos[n];
  endPos = m_filePos[n + 1];
//  std::cout << n << '\t' << m_filePos.size() << std::endl;
//  for (std::vector<std::streampos>::iterator it = m_filePos.begin(); it != m_filePos.end(); ++it)
//    std::cout << *it << '\t';
//  std::cout << std::endl;
  readLength = (int)endPos - startPos;

//  std::cout << startPos <<'\t' << endPos << '\t' << readLength << std::endl;
  m_infile.open(m_filename.c_str(), std::ios_base::in | std::ios_base::binary);
  m_infile.seekg(startPos);
  if (!m_infile.good()) {
    std::cerr << "Error seeking chunk" << std::endl;
    m_infile.close();
    m_good = false;
    return 1;
  }
  m_infile.read(x, readLength);
  if (!m_infile.good()) {
    std::cerr << "Error reading chunk" << std::endl;
    m_infile.close();
    m_good = false;
    return 1;
  }
  m_infile.close();
  m_readBuffer[readLength] = 0;
  m_currentChunk = n;
  m_iss.str(m_readBuffer);
/*
  std::string junk;
  for (int i = 0; i < 12; ++i) {
    m_iss >> junk;
    std::cout << '\t' << junk;
  }
  std::cout << '\n';
*/
  return 0;
}

void CMiniReader::ChunkIt(const std::vector<std::streampos> &indices) {
  std::vector<std::streampos>::const_iterator index;
  std::vector<std::streampos>::iterator itStrPos;
  std::vector<int>::iterator itChunk;
  std::streampos currentPos, lastPos;
  int i, j;

  std::cout << "Entering ChunkIt" << std::endl;
  if (indices.size() != (unsigned int)m_numSNPs) {
    std::cerr << "Number of indices does not equal number of SNPs" << std::endl;
    return;
  }

  m_infile.seekg(0, std::ios_base::end);
  lastPos = m_infile.tellg();
  std::cout << lastPos << std::endl;
  CloseFile();
  std::cout << "Closed file:\t" << lastPos << std::endl;

  m_readBuffer.resize(ReadBufferSize + 1);
  m_startSNP.resize(0);
  m_filePos.resize(0);
  std::cout << m_numSNPs << std::endl;
  m_snpChunk.resize(m_numSNPs);
  m_stringPos.resize(m_numSNPs);
//  m_readString.resize(ReadBufferSize);
  std::cout << "After sizing" << std::endl;

  index = indices.begin();
  std::cout << "After index" << std::endl;
  i = 0;
  j = 0;
  std::cout << "Before pushback" << std::endl;
  std::cout << m_startSNP.size() << std::endl;
  std::cout << i << std::endl;
  m_startSNP.push_back(i);
  std::cout << "Before currentPos" << std::endl;
  currentPos = *index;
  std::cout << currentPos << std::endl;
  m_filePos.push_back(currentPos);
  itChunk = m_snpChunk.begin();
  m_stringPos.push_back(*index - currentPos);
  itStrPos = m_stringPos.begin();
  std::cout << *index << '\t' << currentPos << '\t' << ReadBufferSize << std::endl;
  do {
    if (*index - currentPos > ReadBufferSize) {
      m_startSNP.push_back(i - 1);
      m_filePos.push_back(*(index - 1));
      currentPos = *(index - 1);
      *(itStrPos - 1) = 0;
      ++j;
      *(itChunk - 1) = j;
    }
    *itStrPos = *index - currentPos;
    *itChunk = j;

    ++itStrPos;
    ++itChunk;
    ++index;
    ++i;
  } while (index != indices.end());
  std::cout << "Last pos\t" << lastPos << std::endl;
  if (lastPos - currentPos > ReadBufferSize) {
    m_startSNP.push_back(i - 1);
    m_filePos.push_back(*(index - 1));
    currentPos = lastPos;
    *(itStrPos - 1) = 0;
    ++j;
    *(itChunk - 1) = j;
  }
  m_startSNP.push_back(i);
  m_filePos.push_back(lastPos);
  m_chunked = true;

  m_currentChunk = 0;
  std::cout << "Before ReadChunk:\t" << m_currentChunk << std::endl;
  ReadChunk(m_currentChunk);
/*
  for (i = 0; i < 5; ++i) {
    std::cout << m_startSNP[i] << '\t' << m_filePos[i] << '\t' << m_stringPos[m_startSNP[i]]
              << '\t' << m_startSNP[i] << '\t' << m_stringPos[m_startSNP[i + 1] - 1] << std::endl;
  }

  for (i = 75; i < 85; ++i) {
    std::cout << m_filePos[m_snpChunk[i]] << '\t' << m_stringPos[i] << '\t' << m_snpChunk[i] << std::endl;
  }
*/
}

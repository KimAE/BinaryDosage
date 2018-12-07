// Generated by using Rcpp::compileAttributes() -> do not edit by hand
// Generator token: 10BE3573-1514-4C36-9D1C-5A225CD40393

#include <Rcpp.h>

using namespace Rcpp;

// BDConvertC
Rcpp::List BDConvertC(const Rcpp::List& bdInfo, const std::string& newFile, const std::string& famFile, const std::string& mapFile, int newFormat, int newVersion);
RcppExport SEXP _BinaryDosage_BDConvertC(SEXP bdInfoSEXP, SEXP newFileSEXP, SEXP famFileSEXP, SEXP mapFileSEXP, SEXP newFormatSEXP, SEXP newVersionSEXP) {
BEGIN_RCPP
    Rcpp::RObject rcpp_result_gen;
    Rcpp::RNGScope rcpp_rngScope_gen;
    Rcpp::traits::input_parameter< const Rcpp::List& >::type bdInfo(bdInfoSEXP);
    Rcpp::traits::input_parameter< const std::string& >::type newFile(newFileSEXP);
    Rcpp::traits::input_parameter< const std::string& >::type famFile(famFileSEXP);
    Rcpp::traits::input_parameter< const std::string& >::type mapFile(mapFileSEXP);
    Rcpp::traits::input_parameter< int >::type newFormat(newFormatSEXP);
    Rcpp::traits::input_parameter< int >::type newVersion(newVersionSEXP);
    rcpp_result_gen = Rcpp::wrap(BDConvertC(bdInfo, newFile, famFile, mapFile, newFormat, newVersion));
    return rcpp_result_gen;
END_RCPP
}
// BDConvertVCFC
int BDConvertVCFC(const Rcpp::List& vcfInfo, const std::string& newFile, const std::string& famFile, const std::string& mapFile, int newFormat, int newVersion, int batchSize);
RcppExport SEXP _BinaryDosage_BDConvertVCFC(SEXP vcfInfoSEXP, SEXP newFileSEXP, SEXP famFileSEXP, SEXP mapFileSEXP, SEXP newFormatSEXP, SEXP newVersionSEXP, SEXP batchSizeSEXP) {
BEGIN_RCPP
    Rcpp::RObject rcpp_result_gen;
    Rcpp::RNGScope rcpp_rngScope_gen;
    Rcpp::traits::input_parameter< const Rcpp::List& >::type vcfInfo(vcfInfoSEXP);
    Rcpp::traits::input_parameter< const std::string& >::type newFile(newFileSEXP);
    Rcpp::traits::input_parameter< const std::string& >::type famFile(famFileSEXP);
    Rcpp::traits::input_parameter< const std::string& >::type mapFile(mapFileSEXP);
    Rcpp::traits::input_parameter< int >::type newFormat(newFormatSEXP);
    Rcpp::traits::input_parameter< int >::type newVersion(newVersionSEXP);
    Rcpp::traits::input_parameter< int >::type batchSize(batchSizeSEXP);
    rcpp_result_gen = Rcpp::wrap(BDConvertVCFC(vcfInfo, newFile, famFile, mapFile, newFormat, newVersion, batchSize));
    return rcpp_result_gen;
END_RCPP
}
// GetBDose4Header
Rcpp::List GetBDose4Header(std::string& filename);
RcppExport SEXP _BinaryDosage_GetBDose4Header(SEXP filenameSEXP) {
BEGIN_RCPP
    Rcpp::RObject rcpp_result_gen;
    Rcpp::RNGScope rcpp_rngScope_gen;
    Rcpp::traits::input_parameter< std::string& >::type filename(filenameSEXP);
    rcpp_result_gen = Rcpp::wrap(GetBDose4Header(filename));
    return rcpp_result_gen;
END_RCPP
}
// GetBDoseFormatC
Rcpp::List GetBDoseFormatC(const std::string& bdFilename);
RcppExport SEXP _BinaryDosage_GetBDoseFormatC(SEXP bdFilenameSEXP) {
BEGIN_RCPP
    Rcpp::RObject rcpp_result_gen;
    Rcpp::RNGScope rcpp_rngScope_gen;
    Rcpp::traits::input_parameter< const std::string& >::type bdFilename(bdFilenameSEXP);
    rcpp_result_gen = Rcpp::wrap(GetBDoseFormatC(bdFilename));
    return rcpp_result_gen;
END_RCPP
}
// GetBinaryDosage1Info
Rcpp::List GetBinaryDosage1Info(const std::string& bdFilename, const Rcpp::DataFrame& subjects, const Rcpp::DataFrame& snps, const int index);
RcppExport SEXP _BinaryDosage_GetBinaryDosage1Info(SEXP bdFilenameSEXP, SEXP subjectsSEXP, SEXP snpsSEXP, SEXP indexSEXP) {
BEGIN_RCPP
    Rcpp::RObject rcpp_result_gen;
    Rcpp::RNGScope rcpp_rngScope_gen;
    Rcpp::traits::input_parameter< const std::string& >::type bdFilename(bdFilenameSEXP);
    Rcpp::traits::input_parameter< const Rcpp::DataFrame& >::type subjects(subjectsSEXP);
    Rcpp::traits::input_parameter< const Rcpp::DataFrame& >::type snps(snpsSEXP);
    Rcpp::traits::input_parameter< const int >::type index(indexSEXP);
    rcpp_result_gen = Rcpp::wrap(GetBinaryDosage1Info(bdFilename, subjects, snps, index));
    return rcpp_result_gen;
END_RCPP
}
// GetBinaryDosage4Info
Rcpp::List GetBinaryDosage4Info(const std::string& bdFilename, const int index);
RcppExport SEXP _BinaryDosage_GetBinaryDosage4Info(SEXP bdFilenameSEXP, SEXP indexSEXP) {
BEGIN_RCPP
    Rcpp::RObject rcpp_result_gen;
    Rcpp::RNGScope rcpp_rngScope_gen;
    Rcpp::traits::input_parameter< const std::string& >::type bdFilename(bdFilenameSEXP);
    Rcpp::traits::input_parameter< const int >::type index(indexSEXP);
    rcpp_result_gen = Rcpp::wrap(GetBinaryDosage4Info(bdFilename, index));
    return rcpp_result_gen;
END_RCPP
}
// GetSNPValuesC
int GetSNPValuesC(const std::string& filename, const std::string& filetype, int geneProb, const Rcpp::IntegerVector& subVec, const Rcpp::IntegerVector snpVec, const Rcpp::IntegerVector& indices, Rcpp::NumericMatrix& valueMatrix, const int numSubjects, const int numSNPs);
RcppExport SEXP _BinaryDosage_GetSNPValuesC(SEXP filenameSEXP, SEXP filetypeSEXP, SEXP geneProbSEXP, SEXP subVecSEXP, SEXP snpVecSEXP, SEXP indicesSEXP, SEXP valueMatrixSEXP, SEXP numSubjectsSEXP, SEXP numSNPsSEXP) {
BEGIN_RCPP
    Rcpp::RObject rcpp_result_gen;
    Rcpp::RNGScope rcpp_rngScope_gen;
    Rcpp::traits::input_parameter< const std::string& >::type filename(filenameSEXP);
    Rcpp::traits::input_parameter< const std::string& >::type filetype(filetypeSEXP);
    Rcpp::traits::input_parameter< int >::type geneProb(geneProbSEXP);
    Rcpp::traits::input_parameter< const Rcpp::IntegerVector& >::type subVec(subVecSEXP);
    Rcpp::traits::input_parameter< const Rcpp::IntegerVector >::type snpVec(snpVecSEXP);
    Rcpp::traits::input_parameter< const Rcpp::IntegerVector& >::type indices(indicesSEXP);
    Rcpp::traits::input_parameter< Rcpp::NumericMatrix& >::type valueMatrix(valueMatrixSEXP);
    Rcpp::traits::input_parameter< const int >::type numSubjects(numSubjectsSEXP);
    Rcpp::traits::input_parameter< const int >::type numSNPs(numSNPsSEXP);
    rcpp_result_gen = Rcpp::wrap(GetSNPValuesC(filename, filetype, geneProb, subVec, snpVec, indices, valueMatrix, numSubjects, numSNPs));
    return rcpp_result_gen;
END_RCPP
}
// GetAlleleFreqC
int GetAlleleFreqC(const std::string& filename, const std::string& filetype, const Rcpp::IntegerVector& subVec, const Rcpp::IntegerVector snpVec, const Rcpp::IntegerVector& indices, Rcpp::NumericVector& freqVec, const int numSubjects, const int numSNPs);
RcppExport SEXP _BinaryDosage_GetAlleleFreqC(SEXP filenameSEXP, SEXP filetypeSEXP, SEXP subVecSEXP, SEXP snpVecSEXP, SEXP indicesSEXP, SEXP freqVecSEXP, SEXP numSubjectsSEXP, SEXP numSNPsSEXP) {
BEGIN_RCPP
    Rcpp::RObject rcpp_result_gen;
    Rcpp::RNGScope rcpp_rngScope_gen;
    Rcpp::traits::input_parameter< const std::string& >::type filename(filenameSEXP);
    Rcpp::traits::input_parameter< const std::string& >::type filetype(filetypeSEXP);
    Rcpp::traits::input_parameter< const Rcpp::IntegerVector& >::type subVec(subVecSEXP);
    Rcpp::traits::input_parameter< const Rcpp::IntegerVector >::type snpVec(snpVecSEXP);
    Rcpp::traits::input_parameter< const Rcpp::IntegerVector& >::type indices(indicesSEXP);
    Rcpp::traits::input_parameter< Rcpp::NumericVector& >::type freqVec(freqVecSEXP);
    Rcpp::traits::input_parameter< const int >::type numSubjects(numSubjectsSEXP);
    Rcpp::traits::input_parameter< const int >::type numSNPs(numSNPsSEXP);
    rcpp_result_gen = Rcpp::wrap(GetAlleleFreqC(filename, filetype, subVec, snpVec, indices, freqVec, numSubjects, numSNPs));
    return rcpp_result_gen;
END_RCPP
}
// GetVCFHeaderC
Rcpp::List GetVCFHeaderC(std::string& vcfFile);
RcppExport SEXP _BinaryDosage_GetVCFHeaderC(SEXP vcfFileSEXP) {
BEGIN_RCPP
    Rcpp::RObject rcpp_result_gen;
    Rcpp::RNGScope rcpp_rngScope_gen;
    Rcpp::traits::input_parameter< std::string& >::type vcfFile(vcfFileSEXP);
    rcpp_result_gen = Rcpp::wrap(GetVCFHeaderC(vcfFile));
    return rcpp_result_gen;
END_RCPP
}
// GetVCFSNPInfoC
Rcpp::List GetVCFSNPInfoC(std::string& filename, int startData, int reserve);
RcppExport SEXP _BinaryDosage_GetVCFSNPInfoC(SEXP filenameSEXP, SEXP startDataSEXP, SEXP reserveSEXP) {
BEGIN_RCPP
    Rcpp::RObject rcpp_result_gen;
    Rcpp::RNGScope rcpp_rngScope_gen;
    Rcpp::traits::input_parameter< std::string& >::type filename(filenameSEXP);
    Rcpp::traits::input_parameter< int >::type startData(startDataSEXP);
    Rcpp::traits::input_parameter< int >::type reserve(reserveSEXP);
    rcpp_result_gen = Rcpp::wrap(GetVCFSNPInfoC(filename, startData, reserve));
    return rcpp_result_gen;
END_RCPP
}
// MergeBDC
int MergeBDC(const std::string& mergeFilename, const Rcpp::StringVector& filenames, const Rcpp::List& mergeInfo, const Rcpp::List& bdInfoList, const std::string& famFilename, const std::string& mapFilename, int format, int version, int batchSize);
RcppExport SEXP _BinaryDosage_MergeBDC(SEXP mergeFilenameSEXP, SEXP filenamesSEXP, SEXP mergeInfoSEXP, SEXP bdInfoListSEXP, SEXP famFilenameSEXP, SEXP mapFilenameSEXP, SEXP formatSEXP, SEXP versionSEXP, SEXP batchSizeSEXP) {
BEGIN_RCPP
    Rcpp::RObject rcpp_result_gen;
    Rcpp::RNGScope rcpp_rngScope_gen;
    Rcpp::traits::input_parameter< const std::string& >::type mergeFilename(mergeFilenameSEXP);
    Rcpp::traits::input_parameter< const Rcpp::StringVector& >::type filenames(filenamesSEXP);
    Rcpp::traits::input_parameter< const Rcpp::List& >::type mergeInfo(mergeInfoSEXP);
    Rcpp::traits::input_parameter< const Rcpp::List& >::type bdInfoList(bdInfoListSEXP);
    Rcpp::traits::input_parameter< const std::string& >::type famFilename(famFilenameSEXP);
    Rcpp::traits::input_parameter< const std::string& >::type mapFilename(mapFilenameSEXP);
    Rcpp::traits::input_parameter< int >::type format(formatSEXP);
    Rcpp::traits::input_parameter< int >::type version(versionSEXP);
    Rcpp::traits::input_parameter< int >::type batchSize(batchSizeSEXP);
    rcpp_result_gen = Rcpp::wrap(MergeBDC(mergeFilename, filenames, mergeInfo, bdInfoList, famFilename, mapFilename, format, version, batchSize));
    return rcpp_result_gen;
END_RCPP
}

static const R_CallMethodDef CallEntries[] = {
    {"_BinaryDosage_BDConvertC", (DL_FUNC) &_BinaryDosage_BDConvertC, 6},
    {"_BinaryDosage_BDConvertVCFC", (DL_FUNC) &_BinaryDosage_BDConvertVCFC, 7},
    {"_BinaryDosage_GetBDose4Header", (DL_FUNC) &_BinaryDosage_GetBDose4Header, 1},
    {"_BinaryDosage_GetBDoseFormatC", (DL_FUNC) &_BinaryDosage_GetBDoseFormatC, 1},
    {"_BinaryDosage_GetBinaryDosage1Info", (DL_FUNC) &_BinaryDosage_GetBinaryDosage1Info, 4},
    {"_BinaryDosage_GetBinaryDosage4Info", (DL_FUNC) &_BinaryDosage_GetBinaryDosage4Info, 2},
    {"_BinaryDosage_GetSNPValuesC", (DL_FUNC) &_BinaryDosage_GetSNPValuesC, 9},
    {"_BinaryDosage_GetAlleleFreqC", (DL_FUNC) &_BinaryDosage_GetAlleleFreqC, 8},
    {"_BinaryDosage_GetVCFHeaderC", (DL_FUNC) &_BinaryDosage_GetVCFHeaderC, 1},
    {"_BinaryDosage_GetVCFSNPInfoC", (DL_FUNC) &_BinaryDosage_GetVCFSNPInfoC, 3},
    {"_BinaryDosage_MergeBDC", (DL_FUNC) &_BinaryDosage_MergeBDC, 9},
    {NULL, NULL, 0}
};

RcppExport void R_init_BinaryDosage(DllInfo *dll) {
    R_registerRoutines(dll, NULL, CallEntries, NULL, NULL);
    R_useDynamicSymbols(dll, FALSE);
}

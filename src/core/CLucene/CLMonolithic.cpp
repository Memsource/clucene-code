/*------------------------------------------------------------------------------
* Copyright (C) 2003-2006 Ben van Klinken and the CLucene Team
*
* Distributable under the terms of either the Apache License (Version 2.0) or
* the GNU Lesser General Public License, as specified in the COPYING file.
------------------------------------------------------------------------------*/
/*
* this is a monolithic file that can be used to compile clucene using one source file.
* it simplifies some build processes by avoiding static & dynamic compalation pitfalls.
*
* note: when creating a project add either this file, or all the other .cpp files, not both!
*/
#include "CLucene/StdHeader.cpp"
#include "CLucene/debug/error.cpp"
#include "CLucene/analysis/Analyzers.cpp"
#include "CLucene/analysis/AnalysisHeader.cpp"
#include "CLucene/analysis/standard/StandardAnalyzer.cpp"
#include "CLucene/analysis/standard/StandardFilter.cpp"
#include "CLucene/analysis/standard/StandardTokenizer.cpp"
#include "CLucene/document/DateField.cpp"
#include "CLucene/document/DateTools.cpp"
#include "CLucene/document/Document.cpp"
#include "CLucene/document/FieldSelector.cpp"
#include "CLucene/document/NumberTools.cpp"
#include "CLucene/document/Field.cpp"
#include "CLucene/index/CompoundFile.cpp"
#include "CLucene/index/DirectoryIndexReader.cpp"
#include "CLucene/index/DocumentsWriter.cpp"
#include "CLucene/index/DocumentsWriterThreadState.cpp"
#include "CLucene/index/FieldInfos.cpp"
#include "CLucene/index/FieldsReader.cpp"
#include "CLucene/index/FieldsWriter.cpp"
#include "CLucene/index/IndexDeletionPolicy.cpp"
#include "CLucene/index/IndexFileDeleter.cpp"
#include "CLucene/index/IndexFileNameFilter.cpp"
#include "CLucene/index/IndexFileNames.cpp"
#include "CLucene/index/IndexModifier.cpp"
#include "CLucene/index/IndexWriter.cpp"
#include "CLucene/index/IndexReader.cpp"
#include "CLucene/index/MergePolicy.cpp"
#include "CLucene/index/MergeScheduler.cpp"
#include "CLucene/index/MultiReader.cpp"
#include "CLucene/index/MultiSegmentReader.cpp"
#include "CLucene/index/MultipleTermPositions.cpp"
#include "CLucene/index/Payload.cpp"
#include "CLucene/index/SegmentInfos.cpp"
#include "CLucene/index/SegmentMergeInfo.cpp"
#include "CLucene/index/SegmentMergeQueue.cpp"
#include "CLucene/index/SegmentMerger.cpp"
#include "CLucene/index/SegmentReader.cpp"
#include "CLucene/index/SegmentTermDocs.cpp"
#include "CLucene/index/SegmentTermEnum.cpp"
#include "CLucene/index/SegmentTermPositions.cpp"
#include "CLucene/index/SegmentTermVector.cpp"
#include "CLucene/index/SkipListReader.cpp"
#include "CLucene/index/SkipListWriter.cpp"
#include "CLucene/index/Term.cpp"
#include "CLucene/index/Terms.cpp"
#include "CLucene/index/TermInfo.cpp"
#include "CLucene/index/TermInfosReader.cpp"
#include "CLucene/index/TermInfosWriter.cpp"
#include "CLucene/index/TermVectorReader.cpp"
#include "CLucene/index/TermVectorWriter.cpp"
#include "CLucene/queryParser/FastCharStream.cpp"
#include "CLucene/queryParser/QueryParserTokenManager.cpp"
#include "CLucene/queryParser/MultiFieldQueryParser.cpp"
#include "CLucene/queryParser/QueryParser.cpp"
#include "CLucene/queryParser/QueryToken.cpp"
#include "CLucene/search/BooleanQuery.cpp"
#include "CLucene/search/BooleanScorer.cpp"
#include "CLucene/search/BooleanScorer2.cpp"
#include "CLucene/search/CachingWrapperFilter.cpp"
#include "CLucene/search/ChainedFilter.cpp"
#include "CLucene/search/Compare.cpp"
#include "CLucene/search/DateFilter.cpp"
#include "CLucene/search/ConjunctionScorer.cpp"
#include "CLucene/search/DisjunctionSumScorer.cpp"
#include "CLucene/search/ExactPhraseScorer.cpp"
#include "CLucene/search/Explanation.cpp"
#include "CLucene/search/FieldCache.cpp"
#include "CLucene/search/FieldCacheImpl.cpp"
#include "CLucene/search/FieldDocSortedHitQueue.cpp"
#include "CLucene/search/FieldSortedHitQueue.cpp"
#include "CLucene/search/FilteredTermEnum.cpp"
#include "CLucene/search/FuzzyQuery.cpp"
#include "CLucene/search/Hits.cpp"
#include "CLucene/search/HitQueue.cpp"
#include "CLucene/search/IndexSearcher.cpp"
#include "CLucene/search/MatchAllDocsQuery.cpp"
#include "CLucene/search/MultiSearcher.cpp"
#include "CLucene/search/MultiTermQuery.cpp"
#include "CLucene/search/MultiPhraseQuery.cpp"
#include "CLucene/search/PhrasePositions.cpp"
#include "CLucene/search/PhraseQuery.cpp"
#include "CLucene/search/PhraseScorer.cpp"
#include "CLucene/search/PrefixQuery.cpp"
#include "CLucene/search/QueryFilter.cpp"
#include "CLucene/search/RangeQuery.cpp"
#include "CLucene/search/RangeFilter.cpp"
#include "CLucene/search/SearchHeader.cpp"
#include "CLucene/search/Similarity.cpp"
#include "CLucene/search/SloppyPhraseScorer.cpp"
#include "CLucene/search/Scorer.cpp"
#include "CLucene/search/ScorerDocQueue.cpp"
#include "CLucene/search/Sort.cpp"
#include "CLucene/search/TermQuery.cpp"
#include "CLucene/search/TermScorer.cpp"
#include "CLucene/search/WildcardQuery.cpp"
#include "CLucene/search/WildcardTermEnum.cpp"
#include "CLucene/store/FSDirectory.cpp"
#include "CLucene/store/IndexInput.cpp"
#include "CLucene/store/Lock.cpp"
#include "CLucene/store/LockFactory.cpp"
#include "CLucene/store/MMapDirectory.cpp"
#include "CLucene/store/IndexOutput.cpp"
#include "CLucene/store/Directory.cpp"
#include "CLucene/store/RAMDirectory.cpp"
#include "CLucene/store/RawIndexInput.cpp"
#include "CLucene/store/RawIndexOutput.cpp"
#include "CLucene/store/RawDirectory.cpp"
#include "CLucene/store/SharedHandle.cpp"
#include "CLucene/util/BitSet.cpp"
#include "CLucene/util/Equators.cpp"
#include "CLucene/util/FastCharStream.cpp"
#include "CLucene/util/MD5Digester.cpp"
#include "CLucene/util/Reader.cpp"
#include "CLucene/util/StringIntern.cpp"
#include "CLucene/util/ThreadLocal.cpp"

#include "CLucene/CLSharedMonolithic.cpp"

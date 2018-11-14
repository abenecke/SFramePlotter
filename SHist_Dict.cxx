// Do NOT change. Changes will be lost next time file is generated

#define R__DICTIONARY_FILENAME SHist_Dict

/*******************************************************************/
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <assert.h>
#define G__DICTIONARY
#include "RConfig.h"
#include "TClass.h"
#include "TDictAttributeMap.h"
#include "TInterpreter.h"
#include "TROOT.h"
#include "TBuffer.h"
#include "TMemberInspector.h"
#include "TInterpreter.h"
#include "TVirtualMutex.h"
#include "TError.h"

#ifndef G__ROOT
#define G__ROOT
#endif

#include "RtypesImp.h"
#include "TIsAProxy.h"
#include "TFileMergeInfo.h"
#include <algorithm>
#include "TCollectionProxyInfo.h"
/*******************************************************************/

#include "TDataMember.h"

// Since CINT ignores the std namespace, we need to do so in this file.
namespace std {} using namespace std;

// Header files passed as explicit arguments
#include "SHist.h"

// Header files passed via #pragma extra_include

namespace ROOT {
   static void delete_SHist(void *p);
   static void deleteArray_SHist(void *p);
   static void destruct_SHist(void *p);
   static void streamer_SHist(TBuffer &buf, void *obj);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::SHist*)
   {
      ::SHist *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::SHist >(0);
      static ::ROOT::TGenericClassInfo 
         instance("SHist", ::SHist::Class_Version(), "SHist.h", 11,
                  typeid(::SHist), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::SHist::Dictionary, isa_proxy, 16,
                  sizeof(::SHist) );
      instance.SetDelete(&delete_SHist);
      instance.SetDeleteArray(&deleteArray_SHist);
      instance.SetDestructor(&destruct_SHist);
      instance.SetStreamerFunc(&streamer_SHist);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::SHist*)
   {
      return GenerateInitInstanceLocal((::SHist*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_(Init) = GenerateInitInstanceLocal((const ::SHist*)0x0); R__UseDummy(_R__UNIQUE_(Init));
} // end of namespace ROOT

//______________________________________________________________________________
atomic_TClass_ptr SHist::fgIsA(0);  // static to hold class pointer

//______________________________________________________________________________
const char *SHist::Class_Name()
{
   return "SHist";
}

//______________________________________________________________________________
const char *SHist::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::SHist*)0x0)->GetImplFileName();
}

//______________________________________________________________________________
int SHist::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::SHist*)0x0)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *SHist::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::SHist*)0x0)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *SHist::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD2(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::SHist*)0x0)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
void SHist::Streamer(TBuffer &R__b)
{
   // Stream an object of class SHist.

   TObject::Streamer(R__b);
}

namespace ROOT {
   // Wrapper around operator delete
   static void delete_SHist(void *p) {
      delete ((::SHist*)p);
   }
   static void deleteArray_SHist(void *p) {
      delete [] ((::SHist*)p);
   }
   static void destruct_SHist(void *p) {
      typedef ::SHist current_t;
      ((current_t*)p)->~current_t();
   }
   // Wrapper around a custom streamer member function.
   static void streamer_SHist(TBuffer &buf, void *obj) {
      ((::SHist*)obj)->::SHist::Streamer(buf);
   }
} // end of namespace ROOT for class ::SHist

namespace {
  void TriggerDictionaryInitialization_SHist_Dict_Impl() {
    static const char* headers[] = {
"SHist.h",
0
    };
    static const char* includePaths[] = {
"/.",
"/cvmfs/cms.cern.ch/slc6_amd64_gcc530/lcg/root/6.06.00-ikhhed5/include",
"/nfs/dust/cms/user/abenecke/scripts/ForAnna/",
0
    };
    static const char* fwdDeclCode = R"DICTFWDDCLS(
#line 1 "SHist_Dict dictionary forward declarations' payload"
#pragma clang diagnostic ignored "-Wkeyword-compat"
#pragma clang diagnostic ignored "-Wignored-attributes"
#pragma clang diagnostic ignored "-Wreturn-type-c-linkage"
extern int __Cling_Autoloading_Map;
class __attribute__((annotate(R"ATTRDUMP(SFrame histograms)ATTRDUMP"))) __attribute__((annotate("$clingAutoload$SHist.h")))  SHist;
)DICTFWDDCLS";
    static const char* payloadCode = R"DICTPAYLOAD(
#line 1 "SHist_Dict dictionary payload"

#ifndef G__VECTOR_HAS_CLASS_ITERATOR
  #define G__VECTOR_HAS_CLASS_ITERATOR 1
#endif

#define _BACKWARD_BACKWARD_WARNING_H
#include "SHist.h"

#undef  _BACKWARD_BACKWARD_WARNING_H
)DICTPAYLOAD";
    static const char* classesHeaders[]={
"SHist", payloadCode, "@",
nullptr};

    static bool isInitialized = false;
    if (!isInitialized) {
      TROOT::RegisterModule("SHist_Dict",
        headers, includePaths, payloadCode, fwdDeclCode,
        TriggerDictionaryInitialization_SHist_Dict_Impl, {}, classesHeaders);
      isInitialized = true;
    }
  }
  static struct DictInit {
    DictInit() {
      TriggerDictionaryInitialization_SHist_Dict_Impl();
    }
  } __TheDictionaryInitializer;
}
void TriggerDictionaryInitialization_SHist_Dict() {
  TriggerDictionaryInitialization_SHist_Dict_Impl();
}

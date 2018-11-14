// Do NOT change. Changes will be lost next time file is generated

#define R__DICTIONARY_FILENAME BaseSteer_Dict

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
#include "BaseSteer.h"

// Header files passed via #pragma extra_include

namespace ROOT {
   static void *new_BaseSteer(void *p = 0);
   static void *newArray_BaseSteer(Long_t size, void *p);
   static void delete_BaseSteer(void *p);
   static void deleteArray_BaseSteer(void *p);
   static void destruct_BaseSteer(void *p);
   static void streamer_BaseSteer(TBuffer &buf, void *obj);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::BaseSteer*)
   {
      ::BaseSteer *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::BaseSteer >(0);
      static ::ROOT::TGenericClassInfo 
         instance("BaseSteer", ::BaseSteer::Class_Version(), "BaseSteer.h", 12,
                  typeid(::BaseSteer), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::BaseSteer::Dictionary, isa_proxy, 16,
                  sizeof(::BaseSteer) );
      instance.SetNew(&new_BaseSteer);
      instance.SetNewArray(&newArray_BaseSteer);
      instance.SetDelete(&delete_BaseSteer);
      instance.SetDeleteArray(&deleteArray_BaseSteer);
      instance.SetDestructor(&destruct_BaseSteer);
      instance.SetStreamerFunc(&streamer_BaseSteer);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::BaseSteer*)
   {
      return GenerateInitInstanceLocal((::BaseSteer*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_(Init) = GenerateInitInstanceLocal((const ::BaseSteer*)0x0); R__UseDummy(_R__UNIQUE_(Init));
} // end of namespace ROOT

//______________________________________________________________________________
atomic_TClass_ptr BaseSteer::fgIsA(0);  // static to hold class pointer

//______________________________________________________________________________
const char *BaseSteer::Class_Name()
{
   return "BaseSteer";
}

//______________________________________________________________________________
const char *BaseSteer::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::BaseSteer*)0x0)->GetImplFileName();
}

//______________________________________________________________________________
int BaseSteer::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::BaseSteer*)0x0)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *BaseSteer::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::BaseSteer*)0x0)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *BaseSteer::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD2(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::BaseSteer*)0x0)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
void BaseSteer::Streamer(TBuffer &R__b)
{
   // Stream an object of class BaseSteer.

   TNamed::Streamer(R__b);
}

namespace ROOT {
   // Wrappers around operator new
   static void *new_BaseSteer(void *p) {
      return  p ? new(p) ::BaseSteer : new ::BaseSteer;
   }
   static void *newArray_BaseSteer(Long_t nElements, void *p) {
      return p ? new(p) ::BaseSteer[nElements] : new ::BaseSteer[nElements];
   }
   // Wrapper around operator delete
   static void delete_BaseSteer(void *p) {
      delete ((::BaseSteer*)p);
   }
   static void deleteArray_BaseSteer(void *p) {
      delete [] ((::BaseSteer*)p);
   }
   static void destruct_BaseSteer(void *p) {
      typedef ::BaseSteer current_t;
      ((current_t*)p)->~current_t();
   }
   // Wrapper around a custom streamer member function.
   static void streamer_BaseSteer(TBuffer &buf, void *obj) {
      ((::BaseSteer*)obj)->::BaseSteer::Streamer(buf);
   }
} // end of namespace ROOT for class ::BaseSteer

namespace {
  void TriggerDictionaryInitialization_BaseSteer_Dict_Impl() {
    static const char* headers[] = {
"BaseSteer.h",
0
    };
    static const char* includePaths[] = {
"/.",
"/cvmfs/cms.cern.ch/slc6_amd64_gcc530/lcg/root/6.06.00-ikhhed5/include",
"/nfs/dust/cms/user/abenecke/scripts/ForAnna/",
0
    };
    static const char* fwdDeclCode = R"DICTFWDDCLS(
#line 1 "BaseSteer_Dict dictionary forward declarations' payload"
#pragma clang diagnostic ignored "-Wkeyword-compat"
#pragma clang diagnostic ignored "-Wignored-attributes"
#pragma clang diagnostic ignored "-Wreturn-type-c-linkage"
extern int __Cling_Autoloading_Map;
class __attribute__((annotate("$clingAutoload$BaseSteer.h")))  BaseSteer;
)DICTFWDDCLS";
    static const char* payloadCode = R"DICTPAYLOAD(
#line 1 "BaseSteer_Dict dictionary payload"

#ifndef G__VECTOR_HAS_CLASS_ITERATOR
  #define G__VECTOR_HAS_CLASS_ITERATOR 1
#endif

#define _BACKWARD_BACKWARD_WARNING_H
#include "BaseSteer.h"

#undef  _BACKWARD_BACKWARD_WARNING_H
)DICTPAYLOAD";
    static const char* classesHeaders[]={
"BaseSteer", payloadCode, "@",
nullptr};

    static bool isInitialized = false;
    if (!isInitialized) {
      TROOT::RegisterModule("BaseSteer_Dict",
        headers, includePaths, payloadCode, fwdDeclCode,
        TriggerDictionaryInitialization_BaseSteer_Dict_Impl, {}, classesHeaders);
      isInitialized = true;
    }
  }
  static struct DictInit {
    DictInit() {
      TriggerDictionaryInitialization_BaseSteer_Dict_Impl();
    }
  } __TheDictionaryInitializer;
}
void TriggerDictionaryInitialization_BaseSteer_Dict() {
  TriggerDictionaryInitialization_BaseSteer_Dict_Impl();
}

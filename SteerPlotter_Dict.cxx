// Do NOT change. Changes will be lost next time file is generated

#define R__DICTIONARY_FILENAME SteerPlotter_Dict

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
#include "SteerPlotter.h"

// Header files passed via #pragma extra_include

namespace ROOT {
   static void *new_SteerPlotter(void *p = 0);
   static void *newArray_SteerPlotter(Long_t size, void *p);
   static void delete_SteerPlotter(void *p);
   static void deleteArray_SteerPlotter(void *p);
   static void destruct_SteerPlotter(void *p);
   static void streamer_SteerPlotter(TBuffer &buf, void *obj);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::SteerPlotter*)
   {
      ::SteerPlotter *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::SteerPlotter >(0);
      static ::ROOT::TGenericClassInfo 
         instance("SteerPlotter", ::SteerPlotter::Class_Version(), "SteerPlotter.h", 11,
                  typeid(::SteerPlotter), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::SteerPlotter::Dictionary, isa_proxy, 16,
                  sizeof(::SteerPlotter) );
      instance.SetNew(&new_SteerPlotter);
      instance.SetNewArray(&newArray_SteerPlotter);
      instance.SetDelete(&delete_SteerPlotter);
      instance.SetDeleteArray(&deleteArray_SteerPlotter);
      instance.SetDestructor(&destruct_SteerPlotter);
      instance.SetStreamerFunc(&streamer_SteerPlotter);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::SteerPlotter*)
   {
      return GenerateInitInstanceLocal((::SteerPlotter*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_(Init) = GenerateInitInstanceLocal((const ::SteerPlotter*)0x0); R__UseDummy(_R__UNIQUE_(Init));
} // end of namespace ROOT

//______________________________________________________________________________
atomic_TClass_ptr SteerPlotter::fgIsA(0);  // static to hold class pointer

//______________________________________________________________________________
const char *SteerPlotter::Class_Name()
{
   return "SteerPlotter";
}

//______________________________________________________________________________
const char *SteerPlotter::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::SteerPlotter*)0x0)->GetImplFileName();
}

//______________________________________________________________________________
int SteerPlotter::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::SteerPlotter*)0x0)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *SteerPlotter::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::SteerPlotter*)0x0)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *SteerPlotter::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD2(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::SteerPlotter*)0x0)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
void SteerPlotter::Streamer(TBuffer &R__b)
{
   // Stream an object of class SteerPlotter.

   BaseSteer::Streamer(R__b);
}

namespace ROOT {
   // Wrappers around operator new
   static void *new_SteerPlotter(void *p) {
      return  p ? new(p) ::SteerPlotter : new ::SteerPlotter;
   }
   static void *newArray_SteerPlotter(Long_t nElements, void *p) {
      return p ? new(p) ::SteerPlotter[nElements] : new ::SteerPlotter[nElements];
   }
   // Wrapper around operator delete
   static void delete_SteerPlotter(void *p) {
      delete ((::SteerPlotter*)p);
   }
   static void deleteArray_SteerPlotter(void *p) {
      delete [] ((::SteerPlotter*)p);
   }
   static void destruct_SteerPlotter(void *p) {
      typedef ::SteerPlotter current_t;
      ((current_t*)p)->~current_t();
   }
   // Wrapper around a custom streamer member function.
   static void streamer_SteerPlotter(TBuffer &buf, void *obj) {
      ((::SteerPlotter*)obj)->::SteerPlotter::Streamer(buf);
   }
} // end of namespace ROOT for class ::SteerPlotter

namespace {
  void TriggerDictionaryInitialization_SteerPlotter_Dict_Impl() {
    static const char* headers[] = {
"SteerPlotter.h",
0
    };
    static const char* includePaths[] = {
"/.",
"/cvmfs/cms.cern.ch/slc6_amd64_gcc530/lcg/root/6.06.00-ikhhed5/include",
"/nfs/dust/cms/user/abenecke/scripts/ForAnna/",
0
    };
    static const char* fwdDeclCode = R"DICTFWDDCLS(
#line 1 "SteerPlotter_Dict dictionary forward declarations' payload"
#pragma clang diagnostic ignored "-Wkeyword-compat"
#pragma clang diagnostic ignored "-Wignored-attributes"
#pragma clang diagnostic ignored "-Wreturn-type-c-linkage"
extern int __Cling_Autoloading_Map;
class __attribute__((annotate(R"ATTRDUMP(steering class for the SFrame Plotter)ATTRDUMP"))) __attribute__((annotate("$clingAutoload$SteerPlotter.h")))  SteerPlotter;
)DICTFWDDCLS";
    static const char* payloadCode = R"DICTPAYLOAD(
#line 1 "SteerPlotter_Dict dictionary payload"

#ifndef G__VECTOR_HAS_CLASS_ITERATOR
  #define G__VECTOR_HAS_CLASS_ITERATOR 1
#endif

#define _BACKWARD_BACKWARD_WARNING_H
#include "SteerPlotter.h"

#undef  _BACKWARD_BACKWARD_WARNING_H
)DICTPAYLOAD";
    static const char* classesHeaders[]={
"SteerPlotter", payloadCode, "@",
nullptr};

    static bool isInitialized = false;
    if (!isInitialized) {
      TROOT::RegisterModule("SteerPlotter_Dict",
        headers, includePaths, payloadCode, fwdDeclCode,
        TriggerDictionaryInitialization_SteerPlotter_Dict_Impl, {}, classesHeaders);
      isInitialized = true;
    }
  }
  static struct DictInit {
    DictInit() {
      TriggerDictionaryInitialization_SteerPlotter_Dict_Impl();
    }
  } __TheDictionaryInitializer;
}
void TriggerDictionaryInitialization_SteerPlotter_Dict() {
  TriggerDictionaryInitialization_SteerPlotter_Dict_Impl();
}

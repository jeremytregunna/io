//metadoc LLVM copyright Jeremy Tregunna, 2011
//metadoc LLVM license MIT

#ifndef IOLLVMCONTEXT_DEFINED
#define IOLLVMCONTEXT_DEFINED 1

#include "IoObject.h"
#include "IoMessage.h"
#include <llvm-c/Core.h>

typedef IoObject IoLLVMContext;

typedef struct
{
	LLVMContextRef context;
} IoLLVMContextData;

IoLLVMContext* IoLLVMContext_proto(void*);
IoLLVMContext* IoLLVMContext_rawClone(IoLLVMContext*);
IoLLVMContext* IoLLVMContext_new(void*);
void IoLLVMContext_free(IoLLVMContext*);

IoObject* IoLLVMContext_getGlobalContext(IoObject*, IoObject*, IoMessage*);
IoObject* IoLLVMContext_getMDKindID(IoObject*, IoObject*, IoMessage*);
IoObject* IoLLVMContext_getMDKindIDInContext(IoObject*, IoObject*, IoMessage*);

#endif
